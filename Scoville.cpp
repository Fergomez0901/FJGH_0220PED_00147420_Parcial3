#include <iostream>
using namespace std; 

enum Color{Verde, Amarillo, Naranja, Rojo};

struct Chile{
    string nombre; 
    int shu; 
    Color color; 
};

struct Nodo{
    struct Chile chile; 
    struct Nodo *izq; 
    struct Nodo *der; 
};
typedef struct Nodo *Arbol; 

Chile unChile; 

Arbol crearNodo(Chile chile)
{
    Arbol hijo = new Nodo; 
    hijo->chile = chile; 
    hijo->izq = NULL; 
    hijo->der = NULL; 
    return hijo; 
}

void agregarNodo(Arbol a, Chile chile)
{
    Arbol aux = a; 
    while(true)
    {
        if(aux->chile.shu == chile.shu)
        {
            cout << "No se puede agregar el pimiento porque ya existe en el arbol" << endl;
            break; 
        }
        else if(aux->chile.shu > chile.shu)
        {
            if(aux->izq == NULL)
            {
                aux->izq = crearNodo(chile);
                break; 
            }
            else
            {
                aux = aux->izq;
            }
        }
        else
        {
            if(aux->der == NULL)
            {
                aux->der = crearNodo(chile); 
                break; 
            }
            else
            {
                aux = aux->der; 
            }
        }
    }
}

void mostrarDatos(Chile chile)
{
    cout << endl << "Nombre del pimiento: " << chile.nombre << endl; 
    cout << "SHU del pimiento: " << chile.shu << endl; 
    cout << "Color del pimiento: ";

    switch(chile.color)
    {
        case Verde: cout << "Verde"; break; 
        case Amarillo: cout << "Amarillo"; break; 
        case Naranja: cout << "Naranja"; break; 
        case Rojo: cout << "Rojo"; break;
        default: break; 
    }
    cout << endl << endl; 
}

Color seleccionarColor()
{
    int opcion = 0; 
    cout << "***** COLORES DEL PIMIENTO *****" << endl; 
    cout << "1. Verde" << endl; 
    cout << "2. Amarillo" << endl; 
    cout << "3. Naranja" << endl; 
    cout << "4. Rojo" << endl; 
    cout << "Seleccione el color del pimiento: ";
    cin >> opcion; cin.ignore(); 

    switch(opcion)
    {
        case 1: return Verde; break; 
        case 2: return Amarillo; break; 
        case 3: return Naranja; break ;
        case 4: return Rojo; break; 
        default: cout << "Opcion invalida" << endl; break; 
    }
}

Chile solicitarDatos()
{
    unChile.shu = -1;
    cout << endl << "Ingrese el nombre del pimiento: "; getline(cin, unChile.nombre);
    while(unChile.shu < 0)
    {
        cout << "Ingrese el numero de unidades Scoville del pimiento (SHU): "; cin >> unChile.shu; cin.ignore(); 
    }
    cout << "Seleccionando color del pimiento..." << endl; 
    unChile.color = seleccionarColor();

    return unChile; 
}

void inOrden(Arbol a)
{
    if(a != NULL)
    {
        inOrden(a->izq);
        mostrarDatos(a->chile); 
        inOrden(a->der);
    }
}

void preOrden(Arbol a)
{
    if(a != NULL)
    {
        if(a->chile.color == Rojo)
        {
            mostrarDatos(a->chile); 
        }
        preOrden(a->izq); 
        preOrden(a->der);
    }
}

void postOrden(Arbol a)
{
    if(a != NULL)
    {
        postOrden(a->izq);
        postOrden(a->der);
        if(a->chile.shu > 50000)
        {
            mostrarDatos(a->chile); 
        }
    }
}

void menu(Arbol a)
{
    int opcion = 0; 
    bool status = true; 
    while(status)
    {
        cout << endl << "***** MENU DE PIMIENTOS *****" << endl; 
        cout << "1) Agregar un pimiento al arbol" << endl; 
        cout << "2) Mostrar todos los pimientos almacenados (In-orden)" << endl; 
        cout << "3) Mostrar unicamente los pimientos color rojo (Pre-orden)" << endl; 
        cout << "4) Mostrar unicamente los pimientos con unu SHU mayor a 50000 (Post-orden)" << endl; 
        cout << "5) Salir del programa" << endl; 
        cout << "Ingrese una opcion: ";     
        cin >> opcion; cin.ignore(); 

        switch(opcion)
        {
            case 1: agregarNodo(a, solicitarDatos()); break; 
            case 2: inOrden(a); break; 
            case 3: preOrden(a); break;
            case 4: postOrden(a);  break; 
            case 5: status = false; cout << "Fin del programa" << endl << endl; break; 
        }
    }
}

int main()
{
    cout << endl << "Creando arbol..." << endl; 
    cout << "Ingrese los datos de la raiz del arbol: " << endl; 
    Arbol arbol = crearNodo(solicitarDatos()); 
    menu(arbol);
    return 0; 
}