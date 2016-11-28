addpath ../matlab

MPIbuffer=zeros(1,13107200); %100MB buffer
%err=MPI_Buffer_attach(MPIbuffer,100*1024*1024);


GetMPIEnvironment;
status=MPI_Status;
comm=MPI_COMM_WORLD;
comm_size=0;
my_rank=0;
err=MPI_Init(0,0);
err=MPI_Comm_size(MPI_COMM_WORLD,comm_size);
err=MPI_Comm_rank(MPI_COMM_WORLD,my_rank);
% Do a synchronized start. 
err=MPI_Barrier(MPI_COMM_WORLD);
n_image_x = 2.^(10+1)*comm_size; % Set image size (use powers of 2). 
n_image_y = 2.^10; 
n_point = 100; % Number of points to put in each sub-image. 
% Set filter size (use powers of 2). 
n_filter_x = 2.^5; 
n_filter_y = 2.^5; 
n_trial = 20; 
% Set the number of times to filter. 
% Computer number of operations. 
total_ops = 2.*n_trial*n_filter_x*n_filter_y*n_image_x*n_image_y; 
if(rem(n_image_x,comm_size) ~= 0)
	disp('ERROR: processors need to evenly divide image');
	exit; 
end
disp(['my_rank: ',num2str(my_rank)]); % Print rank.
left = my_rank - 1; % Set who is source and who is destination.
if (left < 0)
	left = comm_size - 1; 
end
right = my_rank + 1; 
if (right >= comm_size)
	right = 0; 
end
tag = 1; % Create a unique tag id for this message. 
start_time = zeros(n_trial); % Create timing matrices. 
end_time = start_time; 
zero_clock = clock; % Get a zero clock.
n_sub_image_x = n_image_x./comm_size; % Compute sub_images for each processor. 
n_sub_image_y = n_image_y;
% Create starting image and working images.. 
sub_image0 = rand(n_sub_image_x,n_sub_image_y).^10; 
sub_image = sub_image0; 
work_image = zeros(n_sub_image_x+n_filter_x,n_sub_image_y+n_filter_y); 
% Create kernel. 
x_shape = sin(pi.*(0:(n_filter_x-1))./(n_filter_x-1)).^2; 
y_shape = sin(pi.*(0:(n_filter_y-1))./(n_filter_y-1)).^2; 
kernel = x_shape.' * y_shape; 
% Create box indices. 
lboxw = [1,n_filter_x/2,1,n_sub_image_y]; 
cboxw = [n_filter_x/2+1,n_filter_x/2+n_sub_image_x,1,n_sub_image_y]; 
rboxw = [n_filter_x/2+n_sub_image_x+1,n_sub_image_x+n_filter_x,1,n_sub_image_y];
lboxi = [1,n_filter_x/2,1,n_sub_image_y]; 
rboxi = [n_sub_image_x-n_filter_x/2+1,n_sub_image_x,1,n_sub_image_y]; 
start_time = etime(clock,zero_clock); % Set start time. 
% Loop over each trial. 

r_pad=sub_image(lboxi(1):lboxi(2),lboxi(3):lboxi(4));
l_pad=sub_image(rboxi(1):rboxi(2),rboxi(3):rboxi(4));

for i_trial = 1:n_trial
	%i_trial
	% Copy center sub_image into work_image. 
	work_image(cboxw(1):cboxw(2),cboxw(3):cboxw(4)) = sub_image; 
	if (comm_size > 1)
		ltag = 2.*i_trial;
		rtag = 2.*i_trial+1; 
		
		
		% Send left sub-image. 
		l_sub_image = sub_image(lboxi(1):lboxi(2),lboxi(3):lboxi(4)); 
		%err=MPI_Bsend(l_sub_image,numel(l_sub_image),MPI_DOUBLE,left,ltag,comm);
		% Receive right padding. 
		%err=MPI_Recv(r_pad,numel(l_sub_image),MPI_DOUBLE,right,ltag,comm,status); 
		
		err=MPI_Sendrecv(l_sub_image,numel(l_sub_image),MPI_DOUBLE,left,ltag, ...
						 r_pad,numel(l_sub_image),MPI_DOUBLE,right,ltag, ...
						 comm,status);
		
		
		work_image(rboxw(1):rboxw(2),rboxw(3):rboxw(4)) = r_pad; 
		
		
		% Send right sub-image. 
		r_sub_image = sub_image(rboxi(1):rboxi(2),rboxi(3):rboxi(4)); 
		%err=MPI_Bsend(r_sub_image,numel(r_sub_image),MPI_DOUBLE,right,rtag,comm);
		% Receive left padding. 
		%err=MPI_Recv(l_pad,numel(r_sub_image),MPI_DOUBLE,left,rtag,comm,status); 
		
		err=MPI_Sendrecv(r_sub_image,numel(r_sub_image),MPI_DOUBLE,right,rtag, ...
						 l_pad,numel(r_sub_image),MPI_DOUBLE,left,rtag, ...
						 comm,status);
		
		
		work_image(lboxw(1):lboxw(2),lboxw(3):lboxw(4)) = l_pad;
	end 
	work_image = conv2(work_image,kernel,'same');
	% Compute convolution. 
	% Extract sub_image. 
	sub_image = work_image(cboxw(1):cboxw(2),cboxw(3):cboxw(4));
end 
end_time = etime(clock,zero_clock); 
% Get end time for the this message. 
total_time = end_time - start_time 
% Print the results. 
% Print compute performance. 
gigaflops = total_ops / total_time / 1.e9; 
disp(['GigaFlops: ',num2str(gigaflops)]); 
err=MPI_Finalize(); % Finalize Matlab MPI. 
exit;