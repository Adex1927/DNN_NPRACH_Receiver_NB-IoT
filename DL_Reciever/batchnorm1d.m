% Function to apply BATCHNORM1D forward pass

function y = batchnorm1d(x, weights, bias, running_mean, running_var)

    x_shape = size(x);
    y = zeros(x_shape);
    
    for ch = 1:x_shape(1)
        
        ch_mean = running_mean(ch);
        ch_var = running_var(ch);
        epsilon = 0.00001;
        
        ch_std = sqrt(ch_var + epsilon);
        
        for sample = 1:x_shape(2)
            y(ch, sample) = ((x(ch, sample) - ch_mean) * weights(ch))/ch_std + bias(ch);
        end
    end
end

