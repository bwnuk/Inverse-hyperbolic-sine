// admin.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <math.h>
#include <Windows.h>
#pragma warning(disable: 4996)
FILE *plik;


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
		printf("Podales ten sam przedzial! ");
		system("pause");
		exit(1);
	}
}


double sum(double x, double delta, double m, int* ele, int* mm)
{
	double suma = 0;
	double i = 1;
	double wyraz = x;
	double znak = 1.0;
	int por = *ele;

	while (fabs(wyraz) > delta && por < m)
	{

		suma += znak*wyraz;
		wyraz = wyraz * (i * i* x * x) / ((i + 1)*(i + 2));
		znak = (-1.0) * znak;
		por++;
		i += 2;
	}

	//				Sprawdzanie czy zosta³a osi¹gnieta dok³adnoœæ

	if (fabs(wyraz) > delta)
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
	plik = fopen("wynik.txt", "w");

	double a, b, dx, wynik, ww, delta;
	int n, m;
	int metoda = 0;
	int ele = 0;

	printf("Podaj a i b (-1:1): \n");
	while (scanf("%lf %lf", &a, &b) != 2 || (a <= -1 || a >= 1 || b <= -1 || b >= 1))
	{
		printf("Podaj poprawne a i b (-1:1) : \n");
		while ((getchar()) != '\n');
	}

	while ((getchar()) != '\n');

	check(&a, &b);

	printf("Podaj ilosc przedzialow <calkowita>: ");
	while (scanf("%d", &n) != 1 || n < 0)
	{
		printf("Nie podales ilosci przedzialow!");
		while ((getchar()) != '\n');
	}
	while ((getchar()) != '\n');


	printf("Podaj dokladnosc np.(0.0001): ");
	while (scanf("%lf", &delta) != 1 || delta > 1 || delta < 0)
	{
		printf("Podaj poprawna dokladnosc!");
		while ((getchar()) != '\n');
	}
	while ((getchar()) != '\n');

	printf("Podaj do ktorej liczby ma liczyc: ");
	while (scanf("%d", &m) != 1 || m < 0)
	{
		printf("Podaj poprawna liczby!");
		while ((getchar()) != '\n');
	}
	while ((getchar()) != '\n');

	//					Wypisywanie 

	printf("[%lf : %lf]\n", a, b);
	printf("Dokladnosc:  %lf\n", delta);
	printf("Ilosc przedzialow: %d\n", n);
	printf("Ma zliczac do: %d\n", m);


	dx = (b - a) / n;

	int z = 1213;
	for (double x = a; x < b; x += dx)
	{
		ele = 0;
		ww = sum(x, delta, m, &ele, &metoda);
		wynik = log(x + pow(x*x + 1, 1. / 2));

		printf("\n%lf \t %12lf   \t %12lf \t %d \n", x, wynik, ww, ele);

		// 				Sprawdzanie czy zosta³a osi¹gnieta dok³adnoœc

		if (metoda == 0)
		{
			printf("Zosta³a osiagnieta liczba do ktorej ma liczcy!\n\n");
		}
		else
		{
			printf("Zosta³a osiagnieta dokladnosc!\n\n");
		}

		fprintf(plik, "\n%lf \t %12lf   \t %12lf \t %d \n", x, wynik, ww, ele);

		// 				Sprawdzanie czy zosta³a osi¹gnieta dok³adnoœc

		if (metoda == 0)
		{
			fprintf(plik, "Zosta³a osiagnieta liczba do ktorej ma liczcy!\n");
		}
		else
		{
			fprintf(plik, "Zosta³a osiagnieta dokladnosc!\n");
		}

		metoda = 0;
	}
	fclose(plik);
	system("pause");

	return 0;
}