#include<iostream>
#include "campus_virtual.h"
#include<cstring>
#include<fstream>

using namespace std;


Campus_Virtual::Campus_Virtual()//constructor vacio
{

}

void Campus_Virtual::inicio()//Menu del campus virtual
{
    ofstream archivo;//Fichero de salida
    ifstream archivo_s;//Fichero de entrada
    char opcion_user;//Elegir primera opcion: alumno, recurso o admin

    entrada_archivos(archivo_s);//Cargarmos ficheros

    string user;//codigo del usuario o recurso para registrarse(NIA,...)
    string password;//Contraseña de los usuarios (extra del proyecto)
    string contrasena;//Uso para el primer admin
    bool igualacion=false;//Se utilizara para poder acceder a los usuarios
    Administrador primer_admin("Nombre","codigo1");//Objeto creado para el caso de que no existiera nada y se obligara a crear un primer admin

    do{
        cout<<"Menu Campus Virtual"<<endl;
        cout<<"\n1.Identificarse como Alumno"<<endl;//Menu principal del campus.En esta parte solo funciona la opcion 3 y 4
        cout<<"2.Identificarse como Profesor"<<endl;
        cout<<"3.Identificarse como Administrador"<<endl;
        cout<<"4.Salir"<<endl;

        do{
           cout<<"Opcion (numero): ";

           cin.get(opcion_user);

           switch (opcion_user)
           {
            case '1':if(mis_alumnos.size()>0)//Vemos si hay alumnos creados
                       {
                        unsigned al=0;//Variable que se usa para guardar la posicion del alumno en la que se encuentra en el vector
                        igualacion=false;

                        cout<<"Usuario:";
                        cin>>user;
                        cin.ignore();
                        cout<<"Contraseña:";                        
                        getline(cin,password);

                        for(unsigned a=0;a<mis_alumnos.size() && igualacion==false ;a++)
                           {
                                if(mis_alumnos[a]->getnia()==user && mis_alumnos[a]->get_password()==password)//Comparacion de si el codigo y contraseña coincide con uno de los alumnos
                                {
                                    igualacion=true;
                                    al=a;
                                }
                                else{igualacion=false;}
                           }

                        if(igualacion==true)
                          {
                           menu_alumno(al);//Llamada a la funcion del menu alumno y pasamos la posicion que servira para realizar operaciones con las demas funciones
                          }
                        else
                        {cout<<"Usuario incorrecto"<<endl;}
                   }
                   else
                     {cout<<"No existe alumnos en el registro,\nel administrador debe añadir al menos 1 alumno"<<endl;}
                   break;

            case '2':if(mis_profesores.size()>0)
                       {
                        unsigned pr=0;//Variable para guardar la posicion del profesor registrado
                        igualacion=false;
                        cout<<"Usuario:";
                        cin>>user;
                        cin.ignore();
                        cout<<"Contraseña:";
                        getline(cin,password);

                        for(unsigned p=0;p<mis_profesores.size() && igualacion==false ;p++)
                        {
                                if(mis_profesores[p].getcodigo()==user && mis_profesores[p].get_password()==password)//Comparacion de si el codigo y la contraseña coinciden con uno de los profesores
                                {
                                    igualacion=true;
                                    pr=p;
                                }
                                else{igualacion=false;}
                        }

                        if(igualacion==true)
                          {
                            menu_profesor(pr,user);//Llamada a la funcion del menu profesor y pasamos la posicion que servira para realizar operaciones con las demas funciones
                          }
                        else{cout<<"Usuario incorrecto"<<endl;}
                     }
                   else{cout<<"No existen profesores en el registro,\nel administrador debe añadir al menos 1 profesor"<<endl;}

            break;

            case '3':
                   if(mis_administradores.size()>0)//Si existe ya un administrador, este tiene que escribir su codigo
                     {
                       unsigned ad=0;//Variable para guardar la posicion del administrador registrado
                       igualacion=false;

                       cout<<"Usuario:";
                       cin>>user;
                       cin.ignore();
                       cout<<"Contraseña:";
                       getline(cin,password);
                       for(unsigned u=0;u<mis_administradores.size() && igualacion==false ;u++)
                          {
                            if(mis_administradores[u].getcode()==user && mis_administradores[u].get_password()==password)//Comparacion de si el codigo coincide con uno de los administradores
                              {
                                ad=u;
                                igualacion=true;
                              }
                            else{igualacion=false;}
                          }

                       if(igualacion==true)
                         {menu_admin(ad);}//Llamada a la funcion del menu del administrador y pasamos la posicion que servira para realizar operaciones con las demas funciones

                       else{cout<<"\n****Usuario incorrecto****\n"<<endl;}
                     }
                   else  //Este caso solo ocurre si eres un primer usuario, te registras como adminsitrador y vuelves al menu para introducir tu codigo
                    {
                       cout<<"\n///Debes registrarte como primer administrador///\n"<<endl;
                       primer_admin.dar_alta_Administrador(mis_administradores);
                       cout<<"Introduce Usuario: ";
                       cin>>user;
                       cout<<"Introduce contraseña: ";
                       cin.ignore();
                       getline(cin,contrasena);

                       mis_administradores[mis_administradores.size()-1].set_password(contrasena);
                       menu_admin(0);

                   }
            break;
            case '4':cout<<"Guardando base de datos"<<endl;

                     salida_archivos(archivo);//Guardamos los datos en los ficheros
                   break;

            default:cout<<"Error. Introduce de nuevo su opcion"<<endl;//Si la opcion no es correcta, salta el mensaje
                    cin.ignore();
            break;
            }

          }while(opcion_user<49 || opcion_user>52);//Esca condicion es en el caso de introducir una opcion erronea

      }while(opcion_user!='4');//Este caso es para salir
}

