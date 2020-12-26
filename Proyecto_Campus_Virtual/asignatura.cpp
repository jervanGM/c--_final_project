#include<iostream>
#include"asignatura.h"
#include<cstring>

using namespace std;
//Constructores y metodos de la clase asignatura. El constructor parametrizado inicializa tambien los atributos de la clase padre
Asignatura::Asignatura(const string nombre_titulacion,const string nombre_asignatura,const int creditos,const string codigo_recurso,const string estado)
{
    _nombre_titulacion=nombre_titulacion;
    _nombre_asignatura=nombre_asignatura;
    _creditos=creditos;
    _codigo_recurso=codigo_recurso;
    _estado=estado;
    plaza_ocupada=false;//Variable usada en meter alumno

}
Asignatura::Asignatura(const Asignatura &As)//Constructor copia
{
   _nombre_asignatura=As._nombre_asignatura;
   _nombre_titulacion=As._nombre_titulacion;
   _creditos=As._creditos;
   _estado=As._estado;
   _codigo_recurso=As._codigo_recurso;
   plaza_ocupada=As.plaza_ocupada;
}
void Asignatura::setasignatura(string nombre_titulacion,string nombre_asignatura,int creditos, string codigo_recurso, string estado)
{
    _nombre_titulacion=nombre_titulacion;
    _nombre_asignatura=nombre_asignatura;
    _creditos=creditos;
    _codigo_recurso=codigo_recurso;
    _estado=estado;
}

void Asignatura::setnota(float nota,unsigned a)//Se le pasa la nota y posicion del alumno en la lista
{
    notas[a]=nota;
}
int Asignatura::comprobar_profesor_asignatura(string codigo_id)//Recibe el codigo del profesor
{
    int comprobar_profe=0;//Comprobante

    if(_uno==nullptr && _dos==nullptr)//Si no hay profesor
      {comprobar_profe=0;}

    else if(_uno->getcodigo()==codigo_id && comprobar_profe==0)//Comprobamos los codigos
      {comprobar_profe=1;}

    else if( _dos->getcodigo()==codigo_id && comprobar_profe==0)
      {comprobar_profe=1;}

    else{comprobar_profe=0;}

return comprobar_profe;//Devuelva el comprobante
}

void Asignatura::meter_profesores(Profesor &primero)
{//Funcion que permite asignar un profesor,lo mismo que la de meter_segundo
    _uno=&primero;
}

void Asignatura::meter_segundo(Profesor &segundo)
{
    _dos=&segundo;
}

void Asignatura::imprimir_profesores(){//Al llamarla, imprime los nombres de los profesores.Esto puede cambiarse para imprimir tambien los codigos
    if(_uno!=nullptr){//Si uno o los dos profesor no existen, solo se imprimiran por pantalla los existentes
    cout<<"Nombre primer profesor:"<<_uno->getnombre()<<endl;
    }
    if(_dos!=nullptr){
    cout<<"Nombre segundo profesor:"<<_dos->getnombre()<<endl;
    }
    if(_uno==nullptr || _dos==nullptr){
        cout<<"\n******Se necesita añadir dos profesores a esta asignatura******\n"<<endl;
    }
}

bool Asignatura::meter_alumno(Alumno* &lista)
{
    bool meter;

    if(_estado=="Finalizado" || _estado=="finalizado")//El alumno no puede inscribirse en una asignatura que ha finalizado
      {
       cout<<"La asignatura ha finalizado, no puede darse de alta"<<endl;
       meter=false;
      }
    else
      {
        for(unsigned p=0;p<lista_alumnos.size() && plaza_ocupada==false;p++)//Evita que el alumno se vuelva a incribir
           {
            if((*lista_alumnos[p])->getnia()==lista->getnia())
              {plaza_ocupada=true;}
            else{plaza_ocupada=false;}
           }

        if(plaza_ocupada==false)
          {/*Cada vez que se crea un nuevo alumno se genera un espacio en la lista de notas */
            lista_alumnos.push_back(&lista);
            notas.push_back(0);
            meter=true;
          }
         else
            {
             cout<<"Ya se encuentra registrado/a en esta asignatura"<<endl;
             meter=false;
            }
      }
    return meter;//Booleano utilizado en campus virtual
}

void Asignatura::cambiar_notas_alumnos(unsigned j)//Recibe la posicion del alumno que es la misma que la del vector notas
{
    float nota;
    cout<<"Nueva nota: ";
    cin>>nota;
    notas[j]=nota;

}

void Asignatura::expulsar_alumnos_asignatura()
{
    for(unsigned ex=0;ex<lista_alumnos.size();ex++)
       {
       (*lista_alumnos[ex])->darse_baja_asignatura(this->getasignatura_codigo());//Envia el codigo de la asignatura a la funcion darse de baja para eliminar la asignatura de la lista de los alumnos
       }
}
void Asignatura::comprobar_alumno_asignatura(string nia)
{
    bool found_nia=false;
    for(unsigned i=0;i<lista_alumnos.size() && found_nia==false;i++)//Recibe el nia y si coincide con alguno de la lista llama a la funcion para que lo elimine de la asignatura
       {
        if((*lista_alumnos[i])->getnia()==nia)
          {
            sacar_alumno(i);
            found_nia=true;
          }
        else{found_nia=false;}
    }
}

