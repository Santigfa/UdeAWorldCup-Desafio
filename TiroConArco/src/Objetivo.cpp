#include "Objetivo.h"

Objetivo::Objetivo()
{
    x = 0;
    y = 0;
    radio = 1;
    activo = true;
}

Objetivo::Objetivo(const Objetivo& o)
{
    x = o.x;
    y = o.y;
    radio = o.radio;
    activo = o.activo;
}

Objetivo::~Objetivo()
{
}

void Objetivo::destruir()
{
    activo = false;
}

bool Objetivo::estaActivo()
{
    return activo;
}

float Objetivo::getX()
{
    return x;
}

void Objetivo::setX(float val)
{
    x = val;
}

float Objetivo::getY()
{
    return y;
}

void Objetivo::setY(float val)
{
    y = val;
}

float Objetivo::getRadio()
{
    return radio;
}

void Objetivo::setRadio(float val)
{
    radio = val;
}