#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <iostream>
#include <vector>
#include <numeric>
#include "ui.hpp"
#include "brain.hpp"

#define PIPE_WIDHT 20
#define PIPE_HEIGHT 100
#define PIPE_SPACING 200

class Entity{
    public:
        Entity(int _posX, int _posY, int _width, int _height, int r, int g, int b);

        virtual void draw(UI* ui){};
        virtual void step(){};
        virtual void step(std::vector<Entity*> context){};

        int getPosX();
        int getPosY();
        int getWidth();
        int getHeight();

    protected:
        int posX;
        int posY;
        int width;
        int height;

        int r;
        int g;
        int b;
};

// Optimization to reduce CPU usage
template<class T>
class EntityGroup : public Entity{
    public:
        EntityGroup():Entity(0, 0, 0, 0, 0, 0, 0){};

        void draw(UI* ui){
            for(T* todraw: this->entities){
                todraw->draw(ui);
            };
        }

        void step(){
            for(Entity* toStep: this->entities){
                toStep->step();
            }
        };

        void registerEntity(T *entity) {this->entities.push_back(entity);};
    
    protected:
        std::vector<T*> entities;

};


#endif