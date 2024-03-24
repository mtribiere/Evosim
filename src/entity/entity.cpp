#include "entity.hpp"


Entity::Entity(int _posX, int _posY,  int _width, int _height, int _r, int _g, int _b)
{
    this->posX = _posX;
    this->posY = _posY;
    this->width = _width;
    this->height = _height;

    this->r = _r;
    this->g = _g;
    this->b = _b;
}

int Entity::getPosX(){
    return this->posX;
}

int Entity::getPosY(){
    return this->posY;
}

int Entity::getWidth()
{
    return this->width;
}


int Entity::getHeight()
{
    return this->height;
}