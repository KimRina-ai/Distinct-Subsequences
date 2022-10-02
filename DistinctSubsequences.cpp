#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct INPUT {
	char X[10000];
	char Z[100];
}input;

input* in;

typedef struct OUTPUT {
	int count[10000][100];
	int result;
}output;

output* out;

int fileRead(char* filename);
void run_algorithm(int num_cases);
void fileWrite(int num_schedule, char* filename);

int main()
{
	char inFileName[5][20] = { "Input_1.txt", "Input_2.txt", "Input_3.txt", "Input_4.txt", "Input_5.txt" };
	char outFileName[5][20] = { "Output_1.txt", "Output_2.txt", "Output_3.txt", "Output_4.txt", "Output_5.txt" };

	for (int i = 0; i < 5; i++)
	{
		int num_cases;	

		num_cases = fileRead(inFileName[i]);
		run_algorithm(num_cases);
		fileWrite(num_cases, outFileName[i]);
	}

	return 0;
}

/*
	fileRead function
	parameter : filename(char)
	return : num_cases(int)
	function : Read text file
*/
int fileRead(char* filename)
{
	int num_cases;

	FILE* inFile;

	inFile = fopen(filename, "r");
	if (inFile == NULL)
		printf("Input File Could Not Be Opened\n");

	//Receive the first line (indicating the number of test cases)
	fscanf(inFile, "%d", &num_cases);

	in = (input*)malloc(sizeof(input) * num_cases);
	out = (output*)malloc(sizeof(output) * num_cases);

	//Get string X, Z from text file
	for (int i = 0; i < num_cases; i++)
	{
		fscanf(inFile, "%s", &in[i].X);
		fscanf(inFile, "%s", &in[i].Z);
	}

	fclose(inFile);

	return num_cases;
}

/*
	run_algorithm function
	parameter : num_cases(int)
	function : output the number of distinct occurences of X in X as a subsequence
*/
void run_algorithm(int num_cases)
{
	for (int n = 0; n < num_cases; n++)
	{
		int len_x = strlen(in[n].X);
		int len_z = strlen(in[n].Z);

		//initialize count[0][0]
		if (in[n].X[0] == in[n].Z[0])
			out[n].count[0][0] = 1;
		else
			out[n].count[0][0] = 0;

		for (int j = 0; j < len_z; j++)
		{
			for (int i = 1; i < len_x; i++)
			{
				//initialize count[0][j] = 0 when j != 0 & i == 1 
				if (j != 0 && i == 1)
					out[n].count[i - 1][j] = 0;

				//Replicate the number in the previous row
				out[n].count[i][j] = out[n].count[i - 1][j];
				
				//When X, Z is same character
				if (in[n].X[i] == in[n].Z[j])
				{
					if (j == 0)		//if j == 0, plus 1
						out[n].count[i][j]++;
					else			//when j != 0, previous row + left diagonal num
						out[n].count[i][j] += out[n].count[i - 1][j - 1];
				}
			}
		}
		int x = len_x - 1;
		int z = len_z - 1;
		out[n].result = out[n].count[x][z];
	}
}

/*
	fileWrite function
	parameter : num_cases(int), filename(char)
	function : Write text file the output
*/
void fileWrite(int num_cases, char* filename)
{
	FILE* outFile;

	outFile = fopen(filename, "w");
	
	//print out text file the results
	for (int i = 0; i < num_cases; i++)
		fprintf(outFile, "%d\n", out[i].result);

	fclose(outFile);
}