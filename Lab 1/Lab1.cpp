/*1. Fie un fisier ce contine un graf neorientat reprezentat sub forma: prima linie contine numarul nodurilor iar urmatoarele 
randuri muchiile grafului. Sa se scrie un program in C/C++ care sa citeasca fisierul si sa reprezinte/stocheze un graf folosind 
matricea de adiacenta, lista de adiacenta si matricea de incidenta. Sa se converteasca un graf dintr-o forma de reprezentare in alta.

2. Fie un graf reprezentat sub o anumita forma (graful este citit dintr-un fisier). Sa se rezolve:
a. sa se determine nodurile izolate dintr-un graf.
b. sa se determine daca graful este regular.
c. pentru un graf reprezentat cu matricea de adiacenta sa se determine matricea distantelor.
d. pentru un graf reprezentat cu o matrice de adiacenta sa se determine daca este conex.
*/

#include <iostream>
#include <fstream>
#define inf 0x3f3f3f3f

void FloydWarshall(int md[][101], int n)
{
	int i, j, k;
	for ( k = 1; k <= n; k++ )
		for ( i = 1; i <= n; i++ )
			for ( j = 1; j <= n; j++ )
				if ( md[i][k] != inf && md[k][j] != inf )
					if ( md[i][j] > md[i][k] + md[k][j] )
						md[i][j] = md[i][k] + md[k][j];
}

int main()
{
	int n, m, x, y, ma[101][101] = {}, mi[101][101] = {}, la[101][101] = {};
	// Citire din fisier
	std::ifstream fin( "in.txt" );
	fin >> n; // numarul de noduri
	m = 0; // numarul de muchii
	while ( fin >> x >> y )
	{
		// Pe linia 0 din matricea de adiacenta punem gradele nodurilor
		ma[0][x]++;
		ma[0][y]++;
		// Construim matricea de adiacenta
		ma[x][y] = 1;
		ma[y][x] = 1;
	}
	fin.close();
	// Construim matricea de incidenta
	for ( int i = 1; i <= n; i++ )
		for ( int j = 1; j <= i; j++ )
			if ( ma[i][j] )
			{
				m++;
				mi[i][m] = 1;
				mi[j][m] = 1;
			}
	// Construim lista de adiacenta
	for ( int i = 0; i <= n; i++ )
		for ( int j = 1; j <= i; j++ )
			if ( ma[i][j] )
			{
				la[i][0]++;
				la[i][la[i][0]] = j;
				la[j][0]++;
				la[j][la[j][0]] = i;
			}
	// Afisare matrice de adiacenta
	std::cout << "Matricea de adiacenta este:\n";
	for ( int i = 1; i <= n; i++ )
	{
		for ( int j = 1; j <= n; j++ )
			std::cout << ma[i][j] << " ";
		std::cout << '\n';
	}
	// Afisare matrice de incidenta
	std::cout << "Matricea de incidenta este:\n";
	for ( int i = 1; i <= n; i++ )
	{
		for ( int j = 1; j <= m; j++ )
			std::cout << mi[i][j] << " ";
		std::cout << '\n';
	}
	// Afisare lista de adiacenta
	std::cout << "Lista de adiacenta este:\n";
	for ( int i = 1; i <= n; i++ )
	{
		std::cout << i << ": ";
		for ( int j = 1; j <= la[i][0]; j++ )
			std::cout << la[i][j] << " ";
		std::cout << '\n';
	}
	// Afisare noduri izolate
	bool izolate = false;
	std::cout << "Nodurile izolate sunt: ";
	for ( int i = 1; i <= n; i++ )
	{
		bool izolat = true;
		for ( int j = 1; j <= n && izolat; j++ )
			if ( ma[i][j] )
				izolat = false;
		if ( izolat )
		{
			std::cout << i << " ";
			izolate = true;
		}
	}
	if ( !izolate )
		std::cout << "niciunul";
	std::cout << '\n';
	// Determinare graf regular sau nu
	bool regular = true;
	for ( int i = 1; i < n && regular; i++ )
		if ( ma[0][i] != ma[0][i + 1] )
			regular = false;
	if ( regular )
		std::cout << "Graful este regular\n";
	else
		std::cout << "Graful NU este regular\n";
	// Afisare matricea distantelor
	int md[101][101];
	for ( int i = 1; i <= n; i++ )
		for ( int j = 1; j <= n; j++ )
			if ( i == j )
				md[i][j] = 0;
			else if ( ma[i][j] )
				md[i][j] = 1;
			else 
				md[i][j] = inf;
	FloydWarshall( md, n );
	std::cout << "Matricea distantelor este:\n";
	for ( int i = 1; i <= n; i++ )
	{
		for ( int j = 1; j <= n; j++ )
			if ( md[i][j] == inf )
				std::cout << "inf ";
			else
				std::cout << md[i][j] << " ";
		std::cout << '\n';
	}
	// Determinare graf conex
	bool conex = true;
	for ( int i = 1; i <= n && conex; i++ )
		for ( int j = i + 1; j <= n && conex; j++ )
			if ( md[i][j] == inf )
				conex = false;
	if ( conex )
		std::cout << "Graful este conex\n";
	else
		std::cout << "Graful NU este conex\n";
	return 0;
}
