#ifndef OBJETIVO_H
#define OBJETIVO_H

class Objetivo
{
protected:
    float x;
    float y;
    float radio;
    bool activo;

public:
    Objetivo();
    Objetivo(const Objetivo&);
    virtual ~Objetivo();

    void destruir();
    bool estaActivo();

    virtual void verificar() = 0;

    float getX();
    void setX(float);

    float getY();
    void setY(float);

    float getRadio();
    void setRadio(float);
};

#endif