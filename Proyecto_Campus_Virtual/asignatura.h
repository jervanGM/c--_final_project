#pragma once
#ifndef ASIGNATURA_H
#define ASIGNATURA_H

#include "recurso.h"
#include <iostream>
#include "alumno.h"
#include "nota.h"
#include "profesor.h"
#include <vector>

using namespace std;
class Alumno;
class Profesor;

class Asignatura:public Recurso//Asignas atributos y herencia de la clase Asignatura
{
private:
    string _nombre_titulacion;
    string _nombre_asignatura;
    bool plaza_ocupada;//Se usa para comprobar si el alumno esta dentro de un asignatura
    int _creditos;
    vector<Alumno**>lista_alumnos;//Lista de alumnos,notas y profesores de la asignatura
    vector<float>notas;//lista de notas
    Profesor *_uno;//primer profesor
    Profesor *_dos;//segundo profesor

public:

    void setasignatura(string nombre_titulacion,string nombre_asignatura,int creditos,string codigo_recurso, string estado);
    int comprobar_profesor_asignatura(string codigo_id);//Funcion para comprobar los profesores que tiene la asignatura y ver si estos pueden modificarlas
    void cambiar_notas_alumnos(unsigned j);//Funcion que cambia las notas del vector notas
    void setnota(float nota,unsigned a);
    void meter_profesores(Profesor &primero);//Funciones para meter un profesor
    void meter_segundo(Profesor &segundo);//Funciones para meter un segundo profesor
    bool meter_alumno(Alumno* &lista);//Funcion para meter alumnos
    void sacar_alumno(unsigned a);//Eliminar alumno de la lista de alumnos de asignatura
    void sacar_profesor(string codigo);//Elimina el profesor de la asignatura
    void expulsar_alumnos_asignatura();//Si se borra la asignatura se da de baja a todos los alumnos de ella
    void comprobar_alumno_asignatura(string nia);//Funcion que se usa para saber si el alumno esta en la asignatura y poder darlo de baja
    void imprimir_profesores();//Imprime profesores de la asignatura
    void imprimir_alumnos();//Imprime los alumnos de la asignatura

    string getnombre();
    string getnombre_titulacion();
    string getasignatura_codigo();
    string getestado();
    int getcreditos();
    Asignatura(const string nombre_titulacion,const string nombre_asignatura,const int creditos,const string codigo_recurso, const string estado);
    Asignatura(const Asignatura &As);

    void imprimir_asignatura();//Imprime los atributos de la asignatura

    friend ofstream& operator<<(ofstream& salida,Asignatura* &lista);
    friend ifstream& operator>>(ifstream& entrada,Asignatura&lista);

};

#endif // ASIGNATURA_H
