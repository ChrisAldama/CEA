#include "board.h"
#include "evo.h"
#include <random>


void Board::Cell::mutate()
{
    using int_dist = std::uniform_int_distribution<int>;
    static std::random_device dv;
    static std::mt19937 gen(dv());
    static int_dist dist_type (-m_amount_type, m_amount_type);
    static int_dist dist_dir (-m_amount_dir, m_amount_dir);

    int t = static_cast<int>(type);
    int d = static_cast<int>(dir);

    d += dist_dir(gen);
    t += dist_type(gen);

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

Board::Cell Board::Cell::fromRandom()
{
    using Dist = std::uniform_int_distribution<int>;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static Dist type(static_cast<int>(CellType::None), static_cast<int>(CellType::OUT));
    static Dist dir(static_cast<int>(Direction::UP), static_cast<int>(Direction::NONE));

    Cell c(static_cast<CellType>(type(gen)),
           static_cast<Direction>(dir(gen)));
    c.data = type(gen)/ 4.0;

    return c;
}

Board::Tissue Board::initTissue(unsigned w, unsigned h)
{
    auto tissue_d = Evo::initGenome(w*h);
    Tissue tissue = {std::make_shared<decltype(tissue_d)>(tissue_d), w, h};
    return tissue;
}

VVector Board::test(const Board::Tissue &tissue, const Stimuli &st, Activation &act)
{
    int idx = 0;
    int odx = 0;
    int c_index = 0;
    VVector out;
    const unsigned w = tissue.width;
    const unsigned h = tissue.height;

    for(int sample = 0; sample < st.samples; ++sample){
        Vector current(st.outputs);
        for(unsigned j = 0; j < h; ++j){
            for(unsigned i = 0; i < w; ++i){
                Cell &cell = getCell(tissue, i, j);
                switch(cell.type){

                case CellType::IN:
                    cell.data = st.in[sample][idx];
                    idx = (idx + 1) % st.inputs;
                    propagateAxon(tissue, i, j, cell.data);
                    break;

                case CellType::OUT:
                    current[odx] = cell.data;
                    odx = (odx + 1) % st.outputs;
                    break;

                case CellType::Body: {
                    double sum = getSum(tissue, i, j);
                    double result = act(sum);
                    propagate(tissue, i, j, result);

                }

                case CellType::Axon:
                    propagateAxon(tissue, i, j, cell.data);
                    break;

                case CellType::Dendrite:
                    propagateAxon(tissue, i, j, cell.data);
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
    const int points[nei][dim] = {{x, y - 1},{x+1, y},{x, y + 1},{x - 1, y}};
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
    const int points[nei][dim] = {{x, y - 1},{x+1, y},{x, y + 1},{x - 1, y}};

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

void Board::propagateAxon(const Board::Tissue &tissue, const int x, const int y, double data)
{
    const int nei = 4;
    const int dim = 2;
    const int points[nei][dim] = {{x, y - 1},{x+1, y},{x, y + 1},{x - 1, y}};

    for(int i = 0; i < nei; ++i){
        Cell &cell = getCell(tissue, points[i][0], points[i][1]);
        if(cell.type == CellType::Axon
                || cell.type == CellType::Dendrite
                || cell.type == CellType::OUT){
            cell.data = data;
        }
    }

}