void Campus_Virtual::menu_admin(unsigned ad)
{
    char opcion;//Esto sera para ir accediendo por el menu (dar alta, baja,...)
    string opcion2;//Esto sera para ir accediendo por el menu (usuario o recurso)
    string opcion3;//Esto sera para ir accediendo por el menu (elegir a quien/que(alumno, asignatura,...) quieres modificar, crear,...)
    string password;//Contraseña de los usuarios

do{
    cout<<"\nMenu administrador:"<<endl;
    cout<<"1.Dar alta recurso/usuario"<<endl;
    cout<<"2.Dar baja recurso/usuario"<<endl;
    cout<<"3.Modificar recurso/usuario"<<endl;
    cout<<"4.Cambiar contraseña"<<endl;
    cout<<"5.Imprimir datos de recursos y usuarios"<<endl;
    cout<<"6.Salir menu admin"<<endl;

    do{//Este bucle sirve para el caso de introducir una opcion mayor de 6
       cout<<"\nIngrese opcion:";
       cin.get(opcion);
       switch(opcion)
       {
        case '1':
             do{//este bucle do-while servira para el caso de introducir mal usuario o recurso
                cout<<"Dar alta usuario o recurso: ";
                cin>>opcion2;

                if(opcion2=="Usuario"||opcion2=="usuario")
                  {
                    do{
                       cout<<"Dar alta Alumno/Profesor/Administrador: ";//Opciones de agregar los usuarios definidos
                       cin>>opcion3;

                       if(opcion3=="Alumno"||opcion3=="alumno")
                         {mis_administradores[ad].dar_alta_Alumno(mis_alumnos);}//Llama a la funcion de añadir alumno que devuelve un alumno,y ese se añade al registro de alumnos.

                       else if(opcion3=="Profesor"||opcion3=="profesor")
                         {mis_administradores[ad].dar_alta_Profesor(mis_profesores);}//Equivalente pero con profesores

                       else if (opcion3=="Administrador"||opcion3=="administrador")
                         {mis_administradores[ad].dar_alta_Administrador(mis_administradores);}//Añade administradores,teniendo en cuenta al primero creado en el menu del campus virtual

                       else{cout<<"opcion incorrecta"<<endl;}

                    }while(opcion3!="Alumno" && opcion3!="Profesor" && opcion3!="Administrador" && opcion3!="alumno" && opcion3!="profesor" && opcion3!="administrador");
                  }

                else if(opcion2=="Recurso"||opcion2=="recurso")//Igual que el caso anterior pero para recursos
                  {
                    do{
                        cout<<"Dar alta Seminario/Tfe/Asignatura: ";

                        cin>>opcion3;

                        if(opcion3=="Seminario"||opcion3=="seminario")
                        {
                         mis_administradores[ad].dar_alta_Seminario(mis_seminarios);//Crea el recurso y seguidamente llama a la funcion de meter profesores en el seminario
                         mis_administradores[ad].meter_profesores_seminario(mis_seminarios[mis_seminarios.size()-1],mis_profesores);//Pasamos el vector de profesores y el ultimo seminario creado
                        }
                        /*De la misma forma que seminario*/
                        else if(opcion3=="Tfe"||opcion3=="tfe")
                        {
                         mis_administradores[ad].dar_alta_Tfe(mis_tfe);
                         mis_administradores[ad].meter_profesores_tfe(mis_tfe[mis_tfe.size()-1],mis_profesores);
                        }

                        else if (opcion3=="Asignatura"||opcion3=="asignatura")
                          {
                           mis_administradores[ad].dar_alta_Asignatura(mis_asignaturas);
                           mis_administradores[ad].meter_profesores_asignatura(mis_asignaturas[mis_asignaturas.size()-1],mis_profesores);
                          }

                       else{cout<<"opcion incorrecta"<<endl;}

                      }while(opcion3!="Seminario" && opcion3!="Tfe" && opcion3!="Asignatura"&&opcion3!="seminario" && opcion3!="tfe" && opcion3!="asignatura");
                  }
                else {cout<<"opcion incorrecta"<<endl;}

               }while(opcion2!="Usuario" && opcion2!="Recurso" && opcion2!="usuario" && opcion2!="recurso");
           cin.ignore();
        break;

        case '2'://En este caso, el usuario busca el recurso o usuario que quiere eliminar
             do{
                     cout<<"Dar baja usuario o recurso"<<endl;

                     cin>>opcion2;

                     if(opcion2=="Usuario"||opcion2=="usuario")
                       {
                        do{
                           cout<<"Dar baja Alumno/Profesor/Administrador: ";
                           cin>>opcion3;

                         if(opcion3=="Alumno"||opcion3=="alumno")
                           {
                             char posicion;//Variable donde se guarda el lugar del usuario o recurso al que se le quiere realizar una operacion

                             for(unsigned i=0;i<mis_alumnos.size();i++)//Imprimimos todos los alumnos para ver cual se quiere eliminar
                                {
                                 cout<<"Nombre del alumno["<<i<<"]:"<<mis_alumnos[i]->getnombre()<<endl;
                                 cout<<"NIA del alumno["<<i<<"]:"<<mis_alumnos[i]->getnia()<<endl;
                                }
                             do{//bucle para comprobar el numero introducido no es mayor que el tamaño de alumnos
                                do{//bucle para comprobar que la posicion corresponda a un numero en ascii

                                     cout<<"\nIntroduzca el numero del alumno a dar de baja: ";
                                     cin.get(posicion);
                                 }while(posicion<48 || posicion>57);
                             }while(posicion-48>mis_alumnos.size());//transformacion del char al int

                             /*Antes de eliminar el alumno, lo sacamos de sus recursos*/
                             mis_alumnos[posicion-48]->expulsar_alumno();
                             mis_administradores[ad].dar_baja_Alumno(mis_alumnos,posicion-48);//Llamamos a la funcion de eliminar un alumno y le pasamos el vector y la posicion del alumno en el
                           }
                        /*El resto de opciones son equivalentes a la anterior*/
                         else if(opcion3=="Profesor"||opcion3=="profesor")
                           {
                             char posicion;
                             for(unsigned i=0;i<mis_profesores.size();i++)
                                {
                                 cout<<"Nombre del profesor["<<i<<"]:"<<mis_profesores[i].getnombre()<<endl;
                                 cout<<"Usuario del profesor["<<i<<"]:"<<mis_profesores[i].getcodigo()<<endl;
                                }

                             do{
                                 do{
                                     cout<<"\nIntroduzca el numero del profesor a dar de baja: ";
                                     cin.get(posicion);
                                 }while(posicion<48 || posicion>57);
                             }while(posicion-48>mis_profesores.size());
                                mis_profesores[posicion-48].eliminar_profesor_recursos(mis_seminarios,mis_asignaturas,mis_tfe);//El profesor se saca de todos los recursos en los que participa
                                mis_administradores[ad].dar_baja_Profesor(mis_profesores,posicion-48);
                             }

                         else if (opcion3=="Administrador"||opcion3=="Administrador")
                           {
                             char posicion;

                             for(unsigned i=0;i<mis_administradores.size();i++)
                                {
                                 cout<<"Nombre del administrador["<<i<<"]:"<<mis_administradores[i].getnombre()<<endl;
                                 cout<<"Usuario del administrador["<<i<<"]:"<<mis_administradores[i].getcode()<<endl;
                             }
                             do{
                                 do{
                                     cout<<"\nIntroduzca el numero del administrador a dar de baja: ";
                                     cin.get(posicion);
                                 }while(posicion<48 || posicion>57);
                             }while(posicion-48>mis_administradores.size());

                                 mis_administradores[ad].dar_baja_Administrador(mis_administradores,posicion-48);
                           }
                         else{cout<<"opcion incorrecta"<<endl;}

                      }while(opcion3!="Alumno" && opcion3!="Profesor" && opcion3!="Administrador" &&opcion3!="alumno" && opcion3!="profesor" && opcion3!="administrador");
                     }

                     else if(opcion2=="Recurso"||opcion2=="recurso")
                       {
                         do{
                             cout<<"Seminario/Tfe/Asignatura: ";
                             cin>>opcion3;

                             if(opcion3=="Seminario"||opcion3=="seminario")
                               {
                                 unsigned posicion;//Variable para guardar la poscicion
                                 posicion=listas_seminario();//La funcion devuelve un entero que es la posicion del seminario

                                 mis_seminarios[posicion]->expulsar_alumnos_seminario();//Eliminamos los alumnos apuntados al seminario
                                 mis_administradores[ad].dar_baja_Seminario(mis_seminarios,posicion);//Luego eliminamos el seminario que queriamos usando la variable posicion para buscarlo en el vector
                               }
                            /*Al igual que ocurre con seminarios realizamos las mismas operaciones con asignaturas y tfe*/
                             else if(opcion3=="Tfe"||opcion3=="tfe")
                               {
                                unsigned posicion;
                                posicion=listas_tfe();

                                mis_tfe[posicion]->expulsar_alumno();
                                mis_administradores[ad].dar_baja_Tfe(mis_tfe,posicion);
                               }

                             else if (opcion3=="Asignatura"||opcion3=="asignatura")
                               {
                                 unsigned posicion;
                                 posicion=listas_asignatura();

                                 mis_asignaturas[posicion]->expulsar_alumnos_asignatura();
                                 mis_administradores[ad].dar_baja_Asignatura(mis_asignaturas,posicion);
                                }

                             else{cout<<"opcion incorrecta"<<endl;}
                         }while(opcion3!="Seminario" && opcion3!="Tfe" && opcion3!="Asignatura" && opcion3!="seminario" && opcion3!="tfe" && opcion3!="asignatura");
                        }

                     else if(opcion3=="Salir"||opcion3=="salir")
                       {break;}
                     else{cout<<"opcion incorrecta"<<endl;}

              }while(opcion2!="Usuario" && opcion2!="Recurso"&&opcion2!="usuario" && opcion2!="recurso");
           cin.ignore();
                    break;

        case '3'://En este caso, se llama a las funciones de modificar recurso o usuario
            do{
                     cout<<"Modificar usuario o recurso: ";
                     cin>>opcion2;

                     if(opcion2=="Usuario"||opcion2=="usuario")
                     {
                      do{
                         cout<<"Modificar Alumno/Profesor/Administrador o salir: ";
                         cin>>opcion3;
                       /*Mismas operaciones explicadas en el case 2 (eliminar usuarios/recurso)*/
                         if(opcion3=="Alumno"||opcion3=="alumno")
                           {
                             char posicion;

                             for(unsigned i=0;i<mis_alumnos.size();i++)
                                {
                                 cout<<"Nombre del alumno["<<i<<"]:"<<mis_alumnos[i]->getnombre()<<endl;
                                 cout<<"Usuario del alumno["<<i<<"]:"<<mis_alumnos[i]->getnia()<<endl;
                                }
                             do{
                                 do{
                                     cout<<"\nIntroduzca el numero del alumno a dar de baja: ";
                                     cin.get(posicion);
                                 }while(posicion<48 || posicion>57);
                             }while(posicion-48>mis_alumnos.size());

                            mis_administradores[ad].modificar_Alumno(mis_alumnos,posicion-48);//Llamada a la funcion modificar pasando la posicion del alumno y el vector
                           }

                         else if(opcion3=="Profesor"||opcion3=="profesor")
                           {
                             char posicion;
                             for(unsigned i=0;i<mis_profesores.size();i++)
                                {
                                 cout<<"Nombre del profesor["<<i<<"]:"<<mis_profesores[i].getnombre()<<endl;
                                 cout<<"Usuario del profesor["<<i<<"]:"<<mis_profesores[i].getcodigo()<<endl;
                                }
                             do{
                                 do{
                                     cout<<"\nIntroduzca el numero del profesor a dar de baja: ";
                                     cin.get(posicion);
                                 }while(posicion<48 || posicion>57);
                             }while(posicion-48>mis_profesores.size());

                             mis_administradores[ad].modificar_Profesor(mis_profesores,posicion-48);
                           }

                         else if (opcion3=="Administrador"||opcion3=="Administrador")
                           {
                             char posicion;
                             for(unsigned i=0;i<mis_administradores.size();i++)
                                {
                                 cout<<"Nombre del administrador["<<i<<"]:"<<mis_administradores[i].getnombre()<<endl;
                                 cout<<"Usuario del administrador["<<i<<"]:"<<mis_administradores[i].getcode()<<endl;
                                }
                             do{
                                 do{
                                     cout<<"\nIntroduzca el numero del administrador a dar de baja: ";
                                     cin.get(posicion);
                                 }while(posicion<48 || posicion>57);
                             }while(posicion-48>mis_administradores.size());

                             mis_administradores[ad].modificar_Administrador(mis_administradores,posicion-48);
                           }
                         else{cout<<"opcion incorrecta"<<endl;}
                        }while(opcion3!="Alumno" && opcion3!="Profesor" && opcion3!="Administrador"&&opcion3!="alumno" && opcion3!="profesor" && opcion3!="administrador" && opcion3!="salir");
                       }

                     else if(opcion2=="Recurso"||opcion2=="recurso")
                       {
                         /*Mismas operaciones que en el case 2(eliminar usuario/recurso*/
                        do{
                           cout<<"Modificar Seminario/Tfe/Asignatura: ";
                           cin>>opcion3;

                           if(opcion3=="Seminario"||opcion3=="seminario")
                             {
                              unsigned posicion;
                              posicion=listas_seminario();

                              mis_administradores[ad].modificar_Seminario(mis_seminarios,posicion);//Llamamos a la funcion modificar y le pasamos la posicion del seminario en el vector y el vector
                              mis_administradores[ad].meter_profesores_seminario(mis_seminarios[posicion],mis_profesores);//Luego llamamos a la funcion de meter profesores por si se quieren cambiar
                             }
                           /*Al igual que en seminarios, se hace lo mismo en asignaturas y tfe*/
                           else if(opcion3=="Tfe"||opcion3=="tfe")
                             {
                              unsigned posicion;
                              posicion=listas_tfe();

                              mis_administradores[ad].modificar_Tfe(mis_tfe,posicion);
                              mis_administradores[ad].meter_profesores_tfe(mis_tfe[posicion],mis_profesores);
                             }

                           else if (opcion3=="Asignatura"||opcion3=="asignatura")
                             {
                              unsigned posicion;
                              posicion=listas_asignatura();

                              mis_administradores[ad].modificar_Asignatura(mis_asignaturas,posicion);
                              mis_administradores[ad].meter_profesores_asignatura(mis_asignaturas[posicion],mis_profesores);
                             }
                           else{cout<<"opcion incorrecta"<<endl;}
                         }while(opcion3!="Seminario" && opcion3!="Tfe" && opcion3!="Asignatura"&&opcion3!="seminario" && opcion3!="tfe" && opcion3!="asignatura");
                        }
                      else{cout<<"opcion incorrecta"<<endl;}

              }while(opcion2!="Usuario" && opcion2!="Recurso"&&opcion2!="usuario" && opcion2!="recurso");
           cin.ignore();
         break;

        case '4'://Caso para cambiar la contraseña (extra del entregable)
                  cout<<"Introduce nueva contraseña"<<endl;
                  cin.ignore();
                  getline(cin,password);
                  mis_administradores[ad].set_password(password);//Llamada a la funcion para modificar la comtraseña
        break;
        case '5'://Caso de imprimir los todos los datos del programa
                 mis_administradores[ad].imprimir_datos(mis_seminarios,mis_asignaturas,mis_tfe,mis_alumnos,mis_profesores,mis_administradores);
        break;
        default:cin.ignore();
                break;
            }
    }while (opcion<49 || opcion>54);
 }while(opcion!='6');
cout<<endl;
cin.ignore();
}

