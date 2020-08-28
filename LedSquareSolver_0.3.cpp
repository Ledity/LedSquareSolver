#include <stdio.h>
#include <math.h>
#include <assert.h>
const int SS_INF_ROOTS = -1;

void input (double* a, double* b, double* c);

int solveSquare(double a, double  b, double c,
		double* x1, double* x2);



/**
 * \brief This function is responsible for IO
 * \author Ledity
 * \vesion 0.2
 * \date Aug 2020
 *
 * This function outputs programme's name, purpose and asks the user to input a, b and c coefficents. Then it calles squareSolver. After that the function outputs roots.
 */ 

int main() 
{
	printf("# LedSquareSolver\n"
			"# Программа для решения кв. уравнений\n"
			"# (c) Ledity, 2020\n\n");

	printf("# Решение уравнения вида ax^2 + bx + c = 0\n"
			"# Введите a, b, c: ");

	double a = -1.7E308, b = -1.7E308, c = -1.7E308;
	input(&a, &b, &c);

	double x1 = 0, x2 = 0;
	int nRoots = solveSquare(a, b, c, &x1, &x2);

	switch (nRoots)
	{
		case 0:
			printf("\nНет корней.\n");
			break;
		case 1:
			printf("\nx = %+lg\n", x1);
			break;
		case 2:
			printf("\nx1 = %+lg,  x2 = %+lg\n", x1, x2);
			break;
		case SS_INF_ROOTS:
			printf("\nКорень - любое число.\n");
			break;
		default:
			printf("\nmain(): ERROR: nRoots = %d\n",	nRoots);
			return 1;
	}
}

void input (double* a, double* b, double* c)
{
	assert(a != NULL);
	assert(b != NULL);
	assert(c != NULL);
	assert(a != b);
	assert(a != c);
	scanf("%lg %lg %lg", &*a, &*b, &*c);
	if (*a == -1.7E308 && *b == -1.7E308 && *c == -1.7E308)
	{
		while (*a == -1.7E308 && *b == -1.7E308 && *c == -1.7E308)
		{
			printf("\n# Ошибка ввода. Введите снова ");
			scanf("%lg %lg %lg", &*a, &*b, &*c);
		}
	}
}

/**
 * \brief This function solves square equations
 * \author Ledity
 * \version 0.1
 * \date Aug 2020
 *
 *	This function recieves a, b and c coefficents of square equation and links to x1 and x2 variables of another function (such as int main), that will be transformed into sqruare roots.
 *	The function itself outputs number of roots, where SS_INFROOTS means infinite number of roots.
 *	Use &x1 and &x2 in input to let int solveSquare сhange your x1 and x2 variables.
 */

int solveSquare(double a, double  b, double c,
		double* x1, double* x2)
{
	assert(std::isfinite (a));
	assert(std::isfinite (b));
	assert(std::isfinite (c));

	assert(x1 != NULL);
	assert(x2 != NULL);
	assert(x1 != x2);

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
		double discr = b * b  - 4 * a * c;

		if (discr == 0)
		{
			*x1 = -b / 2 / a;
			return 1;
		}
       		else if (discr > 0)
		{
			*x1 = (-b + sqrt(discr)) / 2 / a;
			*x2 = -b / a - *x1;
			return 2;
		}
		else
		{
			return 0;
		}
	}
	}





