#include "board.h"
#include "evo.h"
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

Board::Tissue Board::initTissue(unsigned w, unsigned h)
{
    auto tissue_d = Evo::initGenome<Cell>(w*h);
    Tissue tissue = {tissue_d, w, h};
    return tissue;
}

VVector Board::test(const Board::Tissue &tissue, const Stimuli &st, Activation &act)
{
    int idx = 0;
    int c_index = 0;
    VVector out;
    const unsigned w = tissue.width;
    const unsigned h = tissue.height;

    for(int sample = 0; sample < st.samples; ++sample){
        Vector current;
        for(unsigned i = 0; i < w; ++i){
            for(unsigned j = 0; j < h; ++j){
                Cell &cell = getCell(tissue, j, i);
                switch(cell.type){

                case CellType::IN:
                    cell.data = st.in[sample][idx];
                    idx = (idx + 1) % st.in.size();
                    break;

                case CellType::OUT:
                    current.push_back(cell.data);
                    break;

                case CellType::Body: {
                    double sum = getSum(tissue, c_index,0);
                    double result = act(sum);
                    propagate(tissue, c_index, result,0);

                }

                case CellType::Axon:
                    break;

                case CellType::Dendrite:
                    break;

                case CellType::None:
                default:
                    break;
                }
                c_index++;
            }
        }
        out.push_back(current);
    }

    return out;
}

double Board::getSum(const Board::Tissue &tissue, const int x, const int y)
{
    const int nei = 4;
    const int dim = 2;
    const int points[nei][dim] = {{x, y - 1},{x+1, y},{x, y - 1},{x - 1, y}};
    double sum = 0.0;

    for(int i = 0; i < nei; ++i){
        const Cell &cell = getCell(tissue, points[i][0], points[i][1]);
        if(cell.type == CellType::Dendrite){
            sum += cell.data;
        }
    }

    return sum;
}

void Board::propagate(const Board::Tissue &tissue, const int x, const int y, double data)
{
    const int nei = 4;
    const int dim = 2;
    const int points[nei][dim] = {{x, y - 1},{x+1, y},{x, y - 1},{x - 1, y}};

    for(int i = 0; i < nei; ++i){
        Cell &cell = getCell(tissue, points[i][0], points[i][1]);
        if(cell.type == CellType::Axon){
            cell.data = data;
        }
    }

}

Board::Cell &Board::getCell(const Board::Tissue &tissue, const int x, const int y)
{
    auto &&buffer = tissue.buffer;
    const int width = tissue.width;
    const int height = tissue.height;

    int x_ = x % width;
    int y_ = y % height;


    if(x_ < 0) x_ = width + x_;
    if(y_ < 0) y_ = height + y_;
    int idx = y_ * width + x_;

    return buffer->operator[](idx);
}
