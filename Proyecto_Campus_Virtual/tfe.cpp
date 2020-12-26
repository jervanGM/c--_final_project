#include<iostream>
#include"tfe.h"
#include<cstring>

using namespace std;

Tfe::Tfe(const string titulacion, const string codigo_recurso,const string estado)
{//Constructores y metodos de la clase tfe
    _titulacion=titulacion;
    _codigo_recurso=codigo_recurso;
    _estado=estado;
    _ocupado=false;
}

Tfe::Tfe(const Tfe &T)
{
    _titulacion=T._titulacion;
    _codigo_recurso=T._codigo_recurso;
    _estado=T._estado;
    _ocupado=T._ocupado;
}

void Tfe::settfe(string nombre_tfe,string codigo_recurso,string estado)
{
    _titulacion=nombre_tfe;
    _codigo_recurso=codigo_recurso;
    _estado=estado;
}

string Tfe::gettfe()
{
    return _titulacion;
}

string Tfe::get_estado()
{
    return _estado;
}
string Tfe::gettfe_codigo()
{
    return _codigo_recurso;
}

void Tfe::meter_tutor(Profesor &Tut)//Metemos apuntando por direcciones de memoria el profe tutor
{   _tutor=&Tut;
}

void Tfe::meter_cotutor(Profesor &C)//Igual que antes
{    _cotutor=&C;
}

int Tfe::comprobar_profesor_tfe(string codigo_id)//Le pasamos el codigo del profe
{
    int comprobar_profe=0;//Comprobante

    if(_tutor==nullptr && _cotutor==nullptr)//Opcion de si estan vacios los punteros
      {comprobar_profe=0;}

    else if(_tutor->getcodigo()==codigo_id && comprobar_profe==0)
      {comprobar_profe=1;}

    else if(_cotutor->getcodigo()==codigo_id && comprobar_profe==0)
      {comprobar_profe=1;}

    else{comprobar_profe=0;}

    return comprobar_profe;//Devolvemos el comprobante
}

bool Tfe::meter_alumno(Alumno* &al)
{
    if(_ocupado==true)
      {_disponible=false;}

    else{_disponible=true;}

    if(_ocupado==true)
      {cout<<"\nEste Tfe ya lo ha ocupado otro alumno"<<endl;}

    else
      {
        mi_alumno=&al;//Metemos el alumno que pasamos
       _ocupado=true;//Ponemos a true por la primera opcion
      }

    return _disponible;//devolvemos el booleano disponible para comprobar fuera de la funcion si esta libre o no
}

void Tfe::sacar_alumno()
{  if(mi_alumno==nullptr){}
    else{
    mi_alumno=nullptr;//Convierte al objeto alumno en vacio
    _ocupado=false;
    }
}

void Tfe::sacar_profesor(string codigo){
    if(_tutor==nullptr){}
    else if(_tutor->getcodigo()==codigo){
        _tutor=nullptr;
    }
    if(_cotutor==nullptr){}
    else if(_cotutor->getcodigo()==codigo){
        _cotutor=nullptr;
    }

}

void Tfe::expulsar_alumno()
{
  (*mi_alumno)->darse_baja_tfe(this->gettfe_codigo());//Damos de baja al alumno
}
void Tfe::imprimir_alumno()
{
    if(mi_alumno==nullptr)//Caso en el que no halla nadie en el tfe
      {cout<<"******Todavia no hay alumnos registrados en este Tfe******"<<endl;}
    else{
        cout<<"Nombre del alumno:"<<(*mi_alumno)->getnombre()<<endl;

    }
}
void Tfe::imprimir_tutores()
{
    cout<<"Nombre tutor:"<<this->_tutor->getnombre()<<endl;
    if(_cotutor!=nullptr)
      {
       cout<<"Nombre cotutor:"<<this->_cotutor->getnombre()<<endl;
       }

}

void Tfe::imprimir_tfe()
{
    cout<<"======================================================="<<endl;
    cout<<"Titulacion del Tfe:"<<_titulacion<<endl;
    cout<<"Estado:"<<_estado<<endl;
    cout<<"Codigo del Tfe:"<<_codigo_recurso<<endl;
    cout<<"\nProfesores:"<<endl;

    if(_tutor!=nullptr)
      {imprimir_tutores();}//Aqui imprimimos los tutores
    else{cout<<"Debe añadir un tutor a este tfe"<<endl;}

    cout<<"\nAlumno inscrito:"<<endl;
        imprimir_alumno();//Imprimimos el alumno del tfe
    cout<<"======================================================="<<endl;
}

ofstream& operator<<(ofstream& salida,Tfe* &lista)
{
 int tutor=0;//Comprobar si hay tutor
 int cotutor=0;//Comprobar si hay cotutor
 int alumno=0;//Comprobar si hay alumno

 /*Pasamos los datos del tfe*/
  salida<<lista->_titulacion<<endl;
  salida<<lista->_codigo_recurso<<endl;
  salida<<lista->_estado<<endl;

  if(lista->_tutor!=nullptr)//Vemos si hay tutor
    {
     tutor=1;
     salida<<tutor<<endl;//Pasamos el valor y a continuacion los datos de este
     salida<<(*lista->_tutor).getnombre()<<endl;
     salida<<(*lista->_tutor).getcodigo()<<endl;
    }
  else
    {
     tutor=0;
     salida<<tutor<<endl;
    }
/*Igual que para tutor*/
  if(lista->_cotutor!=nullptr)
    {
     cotutor=1;
     salida<<cotutor<<endl;
     salida<<(*lista->_cotutor).getnombre()<<endl;
     salida<<(*lista->_cotutor).getcodigo()<<endl;
    }
 else
   {
    cotutor=0;
    salida<<cotutor<<endl;
   }

 if(lista->mi_alumno!=nullptr)//Vemos si hay alumnos
   {
    alumno=1;
    salida<<alumno<<endl;//Pasamos el valor y a continuacion los datos de este
    salida<<(*lista->mi_alumno)->getnombre()<<endl;
    salida<<(*lista->mi_alumno)->getnia()<<endl;
    salida<<(*lista->mi_alumno)->getnombre_titulacion()<<endl;
   }
 else
   {
    alumno=0;
    salida<<alumno<<endl;
   }
return salida;
}

ifstream& operator>>(ifstream& entrada,Tfe&lista){
        getline(entrada,lista._titulacion);
        entrada>>lista._codigo_recurso;
        entrada>>lista._estado;
        return entrada;
}
