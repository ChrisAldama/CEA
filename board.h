#ifndef BOARD_H
#define BOARD_H

#include "evo.h"

namespace Board {

enum class CellType{
    None = 0,
    Axon,
    Dendrite,
    Body
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
    static Cell fromRandom(std::mt19937 &gen);
    const static int m_amount_type = 1;
    const static int m_amount_dir = 1;
};

using Tissue = std::shared_ptr<std::vector<Cell>>;
/*void initTissue(unsigned w, unsigned h){

}*/

}

#endif // BOARD_H
