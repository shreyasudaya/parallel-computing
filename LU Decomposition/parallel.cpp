#include <bits/stdc++.h>
#include <mpi.h>

using namespace std;

void lu(float[][10], float[][10], float[][10], int, int);
void output(float[][10], int);

int main(int argc, char **argv)
{
    
    time_t start,end;
    float a[10][10], l[10][10], u[10][10];
    int n;
    int i = 0, j = 0;
    int size, rank;
    //Init
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        cout << "Enter size of 2d array(Square matrix) : ";
        cin >> n;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                cout << "Enter values no:" << i << ", " << j << ": ";
                cin >> a[i][j];
            }
        }
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&a, 100, MPI_FLOAT, 0, MPI_COMM_WORLD);
    time(&start);
    lu(a, l, u, n, rank);
    time(&end);
    double t=double(end-start);
    if (rank == 0)
    {
        cout << "\nL Decomposition\n\n";
        output(l, n);
        cout << "\nU Decomposition\n\n";
        output(u, n);
        cout<<"Time taken: "<<t<<endl;
    }

    MPI_Finalize();
    return 0;
}

void lu(float a[][10], float l[][10], float u[][10], int n, int rank)
{
    int i = 0, j = 0, k = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (j < i)
                l[j][i] = 0;
            else
            {
                l[j][i] = a[j][i];
                for (k = 0; k < i; k++)
                {
                    l[j][i] = l[j][i] - l[j][k] * u[k][i];
                }
            }
        }
        for (j = 0; j < n; j++)
        {
            if (j < i)
                u[i][j] = 0;
            else if (j == i)
                u[i][j] = 1;
            else
            {
                u[i][j] = a[i][j] / l[i][i];
                for (k = 0; k < i; k++)
                {
                    u[i][j] = u[i][j] - ((l[i][k] * u[k][j]) / l[i][i]);
                }
            }
        }
        //Send the cells for l and u to root to recieve
        if (rank != 0)
        {
            MPI_Send(&l, 100, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
            MPI_Send(&u, 100, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
        }
        if (rank == 0 && i != 0)
        {
            MPI_Recv(&l, 100, MPI_FLOAT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&u, 100, MPI_FLOAT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }
}

void output(float x[][10], int n)
{
    int i = 0, j = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%f ", x[i][j]);
        }
        cout << "\n";
    }
}
