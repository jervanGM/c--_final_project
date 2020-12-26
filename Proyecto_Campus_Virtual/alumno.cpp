#include<iostream>
#include"alumno.h"
#include<cstring>

using namespace std;


Alumno::Alumno(const string nombre_alumno,const string nombre_titulacion,const string NIA,const string password){//Funciones no finalizadas.Se acabaran para el hito2
    _nombre_alumno=nombre_alumno;
    _nombre_titulacion=nombre_titulacion;
    _NIA=NIA;
    _mi_tfe=nullptr;
    _password=password;
    this->ocupado=false;//Atributo utilizado en meter tfe
}
Alumno::Alumno(const Alumno &A)
{
    _nombre_alumno=A._nombre_alumno;
    _nombre_titulacion=A._nombre_titulacion;
    _NIA=A._NIA;
    _password=A._password;
    this->ocupado=A.ocupado;
}

string Alumno::getnombre()
{
    return _nombre_alumno;
}

string Alumno::getnombre_titulacion()//Funciones de imprimir,retornan el atributo correspondiente
{
    return _nombre_titulacion;
}

string Alumno::getnia()
{
    return _NIA;
}

void Alumno::setalumno(string nombre_alumno,string nombre_titulacion,string NIA)//Funcion para modificar la clase
{
    _nombre_alumno=nombre_alumno;
    _nombre_titulacion=nombre_titulacion;
    _NIA=NIA;
}


void Alumno::aniadir_seminario(Seminario* &seminario)
{
   lista_semi.push_back(&seminario);//Añade a la ultima posicion del vector el objeto
}

void Alumno::darse_baja_seminario(string expulsar)//Se le pasa el codigo y se busca el seminario en lista semi
{
    bool found=false;

    for(unsigned b=0;b<lista_semi.size() && found==false;b++)
       {
        if(expulsar==(*lista_semi[b])->getseminario_codigo())
          {
           lista_semi.erase(lista_semi.begin()+b);//Elimina el objeto de la lista semi del alumno
           found=true;
          }
        else{found=false;}
       }
}

void Alumno::aniadir_asignatura(Asignatura* &lista)//Se le pasa la asignatura a la que se quiere añadir
{
    lista_asign.push_back(&lista);//Se hace un pushback para almacenarla en la ultima posicion del vector
}

void Alumno::darse_baja_asignatura(string expulsar)//Se le pasa el codigo y se busca la asignatura en lista asign
{
  bool found=false;
  for(unsigned b=0;b<lista_asign.size() && found==false;b++)
     {
      if(expulsar==(*lista_asign[b])->getasignatura_codigo())
        {
         lista_asign.erase(lista_asign.begin()+b);//Elimina el objeto deseado por el usuario
         found=true;
        }
      else{found=false;}
    }
}

void Alumno::aniadir_tfe(Tfe* &unico)//Permite que el alumno no se inscriba en otro tfe
{
    if(ocupado==false)
      {
        _mi_tfe=&unico;
        ocupado=true;
       }
    else{cout<<"Este alumno ya se ha inscrito anteriormente a un tfe"<<endl;}
}

void Alumno::darse_baja_tfe(string expulsar)
{
    if(expulsar==(*_mi_tfe)->gettfe_codigo())//Se le pasa el codigo y se busca si coincide con el tfe inscrito
      {
        _mi_tfe=nullptr;//Al darse baja, el tfe lo pasa a vacio
        delete _mi_tfe;
        ocupado=false;
    }
}

void Alumno::comprobar_codigo_id(string &codigo_id)//Comprobar NIA
{
        int c=0;//Comprobar NIA
    do{
        do{
            cout<<"Introduce su NIA:";
               cin>>codigo_id;

            if(codigo_id.size()!=7)
              {
               cout<<"El NIA debe tener 7 digitos"<<endl;
              }
           else
             {
              for(unsigned i=0;i<7;i++)
                 {
                  if(codigo_id[i]>=48 && codigo_id[i]<=57)
                    {
                     c=0;
                    }
                  else
                    {
                     c=1;
                    }
                }
            if(c==1)
              {
               cout<<"Error, el NIA debe contener solo digitos"<<endl;
              }
            else{continue;}
           }
          }while(c==1);
        }while(codigo_id.size()!=7);
}

void Alumno::expulsar_alumno()
{
    for(unsigned s=0;s<lista_semi.size();s++)
       {(*lista_semi[s])->comprobar_alumno_seminario(this->getnia());}//le pasamos el nia a la funcion y en ella se comprueba si el alumno esta

    for(unsigned a=0;a<lista_asign.size();a++)
       {(*lista_asign[a])->comprobar_alumno_asignatura(this->getnia());}//le pasamos el nia a la funcion y en ella se comprueba si el alumno esta

    (*_mi_tfe)->sacar_alumno();//como solo hay un alumno  y un tfe correspodiente pues se le llama a la funcion directamente
}

