% Function to apply a logsoftmax activation

function y = logsoftmax(x)
    
    y = exp(x);
    y = y / sum(y);
    y = log10(y);
end