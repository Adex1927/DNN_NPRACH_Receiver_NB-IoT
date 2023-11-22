% Function to generate a Layer 6 of UAD NN

function uad = layer_6(x, L6_0_w, L6_0_b)
    
    x_shape = size(x);
    uad = zeros(x_shape(1), 1);

    for i = 1:x_shape(1)
        y = x(i, :).';
        y = linear(y, L6_0_w, L6_0_b);
        y = sigmoid(y);
        uad(i, 1) = y;
    end
end