#include "fann.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"


float f1(float x)
{
	//	printf("\n\nf(x) = 1 - exp(-(x + 1)/2) TEST:\n\n");
	return 1.0 - exp(-(0.5*(x + 1.0)));
}

float f(float x)
{
	return exp(x);
}

int main()
{
	struct fann *ann;
	struct fann_train_data *train_data;
	
	ann = train_data = NULL;

	int num_of_inputs = 1;
	int num_of_outputs = 1;
	int num_of_layers = 4;
	int size_of_hidden_layer_one = 2;
	int size_of_hidden_layer_two = 4;
	int max_epochs = 500000;
	int epochs_between_reports = 1000;
	float desired_error = 0.01f;
	float new_input_min;
   	float new_input_max;
   	float new_output_min;
   	float new_output_max;

//	ann = fann_create_standard(num_of_layers, num_of_inputs, size_of_hidden_layer_one, size_of_hidden_layer_two, num_of_outputs);
//	fann_train_on_file(ann, "exp_data.txt", max_epochs, epochs_between_reports, desired_error);
//	fann_destroy(ann);

	
	unsigned const int layers_array[] = {1, 10, 20, 10, 1};
	const int layers_num = 5;
	max_epochs = 500000; epochs_between_reports = 1000; desired_error = 0.01f;
	ann = fann_create_standard_array(layers_num, layers_array);
	
	fann_set_activation_function_layer(ann, FANN_SIGMOID, 0);
	fann_set_activation_function_hidden(ann, FANN_SIGMOID);
	fann_set_activation_function_output(ann, FANN_SIGMOID);


	
	new_input_min = 0.0;
	new_input_max = 1.0;
   	new_output_min = 0.0;
   	new_output_max = 1.0;
	train_data = fann_read_train_from_file("exp_data.txt");
	fann_scale_train_data(train_data, new_input_min, new_input_max);
	fann_set_scaling_params(ann, train_data, new_input_min, new_input_max, new_output_min, new_output_max);
	fann_train_on_data(ann, train_data, max_epochs, epochs_between_reports, desired_error);
	
   		
	fann_save(ann, "exp_float.net");


	fann_type in1, in2;
	in1 = 0.0;
	in2 = 0.0;
	
	int i;
	float step = 0.05;
	int num_of_tests = 100;


	printf("\n\nf(x) = exp(x) TEST:\n\n");
	
	num_of_tests = 49;
	in1 = -1.0;
	in2 = in1 + step;

	for(i = 0; i < num_of_tests / 2; i++)
	{
		fann_type *out[2];
		fann_type in[2];
		float error[2];
		in[0] = in1;
		in[1] = in2;

		fann_scale_input(ann, &in[0]);
		fann_scale_input(ann, &in[1]);
		
		printf("SCALED IN: %f, %f\tDESCALED IN: %f, %f\n", in[0], in[1], in1, in2);
		
		out[0] = fann_run(ann, &in[0]);
		out[1] = fann_run(ann, &in[1]);
		printf("SCALED OUT: %f, %f\t", *out[0], *out[1]);
		fann_descale_output(ann, out[0]);
		fann_descale_output(ann, out[1]);
		fann_descale_input(ann, &in[0]);
		fann_descale_input(ann, &in[1]);
		printf("DESCALED OUT: %f, %f\n", *out[0], *out[1]);
	
	

		
		error[0] = fabs(f((float)in[0]) - (float)*out[0]);
		error[1] = fabs(f((float)in[1]) - (float)*out[1]);
		in1 = in2 + step;
		in2 = in1 + step;
		continue;
		

		printf("\t\t\t\tx = %f\t\t|\tx = %f\n", (float)in[0], (float)in[1]);
		printf("\t\t\tf(%f) = %f\t\t|", (float)in[0], f((float)in[0]));
		printf("\tf(%f) = %f\n", (float)in[1], f((float)in[1]));
		printf("\texp(%f) = %f\t\t|", (float)in[0], f((float)in[0]));
		printf("\texp(%f) = %f\n", (float)in[1], f((float)in[1]));
		printf("\t\texp(%f) = %f\t\t|", (float)in[0], f((float)in[0]));
		printf("\texp(%f) = %f\n", (float)in[1], f((float)in[1]));
		printf("ANN G(%f) = %f\td: %f\t\t|", (float)in[0], (float)*out[0], error[0]);
		printf("\tANN G(%f) = %f\td: %f\n", (float)in[1], (float)*out[1], error[1]);
		
		
		putchar('\n');

		
	
	}
	
	


	fann_destroy_train(train_data);
	fann_destroy(ann);

	return 0;
}
