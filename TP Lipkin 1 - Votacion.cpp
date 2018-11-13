#include <iostream>
#include <cmath>
using namespace std;

/* DEFINICION DE CONSTANTES */
#define CANTIDADCANDIDATOS 2
#define CANTIDADBANCAS 5
//#define CANTIDADLISTAS 5

/* DEFINICION DE STRUCTS */
struct candidato{
	int numCandidato;
	char nombreCandidato[30];
};	

struct listas{
	int numLista;
	char nombreLista[30];
	candidato candidatos[CANTIDADCANDIDATOS];
	int cantVotos, cantidadBancasAsignadas, porcenVotos;
	int bancas[CANTIDADBANCAS];
};

struct votante{
	char sexo;
	int edad;
	int voto;
};

/* DECLARACION DE FUNCIONES*/
void poblarListas(listas arrListas[], int cListas);
void mostrarListas(listas arrListas[], int cListas);
int pedirCantidadListas();
int pedirCantidadVotantes();

void poblarVotantes(votante Vots[], int cVotantes, int cListas);
void mostrarVotantes (votante Vots[], int cVotantes);
void analizarVotantes (votante Vots[], listas arrListas[], int cVotantes, int cListas, int *vBlanco, int *vNulo); 
void analizarBancas(listas arrListas[], int cListas, int arrBancasPorLista[][2]);

int main() 
{
	//Pido la cantidad de Listas, y genero el Array.
	int cantidadListas = pedirCantidadListas();
	listas arrListas[cantidadListas];
	//Lleno la lista con inputs
	poblarListas(arrListas, cantidadListas);
	//Muestro las listas
	mostrarListas(arrListas, cantidadListas);

	//votantes:
	//Pido la cantidad de votantes y genero un array de votantes.
	int cantidadVotantes = pedirCantidadVotantes();
	votante arrVot[cantidadVotantes];
	//Lleno los votantes con los inputs
	poblarVotantes(arrVot, cantidadVotantes, cantidadListas);
	//Muestro
	mostrarVotantes(arrVot, cantidadVotantes);

	//Procesar Votos
	int votBlanco=0;
	int votNulo=0;
	analizarVotantes(arrVot, arrListas, cantidadVotantes, cantidadListas, &votBlanco, &votNulo);
	
	
	int arrBancasPorLista[CANTIDADBANCAS][2];
	//Recorro el array de listas, e itero sobre las bancas, buscando los X mayores (donde X es CANTIDADBANCAS)
	analizarBancas(arrListas, cantidadListas, arrBancasPorLista);
	system("pause");
    return 0;
}

/** @brief Completa las listas con input del usuario
 * 
 *  @param[in,out] Vots Array de Votantes
 *  @param[in,out] arrListas Array de Listas
 *  @param[in] cVotantes Cantidad de Votantes
 *  @param[in] cListas Cantidad de listas
 *  @param[out] vBlanco Puntero a contador de Votos en blanco
 *  @param[out] vNulo Puntero a contador de Votos Nulos
 *  @return none
 */
void analizarVotantes(votante Vots[], listas arrListas[], int cVotantes, int cListas, int *vBlanco, int *vNulo){
	int votoNormalizado;
	int votosValidos;
	
	for(int i=0; i<cVotantes; i++){
		if(Vots[i].voto==0){
			vBlanco++;
		}else{
		if(Vots[i].voto>cListas){
			vNulo++;
		}else{
		votoNormalizado = Vots[i].voto - 1; //Normalizo el voto del Votante, restandole uno para que coincida con el Index de la Lista
		arrListas[votoNormalizado].cantVotos++;
		votosValidos++;
		}
		}
	}
	for(int j=0; j<cListas; j++){
		arrListas[j].porcenVotos=round((arrListas[j].cantVotos*100)/votosValidos);
		for(int k=0; k<CANTIDADBANCAS; k++){
			arrListas[j].bancas[k]= round(arrListas[j].cantVotos/(k+1));
		}
	}
}

/** @brief Pide la cantidad de Listas al usuario
 * 
 *  @param none
 * 
 *  @return Int.
 */
int pedirCantidadListas(){
	int cListas = 0;
	cout<<"Ingrese cantidad de Listas: ";
	cin >> cListas;
	getchar();
	return cListas;
}

/** @brief Pide la cantidaad de Votantes al usuario
 * 
 *  @param none
 * 
 *  @return Int.
 */
int pedirCantidadVotantes(){
	int cVotantes = 0;
	cout<<"Ingrese cantidad de Votantes: ";
	cin >> cVotantes;
	getchar();
	return cVotantes;
}

/** @brief Completa las listas con input del usuario
 * 
 *  @param[in,out] arrListas Array de listas
 *  @param[in] cListas Cantidad de listas
 * 
 *  @return none
 */
