//============================================================================
// Name        : Gerador.cpp
// Author      : Iasmim
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h> // para gerar numeros aleatorios
#include <time.h> // para gerar a 'random seed' baseada no tempo
#include <fstream>
using namespace std;

int main() {
	int i;
	cout<<"valor de N"<<endl;
	cin>>i;

	srand (time (NULL)); // Gera uma 'random seed' baseada no retorno da funcao time()
	double numero;
	 // Retorna um numero aleatorio entre 0 e 10

	ofstream fout("aleatorios.txt"); // Cria arquivo para gravação
	 //em modo texto
	for (int j = 0; j < i; j++) {
		numero = (double)rand ()/(numero + 1);
		fout << (float)numero<<"\n" ;
	}

}
