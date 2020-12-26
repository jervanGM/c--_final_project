#pragma once
#ifndef TFE_H
#define TFE_H

#include<iostream>
#include "profesor.h"
#include"recurso.h"
#include "alumno.h"

class Profesor;
class Alumno;
using namespace std;

class Tfe:public Recurso
{
private:
    string _titulacion;
    /*Estos dos atributos se usan en meter_alumno para comprobar si el tfe esta lleno u ocupado*/
    bool _ocupado;
    bool _disponible;

    Profesor *_tutor;
    Profesor *_cotutor;
    Alumno **mi_alumno;//Alumno inscrito al tfe

public:
    void settfe(string nombre_tfe,string codigo_recurso,string estado);
    void meter_tutor(Profesor &Tut);//Introducimos un tutor para el tfe
    void meter_cotutor(Profesor &C);//Introducimos un cotutor para el tfe
    bool meter_alumno(Alumno* &al);//Metemos un alumno en el tfe
    void sacar_alumno();//Lo expulsamos de este
    void sacar_profesor(string codigo);//Elimina el profesor del tfe
    void expulsar_alumno();//En el caso de que se elimine el tfe sacamos al alumno de el
    void imprimir_tutores();//Imprime los profes del tfe
    void imprimir_alumno();//Imprime el alumno
    int comprobar_profesor_tfe(string codigo_id);//Vemos si hay profesores en el tfe y quienes son a partir de su codigo para saber si pueden modificarlo o no
    string gettfe();//devuelve el nombre del la titulacion
    string gettfe_codigo();
    string get_estado();
    Tfe(const string titulacion,const string codigo_recurso,const string estado);
    Tfe(const Tfe &T);
    void imprimir_tfe();//Imrpime atributos del tfe

    friend ofstream& operator<<(ofstream& salida,Tfe* &lista);
    friend ifstream& operator>>(ifstream& entrada,Tfe&lista);
};

#endif // TFE_H
