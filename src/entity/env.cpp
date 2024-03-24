#include "env.hpp"

Environnement::Environnement(int seed) : EntityGroup()
{

    // Init UI
    this->ui = new UI();
    ui->initDisplay();

    // Init random seed
    srand(seed);
}

void Environnement::step(){
    EntityGroup::step();
}

void Environnement::draw(){
    
    ui->ClearDisplay();
    EntityGroup::draw(this->ui);
    ui->UpdateDisplay();

}

UI *Environnement::getUI()
{
    return this->ui;
}
