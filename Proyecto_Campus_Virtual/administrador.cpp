#include "administrador.h"
#include <iostream>
#include <cstring>

using namespace std;
string comprobar_codigo_recurso(string codigo_recurso);

Administrador::Administrador(const string nombre_admin,const string codigo_id)//Constructor parametrizado,uso en la creacion de administradores
{
    _nombre_admin=nombre_admin;
    _codigo_id=codigo_id;
    _password.clear();
}
Administrador::Administrador(const Administrador &Admin)//Constructor copia,uso en la creacion y modificacion de administradores
{
    _nombre_admin=Admin._nombre_admin;
    _codigo_id=Admin._codigo_id;
    _password=Admin._password;
}
//Funciones get para imprimir y set para modificar.Este criterio se aplica al resto de los set y get de las clases
string Administrador::getnombre()
{
    return _nombre_admin;
}

string  Administrador::getcode()
{
    return _codigo_id;
}

void Administrador::setadmin(string nombre_admin,string codigo_id)
{
    _nombre_admin=nombre_admin;
    _codigo_id=codigo_id;
}

void Administrador::dar_alta_Seminario(vector<Seminario*>&lista)
{
    int dia,mes,anio,plazas;
    string codigo_recurso;
    string estado;
    bool igual=false;//Se usa para ver si se repite el codigo del recurso o no

    cout<<"Introduce datos: "<<endl;
    do{
        cout<<"Dia:";
        cin>>dia;
    }while(dia>31);

    do{
        cout<<"Mes:";
        cin>>mes;
    }while(mes>12);

    cout<<"Año:";
    cin>>anio;

    cout<<"Introduce el numero de plazas: ";
    cin>>plazas;
    do{
        cout<<"Introduce estado del Seminario(creado,iniciado o finalizado):";
        cin>>estado;
    }while(estado!="creado" && estado!="iniciado" && estado!="finalizado");

    do{
        codigo_recurso=comprobar_codigo_recurso(codigo_recurso);//Llamamos a la funcion para comprobar codigo
        igual=false;
    /*Esto for se hace para que no se pueda repetir el codigo*/
        for(unsigned i=0;i<lista.size() && igual==false;i++)
           {
            if(codigo_recurso==lista[i]->getseminario_codigo())
              {igual=true;}

            else{igual=false;}
           }
        if(igual==true)
          {cout<<"Este codigo ya es de otro seminario"<<endl;}

     }while(igual==true);
lista.push_back(new Seminario(dia,mes,anio,plazas,codigo_recurso,estado));//El new crea espacio de memorio para meter los datos del nuevo seminario y el pushback los almacena en la ultima posicion del vector
}/*El resto de las funciones crear recursos siguen la misma idea que esta*/


void Administrador::dar_baja_Seminario(vector<Seminario*>&baja,unsigned a)
{
       baja.erase(baja.begin()+a);//Funcion erase del vector, elimina el objeto que el usuario desea eliminar.
}/*El resto de las funciones dar baja son iguales a esta, pero con su correspondiente vector*/

void Administrador::modificar_Seminario(vector<Seminario*>&modificar,unsigned s)//El proceso de recogida de datos es equivalente al de dar alta
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
          nuevo_codigo_recurso=comprobar_codigo_recurso(nuevo_codigo_recurso);
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

void Administrador::meter_profesores_seminario(Seminario* &lista,vector<Profesor>&lista_profe)
{
    char profesor;//Por si quieres añadir profesores o no
    unsigned profe=0;
    char validar;//Escoger el profesor
    do{
        cout<<"¿Desdea añadir profesores al seminario?(s/n):";
        cin.ignore();
        cin.get(profesor);
        if(profesor=='s')
          {
            if(lista_profe.size()<2)//Si no hay dos profesores, luego los podra añadir en modificar recurso
            {
             cout<<"No hay profesores para añadir, debes agregar al menos dos profesores"<<endl;
            }
            else{
                cout<<endl;
                for(unsigned p=0;p<lista_profe.size();p++)//for que lee los profesores para elegir cual meter
                   {
                    cout<<"Nombre del profesor["<<p<<"]:"<<lista_profe[p].getnombre()<<endl;
                    cout<<"Usuario del profesor["<<p<<"]:"<<lista_profe[p].getcodigo()<<endl;
                    cout<<"============================================="<<endl;
                   }
                cout<<endl;

                do{//Evitar que se escoga un numero mayor de los profes que hay
                    do{//Evitar que se escoga algo que no sea un numero
                        cout<<"Introduce el numero del profesor como ponente:";
                        cin.ignore(1000,'\n');
                        cin.get(validar);
                    }while(validar<48 || validar>57);
                    profe=validar-48;//Guardamos la posicion
                }while(profe>lista_profe.size()-1);

               lista->meter_ponente(lista_profe[profe]);
              }

             do{
                do{
                    cout<<"Introduce el numero del profesor como profesor responsable:";
                    cin.ignore();
                    cin.get(validar);
                  }while(validar<48 || validar>57);
                  profe=validar-48;
              }while(profe>lista_profe.size()-1);

            lista->meter_profesor_responsable(lista_profe[profe]);//Llamamos a la funcion de meter profesores y le pasamos la posicion del profesor elegido
          }
        else{continue;}

    }while(profesor!='s' && profesor !='n');
}

