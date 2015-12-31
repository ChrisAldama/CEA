#include "model.h"



void Model::init(unsigned w, unsigned h)
{
    network = Board::initTissue(w,h);
}

std::function<double ()> Model::makeCompute(const Stimuli &st)
{
    double error = 0;
    return [this,error]{
        Evo::mutate<Board::Cell>(network, 0.1);

        return error;
    };

}
