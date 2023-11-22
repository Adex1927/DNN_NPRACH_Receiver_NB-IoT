// This file loads data, weights and baises for the NPRACH DL Receiver
#include "dl_nprach_head.h"

void read_file(char* name, int size, DATA *data_in)
{
    FILE *fptr;
    // open file using file pointer
    fptr = fopen(name, "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

	int MAX_SIZE = 100;
	char str[MAX_SIZE];

	for(int i = 0; i < size; i++)
	{
		fgets(str, MAX_SIZE, fptr);
		//printf("%s ", str);
		sscanf(str, "%hd", &(data_in[i]));
	}

    fclose(fptr);
}

void load_mat3d(int ch, int row, int col, DATA (*mat)[ch][row][col], DATA *data_in)
{
	int c = 0;
	for(int i = 0; i < col; i++)
	{
		for(int j = 0; j < row; j++)
		{
			for(int k = 0; k < ch; k++)
			{
				(*mat)[k][j][i] = data_in[c];
				c++;
			}
		}
	}
}

void load_rx_mat3d(int ch, int row, int col, DATA ***rx_mat, DATA *data_in)
{
	int c = 0;
	for(int i = 0; i < col; i++)
	{
		for(int j = 0; j < row; j++)
		{
			for(int k = 0; k < ch; k++)
			{
				rx_mat[k][j][i] = data_in[c];
				c++;
			}
		}
	}
}

void load_data_all(weights_t *nn_w, LUT_t *sig_lut, LUT_t *lgsm_lut)
{
	DATA data_in[500000];

	// // RX DATA MATRIX
	// read_file("RxData/rxDataMat_Err_UAD.txt", NUM_ITEM*2*SMPL_PER_PRMB, data_in);
	// load_rx_mat3d(NUM_ITEM, 2, SMPL_PER_PRMB, rx_data->rxDataMat, data_in);

	// LAYER 1
	read_file("Weights/L1_0_w.txt", 32*2*5, data_in);
	load_mat3d(32, 2, 5, &(nn_w->L1_0_w), data_in);
	read_file("Weights/L1_0_b.txt", 32, nn_w->L1_0_b);
	read_file("Weights/L1_1_w.txt", 32, nn_w->L1_1_w);
	read_file("Weights/L1_1_b.txt", 32, nn_w->L1_1_b);
	read_file("Weights/L1_1_mean.txt", 32, nn_w->L1_1_mean);
	read_file("Weights/L1_1_var.txt", 32, nn_w->L1_1_var);

	// LAYER 2
	read_file("Weights/L2_0_w.txt", 48*32*2, data_in);
	load_mat3d(48, 32, 2, &(nn_w->L2_0_w), data_in);
	read_file("Weights/L2_0_b.txt", 48, nn_w->L2_0_b);
	read_file("Weights/L2_1_w.txt", 48, nn_w->L2_1_w);
	read_file("Weights/L2_1_b.txt", 48, nn_w->L2_1_b);
	read_file("Weights/L2_1_mean.txt", 48, nn_w->L2_1_mean);
	read_file("Weights/L2_1_var.txt", 48, nn_w->L2_1_var);

	// LAYER 3
	read_file("Weights/L3_0_w.txt", 48*48*2, data_in);
	load_mat3d(48, 48, 2, &(nn_w->L3_0_w), data_in);
	read_file("Weights/L3_0_b.txt", 48, nn_w->L3_0_b);
	read_file("Weights/L3_1_w.txt", 48, nn_w->L3_1_w);
	read_file("Weights/L3_1_b.txt", 48, nn_w->L3_1_b);
	read_file("Weights/L3_1_mean.txt", 48, nn_w->L3_1_mean);
	read_file("Weights/L3_1_var.txt", 48, nn_w->L3_1_var);

	// LAYER 4
	read_file("Weights/L4_0_w.txt", 1*384*192, data_in);
	load_mat3d(1, 384, 192, &(nn_w->L4_0_w), data_in);
	read_file("Weights/L4_0_b.txt", 192, nn_w->L4_0_b);
	read_file("Weights/L4_1_w.txt", 192, nn_w->L4_1_w);
	read_file("Weights/L4_1_b.txt", 192, nn_w->L4_1_b);
	read_file("Weights/L4_1_mean.txt", 192, nn_w->L4_1_mean);
	read_file("Weights/L4_1_var.txt", 192, nn_w->L4_1_var);

	// LAYER 5
	read_file("Weights/L5_0_w.txt", 1*192*128, data_in);
	load_mat3d(1, 192, 128, &(nn_w->L5_0_w), data_in);
	read_file("Weights/L5_0_b.txt", 128, nn_w->L5_0_b);
	read_file("Weights/L5_1_w.txt", 128, nn_w->L5_1_w);
	read_file("Weights/L5_1_b.txt", 128, nn_w->L5_1_b);
	read_file("Weights/L5_1_mean.txt", 128, nn_w->L5_1_mean);
	read_file("Weights/L5_1_var.txt", 128, nn_w->L5_1_var);

	// Layer 6
	read_file("Weights/L6_0_w.txt", 1*128*1, data_in);
	load_mat3d(1, 128, 1, &(nn_w->L6_0_w), data_in);
	read_file("Weights/L6_0_b.txt", 1, nn_w->L6_0_b);

	// Layer 6a
	read_file("Weights/L6a_0_w.txt", 1*128*2, data_in);
	load_mat3d(1, 128, 2, &(nn_w->L6a_0_w), data_in);
	read_file("Weights/L6a_0_b.txt", 2, nn_w->L6a_0_b);

	// Sigmoid LUT
	read_file("LUT/sigmoid_LUT_x.txt", LUT_LEN, sig_lut->x);
	read_file("LUT/sigmoid_LUT_y.txt", LUT_LEN, sig_lut->y);

	// Logsoftmax LUT
}

void load_rx_data_ant1(rxData_t *rx_data)
{
	DATA data_in[500000];

	// RX DATA MATRIX
	read_file("RxData/rxDataMat_Err_UAD.txt", NUM_ITEM*2*SMPL_PER_PRMB, data_in);
	load_rx_mat3d(NUM_ITEM, 2, SMPL_PER_PRMB, rx_data->rxDataMat, data_in);
}

void load_rx_data_ant2(rxData_ant2_t *rx_data)
{
	DATA data_in[NUM_INP_SMPL];

	// RX DATA MATRIX
	read_file("RxData/rxDataMat_Err_UAD_snr10_ant1.txt", NUM_ITEM*2*SMPL_PER_PRMB, data_in);
	load_rx_mat3d(NUM_ITEM, 2, SMPL_PER_PRMB, rx_data->rxDataMat_1, data_in);

	read_file("RxData/rxDataMat_Err_UAD_snr10_ant2.txt", NUM_ITEM*2*SMPL_PER_PRMB, data_in);
	load_rx_mat3d(NUM_ITEM, 2, SMPL_PER_PRMB, rx_data->rxDataMat_2, data_in);
}