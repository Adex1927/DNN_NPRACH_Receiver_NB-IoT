% Scale data for fixed point

scale = 256; % 2^8

%% RxDATA

rxDataMat_Err_UAD_save = rxDataMat_Err_UAD_norm(1:100,:,:);

%% Scale up

rxDataMat_Err_UAD_save = round(rxDataMat_Err_UAD_save * scale);

%% Save

temp = reshape(rxDataMat_Err_UAD_save, [numel(rxDataMat_Err_UAD_save), 1]);
writematrix(temp, 'Data_txt_fixed\rxDataMat_Err_UAD.txt', 'Delimiter', " ");

%% Save test data

snr_array = [2.1, 3.1, 4.1, 5.1, 6.1, 7.1, 8.1, 9.1, 10.1];
    
snr_db = snr_array(2);
snr = 10 ^ (snr_db/10);
noise = randn(size(rxDataMat_Err_UAD)) * (1/sqrt(2*snr));

% Add the noise to the Rx matrix
rxDataMat_Err_UAD_n = rxDataMat_Err_UAD + noise; % noisy rx signal

% Normalize
rx_shape = size(rxDataMat_Err_UAD_n);
rxDataMat_Err_UAD_norm = zeros(rx_shape);
for i = 1:rx_shape(1)
    for j = 1:rx_shape(2)
        mean_i = mean(rxDataMat_Err_UAD_n(i, j, :, :), 'all');
        std_i = std(rxDataMat_Err_UAD_n(i, j, :, :), 0, 'all');

        rxDataMat_Err_UAD_norm(i, j, :, :) = (rxDataMat_Err_UAD_n(i, j, :, :) - mean_i) / std_i;
    end
end

%% Save for different SNRs
rxDataMat_Err_UAD_save_1 = rxDataMat_Err_UAD_norm(:, 1, :, :); % antenna 1
rxDataMat_Err_UAD_save_1 = round(rxDataMat_Err_UAD_save_1 * scale);
rxDataMat_Err_UAD_save_2 = rxDataMat_Err_UAD_norm(:, 2, :, :); % antenna 2
rxDataMat_Err_UAD_save_2 = round(rxDataMat_Err_UAD_save_2 * scale);

temp = reshape(rxDataMat_Err_UAD_save_1, [numel(rxDataMat_Err_UAD_save_1), 1]);
writematrix(temp, 'Data_txt_fixed\rxDataMat_Err_UAD_snr10_ant1.txt', 'Delimiter', " ");
temp = reshape(rxDataMat_Err_UAD_save_2, [numel(rxDataMat_Err_UAD_save_2), 1]);
writematrix(temp, 'Data_txt_fixed\rxDataMat_Err_UAD_snr10_ant2.txt', 'Delimiter', " ");

%% Save for different SNRs
rxDataMat_Err_UAD_save_1 = rxDataMat_Err_UAD_norm(1:10000, 1, :, :); % antenna 1
rxDataMat_Err_UAD_save_1 = round(rxDataMat_Err_UAD_save_1 * scale);
rxDataMat_Err_UAD_save_2 = rxDataMat_Err_UAD_norm(1:10000, 2, :, :); % antenna 2
rxDataMat_Err_UAD_save_2 = round(rxDataMat_Err_UAD_save_2 * scale);

temp = reshape(rxDataMat_Err_UAD_save_1, [numel(rxDataMat_Err_UAD_save_1), 1]);
writematrix(temp, 'Data_noUE\rxDataMat_Err_UAD_snr10_ant1.txt', 'Delimiter', " ");
temp = reshape(rxDataMat_Err_UAD_save_2, [numel(rxDataMat_Err_UAD_save_2), 1]);
writematrix(temp, 'Data_noUE\rxDataMat_Err_UAD_snr10_ant2.txt', 'Delimiter', " ");

%% Scale weights and biases

L1_0_w = round(L1_0_w * scale);
L1_0_b = round(L1_0_b * scale);
L1_1_w = round(L1_1_w * scale);
L1_1_b = round(L1_1_b * scale);
L1_1_mean = round(L1_1_mean * scale);
L1_1_var = round(L1_1_var * scale);

L2_0_w = round(L2_0_w * scale);
L2_0_b = round(L2_0_b * scale);
L2_1_w = round(L2_1_w * scale);
L2_1_b = round(L2_1_b * scale);
L2_1_mean = round(L2_1_mean * scale);
L2_1_var = round(L2_1_var * scale);

L3_0_w = round(L3_0_w * scale);
L3_0_b = round(L3_0_b * scale);
L3_1_w = round(L3_1_w * scale);
L3_1_b = round(L3_1_b * scale);
L3_1_mean = round(L3_1_mean * scale);
L3_1_var = round(L3_1_var * scale);

L4_0_w = round(L4_0_w * scale);
L4_0_b = round(L4_0_b * scale);
L4_1_w = round(L4_1_w * scale);
L4_1_b = round(L4_1_b * scale);
L4_1_mean = round(L4_1_mean * scale);
L4_1_var = round(L4_1_var * scale);

