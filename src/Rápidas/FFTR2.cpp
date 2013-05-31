#include <iostream>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char **argv) {
	struct timeval Inicio, Fim;
	double Segundos, Milissegundos, Microssegundos;
	int N = atoi(argv[1]);
	double *dados =new double [N];

	cout << "Entradas:"<<N<<endl;

	string line;
	int i = 0;

	ifstream myfile ("aleatorios.txt"); // ifstream = padrão ios:in
	if (myfile.is_open())
	{
		while (! myfile.eof() ) //enquanto end of file for false continua
		{
			getline (myfile,line); // como foi aberto em modo texto(padrão)
			//e não binário(ios::bin) pega cada linha
			dados[i] = (double)atof(line.c_str());///strtod(line.c_str(),NULL);
			printf("%f\n",(float)dados[i]);
			i++;
		}
		myfile.close();
	}

	else cout << "Erro ao abrir arquivo!";


	gettimeofday(&Inicio, NULL);

	double *real = new double[ N ];
	double *imag = new double[ N ];

	double *tmpreal = new double[ N ];
	double *tmpimg = new double[ N ];
	int *pot = new int[ N ];
	int indicebase;
	int indice;
	double a,b,c,d;
	double pi2_N = (M_PI + M_PI) / N;
	int N2 = N/2;


	int passo = N2;

	for (int j = 0; j < N; j++)
	{
		pot[ j ] = 0;
		tmpreal[ j ] = dados[ j ];
		tmpimg[ j ] = 0;
	}

	for (int k = 1; k < N; k += k )
	{
		for (int j = 0; j < N2; j++)
			pot[ j ] = pot[ j + j ];
		for (int j = 0; j < N2; j++)
			pot[ N2 + j ] = pot[ j ] + passo;
		indicebase = 0;
		for (int m = 0; m < k; m++)
		{
			for (int j = 0; j < passo; j++)
			{
				indice = indicebase + j;

				a = tmpreal[ indice + passo ];
				b = tmpimg[ indice + passo ];
				c = cos(pi2_N * pot[ indice ]);
				d = -sin(pi2_N * pot[ indice ]);
				real[ indice ] = tmpreal[ indice ] + (a*c - b*d);
				imag[ indice ] = tmpimg[ indice ] + (b*c + a*d);

				c = cos(pi2_N * pot[ indice + passo ]);
				d = -sin(pi2_N * pot[ indice + passo ]);

				real[ indice + passo ] = tmpreal[ indice ] + (a*c - b*d);
				imag[ indice + passo ] = tmpimg[ indice ] + (b*c + a*d);
			}
			indicebase += passo + passo;
		}
		for(int j = 0; j < N; j++)
		{
			tmpreal[ j ] = real[ j ];
			tmpimg[ j ] = imag[ j ];
		}
		passo = passo * 0.5;
	}
	for(int j = 0; j < N; j++)
	{
		real[ j ] = tmpreal[ pot[ j ] ];
		imag[ j ] = tmpimg[ pot[ j ] ];
	}
	gettimeofday(&Fim, NULL);                                                    /* Coleta a data de fim do processo*/
	/* Calcula o espaço de tempo */

	Segundos = Fim.tv_sec - Inicio.tv_sec;
	Microssegundos = Fim.tv_usec - Inicio.tv_usec;


	Milissegundos = Segundos * 1000 + Microssegundos / 1000;                    /* Transforma segundos e microssegundos em milissegundos */

	delete tmpreal;
	delete tmpimg;
	delete pot;
	for(int j = 0; j < N; j++)
	{
		cout << real[ j ] <<"\t"<<"\t"; // prints !!!Hello World!!!
		cout << imag[ j ] <<"\t"<< "\n"; // prints !!!Hello World!!!
	}

	cout<<"Inicio:"<<Inicio.tv_sec <<" Fim:"<< Fim.tv_sec<<endl;
	cout << "\nO programa demorou " << Milissegundos << " milissegundos \n"<< endl;



	return 0;
}