void Administrador::dar_alta_Asignatura(vector<Asignatura*>&lista)
{
    string codigo_recurso;
    string nombre_titulacion;
    string nombre_asignatura;
    string estado;
    int creditos;
    bool igual=false;

         cout<<"Introduce datos: "<<endl;

         cout<<"Introduce el nombre de la titulacion: ";
         cin.ignore();
         getline(cin,nombre_titulacion);

         cout<<"Introduce el nombre de la asignatura: ";
         getline(cin,nombre_asignatura);

         cout<<"Introduce creditos: ";
         cin>>creditos;

         do{
            cout<<"Introduce estado de la Asignatura(creado,iniciado o finalizado):";
            cin>>estado;
          }while(estado=="creado" && estado=="iniciado" && estado=="finalizado");

         do{
           codigo_recurso=comprobar_codigo_recurso(codigo_recurso);
           igual=false;
           for(unsigned i=0;i<lista.size() && igual==false;i++)
              {
               if(codigo_recurso==lista[i]->getasignatura_codigo())
                 {igual=true;}
               else{igual=false;}
              }
           if(igual==true)
             {cout<<"Este codigo ya es de otra asignatura"<<endl;}

         }while(igual==true);

         lista.push_back(new Asignatura(nombre_titulacion,nombre_asignatura,creditos,codigo_recurso,estado));
}

void Administrador::dar_baja_Asignatura(vector<Asignatura*>&baja,unsigned a)
{
    baja.erase(baja.begin()+a);
}

void Administrador::modificar_Asignatura(vector<Asignatura*>&modificar,unsigned as)
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
          nuevo_codigo_recurso=comprobar_codigo_recurso(nuevo_codigo_recurso);
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

/*Igual que meter profesor en seminario*/
void Administrador::meter_profesores_asignatura(Asignatura* &lista,vector<Profesor>&lista_profe){

    string codigo_recurso;
    char profesor;
    unsigned profe=0;
    char validar;
    do{
        cout<<"¿Desdea añadir profesores a la asignatura?(s/n):";
        cin.ignore();
        cin.get(profesor);
        if(profesor=='s')
          {
            if(lista_profe.size()<2)//Si no hay dos profesores, luego los podra añadir en modificar recurso
              {cout<<"No hay profesores para añadir, debes agregar al menos dos profesores"<<endl;}
            else
              {
               cout<<endl;
               for(unsigned p=0;p<lista_profe.size();p++)
                  {
                   cout<<"Nombre del profesor["<<p<<"]:"<<lista_profe[p].getnombre()<<endl;
                   cout<<"Usuario del profesor["<<p<<"]:"<<lista_profe[p].getcodigo()<<endl;
                   cout<<"============================================="<<endl;
                  }
                cout<<endl;

                do{
                    do{
                        cout<<"Introduce el numero del profesor como primer profesor:";
                        cin.ignore(1000,'\n');
                        cin.get(validar);
                    }while(validar<48 || validar>57);
                    profe=validar-48;
                }while(profe>lista_profe.size()-1);

             lista->meter_profesores(lista_profe[profe]);
            }

            do{
                do{
                   cout<<"Introduce el numero del profesor como segundo profesor:";
                   cin.ignore();
                   cin.get(validar);
                }while(validar<48 || validar>57);
                profe=validar-48;
            }while(profe>lista_profe.size()-1);

          lista->meter_segundo(lista_profe[profe]);

          }
        else{continue;}

    }while(profesor!='s' && profesor !='n');
}

