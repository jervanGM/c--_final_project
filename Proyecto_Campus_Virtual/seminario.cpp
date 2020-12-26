#include<iostream>
#include "seminario.h"
#include<cstring>

using namespace std;
//Constructor parametrizado y copia del seminario
Seminario::Seminario(const int dia,const int mes,const int anio,const int nplazas,const string codigo_recurso,const string estado)
{
    _dia=dia;
    _mes=mes;
    _anio=anio;
    _nplazas=nplazas;
    _codigo_recurso=codigo_recurso;
    _estado=estado;


}
Seminario::Seminario(const Seminario &S)
{
    _dia=S._dia;
    _mes=S._mes;
    _anio=S._anio;
    _nplazas=S._nplazas;
    _codigo_recurso=S._codigo_recurso;
    _estado=S._estado;
}
void Seminario::setseminario(int dia,int mes,int anio,string codigo_recurso,string estado,int nplazas)//Funcion dedicada para modificar
{
    _dia=dia;
    _mes=mes;
    _anio=anio;
    _codigo_recurso=codigo_recurso;
    _estado=estado;
    _nplazas=nplazas;
}
int Seminario::getdia()
{
    return _dia;
}

int Seminario::getmes()
{
    return _mes;
}

int Seminario::getanio()
{
    return _anio;
}

int Seminario::getplazas(){
    return _nplazas;
}

string Seminario::getseminario_codigo()
{
     return _codigo_recurso;
}

string Seminario::getestado(){
    return _estado;
}

unsigned Seminario::getplazasocupadas(){//Devuelve las plazas ocupadas del seminario, esta servirá para que no se introduzcan menos plazas de las ya ocupadas
    return lista_alumnos.size();
}

void Seminario::meter_ponente(Profesor &nuevoP)
{
    _ponente=&nuevoP;//Puntero que apunta a la direccion de memoria del profesor asignado
}
void Seminario::meter_profesor_responsable(Profesor &nuevoR)
{
    _p_responsable=&nuevoR;
}

int Seminario::comprobar_profesor_seminario(string codigo_id)
{
    int comprobar_profe=0;

    if(_ponente==nullptr && _p_responsable==nullptr)//Comprueba que los punteros esten o no vacios
      {comprobar_profe=0;}

    else if(_p_responsable->getcodigo()==codigo_id && comprobar_profe==0)//Comprueba si el profesor a operar coincide con alguno de los profesores del seminario
      {comprobar_profe=1;}

    else if(_ponente->getcodigo()==codigo_id && comprobar_profe==0)
      {comprobar_profe=1;}

    else
     {comprobar_profe=0;}

    return comprobar_profe;
}

bool Seminario::meter_alumnos(Alumno* &mis_alumnos)
{
    bool lleno=false;

    if(lista_alumnos.size()==_nplazas){//Comprueba si el seminario esta lleno
        cout<<"Seminario lleno"<<endl;
        lleno=true;
    }
    else if(_estado=="Finalizado" || _estado=="finalizado")//Si el seminario ha finalizado, el alumno no se podrá meter
    {
        cout<<"El seminario ha finalizado, no puede darse de alta"<<endl;
    }

    else
    {   bool plaza_ocupada=false;
        for(unsigned p=0;p<lista_alumnos.size() && plaza_ocupada==false;p++)
        {
            if((*lista_alumnos[p])->getnia()==mis_alumnos->getnia()){//Indica si el alumno ya se ha inscrito al seminario anteriormente

                plaza_ocupada=true;
            }
            else{
                plaza_ocupada=false;
            }
        }

        if(plaza_ocupada==false)//Si se cumplen correctamente las condiciones anteriores, entonces mete el alumno en el seminario
        {
            lista_alumnos.push_back(&mis_alumnos);

        }
        else
        {
             cout<<"Ya se encontraba registrado/a en este seminario"<<endl;
             lleno=true;
        }
    }
     return lleno;//Booleano que retorna si el seminario esta lleno o el alumno ya estaba registrado anteriormente
}

void Seminario::expulsar_alumnos_seminario()//Cuando el seminario es eliminario, los alumnos deben darse de baja automaticamente
{
    for(unsigned ex=0;ex<lista_alumnos.size();ex++)
       {
        (*lista_alumnos[ex])->darse_baja_seminario(this->getseminario_codigo());//Hacemos dar de baja en cada alumno del seminario
       }
}

void Seminario::comprobar_alumno_seminario(string nia)//Esta funcion es para cuando el alumno es eliminado, se tiene que dar de baja de/los seminario/s
{
    bool found_nia=false;
    for(unsigned i=0;i<lista_alumnos.size() && found_nia==false;i++)
       {
        if((*lista_alumnos[i])->getnia()==nia)
           {
            sacar_alumno(i);
            found_nia=true;
           }
        else{found_nia=false;}
    }
}
void Seminario::sacar_alumno(unsigned a)//Elimina con erase la posicion del alumno a darse de baja
{
    lista_alumnos.erase(lista_alumnos.begin()+a);
}

