%% Get original UAD and CVA

load("..\NPRACH Receiver\CVA_Err_PRM0_UAD_mix_test_snr");

%% get reference data
cva_test = CVA_Err;
uad_test = cva_test > 0;

snr_array = [2.1, 3.1, 4.1, 5.1, 6.1, 7.1, 8.1, 9.1, 10.1];

%% Error calculation for C fixed point

uad_err_cva1_C = zeros(size(snr_array));
% cva_err_cva1_C = zeros(size(snr_array));
uad_err_cva2_C = zeros(size(snr_array));
% cva_err_cva2_C = zeros(size(snr_array));
uad_err_no_user_C = zeros(size(snr_array));

uad_test_c = uad_test(1:10000);
cva_test_c = cva_test(1:10000);

uad_test_cva1 = uad_test_c(cva_test_c == 1);
uad_test_cva2 = uad_test_c(cva_test_c == 2);
uad_test_no_user = uad_test_c(cva_test_c == 0);

for i = 1:numel(snr_array)
    
    uad_cva1 = UAD_snr_C(cva_test_c == 1, i);
    uad_cva2 = UAD_snr_C(cva_test_c == 2, i);
    uad_no_user = UAD_snr_C(cva_test_c == 0, i);
    
    uad_err_cva1_C(i) = numel(find(uad_cva1 ~= uad_test_cva1));
    uad_err_cva2_C(i) = numel(find(uad_cva2 ~= uad_test_cva2));
    uad_err_no_user_C(i) = numel(find(uad_no_user ~= uad_test_no_user));
end

uad_err_cva1_C = uad_err_cva1_C / numel(uad_test_cva1);
uad_err_cva2_C = uad_err_cva2_C / numel(uad_test_cva2);
uad_err_no_user_C = uad_err_no_user_C / numel(uad_test_no_user);

%% Error calculation for MATLAB floating point

uad_err_cva1_M = zeros(size(snr_array));
uad_err_cva2_M = zeros(size(snr_array));
uad_err_no_user_M = zeros(size(snr_array));

uad_test_cva1 = uad_test(cva_test == 1);
uad_test_cva2 = uad_test(cva_test== 2);
uad_test_no_user = uad_test(cva_test == 0);

for i = 1:numel(snr_array)
    
    uad_cva1 = UAD_snr_M(cva_test == 1, i);
    uad_cva2 = UAD_snr_M(cva_test == 2, i);
    uad_no_user = UAD_snr_M(cva_test == 0, i);
    
    uad_err_cva1_M(i) = numel(find(uad_cva1 ~= uad_test_cva1));
    uad_err_cva2_M(i) = numel(find(uad_cva2 ~= uad_test_cva2));
    uad_err_no_user_M(i) = numel(find(uad_no_user ~= uad_test_no_user));
end

uad_err_cva1_M = uad_err_cva1_M / numel(uad_test_cva1);
uad_err_cva2_M = uad_err_cva2_M / numel(uad_test_cva2);
uad_err_no_user_M = uad_err_no_user_M / numel(uad_test_no_user);

%% Error calculation for C fixed point with Lekha Rx

uad_err_cva1_C_lekha = zeros(size(snr_array));
uad_err_cva2_C_lekha = zeros(size(snr_array));
uad_err_no_user_C_lekha = zeros(size(snr_array));

uad_test_cva1 = uad_test(cva_test == 1);
uad_test_cva2 = uad_test(cva_test== 2);
uad_test_no_user = uad_test(cva_test == 0);

for i = 1:numel(snr_array)
    
    uad_cva1 = UAD_snr_C_lekha(cva_test == 1, i);
    uad_cva2 = UAD_snr_C_lekha(cva_test == 2, i);
    uad_no_user = UAD_snr_C_lekha(cva_test == 0, i);
    
    uad_err_cva1_C_lekha(i) = numel(find(uad_cva1 ~= uad_test_cva1));
    uad_err_cva2_C_lekha(i) = numel(find(uad_cva2 ~= uad_test_cva2));
    uad_err_no_user_C_lekha(i) = numel(find(uad_no_user ~= uad_test_no_user));
end

uad_err_cva1_C_lekha = uad_err_cva1_C_lekha / numel(uad_test_cva1);
uad_err_cva2_C_lekha = uad_err_cva2_C_lekha / numel(uad_test_cva2);
uad_err_no_user_C_lekha = uad_err_no_user_C_lekha / numel(uad_test_no_user);

%% Error calculation for threshold sweep with Lekha Rx

thres_array = [0.65, 0.45, 0.25, 0.05, 0.03, 0.01, 0.008, 0.006, 0.004];

uad_thresh_cva1_C = zeros(size(thres_array));
uad_thresh_cva2_C = zeros(size(thres_array));
uad_thresh_no_user_C = zeros(size(thres_array));

uad_test_cva1 = uad_test(cva_test == 1);
uad_test_cva2 = uad_test(cva_test== 2);
uad_test_no_user = uad_test(cva_test == 0);

for i = 1:numel(snr_array)
    
    uad_cva1 = UAD_thresh_C(cva_test == 1, i);
    uad_cva2 = UAD_thresh_C(cva_test == 2, i);
    uad_no_user = UAD_thresh_C(cva_test == 0, i);
    
    uad_thresh_cva1_C(i) = numel(find(uad_cva1 ~= uad_test_cva1));
    uad_thresh_cva2_C(i) = numel(find(uad_cva2 ~= uad_test_cva2));
    uad_thresh_no_user_C(i) = numel(find(uad_no_user ~= uad_test_no_user));
end

uad_thresh_cva1_C = uad_thresh_cva1_C / numel(uad_test_cva1);
uad_thresh_cva2_C = uad_thresh_cva2_C / numel(uad_test_cva2);
uad_thresh_no_user_C = uad_thresh_no_user_C / numel(uad_test_no_user);

