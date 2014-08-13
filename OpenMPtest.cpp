//Author: Christopher Hiles
//Matrix algorithm *borrowed* from http://www.kerrywong.com/2009/03/07/matrix-multiplication-performance-in-c/
//
//Application that tests matrix multiplcation methods.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <sstream>
#include <omp.h>	//openMP
#include <algorithm> //for_each
using namespace std;


#pragma warning(disable: 4996)



void matrixLog(string message);



int main(void)
{
	
	
	int matrix_sizes[3] = { 40, 1000, 2000 };
	

	for (int i = 0; i < 3; ++i)
	{

		clock_t time;

		int matrix_size = matrix_sizes[i];

		char initMessage[150];
		sprintf(initMessage, "\n\nBeginning ijk iteration of matrix of size %d * %d...\n", matrix_size, matrix_size);
		matrixLog(initMessage);

		string message;

		float **A, **B, **C;

		A = new float*[matrix_size];
		B = new float*[matrix_size];
		C = new float*[matrix_size];

		for (int i = 0; i < matrix_size; i++)
		{
			A[i] = new float[matrix_size];
			B[i] = new float[matrix_size];
			C[i] = new float[matrix_size];
		}

		for (int i = 0; i < matrix_size; i++)
		{
			for (int j = 0; j < matrix_size; j++)
			{
				A[i][j] = rand();
				B[i][j] = rand();
			}
		}




		time = clock();

		{
			for (int i = 0; i < matrix_size; i++)
			{
				for (int j = 0; j < matrix_size; j++)
				{
					//C[i][j] = 0;
					for (int k = 0; k < matrix_size; k++)
					{
						C[i][j] += A[i][k] * B[k][j];
					}
				}
			}
		}
		time = clock() - time;
		message = "Multiplcation Time = ";
		message += to_string((float)time / CLOCKS_PER_SEC);
		message += "seconds.\n";
		matrixLog(message);

		for (int i = 0; i < matrix_size; i++)
		{
			delete A[i];
			delete B[i];
			delete C[i];
		}

		delete A;
		delete B;
		delete C;
	}

	//OpenMP ijk loops
	for (int i = 0; i < 3; ++i)
	{

		clock_t time;

		int matrix_size = matrix_sizes[i];

		char initMessage[150];
		sprintf(initMessage, "\n\nBeginning ijk iteration using OpenMP with parallel and for optimization of matrix of size %d * %d...\n", matrix_size, matrix_size);
		matrixLog(initMessage);

		string message;

		float **A, **B, **C;

		A = new float*[matrix_size];
		B = new float*[matrix_size];
		C = new float*[matrix_size];

		for (int i = 0; i < matrix_size; i++)
		{
			A[i] = new float[matrix_size];
			B[i] = new float[matrix_size];
			C[i] = new float[matrix_size];
		}

		for (int i = 0; i < matrix_size; i++)
		{
			for (int j = 0; j < matrix_size; j++)
			{
				A[i][j] = rand();
				B[i][j] = rand();
			}
		}




		time = clock();

		
		#pragma omp parallel for//magic/millions of man-hours of hard labor
			for (int i = 0; i < matrix_size; i++)
			{
				for (int j = 0; j < matrix_size; j++)
				{
					//C[i][j] = 0;
					for (int k = 0; k < matrix_size; k++)
					{
						C[i][j] += A[i][k] * B[k][j];
					}
				}
			}
		
		time = clock() - time;
		message = "Multiplcation Time = ";
		message += to_string((float)time / CLOCKS_PER_SEC);
		message += "seconds.\n";
		matrixLog(message);

		for (int i = 0; i < matrix_size; i++)
		{
			delete A[i];
			delete B[i];
			delete C[i];
		}

		delete A;
		delete B;
		delete C;
	}
	return 0;

}



void matrixLog(string message)
{
	ofstream logFile;
	logFile.open("MatrixMultiplicationLog.txt", ios::app);
	logFile << message;
	logFile.close();
}