void Campus_Virtual::menu_alumno(unsigned a)
{
   char opcion;//Elegir primera opcion (darse alta, baja,...)
   string opcion2;//Elegir recurso
   string password;
   do{
       cout<<"\nBienvenido/a "<<mis_alumnos[a]->getnombre()<<" al menu alumnos:"<<endl;
       cout<<"1.Darse de alta a un recurso"<<endl;
       cout<<"2.Darse de baja de un recurso"<<endl;
       cout<<"3.Cambiar contraseña"<<endl;
       cout<<"4.Salir"<<endl;

       do{//bucle que se repite cuando no se coge una de las opciones
           cout<<"Ingrese opcion:";

           cin.get(opcion);
           switch (opcion)
            {
             case '1':
                    do{
                      cout<<"Seminario/Tfe/Asignatura: ";
                      cin>>opcion2;

                      if(opcion2=="Seminario" || opcion2=="seminario")
                        {
                         bool iflleno=false;//Variable para comprobar si el seminario esta completo o no
                         unsigned posicion;

                         posicion=listas_seminario();//Sacamos por pantalla los seminarios
                         iflleno=mis_seminarios[posicion]->meter_alumnos(mis_alumnos[a]);//Comprobamos que el seminario no esta completo y a la vez metemos al alumno en el seminario

                         if(iflleno==false)
                           {mis_alumnos[a]->aniadir_seminario(mis_seminarios[posicion]);}//Si esta vacio llamamos a la funcion para que meta el seminario en la lista de seminarios del alumno

                         else{continue;}
                        }

                      else if(opcion2=="Asignatura" || opcion2=="asignatura")
                        {
                          bool equal_degree;//Comprobar que es ha metido el alumno a la asignatura
                          unsigned posicion;

                          posicion=listas_asignatura();//Sacamos por pantalla las asignaturas

                              if(mis_asignaturas[posicion]->getnombre_titulacion()==mis_alumnos[a]->getnombre_titulacion())//Comprobamos que el alumno pueda meterse en las asignaturas de su grado
                                {
                                 equal_degree=mis_asignaturas[posicion]->meter_alumno(mis_alumnos[a]);//Metemos el alumno en la asignatura

                                 if(equal_degree==true)
                                   {mis_alumnos[a]->aniadir_asignatura(mis_asignaturas[posicion]);}//En el caso de que el alumno halla entrado a la asignatura metemos la asignatura en la lista de asginaturas de alumno

                                 else{continue;}
                                }
                              else{cout<<"\nLo siento, esta asignatura no es correspoondiente a su grado"<<endl;}
                        }

                      else if(opcion2=="Tfe" || opcion2=="tfe")
                        {
                          bool disponible=false;//Comprobar que el alumno se pudo meter al tfe
                          unsigned posicion;//Posicion del tfe al que se quiere meter el alumno

                          posicion=listas_tfe();//Sacamos por pantalla los tfe

                          if(mis_tfe[posicion]->gettfe()==mis_alumnos[a]->getnombre_titulacion())//Vemos que el tfe pertenecen a la misma titulacion
                            {
                             disponible=mis_tfe[posicion]->meter_alumno(mis_alumnos[a]);//Metemos el alumno en el tfe y si se ha conseguido devuelve un true

                             if(disponible==true)
                               {mis_alumnos[a]->aniadir_tfe(mis_tfe[posicion]);}//Si se metio el alumno al tfe se añade este a su lista de tfe

                             else{continue;}
                            }
                         else{cout<<"\nLo siento, este tfe no es correspoondiente a su grado"<<endl;}
                       }
                    }while(opcion2!="Seminario" && opcion2!="Tfe" && opcion2!="Asignatura" && opcion2!="seminario" && opcion2!="tfe" && opcion2!="asignatura");
               cin.ignore();
              break;

             case '2':
               do{
                  cout<<"Seminario/Tfe/Asignatura: ";
                  cin>>opcion2;

                  if(opcion2=="Seminario" || opcion2=="seminario")
                    {
                     unsigned posicion;
                     posicion=listas_seminario();//Se imprime los seminarios para que el alumno vea de cual quiere salir para elegir la posicion del seminario

                     mis_seminarios[posicion]->sacar_alumno(a);//Primero eliminamos el alumno del seminario pasando la posicion (a) de este
                     mis_alumnos[a]->darse_baja_seminario(mis_seminarios[posicion]->getseminario_codigo());//Sacamos el seminario de la lista de seminarios del alumno
                    }                                                               /*Esta funcion devuelve el codigo del recurso que se usara en la anterior a esta*/
                 /*Hacemos lo mismo para asignatura y tfe*/
                  else if(opcion2=="Asignatura" || opcion2=="asignatura")
                    {
                     unsigned posicion;
                     posicion=listas_asignatura();

                     mis_asignaturas[posicion]->sacar_alumno(a);
                     mis_alumnos[a]->darse_baja_asignatura(mis_asignaturas[posicion]->getasignatura_codigo());
                    }

                  else if(opcion2=="Tfe" || opcion2=="tfe")
                    {
                     unsigned posicion=listas_tfe();

                     mis_tfe[posicion]->sacar_alumno();
                     mis_alumnos[a]->darse_baja_tfe(mis_tfe[posicion]->gettfe_codigo());
                    }
               }while(opcion2!="Seminario" && opcion2!="Tfe" && opcion2!="Asignatura" && opcion2!="seminario" && opcion2!="tfe" && opcion2!="asignatura");
               cin.ignore();
             break;

             case '3'://Cambiar la contraseña alumno
                    cout<<"Introduce nueva contraseña"<<endl;
                    cin.ignore();
                    getline(cin,password);

                    mis_alumnos[a]->set_password(password);
             break;
             case '4':break;

             default:cout<<"\nOpcion incorrecta"<<endl;
                     cin.ignore();
                     break;
           }
       }while(opcion<49 || opcion>52);

   }while(opcion!='4');
cin.ignore();
}

