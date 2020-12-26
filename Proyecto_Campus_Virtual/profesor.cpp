#include<iostream>
#include"profesor.h"
#include<cstring>
#include"nota.h"

using namespace std;
string comprobar_codigo_recurso_2(string codigo_recurso);

Profesor::Profesor(const string nombre_profesor,const string codigo_id)//Constructores y metodos de la clase Profesor,su contenido es provisional
{
    _nombre_profesor=nombre_profesor;
    _codigo_id=codigo_id;
    _password.clear();
}

Profesor::Profesor(const Profesor &P){//Debido a este constructor el atributo codigo_id de usuario tuvo que ser puesto como protected
    _nombre_profesor=P._nombre_profesor;
    _codigo_id=P._codigo_id;
    _password=P._password;
}

void Profesor::setprofesor(string nombre_profesor,string codigo_id){
    _nombre_profesor=nombre_profesor;
    _codigo_id=codigo_id;

}
string Profesor::getcodigo()
{
    return _codigo_id;
}

void Profesor::cambiar_notas(Asignatura* &datos,unsigned j)
{
       datos->cambiar_notas_alumnos(j);
}

string Profesor::getnombre()
{
    return _nombre_profesor;
}
/*Misma funcion que la de modificar del menu admin pero solo se pasa el seminario porque posicion se elige antes y en modificar asignatura y tfe igual*/
void Profesor::modificar_Seminario(vector<Seminario*>&modificar,unsigned s)//El proceso de recogida de datos es equivalente al de dar alta
{
    unsigned nplazas;//Las funciones modificar puede que para la entrega final se compriman,cambiando el codigo
    int dia;
    int mes;
    int anio;
    bool igual=false;
    string nuevo_codigo_recurso;
    string estado;

        do{//La fecha tendra restricciones de dia y mes
           cout<<"Introduce un nuevo dia: ";
           cin>>dia;
        }while(dia>31);

        do{
           cout<<"Introduce un nuevo mes: ";
           cin>>mes;
        }while(mes>12);

        cout<<"Introduce un nuevo año: ";
        cin>>anio;

        do{//Esta funcion indica que si hay ya alumnos inscritos en el seminario,no puedas bajar del numero de alumnos inscritos al mismo
        cout<<"Introduce el numero de plazas: ";
        cin>>nplazas;

        if(nplazas<modificar[s]->getplazasocupadas())
          {cout<<"\n***El numero de plazas debe ser igual o mayor al numero de alumnos inscritos al seminario***\n"<<endl;}

        }while(nplazas<modificar[s]->getplazasocupadas());

        do{//Funcion de control de estado
           cout<<"Introduce estado del Seminario(creado,iniciado o finalizado):";
           cin>>estado;
         }while(estado!="creado" && estado!="iniciado" && estado!="finalizado");

        do{
          nuevo_codigo_recurso=comprobar_codigo_recurso_2(nuevo_codigo_recurso);
          igual=false;
          for(unsigned i=0;i<modificar.size() && igual==false;i++)
             {
              if(nuevo_codigo_recurso==modificar[i]->getseminario_codigo())
                {igual=true;}
              else{igual=false;}
             }
          if(igual==true)
            {cout<<"Este codigo ya es de otro seminario"<<endl;}
          }while(igual==true);

        //En este caso, usamos un objeto para llamar a la funcion set, asi poder modificar sus atributos
        modificar[s]->setseminario(dia, mes,anio,nuevo_codigo_recurso,estado,nplazas);
}
void Profesor::modificar_Asignatura(vector<Asignatura*>&modificar,unsigned as)
{
    string nombre_titulacion;
    string nombre_asignatura;
    int creditos;
    bool igual=false;
    string estado;
    string nuevo_codigo_recurso;

        cout<<"Introduce el nuevo nombre de la titulacion: ";
        cin.ignore();
        getline(cin,nombre_titulacion);

        cout<<"Introduce el nuevo nombre de la asignatura: ";
        getline(cin,nombre_asignatura);

        cout<<"Introduce nuevos creditos: ";
        cin>>creditos;

        do{
           cout<<"Introduce estado de la Asignatura(creado,iniciado o finalizado):";
           cin>>estado;
        }while(estado=="creado" && estado=="iniciado" && estado=="finalizado");

        do{
          nuevo_codigo_recurso=comprobar_codigo_recurso_2(nuevo_codigo_recurso);
          igual=false;
          for(unsigned i=0;i<modificar.size() && igual==false;i++)
             {
              if(nuevo_codigo_recurso==modificar[i]->getasignatura_codigo())
                {igual=true;}
              else{igual=false;}
             }
          if(igual==true)
            {cout<<"Este codigo ya es de otra asignaturar"<<endl;}

        }while(igual==true);

    modificar[as]->setasignatura(nombre_asignatura,nombre_titulacion,creditos,nuevo_codigo_recurso,estado);
}
void Profesor::modificar_Tfe(vector<Tfe*>&modificar,unsigned t)
{
    string nuevo_codigo_recurso;
    string nombre_tfe;
    string nuevo_estado;
    bool igual=false;

        cout<<"Introduce el nombre de la titulacion: ";
        cin.ignore();
        getline(cin,nombre_tfe);

        do{
          cout<<"Introduce estado el Tfe(creado,iniciado o finalizado):";
          cin>>nuevo_estado;
         }while(nuevo_estado=="creado" && nuevo_estado=="iniciado" && nuevo_estado=="finalizado");

        do{
          nuevo_codigo_recurso=comprobar_codigo_recurso_2(nuevo_codigo_recurso);
          igual=false;
          for(unsigned i=0;i<modificar.size() && igual==false;i++)
             {
              if(nuevo_codigo_recurso==modificar[i]->gettfe_codigo())
                {igual=true;}
              else{igual=false;}
             }
          if(igual==true)
            {cout<<"Este codigo ya es de otro tfe"<<endl;}
        }while(igual==true);

    modificar[t]->settfe(nombre_tfe,nuevo_codigo_recurso,nuevo_estado);

}

