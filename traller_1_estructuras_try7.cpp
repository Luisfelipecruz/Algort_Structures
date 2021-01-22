#include <iostream>
#include <stdlib.h>

using namespace std;

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
        nodo *anterior,*nuevo, *apun;
    public:
        Estudiantes(nodo *,nodo * , nodo *);
        nodo* buscar_nodo(int clave);
        nodo* leer_nodo();
        void crear_lista();
        void imprime_nodo();
        void setApuntador();
        nodo* setAnterior();
        nodo* setMod_I();
        nodo* setMod_A();
        nodo* setApun();
        void eliminar();
        void reco_recur();
        nodo* agregar_nodo(int clave);
        ~Estudiantes();
};

Estudiantes::Estudiantes(nodo *_anterior ,nodo *_nuevo,nodo *_apun){
    anterior = _anterior;
    nuevo = _nuevo;
    apun = _apun;
}

nodo* Estudiantes::leer_nodo(){
    cout <<"Entre el codigo del estudiante: "<<endl;
    cin >>nuevo->codigo;
    cout <<"Entre el nombre del estudiante: "<<endl;
    cin.ignore();
    nuevo->nombre = new char[30];
    cin.getline(nuevo->nombre,30);
    cout <<"Entre el nivel del estudiante: "<<endl;
    cin >>nuevo->nivel;
    return nuevo;
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

void Estudiantes::imprime_nodo(){
    cout << "El codigo es: "<<apun->codigo<<endl;
    cout << "El nombre es: "<<apun->nombre<<endl;
    cout << "El nivel es: "<<apun->nivel<<endl;
}

void Estudiantes::setApuntador(){
    apun = inicial;
}

nodo* Estudiantes::setAnterior(){
    anterior = inicial;
    anterior = buscar_nodo(codigo);
    return anterior;
}
nodo* Estudiantes::setMod_I(){
    inicial = agregar_nodo(codigo);
    return inicial;
}

nodo* Estudiantes::setMod_A(){
    anterior = agregar_nodo(codigo);
    return anterior;
}

void Estudiantes::reco_recur(){
    while(apun != NULL){
        imprime_nodo();
        apun = apun->sig;
        reco_recur();
    }
}

nodo* Estudiantes::setApun(){
    anterior = inicial;
    apun = buscar_nodo(codigo);
    return apun;
}

nodo* Estudiantes::buscar_nodo(int clave){
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
    }
    else{
        // Agregar despues del primero, segundo, ...., o ultimo
        //elemento de la Lista
        nuevo->sig = anterior->sig;
        anterior->sig = nuevo;
        nuevo = leer_nodo();
        return anterior;
    }
}

void Estudiantes::eliminar(){
    nodo *elimina = apun->sig;
    apun->sig = elimina->sig;
    delete elimina;
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
    nodo  *nuevo, *apun, *anterior;
    char resp;
    anterior = NULL;
    cout << "Empieza a crear la lista original \n"<<endl;
    Estudiantes l1(anterior,nuevo,apun);
    do{
        l1.crear_lista();
        cout << "Desea crear otro nodo? (s/n) : "<<endl;
        cin >> resp;
    }while(resp != 'n');
    l1.setApuntador();
    l1.reco_recur();

    // inicio de la agregacionde nuevos nodos
    cout <<endl;
    cout << "Inicio de la agregacion de nuevos nodos a la lista original"<<endl;
    do{
        cout <<endl;
        cout << "entre el codigo clave (Digite 0 si va agregar a la cabeza de la lista."<<endl;
        cout << "(en, caso contrario digite el codigo del nodo anterioral que va a crear) \n"<<endl;
        cin >> codigo;
        if(codigo == 0){
            inicial = l1.setMod_I();
        }
        else{
            anterior = l1.setAnterior();
            if(anterior != NULL){
                anterior = l1.setMod_A();
            }
            else{
                cout << "El nodo no ha sido encontrado " <<endl;
            }
        }
        cout << "Desea agregar otro nodo? (s/n): " <<endl;
        cin >> resp;
    }while(resp != 'n');
    cout << "La lista completa es: "<<endl;
    cout << endl;
    l1.setApuntador();
    l1.reco_recur();
    cout << endl;
    cout << "Desea eliminar un nodo? (s/n): " <<endl;
    cin >> resp;
    cout << "Ingrese el codigo del nodo: "<<endl;
    cin >> codigo;
    while(resp != 'n'){
        apun = l1.setApun();
        if(apun != NULL){
            l1.eliminar();
            cout << "Desea eliminar otro nodo? (s/n): " <<endl;
            cin >> resp;
            if(resp != 'n'){
                cout << "Ingrese el codigo del nodo: "<<endl;
                cin >> codigo;
            }
        }
        else{
            cout << "El nodo no ha sido encontrado " <<endl;
            cout << "Desea eliminar otro nodo? (s/n): " <<endl;
            cin >> resp;
            if(resp != 'n'){
                cout << "Ingrese el codigo del nodo: "<<endl;
                cin >> codigo;
            }
        }
    }
    cout << "La lista completa es: "<<endl;
    cout << endl;
    l1.setApuntador();
    l1.reco_recur();
    l1.~Estudiantes();

}
