//============================================================================
// Name        : DFT.cpp
// Author      : Iasmim
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
/*Considerando que Transformada de Fourier seja:
*                N
   X(k) =       sum  x(n)*exp(-j*2*pi*(k-1)*(n-1)/N), 1 <= k <= N.
                 n=1
*
* */
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
using namespace std;

int main() {
	        struct timeval Inicio, Fim;
	        double Segundos, Milissegundos, Microssegundos;
		    int N;
			cout << "Entre com o valor de N" << endl;                                 /* Entra aqui com N*/
			cin >> N;

            srand(time(NULL));
		    double *x = new double[ N ];
		    cout << "Entradas :"<<endl;
			for (int i = 0; i < N ; ++i) {
		         x[i] = rand()/100;
		         printf("%f ,",(float)x[i]);
			}


			    gettimeofday(&Inicio, NULL);                                                  /* Coleta a data de inicio do processo */


			    double *Xreal = new double [ N ];                                               /* Inicia a transformada */
			    double *Ximag = new double [ N ];

			    double Fpi = ( M_PI + M_PI );
			    double pi_N;

			    for ( int n = 0; n < N; n++ )
			    {
			        Xreal[n] = 0;
			        Ximag[n] = 0;
			        pi_N = n * Fpi;
			        for ( int k = 0; k < N; k++ )
			        {
			            Xreal[ n ]  += x[ k ] * cos( (pi_N * k)/N );
			            Ximag[ n ]  -= x[ k ] * sin( (pi_N * k)/N );
			        }

			    }

			       gettimeofday(&Fim, NULL);                                                    /* Coleta a data de fim do processo*/
			       	   	   	   	   	   	   	   	   	   	   	   	                                /* Calcula o espaço de tempo */

			    Segundos = Fim.tv_sec - Inicio.tv_sec;
			    Microssegundos = Fim.tv_usec - Inicio.tv_usec;


			    Milissegundos = Segundos * 1000 + Microssegundos / 1000;                    /* Transforma segundos e microssegundos em milissegundos */


			    cout << "\nO programa demorou " << Milissegundos << " milissegundos \n"<< endl;

			    cout<< "Saídas :" << endl;
			    for (int var = 0; var < N; ++var) {
			    	printf(" %f  %f j \n",(float)Xreal[ var ],(float)Ximag[ var ]);                  /* Imprime as saídas*/

				}
			    getchar();
          return 0;
}
