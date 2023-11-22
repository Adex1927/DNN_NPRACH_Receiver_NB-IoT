%% Load the weights and biases

load_wb_uad_prm0_12

%% Load Rx data

load("..\NPRACH Receiver\rxDataMat_Err_PRM0_UAD_mix");

%% Normalize
rx_shape = size(rxDataMat_Err_UAD);
rxDataMat_Err_UAD_norm = zeros(rx_shape);

for i = 1:300000
    mean_i = mean(rxDataMat_Err_UAD(i, :, :), 'all');
    std_i = std(rxDataMat_Err_UAD(i, :, :), 0, 'all');
    
    rxDataMat_Err_UAD_norm(i, :, :) = (rxDataMat_Err_UAD(i, :, :) - mean_i) / std_i;
end
%% Extract data
x = rxDataMat_Err_UAD_norm(1:100, :, :);

%% Using NN

uad_prm0_cva12

%% Inferring UAD and CVA

% Inferring UAD
uad_final = uad >= 0.65;

% Inferring CVA
[arg_cva, argmax] = max(cva, [], 2);
cva_final = argmax .* uad_final;

