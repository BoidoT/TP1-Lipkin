#include <iostream>
#include <cmath>
#include <cstring>
#include <ctime>

using namespace std;
/* DEFINICION DE CONSTANTES */
#define CANTIDADCANDIDATOS 1
#define CANTIDADBANCAS 6

/* DEFINICION DE STRUCTS */

struct candidato{
	int numCandidato;
	char nombreCandidato[30];
	bool titular;
};	

struct lCandidato{
	candidato dato;

}
struct listas{
	int numLista;
	char nombreLista[30];
	candidato candidatos[CANTIDADCANDIDATOS] ;
	int cantVotos;
	int porcVotos;
	int cantidadBancasAsignadas;
	int votosHasta18;
	int votosHasta30;
	int votosHasta50;
	int votosMas50;
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

bool leerListas(listas arrListas[], int cListas);
bool leerVotantes(votante Vots[], int cVotantes, int cListas);
bool guardarArchivoListas(listas arrListas[], int cListas);
bool guardarArchivoVotantes(votante Vots[], int cVotantes, int cListas);

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
void mostrarMatrizBancas(int matrizBancas[][CANTIDADBANCAS],listas arrListas[], int cListas, int votosBlanco, int votosNulo);
void asignarBancas(bancas bancasAsignadas[], int matrizBancas[][CANTIDADBANCAS],listas arrListas[], int cListas);
void insertarOrdenadoBancas(bancas bancasAsignadas[], bancas bancaAux, int posicionIngresar);

void ordenarListas(listas arrListas[], int cListas); //Una vez que llamo esta funcion, pierdo el orden por defecto

void mostrarListasVotantes(listas arrListas[], int cListas);

void pausa(const char *);

int menu (bool, bool);

long filesize(const char *file);

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



listas *arrListas = NULL;
votante *arrVot = NULL;

//Fijarse si los archivos Existen, en caso de que si, cargarlos.
listasCargadas = (filesize("..\\Segunda Entrega\\listas.bin") > 0) ? true : false;
if (listasCargadas)
{
	//Leer Listas deberia cargar dentro de si misma, los candidatos.
	cantidadListas = filesize("..\\Segunda Entrega\\listas.bin")/sizeof(struct listas);
	cout<<"Cantidad de listas leidas: "<<cantidadListas<<endl;
	arrListas = new listas[cantidadListas];
	leerListas(arrListas, cantidadListas);
	if (filesize("..\\Segunda Entrega\\votantes.bin") > 0)
	{
		cantidadVotantes = filesize("..\\Segunda Entrega\\votantes.bin")/sizeof(struct votante);
		arrVot = new votante[cantidadVotantes];
		cout<<"Cantidad de Votantes leidos: "<<cantidadVotantes<<endl;
		leerVotantes(arrVot, cantidadVotantes, cantidadListas);
		votantesCargados=true
	}else{
		cout<<"No se han encontrado votantes cargados"<<endl;
	}
	//
}else{
	cout<<"No se han encontrado listas cargadas"<<endl;
	pausa("Finalizando la ejecucion");
	return;
}

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
				mostrarListas(arrListas, cantidadListas);
			break;
			/*case 3:
				if (listasCargadas){
					cantidadVotantes = pedirCantidadVotantes();
					arrVot = new votante[cantidadVotantes];
					poblarVotantes(arrVot, cantidadVotantes, cantidadListas);
					actualizarVotos(arrListas, cantidadListas, arrVot, cantidadVotantes, vBlanco, vNulo);
					ordenarListas(arrListas, cantidadListas);
					//Por que guardar otra vez? Por que aca se actualizaron las variables de los structs.
					guardarArchivoListas(arrListas, cantidadListas);
					guardarArchivoVotantes(arrVot, cantidadVotantes, cantidadListas);
					votantesCargados = true;
				}else{
					cout << "Aun no se han cargado las listas" << endl;
				}
			break;*/
			case 2:
				mostrarVotantes(arrVot, cantidadVotantes);
			break;
			/*case 5:{
				int matrizBancas[cantidadListas][CANTIDADBANCAS];
				bancas bancasAsignadas[CANTIDADBANCAS]; //Utilizando la matriz, asigno el valor y la lista de cada banca
				//actualizarVotos(arrListas, cantidadListas, arrVot, cantidadVotantes, vBlanco, vNulo);
				//ordenarListas(arrListas, cantidadListas);
				cargarMatrizBancas(matrizBancas, arrListas, cantidadListas, vBlanco, vNulo);
				asignarBancas(bancasAsignadas, matrizBancas, arrListas, cantidadListas);
				mostrarMatrizBancas(matrizBancas, arrListas, cantidadListas, vBlanco, vNulo);
				//cout << "Votos en blanco: "<< vBlanco << " | Votos Nulos: " <<vNulo <<endl;
			} break;
			case 6:
				mostrarListasVotantes(arrListas, cantidadListas);
			break;*/
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
	//((listasCargadas) ? "\t1. Sobreescribir Listas\n" : "\t1. Cargar Listas\n") <<
	"\t2. Mostrar Listas\n" <<
	//((votantesCargados) ? "\t3. Sobreescribir Votantes\n" : "\t3. Cargar Votantes\n") <<
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












void cargarMatrizBancas(int matrizBancas[][CANTIDADBANCAS],listas arrListas[], int cListas, int votosBlanco, int votosNulo){
	for(int i=0; i<cListas;i++){ //RECORRO LAS LISTAS PARA MOSTRARLAS
		for(int j=0; j<CANTIDADBANCAS; j++){
		  	if (arrListas[i].porcVotos < 3) {
		  		matrizBancas[i][j] = 0;
		  	}else{
		  		matrizBancas[i][j] = round(arrListas[i].cantVotos/(j+1));
			}
		}
	}
	return;
}

void asignarBancas(bancas bancasAsignadas[], int matrizBancas[][CANTIDADBANCAS], listas arrListas[], int cListas){
	bancas bancaAux;
	for(int k=0; k<cListas; k++) arrListas[k].cantidadBancasAsignadas=0; //Vacio mis bancas asignadas

	for(int j=0; j<CANTIDADBANCAS; j++){
		bancasAsignadas[j].valor=matrizBancas[0][j];
		bancasAsignadas[j].numLista=1;
	}
	for(int i=1; i<cListas;i++){
		for(int j=0; j<CANTIDADBANCAS; j++){
			for(int k=0; k<CANTIDADBANCAS; k++){
		  		if(bancasAsignadas[k].valor<matrizBancas[i][j]){
		  			bancaAux.valor = matrizBancas[i][j];
		  			bancaAux.numLista = i+1;
		  			insertarOrdenadoBancas(bancasAsignadas, bancaAux, k);
		  			break;
		  		}
		  	}
		}
	}
	for(int k=0; k<CANTIDADBANCAS; k++){
		//cout << bancasAsignadas[k].valor << " | " << bancasAsignadas[k].numLista;
		arrListas[bancasAsignadas[k].numLista-1].cantidadBancasAsignadas+=1; //Cargo las bancas que determiné en el paso anterior a mi array de Listas.
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

void mostrarMatrizBancas(int matrizBancas[][CANTIDADBANCAS],listas arrListas[], int cListas, int votosBlanco, int votosNulo){
	cout<<"Listas\t\t| Cant de Votos \t| Porc votos validos \t| "; //TODO: Falta agregar el porcentaje de votos
	for (int k = 0; k<CANTIDADBANCAS; k++){
		cout << "["<<k+1<<"] Banca \t| ";
	}
	cout << "Ganan: \t|" <<endl;
	//TODO: IMPORTANTE! Falta "no contar" aquellas listas con menos del 3% de los votos.
	for(int i=0; i<cListas;i++){
		cout<<arrListas[i].numLista<<". "<<arrListas[i].nombreLista<< "\t\t| " << arrListas[i].cantVotos << " \t\t\t| " << arrListas[i].porcVotos << "% \t\t\t| ";
		for(int j=0; j<CANTIDADBANCAS; j++){
		  cout <<matrizBancas[i][j] << " \t\t| ";
		}
		cout << arrListas[i].cantidadBancasAsignadas <<" \t\t|"<< endl;
	}
	cout << "Votos Blanco \t| " << votosBlanco << " \t\t\t|" << endl;
	cout << "Votos Nulos \t| " << votosNulo << " \t\t\t|" << endl;
	return;
}

void mostrarListasVotantes(listas arrListas[], int cListas){
	cout << endl;
	cout << "Nombre de Lista \t| Cantidad de Votos \t| (Hasta 18 anos) \t| (Hasta 30 anos) \t| (Hasta 50 anos) \t| (Mas de 50 anos) \t|" << endl;
	for(int i=0; i<cListas;i++){ //RECORRO LAS LISTAS PARA MOSTRARLAS
		cout<<arrListas[i].numLista<<". "<<arrListas[i].nombreLista<< " \t\t\t| " << arrListas[i].cantVotos <<" \t\t\t| "<< arrListas[i].votosHasta18<<" \t\t\t| "<<arrListas[i].votosHasta30<<" \t\t\t| "<<arrListas[i].votosHasta50<<" \t\t\t| "<<arrListas[i].votosMas50<<" \t\t\t|"<<endl;
	}
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
	char in[30];
	for(int i=0; i<cListas;i++){ //RECORRO LAS LISTAS PARA COMPLETARLAS
		arrListas[i].cantVotos=0;
		arrListas[i].porcVotos=0;
		arrListas[i].cantidadBancasAsignadas=0;
		arrListas[i].votosHasta18 = 0;
		arrListas[i].votosHasta30 = 0;
		arrListas[i].votosHasta50 = 0;
		arrListas[i].votosMas50 = 0;
		arrListas[i].numLista = i+1;
		cout<<"Ingrese el nombre de la lista numero "<<i+1<<" (de "<<cListas<<"): ";
		//para mi, el tema esta aca. ERROR.
		cin.getline(in,30);
		strcpy(arrListas[i].nombreLista, in);
		
		for(int j=0; j<CANTIDADCANDIDATOS;j++){
			arrListas[i].candidatos[j].numCandidato=j+1;
			cout<<"Ingrese al candidato numero  "<<j+1<<" (de "<<CANTIDADCANDIDATOS<<"): ";
			
			cin.getline(in,30);
			strcpy(arrListas[i].candidatos[j].nombreCandidato, in);
			arrListas[i].candidatos[j].titular = false;
		}
	}
	//TODO: Guardar listas en un archivo binario
	guardarArchivoListas(arrListas, cListas);
	pausa ("\nListas cargadas, presione una tecla para volver al menu principal");
	return;
}

void mostrarListas(listas arrListas[], int cListas)
{	
	cout <<"mostrando Listas: " <<endl;
	for(int i=0; i<cListas;i++){ //RECORRO LAS LISTAS PARA MOSTRARLAS
		cout<<arrListas[i].numLista<<". "<<arrListas[i].nombreLista<< " | Cantidad de Votos: " << arrListas[i].cantVotos <<endl;
		cout<<"		Candidatos:"<<endl;
		for(int j=0; j<CANTIDADCANDIDATOS;j++){
			cout<<"		"<<arrListas[i].candidatos[j].numCandidato<<". "<<arrListas[i].candidatos[j].nombreCandidato<<endl;
		}
	}
	return;
}

void ordenarListas(listas arrListas[], int cListas){
	listas temp;
	for(int i=0;i<cListas;i++)
	{
		for(int j=i+1;j<cListas;j++)
		{
			if(arrListas[i].cantVotos < arrListas[j].cantVotos)
			{
				temp = arrListas[i];
				arrListas[i] = arrListas[j];
				arrListas[j] = temp;
			}
		}
	}

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

void actualizarVotos(listas arrListas[], int cListas, votante Vots[], int cVotantes, int &votosBlanco, int &votosNulo){
	int totalVotosValidos = 0;
	votosBlanco=0;
	votosNulo=0;
	for(int j=0; j<cListas; j++){
		arrListas[j].votosHasta18 = 0;
		arrListas[j].votosHasta30 = 0;
		arrListas[j].votosHasta50 = 0;
		arrListas[j].votosMas50 = 0;
		arrListas[j].cantVotos = 0; //Vacio mi cantidad de Votos actual
	} 

	for(int i=0; i<cVotantes;i++){ //RECORRO VOTANTES
		if(Vots[i].voto > 0 && Vots[i].voto <= cListas){
			for(int k=0; k<cListas; k++){
				if((Vots[i].voto)==arrListas[k].numLista){
					if(Vots[i].edad <= 18) arrListas[k].votosHasta18+=1;
					if(Vots[i].edad > 18 && Vots[i].edad <= 30) arrListas[k].votosHasta30+=1;
					if(Vots[i].edad > 30 && Vots[i].edad <= 50) arrListas[k].votosHasta50+=1;
					if(Vots[i].edad > 50) arrListas[k].votosMas50+=1;
					arrListas[k].cantVotos+=1;
					totalVotosValidos+=1;
					break;
				}
			}
		}else{
			if(Vots[i].voto == 0){
				votosBlanco+=1;
			}else{
				votosNulo+=1;
			}
		}
	}
	for(int j=0; j<cListas; j++){
		arrListas[j].porcVotos = round((arrListas[j].cantVotos * 100) / totalVotosValidos);
	}
return;
}


//Funcion para calcular el tamaño del archivo.
//Puede fallar dependiendo de la implementacion de las librerias. Pero, deberia funcionar en WIN32
long filesize(const char *file)
{
	FILE *f = fopen(file, "rb");
	if(!f) return -1;
	

	fseek(f, 0, SEEK_END); // seek to end of file
	long size = ftell(f); // get current file pointer
	fseek(f, 0, SEEK_SET); // seek back to beginning of file
	fclose(f);

	return size;
}


bool guardarArchivoListas(listas arrListas[], int cListas){
	FILE *f;
	
	f = fopen("listas.bin", "wb");

	if(!f){
		return false;
	}
	
	for(int i=0; i<cListas;i++)
	{
		fwrite(&arrListas[i],sizeof(struct listas),1,f);
	}
	fclose(f);
	return true;
}

bool guardarArchivoVotantes(votante Vots[], int cVotantes, int cListas){
		FILE *f;
	
	f = fopen("votantes.bin", "wb");

	if(!f){
		return false;
	}
	
	for(int i=0; i<cVotantes;i++)
	{
		fwrite(&Vots[i],sizeof(struct votante),1,f);
	}
	fclose(f);
	return true;
}


//Tendria que pasarle el array ya creado.
bool leerListas(listas arrListas[], int cListas){
	listas aux;
    FILE *f;
	f = fopen("listas.bin", "rb");
	if(!f){
		return false;
	}
	
	for(int i=0; i<cListas;i++){
		fread(&arrListas[i], sizeof(struct listas), 1, f);
	}
	cout<<"Leidos: "<<cListas<<" registros de Listas."<<endl;
	fclose(f);
	return true;
}

//TODO:
bool leerVotantes(votante Vots[], int cVotantes, int cListas){
	votante aux;
    FILE *f;
	

	f = fopen("votantes.bin", "rb");
	if(!f){
		return false;
	}
	
	for(int i=0; i<cVotantes;i++){
		fread(&Vots[i], sizeof(struct votante), 1, f);
	}
	cout<<"Leidos: "<<cVotantes<<" registros de Votantes."<<endl;
	return true;
}

void pausa(const char *msg){
  cout << msg << endl;
  getchar();
}

