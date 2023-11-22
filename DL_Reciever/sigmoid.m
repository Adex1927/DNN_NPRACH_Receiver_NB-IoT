% Function to apply a sigmoid activation

function y = sigmoid(x)
    
    x_shape = size(x);
    y = zeros(x_shape);
    
    for i = 1:x_shape(2)
        temp = exp(-1 * x(1, i));
        y(1, i) = 1 / (1 + temp);
    end
end