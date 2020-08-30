#include <stdio.h>
#include <math.h>
#include <assert.h>

//----------------------------------------------------

const int NO_ROOTS = 0;
const int ONE_ROOT = 1;
const int TWO_ROOTS = 2;
const int INF_ROOTS = -1;

const bool CHECK_X1_TRUE = true;
const bool CHECK_X2_TRUE = true;
const bool CHECK_X1_FALSE = false;
const bool CHECK_X2_FALSE = false;

const double PRECISION = 1E-30;

//----------------------------------------------------

void input (double* a, double* b, double* c, int* nAttempts);

void clean_stdin ();

int solve_square (double a, double  b, double c,
		double* x1, double* x2);

bool is_zero (double input);

//----------------------unittest----------------------

void unittest_SOLVE_SQUARE ();

void check_and_report_SOLVE_SQUARE (double aTest, double bTest, double cTest,
				   bool ifX1Check, bool ifX2Check,
				   int rightFuncOut, double rightX1, double rightX);

void unittest_IS_ZERO ();


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
	unittest_SOLVE_SQUARE ();
	unittest_IS_ZERO ();
	printf (" # LedSquareSolver\n"
	        " # Программа для решения кв. уравнений\n"
	        " # (c) Ledity, 2020\n\n"
		
		" # Решение уравнения вида ax^2 + bx + c = 0\n"
	        " # Введите a, b, c: ");

	double a = 666.13, b = 666.13, c = 666.13;
	int nAttempts = 0;

	input (&a, &b, &c, &nAttempts);

	double x1 = 0.0, x2 = 0.0;
	int nRoots = solve_square(a, b, c, &x1, &x2);

	if (nAttempts < 5) {
		switch (nRoots)
		{
			case NO_ROOTS:
				printf("\n Нет корней.");
				break;
			case 1:
				printf("\n x = %lg", x1);
				break;
			case 2:
				printf("\n x1 = %lg,  x2 = %lg", x1, x2);
				break;
			case INF_ROOTS:
				printf("\n Корень - любое число.");
				break;
			default:
				printf("\n #  main(): ERROR: nRoots = %d", nRoots);
				return 1;
		}
	}
	else
	{
		printf ("\n # Ошибка ввода. 5 неудачных вводов. Завершение программы");
	}
}

//-----------------------input------------------------

void input (double* a, double* b, double* c,
	    int* nAttempts)
{
	assert (a != NULL);
	assert (b != NULL);
	assert (c != NULL);
	assert (nAttempts != NULL);

	assert (a != b);
	assert (a != c);
	assert (b != c);

	int checkInput = scanf("%lg %lg %lg", a, b, c);
	
	*nAttempts = 0;
	
	if (checkInput < 3)
	{
		*nAttempts = 1;

		while (checkInput < 3 && *nAttempts < 5) 
		{

			printf ("\n # Неправильный ввод. Осталось попыток: %d."
				"\n # Пожалуйста, введите числовые значения: ",
				5 - *nAttempts);

			clean_stdin();	

			checkInput = scanf("%lg %lg %lg", a, b, c);

			*nAttempts = 1 + *nAttempts;
		}
	}
}

//--------------------clean_stdin---------------------

void clean_stdin ()
{
	int stdin_char = 1;
	while (stdin_char != '\n' && stdin_char != EOF)
	{
		stdin_char = getchar();
	}
}

//--------------------solve_square--------------------

/**
 * \brief This function solves square equations
 * \author Ledity
 * \version 0.1
 * \date Aug 2020
 *
 *	This function recieves a, b and c coefficents of square equation and links to x1 and x2 variables of another function (such as int main), that will be transformed into sqruare roots.
 *	The function itself outputs number of roots, where INFROOTS means infinite number of roots.
 *	Use &x1 and &x2 in input to let int solve_square сhange your x1 and x2 variables.
 */

int solve_square (double a, double  b, double c,
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
			return NO_ROOTS;
		}
	}
	else
	{
		double discr = b * b  - 4 * a * c;

		if (is_zero (discr))
		{
			*x1 = -b / 2 / a;
			return ONE_ROOT;
		}
       		else if (discr > 0 && !is_zero (discr))
		{
			*x1 = (-b + sqrt(discr)) / 2 / a;
			*x2 = -b / a - *x1;
			return TWO_ROOTS;
		}
		else
		{
			return NO_ROOTS;
		}
	}
}

//----------------------unittest----------------------