void Seminario::sacar_profesor(string codigo){//Comprueba si esta o no el profesor que hemos pasado
    if(_ponente==nullptr){}//Si no existe profesor, no se analiza esta parte
    else if(_ponente->getcodigo()==codigo){//Si existe profesor, el puntero que apunta a la memoria del profesor la ponemos a null
        _ponente=nullptr;
    }
    if(_p_responsable==nullptr){}//Proceso equivaente que con ponente
    else if(_p_responsable->getcodigo()==codigo){
        _p_responsable=nullptr;
    }

}

void Seminario::imprimir_alumnos()//Imprime los alumnos inscritos del seminario
{
    if(lista_alumnos.size()>0)
      {
       for(unsigned i=0;i<lista_alumnos.size();i++)
          {
            cout<<"Nombre alumno-"<<i+1<<": "<<(*lista_alumnos[i])->getnombre()<<endl;
            cout<<"Nombre titulacion del alumno-"<<i+1<<": "<<(*lista_alumnos[i])->getnombre_titulacion()<<endl;
            cout<<"NIA del alumno-"<<i+1<<": "<<(*lista_alumnos[i])->getnia()<<"\n"<<endl;
          }
       }
    else{cout<<"******Deben añadirse alumnos a este seminario******"<<endl;}
}



void Seminario::imprimir_seminario(){//Imprime y llama a las funciones de imprimir del seminario
     cout<<"==============================================================================="<<endl;
    cout<<"\nFecha seminario:"<<_dia<<"/"<<_mes<<"/"<<_anio<<endl;
    cout<<"Codigo del seminario:"<<_codigo_recurso<<endl;
    cout<<"Plazas totales:"<<_nplazas<<endl;
    cout<<"\nProfesores:"<<endl;
    if(_ponente!=nullptr){//Si existe el profesor o profesores, se imprimen, sino solo se imprimiran aquellos que si apunten a una direccion de memoria
        cout<<"Nombre ponente:"<<_ponente->getnombre()<<endl;
     }
    if(_p_responsable!=nullptr){
        cout<<"Nombre del profesor responsable:"<<_p_responsable->getnombre()<<endl;
    }
    else{
        cout<<"******Se necesita añadir dos profesores a este seminario******"<<endl;
    }
    cout<<"\nAlumnos inscritos:"<<endl;
      imprimir_alumnos();

    cout<<"==============================================================================="<<endl;
}



ostream& operator<<(ostream& salida,Seminario* &lista)//Funcion pasa todos los atributos y listas al fichero
{
 unsigned long tam=0;//Guardar el tamaño lista alumnos de seminario
 int exist;//Comprobar si hay ponenete
 int existencia;//Comprobar si hay responsable

 /*Pasamos los atributos de seminario*/
 salida<<lista->_dia<<endl;
 salida<<lista->_mes<<endl;
 salida<<lista->_anio<<endl;
 salida<<lista->_nplazas<<endl;
 salida<<lista->_codigo_recurso<<endl;
 salida<<lista->_estado<<endl;

  if(lista->_ponente!=nullptr)//Comprobamos si hay ponentes
    {
     exist=1;
     salida<<exist<<endl;//Pasamos el valor y a continuacion los datos
     salida<<(*lista->_ponente).getnombre()<<endl;
     salida<<(*lista->_ponente).getcodigo()<<endl;
    }
  else
    {
     exist=0;
     salida<<exist<<endl;
    }
/*Igual que el caso de ponente*/
  if(lista->_p_responsable!=nullptr)
    {
     existencia=1;
     salida<<existencia<<endl;
     salida<<(*lista->_p_responsable).getnombre()<<endl;
     salida<<(*lista->_p_responsable).getcodigo()<<endl;
    }
   else
     {
      existencia=0;
      salida<<existencia<<endl;
     }

tam=lista->lista_alumnos.size();//Almacenamos el valor
salida<<tam<<endl;//Lo enviamos

  if(lista->lista_alumnos.size()>0)//Vemos si hay alumnos
    {
     for(unsigned i=0;i<lista->lista_alumnos.size();i++)//Pasamos los datos de cada alumno
        {
         salida<<(*lista->lista_alumnos[i])->getnombre()<<endl;
         salida<<(*lista->lista_alumnos[i])->getnia()<<endl;
         salida<<(*lista->lista_alumnos[i])->getnombre_titulacion()<<endl;
        }
   }
return salida;
}

istream& operator>>(istream& entrada,Seminario& lista){//Operador solo lee del fiichero los atributos principales del seminario, las listas se leen despues de este operador en campus virtual

    entrada>>lista._dia;
    entrada>>lista._mes;
    entrada>>lista._anio;
    entrada>>lista._nplazas;
    entrada>>lista._codigo_recurso;
    entrada>>lista._estado;
    return entrada;
}
