#include <iostream>
#include <cmath>
#include <cstring>
#include <time.h>

using namespace std;
/* DEFINICION DE CONSTANTES */
#define CANTIDADCANDIDATOS 2
#define CANTIDADBANCAS 3

/* DEFINICION DE STRUCTS */
struct listaCandidato{

};
struct candidato{
	int numCandidato;
	char nombreCandidato[30];
	bool titular;
};	

struct listas{
	int numLista;
	char nombreLista[30];
	candidato candidatos[CANTIDADCANDIDATOS] ;
	int cantVotos;
	int porcVotos;
	int cantidadBancasAsignadas;
};
 
struct votante{
	char sexo;
	int edad;
	int voto;
};

struct bancas{
	int valor;
	int numLista;
};

/* DECLARACION DE FUNCIONES*/

bool leerCandidatos();
bool leerVotantes();

int pedirCantidadListas();
int pedirCantidadVotantes();

void poblarListas(listas arrListas[], int cListas);
void mostrarListas(listas arrListas[], int cListas);

void poblarVotantes(votante Vots[], int cVotantes, int cListas);
void mostrarVotantes (votante Vots[], int cVotantes);

void analizarVotantes (votante Vots[], listas arrListas[], int cVotantes, int cListas, int *vBlanco, int *vNulo); 
void analizarBancas(listas arrListas[], int cListas, int arrBancasPorLista[][2], int vBlanco, int vNulo);

void actualizarVotos(listas arrListas[], int cListas, votante Vots[], int cVotantes, int &votosBlanco, int &votosNulo);
void cargarMatrizBancas(int matrizBancas[][CANTIDADBANCAS],listas arrListas[], int cListas, int votosBlanco, int votosNulo);
void mostrarMatrizBancas(int matrizBancas[][CANTIDADBANCAS],listas arrListas[], int cListas);
void asignarBancas(bancas bancasAsignadas[], int matrizBancas[][CANTIDADBANCAS],listas arrListas[], int cListas);
void insertarOrdenadoBancas(bancas bancasAsignadas[], bancas bancaAux, int posicionIngresar);

void ordenarListas(listas arrListas[], int cListas); //Una vez que llamo esta funcion, pierdo el orden por defecto

void pausa(const char *);

int menu (bool, bool);

int main() 
{
bool listasCargadas = false;
bool votantesCargados = false;
int cantidadListas = 0;
int cantidadVotantes = 0;
int vBlanco = 0;
int vNulo = 0;
//CARGAR LISTAS DESDE LOS ARCHIVOS.
//CARGAR VOTANTES DESDE LOS ARCHIVOS.

listas *arrListas;
votante *arrVot;
int opcionMenu;
	while(true){
		opcionMenu = menu(listasCargadas, votantesCargados);
		switch(opcionMenu){
			case 0:
				delete[]arrListas;
				delete[]arrVot;
				return 0;
			break;
			case 1:
				cantidadListas = pedirCantidadListas();
				arrListas = new listas[cantidadListas];
				poblarListas(arrListas, cantidadListas);
				listasCargadas = true;
			break;
			case 2:
				mostrarListas(arrListas, cantidadListas);
				break;
			case 3:
				if (listasCargadas){
					cantidadVotantes = pedirCantidadVotantes();
					arrVot = new votante[cantidadVotantes];
					poblarVotantes(arrVot, cantidadVotantes, cantidadListas);
					votantesCargados = true;
				}else{
					cout << "Aun no se han cargado las listas" << endl;
				}
			break;
			case 4:
				mostrarVotantes(arrVot, cantidadVotantes);
			break;
			case 5:{
				int matrizBancas[cantidadListas][CANTIDADBANCAS];
				bancas bancasAsignadas[CANTIDADBANCAS]; //Utilizando la matriz, asigno el valor y la lista de cada banca
				actualizarVotos(arrListas, cantidadListas, arrVot, cantidadVotantes, vBlanco, vNulo);
				cargarMatrizBancas(matrizBancas, arrListas, cantidadListas, vBlanco, vNulo);
				asignarBancas(bancasAsignadas, matrizBancas, arrListas, cantidadListas);
				mostrarMatrizBancas(matrizBancas, arrListas, cantidadListas);
				//cout << "Votos en blanco: "<< vBlanco << " | Votos Nulos: " <<vNulo <<endl;
				break;
			}
			default:
				//
			break;
		};
	};
	return 0;
}


