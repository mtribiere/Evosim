#ifndef _BIRD_H_
#define _BIRD_H_

#include "entity.hpp"
#include "pipe.hpp"

#define BIRD_SIZE 20

#define EPOCH_DURATION 10000
#define BEST_SELECT_POPULATION 40

#define OUTPUT_NOISE 0

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