void Campus_Virtual::menu_profesor(unsigned pr, string codigo_id)
{
    char opcion;
    string opcion2;//Opcion para escoger seminario, asignatura
    string searchcode;//variable para buscar el recurso que se quiere modificar
    char posicion;//Recoge la posicion del recurso en el vector
    int comprobar_profesor=0;//Variable que recoge el entero de comprobar profesor y ver si se encuentra en el recurso
    string password;//Contraseña profe
    char posicion2;//Variable para elegir el alumno al que se le quiere cambiar la nota

    do{
        cout<<"\nBienvenido/a "<<mis_profesores[pr].getnombre()<<" al menu profesor:"<<endl;
        cout<<"1.Modificar sus recursos"<<endl;
        cout<<"2.Cambiar nota a un alumno"<<endl;
        cout<<"3.Cambiar contraseña"<<endl;
        cout<<"4.Salir"<<endl;
        do{
            cout<<"\nIntroduce opcion(numero):";

            cin.get(opcion);
            switch (opcion)
            {
            case '1':

                 do{
                    cout<<"Seminario/Asignatura/Tfe: ";
                    cin>>opcion2;

                    if(opcion2=="Seminario" || opcion2=="seminario")
                      {
                        unsigned posicion=listas_seminario();//Imprimimos todos los seminarios y devolvemos un entero que es la posicion del seminario en el vector
                        comprobar_profesor=0;

                        comprobar_profesor=mis_seminarios[posicion]->comprobar_profesor_seminario(codigo_id);//Buscamon en seminarios y llamamos a la funcion para ver si está el profesor

                        if(comprobar_profesor==1)//condicion de busqueda del seminario y si tiene el profesor en el seminario
                          {mis_profesores[pr].modificar_Seminario(mis_seminarios,posicion);}//llamada a la funcion de modificar seminario donde le pasamos el vector seminario en la posicion que se quiso modificar
                        else{cout<<"No puede modificar este seminario porque no esta asignado como profesor"<<endl;}
                      }
/*Para los casos de asignatura y tfe se realizan las mismas operaciones que en seminarios*/

                    else if(opcion2=="Asignatura" || opcion2=="asignatura")
                      {
                        unsigned posicion=listas_asignatura();
                        comprobar_profesor=0;

                        comprobar_profesor=mis_asignaturas[posicion]->comprobar_profesor_asignatura(codigo_id);

                        if(comprobar_profesor==1)
                          {mis_profesores[pr].modificar_Asignatura(mis_asignaturas,posicion);}

                         else{cout<<"No puede modificar este asignatura porque no esta asignado como profesor"<<endl;}
                       }

                    else if(opcion2=="Tfe" || opcion2=="tfe")
                      {
                       unsigned posicion=listas_tfe();
                       comprobar_profesor=0;

                       comprobar_profesor=mis_tfe[posicion]->comprobar_profesor_tfe(codigo_id);

                       if(comprobar_profesor==1)
                         {mis_profesores[pr].modificar_Tfe(mis_tfe,posicion);}
                       else{cout<<"No puede modificar este tfe porque no esta asignado como profesor"<<endl;}
                      }

                }while(opcion2!="Seminario" && opcion2!="seminario" && opcion2!="Asignatura" && opcion2!="asignatura" && opcion2!="Tfe" && opcion2!="tfe");
                cin.ignore();
             break;

            case '2':
                cin.ignore();
                do{
                    for(unsigned i=0;i<mis_asignaturas.size();i++)//Imprimimimos lista de asignaturas para elegir
                       {
                        cout<<"Nombre de la asignatura["<<i<<"]: "<<mis_asignaturas[i]->getnombre()<<endl;
                        cout<<"Titulacion asignada a la misma: "<<mis_asignaturas[i]->getnombre_titulacion()<<"\n"<<endl;
                       }
                cout<<"Salir(s)\n"<<endl;
                do{
                    cout<<"Seleccione la asignatura: ";

                    cin.get(posicion);

                    if((posicion<48 || posicion>57) && posicion!='s')
                    {cout<<"\nNo admite caracteres\n"<<endl;}
                  }while((posicion<48 || posicion>57 || posicion-48>mis_asignaturas.size()) && posicion!='s' );

                  if(posicion!='s')
                    {
                     comprobar_profesor=0;
                     if(mis_asignaturas[posicion-48]->comprobar_profesor_asignatura(codigo_id)==1)//Comprobamos que el profesor se encuentra en dicha asignatura
                       {
                         mis_asignaturas[posicion-48]->imprimir_alumnos();//Imprimimos la lista alumnos de la asignatura

                         do{
                             cout<<"Seleccione alumno: ";

                             cin.get(posicion2);
                         }while ((posicion2<48||posicion2>57) && posicion2-49>mis_alumnos.size());

                         mis_profesores[pr].cambiar_notas(mis_asignaturas[posicion-48],posicion2-49);//Se le llama a la funcion
                        cin.ignore();
                         if(posicion2<48||posicion2>57)
                         {cout<<"No se admite caracteres"<<endl;}
                      }
                    else{cout<<"El profesor no se encuentra en ninguna asignatura"<<endl;}
                  }
          }while(comprobar_profesor==0 && posicion!='s');
                cin.ignore();
           break;

            case '3'://Cambiar la contraseña del profesor
                    cout<<"Introduce nueva contraseña"<<endl;
                    cin.ignore();
                    getline(cin,password);

                    mis_profesores[pr].set_password(password);
            break;
            case '4':break;
            default:cout<<"\nERROR\n"<<endl;
                    cin.ignore();
                    break;
             }
        }while(opcion<49 || opcion>52);
    }while(opcion!='4');
cin.ignore();
}


