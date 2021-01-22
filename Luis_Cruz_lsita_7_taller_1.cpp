
#include <conio.h>
#include <stdio.h>
#include <iostream>
using namespace std;
int numero_menu, salir;
char resp;

struct nodo{
    int codigo;
    char *nombre;
    int nivel;
    nodo *sig;
};

nodo *inicial = NULL;
int codigo;

class Estudiantes{
    private:
        nodo *anterior, *nuevo, *apun;
    public:
        Estudiantes(nodo *,nodo *,nodo *);
        nodo* leer_nodo();
        void crear_lista();
        void imprime_nodo();
        void setApuntador();
        void reco_recur();
        void nuevo_inicial_desde_lista_vacia();
        bool revisar_codigo(int cod);
        nodo* set_eliminar_codigo();
        nodo* buscar_codigo(int clave);
        nodo* setAnterior();
        nodo* agregar_anterior();
        nodo* agregar_nodo(int clave);
        nodo* cambiar_inicial();
        void eliminar();
        ~Estudiantes();
};

Estudiantes::Estudiantes(nodo *_anterior ,nodo *_nuevo,nodo *_apun){
    anterior = _anterior;
    nuevo = _nuevo;
    apun = _apun;
}

nodo* Estudiantes::leer_nodo(){
    cout <<"Entre el codigo del estudiante: "<<endl;
    int aux = 0;
    cin >>aux;
    if (revisar_codigo(aux) == true){
      nuevo->codigo = aux;
      cout <<"Entre el nombre del estudiante: "<<endl;
      cin.ignore();
      nuevo->nombre = new char[30];
      cin.getline(nuevo->nombre,30);
      cout <<"Entre el nivel del estudiante: "<<endl;
      cin >>nuevo->nivel;
      return nuevo;
    }else{
      return leer_nodo();
    }
}

void Estudiantes::crear_lista(){
    nuevo = new nodo;
    if(anterior == NULL){
        nuevo->sig = inicial;
        nuevo = leer_nodo();
        inicial = nuevo;
    }
    else{
        nuevo->sig =anterior->sig;
        anterior->sig = nuevo;
        nuevo = leer_nodo();
    }
    anterior = nuevo;
}

void Estudiantes::nuevo_inicial_desde_lista_vacia(){
    nuevo = new nodo;
    nuevo->sig = inicial;
    nuevo = leer_nodo();
    inicial = nuevo;
    anterior = nuevo;
}

void Estudiantes::imprime_nodo(){
    cout << "El codigo es: "<<apun->codigo<<endl;
    cout << "El nombre es: "<<apun->nombre<<endl;
    cout << "El nivel es: "<<apun->nivel<<endl;
}

void Estudiantes::reco_recur(){
    while(apun != NULL){
        imprime_nodo();
        apun = apun->sig;
        reco_recur();
    }
}

void Estudiantes::setApuntador(){
    apun = inicial;
}

nodo* Estudiantes::set_eliminar_codigo(){
    anterior = inicial;
    apun = buscar_codigo(codigo);
    return apun;
}

void Estudiantes::eliminar(){
    nodo *elimina = apun;
    inicial = elimina->sig;
    apun = elimina->sig;
    delete elimina;
}

bool Estudiantes::revisar_codigo(int cod){
    bool respuesta = true;
    setApuntador();
    while(apun != NULL){
      if (apun -> codigo == cod){
        printf("El nodo a agregar ya existe:\n" );
        respuesta = false;
      }
      apun = apun->sig;
    }
    return respuesta;
}

nodo* Estudiantes::cambiar_inicial(){
    inicial = agregar_nodo(codigo);
    return inicial;
}

nodo* Estudiantes::agregar_anterior(){
    anterior = agregar_nodo(codigo);
    return anterior;
}

nodo* Estudiantes::setAnterior(){
    anterior = inicial;
    anterior = buscar_codigo(codigo);
    return anterior;
}

