#pragma once
#include <iostream>
#include <alumno.h>
#ifndef NOTA_H      //Esta parte se vera en la entrega final
#define NOTA_H
using namespace std;
class Nota{
private:
    float _nota;
public:
    void setnota(float nota);
    float getnota();
    Nota(const Nota &N);
    Nota(const float nota);


};

#endif // NOTA_H
