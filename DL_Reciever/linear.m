% Function to generate a Linear layer forward pass

function y = linear(x, weights, bias)
    
    y = (x.' * weights).' + bias;
end