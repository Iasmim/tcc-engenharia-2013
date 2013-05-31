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

	double *result = new double[ N ];

	double *tmpresult = new double[ N ];
	int *permuta = new int[ N ];
	int passo = N/2;
	int indicebase;
	int indice;
	double pi2_N = M_PI;

	permuta[0] = 0;
	permuta[1] = 1;
	for (int k = 2; k < N; k += k )
	{
		for(int j = 0; j < k; j++)
		{
			permuta[j] += permuta[j];
			permuta[ j + k ] = permuta[j] + 1;
		}
	}
	for (int j = 0; j < N; j += 2) //passo1
	{
		tmpresult[ j ] = (dados[ permuta[ j ] ] + dados[ permuta[ j + 1 ]
		                                                          ]) ;
		tmpresult[ j + 1 ] = (dados[ permuta[ j ] ] - dados[ permuta[ j +
		                                                              1 ] ]);
	}
	for (int k = 2; k < N; k += k )
	{
		passo = passo * 0.5;
		pi2_N = pi2_N * 0.5;
		indicebase = 0;

		for (int m = 0; m < passo; m++)
		{
			result[ indicebase ] = tmpresult[ indicebase ]
			                                  + tmpresult[ indicebase + k ];
			result[ indicebase + k ] = tmpresult[ indicebase ]
			                                      - tmpresult[ indicebase + k ];
			for (int j = 1; j < k; j++)
			{

				indice = indicebase + j;
				result[ indice ] = tmpresult[ indice ]
				                              + ( tmpresult[ indice + k ] *
				                            		  cos( pi2_N * j ) )
				                            		  + ( tmpresult[ indicebase + k + k - j ] *
				                            				  sin( pi2_N * j ) );

				result[ indice + k ] = tmpresult[ indice ]
				                                  - ( tmpresult[ indice + k ] *
				                                		  cos( pi2_N * j ) )
				                                		  - ( tmpresult[ indicebase + k + k - j ] *
				                                				  sin( pi2_N * j ) );
			}
			indicebase += k + k;
		}
		for(int j = 0; j < N; j++)
			tmpresult[ j ] = result[ j ];
	}

	gettimeofday(&Fim, NULL);                                                    /* Coleta a data de fim do processo*/
		/* Calcula o espaço de tempo */

		Segundos = Fim.tv_sec - Inicio.tv_sec;
		Microssegundos = Fim.tv_usec - Inicio.tv_usec;


		Milissegundos = Segundos * 1000 + Microssegundos / 1000;                    /* Transforma segundos e microssegundos em milissegundos */


	for(int j = 0; j < N; j++)
	{
		result[ j ] = tmpresult[ j ];
		cout << result[ j ] << endl;
	}

	cout<<"Inicio:"<<Inicio.tv_sec <<" Fim:"<< Fim.tv_sec<<endl;
	cout << "\nO programa demorou " << Milissegundos << " milissegundos \n"<< endl;



	delete tmpresult;
	delete permuta;

	return 0;
}
