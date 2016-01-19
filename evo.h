#ifndef EVO_H
#define EVO_H

#include <random>
#include <algorithm>
#include <utility>
#include <map>
#include <numeric>
#include <memory>
#include <vector>
#include "vector.h"
#include <functional>
#include "board.h"


namespace Evo {

using DNA = std::vector<Board::Cell>;
using DNA_PTR = std::shared_ptr<DNA>;
using Population = std::vector<DNA>;
using Population_PTR = std::shared_ptr<Population>;
using evFunc = std::function<Vector (const DNA&)>;

double fitness(const Vector &out, const Vector &expected);
DNA initGenome(const size_t size);
void mutate(Evo::DNA &genes, const double prob);
void populate(Population *pop, const Vector &fit, int n_winners);
std::function<double()> evolve(DNA *genes, size_t pop, evFunc &eval, const Vector &out);


}


#endif // EVO_H
