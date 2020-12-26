
#pragma once
#ifndef SEMINARIO_H
#define SEMINARIO_H
#include<iostream>
#include "recurso.h"
#include "alumno.h"
#include "profesor.h"
#include<vector>
class Alumno;
class Profesor;   //Forward declaration para alumnos y profesores
using namespace std;

class Seminario:public Recurso
{
private:
    unsigned _nplazas;
    vector<Alumno**>lista_alumnos;//Servirá para las funciones meter y sacar alumno
    Profesor *_p_responsable;//Punteros de los profesores encargados del seminario
    Profesor *_ponente;
    int _dia;
    int _mes;
    int _anio;

public:
    void setseminario(int dia,int mes,int anio,string codigo_recurso, string estado,int nplazas);
    void meter_ponente(Profesor &nuevoP);//Funcion para introducir en el seminario a un profesor
    void meter_profesor_responsable(Profesor &nuevoR);//Funcion para introducir en el seminario a un segundo profesor
    bool meter_alumnos(Alumno* &mis_alumnos);//Funcion para introducir en el seminario a un profesor
    void sacar_alumno(unsigned a);//Elimina el alumno de la lista alumno del seminario
    void sacar_profesor(string codigo);//Elimina el profesor del seminario
    void imprimir_alumnos();//Imprime la lista alumnos del seminario
    void expulsar_alumnos_seminario();//En el caso de que se elimine el seminario se saca a todos los alumnos de el
    int comprobar_profesor_seminario(string codigo_id);//Funcion para ver si un profesor pertenece al seminario o no a traves de su codigo de identificacion
    void comprobar_alumno_seminario(string nia);//Funcion que se usa para saber si el alumno esta en el seminario buscandolo con el nia y poder darlo de baja
    int getdia();
    int getmes();
    int getanio();
    int getplazas();
    string getestado();
    unsigned getplazasocupadas();
    string getseminario_codigo();
    Seminario(const int dia,const int mes,const int anio,const int nplazas,const string codigo_recurso, const string estado);
    Seminario(const Seminario &S);
    void imprimir_seminario();//Funcion encargada de imprimir los atributos del seminario
    friend ostream& operator<<(ostream& salida,Seminario* &lista);
    friend istream& operator>>(istream& entrada,Seminario&lista);
};

#endif // SEMINARIO_H
