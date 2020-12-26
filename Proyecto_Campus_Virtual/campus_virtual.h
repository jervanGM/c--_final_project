#ifndef CAMPUS_VIRTUAL_H
#define CAMPUS_VIRTUAL_H

#include "seminario.h"
#include "asignatura.h"
#include "tfe.h"
#include "alumno.h"
#include "administrador.h"
#include "profesor.h"
#include <vector>
#include<fstream>
using namespace std;

class Campus_Virtual
{
private:
    //Usamos vectores de punteros en las clases que se pasan datos entre ellas para poder modificarlos sin realizar copias
    vector<Seminario*>mis_seminarios;//vector de clases para añadir cada clase al registro segun la opcion que elija el administrador
    vector<Asignatura*>mis_asignaturas;
    vector<Tfe*>mis_tfe;
    vector<Alumno*>mis_alumnos;
    vector<Administrador>mis_administradores;
    vector<Profesor>mis_profesores;
public:
    void inicio();
    Campus_Virtual();//parametros para indicar en el main la cantidad inicial de cada clase
   ~Campus_Virtual();
    void menu_admin(unsigned ad);//Aqui se realizan las funciones del admin
    void menu_alumno(unsigned a);//Funciones para los menus de cada usuario,se pasa la posicion del usuario que ha iniciado sesion
    void menu_profesor(unsigned pr, string codigo_id);//Aqui se realizan las funciones del profesor y le pasamos el codigo para poder ver si esta metido en los recursos y puede modificarlos
    unsigned listas_asignatura();
    unsigned listas_seminario();
    unsigned listas_tfe();
    /*Ficheros de entrada y salida de datos*/
    void salida_archivos(ofstream &salida);
    void entrada_archivos(ifstream &entrada);
};

#endif // CAMPUS_VIRTUAL_H
