
#ifndef USUARIO_H
#define USUARIO_H
#include<iostream>
#include<vector>
using namespace std;
class Seminario;
class Profesor;
class Asignatura;
class Tfe;
class Administrador;
class Alumno;

class Usuario
{
protected://Luego en los constructores de las clases hijas se inicializa el atributo;
    string _codigo_id;
    string _password;//extra del entregable, usuarios tienen un codigo de identificacion y su propia contraseña
public:

    virtual void comprobar_codigo_id(string &codigo_id);//Funcion virtual que se utilizada para comprobar que el codigo introducido es correcto para cada uno de los usuario y recurso
    void set_password(string password);
    string get_password();
};

#endif // USUARIO_H
