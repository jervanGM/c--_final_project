#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H
#include <iostream>
#include "usuario.h"
#include "alumno.h"
#include "profesor.h"
#include<vector>
using namespace std;

class Administrador:public Usuario//Clase herencia de Usuario
{
private:
    string _nombre_admin;
public:
    void setadmin(string nombre_admin,string codigo_id);
    string getcode();
    string getnombre();
    Administrador(const string nombre_admin, const string codigo_id);//Constructor parametrizado
    Administrador(const Administrador &Admin);//Constructor copia

    void dar_alta_Seminario(vector<Seminario*>&lista);//Funcion que permite al administrados crear seminarios
    void dar_baja_Seminario(vector<Seminario*>&baja,unsigned a);//Funcion que permite al administrados eliminar seminarios por lo que se le pasa la posicion de seminario a eliminar y el vector
    void modificar_Seminario(vector<Seminario*>&modificar,unsigned s);//Funcion que permite al administrados modificar seminarios y para ello se le pasa el vector y la posicion del seminario a modificar
    void meter_profesores_seminario(Seminario* &lista,vector<Profesor>&lista_profe);//Funcion que se usa para introducir los profesores a los seminarios
/*El resto realizan la misma funcion tanto para asignatura, tfe, alumno y profesor y administrador*/
    void dar_alta_Asignatura(vector<Asignatura*>&lista);
    void dar_baja_Asignatura(vector<Asignatura*>&baja,unsigned a);
    void modificar_Asignatura(vector<Asignatura*>&modificar,unsigned as);
    void meter_profesores_asignatura(Asignatura* &lista,vector<Profesor>&lista_profe);

    void dar_alta_Tfe(vector<Tfe*>&lista);
    void dar_baja_Tfe(vector<Tfe*>&baja,unsigned a);
    void modificar_Tfe(vector<Tfe*>&modificar,unsigned t);
    void meter_profesores_tfe(Tfe* &lista,vector<Profesor>&lista_profe);

    void dar_alta_Alumno(vector<Alumno*>&alta);
    void dar_baja_Alumno(vector<Alumno*>&baja,unsigned a);
    void modificar_Alumno(vector<Alumno*>&modifica,unsigned m);

    void dar_alta_Profesor(vector<Profesor>&alta);
    void dar_baja_Profesor(vector<Profesor>&baja,unsigned a);
    void modificar_Profesor(vector<Profesor>&modificar,unsigned p);

    void dar_alta_Administrador(vector<Administrador>&alta);
    void dar_baja_Administrador(vector<Administrador>&baja,unsigned a);
    void modificar_Administrador(vector<Administrador>&modificar,unsigned ad);

    void comprobar_codigo_id(string &codigo_id);//Uso de la funcion virtual para comprobar el codigo
    void imprimir_datos(vector<Seminario*>mis_seminarios,vector<Asignatura*>mis_asignaturas,vector<Tfe*>mis_tfe,vector<Alumno*>mis_alumnos,vector<Profesor>mis_profesores,vector<Administrador>mis_administradores);
    /*Funcion que imprime todos los datos*/
    /*Las demas clases tambien los tienen*/
    friend ofstream& operator<<(ofstream& salida,vector<Administrador>&lista);//Sobrecargamos el operador para pasar de una los datos
    friend ifstream& operator>>(ifstream& entrada,Administrador &lista);//Sobrecargamos el operador para leer de una los datos

};

#endif // ADMINISTRADOR_H
