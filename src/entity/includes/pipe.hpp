#ifndef _PIPE_H_
#define _PIPE_H_

#include "entity.hpp"

class Pipe: public Entity{
    public:
        Pipe(int _posX);
        void draw(UI* ui);
        void step();   

        int getGapMiddlePosY(); 
};


class PipeGroup : public EntityGroup<Pipe>{

    public:
        PipeGroup(){this->resetPipes();};
        void step();
        Pipe* getLeadingPipe();
        void spawnNewPipe();

        void resetPipes();
};



#endif