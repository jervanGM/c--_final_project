
#pragma once
#ifndef ALUMNO_H
#define ALUMNO_H
#include "usuario.h"
#include "seminario.h"
#include "asignatura.h"
#include "tfe.h"
#include <vector>
class Seminario;
class Asignatura;
class Tfe;
using namespace std;


class Alumno:public Usuario{//Atributos,metodos y constructores de la clase alumno

private:
    bool ocupado;//Ver si el tfe esta disponible
    vector<string>_comprobante_semi;//Se usa este atributo para ficheros,para guardar el codigo de los seminarios inscritos
    vector<string>_comprobante_asign;//Se usa este atributo para ficheros,para guardar el codigo de las asignaturas inscritos
    string _comprobante_tfe;//Se usa este atributo para ficheros,para guardar el codigo del tfe
    string _nombre_alumno;
    string _NIA;
    string _nombre_titulacion;
    vector<Seminario**>lista_semi;
    vector<Asignatura**>lista_asign;//Listas de seminarios y asignaturas inscritas por el alumno
    Tfe **_mi_tfe;//Tfe del alumno


public:
    void setalumno(string nombre_alumno,string nombre_titulacion,string NIA);
    string getnombre();
    string getnombre_titulacion();
    string getnia();
    string getcomprobante_semi(unsigned c);//Se usa en ficheros para comprobar los seminarios del alumno
    string getcomprobante_asign(unsigned a);//Se usa en ficheros para comprobar las asignaturas del alumno
    string getcomprobante_tfe();//Se usa en ficheros para comprobar el tfe del alumno
    unsigned long gettamanio_comprobante();//Devuelve el tamaño del atributo comprobante_semi
    unsigned long gettamanio_comprobante2();//Devuelve el tamaño del atributo comprobante_asign

    Alumno(const string nombre_alumno,const string nombre_titulacion,const string NIA,const string password);
    Alumno(const Alumno &A);

    void imprimir_listas();//imprimer los recursos inscritos del alumno
    void fichero_seminario(string codigo);//Se usa para guardar los codigos de seminarios inscritos en el vector comprobante semi
    void aniadir_seminario(Seminario* &lista);//darse alta seminario
    void darse_baja_seminario(string expulsar);
    void fichero_asignatura(string codigo);//Se usa para guardar los codigos de asignarturas inscritas en el vector comprobante asign
    void aniadir_asignatura(Asignatura* &lista);//darse alta asignatura
    void darse_baja_asignatura(string expulsar);//Sacar la asignatura de la lista de asign
    void fichero_tfe(string codigo);//Se usa para guardar el codigo del tfe inscrito en el atribubto mi tfe
    void aniadir_tfe(Tfe* &unico);//Esta funcion es equivalente a darse_alta_tfe
    void darse_baja_tfe(string expulsar);
    void expulsar_alumno();//Funcion para sacar alumnos de la lista de alumnos de los recursos
    void comprobar_codigo_id(string &codigo_id);

    friend ofstream& operator<<(ofstream& salida,Alumno* &lista);
    friend ifstream& operator>>(ifstream& entrada,Alumno &lista);

};
#endif // ALUMNO_H