void Asignatura::sacar_alumno(unsigned a)
{
    lista_alumnos.erase(lista_alumnos.begin()+a);//Eliminamos el alumno que se ha dado de baja
}
void Asignatura::sacar_profesor(string codigo){
    if(_uno==nullptr){}
    else if(_uno->getcodigo()==codigo){
        _uno=nullptr;
    }
    if(_dos==nullptr){}
    else if(_dos->getcodigo()==codigo){
        _dos=nullptr;
    }

}
void Asignatura::imprimir_alumnos()
{
    if(lista_alumnos.size()>0)
    {
    for(unsigned i=0;i<lista_alumnos.size();i++){
        cout<<"Nombre alumno-"<<i+1<<": "<<(*lista_alumnos[i])->getnombre()<<endl;
        cout<<"Nombre titulacion del alumno-"<<i+1<<": "<<(*lista_alumnos[i])->getnombre_titulacion()<<endl;
        cout<<"NIA del alumno-"<<i+1<<": "<<(*lista_alumnos[i])->getnia()<<endl;
        cout<<"Nota del alumno-"<<i+1<<": "<<notas[i]<<endl;
    }
    }
    else{
        cout<<"******Deben añadirse alumnos a esta asignatura******"<<endl;
    }
}


string Asignatura::getasignatura_codigo()//Metodos get
{
    return _codigo_recurso;
}

string Asignatura::getestado()//funcion para devolver el estado del recurso
{
    return _estado;
}

string Asignatura::getnombre()
{
    return _nombre_asignatura;
}

string Asignatura::getnombre_titulacion()
{
    return _nombre_titulacion;
}

int Asignatura::getcreditos()
{
    return _creditos;
}


ofstream& operator<<(ofstream& salida,Asignatura* &lista)
{
  unsigned long tam=0;
  int exist=0;//Comprobar si hay primer profe
  int existencia=0;//Comprobar si hay segundo profe

  /*Pasamos los datos de la asignatura*/
  salida<<lista->_nombre_asignatura<<endl;
  salida<<lista->_codigo_recurso<<endl;
  salida<<lista->_creditos<<endl;
  salida<<lista->_nombre_titulacion<<endl;
  salida<<lista->_estado<<endl;

  if(lista->_uno!=nullptr)//Comprobamos si hay profesor
    {
     exist=1;
     salida<<exist<<endl;//Pasamos el valor de si existe y a continuacion los datos
     salida<<(*lista->_uno).getnombre()<<endl;
     salida<<(*lista->_uno).getcodigo()<<endl;
    }
  else{
       exist=0;
       salida<<exist<<endl;
      }
/*Igual que el anterior caso*/
  if(lista->_dos!=nullptr)
    {
     existencia=1;
     salida<<existencia<<endl;
     salida<<(*lista->_dos).getnombre()<<endl;
     salida<<(*lista->_dos).getcodigo()<<endl;
    }
  else{
       existencia=0;
       salida<<existencia<<endl;
      }

tam=lista->lista_alumnos.size();//Guardamos el tamaño de la lista alumnos
salida<<tam<<endl;//Pasamos el tamaño

  if(lista->lista_alumnos.size()>0)//Comrprobamos si hay alumnos en la asignatura
    {
     for(unsigned i=0;i<lista->lista_alumnos.size();i++)//Pasamos los datos de cada uno
        {
         salida<<(*lista->lista_alumnos[i])->getnombre()<<endl;
         salida<<(*lista->lista_alumnos[i])->getnia()<<endl;
         salida<<(*lista->lista_alumnos[i])->getnombre_titulacion()<<endl;
         salida<<lista->notas[i]<<endl;
        }
    }
return salida;
}

ifstream& operator>>(ifstream& entrada,Asignatura&lista){

        getline(entrada,lista._nombre_titulacion,'\n');
        entrada>>lista._codigo_recurso;
        entrada>>lista._creditos;
        entrada.ignore();
        getline(entrada,lista._nombre_asignatura,'\n');
        entrada>>lista._estado;
        return entrada;
}

void Asignatura::imprimir_asignatura(){
    cout<<"====================================================================="<<endl;
    cout<<"Nombre de la asignatura: "<<_nombre_asignatura<<endl;
    cout<<"Nombre de su titulacion: "<<_nombre_titulacion<<endl;
    cout<<"Codigo de la asignatura: "<<_codigo_recurso<<endl;
    cout<<"Creditos: "<<_creditos<<endl;
    cout<<"Estado: "<<_estado<<endl;
    cout<<"\nProfesores:"<<endl;
        imprimir_profesores();

    cout<<"\nAlumnos inscritos:"<<endl;
       imprimir_alumnos();
       cout<<"====================================================================="<<endl;
   }
