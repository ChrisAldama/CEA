#include "board.h"
#include <random>

void Board::Cell::mutate()
{
    using int_dist = std::uniform_int_distribution<int>;
    std::random_device dv;
    std::mt19937 gen(dv());
    int_dist dist_type (-m_amount_type, m_amount_type);
    int_dist dist_dir (-m_amount_dir, m_amount_dir);

    int t = static_cast<int>(type);
    int d = static_cast<int>(dir);

    t += dist_type(gen);
    d += dist_dir(gen);

    if(t < 0){
        t = static_cast<int>(CellType::Body);
    }
    if(d < 0){
        d = static_cast<int>(Direction::NONE);
    }

    t = t % (static_cast<int>(CellType::Body) + 1);
    d = d % (static_cast<int>(Direction::NONE) + 1);

    type = static_cast<CellType>(t);
    dir = static_cast<Direction>(d);
}

Board::Cell Board::Cell::fromRandom(std::mt19937 &gen)
{
    using Dist = std::uniform_int_distribution<int>;

    Dist type(static_cast<int>(CellType::None), static_cast<int>(CellType::Body));
    Dist dir(static_cast<int>(Direction::UP), static_cast<int>(Direction::NONE));
    Cell c(static_cast<CellType>(type(gen)),
           static_cast<Direction>(dir(gen)));

    return c;
}
