#pragma once
#ifndef PROFESOR_H
#define PROFESOR_H

#include "usuario.h"
#include"asignatura.h"
#include"seminario.h"
#include"tfe.h"
#include<vector>
#include<fstream>
using namespace std;
class Seminario;
class Asignatura;
class Tfe;

class Profesor:public Usuario //Las funciones del profesor se veran en la entrega final
{
private:
    string _nombre_profesor;

public:
    void setprofesor(string nombre_profesor,string codigo_id);
    string getnombre();
    string getcodigo();
    Profesor(const string nombre_profesor,const string codigo_id);
    Profesor(const Profesor &P);
    void cambiar_notas(Asignatura* &datos,unsigned j);//Funcion que se le llama desde el menu profesor y se le pasa la asignatura y la posicion del alumno en la lista
    void modificar_Seminario(vector<Seminario*>&modificar,unsigned s);//Permite modificar el seminario en el que estas inscrito
    void modificar_Asignatura(vector<Asignatura*>&modificar,unsigned as);//Permite modificar la asignatura en el que estas inscrito
    void modificar_Tfe(vector<Tfe*>&modificar,unsigned t);//Permite modificar el tfe en el que estas inscrito
    void eliminar_profesor_recursos(vector<Seminario*>&lista_semi,vector<Asignatura*>&lista_asigm,vector<Tfe*>&lista_tfe);//Funcion destinada a eliminar el profesor de todos sus recursos cuando este es eliminado por el administrador
    void comprobar_codigo_id(string &codigo_id);//Funcion virtual para el codigo del profe

    friend ostream& operator<<(ostream& salida,const Profesor& lista);
    friend istream& operator>>(istream& entrada,Profesor& lista);
};

#endif // PROFESOR_H