int menu (bool listasCargadas, bool votantesCargados){
	unsigned short int opcion=-1;
	cout<<"\nMenu Principal: \n" <<
	((listasCargadas) ? "\t1. Sobreescribir Listas\n" : "\t1. Cargar Listas\n") <<
	"\t2. Mostrar Listas\n" <<
	((votantesCargados) ? "\t3. Sobreescribir Votantes\n" : "\t3. Cargar Votantes\n") <<
	"\t4. Mostrar Votantes\n"
	"\t5. Mostrar Detalle Listas\n"
	"\t6. Mostrar Detalle Votantes\n"
	"\t0. Salir\n\n";
	
	do{
		cout<<"\r\t\t\t\t\t\r";
		cout<<"Ingrese su opcion: ";
		cin>>opcion;
	}while(opcion < 0 || opcion > 6);
	
return opcion;	
}



void actualizarVotos(listas arrListas[], int cListas, votante Vots[], int cVotantes, int &votosBlanco, int &votosNulo){
	for(int i=0; i<cVotantes;i++){ //RECORRO VOTANTES
		if(Vots[i].voto > 0 && Vots[i].voto <= cListas){
			arrListas[Vots[i].voto-1].cantVotos+=1;
		}else{
			if(Vots[i].voto == 0){
				votosBlanco+=1;
			}else{
				votosNulo+=1;
			}
		}
	}
	return;
}

void cargarMatrizBancas(int matrizBancas[][CANTIDADBANCAS],listas arrListas[], int cListas, int votosBlanco, int votosNulo){
	for(int i=0; i<cListas;i++){ //RECORRO LAS LISTAS PARA MOSTRARLAS
		for(int j=0; j<CANTIDADBANCAS; j++){
		  matrizBancas[i][j] = arrListas[i].cantVotos/(j+1);
		}
	}
	return;
}

void asignarBancas(bancas bancasAsignadas[], int matrizBancas[][CANTIDADBANCAS], listas arrListas[], int cListas){
	bancas bancaAux;
	for(int j=0; j<CANTIDADBANCAS; j++){
		bancasAsignadas[j].valor=matrizBancas[0][j];
		bancasAsignadas[j].numLista=0;
	}
	for(int i=1; i<cListas;i++){ 
		for(int j=0; j<CANTIDADBANCAS; j++){
			for(int k=0; k<CANTIDADBANCAS; k++){
		  		if(bancasAsignadas[k].valor<matrizBancas[i][j]){
		  			bancaAux.valor = matrizBancas[i][j];
		  			bancaAux.numLista = j+1;
		  			insertarOrdenadoBancas(bancasAsignadas, bancaAux, k);
		  			break;
		  		}
		  	}
		}
	}
	for(int j=0; j<CANTIDADBANCAS; j++){
		cout << bancasAsignadas[j].valor << " | " << bancasAsignadas[j].numLista;
		arrListas[bancasAsignadas[j].numLista].cantidadBancasAsignadas+=1; //Cargo las bancas que determiné en el paso anterior a mi array de Listas.
	}
	return;
}

void insertarOrdenadoBancas(bancas bancasAsignadas[], bancas bancaAux, int posicionIngresar){
	//TODO: Deberia insertar ordenadamente el bancaAux en el array bancasAsignadas
	for(int i=CANTIDADBANCAS-1; i>posicionIngresar;i--){
		bancasAsignadas[i]=bancasAsignadas[i-1];
	}
	bancasAsignadas[posicionIngresar]=bancaAux;
 return;
}

void mostrarMatrizBancas(int matrizBancas[][CANTIDADBANCAS],listas arrListas[], int cListas){
	cout<<"Listas\t\t| Cant de Votos |"; //TODO: Falta agregar el porcentaje de votos
	for (int k = 0; k<CANTIDADBANCAS; k++){
		cout << "["<<k+1<<"] Banca \t| ";
	}
	cout << "Ganan:|" <<endl;
	//TODO: IMPORTANTE! Falta "no contar" aquellas listas con menos del 3% de los votos.
	for(int i=0; i<cListas;i++){
		cout<<arrListas[i].numLista<<". "<<arrListas[i].nombreLista<< "\t\t| " << arrListas[i].cantVotos;
		for(int j=0; j<CANTIDADBANCAS; j++){
		  cout << "\t\t| " <<matrizBancas[i][j];
		}
		cout << "\t\t| " <<arrListas[i].cantidadBancasAsignadas <<"  \t|"<< endl;
	}
	return;
}






