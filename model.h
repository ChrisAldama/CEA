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
    enum class State {
        Testing = 0,
        Evolving = 1
    };

    Stimuli sti;

    void init(unsigned w, unsigned h);
    std::function<double ()> makeCompute(int steps);
    std::function<VVector (int)> makeSimu();
    void setSimuli(const Stimuli &st);
    void openFile(const QString &filename);
    Board::Tissue data();
    Vector plain(const VVector &v);


    State getState();
    void state(State st);
private:

    Board::Tissue network;
    Board::Activation act = nullptr;
    State st = State::Evolving;
};

#endif // MODEL_H
