#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <iostream>
#include <vector>
#include "ui.hpp"
#include "brain.hpp"

#define PIPE_WIDHT 20
#define PIPE_HEIGHT 100
#define PIPE_SPACING 200

#define BIRD_SIZE 20

#define EPOCH_DURATION 10000
#define BEST_SELECT_POPULATION 40

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

class Pipe: public Entity{
    public:
        Pipe(int _posX);
        void draw(UI* ui);
        void step();   

        int getGapMiddlePosY(); 
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


class PipeGroup : public EntityGroup<Pipe>{

    public:
        PipeGroup(){this->resetPipes();};
        void step();
        Pipe* getLeadingPipe();
        void spawnNewPipe();

        void resetPipes();

};

class Bird: public Entity{
    public:
        Bird(int brainSeed);

        void draw(UI* ui);
        void step();
        int getFitness();

        Brain* getBrain();
        void setBrain(Brain *_brain);
        Bird *crossover(Bird* parent);

        PipeGroup* pipeGroup;
    
    private:
        Brain* brain;
        bool isAlive = true;
        int fitness = 0;
    
};

class BirdGroup: public EntityGroup<Bird>{

    public:
        void step();
        void spawnBirds(int count);
        
        PipeGroup* pipeGroup;
    private:
        int epoch = 0;
        int currentEpochDuration = 0;
   

};

#endif