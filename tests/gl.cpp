#include <mgl2/mgl.h>
#include <cstdio>
#include <cmath>
#include "fann.h"
#include "floatfann.h"
#include <cstdlib>

using namespace std;

void logic(void)
{
	const unsigned int num_input = 2;
	const unsigned int num_output = 1;
	const unsigned int num_layers = 3;
	const unsigned int num_neurons_hidden = 3;

	const float angleRange = 3.0f;
	const float angleStep = 0.1f;
	int instances = (int)(angleRange/angleStep);
	int instances2 = instances*instances;	

	struct fann *ann;

	ann = fann_create_standard(num_layers, num_input, num_neurons_hidden, num_output);

	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

	fann_set_train_stop_function(ann, FANN_STOPFUNC_BIT);
  	fann_set_bit_fail_limit(ann, 0.02f);

	fann_set_training_algorithm(ann, FANN_TRAIN_INCREMENTAL);
  	fann_randomize_weights(ann, 0, 1);

	struct fann_train_data *trainingSet;
	trainingSet = fann_create_train(instances*instances, 2, 1);
	
	float angle = 0.0f;
	float *tmp = NULL;
	tmp = (float *)malloc(instances*sizeof(float));
	if(tmp != 0)
	{
		for(int instance = 0; instance < instances; angle+=angleStep, instance++)
		{
			tmp[instance] = angle;
		}
	}
	

	angle = 0;
	int global_counter = 0;
	for(int instance = 0; instance < instances; angle+=angleStep, instance++)
		for(int counter = 0; counter < instances; counter++, global_counter++)
		{
			trainingSet->input[global_counter][0] = angle;
			trainingSet->input[global_counter][1] = tmp[counter];
			trainingSet->output[global_counter][0] = sinf(angle + tmp[counter]);
		}
/*
	for(global_counter = 0; global_counter < instances2; global_counter++)
	{
		printf("sin(%f + %f) = %f\n", trainingSet->input[global_counter][0], trainingSet->input[global_counter][1], trainingSet->output[global_counter][0]);
	}
*/
	fann_train_on_data(ann, trainingSet, 20000, 1000, 1e-8f); // epochs, epochs between reports, desired error

	int k = 0;
	angle = 0;


	global_counter = 0;


	FILE *file = NULL;
	char *file_name = "out.log";
	if((file = fopen("out.log", "w+")) == NULL)
		printf("Can not open file %s\n", file_name);

	for(int instance = 0; instance < instances; angle+=angleStep, instance++)
		for(int counter = 0; counter < instances; counter++, global_counter++)
		{
			float sin_angle = sinf(angle + tmp[counter]);
			float input_data[2] = {angle, tmp[counter]};
	      		float *o = fann_run(ann, input_data);
			printf("%f+%f\t%d\t%f\t%f\t\n", angle, tmp[counter], k++, *o, sin_angle);
			if(file)
				fprintf(file, "%f\t%f\t%f\n", angle, tmp[counter], *o);
		}

	
	fann_destroy(ann);
	
	if(tmp != NULL) free(tmp);
	if(file != NULL) fclose(file);
}

void ReadData(mglData *data)
{
	FILE *file = fopen("out.log", "r");
	float x, y, z;
	for(int i = 0; i < 30*30; i+=2)
	{
		fscanf(file, "%f\t%f\t%f\n", &x, &y, &z);
		data->a[i] = x;
		data->a[i + 1] = 0;

	}

}


int main(int argc,char **argv)
{
	mglGraph gr;
	
	mglData z(30, 30);
	mglData z2(30, 30);
//	ReadData(&z2);
/*	
	float angle = 0.0f;
	const float angleMax = 3.0f;
	const float angleStep = 0.1f;
	const int num_steps = (int)(angleMax/angleStep);
	float angleRange[num_steps];
	for(int i = 0; i < num_steps; angle += angleStep, i++)
		angleRange[i] = angle;
	angle = 0.0f;
	for(int i = 0, angle = 0.0f; i < 30; i++)
		for(int j = 0; j < 30; angle+=angleStep, j+=2)
		{
			z.a[i*num_steps + j] = angle;
			z.a[i*num_steps + j + 1] = angleRange[i];
			 
		}
*/
	z.Fill(0.0, 3.0, 'x');
	z.Fill(0.0, 3.0, 'y');	
	z.Modify("sin(x + y)");

	gr.SetRanges(0,3,0,3,-1,1);
	gr.Rotate(50, 60);
	gr.Light(true);
	gr.Surf(z, "R");
	gr.Axis();
	gr.Grid();
	gr.Box();


	gr.WriteFrame("test.png");

	return 0;

}