void poblarListas(listas arrListas[], int cListas)
{
	
	for(int i=0; i<cListas;i++){ //RECORRO LAS LISTAS PARA COMPLETARLAS
		arrListas[i].cantVotos=0;
		arrListas[i].numLista = i+1;
		cout<<"Ingrese el nombre de la lista numero("<<i+1<<"): ";
		cin.getline(arrListas[i].nombreLista,sizeof(arrListas[i].nombreLista));
		for(int j=0; j<CANTIDADCANDIDATOS;j++){
			arrListas[i].candidatos[j].numCandidato=j+1;
			cout<<"Ingrese al candidato numero("<<j+1<<"): ";
			cin.getline(arrListas[i].candidatos[j].nombreCandidato,sizeof(arrListas[i].candidatos[j].nombreCandidato));
		}
	}
}

/** @brief Completa las listas de Votantes con input del usuario
 * 
 *  @param[in,out] arrVot Array de Votantes
 *  @param[in] cVotantes Cantidad de Votantes
 *  @param[in] cListas Cantidad de Listas
 * 
 *  @return none
 */
void poblarVotantes(votante arrVot[], int cVotantes, int cListas)
{
	for(int i=0; i<cVotantes;i++){ //RECORRO LAS LISTAS PARA COMPLETARLAS
		cout<<"Ingrese el sexo del votante numero("<<i+1<<") (M/F): ";
		cin>>arrVot[i].sexo;
		cout<<"Ingrese la edad del votante numero("<<i+1<<") : ";
		cin>>arrVot[i].edad;
		cout<<"Ingrese a quien voto el votante numero("<<i+1<<") (0 a "<<cListas<<") : ";
		cin>>arrVot[i].voto;
	}
	return;
}

/** @brief Muestra de las listas en pantalla
 * 
 *  @param[in] arrListas Array de Listas
 *  @param[in] cListas Cantidad de Listas
 * 
 *  @return none
 */
void mostrarListas(listas arrListas[], int cListas)
{
	for(int i=0; i<cListas;i++){ //RECORRO LAS LISTAS PARA MOSTRARLAS
		cout<<arrListas[i].numLista<<". "<<arrListas[i].nombreLista<<endl;
		cout<<"		Candidatos:"<<endl;
		for(int j=0; j<CANTIDADCANDIDATOS;j++){
			cout<<"		"<<arrListas[i].candidatos[j].numCandidato<<". "<<arrListas[i].candidatos[j].nombreCandidato<<endl;
		}
	}
	return;
}

/** @brief Muestra de las listas en pantalla
 * 
 *  @param[in] Vots Array de Votantes
 *  @param[in] cVotantes Cantidad de Votantes
 * 
 *  @return none
 */
void mostrarVotantes(votante Vots[], int cVotantes)
{
	for(int i=0; i<cVotantes;i++){ //RECORRO VOTANTES RARLAS
		cout<<"Votante["<<i+1<<"]: "<<"Sexo: "<<Vots[i].sexo<<" Edad: "<<Vots[i].edad<<" Voto: "<<Vots[i].voto<<endl;
			
	}
	
}

/** @brief Calcula las bancas para cada lista,
 * 		   en base a los input de las demas funciones
 * 
 *  @param[in] arrListas Array de Listas
 *  @param[in] cListas Cantidad de Listas
 *  @param[in,out] arrBancasPorLista Array de bancas para cada lista.
 * 
 *  @return none
 */
void analizarBancas(listas arrListas[], int cListas, int arrBancasPorLista[][2])
{
	int flag=0;
		//inicializo la matriz de bancas por lista) [FILA 0 = Lista / FILA 1 = Cant Votos]
		for  (int w=0;w<2;w++)
		{
			for (int z=0;z<CANTIDADBANCAS;z++)
			{
				arrBancasPorLista[z][w] = 0;
			}
		}
	for (int i=0;i<cListas;i++) //Index de la Lista
	{
		for (int j=0;j<CANTIDADBANCAS;j++) //Recorro cada banca para esa lista
		{
			//Comparo con cada uno de los existentes [FILA 0 = Lista / FILA 1 = Cant Votos]
			for (int k=0;k<CANTIDADBANCAS;k++)
			{
				if (!flag)
				{
					if (arrListas[i].bancas[j] > arrBancasPorLista[k][1])
					{
						arrBancasPorLista[k][0] = i;
						arrBancasPorLista[k][1] = arrListas[i].bancas[j];
						flag=1;
					}
				}
			}
			flag=0;
		}				
	}
//Deberia imprimir algo aca para ver si esta bosta funciona, al primer intento;

//Hacer esto bien.

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
