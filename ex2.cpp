#include <iostream>
#include <cstdlib>
#include <cstring>
#include <omp.h>
#include <sys/time.h>


void multisort(int *arr, int *s, int N);
int cmp_f(const void *a, const void *b);
void merge(int *x, int N, int *temp);

int main(int argc, char *argv[])
{
	struct timeval start, end;

	int N = 65536/4, t;
	int *A;
	int *temp;

	double delta;

	std::cout << "Number of threads: ";
	std::cin >> t;

	omp_set_num_threads(t);

	std::cout << "Array size: ";
	std::cin >> N;

	A = new int[N];
	temp = new int[N];

	for (int i = 0; i < N; i++){
		std::cout << "A[" << i << "] = ";
		std::cin >> A[i];
	}

	for (int i = 0; i < N; i++){
		std::cout << A[i] << "\t";
	}

	/*srand(time(0));
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			A[i] = rand() % 1025;
		}
	}*/
	std::cout << std::endl;

	gettimeofday(&start, NULL);
	#pragma omp parallel shared(A)
	#pragma omp single
	multisort(A, temp, N);

	for (int i = 0; i < N; i++){
		std::cout << A[i] << "\t";
	}

	std::cout << std::endl;

	delete [] A;
	delete [] temp;

	gettimeofday(&end, NULL);

	delta = ((end.tv_sec  - start.tv_sec) * 1000000u + 
         end.tv_usec - start.tv_usec) / 1.e6;

	//std::cout << "Time:" << delta << std::endl;

	return 0;
}

int cmp_f(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b );
}

void merge(int *x, int N, int *temp)
{
	int i = 0;
	int j = N/2;
	int k = 0;

	while (i < N/2 && j < N){
		if (x[i] < x[j]){
			temp[k] = x[i];
			i++;
		}
		else {
			temp[k] = x[j];
			j++;
		}

		k++;
	}

	while (i < N/2){
		temp[k] = x[i];
		i++;
		k++;
	}

	while (j < N){
		temp[k] = x[j];
		j++;
		k++;
	}

	//making sure no element was left out of order
    qsort(&temp[0], N, sizeof(int), cmp_f);

	memcpy(x, temp, N*sizeof(int));
}

void multisort(int *arr, int *s, int N)
{
	int q = N / 4;

	if (q < 4){
		qsort(&arr[0], N, sizeof(int), cmp_f);
	}
	else {
        //split the input array to 4 subarrays
        #pragma omp task
		multisort(&arr[0], &s[0], q);
        #pragma omp task
		multisort(&arr[N/4], &s[N/4], q);
        #pragma omp task
		multisort(&arr[N/2], &s[N/2], q);
        #pragma omp task
		multisort(&arr[3*N/4], &s[3*N/4], q);
		#pragma omp taskwait

		//merge the 4 subarrays in couples
		#pragma omp task
		merge(&arr[0], N/2, &s[0]);
		#pragma omp task
		merge(&arr[N/2], N/2, &s[N/2]);
        #pragma omp taskwait

        //merge the couples together
        merge(&arr[0], N, &s[0]);		
	}
}