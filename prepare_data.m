% prepare test data files for MarkovPrediction exe

% global vars 
cd C:/Workspace/GitHub/MarkovPrediction/
L = 1000; % test series length
p = 50; % prediction range
t = (1:L+p)';
disp('Globals loaded!');

%% constant value
x = 5*ones(length(t),1); %#ok<*NASGU>
xOUT = x(1:L);
save('sample_input.txt', 'xOUT', '-ascii');
disp('Done')

%% straight line
x = linspace(0, 1, length(t))';
xOUT = x(1:L);
save('sample_input.txt', 'xOUT', '-ascii');
disp('Done')

%% quadratic
x = (t/100).^2;
plot(t, x);
xOUT = x(1:L);
save('sample_input.txt', 'xOUT', '-ascii');
disp('Done')

%% exponential
x = exp(t/500);
plot(t, x);
xOUT = x(1:L);
save('sample_input.txt', 'xOUT', '-ascii');
disp('Done')

%% periodic signal (monochromatic)
x = sin(2*pi*(t+40)/200);
plot(t,x);
xOUT = x(1:L);
save('sample_input.txt', 'xOUT', '-ascii');
disp('Done')

%% periodic signal (multiple sine waves)
x = sin(2*pi*t/200) + sin(2*pi*t/50);
plot(t,x);
xOUT = x(1:L);
save('sample_input.txt', 'xOUT', '-ascii');
disp('Done')

%% Load results and plot prediction scenarios

font_size = 12;

y = load('prediction.txt', '-ascii');
s = size(y);

subplot(1,2,1);
plot(t, x, '-o'); xlim([1, L-s(1)]);
set(gca, 'xtick', [1; (100:100:900)'; 950], 'Fontsize', font_size);
xlabel('time');
title('Training Series');

subplot(1,2,2);
plot(t, x, '-ob', L+1:L+s(1), y, '-xr');
set(gca, 'Fontsize', font_size);
legend('True Values', 'Prediction');
xlabel('time');
xlim([L-s(1), L+s(1)]);
title('Prediction');
disp('Done')
