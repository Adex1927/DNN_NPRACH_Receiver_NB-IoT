% Neural Network for UAD, PRM0, CVA = 1,2

x_shape = size(x);
uad = zeros(x_shape(1), 1);
cva = zeros(x_shape(1), 2);
y_out = zeros(x_shape(1), 128, 1);

for x_iter = 1 : x_shape(1)
    x_i = reshape(x(x_iter, :, :), [2, 160]);

    % Layer 1
    y = conv1d(x_i, [32, 32], L1_0_w, L1_0_b, 5);
    y = batchnorm1d(y, L1_1_w, L1_1_b, L1_1_mean, L1_1_var);
    y = relu(y);

    % Layer 2
    y = conv1d(y, [48, 16], L2_0_w, L2_0_b, 2);
    y = batchnorm1d(y, L2_1_w, L2_1_b, L2_1_mean, L2_1_var);
    y = relu(y);
    
    % Layer 3
    y = conv1d(y, [48, 8], L3_0_w, L3_0_b, 2);
    y = batchnorm1d(y, L3_1_w, L3_1_b, L3_1_mean, L3_1_var);
    y = relu(y);
    
    % Flattening
    y = reshape(y.', [1, 384]);
    y = y.';
    
    % Layer 4
    y = linear(y, L4_0_w, L4_0_b);
    y = batchnorm1d(y, L4_1_w, L4_1_b, L4_1_mean, L4_1_var);
    y = relu(y);
    
    % Layer 5
    y = linear(y, L5_0_w, L5_0_b);
    y = batchnorm1d(y, L5_1_w, L5_1_b, L5_1_mean, L5_1_var);
    y = relu(y);
    
    y_out(x_iter, :, :) = y;
    
    % Layer 6
%     y_temp = linear(y, L6_0_w, L6_0_b);
%     y_temp = sigmoid(y_temp);
%     uad(x_iter, 1) = y_temp;
%     
%     % Layer 6a
%     y_temp = linear(y, L6a_0_w, L6a_0_b);
%     y_temp = logsoftmax(y_temp);
%     cva(x_iter, :) = y_temp;
    
end