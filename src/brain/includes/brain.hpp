#ifndef _BRAIN_H_
#define _BRAIN_H_

#include <MiniDNN.h>

using namespace MiniDNN;

typedef Eigen::MatrixXd Matrix;
typedef Eigen::VectorXd Vector;


class Brain{
    public:
        Brain(int seed);
        Matrix getAction(Matrix input);
        Brain* crossover(Brain* parent);

        Network* getNetwork(){return this->network;};
        void setNetwork(std::vector<std::vector<Scalar>> _parameters);

    private:
        Network *network;

};

#endif