void Administrador::dar_alta_Tfe(vector<Tfe*>&lista)
{      string nombre_tfe;
       string codigo_recurso;
       string estado;
       bool igual=false;

          cout<<"Introduce datos:"<<endl;
          cout<<"Nombre titulacion del tfe: ";
          cin.ignore();
          getline(cin,nombre_tfe);

          do{
             cout<<"Introduce estado el Tfe(creado,iniciado o finalizado):";
             cin>>estado;
            }while(estado=="creado" && estado=="iniciado" && estado=="finalizado");

             do{
               codigo_recurso=comprobar_codigo_recurso(codigo_recurso);
               igual=false;
               for(unsigned i=0;i<lista.size() && igual==false;i++)
                  {
                   if(codigo_recurso==lista[i]->gettfe_codigo())
                     {igual=true;}
                   else{igual=false;}
                  }
               if(igual==true)
                 {cout<<"Este codigo ya es de otro tfe"<<endl;}
             }while(igual==true);

      lista.push_back(new Tfe(nombre_tfe,codigo_recurso,estado));
}

void Administrador::dar_baja_Tfe(vector<Tfe*>&baja,unsigned a)
{
    baja.erase(baja.begin()+a);
}

void Administrador::modificar_Tfe(vector<Tfe*>&modificar,unsigned t)
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
          nuevo_codigo_recurso=comprobar_codigo_recurso(nuevo_codigo_recurso);
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
/*Igual que meter profesores seminario*/
void Administrador::meter_profesores_tfe(Tfe* &lista,vector<Profesor>&lista_profe)
{
    string codigo_recurso;
    char profesor;
    unsigned e=0;
    unsigned profe=0;
    char validar;

    do{
        cout<<"¿Desdea añadir profesores al tfe?(s/n):";
        cin.ignore();
        cin.get(profesor);

        if(profesor=='s')
          {
          if(lista_profe.size()<2)//Si no hay dos profesores, luego los podra añadir en modificar recurso
            {cout<<"No hay profesores para añadir, debes agregar al menos dos profesores"<<endl;}
            else{
                cout<<endl;
                for(unsigned p=0;p<lista_profe.size();p++)
                   {
                    cout<<"Nombre del profesor["<<p<<"]:"<<lista_profe[p].getnombre()<<endl;
                    cout<<"Usuario del profesor["<<p<<"]:"<<lista_profe[p].getcodigo()<<endl;
                    cout<<"============================================="<<endl;
                   }
                cout<<endl;

                do{
                    do{
                       cout<<"Introduce el numero del profesor como tutor:";
                       cin.ignore(1000,'\n');
                       cin.get(validar);
                      }while(validar<48 || validar>57);
                    profe=validar-48;
                  }while(profe>lista_profe.size()-1);

              lista->meter_tutor(lista_profe[profe]);
              }

            do{
              do{
                  cout<<"Introduce el numero del profesor como cotutor:";
                  cin.ignore();
                  cin.get(validar);

                }while(validar<48 || validar>57);
                profe=validar-48;
              }while(profe>lista_profe.size()-1);

           lista->meter_cotutor(lista_profe[profe]);

           }
        else{continue;}

    }while(profesor!='s' && profesor !='n');
}
void Administrador::dar_alta_Alumno(vector<Alumno*>&alta)
{
    string NIA;
    string nombre_alumno;
    string nombre_titulacion;
    bool igual=false;

    cout<<"Introduce datos:"<<endl;
    cout<<"Nombre del alumno:";
    cin.ignore();
    getline(cin,nombre_alumno);

    cout<<"Nombre de su titulacion:";
    getline(cin,nombre_titulacion);

    do{
        alta[0]->comprobar_codigo_id(NIA);//Dentro preguntamos por el nia y comprobamos si esta bien puesto
        igual=false;

        for(unsigned i=0;i<alta.size() && igual==false;i++)//Comprobamos que el nia no pertenezca a otro alumno
           {
            if(NIA==alta[i]->getnia())
              {igual=true;}
           else{igual=false;}
          }
    if(igual==true)
      {cout<<"Este NIA ya es de otro alumno"<<endl;}
    }while(igual==true);
    alta.push_back(new Alumno(nombre_alumno,nombre_titulacion,NIA,"\0"));
}/*El resto de las funciones crear usuario siguen la misma idea*/

void Administrador::dar_baja_Alumno(vector<Alumno*>&baja,unsigned a)
{
     baja.erase(begin(baja)+a);
}

