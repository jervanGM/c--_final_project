TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    administrador.cpp \
    tfe.cpp \
    seminario.cpp \
    recurso.cpp \
    alumno.cpp \
    profesor.cpp \
    campus_virtual.cpp \
    usuario.cpp \
    asignatura.cpp

HEADERS += \
    alumno.h \
    administrador.h \
    profesor.h \
    usuario.h \
    seminario.h \
    asignatura.h \
    tfe.h \
    recurso.h \
    campus_virtual.h
