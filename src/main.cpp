#include "ui.hpp"

#include "env.hpp"
#include "pipe.hpp"
#include "bird.hpp"

int main(int argc, char *argv[])
{
    
    PipeGroup *pipeGroup = new PipeGroup();

    BirdGroup *birdGroup = new BirdGroup(); 
    birdGroup->pipeGroup = pipeGroup;
    birdGroup->spawnBirds(100);

    Environnement env = Environnement(0);
    env.registerEntity(pipeGroup);
    env.registerEntity(birdGroup); 

    while(1){
        
        env.step();
        env.draw();

        //env.getUI()->sleep(10);
        env.getUI()->pullLastEvent();
        if(env.getUI()->shouldQuit())
            break;
        

    }

    return 0;
}