void Administrador::modificar_Alumno(vector<Alumno*>&modifica,unsigned m)
{
    string nuevo_NIA;
    string nombre_alumno;
    string nombre_titulacion;
    bool igual=false;

    cout<<"Introdue datos:"<<endl;
    cout<<"Nombre del alumno:";
    cin.ignore();
    getline(cin,nombre_alumno);

    cout<<"Nombre de su titulacion:";
    getline(cin,nombre_titulacion);

    do{/*Aqui usamos la posicion del alumno*/
      modifica[m]->comprobar_codigo_id(nuevo_NIA);//Dentro preguntamos por el nia y lo comprobamos
      igual=false;
      for(unsigned i=0;i<modifica.size() && igual==false;i++)
         {
          if(nuevo_NIA==modifica[i]->getnia())//Comprobamos que no se repita
            {igual=true;}
          else{igual=false;}
         }
      if(igual==true){
          cout<<"Este NIA ya es de otro alumno"<<endl;
      }
      }while(igual==true);

    modifica[m]->setalumno(nombre_alumno,nombre_titulacion,nuevo_NIA);
}

void Administrador::dar_alta_Profesor(vector<Profesor>&alta)
{
        string nombre_profesor;
        string codigo_id;
        bool igual=false;

        cout<<"Introduce datos:"<<endl;
        cout<<"Nombre:";
        cin.ignore();
        getline(cin,nombre_profesor);

            do{
              alta[0].comprobar_codigo_id(codigo_id);
              igual=false;
              for(unsigned i=0;i<alta.size() && igual==false;i++)
                 {
                  if(codigo_id==alta[i].getcodigo())
                     {igual=true;}
                  else{igual=false;}
                 }
              if(igual==true)
                {cout<<"Este codigo ya es de otro profesor"<<endl;}
              }while(igual==true);

        Profesor p(nombre_profesor,codigo_id);
        alta.push_back(p);
}

void Administrador::dar_baja_Profesor(vector<Profesor>&profe,unsigned a)
{
    profe.erase(begin(profe)+a);
}

void Administrador::modificar_Profesor(vector<Profesor>&modificar,unsigned p)
{
            string nombre_profesor;
            string nuevo_id;
            bool igual=false;

            cout<<"Introduce datos:"<<endl;
            cout<<"Nombre:";
            cin.ignore();
            getline(cin,nombre_profesor);

            do{
              modificar[p].comprobar_codigo_id(nuevo_id);
              igual=false;
              for(unsigned i=0;i<modificar.size() && igual==false;i++)
                 {
                  if(nuevo_id==modificar[i].getcodigo())
                    {igual=true;}
                  else{igual=false;}
                 }
              if(igual==true)
                {cout<<"Este codigo ya es de otro profesor"<<endl;}
              }while(igual==true);
         modificar[p].setprofesor(nombre_profesor,nuevo_id);
}

void Administrador::dar_alta_Administrador(vector<Administrador>&alta)
{
        string nombre_admin;
        string codigo_id;
        bool igual=false;

        cout<<"Introduce datos:"<<endl;
        cout<<"Nombre:";
        cin.ignore();
        getline(cin,nombre_admin);

            do{
              alta[0].comprobar_codigo_id(codigo_id);
              igual=false;
              for(unsigned i=0;i<alta.size() && igual==false;i++)
                 {
                  if(codigo_id==alta[i].getcode())
                    {igual=true;}
                  else{igual=false;}
                 }
             if(igual==true)
               {cout<<"Este codigo ya es de otro administrador"<<endl;}
           }while(igual==true);

        Administrador lista(nombre_admin,codigo_id);
        alta.push_back(lista);
}

void Administrador::dar_baja_Administrador(vector<Administrador>&baja,unsigned a)
{
    baja.erase(baja.begin()+a);
}

void Administrador::modificar_Administrador(vector<Administrador>&modificar,unsigned ad)
{
        string nombre_admin;
        string nuevo_id;
        bool igual=false;
        cout<<"\nIntroduce datos:"<<endl;
        cout<<"Nombre:";
        cin>>nombre_admin;

        do{
          modificar[ad].comprobar_codigo_id(nuevo_id);
          igual=false;
          for(unsigned i=0;i<modificar.size() && igual==false;i++)
             {
              if(nuevo_id==modificar[i].getcode())
                 {igual=true;}
              else{igual=false;}
             }
          if(igual==true)
            {cout<<"Este codigo ya es de otro administrador"<<endl;}
         }while(igual==true);

    modificar[ad].setadmin(nombre_admin,nuevo_id);
}