string comprobar_codigo_recurso_2(string codigo_recurso)//Funcion para comprobar que el codigo del recurso este correcto
{
    int c=0;//Variable para el codigo parte de letras
    int b=0;//Variable para comprobar codigo parte numerica
    do{
        cout<<"Introduce codigo: ";
        cin>>codigo_recurso;

        if(codigo_recurso.size()!=7)//Si el codigo es mayor o menor que 7, imprime el mensaje
          {
           cout<<"El codigo debe tener un maximo de 7 espacios"<<endl;
          }
        else
          {
           for(unsigned i=0;i<3;i++)//Esta parte permite que los primeros caracteres del codigo sean 3 letras y los ultimos sean 4 numeros.Para ello,usa ASCII
              {
                if((codigo_recurso[i]>64 && codigo_recurso[i]<91) || (codigo_recurso[i]>96 && codigo_recurso[i]<123))
                {
                 c=c+1;
                }
                else{c=0;}
              }

            for(unsigned i=3;i<7;i++)
               {
                if(codigo_recurso[i]>47 && codigo_recurso[i]<58)
                  {b=b+1;}
                else{b=0;}
               }
            if(c<3)
            {
             cout<<"El codigo debe tener 3 digitos"<<endl;
            }
            else if(b<4)
            {cout<<"El codigo debe tener 4 digitos"<<endl;}
          }
      }while(c<3 || b<4);

    return codigo_recurso;
}
void Profesor::comprobar_codigo_id(string &codigo_id)//Analizamos el codigo del profesor
{
    do{
        cout<<"Codigo de identificacion:";
        getline(cin,codigo_id);
        if(codigo_id.size()!=7)
          {cout<<"El codigo debe contener 7 caracteres"<<endl;}
    }while(codigo_id.size()!=7);
}

void Profesor::eliminar_profesor_recursos(vector<Seminario*>&lista_semi,vector<Asignatura*>&lista_asign,vector<Tfe*>&lista_tfe){
    for(unsigned i=0;i<lista_semi.size();i++){
           lista_semi[i]->sacar_profesor(_codigo_id);//Pasa el codigo a todos los recurso para comprobar si es o no de ese recurso
    }
    for(unsigned i=0;i<lista_asign.size();i++){
           lista_asign[i]->sacar_profesor(_codigo_id);
    }
    for(unsigned i=0;i<lista_tfe.size();i++){
           lista_tfe[i]->sacar_profesor(_codigo_id);
    }
}
ostream& operator<<(ostream& salida,const Profesor& lista)//Pasa al fichero los atributos del profesor
{
  salida<<lista._nombre_profesor<<endl;
  salida<<lista._codigo_id<<endl;
  salida<<lista._password<<endl;

return salida;
}



istream& operator>>(istream& entrada,Profesor&lista)//Lee del fichero los atributos del profesor
{
  getline(entrada,lista._nombre_profesor);
  entrada>>lista._codigo_id;
  entrada.ignore();
  entrada>>lista._password;

return entrada;
}