nodo* Estudiantes::buscar_codigo(int clave){
    while(anterior != NULL){
        if( anterior->codigo == clave ){
             return anterior;
        }
        else {
            anterior = anterior->sig;
        }
    }
    return NULL;
}

nodo* Estudiantes::agregar_nodo(int clave){
      nuevo = new nodo;
      if(clave == 0){
          // agregar al inicio de la lista
          nuevo->sig = anterior;
          anterior = nuevo;
          nuevo = leer_nodo();
          return anterior;
      }else{
          // Agregar despues del primero, segundo, ...., o ultimo
          //elemento de la Lista
          nuevo->sig = anterior->sig;
          anterior->sig = nuevo;
          nuevo = leer_nodo();
          return anterior;
        }
}

Estudiantes::~Estudiantes(){
    nodo *apun = inicial;
	while(apun != NULL){
		inicial = apun->sig;
		delete apun ;
		apun = inicial ;
	}
}

int main(){
        nodo *anterior, *nuevo, *apun;
        char resp;
        anterior = NULL;
        apun = NULL;
        nuevo = new nodo;
        Estudiantes l1(anterior,nuevo,apun);
        cout << "Empieza a crear la lista original \n"<<endl;
        do{
            l1.crear_lista();
            cout << "Desea crear otro nodo? (s/n) : "<<endl;
            cin >> resp;
            resp=tolower(resp);
        }while(resp != 'n');
        l1.setApuntador();
        l1.reco_recur();
        do{
          printf("Que operacion desea usar:\n" );
          printf("1) Eliminar el primer nodo \n");
          printf("2) Eliminar nodo de la lista (Codigo) \n");
          printf("3) Agregar un nodo a la lista original \n");
          printf("4) Crear el inicial de una lista vacia \n");
          printf("5) Eliminar toda la lista \n");
          printf("Inserte el numero de la accion que desea hacer:\n");
          printf("Presione el numero Cero (0) para salir\n");
          scanf("%d",&numero_menu);
            switch (numero_menu) {
            case 1: {
              printf("ejecuto 1) Eliminar el primer nodo  \n\n");
              l1.setApuntador();
              l1.eliminar();
              l1.reco_recur();
              break;
            }case 2: {
              printf("ejecuto 2) Eliminar nodo de la lista (Codigo) \n");
              printf("Digite el codigo del nodo que desea eliminar\n");
              scanf("%d",&codigo);
              apun = l1.set_eliminar_codigo();
              if(apun != NULL){
                l1.eliminar();
                if (apun->sig == NULL){
                  printf("Elimino el unico nodo que quedaba, la lista quedo vacia\n");
                }
                l1.setApuntador();
                l1.reco_recur();
              }else{
                printf("El nodo no ha sido encontrado \n");
              }
              break;
            }case 3: {
              printf("ejecuto 3) Agregar un nodo a la lista original \n\n");
              printf("Digite 0 si va agregar a la cabeza de la lista, desplazando la existente \n");
              printf("Si no digite el codigo anterior de la posicion deseada \n");
              scanf("%d",&codigo);

              if(codigo == 0){
                  inicial = l1.cambiar_inicial();
              }
              else{
                  anterior = l1.setAnterior();
                  if(anterior != NULL){
                      anterior = l1.agregar_anterior();
                  }
                  else{
                      cout << "El nodo no ha sido encontrado " <<endl;
                  }
              }
              l1.setApuntador();
              l1.reco_recur();
              break;
            }case 4: {
              printf("ejecuto  4) Crear el inicial de una lista vacia \n\n");
              anterior = NULL;
              apun = NULL;
              l1.nuevo_inicial_desde_lista_vacia();
              l1.setApuntador();
              l1.reco_recur();
              break;
            }case 5: {
              printf("ejecuto  5) Eliminar toda la lista \n\n");
              l1.~Estudiantes();
              l1.setApuntador();
              l1.reco_recur();
              break;
            }default: {
              printf("La opcion no esta en el menu \n\n");
              break;
            }
            }
      }while (numero_menu != 0);
      printf("Gracias por preferirme para crear su lista simplemente enlazada \n\n");
}