Campus_Virtual::~Campus_Virtual()//Destructor que elimina la memoria dinamica de los arrays de usuarios y recursos
{

}

void Campus_Virtual::salida_archivos(ofstream &salida)
{
//Profesores----------------------------------------------------------------------------------
    salida.open("Profesores.txt",ios::out);//Abrimos el fichero
    if(salida.is_open())
      {
        for(unsigned i=0;i<mis_profesores.size();i++)
           {salida<<mis_profesores[i];}//Leemos cada profesor del vector y usamos el operador sobrecargado para guardar en el fichero
      }
    else{cout<<"Error al guardar"<<endl;}

    salida.close();//Cerramos el fichero

/*El resto igua que el profesor aunque el operador hace diferentes funciones*/
//Administradores------------------------------------------------------------------------------
    salida.open("Administradores.txt",ios::out);

    if(salida.is_open())
      {salida<<mis_administradores;}

    else{cout<<"Error al guardar"<<endl;}

    salida.close();

//Alumnos--------------------------------------------------------------------------------------
    salida.open("Alumnos.txt",ios::out);
    if(salida.is_open())
      {
        for(unsigned i=0;i<mis_alumnos.size();i++)
           {salida<<mis_alumnos[i];}
      }
    else{cout<<"Error al guardar"<<endl;}

    salida.close();

//Asignaturas----------------------------------------------------------------------------------
    salida.open("Asignaturas.txt",ios::out);
    if(salida.is_open()){
        for(unsigned i=0;i<mis_asignaturas.size();i++){
             salida<<mis_asignaturas[i];
        }
    }
    else{cout<<"Error al guardar"<<endl;}
    salida.close();

//Seminarios-----------------------------------------------------------------------------------
    salida.open("Seminarios.txt",ios::out);
    if(salida.is_open())
      {
        for(unsigned i=0;i<mis_seminarios.size();i++)
          {salida<<mis_seminarios[i];}
       }
    else{cout<<"Error al guardar"<<endl;}
salida.close();

//Tfe------------------------------------------------------------------------------------------
   salida.open("Tfe.txt",ios::out);
    if(salida.is_open())
      {
       for(unsigned i=0;i<mis_tfe.size();i++)
          {salida<<mis_tfe[i];}
      }
    else{cout<<"Error al guardar"<<endl;}

 salida.close();
}

