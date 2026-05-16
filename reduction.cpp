#include<iostream>
using namespace std;

int main()
{
	int arr[] = {1,2,3,4,5,6,7,8,9,10};

	int sum = 0,min_v = arr[0], max_v = arr[0];

	#pragma omp parallel for reduction(+:sum) reduction(min:min_v) reduction(max:max_v)
	for(int i = 0; i < 10; i++)
	{
		sum += arr[i];

		if(arr[i] < min_v)
			min_v = arr[i];
		if(arr[i] > max_v)
			max_v = arr[i];


	}


	cout << "Sum : " << sum <<  endl;
	cout << "Min : " << min_v <<  endl;
	cout << "Max : " << max_v <<  endl;
	return 0;
}
//       !g++ -fopenmp filename.cpp -o filename
//       !./filename
