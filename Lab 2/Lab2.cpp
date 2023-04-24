/*
1. Implementați algoritmul lui Moore pentru un graf orientat neponderat (algoritm bazat pe Breath-first search, vezi cursul 2). 
Datele sunt citete din fisierul graf.txt. Primul rând din graf.txt conține numărul vârfurilor, iar următoarele rânduri conțin muchiile grafului. 
Programul trebuie să afiseze lanțul cel mai scurt dintr-un vârf (vârful sursa poate fi citit de la tastatura).

2. Sa se determine închiderea transitivă a unui graf orientat. 
(Închiderea tranzitivă poate fi reprezentată ca matricea care descrie, pentru fiecare vârf în parte, care sunt vârfurile accesibile din acest vârf. 
Matricea inchiderii tranzitive arată unde se poate ajunge din fiecare vârf.) ex. figura inchidere_tranzitiva.png - pentru graful de sus se construieste 
matricea de jos care arata inchiderea tranzitiva.

3. Să se scrie un program care găsește o soluție pentru unul din următoarele labirinturi: labirint_1.txt, labirint_2.txt, labirint_cuvinte.txt. 
Pentru labirintul 1 si 2 punctul de pornire este indicat de litera S și punctul de oprire este indicat de litera F, spre deosebire de labirintul 1 și 2, labirintul 3 nu are o soluție unică.

4. Pentru un graf dat să se afișeze pe ecran vârfurile descoperite de algoritmul BFS și distanța față de vârful sursă (arborele descoperit).

5. Pentru un graf dat să se afișeze pe ecran vârfurile descoperite de apelul recursiv al procedurii DFS_VISIT(G, u) (apadurea descoperită de DFS).
*/

#include <iostream>
#include <fstream>
#include <string>
#define inf 0x3f3f3f

void Tranzitiva(int t[][101], int n)
{
	int k, i, j;
	for (k = 1; k <= n; k++)
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				if (t[i][j] == 0)
					t[i][j] = (t[i][k] && t[k][j]);
}

void Moore( int ma[][101], int n, int s, int d)
{
	int l[101] = {}, p[101] = {}, i, x;
	l[s] = 0;
	for (i = 1; i < s; i++)
		l[i] = inf;
	for (i = s+1; i <= n; i++)
		l[i] = inf;
	int Q[101] = {}, sq = 0, dq = 1;
	Q[0] = s;
	while (sq < dq)
	{
		x = Q[sq];
		for (i = 1; i <= n; i++)
			if (ma[x][i] && l[i] == inf)
			{
				p[i] = x;
				l[i] = l[x] + 1;
				Q[dq++] = i;
			}
		sq++;
	}
	std::cout << "Distanta minima de la varful " << s << " la varful " << d << " este " << l[d] << '\n';
	std::cout << "Drumul de lungime minima este: ";
	i = d;
	x = l[d];
	while (i != s)
	{
		Q[x] = i;
		i = p[i];
		x--;
	}
	Q[0] = s;
	for (i = 0; i <= l[d]; i++)
		std::cout << Q[i] << " ";
	std::cout << '\n';
}

void BFS( int ma[][101], int n, int s )
{
	int sq, dq, k, Q[101] = {}, viz[101] = {};
	sq = dq = 1;
	Q[1] = s;
	viz[s] = 1;
	while (sq <= dq)
	{
		for (k = 1; k <= n; k++)
			if (ma[Q[sq]][k] == 1 && viz[k] == 0)
			{
				Q[++dq] = k;
				viz[k] = 1;
			}
		sq++;
	}
	for (k = 1; k <= dq; k++)
		std::cout << Q[k] << " ";
}

void DFS( int ma[][101], int n, int s, int v[] )
{
	int i;
	v[s] = 1;
	std::cout << s << " ";
	for (i = 1; i <= n; i++)
		if (ma[s][i] == 1 && v[i] == 0)
			DFS( ma, n, i, v );
}

struct position {
	int l, c;
};

int v[] = { -1, 0, 1, 0 };
int o[] = { 0, -1, 0, 1 };

void fillLabirinth( int x, int y, int m, int n, char labirinth[][701], int path[][701] )
{
	int _x, _y;
	labirinth[y][x] = 'X';
	for ( int k = 0; k < 4; k++ )
	{
		_x = x + o[k];
		_y = y + v[k];
		if ( _x >= 0 && _x < n && _y >= 0 && _y < m && path[_y][_x] == path[y][x] - 1 )
		{
			fillLabirinth( _x, _y, m, n, labirinth, path );
			return;
		}
	}
}

void Lee( std::string file, std::string result )
{
	position Q[10001], posStart, posFinish;
	char labirinth[101][701];
	int path[101][701] = {};
	int sq = 0, dq = 1, k = 0, n, m;
	std::ifstream fin( file );
	std::ofstream fout( result );
	while (fin.getline( labirinth[k], sizeof( labirinth[k] ) ))
		k++;
	n = k;	// linii
	m = strlen( labirinth[0] ); // coloane
	// Cautam pozitiile de inceput si final
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if (labirinth[i][j] == 'S')
			{
				posStart.c = j;
				posStart.l = i;
			}
			else if (labirinth[i][j] == 'F')
			{
				posFinish.c = j;
				posFinish.l = i;
			}
		}
	// Algoritmul lui Lee
	Q[0] = posStart;
	labirinth[posStart.l][posStart.c] = 'X';
	path[posStart.l][posStart.c] = 1;
	while (sq < dq)
	{
		position current = Q[sq++];
		position next;
		for (k = 0; k < 4; k++)
		{
			next.l = current.l + v[k];
			next.c = current.c + o[k];
			if (labirinth[next.l][next.c] != '1' && path[next.l][next.c] == 0 && next.c >= 0 && next.l >= 0 && next.c < m && next.l < n)
			{
				path[next.l][next.c] = path[current.l][current.c] + 1;
				Q[dq++] = next;
			}
		}
	}
	fillLabirinth( posFinish.c, posFinish.l, n, m, labirinth, path );
	for ( int i = 0; i < n; i++ )
		fout << labirinth[i] << '\n';
	fin.close();
	fout.close();
}

int main()
{
	int n, m, x, y, s, d, ma[101][101] = {}, mt[101][101] = {}, v[101] = {};
	// Citire din fisier
	std::ifstream fin( "graf.txt" );
	fin >> n; // numarul de noduri
	m = 0; // numarul de muchii
	while (fin >> x >> y)
	{
		// Construim matricea de adiacenta
		ma[x][y] = 1;
		mt[x][y] = 1;
		m++;
	}
	fin.close();
	Tranzitiva( mt, n );
	// Afisam matricea inchiderii tranzitive
	std::cout << "Matricea inchiderii trazitive este:\n";
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			std::cout << mt[i][j] << " ";
		std::cout << '\n';
	}
	// Moore
	std::cout << "Alegeti doua varfuri pentru care doriti distanta minima (Moore): ";
	std::cin >> s >> d;
	Moore( ma, n, s, d );
	// BFS + DFS
	std::cout << "Alegeti un varf pentru a afisa varfurile vizitate cu BFS si DFS: ";
	std::cin >> s;
	std::cout << "BFS: ";
	BFS( ma, n, s );
	std::cout << '\n';
	std::cout << "DFS: ";
	DFS(ma, n, s, v);
	std::cout << '\n';
	// LEE
	Lee( "labirint1.txt", "sol_labirint1.txt" );
	Lee( "labirint2.txt", "sol_labirint2.txt" );
	Lee( "labirint_cuvinte.txt", "sol_labirint_cuvinte.txt" );
	return 0;
}
