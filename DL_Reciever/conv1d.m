% Function to generate a CONV1D layer forward pass

function y = conv1d(x, y_shape, weights, bias, stride)
    
    % Output matrix
    y = zeros(y_shape);
    
    % Extract the channel and kernel sizes
    w_shape = size(weights);
    x_shape = size(x);
    y_channels = w_shape(1);
    x_channels = w_shape(2);
    kernel_size = w_shape(3);
    x_length = x_shape(2);
    y_length = y_shape(2);
    
    % Computing the output using the weights and bias
    for ch = 1:y_channels
        w_ch = reshape(weights(ch, :, :), [w_shape(2), w_shape(3)]);
        
        for sample = 1:y_length
            temp = 0;
            for x_ch = 1:x_channels
                start_pt = (sample-1)*stride+1;
                temp = temp + sum(x(x_ch, start_pt:start_pt+kernel_size-1) .* w_ch(x_ch, :));
            end
            y(ch, sample) = temp + bias(ch);
        end
    end
end