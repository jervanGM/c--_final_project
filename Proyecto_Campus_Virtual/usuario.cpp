#include<iostream>
#include"usuario.h"
#include"administrador.h"

using namespace std;//Este cpp esta vacio provisionalmente,usado en la entrega final;


void Usuario::comprobar_codigo_id(string &codigo_id)
{

}

void Usuario::set_password(string password)
{
    _password=password;
}

string Usuario::get_password(){
    return _password;
}
