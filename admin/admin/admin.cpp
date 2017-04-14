// admin.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <math.h>
#include <Windows.h>
#pragma warning(disable: 4996)
FILE *file;

//						Check if it's the same element

void check(double *x, double *y)
{
	double c;

	if ((*x) > (*y))
	{
		c = *x;
		*x = *y;
		*y = c;
	}
	else if ((*x) == (*y))
	{
		printf("You gave the same compartment! ");
		system("pause");
		exit(1);
	}
}


//Function									Sum of series

double sum(double x, double delta, double m, int* ele, int* mm)
{
	double suma = 0;
	double i = 1;
	double element = x;
	double sign = 1.0;
	int por = *ele;

	while (fabs(element) > delta && por < m)
	{

		suma += sign * element;
		element = element * (i * i* x * x) / ( (i + 1) * (i + 2));
		sign = (-1.0) * sign;
		por++;
		i += 2;
	}

	//				Verification Check if it has been reached precision

	if (fabs(element) > delta)
	{
		*mm = 0;
	}
	else
	{
		*mm = 1;
	}

	*ele = por;
	return suma;
}



int main()
{
	//						File to output

	file = fopen("wynik.txt", "w");

	double a, b, dx, result, ww, delta;
	int n, m;
	int method = 0;
	int ele = 0;

	//							Compartment

	printf("Give a i b (-1:1): \n");

	while (scanf("%lf %lf", &a, &b) != 2 || (a <= -1 || a >= 1 || b <= -1 || b >= 1))
	{
		printf("Give correct a and b (-1:1) : \n");
		while ((getchar()) != '\n');
	}
	while ((getchar()) != '\n');

	check(&a, &b);


	printf("Give amount of compartment <integer>: ");
	
	while (scanf("%d", &n) != 1 || n < 0)
	{
		printf("You didn't give amount of compartment!");
		while ((getchar()) != '\n');
	}
	while ((getchar()) != '\n');


	printf("Give precision np: (0.0001): ");
	
	while (scanf("%lf", &delta) != 1 || delta > 1 || delta < 0)
	{
		printf("Give correct precision!");
		while ((getchar()) != '\n');
	}
	while ((getchar()) != '\n');

	printf("Give number of the element sum of series to counting: ");
	
	while (scanf("%d", &m) != 1 || m < 0)
	{

		printf("Give correct number!");
		while ((getchar()) != '\n');

	}
	while ((getchar()) != '\n');

	//					Informations 

	printf("[%lf : %lf]\n", a, b);
	printf("Precision:  %lf\n", delta);
	printf("Number of compartment: %d\n", n);
	printf("Sum to: %d\n", m);


	dx = (b - a) / n;

	int z = 1213;
	
	
	for (double x = a; x < b + 0.5*dx; x += dx)
	{

		ele = 0;
		ww = sum(x, delta, m, &ele, &method);
		result = log(x + pow(x*x + 1, 1. / 2));

		//					Terminal output

		printf("\n%lf \t %12lf   \t %12lf \t %d \n", x, result, ww, ele);
		
		//					File output
		
		fprintf(file, "\n%lf \t %12lf   \t %12lf \t %d \n", x, result, ww, ele);


		// 				Verification Check if it has been reached precision

		if (method == 0)
		{
			printf("Zosta³a osiagnieta liczba do ktorej ma liczcy!\n\n");

			fprintf(file, "Zosta³a osiagnieta liczba do ktorej ma liczcy!\n");
		}
		else
		{
			printf("Zosta³a osiagnieta dokladnosc!\n\n");

			fprintf(file, "Zosta³a osiagnieta dokladnosc!\n");
		}

		method = 0;

	}
	
	fclose(file);
	system("pause");

	return 0;
}