int pedirCantidadListas(){
	int cListas = 0;
	cout<<"\n\nIngrese cantidad de Listas: ";
	cin >> cListas;
	getchar();
	return cListas;
}

void poblarListas(listas arrListas[], int cListas)
{
	for(int i=0; i<cListas;i++){ //RECORRO LAS LISTAS PARA COMPLETARLAS
		arrListas[i].cantVotos=0;
		arrListas[i].cantidadBancasAsignadas=0;
		arrListas[i].numLista = i+1;
		cout<<"Ingrese el nombre de la lista numero "<<i+1<<" (de "<<cListas<<"): ";
		cin.getline(arrListas[i].nombreLista,sizeof(arrListas[i].nombreLista));
		for(int j=0; j<CANTIDADCANDIDATOS;j++){
			arrListas[i].candidatos[j].numCandidato=j+1;
			cout<<"Ingrese al candidato numero  "<<j+1<<" (de "<<CANTIDADCANDIDATOS<<"): ";
			cin.getline(arrListas[i].candidatos[j].nombreCandidato,sizeof(arrListas[i].candidatos[j].nombreCandidato));
		}
	}
	//TODO: Guardar listas en un archivo binario
	pausa ("\nListas cargadas, presione una tecla para volver al menu principal");
	return;
}

void mostrarListas(listas arrListas[], int cListas)
{	
	cout << endl;
	for(int i=0; i<cListas;i++){ //RECORRO LAS LISTAS PARA MOSTRARLAS
		cout<<arrListas[i].numLista<<". "<<arrListas[i].nombreLista<< " | Cantidad de Votos: " << arrListas[i].cantVotos <<endl;
		cout<<"		Candidatos:"<<endl;
		for(int j=0; j<CANTIDADCANDIDATOS;j++){
			cout<<"		"<<arrListas[i].candidatos[j].numCandidato<<". "<<arrListas[i].candidatos[j].nombreCandidato<<endl;
		}
	}
	return;
}





int pedirCantidadVotantes(){
	int cVotantes = 0;
	cout<<"Ingrese cantidad de Votantes: ";
	cin >> cVotantes;
	getchar();
	return cVotantes;
}

void poblarVotantes(votante arrVot[], int cVotantes, int cListas)
{
	for(int i=0; i<cVotantes;i++){ //RECORRO LAS LISTAS PARA COMPLETARLAS
		cout<<"Ingrese el sexo del votante numero "<<i+1<<" (de "<< cVotantes <<") (M/F): ";
		cin>>arrVot[i].sexo;
		cout<<"Ingrese la edad del votante numero "<<i+1<<" (de "<< cVotantes <<") : ";
		cin>>arrVot[i].edad;
		cout<<"Ingrese a quien voto el votante numero "<<i+1<<" (de "<< cVotantes <<") (0 a "<<cListas<<") : ";
		cin>>arrVot[i].voto;
	}
	//TODO: Guardar listas en un archivo binario
	return;
}

void mostrarVotantes(votante Vots[], int cVotantes)
{
	for(int i=0; i<cVotantes;i++){ //RECORRO VOTANTES
		cout<<"Votante["<<i+1<<"]: "<<"Sexo: "<<Vots[i].sexo<<" Edad: "<<Vots[i].edad<<" Voto: "<<Vots[i].voto<<endl;	
	}
	
}







bool leerCandidatos(){
	FILE *f;
	f = fopen("candidatos.csv", "r");
	if(!f){
		return false;
	}
	do{

	}while(!feof(f));
	return true;
}
bool leerVotantes(){
	FILE *f;
	f = fopen("candidatos.csv", "r");
	if(!f){
		return false;
	}
	do{

	}while(!feof(f));
	return true;
}

void pausa(const char *msg){
  cout << msg << endl;
  getchar();
}