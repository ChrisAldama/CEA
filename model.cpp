#include "model.h"
#include "sigmoid.h"

void Model::init(unsigned w, unsigned h)
{
    network = Board::initTissue(w,h);
    act = sigmoid<double>;
}

Vector Model::plain(const VVector &v)
{
    Vector res;
    for(const auto &subV : v){
        for(const auto &val: subV){
          res.push_back(val);
        }
    }

    return res;
}

std::function<double ()> Model::makeCompute(int steps)
{
    const Vector out = plain(sti.out);
    Evo::evFunc eval =
             [this, steps](const Evo::DNA &net) -> Vector{
        VVector res;
        Board::Tissue t = network;
        t.buffer = std::make_shared<std::vector<Board::Cell>>(net);
        for(int i = 0; i < steps; ++i){
            res = Board::test(t, sti, act);
        }

        return plain(res);

    };   
    auto evo = Evo::evolve(network.buffer.get(), 20, eval, out);
    return evo;

}

std::function<VVector (int)> Model::makeSimu()
{

    return [this](int steps) -> VVector {
        VVector res;
        for(int i = 0; i < steps; ++i){
            res = Board::test(network, sti, act);
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
