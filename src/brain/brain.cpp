#include "brain.hpp"

Brain::Brain(int seed)
{
    //Init network
    this->network = new Network();

    Layer* layer1 = new FullyConnected<Identity>(2, 4);
    Layer* layer2 = new FullyConnected<Identity>(4, 4);
    Layer* layer3 = new FullyConnected<Identity>(4, 3);
    Layer* layer4 = new FullyConnected<Identity>(3, 2);

    // Add layers to the network object
    this->network->add_layer(layer1);
    this->network->add_layer(layer2);
    this->network->add_layer(layer3);
    this->network->add_layer(layer4);

    this->network->set_output(new RegressionMSE());
    this->network->init(0.2, 0.5, seed);
}



Matrix Brain::getAction(Matrix input)
{
    Matrix prediction = this->network->predict(input);
    //std::cout << prediction(0) << ";" << prediction(1) << ";" << prediction(2) << std::endl;
    return prediction;
}

Brain* Brain::crossover(Brain* parent){
    
    // Get the parent's parameters
    auto parentA = this->network->get_parameters();
    auto parentB = parent->getNetwork()->get_parameters();

    // Create the new brain
    Brain *newBrain = new Brain(0);
    auto newNetwork = newBrain->getNetwork()->get_parameters();

    // For all layers
    for(int layerId = 0;layerId<parentA.size();layerId++){
        
        // Find a random split point
        int splitPoint = rand() % (parentA[layerId].size());

        // For all the first part, take from parent A then B
        for(int i = 0;i<splitPoint;i++){
            newNetwork[layerId][i] = parentA[layerId][i];
        }
        
        for(int i = splitPoint;i<parentA.size();i++){
            newNetwork[layerId][i] = parentB[layerId][i];
        }

        // Introduce mutation
        if(rand()%100000 == 45){
            newNetwork[layerId][rand()%(parentA.size())] = (rand()%100) / 100;
        }

    }

    newBrain->setNetwork(newNetwork);
    return newBrain;
}

void Brain::setNetwork(std::vector<std::vector<Scalar>> _parameters)
{
    this->network->set_parameters(_parameters);
}
