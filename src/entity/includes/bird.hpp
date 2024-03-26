#ifndef _BIRD_H_
#define _BIRD_H_

#include "entity.hpp"
#include "pipe.hpp"

#define BIRD_SIZE 20

#define EPOCH_DURATION 10000
#define BEST_SELECT_POPULATION 40
#define THREAD_NUMBER 4

#define WIND_FORCE 10
#define SENSOR_NOISE 10
#define ACTUATOR_NOISE 10
#define RESPONSE_LATENCY 30

class Bird: public Entity{
    public:
        Bird(int brainSeed);

        void draw(UI* ui);
        void step();
        int getFitness();
        bool isAlive();

        Brain* getBrain();
        void setBrain(Brain *_brain);
        Bird *crossover(Bird* parent);

        void performActionWithLatency(int action);

        PipeGroup* pipeGroup;
    
    private:
        Brain* brain;
        bool alive = true;
        int fitness = 0;

        std::vector<int> actionBuffer;
    
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