unsigned Campus_Virtual::listas_seminario()//Imprimimos todos los seminarios y elegimos la que queremos modificar crear o eliminar
{
    char posicion;

    for(unsigned i=0;i<mis_seminarios.size();i++)
       {
        cout<<"\nFecha del seminario["<<i<<"]:"<<mis_seminarios[i]->getdia()<<"/"<<mis_seminarios[i]->getmes()<<"/"<<mis_seminarios[i]->getanio()<<endl;
        cout<<"Codigo del seminario:"<<mis_seminarios[i]->getseminario_codigo()<<"\n"<<endl;
       }
    do{
        do{
            cout<<"\nIntroduzca el numero del seminario: ";
            cin.ignore();
            cin.get(posicion);
        }while(posicion<48 || posicion>57);
    }while(posicion-48>mis_seminarios.size());

    return posicion-48;//Devuelve la posicion
}
/*Igual que en los seminarios*/
unsigned Campus_Virtual::listas_asignatura()
{
    char posicion;
    for(unsigned i=0;i<mis_asignaturas.size();i++)
       {
        cout<<"\nTitulacion de la asignatura["<<i<<"]:"<<mis_asignaturas[i]->getnombre_titulacion()<<endl;
        cout<<"Nombre de la asignatura:"<<mis_asignaturas[i]->getnombre()<<endl;
        cout<<"Codigo de la asignatura:"<<mis_asignaturas[i]->getasignatura_codigo()<<"\n"<<endl;
       }
    do{
        do{
            cout<<"\nIntroduzca el numero de la asignatura: ";
            cin.ignore();
            cin.get(posicion);
        }while(posicion<48 || posicion>57);
    }while(posicion-48>mis_asignaturas.size());

    return posicion-48;
}

unsigned Campus_Virtual::listas_tfe()
{
    char posicion;
    for(unsigned i=0;i<mis_tfe.size();i++)
       {
        cout<<"\nTitulacion del tfe[:"<<i<<"]:"<<mis_tfe[i]->gettfe()<<endl;
        cout<<"Codigo del tfe["<<i<<"]:"<<mis_tfe[i]->gettfe_codigo()<<"\n"<<endl;
       }
    do{
        do{
            cout<<"\nIntroduzca el numero del tfe: ";
            cin.ignore();
            cin.get(posicion);
        }while(posicion<48 || posicion>57);
    }while(posicion-48>mis_tfe.size());

return posicion-48;
}

