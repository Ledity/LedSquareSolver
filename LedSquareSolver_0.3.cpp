#include <stdio.h>
#include <math.h>
#include <assert.h>

//----------------------------------------------------

const int ZERO_ROOTS = 0;
const int INF_ROOTS = -1;

//----------------------------------------------------

void input (double* a, double* b, double* c);

void clean_stdin ();

int solveSquare (double a, double  b, double c,
		double* x1, double* x2);

//----------------------unittest----------------------

void unittest_solveSquare ();



//----------------------int main----------------------

/**
 * \brief This function is responsible for IO
 * \author Ledity
 * \vesion 0.2
 * \date Aug 2020
 *
 * 	This function outputs programme's name, purpose and asks the user to input a, b and c coefficents. Then it calles squareSolver. After that the function outputs roots.
 */ 

int main() 
{
	unittest_solveSquare ();
	printf (" # LedSquareSolver\n"
	        " # Программа для решения кв. уравнений\n"
	        " # (c) Ledity, 2020\n\n"
		
		" # Решение уравнения вида ax^2 + bx + c = 0\n"
	        " # Введите a, b, c: ");

	double a, b, c;
	input (&a, &b, &c);

	double x1 = 0, x2 = 0;
	int nRoots = solveSquare(a, b, c, &x1, &x2);

	switch (nRoots)
	{
		case ZERO_ROOTS:
			printf("\n Нет корней.\n");
			break;
		case 1:
			printf("\n x = %+lg\n", x1);
			break;
		case 2:
			printf("\n x1 = %+lg,  x2 = %+lg\n", x1, x2);
			break;
		case INF_ROOTS:
			printf("\n Корень - любое число.\n");
			break;
		default:
			printf("\n main(): ERROR: nRoots = %d\n", nRoots);
			return 1;
	}
}

//----------------------------------------------------

void input (double* a, double* b, double* c)
{
	assert (a != NULL);
	assert (b != NULL);
	assert (c != NULL);
	assert (a != b);
	assert (a != c);

	int checkInput = scanf("%lg %lg %lg", a, b, c);
	
	if (checkInput < 3)
	{
		while (checkInput < 3) 
		{
			printf ("\n # Неправильный ввод."
				"\n # Пожалуйста, введите числовые значения: ");

			clean_stdin();	

			checkInput = scanf("%lg %lg %lg", a, b, c);
		}
	}
}

//----------------------------------------------------

void clean_stdin ()
{
	int stdin_char = 1;
	while (stdin_char != '\n' && stdin_char != EOF)
	{
		stdin_char = getchar();
	}
}

//----------------------------------------------------

/**
 * \brief This function solves square equations
 * \author Ledity
 * \version 0.1
 * \date Aug 2020
 *
 *	This function recieves a, b and c coefficents of square equation and links to x1 and x2 variables of another function (such as int main), that will be transformed into sqruare roots.
 *	The function itself outputs number of roots, where INFROOTS means infinite number of roots.
 *	Use &x1 and &x2 in input to let int solveSquare сhange your x1 and x2 variables.
 */

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
			return INF_ROOTS;
		}
		else
		{
			return ZERO_ROOTS;
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
			return ZERO_ROOTS;
		}
	}
}

//----------------------unittest----------------------

void unittest_solveSquare ()
{
	printf (" # Testing 'int solveSquare ()'.\n");
	int nPassedTests = 0, nTests = 0;

	int test_a, test_b, test_c;

	double test_x1, test_x2;
	int    test_func_out;

	// Test #1. a = 1, b = -2, c = 1.
	
	nTests++;

	test_a = 1;
	test_b = -2;
	test_c = 1;

	if (test_func_out = solveSquare (test_a, test_b, test_c, &test_x1, &test_x2) == 1
	    && test_x1 ==1)
	{
		nPassedTests++;
	}
	else
	{
		printf ("\n # UNITTEST ERROR: 'int solveSquare ()' test #%d failed.\n"
			  "	input: a = %lg, b = %lg, c = %lg.\n"
			  "	output: x1 = %lg, function out = %lg.\n",
			nTests, test_a, test_b, test_c, test_x1, test_func_out);
	};

	// Test #2. a = 1, b = 3, c = 2
	
	nTests++;

	test_a = 1;
	test_b = 3;
	test_c = 2;

	if (test_func_out = solveSquare (test_a, test_b, test_c, &test_x1, &test_x2) == 2
	    && (test_x1 == -1 && test_x2 == -2 || test_x1 == -2 && test_x1 == -1))
	{
		nPassedTests++;
	}
	else
	{
		printf ("\n # UNITTEST ERROR: 'int solveSquare ()' test #%d failed.\n"
			  "	input: a = %lg, b = %lg, c = %lg.\n"
			  "	output: x1 = %lg, x2 = %lg, function out = %lg.\n",
			nTests, test_a, test_b, test_c, test_x1, test_x2, test_func_out);
	};
	
	// Test #3. a = 0, b = 0, c = 0
	
	nTests++;

	test_a = 0;
	test_b = 0;
	test_c = 0;

	if (test_func_out = solveSquare (test_a, test_b, test_c, &test_x1, &test_x2) == ZERO_ROOTS)
	{
		nPassedTests++;
	}
	else
	{
		printf ("\n # UNITTEST ERROR: 'int solveSquare ()' test #%d failed.\n"
			  "	input: a = %lg, b = %lg, c = %lg.\n"
			  "	output: function out = %lg.\n",
			nTests, test_a, test_b, test_c, test_func_out);
	};

	// Test #4. a = 0, b = 0, c = 2
	
	nTests++;

	test_a = 0;
	test_b = 0;
	test_c = 2;

	if (test_func_out = solveSquare (test_a, test_b, test_c, &test_x1, &test_x2) == INF_ROOTS)
	{
		nPassedTests++;
	}
	else
	{
		printf ("\n # UNITTEST ERROR: 'int solveSquare ()' test #%d failed.\n"
			  "	input: a = %lg, b = %lg, c = %lg\n"
			  "	output: x1 = %lg, x2 = %lg, function out = %lg.\n",
			nTests, test_a, test_b, test_c, test_func_out);
	};

	// Test #5. a = 1, b = 2, c = 3
	
	nTests++;

	test_a = 1;
	test_b = 2;
	test_c = 3;

	if (test_func_out = solveSquare (test_a, test_b, test_c, &test_x1, &test_x2) == ZERO_ROOTS)
	{
		nPassedTests++;
	}
	else
	{
		printf ("\n # UNITTEST ERROR: 'int solveSquare ()' test #%d failed.\n"
			  "	input: a = %lg, b = %lg, c = %lg\n"
			  "	output: function out = %lg\n",
			nTests, test_a, test_b, test_c, test_func_out);
	};
	printf("\n # Testing 'int solveSquare ()' complete. %d successuful, %d failed.\n\n", nPassedTests, nTests-nPassedTests);
}
