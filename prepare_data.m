% prepare test data files for MarkovPrediction exe

% global vars 
cd C:/Workspace/GitHub/MarkovPrediction/
L = 1000;
t = (1:L)';

%% constant value
x = ones(L,1); %#ok<*NASGU>
save('sample_input_00.txt', 'x', '-ascii');

%% straight line
x = linspace(0, 1, L);
save('sample_input_01.txt', 'x', '-ascii');

%% quadratic
x = (t/100).^2;
plot(t, x);
save('sample_input_02.txt', 'x', '-ascii');

%% exponential
x = exp(t/500);
plot(t, x);
save('sample_input_03.txt', 'x', '-ascii');

%% periodic signal (monochromatic)
x = sin(2*pi*(t+40)/200);
plot(t,x);
save('sample_input_04.txt', 'x', '-ascii');

%% periodic signal (multiple sine waves)
x = sin(2*pi*t/200) + sin(2*pi*t/50);
plot(t,x);
save('sample_input_05.txt', 'x', '-ascii');

%% Load results and plot prediction scenarios

y = load('prediction.txt', '-ascii');
s = size(y);
plot(t, x, '-ob', L+1:L+s(1), y, '-xr');
xlim([L-s(1), L+s(1)]);