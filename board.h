#ifndef BOARD_H
#define BOARD_H
#include <memory>
#include <random>
#include <functional>
#include "vector"
#include "stimuli.h"

namespace Board {


enum class CellType{
    None = 0,
    Axon,
    Dendrite,
    Body,
    IN,
    OUT
};

enum class Direction{
    UP= 0,
    RIGHT,
    DOWN,
    LEFT,
    NONE
};


struct Cell{
    CellType type = CellType::None;
    Direction dir = Direction::NONE;
    double data = 0.0;

    Cell(CellType type, Direction d){
        this->type = type;
        this->dir = d;
    }

    Cell(){

    }

    void mutate();
    static Cell fromRandom();
    const static int m_amount_type = 1;
    const static int m_amount_dir = 1;
};

using TissueData = std::shared_ptr<std::vector<Cell>>;
using Activation = std::function<double(double)>;


struct Tissue {
    TissueData buffer;
    unsigned int width;
    unsigned int height;

};

Tissue initTissue(unsigned w, unsigned h);
VVector test(const Tissue &tissue, const Stimuli &st, Activation &act);
double getSum(const Tissue &tissue, const int x, const int y);
void propagate(const Tissue &tissue, const int x, const int y, double data);
void propagateAxon(const Tissue &tissue, const int x, const int y, double data);
Cell &getCell(const Tissue &tissue, int x, int y);



}

#endif // BOARD_H
