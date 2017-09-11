#include "fann.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"

char *data_file = "sin_data.txt";
char *save_file = "sin_float.net";
char *function_name = "f(x) = sin(x)";

struct settings 
{
	int in;
	int out;
	int layers;
	int epochs;
	int reports;
	float error;
	int *sizes;
};

float f(float x)
{
	return sin(x);
}

struct settings get_settings(int argc, char **argv)
{
	int i;
	struct settings result;
	result.in = result.out = 0;
	result.layers = result.epochs = 0;
	result.reports = 0;
	result.sizes = NULL;
	result.error = 0.0f;
	char buffer[__SIZEOF_FLOAT__];
	if(argc == 1) return result;
	for(i = 1; i < argc; i++)
	{
		if(!strcmp(argv[i], "-e") && i != argc - 1)
			result.error = atof(argv[i + 1]);
	}
	return result;
}

int main(int argc, char **argv)
{
	
	struct settings options;

	struct fann *ann;
	struct fann_train_data *train_data;
	
	ann = train_data = NULL;

	int num_of_inputs = 2;
	int num_of_outputs = 1;
	int num_of_layers = 3;
	int size_of_hidden_layer_one = 2;
	int size_of_hidden_layer_two = 4;
	int max_epochs = 500000;
	int epochs_between_reports = 1000;
	float desired_error = 0.01f;
	float new_input_min;
   	float new_input_max;
   	float new_output_min;
   	float new_output_max;

	options = get_settings(argc, argv);
	

//	ann = fann_create_standard(num_of_layers, num_of_inputs, size_of_hidden_layer_one, size_of_hidden_layer_two, num_of_outputs);
//	fann_train_on_file(ann, data_file, max_epochs, epochs_between_reports, desired_error);
//	fann_destroy(ann);

	
	unsigned const int layers_array[] = {2, 10, 20, 1};
	const int layers_num = 4;
	max_epochs = 500000; epochs_between_reports = 1000; desired_error = 0.001f;
	if(options.error != 0.0) desired_error = options.error;
	ann = fann_create_standard_array(layers_num, layers_array);
	
	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);


	
	new_input_min = -1.0;
	new_input_max = 1.0;
   	new_output_min = -1.0;
   	new_output_max = 1.0;
	train_data = fann_read_train_from_file(data_file);
//	fann_scale_train_data(train_data, new_input_min, new_input_max);
//	fann_set_scaling_params(ann, train_data, new_input_min, new_input_max, new_output_min, new_output_max);
	fann_train_on_data(ann, train_data, max_epochs, epochs_between_reports, desired_error);
	
   		
	fann_save(ann, save_file);
	
	

	fann_type in1[2], in2[2];
	in1[0] = 0.0;
	in2[0] = 0.0;
	in1[1] = 1.0;
	in2[1] = 1.0;
	
	int i;
	float step = 0.05;
	int num_of_tests = 100;


	printf("\n\n%s TEST:\n\n", function_name);
	
	num_of_tests = 49;
	in1[0] = 0.0;
	in2[0] = in1[0] + step;
	
	for(i = 0; i < num_of_tests / 2; i++)
	{
		fann_type *out[2];
		fann_type in[2][2];
		float error[2];
		in[0][0] = in1[0];
		in[0][1] = in1[1];
		in[1][0] = in2[0];
		in[1][1] = in2[1];

//		fann_scale_input(ann, in[0]);
//		fann_scale_input(ann, in[1]);
//		printf("SCALED IN: %f, %f\t\tDESCALED IN: %f, %f\n", in[0][0], in[1][0], in1[0], in2[0]);
		
		out[0] = fann_run(ann, in[0]);
		out[1] = fann_run(ann, in[1]);

//		printf("SCALED OUT: %f, %f\t\t", *out[0], *out[1]);
//		fann_descale_output(ann, out[0]);
//		fann_descale_output(ann, out[1]);
//		fann_descale_input(ann, in[0]);
//		fann_descale_input(ann, in[1]);
//		printf("DESCALED OUT: %f, %f\n", *out[0], *out[1]);
	
	

		
		error[0] = fabs(f((float)in[0][0]) - (float)*out[0]);
		error[1] = fabs(f((float)in[1][0]) - (float)*out[1]);
		in1[0] = in2[0] + step;
		in2[0] = in1[0] + step;
		printf("[%f]|%f, %f|%f\t\t[%f]|%f, %f| %f\n", (float)in[0][0], f((float)in[0][0]), (float)*out[0], error[0], (float)in[1][0], f((float)in[1][0]), (float)*out[1], error[1]);
		continue;
		

		printf("\t\t\t\tx = %f\t\t|\tx = %f\n", (float)in[0][0], (float)in[1][0]);
		printf("\t\t\tf(%f) = %f\t\t|", (float)in[0][0], f((float)in[0][0]));
		printf("\tf(%f) = %f\n", (float)in[1][0], f((float)in[1][0]));
		printf("\tsin(%f) = %f\t\t|", (float)in[0][0], f((float)in[0][0]));
		printf("\tsin(%f) = %f\n", (float)in[1][0], f((float)in[1][0]));
		printf("\t\tsin(%f) = %f\t\t|", (float)in[0][0], f((float)in[0][0]));
		printf("\tsin(%f) = %f\n", (float)in[1][0], f((float)in[1][0]));
		printf("ANN G(%f) = %f\td: %f\t\t|", (float)in[0][0], (float)*out[0], error[0]);
		printf("\tANN G(%f) = %f\td: %f\n", (float)in[1][0], (float)*out[1], error[1]);
		
		
		putchar('\n');

		
	
	}
	
	


	fann_destroy_train(train_data);
	fann_destroy(ann);

	return 0;
}
