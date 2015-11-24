% prepare test data files for MarkovPrediction exe

% global vars 
cd C:/Workspace/GitHub/MarkovPrediction/
L = 1000; % test series length
p = 50; % prediction range
t = (1:L)';
disp('Globals loaded!');

%% constant value
x = 5*ones(L,1); %#ok<*NASGU>
save('sample_input.txt', 'x', '-ascii');
disp('Done')

%% straight line
x = linspace(0, 1, L)';
save('sample_input.txt', 'x', '-ascii');
disp('Done')

%% quadratic
x = (t/100).^2;
plot(t, x);
save('sample_input.txt', 'x', '-ascii');
disp('Done')

%% exponential
x = exp(t/500);
plot(t, x);
save('sample_input.txt', 'x', '-ascii');
disp('Done')

%% periodic signal (monochromatic)
x = sin(2*pi*(t+40)/200);
plot(t,x);
save('sample_input.txt', 'x', '-ascii');
disp('Done')

%% periodic signal (multiple sine waves)
x = sin(2*pi*t/200) + sin(2*pi*t/50);
plot(t,x);
save('sample_input.txt', 'x', '-ascii');
disp('Done')

%% Load results and plot prediction scenarios

y = load('prediction.txt', '-ascii');
s = size(y);
plot(t, x, '-ob', L+1:L+s(1), y, '-xr');
xlim([L-s(1), L+s(1)]);
disp('Done')
