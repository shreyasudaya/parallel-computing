//Parallel implementation using openmp
#include <bits/stdc++.h>
#include <omp.h>

//Change size for larger inputs. Keep twice the size to accomodate the identity matrix
#define SIZE 10
using namespace std;
//Using traditional method of determinant and adjoint is very cumbersome so we will use gaussian elimination
int main()
{
        
         time_t start,end;
		 float a[SIZE][SIZE], x[SIZE], ratio;
		 int i,j,k,n;

         //Give to three decimal points
         cout<< setprecision(3)<< fixed;

		 cout<<"Enter size of matrix: ";
		 cin>>n;

	
		 cout<<"Enter coefficients of Matrix: " << endl;
		 for(i=1;i<=n;i++)
		 {
			  for(j=1;j<=n;j++)
			  {
				   cout<<"a["<< i<<"]["<< j<<"]= ";
                   cin>>a[i][j];
			  }
		 }

		 //Augmenting 
        
		 for(i=1;i<=n;i++)
		 {
			  for(j=1;j<=n;j++)
			  {
				   if(i==j)
				   {
				    	a[i][j+n] = 1;
				   }
				   else
				   {
				    	a[i][j+n] = 0;
				   }
			  }
		 }
        time(&start);
		//Gauss jordan
        #pragma omp parallel for private(j, k, ratio) shared(a, n)
		 for(i=1;i<=n;i++)
		 {
			  if(a[i][i] == 0.0)
			  {
				   cout<<"Mathematical Error!";
				   exit(0);
			  }
			  for(j=1;j<=n;j++)
			  {
				   if(i!=j)
				   {
					    ratio = a[j][i]/a[i][i];
					    for(k=1;k<=2*n;k++)
					    {
					     	a[j][k] = a[j][k] - ratio*a[i][k];
					    }
				   }
			  }
		 }
		 //make diagonal to 1
        #pragma omp parallel for private(j) shared(a, n)
		 for(i=1;i<=n;i++)
		 {
			  for(j=n+1;j<=2*n;j++)
			  {
			   	a[i][j] = a[i][j]/a[i][i];
			  }
		 }
        time(&end);
		
		 cout<< endl<<"Inverse Matrix is:"<< endl;
         double t=double(end-start);
		 for(i=1;i<=n;i++)
		 {
			  for(j=n+1;j<=2*n;j++)
			  {
			   	cout<< a[i][j]<<"\t";
			  }
			  cout<< endl;
		 }
         cout<<"Time Taken is : "<<t<<endl;
		 return(0);
}