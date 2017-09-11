#include "stdio.h"
#include "math.h"
#include "fann.h"
#include "floatfann.h"

int main()
{
	const unsigned int num_input = 1;
	const unsigned int num_output = 1;
	const unsigned int num_layers = 3;
	const unsigned int num_neurons_hidden = 2;

	const float angleRange = 3.0f;
	const float angleStep = 0.1f;
	int instances = (int)(angleRange/angleStep);

	struct fann *ann;

	ann = fann_create_standard(num_layers, num_input, num_neurons_hidden, num_output);

	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

	fann_set_train_stop_function(ann, FANN_STOPFUNC_BIT);
  	fann_set_bit_fail_limit(ann, 0.02f);

	fann_set_training_algorithm(ann, FANN_TRAIN_INCREMENTAL);
  	fann_randomize_weights(ann, 0, 1);

	struct fann_train_data *trainingSet;
	trainingSet = fann_create_train(instances, 1, 1);
	  float angle=0;
	  for(int instance=0; instance < instances; angle+=angleStep, instance++) {
	      trainingSet->input[instance][0] = angle;
	      trainingSet->output[instance][0] = sinf(angle);
	  }

	  fann_train_on_data(ann, trainingSet, 20000, 1000, 1e-8f); // epochs, epochs between reports, desired error

	  int k = 0;
	  angle=0;
	  for(int instance=0; instance < instances; angle+=angleStep, instance++) {
	      float sin_angle = sinf(angle);
	      float *o = fann_run(ann, &angle);
	      printf("%f\t%d\t%f\t%f\t\n", angle, k++, *o, sin_angle);
	  }

	  fann_destroy(ann);

	return 0;

}
