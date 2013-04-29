
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
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char **argv) {
	        struct timeval Inicio, Fim;
	        double Segundos, Milissegundos, Microssegundos;
		    int N = atoi(argv[1]);
		    double *x = new double[ N ];
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
		   	      x[i] = (double)atof(line.c_str());///strtod(line.c_str(),NULL);
		   	      printf("%f\n",(float)x[i]);
		   	      i++;
		   	    }
		   	    myfile.close();
		   	  }

		   	  else cout << "Erro ao abrir arquivo!";


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
			            Xreal[ n ]  += x[ k ] *( cos( (pi_N * k)/N )+ sin((pi_N * k)/N ));
			        }

			    }

			       gettimeofday(&Fim, NULL);                                                    /* Coleta a data de fim do processo*/
			       	   	   	   	   	   	   	   	   	   	   	   	                                /* Calcula o espaço de tempo */

			    Segundos = Fim.tv_sec - Inicio.tv_sec;
			    Microssegundos = Fim.tv_usec - Inicio.tv_usec;


			    Milissegundos = Segundos * 1000 + Microssegundos / 1000;                    /* Transforma segundos e microssegundos em milissegundos */



			    cout<< "Saídas :" << endl;
			    for (int var = 0; var < N; ++var) {
			    	printf(" %f ",(float)Xreal[ var ]);                  /* Imprime as saídas*/

				}
			    cout<<"Inicio:"<<Inicio.tv_sec <<" Fim:"<< Fim.tv_sec<<endl;
			    cout << "\nO programa demorou " << Milissegundos << " milissegundos \n"<< endl;

			  return  system("pause");

}
