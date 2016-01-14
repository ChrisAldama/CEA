#include "model.h"
#include "sigmoid.h"

void Model::init(unsigned w, unsigned h)
{
    network = Board::initTissue(w,h);
}

std::function<double ()> Model::makeCompute(const Stimuli &st)
{
    double error = 0;
    Board::Activation act = sigmoid<double>;
    //auto ev = Evo::evolve(*network.buffer, 20);


    return [=,&act]{


        return error;
    };

}

std::function<double ()> Model::makeCompute()
{
    return makeCompute(sti);
}

std::function<VVector (int)> Model::makeSimu()
{

    return [this](int steps) -> VVector {
        VVector res;
        for(int i = 0; i < steps; ++i){
            res = test(network, sti, act);
        }
        return res;
    };

}

void Model::setSimuli(const Stimuli &st)
{
    sti = st;
}

void Model::openFile(const QString &filename)
{
    sti = Stimuli::fromFile(filename);
}

Board::Tissue Model::data()
{
    return network;
}

Model::State Model::getState()
{
    return st;
}

void Model::state(Model::State st)
{
    this->st = st;
}
