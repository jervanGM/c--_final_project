#include<iostream>
#include"listas.h"

using namespace std;

Lista::Lista(){
    cuenta_s=0;
    cuenta_a=0;
}
Lista::~Lista(){
    delete[] *lista_semi;
    delete[] *lista_asignaturas;
}

void Lista::aniadir_asignatura(Asignatura *unir){
    lista_asignaturas[cuenta_a]=unir;
    cuenta_a++;
}

void Lista::aniadir_seminario(Seminario* unir){
    lista_semi[cuenta_s]=unir;
    cuenta_s++;
}

void Lista::aniadir_tfe(Tfe *unir){
    mi_tfe=unir;
}

void Lista::imprimir_lista(){
    cout<<"Seminarios inscritos:"<<endl;
    if(cuenta_s>0){
        for(int i=0;i<cuenta_s;i++){
            cout<<"\nFecha seminario:"<<lista_semi[i]->getdia()<<"/"<<lista_semi[i]->getmes()<<"/"<<lista_semi[i]->getanio()<<endl;
            cout<<"Codigo del seminario:"<<lista_semi[i]->getseminario_codigo()<<endl;
            cout<<"Plazas totales:"<<lista_semi[i]->getplazas()<<endl;
        }
    }
    else{
        cout<<"[El alumno no esta inscrito a ningun seminario]"<<endl;
    }
    cout<<"Asingnaturas inscritas:"<<endl;
    cout<<endl;
    if(cuenta_a>0){
        for(int i=0;i<cuenta_a;i++){
        cout<<"Nombre de la asignatura: "<<lista_asignaturas[i]->getnombre()<<endl;
        cout<<"Nombre de su titulacion: "<<lista_asignaturas[i]->getnombre_titulacion()<<endl;
        cout<<"Creditos: "<<lista_asignaturas[i]->getcreditos()<<endl;
        cout<<"Estado: "<<lista_asignaturas[i]->getestado()<<endl;
        }
    }
    else{
        cout<<"[El alumno no esta inscrito en ninguna asignatura]"<<endl;
    }
    cout<<"Tfe del alumno:"<<endl;
    cout<<endl;
    cout<<"Nombre titulacion: "<<mi_tfe->gettfe()<<endl;
    cout<<"Codigo del tfe: "<<mi_tfe->gettfe_codigo()<<endl;
    cout<<"Estado del tfe: "<<mi_tfe->get_estado()<<endl;

}
