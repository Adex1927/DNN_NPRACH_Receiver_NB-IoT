% To write all the data into TXT files for C code

format LONG

%% Rx Data Matrix
temp = reshape(rxDataMat_Err_UAD_save, [numel(rxDataMat_Err_UAD_save), 1]);
writematrix(temp, 'Data_txt\rxDataMat_Err_UAD.txt', 'Delimiter', " ");

%% Layer 1
temp = reshape(L1_0_w, [320, 1]);
writematrix(temp, 'Data_txt\L1_0_w.txt', 'Delimiter', " ");
writematrix(L1_0_b, 'Data_txt\L1_0_b.txt', 'Delimiter', " ");
writematrix(L1_1_w, 'Data_txt\L1_1_w.txt', 'Delimiter', " ");
writematrix(L1_1_b, 'Data_txt\L1_1_b.txt', 'Delimiter', " ");
writematrix(L1_1_mean.', 'Data_txt\L1_1_mean.txt', 'Delimiter', " ");
writematrix(L1_1_var.', 'Data_txt\L1_1_var.txt', 'Delimiter', " ");

%% Layer 2
temp = reshape(L2_0_w, [48*32*2, 1]);
writematrix(temp, 'Data_txt\L2_0_w.txt', 'Delimiter', " ");
writematrix(L2_0_b, 'Data_txt\L2_0_b.txt', 'Delimiter', " ");
writematrix(L2_1_w, 'Data_txt\L2_1_w.txt', 'Delimiter', " ");
writematrix(L2_1_b, 'Data_txt\L2_1_b.txt', 'Delimiter', " ");
writematrix(L2_1_mean.', 'Data_txt\L2_1_mean.txt', 'Delimiter', " ");
writematrix(L2_1_var.', 'Data_txt\L2_1_var.txt', 'Delimiter', " ");

%% Layer 3
temp = reshape(L3_0_w, [48*48*2, 1]);
writematrix(temp, 'Data_txt\L3_0_w.txt', 'Delimiter', " ");
writematrix(L3_0_b, 'Data_txt\L3_0_b.txt', 'Delimiter', " ");
writematrix(L3_1_w, 'Data_txt\L3_1_w.txt', 'Delimiter', " ");
writematrix(L3_1_b, 'Data_txt\L3_1_b.txt', 'Delimiter', " ");
writematrix(L3_1_mean.', 'Data_txt\L3_1_mean.txt', 'Delimiter', " ");
writematrix(L3_1_var.', 'Data_txt\L3_1_var.txt', 'Delimiter', " ");

%% Layer 4
temp = reshape(L4_0_w, [384*192, 1]);
writematrix(temp, 'Data_txt\L4_0_w.txt', 'Delimiter', " ");
writematrix(L4_0_b, 'Data_txt\L4_0_b.txt', 'Delimiter', " ");
writematrix(L4_1_w, 'Data_txt\L4_1_w.txt', 'Delimiter', " ");
writematrix(L4_1_b, 'Data_txt\L4_1_b.txt', 'Delimiter', " ");
writematrix(L4_1_mean.', 'Data_txt\L4_1_mean.txt', 'Delimiter', " ");
writematrix(L4_1_var.', 'Data_txt\L4_1_var.txt', 'Delimiter', " ");

%% Layer 5
temp = reshape(L5_0_w, [192*128, 1]);
writematrix(temp, 'Data_txt\L5_0_w.txt', 'Delimiter', " ");
writematrix(L5_0_b, 'Data_txt\L5_0_b.txt', 'Delimiter', " ");
writematrix(L5_1_w, 'Data_txt\L5_1_w.txt', 'Delimiter', " ");
writematrix(L5_1_b, 'Data_txt\L5_1_b.txt', 'Delimiter', " ");
writematrix(L5_1_mean.', 'Data_txt\L5_1_mean.txt', 'Delimiter', " ");
writematrix(L5_1_var.', 'Data_txt\L5_1_var.txt', 'Delimiter', " ");

%% Layer 6
writematrix(L6_0_w, 'Data_txt\L6_0_w.txt', 'Delimiter', " ");
writematrix(L6_0_b, 'Data_txt\L6_0_b.txt', 'Delimiter', " ");

%% Layer 6a
temp = reshape(L6a_0_w, [128*2, 1]);
writematrix(temp, 'Data_txt\L6a_0_w.txt', 'Delimiter', " ");
writematrix(L6a_0_b, 'Data_txt\L6a_0_b.txt', 'Delimiter', " ");

%% Function

function file_write(filename, data)
    
    fid = fopen(filename, 'wt');
    if fid ~= -1
        for row = 1 : size(data, 1);
            fprintf(fid, '%.10f,\n', data(row,1));
        end
    end
        
    fclose(fid);
end