L5_0_w = round(L5_0_w * scale);
L5_0_b = round(L5_0_b * scale);
L5_1_w = round(L5_1_w * scale);
L5_1_b = round(L5_1_b * scale);
L5_1_mean = round(L5_1_mean * scale);
L5_1_var = round(L5_1_var * scale);

L6_0_w = round(L6_0_w * scale);
L6_0_b = round(L6_0_b * scale);

L6a_0_w = round(L6a_0_w * scale);
L6a_0_b = round(L6a_0_b * scale);

%% Save

% Layer 1
temp = reshape(L1_0_w, [320, 1]);
writematrix(temp, 'Data_txt_fixed\L1_0_w.txt', 'Delimiter', " ");
writematrix(L1_0_b, 'Data_txt_fixed\L1_0_b.txt', 'Delimiter', " ");
writematrix(L1_1_w, 'Data_txt_fixed\L1_1_w.txt', 'Delimiter', " ");
writematrix(L1_1_b, 'Data_txt_fixed\L1_1_b.txt', 'Delimiter', " ");
writematrix(L1_1_mean.', 'Data_txt_fixed\L1_1_mean.txt', 'Delimiter', " ");
writematrix(L1_1_var.', 'Data_txt_fixed\L1_1_var.txt', 'Delimiter', " ");

% Layer 2
temp = reshape(L2_0_w, [48*32*2, 1]);
writematrix(temp, 'Data_txt_fixed\L2_0_w.txt', 'Delimiter', " ");
writematrix(L2_0_b, 'Data_txt_fixed\L2_0_b.txt', 'Delimiter', " ");
writematrix(L2_1_w, 'Data_txt_fixed\L2_1_w.txt', 'Delimiter', " ");
writematrix(L2_1_b, 'Data_txt_fixed\L2_1_b.txt', 'Delimiter', " ");
writematrix(L2_1_mean.', 'Data_txt_fixed\L2_1_mean.txt', 'Delimiter', " ");
writematrix(L2_1_var.', 'Data_txt_fixed\L2_1_var.txt', 'Delimiter', " ");

% Layer 3
temp = reshape(L3_0_w, [48*48*2, 1]);
writematrix(temp, 'Data_txt_fixed\L3_0_w.txt', 'Delimiter', " ");
writematrix(L3_0_b, 'Data_txt_fixed\L3_0_b.txt', 'Delimiter', " ");
writematrix(L3_1_w, 'Data_txt_fixed\L3_1_w.txt', 'Delimiter', " ");
writematrix(L3_1_b, 'Data_txt_fixed\L3_1_b.txt', 'Delimiter', " ");
writematrix(L3_1_mean.', 'Data_txt_fixed\L3_1_mean.txt', 'Delimiter', " ");
writematrix(L3_1_var.', 'Data_txt_fixed\L3_1_var.txt', 'Delimiter', " ");

% Layer 4
temp = reshape(L4_0_w, [384*192, 1]);
writematrix(temp, 'Data_txt_fixed\L4_0_w.txt', 'Delimiter', " ");
writematrix(L4_0_b, 'Data_txt_fixed\L4_0_b.txt', 'Delimiter', " ");
writematrix(L4_1_w, 'Data_txt_fixed\L4_1_w.txt', 'Delimiter', " ");
writematrix(L4_1_b, 'Data_txt_fixed\L4_1_b.txt', 'Delimiter', " ");
writematrix(L4_1_mean.', 'Data_txt_fixed\L4_1_mean.txt', 'Delimiter', " ");
writematrix(L4_1_var.', 'Data_txt_fixed\L4_1_var.txt', 'Delimiter', " ");

% Layer 5
temp = reshape(L5_0_w, [192*128, 1]);
writematrix(temp, 'Data_txt_fixed\L5_0_w.txt', 'Delimiter', " ");
writematrix(L5_0_b, 'Data_txt_fixed\L5_0_b.txt', 'Delimiter', " ");
writematrix(L5_1_w, 'Data_txt_fixed\L5_1_w.txt', 'Delimiter', " ");
writematrix(L5_1_b, 'Data_txt_fixed\L5_1_b.txt', 'Delimiter', " ");
writematrix(L5_1_mean.', 'Data_txt_fixed\L5_1_mean.txt', 'Delimiter', " ");
writematrix(L5_1_var.', 'Data_txt_fixed\L5_1_var.txt', 'Delimiter', " ");

% Layer 6
writematrix(L6_0_w, 'Data_txt_fixed\L6_0_w.txt', 'Delimiter', " ");
writematrix(L6_0_b, 'Data_txt_fixed\L6_0_b.txt', 'Delimiter', " ");

% Layer 6a
temp = reshape(L6a_0_w, [128*2, 1]);
writematrix(temp, 'Data_txt_fixed\L6a_0_w.txt', 'Delimiter', " ");
writematrix(L6a_0_b, 'Data_txt_fixed\L6a_0_b.txt', 'Delimiter', " ");

