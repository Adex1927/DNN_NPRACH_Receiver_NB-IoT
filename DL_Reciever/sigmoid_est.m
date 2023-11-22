% Function to apply a sigmoid activation

function y = sigmoid_est(x)
    
    x_shape = size(x);
    y = zeros(x_shape);
    
    for i = 1:x_shape(2)
        y(1, i) = 0.524979 + (x(1,i) - 0.1) * 0.249376;
        y(1, i) = y(1, i) - (0.00622921 * (x(1,i) - 0.1) * (x(1,i) - 0.1))
end