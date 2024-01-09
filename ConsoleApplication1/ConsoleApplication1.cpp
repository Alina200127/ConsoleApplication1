#include <iostream>
#include <omp.h>
#include <time.h>
#include <math.h>
using namespace std;


void umn_matr_parallel(float** A, float** B, float** C, int N)
{
#pragma omp parallel for shared(A, B, C)
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			C[i][j] = 0.0;
			for (int k = 0; k < N; k++) C[i][j] += A[i][k] * B[k][j];
		}
	}
}


void umn_matr(float** A, float** B, float** C, int N)
{
	//#pragma omp parallel for shared(A, B, C) private (i,j,k)
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			C[i][j] = 0.0;
			for (int k = 0; k < N; k++) C[i][j] += A[i][k] * B[k][j];
		}
	}
}
int main()
{
	int i, j, k, N;
	cin >> N;
	cout << "� ������� " << omp_get_num_procs() << " ����������" << endl;
	float** a, ** b, ** c;
	a = new float* [N];
	for (i = 0; i < N; i++)
		a[i] = new float[N];
	b = new float* [N];
	for (i = 0; i < N; i++)
		b[i] = new float[N];
	c = new float* [N];
	for (i = 0; i < N; i++)
		c[i] = new float[N];
	float t1, t2, tn, tk;

	// ������������� ������

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			a[i][j] = b[i][j] = sin(i) * cos(j);
	cout << "�����!!!\n";
	tn = omp_get_wtime();
	umn_matr(a, b, c, N);
	tk = omp_get_wtime();
	cout << "����� ����������������� �����=" << tk - tn << endl;
	t1 = omp_get_wtime();
	umn_matr_parallel(a, b, c, N);
	t2 = omp_get_wtime();
	cout << "����� ������������� �����=" << t2 - t1 << endl;
}