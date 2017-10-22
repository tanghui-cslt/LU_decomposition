#include<cmath>
#include<cstring>
#include <iostream>
using namespace std;

void solution(double **a, double *b, int n);
void LU_decom(double **&a, double **&l, double **&u, int n);
void Calc_X(double **&l, double **&u, double *&b, int n);

int main()
{
	double **a = NULL;
	double *b = NULL;
	int n = 4;

	a = new double *[n];
	b = new double[n];

	double temp[4][4] = {2,10,0,-3,-3,-4,-12,13,1,2,3,-4,4,14,9,-13};
	//double temp[4][4]= { 9,18,9,-27,18,45,0,-45,9,0,126,9,-27,-45,9,135 };
	//double temp_b[4] = { 1,2,16,8 };
	double temp_b[4] = { 10,5,-2,7 };
	for (int i = 0; i < n; i++)
	{
		a[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			a[i][j] = temp[i][j];
		}
		b[i] = temp_b[i];
	}

	solution(a, b, n);
	getchar();
}

void solution(double **a, double *b, int n)
{
	double **L = NULL, **U = NULL;
	//LU分解
	LU_decom(a, L, U, n);
	//根据LU计算x的值
	Calc_X(L, U, b, n);
}

void LU_decom(double **&a, double **&l, double **&u, int n)
{
	//初始化空间l u
	l = new double *[n];
	u = new double *[n];
	for (int i = 0; i < n; i++)
	{
		l[i] = new double[n];
		u[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			l[i][j] = 0;
			u[i][j] = 0;
			if (i == j)
				l[i][j] = 1;
		}
	}

	//计算l u矩阵的结果
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j == 0 && i != 0)
				l[i][j] = a[i][j] / u[0][0];
			else if (i == 0)
				u[i][j] = a[i][j];
			else {
				int min_temp = i > j ? j : i;

				if (i > j)
				{
					double sum = 0;
					for (int k = 0; k < min_temp; k++)
					{
						sum += l[i][k] * u[k][j];
					}
					l[i][j] = (a[i][j] - sum) / u[min_temp][min_temp];
				}
				else {
					double sum = 0;
					for (int k = 0; k < min_temp; k++)
					{
						sum += l[i][k] * u[k][j];
					}
					u[i][j] = (a[i][j] - sum);
				}
			}
			//cout << l[i][j] << " ";
		}
		//cout << endl;
	}

}

void Calc_X(double **&l, double **&u, double *&b, int n)
{
	double *y = NULL, *x = NULL;
	x = new double[n];
	y = new double[n];
	//计算y
	for (int i = 0; i < n; i++)
	{
		
		double sum_x = 0;
		for (int j = 0; j < i; j++)
		{
			sum_x += l[i][j] * y[j];
		}
		y[i] = b[i] - sum_x;
		//cout << y[i] << " ";
	}

	//计算x
	
	for (int i = n - 1; i >= 0; i--)
	{

		double sum_y = 0;
		for (int j = n - 1; j > i; j--)
		{
			sum_y += u[i][j] * x[j];
		}
		x[i] = (y[i] - sum_y) / u[i][i];
	}

	cout << "x的值为：\n";
	for (int i =0; i <n ; i++)
	{
		cout <<"\tx"<<"["<<i<<"]=" <<x[i];
	}
}