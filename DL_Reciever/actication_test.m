% testing for sigmoid and logsoftmax

scale = 256; % scaling factor

x_in = -4 : 0.05 : +4;
y_sig = sigmoid(x_in);
% y_sig_est = sigmoid_est(x_in);

lookup_table = round(y_sig.' * scale);
x_scale = round(x_in.' * scale);

%% Plot
plot(x_in, y_sig);
hold on
plot(x_in, y_sig_est);
hold off

%% Plot error
plot(x_scale, lookup_table);

%% Save for sigmoid lookup table
lookup_table = round(y_sig.' * scale);
x_scale = round(x_in.' * scale);

writematrix(lookup_table, 'Data_txt_fixed\sigmoid_LUT_y.txt', 'Delimiter', " ");
writematrix(x_scale, 'Data_txt_fixed\sigmoid_LUT_x.txt', 'Delimiter', " ");
