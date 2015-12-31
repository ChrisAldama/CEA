#ifndef MODEL_H
#define MODEL_H

#include "sigmoid.h"
#include "evo.h"
#include "board.h"
#include "stimuli.h"
#include <functional>

class Model
{
public:
    void init(unsigned w, unsigned h);
    std::function<double ()> makeCompute(const Stimuli &st);
private:
    Board::Tissue network;
};

#endif // MODEL_H
