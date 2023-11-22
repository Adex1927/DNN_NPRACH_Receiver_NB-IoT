%% Plot the error rates vs SNR
% Load all uad and cva data for fixed point C code, MATLAB and Pytorch
snr_array = [2.1, 3.1, 4.1, 5.1, 6.1, 7.1, 8.1, 9.1, 10.1];

% Python data is for SNR range 0.1 to 20.1, so using 2.1 to 10.1 for plots

figure(1);
%semilogy(snr_array, (uad_err/numel(CVA_Err)));
plot(snr_array(4:9), 1-uad_cva1_err_py(3+3:11), '-r', 'LineWidth', 2.0);
hold on
%plot(snr_array(4:9), 1-uad_err_cva1_M(4:9), '-b', 'LineWidth', 2.0);
%plot(snr_array, 1-uad_err_cva1_C, '-c', 'LineWidth', 2.0);
plot(snr_array(4:9), 1-uad_err_cva1_C_lekha(4:9), '-b', 'LineWidth', 2.0);
hold off;
title('Probability of Detection vs. SNR - CVA1');
%legend('Pytorch Model (Python)', 'Floating Point (MATLAB)', 'Fixed Point (C, Lekha Rx)');
legend('Pytorch Model (Python)', 'Fixed Point (C, Lekha Rx)');
xlabel('SNR (dB)');
ylabel('Probability of Detection');
grid on;

figure(2);
plot(snr_array(4:9), 1-uad_cva2_err_py(3+3:11), '-r', 'LineWidth', 2.0);
hold on
%plot(snr_array(4:9), 1-uad_err_cva2_M(4:9), '-b', 'LineWidth', 2.0);
%plot(snr_array, 1-uad_err_cva2_C, '-c', 'LineWidth', 2.0);
plot(snr_array(4:9), 1-uad_err_cva2_C_lekha(4:9), '-b', 'LineWidth', 2.0);
hold off;
title('Probability of Detection vs. SNR - CVA2');
%legend('Pytorch Model (Python)', 'Floating Point (MATLAB)', 'Fixed Point (C, Lekha Rx)');
legend('Pytorch Model (Python)', 'Fixed Point (C, Lekha Rx)');
xlabel('SNR (dB)');
ylabel('Probability of Detection');
grid on;

% figure(3);
% plot(snr_array, uad_no_user_err_py(3:11), '-r', 'LineWidth', 2.0);
% hold on
% plot(snr_array, uad_err_no_user_M, '-b', 'LineWidth', 2.0);
% plot(snr_array, uad_err_no_user_C, '-c', 'LineWidth', 2.0);
% plot(snr_array, uad_err_no_user_C_lekha, '-g', 'LineWidth', 2.0);
% hold off;
% title('UAD Error vs. SNR - No UE');
% legend('Pytorch Model (Python)', 'Floating Point (MATLAB)', 'Fixed Point (C)', 'Fixed Point (C, Lekha Rx)');
% xlabel('SNR (dB)');
% ylabel('Error Rate in UAD');
% grid on;

%% CVA1 and CVA2 plot for Fixed C

figure(1);
plot(snr_array, 1-uad_err_cva1_C, '-r', 'LineWidth', 2.0);
hold on
plot(snr_array, 1-uad_err_cva2_C, '-b', 'LineWidth', 2.0);
hold off;
title('Probability of Detection vs. SNR - Fixed Point (C)');
legend('CVA1', 'CVA2');
xlabel('SNR (dB)');
ylabel('Probability of Detection');
grid on;

%% Plot for threshold sweep

thres_array = [0.65, 0.45, 0.25, 0.05, 0.03, 0.01, 0.008, 0.006, 0.004];

figure(1);
semilogx(thres_array, (uad_thresh_cva1_C), '-r', 'LineWidth', 2.0);
hold on
semilogx(thres_array, (uad_thresh_cva2_C), '-b', 'LineWidth', 2.0);
semilogx(thres_array, uad_thresh_no_user_C, '-g', 'LineWidth', 2.0);
hold off;
title('Threshold Search - Fixed Point (C, Lekha Rx)');
legend('UAD Error for CVA1', 'UAD Error for CVA2', 'False Alarm (No UE)');
xlabel('Threshold');
ylabel('Probability');
grid on;

%% Plot higher SNR range for Pytorch

snr_array = 0.1 : 1 : 20.1;

figure(1);
semilogy(snr_array, uad_cva1_err_py, 'LineWidth', 2.0);
hold on
semilogy(snr_array, uad_cva2_err_py, 'LineWidth', 2.0);
semilogy(snr_array, uad_no_user_err_py, 'LineWidth', 2.0);
hold off;
title('UAD Error vs. SNR - Pytorch Model');
legend('CVA1', 'CVA2', 'No UE');
xlabel('SNR (dB)');
ylabel('Error Rate in UAD');
grid on;