void unittest_SOLVE_SQUARE ()
{
	printf (" # Testing 'int solve_square ()'.\n");

	double aTest = 0.0, bTest = 0.0, cTest = 0.0;
	double x1Test = 0.0, x2Test = 0.0;

	// Test #1. a = 1, b = -2, c = 1.
	
	check_and_report_SOLVE_SQUARE (aTest = 1.0, bTest = -2.0, cTest = 1.0,
				       CHECK_X1_TRUE, CHECK_X2_FALSE,
				       ONE_ROOT, x1Test = 1.0, x2Test = 0.0);

	// Test #2. a = 1, b = 3, c = 2

	check_and_report_SOLVE_SQUARE (aTest = 1.0, bTest = 3.0, cTest = 2.0,
				       CHECK_X1_TRUE, CHECK_X2_TRUE,
				       TWO_ROOTS, x1Test = -1.0, x2Test = -2.0);
	
	// Test #3. a = 0, b = 0, c = 0

	check_and_report_SOLVE_SQUARE (aTest = 0.0, bTest = 0.0, cTest = 0.0,
				       CHECK_X1_FALSE, CHECK_X2_FALSE,
				       INF_ROOTS, x1Test = 0.0, x2Test = 0.0);

	// Test #4. a = 0, b = 0, c = 2

	check_and_report_SOLVE_SQUARE (aTest = 0.0, bTest = 0.0, cTest = 2.0,
				       CHECK_X1_FALSE, CHECK_X2_FALSE,
				       NO_ROOTS, x1Test = 0.0, x2Test = 0.0);

	// Test #5. a = 1, b = 2, c = 3

	check_and_report_SOLVE_SQUARE (aTest = 1.0, bTest = 2.0, cTest = 3.0,
				       CHECK_X1_FALSE, CHECK_X2_FALSE,
				       NO_ROOTS, x1Test = 0.0, x2Test = 0.0);

	printf("\n # Testing 'int solve_square ()' complete.\n\n");
}

//----------------------unittest----------------------

void check_and_report_SOLVE_SQUARE (double aTest, double bTest, double cTest,
				   bool ifX1Check, bool ifX2Check,
				   int rightFuncOut, double rightX1, double rightX2)
{
	double x1Test = 0.0, x2Test = 0.0;
	int    testFuncOut = 0.0;

	if (ifX1Check == true)
	{
		if (ifX2Check == true)
		{
			if ( !(testFuncOut = solve_square (aTest, bTest, cTest, &x1Test, &x2Test) == rightFuncOut && (x1Test == rightX1 && x2Test == rightX2 || x1Test == rightX2 && x2Test == rightX1)) )
			{
				printf ("\n # UNITTEST ERROR: 'int solve_square ()' test failed.\n"
					  "	input: a = %lg, b = %lg, c = %lg.\n"
					  "	output: x1 = %lg, x2 = %lg, function out = %lg.\n",
					aTest, bTest, cTest, x1Test, x2Test, testFuncOut);
			};
		}
		else
		{
			if ( !(testFuncOut = solve_square (aTest, bTest, cTest, &x1Test, &x2Test) == rightFuncOut
			    && x1Test == rightX1) )
			{
			printf ("\n # UNITTEST ERROR: 'int solve_square ()' test failed.\n"
				  "	input: a = %lg, b = %lg, c = %lg.\n"
				  "	output: x1 = %lg, function out = %lg.\n",
				aTest, bTest, cTest, x1Test, testFuncOut);
			};
		};
	}
	else
        {
		if ( !(testFuncOut = solve_square (aTest, bTest, cTest, &x1Test, &x2Test) == rightFuncOut) )
		{
			printf ("\n # UNITTEST ERROR: 'int solve_square ()' test failed.\n"
				  "	input: a = %lg, b = %lg, c = %lg\n"
				  "	output: x1 = %lg, x2 = %lg, function out = %lg.\n",
				aTest, bTest, cTest, testFuncOut);
		};	
	};
}

//----------------------is_zero-----------------------

bool is_zero (double value)
{
	return (abs (value) <= PRECISION);
}

//----------------------unittest----------------------

void unittest_IS_ZERO ()
{
	printf (" # Testing 'bool is_zero ()'.\n");

	bool testFuncOut = 0;
	double valueTest = 0.0;
	
	if ( testFuncOut = is_zero (valueTest = 0.0) != true)
	{
		printf ("\n # UNITTEST ERROR: 'bool is_zero ()' test failed.\n"
				  "	input: value = %lg\n"
				  "	output: function out %d\n",
				valueTest, testFuncOut);
	};

	if ( testFuncOut = is_zero (valueTest = 0.05) != false)
	{
		printf ("\n # UNITTEST ERROR: 'bool is_zero ()' test failed.\n"
				  "	input: value = %lg\n"
				  "	output: function out %d\n",
				valueTest, testFuncOut);
	};

	if ( testFuncOut = is_zero (valueTest = PRECISION) != true)
	{
		printf ("\n # UNITTEST ERROR: 'bool is_zero ()' test failed.\n"
				  "	input: value = %lg\n"
				  "	output: function out %d\n",
				valueTest, testFuncOut);
	};
	
	printf("\n # Testing 'bool is zero ()' completed.\n\n");
}
