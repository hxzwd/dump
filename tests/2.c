#include "stdio.h"
#include "math.h"
#include "fann.h"
#include "floatfann.h"
#include "string.h"
#include "memory.h"
#include "stdlib.h"
#include "time.h"




int main(void)
{

	FILE *file = NULL;
	struct fann *ann = NULL;
	char *other_file_name = "new_out.log";
	char *out_file_name = "output.txt";
	int num_of_values = 0;
	ann = fann_create_from_file("ANN.NET");
	float *input = NULL;	


	if((file = fopen(other_file_name, "r")) != NULL)
	{
		fscanf(file, "%d", &num_of_values);
		input = (float *)malloc(sizeof(float)*num_of_values*2);
		num_of_values = 0;
		while(!feof(file))
		{
			
			float x, y;
			fscanf(file, "%f%f", &x, &y);
			printf("%f\t\t%f\n", x, y);
			if(input)
			{
				input[num_of_values] = x;
				input[num_of_values + 1] = y;
			}
			
			num_of_values += 2;
		}
		printf("%d\n", num_of_values);

	}

	if(!file) 
	{
		fclose(file);
		file = NULL;
	}
	if((file = fopen(out_file_name, "w+")) == NULL)
		printf("Can not open file %s\n", out_file_name);

	for(int i = 0; i < num_of_values; i += 2)
	{
		float *output;
		float in[2];
		in[0] = input[i];
		in[1] = input[i + 1];
		output = fann_run(ann, in);

		printf("%f\t%f\t%f\t%f\n", in[0], in[1], *output, fabs(*output - sinf(in[0] + in[1])));
		if(file != NULL)
		{
			if(i != 0 && i % 60 == 0)
				fprintf(file, "\n");
			fprintf(file, "%f\t%f\t%f\n", in[0], in[1], *output);
		}
			
	}

	for(int i = 0; i < num_of_values; i += 2)
	{
		float *output;
		float in[2];
		in[1] = input[i];
		in[0] = input[i + 1];
		output = fann_run(ann, in);

		printf("%f\t%f\t%f\t%f\n", in[0], in[1], *output, fabs(*output - sinf(in[0] + in[1])));
		if(file != NULL)
		{
			if(i != 0 && i % 60 == 0)
				fprintf(file, "\n");
			fprintf(file, "%f\t%f\t%f\n", in[0], in[1], *output);
		}
			
	}  
	
	
	if(!input) free(input);
	if(!file) fclose(file);
	fann_destroy(ann);
	return 0;
}
