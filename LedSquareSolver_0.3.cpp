#include <stdio.h>
#include <math.h>
#include <assert.h>
const int SS_INF_ROOTS = -1;

//----------------------------------------------

int solveSquare (double a, double  b, double c,
		double* x1, double* x2)
{
	assert (std::isfinite (a));
	assert (std::isfinite (b));
	assert (std::isfinite (c));

	assert (x1 != NULL);
	assert (x2 != NULL);
	assert (x1 != x2);

	if (a == 0 && b == 0)
	{
		if (c == 0) 
		{
			return SS_INF_ROOTS;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		double d = b * b  - 4 * a * c;

		if (d == 0)
		{
			*x1 = - b / 2 / a;
			return 1;
		}
	       	else if (d > 0)
		{
			*x1 = ( - b + sqrt(d)) / 2 / a;
			*x2 = - b / a - *x1;
			return 2;
		}
		else
		{
			return 0;
		}
	}
}

//----------------------------------------------

int main() 
{
	printf("# Программа для решения кв. уравнений\n"
			"# (c) Ledity, 2020\n\n");

	printf("# Решение уравнения вида ax^2 + bx + c = 0\n");
	printf("# Введите a, b, c: ");

	double a = 0, b = 0, c = 0;
	scanf("%lg %lg %lg", &a, &b, &c);
	printf("\n");

	double x1 = 0, x2 = 0;
	int nRoots = solveSquare(a, b, c, &x1, &x2);

	switch (nRoots)
	{
		case 0:
			printf ("Нет корней.\n");
			break;
		case 1:
			printf ("x = %lg\n", x1);
			break;
		case 2:
			printf  ("x1 = %lg,  x2 = %lg\n", x1, x2);
			break;
		case SS_INF_ROOTS:
			printf ("Корень - любое число.\n");
			break;
		default:
			printf ("main(): ERROR: nRoots = %d\n",	nRoots);
			return 1;

	}
}
