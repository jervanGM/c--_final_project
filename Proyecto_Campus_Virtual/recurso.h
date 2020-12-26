#include<iostream>

#ifndef RECURSO_H
#define RECURSO_H
using namespace std;
class Recurso
{
protected://Se pone como protected para inicializar dichos atributos en los constructores de las clases hijas
    string _estado;//estado del recurso
    string _codigo_recurso;
public:
    virtual void sacar_profesor(string codigo)=0;
};

#endif // RECURSO_H
