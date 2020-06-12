// MPITest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "mpi.h"
#include <math.h>

using namespace std;

int main(int argc, char* argv[])
{
	int myrank, res, p, dst = 0, tag = 0, ar[100], i;

	for (int i = 0; i < 100; i++)
		ar[i] = i;

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if (myrank != 0)
	{
		int interval = 100 / (p - 1), x, y;
		x = interval * (myrank - 1);
		y = interval * (myrank)-1;

		res = 0;
		for (i = x; i <= y; i++)
			res += ar[i];
		//cout<<"******sum "<<res <<"\n";
		MPI_Send(&res, sizeof(res), MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	else
	{
		int sum = 0;
		for (int src = 1; src < p; src++)
		{
			MPI_Recv(&res, sizeof(res), MPI_INT, src, 0, MPI_COMM_WORLD, &status);
			printf("sum recieved from the process: %d is %d\n", src, res);
			sum = sum + res;
		}
		printf("the total sum is %d\n", sum);
	}

	MPI_Finalize();
	return 0;
}

/*
	@Params:
		a: the given array
		b: the actual number to attach the array
*/

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