void Alumno::imprimir_listas(){//Imprime los recursos del alumno
    if(lista_semi.size()>0)
      {
        cout<<"\nSeminarios inscritos por el Alumno:"<<endl;
        for(unsigned i=0;i<lista_semi.size();i++)
           {
            cout<<"Fecha seminario:"<<(*lista_semi[i])->getdia()<<"/"<<(*lista_semi[i])->getmes()<<"/"<<(*lista_semi[i])->getanio()<<endl;
            cout<<"Codigo del seminario:"<<(*lista_semi[i])->getseminario_codigo()<<endl;
            cout<<"Plazas del seminario:"<<(*lista_semi[i])->getplazas()<<endl;
          }
      }
    else{cout<<"\n****Este alumno no se ha inscrito a ningun seminario****"<<endl;}

    if(lista_asign.size()>0)
      {
       cout<<"\nAsignaturas que se ha inscrito el alumno:"<<endl;
       for(unsigned i=0;i<lista_asign.size();i++){
       cout<<"Nombre asignatura:"<<(*lista_asign[i])->getnombre()<<endl;
       cout<<"Titulacion de la asignatura:"<<(*lista_asign[i])->getnombre_titulacion()<<endl;
       cout<<"Codigo del seminario:"<<(*lista_asign[i])->getasignatura_codigo()<<endl;
       cout<<"Creditos de la asignatura: "<<(*lista_asign[i])->getcreditos()<<endl;
       cout<<"Estado de la asignatura:"<<(*lista_asign[i])->getestado()<<endl;
      }
    }
    else{cout<<"\n****Este alumno no se ha inscrito a ninguna asignatura****"<<endl;}

    if(_mi_tfe!=nullptr)
      {//Si existe un tfe inscrito,lo imprime
        cout<<"\nTfe del alumno:"<<endl;
        cout<<"Nombre titulacion:"<<(*_mi_tfe)->gettfe()<<endl;
        cout<<"Codigo del tfe:"<<(*_mi_tfe)->gettfe_codigo()<<endl;
        cout<<"Estado del tfe:"<<(*_mi_tfe)->get_estado()<<endl;
       }
    else{cout<<"\n****Este alumno aun no se ha inscrito a ningun tfe****"<<endl;}

}
//Mete el codigo en la ultima posicion del comprobante para que luego se use este atributo al meter los seminarios en la lista semi del alumno
void Alumno::fichero_seminario(string codigo)
{
  _comprobante_semi.push_back(codigo);
}

void Alumno::fichero_asignatura(string codigo)
{
    _comprobante_asign.push_back(codigo);
}

void Alumno::fichero_tfe(string codigo)
{
    _comprobante_tfe=codigo;
}
string Alumno::getcomprobante_semi(unsigned c)
{
    return _comprobante_semi[c];
}

string Alumno::getcomprobante_asign(unsigned a)
{
    return _comprobante_asign[a];
}

string Alumno::getcomprobante_tfe()
{
    return _comprobante_tfe;
}

unsigned long Alumno::gettamanio_comprobante()
{
    return _comprobante_semi.size();
}

unsigned long Alumno::gettamanio_comprobante2()
{
    return _comprobante_asign.size();
}

ofstream& operator<<(ofstream& salida,Alumno*&lista)
{
  unsigned long tam=0;//Tamaño lista seminarios
  unsigned long tam2=0;//Tamaño lista asignaturas
  int existencia=0;//Para ver si existe tfe

  salida<<lista->_nombre_alumno<<endl;
  salida<<lista->_NIA<<endl;
  salida<<lista->_nombre_titulacion<<endl;
  salida<<lista->_password<<endl;
  tam=lista->lista_semi.size();//Guardamos el tamaño
  salida<<tam<<endl;//Pasamos el tamaño

  if(lista->lista_semi.size()>0)//Comprobar que hay seminarios en la lista
    {
      for(unsigned i=0;i<lista->lista_semi.size();i++)//Sacamos los parametros de la lista seminario
         {
          salida<<(*lista->lista_semi[i])->getdia()<<endl;
          salida<<(*lista->lista_semi[i])->getmes()<<endl;
          salida<<(*lista->lista_semi[i])->getanio()<<endl;
          salida<<(*lista->lista_semi[i])->getseminario_codigo()<<endl;
          salida<<(*lista->lista_semi[i])->getplazas()<<endl;
         }
    }
  tam2=lista->lista_asign.size();//Guardamos el tamaño
  salida<<tam2<<endl;//Pasamos el tamaño

  if(lista->lista_asign.size()>0)//Comprobar que hay asignaturas en la lista
    {
     for(unsigned i=0;i<lista->lista_asign.size();i++)//Sacamos los parametros de la lista asignaturas
        {
         salida<<(*lista->lista_asign[i])->getnombre()<<endl;
         salida<<(*lista->lista_asign[i])->getnombre_titulacion()<<endl;
         salida<<(*lista->lista_asign[i])->getasignatura_codigo()<<endl;
         salida<<(*lista->lista_asign[i])->getestado()<<endl;
         salida<<(*lista->lista_asign[i])->getcreditos()<<endl;
        }
    }

   if(lista->_mi_tfe!=nullptr)//Comprobamos si hay un tfe
     {
      existencia=1;
      salida<<existencia<<endl;//Mandamos si hay un tfe o no
      salida<<(*lista->_mi_tfe)->gettfe()<<endl;//Sacamos todos los datos del tfe
      salida<<(*lista->_mi_tfe)->gettfe_codigo()<<endl;
      salida<<(*lista->_mi_tfe)->get_estado()<<endl;
     }
   else
     {
      existencia=0;
      salida<<existencia<<endl;
     }
return salida;
}

ifstream& operator>>(ifstream& entrada,Alumno &lista)
{
    getline(entrada,lista._nombre_alumno);
    entrada>>lista._NIA;
    entrada.ignore();
    getline(entrada,lista._nombre_titulacion);
    getline(entrada,lista._password);

return entrada;
}

