#include "pipe.hpp"

Pipe::Pipe(int _posX) : Entity(_posX, 0, PIPE_WIDHT, PIPE_HEIGHT, 0, 200, 0)
{
    this->posY = rand() % (WINDOW_HEIGHT-this->height-100) + 100;
}

void Pipe::draw(UI *ui)
{
    //Top part
    ui->drawRectangle(this->posX, 0, this->width, this->posY, this->r, this->g, this->b);
    //Bottow part
    ui->drawRectangle(this->posX, this->posY + this->height, this->width, WINDOW_HEIGHT - (this->height + this->posY), this->r, this->g, this->b);
}

void Pipe::step()
{
    this->posX--;
}

int Pipe::getGapMiddlePosY()
{
    return (this->posY + (this->height/2));
}



void PipeGroup::step()
{

    EntityGroup::step();

    //If the first pipe goes off screen
    if(this->entities[0]->getPosX()+PIPE_WIDHT < 0){
        
        //Destroy it
        delete(this->entities[0]);
        this->entities.erase(this->entities.begin());
        
        // Create a new pipe
        this->spawnNewPipe();
    }
}

Pipe* PipeGroup::getLeadingPipe(){
    for(Pipe* toCheck: this->entities){
        if(toCheck->getPosX() > 50 -  PIPE_WIDHT){
            return toCheck;
        }
    }

    return nullptr;
}

void PipeGroup::resetPipes(){
    
    // Delete all the pipes
    for(int i = 0;i<this->entities.size();i++){
        delete(this->entities[i]);
    }

    this->entities.clear();

    // Create new pipes
    for(int i = 0;i<4;i++)
        this->spawnNewPipe();

}

void PipeGroup::spawnNewPipe()
{
    if(this->entities.size() == 0){

        this->registerEntity(new Pipe(400));

    }else{

        this->entities.push_back(new Pipe(
            this->entities.back()->getPosX() + PIPE_SPACING + PIPE_WIDHT
        ));

    }
}

