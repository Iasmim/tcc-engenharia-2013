#include <iostream>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <fstream>
#include <string>
using namespace std;
#define PI 3.14159265359
#define MAXPOW 24

struct complex
{
    double r;
    double i;
};

int pow_2[MAXPOW];
int pow_4[MAXPOW];

void twiddle(struct complex *W, int N, double stuff)
{
    W->r=cos(stuff*2.0*PI/(double)N);
    W->i=-sin(stuff*2.0*PI/(double)N);
}

void bit_r4_reorder(struct complex *W, int N)
{
    int bits, i, j, k;
    double tempr, tempi;

    for (i=0; i<MAXPOW; i++)
	if (pow_2[i]==N) bits=i;

    for (i=0; i<N; i++)
    {
	j=0;
	for (k=0; k<bits; k+=2)
	{
	    if (i&pow_2[k]) j+=pow_2[bits-k-2];
	    if (i&pow_2[k+1]) j+=pow_2[bits-k-1];
	}

	if (j>i)
	{
	    tempr=W[i].r;
	    tempi=W[i].i;
	    W[i].r=W[j].r;
	    W[i].i=W[j].i;
	    W[j].r=tempr;
	    W[j].i=tempi;
	}
    }
}

/** RADIX-4 FFT ALGORITHM */
void radix4(struct complex *x, int N)
{
    int    n2, k1, N1, N2;
    struct complex W, bfly[4];

    N1=4;
    N2=N/4;


    for (n2=0; n2<N2; n2++)
    {

	bfly[0].r = (x[n2].r + x[N2 + n2].r + x[2*N2+n2].r + x[3*N2+n2].r);
	bfly[0].i = (x[n2].i + x[N2 + n2].i + x[2*N2+n2].i + x[3*N2+n2].i);

	bfly[1].r = (x[n2].r + x[N2 + n2].i - x[2*N2+n2].r - x[3*N2+n2].i);
	bfly[1].i = (x[n2].i - x[N2 + n2].r - x[2*N2+n2].i + x[3*N2+n2].r);

	bfly[2].r = (x[n2].r - x[N2 + n2].r + x[2*N2+n2].r - x[3*N2+n2].r);
	bfly[2].i = (x[n2].i - x[N2 + n2].i + x[2*N2+n2].i - x[3*N2+n2].i);

	bfly[3].r = (x[n2].r - x[N2 + n2].i - x[2*N2+n2].r + x[3*N2+n2].i);
	bfly[3].i = (x[n2].i + x[N2 + n2].r - x[2*N2+n2].i - x[3*N2+n2].r);


	for (k1=0; k1<N1; k1++)
	{
	    twiddle(&W, N, (double)k1*(double)n2);
	    x[n2 + N2*k1].r = bfly[k1].r*W.r - bfly[k1].i*W.i;
	    x[n2 + N2*k1].i = bfly[k1].i*W.r + bfly[k1].r*W.i;
	}
    }
    if (N2!=1)
	for (k1=0; k1<N1; k1++)
	{
	    radix4(&x[N2*k1], N2);
	}
}


int main(int argc, char *argv[])
{
    FILE   *infile;
    int    N, radix, numsamp;
    int    i;
    struct complex data[atoi(argv[2])];
    double freq, phase, fs, A;
    int    dotime;
    struct timeval start, end;
    long   totaltime;
    double Segundos, Milissegundos, Microssegundos;

#ifdef GEN

    sscanf(argv[1], "%f", &A);
    sscanf(argv[2], "%f", &freq);
    sscanf(argv[3], "%f", &phase);
    sscanf(argv[4], "%f", &fs);
#endif
#ifndef GEN
    if ((infile=fopen(argv[1], "r"))==NULL)
    {
	printf("Error reading input sequence file: %s\n", argv[1]);
	exit(1);
    }

    sscanf(argv[2], "%d", &N);
    sscanf(argv[3], "%d", &radix);
    dotime=0;
#endif


    pow_2[0]=1;
    for (i=1; i<MAXPOW; i++)
	pow_2[i]=pow_2[i-1]*2;
    pow_4[0]=1;
    for (i=1; i<MAXPOW; i++)
	pow_4[i]=pow_4[i-1]*4;


#ifdef GEN
    for (i=0; i<N; i++)
    {
	data[i].r=0.0;
	data[i].i=0.0;
    }
    for (i=0; i<numsamp; i++)
	data[i].r=A*cos(2.0*PI*freq*i/fs - phase*PI/180);
#endif
#ifndef GEN

    string line;
    	int in = 0;

    	ifstream myfile ("aleatorios.txt"); // ifstream = padrão ios:in
    	if (myfile.is_open())
    	{
    		while (! myfile.eof() ) //enquanto end of file for false continua
    		{
    			getline (myfile,line); // como foi aberto em modo texto(padrão)
    			//e não binário(ios::bin) pega cada linha
    			data[in].r = (double)atof(line.c_str());///strtod(line.c_str(),NULL);
    			data[in].i=0.0;
    			in++;
    		}
    	}

#endif

    gettimeofday(&start, NULL);
    if (radix==4) radix4(data, N);
    gettimeofday(&end, NULL);

    if (radix==4) bit_r4_reorder(data, N);


	/* Calcula o espaço de tempo */

	Segundos = end.tv_sec - start.tv_sec;
	Microssegundos = end.tv_usec - start.tv_usec;


	Milissegundos = Segundos * 1000 + Microssegundos / 1000;

    if (!dotime)
	for (i=0; i<N; i++)
		 printf("%f %f\n", sqrt(data[i].r*data[i].r) ,
			    		sqrt(data[i].i*data[i].i));
#ifndef GEN
    fclose(infile);
    myfile.close();
#endif
    cout << "\nO programa demorou " << Milissegundos << " milissegundos \n";

    return 0;
}
