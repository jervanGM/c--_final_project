#include "seminario.h"
#include "tfe.h"
#include "asignatura.h"

#ifndef LISTAS_H
#define LISTAS_H
class Lista{
private:
    int cuenta_s;
    int cuenta_a;
    Seminario *lista_semi[10];
    Asignatura *lista_asignaturas[10];
    Tfe *mi_tfe;
public:
    Lista();
    ~Lista();
    void aniadir_seminario(Seminario *unir);
    void aniadir_asignatura(Asignatura *unir);
    void aniadir_tfe(Tfe *unir);

    void imprimir_lista();
};

#endif // LISTAS_H
