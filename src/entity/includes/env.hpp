#ifndef _ENV_H_
#define _ENV_H_
#include <vector>
#include "entity.hpp"
#include "ui.hpp"

#define WINDOW_HEIGHT 400
#define WINDOW_WIDTH 300

class Environnement : public EntityGroup<Entity>{      
    public:          
        Environnement(int seed);
        void step();
        void draw();

        UI* getUI();

    private:
        std::vector<Entity*> entities;
        UI *ui;

     
};

#endif