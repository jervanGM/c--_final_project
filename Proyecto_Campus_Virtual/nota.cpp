#include<iostream>
#include"nota.h"

using namespace std;

Nota::Nota(float nota){//Constructores y metodos de la clase nota,no usada en este hito
    _nota=nota;
}
Nota::Nota(const Nota &N){
    _nota=N._nota;
}
float Nota::getnota(){
    return _nota;
}
void Nota::setnota(float nota){
    _nota=nota;
}
