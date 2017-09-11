%../set/set1: InputsDelay = 10
%../set/set2: InputsDelay = 15

InputsDelay = 10;
N_train = 8000;
N_test = 1000;

%{
P_inputs = readtable('../py/output_data_34-43_inputs');
P_outputs = readtable('../py/output_data_34-43_outputs');
W_inputs = readtable('../py/output_data_36-43_inputs');
W_outputs = readtable('../py/output_data_36-43_outputs');
%}

P_inputs = readtable('../sets/set1/output_data_34-43_inputs');
P_outputs = readtable('../sets/set1/output_data_34-43_outputs');
W_inputs = readtable('../sets/set1/output_data_36-43_inputs');
W_outputs = readtable('../sets/set1/output_data_36-43_outputs');

P_inputs = cell2mat(table2cell(P_inputs));
P_outputs = cell2mat(table2cell(P_outputs));
W_inputs = cell2mat(table2cell(W_inputs));
W_outputs = cell2mat(table2cell(W_outputs));

P_inputs_train = P_inputs(1:N_train,1:InputsDelay);
W_inputs_train = W_inputs(1:N_train,1:InputsDelay); 
P_outputs_train = P_outputs(1:N_train,:);
W_outputs_train = W_outputs(1:N_train,:);

P_inputs_test = P_inputs(N_train + 1:N_train + N_test,1:InputsDelay);
P_outputs_test = P_outputs(N_train + 1:N_train + N_test,:);
W_inputs_test = W_inputs(N_train + 1:N_train + N_test,1:InputsDelay);
W_outputs_test = W_outputs(N_train + 1:N_train + N_test,:);

P_inputs_train = P_inputs_train';
W_outputs_train = W_outputs_train';
P_outputs_train = P_outputs_train';
W_inputs_train = W_inputs_train';

P_inputs_test = P_inputs_test';
W_outputs_test = W_outputs_test';
P_outputs_test = P_outputs_test';
W_inputs_test = W_inputs_test';

