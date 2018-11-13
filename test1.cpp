#include <iostream>
#include <cmath>
using namespace std;

/* DEFINICION DE CONSTANTES */
#define CANTIDADCANDIDATOS 2
#define CANTIDADBANCAS 5


int main() 
{

int arrBancasPorLista[CANTIDADBANCAS][2] = {0,1,1,1,2,0,1,2,3,4};

cout<<"Bancas Por Lista: "<<endl;
cout<<"Lista\t\tC. Votos\t\t\%Votos Validos\t\tPrimera Banca\t\tSegunda Banca\t\tTercera Banca\t\tCuarta Banca\t\tQuinta Banca"<<endl;
		for  (int a=0;a<2;a++)
		{
			for (int b=0;b<CANTIDADBANCAS;b++)
			{
				
				printf("Lista\t\tC. Votos\t\t\%Votos Validos\t\t%11d\t\t%11d\t\t\n",a,b);
			}
		}

}