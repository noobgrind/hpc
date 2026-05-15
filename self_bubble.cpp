#include<iostream>
#include<omp.h>
using namespace std;


void bub(int arr[], int n)
{
	for(int i = 0; i < n-1; i++)
	{
		for(int j = 0; j < n - i - 1; j++)
		{
			if(arr[j] > arr[j+1])
				swap(arr[j], arr[j+1]);
		}
	}
}

void bub_para(int arr[], int n)
{
	for(int i = 0; i < n; i++)
	{
		#pragma omp parallel for
		for(int j = 0; j < n-1; j+=2)
		{
			if(arr[j] > arr[j + 1])
				swap(arr[j], arr[j+1]);
		}

		#pragma omp parallel for
		for(int j = 1; j < n-1; j+=2)
		{
			if(arr[j] > arr[j + 1])
				swap(arr[j], arr[j+1]);
		}
	}
}

int main()
{
	int arr[] = {5,4,3,2,1,5,4,3,2,1}, size = 10;
	int arr2[] = {5,4,3,2,1,5,4,3,2,1}, size2 = 10;
	double start,end;
	start = omp_get_wtime();
	bub(arr, size);
	end = omp_get_wtime();
	cout << "Time : " << end-start << endl;
	for(auto i : arr)
		cout << i << " ";
	cout << endl;
	start = omp_get_wtime();
	bub_para(arr2, size2);
	end = omp_get_wtime();
	cout << "Time : " << end-start << endl;
	for(auto i : arr)
		cout << i << " ";
	return 0;
}