#include <bits/stdc++.h>
#include <chrono>
#include "mpi.h"

using namespace std;
//Parallel implementation of array sum using simple MPI_Scatter
//Program can be done with just Reduce and Bcast but will use scatter in case processors are not that many

int main(int argc,char* argv[]){
    time_t start,end;
    //Initialize MPI
    MPI_Init(&argc,&argv);
    int rank,size;
    //Determine processors rank and size of communicating grp
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int n;
    int sum;
    int *A;
    //at root processor take in input for array size and make consecutive numbered array for it
    if(rank==0){
        cin>>n;
        A = new int [n];
        for(int i=0; i<n; i++)
    		A[i]=i+1;
    }
    //Broadcast
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int subarray_size = n/size;
    int sub[subarray_size];

    time(&start);
    int partial=0;
    //Scatter the array to subarray which calculates partial sums 
    MPI_Scatter(A, subarray_size, MPI_INT, sub, subarray_size, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i=0; i<subarray_size; i++){
		partial+=sub[i];
	}
    //Return partial to final sum
    MPI_Reduce(&partial, &sum, 1, MPI_INT, MPI_SUM, 0,MPI_COMM_WORLD);
    time(&end); 
    double t=double(end - start);
    cout<<"The Sum of array is: "<<sum<<endl;
    cout<<"The time taken is: "<<t<<endl;
    
    MPI_Finalize();
    
}