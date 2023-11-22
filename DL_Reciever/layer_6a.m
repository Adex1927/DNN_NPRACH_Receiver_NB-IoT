% Function to generate a Layer 6a of UAD NN

function cva = layer_6a(x, L6a_0_w, L6a_0_b)
    
    x_shape = size(x);
    cva = zeros(x_shape(1), 2);

    for i = 1:x_shape(1)
        y = x(i, :).';
        y = linear(y, L6a_0_w, L6a_0_b);
        y = logsoftmax(y);
        cva(i, :) = y;
    end
end