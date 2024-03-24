#include "bird.hpp"

Bird::Bird(int brainSeed) : Entity(50, WINDOW_HEIGHT/2 ,BIRD_SIZE, BIRD_SIZE, 200, 200, 150)
{
    this->brain = new Brain(brainSeed);
}


void Bird::draw(UI *ui)
{
    // If not alive, skip
    if(!(this->isAlive))
        return;
    ui->drawRectangle(this->posX, this->posY, this->width, this->height, this->r, this->g, this->b);
}

double sigmoid(double x){
    return x / (1+abs(x));
}

void Bird::step()
{

    // If not alive, skip
    if(!(this->isAlive))
        return;

    
    this->fitness++;

    //Predict the next action
    Matrix inputFromNN = Matrix::Random(2,1);

    inputFromNN(0, 0) = sigmoid(this->posY - this->pipeGroup->getLeadingPipe()->getGapMiddlePosY());
    inputFromNN(1, 0) = sigmoid(this->pipeGroup->getLeadingPipe()->getPosX());
    Matrix prediction = this->brain->getAction(inputFromNN);

    if(sigmoid(prediction(0)) >= 0.5){
        this->posY += (rand()%(OUTPUT_NOISE + 1) + 1);
    }
    if(sigmoid(prediction(1)) > 0.5){
        this->posY -= (rand()%(OUTPUT_NOISE + 1) + 1);
    }

    // Collision for the top and bottom of the screen
    if(this->posY < 0)
        this->posY = 0;

    if(this->posY > WINDOW_HEIGHT-this->height)
        this->posY = WINDOW_HEIGHT-this->height;


    // Collision with the pipe
    if(this->pipeGroup->getLeadingPipe()->getPosX() < (this->posX + this->width)){
        if(this->posY < this->pipeGroup->getLeadingPipe()->getPosY() ||
            (this->posY+this->height) > this->pipeGroup->getLeadingPipe()->getPosY() +  this->pipeGroup->getLeadingPipe()->getHeight() ){
            this->isAlive = false;
            this->fitness -= 50;
        }
    }else{
        this->r = 200;
        this->g = 200;
        this->b = 150;
    }

    //std::cout << prediction(0) << ";" << prediction(1) << std::endl;

}

int Bird::getFitness()
{
    return this->fitness;
}

Bird *Bird::crossover(Bird *parent)
{
    //Create the new bird and set its brain
    Bird *newBird = new Bird(0);
    newBird->setBrain(this->getBrain()->crossover(parent->getBrain()));

    // Give the bird its new brain
    return newBird;
}

Brain* Bird::getBrain()
{
    return this->brain;
}

void Bird::setBrain(Brain *_brain)
{
    this->brain = _brain;
}

void BirdGroup::spawnBirds(int count) {
    for(int i = 0;i<count;i++){
        Bird* bird = new Bird(i);
        bird->pipeGroup = this->pipeGroup;

        this->registerEntity(bird);
    }
}

void BirdGroup::step(){

    // Step all the birds
    EntityGroup::step();

    // Check for the end of the epoch
    currentEpochDuration++;
    if(currentEpochDuration >= EPOCH_DURATION){
        
        // Sort all the birds by fitness
        std::sort(this->entities.begin(), this->entities.end(), [](Bird* &a, Bird* &b){return (a->getFitness() > b->getFitness());});

        double meanFitness = std::accumulate(this->entities.begin(),  this->entities.end(), 
                                            (double)this->entities[0]->getFitness(),
                                            [](double a, Bird* &b){return (a + (double)b->getFitness());}
                                        ) / (double) this->entities.size();
        
        //std::cout << std::endl;
        std::cout << "[EPOCH " << epoch << "] Mean fit " << (double)meanFitness << std::endl;

        //Create a new population
        std::vector<Bird*> newPopulation;
        for(int i = 0;i<this->entities.size();i++){
            
            //Select random Birds
            Bird* parentA = this->entities[rand()%BEST_SELECT_POPULATION];
            Bird* parentB = this->entities[rand()%BEST_SELECT_POPULATION];

            // Create a new bird from those 2 parents
            Bird* newBird = parentA->crossover(parentB);
            newBird->pipeGroup = this->pipeGroup;

            // Add this bird to the new population
            newPopulation.push_back(newBird);
        }

        //Destroy the old population
        for(int i = 0;i<this->entities.size();i++){
            delete(this->entities[i]);
        }

        // Replace the population
        this->entities = newPopulation;

        // Reset the pipe group
        this->pipeGroup->resetPipes();

        // Go to the next epoch
        epoch++;
        currentEpochDuration = 0;

    }
    
}