#include "fann.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int main()
{
	int num_of_inputs = 2;
	int num_of_outputs = 1;
	int num_of_layers = 3;
	int size_of_hidden_layer = 3;
	float desired_error = 0.001f;
	int max_epochs = 500000;
	int epochs_between_reports = 10000;
	
	struct fann *ann = fann_create_standard(num_of_layers, num_of_inputs, size_of_hidden_layer, num_of_outputs);
	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

	fann_train_on_file(ann, "xor_data.txt", max_epochs, epochs_between_reports, desired_error);
	fann_save(ann, "xor_float.net");


	fann_type *out;
	fann_type in[2];

	in[0] = 1;
	in[1] = 1;

	out = fann_run(ann, in);

	printf("XOR TEST:\n %.3f xor %.3f = %.3f\n", in[0], in[1], out[0]);	


	fann_destroy(ann);

	return 0;
}
