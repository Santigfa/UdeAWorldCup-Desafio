#ifndef OBJETIVOFIJO_H
#define OBJETIVOFIJO_H

#include "Objetivo.h"

class ObjetivoFijo : public Objetivo
{
public:
    ObjetivoFijo();
    ObjetivoFijo(const ObjetivoFijo&);
    ~ObjetivoFijo();

    void verificar();
};

#endif