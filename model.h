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
    std::function<double ()> makeCompute();
    void setSimuli(const Stimuli &st);
    void openFile(const QString &filename);
private:
    Board::Tissue network;
    Stimuli sti;
};

#endif // MODEL_H
