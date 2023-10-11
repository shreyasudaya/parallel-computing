#include <bits/stdc++.h>
#include <chrono>
#include "mpi.h"

using namespace std;


int main(){
    time_t start,end;
    int n;
    cout<<"Give size of array: ";
    cin>>n;
    int array[n];
    for(int i=0;i<n;i++){
        array[i]=i+1;
    }
    int sum=0;
    time(&start);
    for(int i=0;i<n;i++){
        sum+=array[i];
    }
    
    time(&end); 
    double t=double(end - start);
    cout<<"The Sum of array is: "<<sum<<endl;
    cout<<"The time taken is: "<<t<<endl;
    
}