void Campus_Virtual::entrada_archivos(ifstream &entrada)
{
//Profesores-------------------------------------------------------------------------------
entrada.open("Profesores.txt",ios::in);

  if(entrada.is_open())
    {
     do{
        Profesor nuevo("Nombre","codeing");//Se crea un objeto
        entrada>>nuevo;//Se pasan los parametros al objeto y el operador sobrecargado >> pasa los atributos principales
        entrada.ignore();//Limpia el buffer para que pueda leer los demas profesores
        mis_profesores.push_back(nuevo);//Los almacena en la ultima posicion del vector
       }while(!entrada.eof());//Lee profesores hasta que se termine el archivo

      mis_profesores.pop_back();//Elimina la ultima posicion del vector
      entrada.close();//Cerramos el archivo
 }
 else{cout<<"Ha ocurrido un error con el archivo.No han podido cargarse los datos"<<endl;}

//Administradores--------------------------------------------------------------------------
  entrada.open("Administradores.txt",ios::in);
if(entrada.is_open()){
   do{
        Administrador nuevo("Nombre","codeing");
         entrada>>nuevo;
         entrada.ignore();
         mis_administradores.push_back(nuevo);

    } while(!entrada.eof());
   entrada.close();
}
else{
   cout<<"Ha ocurrido un error con el archivo.No han podido cargarse los datos"<<endl;
}

 //Alumnos--------------------------------------------------------------------------------
  entrada.open("Alumnos.txt",ios::in);
if(entrada.is_open())
  {
    Alumno nuevo("Nombre","Titulacion","0000000","\0");
    while(entrada>>nuevo)
    {
     unsigned long tam=0;//Tamaño seminario
     unsigned long tam2=0;//Tamaño asignatura
     int existencia=0;//Ver si hay tfe

     mis_alumnos.push_back(new Alumno(nuevo.getnombre(),nuevo.getnombre_titulacion(),nuevo.getnia(),nuevo.get_password()));//Crea el alumno en el programa
     entrada>>tam;//Cogemos el tamaño

     if(tam>0)
       {
        for(unsigned i=0;i<tam;i++)//Bucle para leer el seminario y sus atributos
           {
            int dia,mes,anio,plazas;
            string codigo;

            entrada>>dia>>mes>>anio;
            entrada>>codigo;
            entrada>>plazas;
            mis_alumnos[mis_alumnos.size()-1]->fichero_seminario(codigo);//Guarda el codigo en la ultima posicion del vector
           }
       }
/*Igual que seminarios*/
     entrada>>tam2;
     if(tam2>0)
       {
        for(unsigned i=0;i<tam2;i++)
           {
            string titulacion,nombre,estado,codigo;
            int creditos;

            entrada.ignore();
            getline(entrada,nombre);
            getline(entrada,titulacion,'\n');
            entrada>>codigo;
            entrada>>estado;
            entrada>>creditos;
            mis_alumnos[mis_alumnos.size()-1]->fichero_asignatura(codigo);
          }
        }
     entrada>>existencia;//Leemos si hay o no tfe
     if(existencia==1)//Comprueba si hay tfe y pasa los parametros
       {//Como solo es uno no hace falta el for
        string titulacion,codigo,estado;
        entrada.ignore();
        getline(entrada,titulacion);
        entrada>>codigo;
        entrada>>estado;
        mis_alumnos[mis_alumnos.size()-1]->fichero_tfe(codigo);
       }
  entrada.ignore();
  }
entrada.close();

}
else{cout<<"Ha ocurrido un error con el archivo.No han podido cargarse los datos"<<endl;}

//Seminarios-------------------------------------------------------------------------------
    entrada.open("Seminarios.txt",ios::in);
  if(entrada.is_open())
    {
     Seminario nuevo(0,0,0,0,"eln1111","estado");
     while(entrada>>nuevo)
         {
          unsigned tam=0;//Tamaño lista alumnos
          int exist;//Leer ponente
          int existencia;//Leer responsable

          mis_seminarios.push_back(new Seminario(nuevo.getdia(),nuevo.getmes(),nuevo.getanio(),nuevo.getplazas(),nuevo.getseminario_codigo(),nuevo.getestado()));
          entrada>>exist;//Lee si hay profe
          Profesor prueba("Nombre","codeing");

          if(exist==1)
            {
             bool professor=false;
             string nombre,codigo;

             entrada.ignore();
             getline(entrada,nombre);//Lee el nombre
             entrada>>codigo;//Lee el codigo
             prueba.setprofesor(nombre,codigo);

             for(unsigned i=0;i<mis_profesores.size() && professor==false;i++)//Comprobamos el codigo del profesor con los demas profesores creados
                {
                 if(prueba.getcodigo()==mis_profesores[i].getcodigo())
                   {
                    mis_seminarios[mis_seminarios.size()-1]->meter_ponente(mis_profesores[i]);//Si se encuentra se llama a la funcion de meter ponente
                    professor=true;
                   }
                 else{professor=false;}
                }
           }

          /*Igual que ponente*/
           entrada>>existencia;
           if(existencia==1)
             {
               bool professor=false;
               string nombre,codigo;

               entrada.ignore();
               getline(entrada,nombre);
               entrada>>codigo;
               prueba.setprofesor(nombre,codigo);

               for(unsigned i=0;i<mis_profesores.size() && professor==false;i++)
                  {
                   if(prueba.getcodigo()==mis_profesores[i].getcodigo())
                     {
                      mis_seminarios[mis_seminarios.size()-1]->meter_profesor_responsable(mis_profesores[i]);
                      professor=true;
                     }
                  else{professor=false;}
                 }
            }
       /*Hace lo mismo que con los profesores*/
           entrada>>tam;//Lee el tamaño
           if(tam>0)
             {
              Alumno inside("Nombre","titulacion","0000000","\0");

               for(unsigned i=0;i<tam;i++)
                  {
                   bool alumni=false;
                   string nombre,nia,titulacion;

                   entrada.ignore();
                   getline(entrada,nombre);
                   entrada>>nia;
                   entrada.ignore();
                   getline(entrada,titulacion);
                   inside.setalumno(nombre,titulacion,nia);

                   for(unsigned a=0;a<mis_alumnos.size() && alumni==false;a++)
                      {
                       if(inside.getnia()==mis_alumnos[a]->getnia())
                         {
                          mis_seminarios[mis_seminarios.size()-1]->meter_alumnos(mis_alumnos[a]);
                          alumni=true;
                         }
                       else{alumni=false;}
                   }
               }
           }
      }
     entrada.close();
  }
  else{
     cout<<"Ha ocurrido un error con el archivo.No han podido cargarse los datos"<<endl;
  }

//Asignaturas---------------------------------------------------------------------------
  entrada.open("Asignaturas.txt",ios::in);
if(entrada.is_open())
  {
   Asignatura nuevo("titulacion","asignatura",0,"eln0000","estado");
   while(entrada>>nuevo)
        {
         unsigned tam=0;//Tamaño alumno
         int exist=0;//Primer profe
         int esistencia=0;//Segundo profe
         mis_asignaturas.push_back(new Asignatura(nuevo.getnombre_titulacion(),nuevo.getnombre(),nuevo.getcreditos(),nuevo.getasignatura_codigo(),nuevo.getestado()));

       /*Igual que seminario pero tiene una funcion mas que es añadir las notas*/
         entrada>>exist;
         Profesor prueba("Nombre","codeing");

         if(exist==1)
           {
            bool professor=false;
            string nombre,codigo;
            entrada.ignore();
            getline(entrada,nombre);
            entrada>>codigo;
            prueba.setprofesor(nombre,codigo);

           for(unsigned i=0;i<mis_profesores.size() && professor==false;i++)
              {
               if(prueba.getcodigo()==mis_profesores[i].getcodigo())
                 {
                  mis_asignaturas[mis_asignaturas.size()-1]->meter_profesores(mis_profesores[i]);
                  professor=true;
                 }
               else{professor=false;}
              }
          }

         entrada>>esistencia;
         if(esistencia==1)
           {
             bool professor=false;
             string nombre,codigo;

             entrada.ignore();
             getline(entrada,nombre);
             entrada>>codigo;
             prueba.setprofesor(nombre,codigo);

             for(unsigned i=0;i<mis_profesores.size() && professor==false;i++)
                {
                 if(prueba.getcodigo()==mis_profesores[i].getcodigo())
                   {
                    mis_asignaturas[mis_asignaturas.size()-1]->meter_segundo(mis_profesores[i]);
                    professor=true;
                   }
                 else{professor=false;}
             }
         }

         entrada>>tam;//Se lee tamaño de los alumnos
         if(tam>0)
           {
             Alumno inside("Nombre","titulacion","0000000","\0");

             for(unsigned i=0;i<tam;i++)
                {
                 bool alumni=false;//Ver si esta el alumno y poder salirse del bucle
                 float nota;
                 string nombre,nia,titulacion;

                 /*Lee datos alumnos*/
                 entrada.ignore();
                 getline(entrada,nombre);
                 entrada>>nia;
                 entrada.ignore();
                 getline(entrada,titulacion);
                 entrada>>nota;
                 inside.setalumno(nombre,titulacion,nia);

                 for(unsigned a=0;a<mis_alumnos.size() && alumni==false;a++)//Lee los alumnos
                    {
                     if(inside.getnia()==mis_alumnos[a]->getnia())//Compara el nia con los demas alumnos
                       {
                        mis_asignaturas[mis_asignaturas.size()-1]->meter_alumno(mis_alumnos[a]);//Se introduce el alumno
                        mis_asignaturas[mis_asignaturas.size()-1]->setnota(nota,a);//Se mete su nota
                        alumni=true;
                       }
                     else{alumni=false;}
                 }

             }
         }
        entrada.ignore();
    }
   entrada.close();
}
else{cout<<"Ha ocurrido un error con el archivo.No han podido cargarse los datos"<<endl;}

//Tfe--------------------------------------------------------------------------------------
entrada.open("Tfe.txt",ios::in);
if(entrada.is_open())
  {/*Igual que seminario pero con un solo alumno*/
   Tfe nuevo("Titulacion","eln0000","estado");
   while(entrada>>nuevo)
       {
        int exist=0;//Si hay tutor
        int existencia=0;//Si hay cotutor
        int alumno=0;//Si hay alumno

        mis_tfe.push_back(new Tfe(nuevo.gettfe(),nuevo.gettfe_codigo(),nuevo.get_estado()));

        entrada>>exist;
        Profesor prueba("Nombre","codeing");
        if(exist==1)
          {
           bool professor=false;
           string nombre,codigo;

           entrada.ignore();
           getline(entrada,nombre);
           entrada>>codigo;
           prueba.setprofesor(nombre,codigo);

           for(unsigned i=0;i<mis_profesores.size() && professor==false;i++)
              {
               if(prueba.getcodigo()==mis_profesores[i].getcodigo())
                 {
                  mis_tfe[mis_tfe.size()-1]->meter_tutor(mis_profesores[i]);
                  professor=true;
                 }
               else{professor=false;}
           }
       }

       entrada>>existencia;
       if(existencia==1)
         {
          bool professor=false;
          string nombre,codigo;

          entrada.ignore();
          getline(entrada,nombre);
          entrada>>codigo;
          prueba.setprofesor(nombre,codigo);

          for(unsigned i=0;i<mis_profesores.size() && professor==false;i++)
             {
              if(prueba.getcodigo()==mis_profesores[i].getcodigo())
                {
                 mis_tfe[mis_tfe.size()-1]->meter_cotutor(mis_profesores[i]);
                 professor=true;
                }
               else{professor=false;}
           }
       }

       entrada>>alumno;
    /*Ver si existe el alumno, sin for porque solo hay uno*/
       if(alumno==1)
         {
            Alumno inside("Nombre","titulacion","0000000","\0");//El \0 pone la contraseña vacia

            bool alumni=false;
            string nombre,nia,titulacion;

            entrada.ignore();
            getline(entrada,nombre);
            entrada>>nia;
            entrada.ignore();
            getline(entrada,titulacion);
            inside.setalumno(nombre,titulacion,nia);

               for(unsigned a=0;a<mis_alumnos.size() && alumni==false;a++)
                  {
                   if(inside.getnia()==mis_alumnos[a]->getnia())
                     {
                      mis_tfe[mis_tfe.size()-1]->meter_alumno(mis_alumnos[a]);
                      alumni=true;
                     }
                  else{alumni=false;}
           }
       }
  }
 entrada.close();
}
else{cout<<"Ha ocurrido un error con el archivo.No han podido cargarse los datos"<<endl;}
/*Parte para asignar los recursos a los alumnos*/ //************************************************************************

  bool resources=false;//Ver si esta o no el recurso
  for(unsigned al=0;al<mis_alumnos.size();al++)
     {
      if(mis_alumnos[al]->gettamanio_comprobante()>0)//Vemos si hay seminarios
        {
         for(unsigned c=0;c<mis_alumnos[al]->gettamanio_comprobante();c++)//bucle para introducir seminarios
            {
             resources=false;
             for(unsigned a=0;a<mis_seminarios.size() && resources==false;a++)
                {
                if(mis_alumnos[al]->getcomprobante_semi(c)==mis_seminarios[a]->getseminario_codigo())//Si coincide se mete el seminario en la lista de seminarios del alumno
                  {
                   mis_alumnos[al]->aniadir_seminario(mis_seminarios[a]);
                   resources=true;
                  }
                else{resources=false;}
               }
           }
     }

     resources=false;
/*Igual que el de seminario*/
     if(mis_alumnos[al]->gettamanio_comprobante2()>0)
       {
        for(unsigned c=0;c<mis_alumnos[al]->gettamanio_comprobante2();c++)
           {
            resources=false;
            for(unsigned a=0;a<mis_asignaturas.size() && resources==false;a++)
               {
                if(mis_alumnos[al]->getcomprobante_asign(c)==mis_asignaturas[a]->getasignatura_codigo())
                  {
                   mis_alumnos[al]->aniadir_asignatura(mis_asignaturas[a]);
                   resources=true;
                  }
                else{resources=false;}
            }
        }
    }
/*Igual pero solo hay un comprobante para el tfe*/
       resources=false;
       for(unsigned a=0;a<mis_tfe.size() && resources==false;a++)
          {
           if(mis_alumnos[al]->getcomprobante_tfe()==mis_tfe[a]->gettfe_codigo())
             {
              mis_alumnos[al]->aniadir_tfe(mis_tfe[a]);
              resources=true;
             }
          else{resources=false;}
         }
      }
}
