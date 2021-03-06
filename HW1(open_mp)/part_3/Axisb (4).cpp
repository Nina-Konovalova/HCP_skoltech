
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>

using namespace std;

//bool DiagDominant(int matrix[N][N], int N) {
//	for (int i = 0; i < N; i++) {
//		int sum = 0;
//		for (int j = 0; j < N; j++) {
//			if (i != j) {
///				sum += abs(matrix[i][j];
//		         }
//	        }
//		if (abs(matrix[i][i]) >= sum) {
//		       return True;
//		 } else {
//		       return False;
//		 }
//	 }
//}        	       

void matrix_diagonal_big(double ** matrix, size_t N)
{
    srand(time(NULL));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = 1;
	}
	matrix[i][i] = 10;

    }
}

void rand_init_vector(double * vector, size_t N) {
    srand(time(NULL));
    unsigned int seed = 0;
    for (int i = 0; i < N; i++) {
        vector[i] = (double)rand_r(&seed) / RAND_MAX;
     }

}


double ** malloc_matrix(size_t N)
{
    double ** matrix = (double **)malloc(N * sizeof(double *));

    for (int i = 0; i < N; ++i)
    {
        matrix[i] = (double *)malloc(N * sizeof(double));
    }

    return matrix;
}




double * malloc_vector(size_t N)
{
    double * vector = (double *)malloc(N * sizeof(double));

    return vector;
}


void zero_init_vector(double * vector, size_t N)
{
    for (int i = 0; i < N; i++)
    {
        vector[i] = 0.0;
        
    }
}



void free_matrix(double ** matrix, size_t N)
{
    for (int i = 0; i < N; ++i)
    {
        free(matrix[i]);
    }

    free(matrix);
}


bool diff(double *x, double *x1, int N, double eps) {
   double diff = 0;

   for (int i = 0; i < N; i++) {
	   diff += (x1[i] - x[i])*(x1[i] - x[i]);
   }

   return (sqrt(diff) < eps);

}


int main() {

   

    double ** A, *b, *x, *x1;
  //  double start, end;
     int Num_Iter = 500, N = 30;
    // matrices

  //  printf("Starting:\n");

   A = malloc_matrix(N);
   matrix_diagonal_big(A, N);
   cout << "A" << endl;
   


   omp_set_dynamic(0);
   omp_set_num_threads(5);


   for (int i = 0; i < N; i++) {
	   for (int j = 0; j < N; j++) {
	   cout << A[i][j]<< ' ';
	   }
	   cout << endl;
   }
   cout << endl;
   cout << 'b' << endl;
    b =  malloc_vector(N);
    rand_init_vector(b,N);
     

    for (int i = 0; i < N; i++) {
	    cout << b[i] << ' ';
   }
    cout << endl;

    x = malloc_vector(N);
    rand_init_vector(x,N);


    x1 = malloc_vector(N);
    for (int i = 0; i < N; i++) {
	   x1[i] = 1 ;
    }
   cout << "x intial" << endl;
   for (int i = 0; i < N; i++) {
            cout << x[i];
   }
   cout << endl;
unsigned int seed = 0;
double eps = 1e-10;
double start = omp_get_wtime();
double sigma = 0;
int i,j;
for (int k = 0; k < Num_Iter; k++) {   
#pragma omp parallel for shared (A,b) private (sigma,i,j) schedule(static) num_threads(5)
// one iteration of Jacoby
   for (i = 0; i < N; i++) {
     int tid = omp_get_thread_num();
    //  cout << tid << ' ';
      sigma = 0;
      for (j = 0; j < N; j++) {
          if (j != i) {
             sigma += A[i][j]*x[j];
          } 
      }
      x[i] = (b[i] - sigma)/A[i][i];
   }		
}
double end = omp_get_wtime();

free_matrix(A,N);
free(b);

cout << "x final"<< endl;
for (int i = 0; i < N; i++) {
	cout << x[i]<< ' ';
}
cout << endl;
cout << "Time: " << double(end - start) << endl;
return 0;
}

