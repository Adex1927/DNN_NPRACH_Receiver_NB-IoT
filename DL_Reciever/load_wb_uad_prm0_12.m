% Function to load the weights and biases for the NN for UAD_PRM0_CVA12

% Layer 1
L1_0_w = importdata("Weights\L1.0.weight");
L1_0_b = importdata("weights\L1.0.bias");
L1_0_b = L1_0_b.data;
L1_1_w = importdata("Weights\L1.1.weight");
L1_1_w = L1_1_w.data;
L1_1_b = importdata("weights\L1.1.bias");
L1_1_b = L1_1_b.data;

% Layer 2
L2_0_w = importdata("Weights\L2.0.weight");
L2_0_b = importdata("weights\L2.0.bias");
L2_0_b = L2_0_b.data;
L2_1_w = importdata("Weights\L2.1.weight");
L2_1_w = L2_1_w.data;
L2_1_b = importdata("weights\L2.1.bias");
L2_1_b = L2_1_b.data;

% Layer 3
L3_0_w = importdata("Weights\L3.0.weight");
L3_0_b = importdata("weights\L3.0.bias");
L3_0_b = L3_0_b.data;
L3_1_w = importdata("Weights\L3.1.weight");
L3_1_w = L3_1_w.data;
L3_1_b = importdata("weights\L3.1.bias");
L3_1_b = L3_1_b.data;

% Layer 4
L4_0_w = importdata("Weights\L4.0.weight");
L4_0_w = L4_0_w.data;
L4_0_b = importdata("weights\L4.0.bias");
L4_0_b = L4_0_b.data;
L4_1_w = importdata("Weights\L4.1.weight");
L4_1_w = L4_1_w.data;
L4_1_b = importdata("weights\L4.1.bias");
L4_1_b = L4_1_b.data;

% Layer 5
L5_0_w = importdata("Weights\L5.0.weight");
L5_0_w = L5_0_w.data;
L5_0_b = importdata("weights\L5.0.bias");
L5_0_b = L5_0_b.data;
L5_1_w = importdata("Weights\L5.1.weight");
L5_1_w = L5_1_w.data;
L5_1_b = importdata("weights\L5.1.bias");
L5_1_b = L5_1_b.data;

% Layer 6
L6_0_w = importdata("Weights\L6.0.weight");
L6_0_w = L6_0_w.data;
L6_0_b = importdata("weights\L6.0.bias");

% Layer 6a
L6a_0_w = importdata("Weights\L6a.0.weight");
L6a_0_w = L6a_0_w.data;
L6a_0_b = importdata("weights\L6a.0.bias");
L6a_0_b = L6a_0_b.data;

% Running means and variance for batchnorm1d layers
L1_1_mean = importdata("Weights\L1_1_running_mean");
L2_1_mean = importdata("Weights\L2_1_running_mean");
L3_1_mean = importdata("Weights\L3_1_running_mean");
L4_1_mean = importdata("Weights\L4_1_running_mean");
L5_1_mean = importdata("Weights\L5_1_running_mean");
L1_1_var = importdata("Weights\L1_1_running_var");
L2_1_var = importdata("Weights\L2_1_running_var");
L3_1_var = importdata("Weights\L3_1_running_var");
L4_1_var = importdata("Weights\L4_1_running_var");
L5_1_var = importdata("Weights\L5_1_running_var");