string comprobar_codigo_recurso(string codigo_recurso)//Funcion que comprueba el codigo de los recursos
{
    int c=0;//Variable para el codigo parte de letras
    int b=0;//Variable para comprobar codigo parte numerica

    do{
        cout<<"Introduce codigo: ";
        cin>>codigo_recurso;

        if(codigo_recurso.size()!=7)//Si el codigo es mayor o menor que 7, imprime el mensaje
          {cout<<"El codigo debe tener un maximo de 7 espacios"<<endl;}
        else
          {
           for(unsigned i=0;i<3;i++)//Esta parte permite que los primeros caracteres del codigo sean 3 letras y los ultimos sean 4 numeros.Para ello,usa ASCII
              {
                if((codigo_recurso[i]>64 && codigo_recurso[i]<91) || (codigo_recurso[i]>96 && codigo_recurso[i]<123))
                {c=c+1;}

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
             cout<<"El codigo debe tener 3 caracteres"<<endl;
            }
            else if(b<4)
            {cout<<"El codigo debe tener 4 digitos"<<endl;}
          }
      }while(c<3 || b<4);

    return codigo_recurso;
}

void Administrador::comprobar_codigo_id(string &codigo_id)//Funcion que comprueba el codigo de los usuario
{
    do{
        cout<<"Codigo de identificacion:";
        getline(cin,codigo_id);
        if(codigo_id.size()!=7)
          {cout<<"El codigo debe contener 7 caracteres"<<endl;}
    }while(codigo_id.size()!=7);
}
/*Imprime todos los datos */
void Administrador::imprimir_datos(vector<Seminario*>mis_seminarios,vector<Asignatura*>mis_asignaturas,vector<Tfe*>mis_tfe,vector<Alumno*>mis_alumnos,vector<Profesor>mis_profesores,vector<Administrador>mis_administradores)
{   char print_option;
    char print;

   do{
    cout<<"\n¿Que usuarios o recursos desea imprimir?"<<endl;
    cout<<"\n1.Seminarios\t     2.Asignaturas  3.Tfe"<<endl;
    cout<<"\n4.Administradores    5.Profesores   6.Alumnos"<<endl;
    do{
    do{
        cout<<"\nOpcion:";
        cin.ignore();
        cin.get(print_option);
    }while(print_option<49||print_option>54);

    switch (print_option)
    {
    case '1':
        for(unsigned i=0;i<mis_seminarios.size();i++)
           {mis_seminarios[i]->imprimir_seminario();}
      break;

    case '2':
        for(unsigned i=0;i<mis_asignaturas.size();i++)
           {mis_asignaturas[i]->imprimir_asignatura();}
     break;

    case '3':
        for(unsigned i=0;i<mis_tfe.size();i++)
           {mis_tfe[i]->imprimir_tfe();}
        break;

    case '4':
        for(unsigned i=0;i<mis_administradores.size();i++)
           {
            cout<<"\nNombre del administrador:"<<mis_administradores[i].getnombre()<<endl;
            cout<<"Codigo del administrador:"<<mis_administradores[i].getcode()<<endl;
           }
      break;

    case '5':
         for(unsigned i=0;i<mis_profesores.size();i++)
            {
            cout<<"\nNombre profesor:"<<mis_profesores[i].getnombre()<<endl;
            cout<<"Codigo del profesor:"<<mis_profesores[i].getcodigo()<<endl;
           }
        break;

    case '6':
        for(unsigned i=0;i<mis_alumnos.size();i++)
           {
            cout<<"==============================================================================="<<endl;
            cout<<"Nombre del alumno:"<<mis_alumnos[i]->getnombre()<<endl;
            cout<<"Titulacion que cursa:"<<mis_alumnos[i]->getnombre_titulacion()<<endl;
            cout<<"NIA:"<<mis_alumnos[i]->getnia()<<endl;
            mis_alumnos[i]->imprimir_listas();
            cout<<"==============================================================================="<<endl;
           }
        break;
    default:
        cout<<"Opcion incorrecta"<<endl;
         break;
    }
    }while(print_option<49 || print_option>54);
    cout<<"¿Desea imprimir otro usuario o recurso?(s/n)"<<endl;
    do{
    cout<<"Opcion:";
    cin>>print;

    }while(print!='s' && print!='n');

    }while(print!='n');

}
ofstream& operator<<(ofstream& salida,vector<Administrador>&lista)
{
  for(unsigned i=0;i<lista.size();i++)//Como pasamos el vector hacemos un for para pasar todos los datos al fichero
     {
      salida<<lista[i]._nombre_admin<<endl;
      salida<<lista[i]._codigo_id<<endl;
      salida<<lista[i]._password<<endl;
     }
return salida;
}

ifstream& operator>>(ifstream& entrada,Administrador &lista)
{
   getline(entrada,lista._nombre_admin);
   entrada>>lista._codigo_id;
   entrada.ignore();
   getline(entrada,lista._password);

return entrada;
}
