% Function to apply a ReLU activation

function y = relu(x)
    
    x_shape = size(x);
    y = zeros(x_shape);
    
    for ch = 1:x_shape(1)
        for sample = 1:x_shape(2)
            y(ch, sample) = max([0, x(ch, sample)]);
        end
    end
end