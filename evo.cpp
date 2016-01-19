#include "evo.h"
#include "board.h"

namespace Evo{

double fitness(const Vector &out, const Vector &expected)
{
    if(out.size()  != expected.size()){
        return 0.0;

    }

    const size_t size = out.size();
    int acc = 0;
    for(size_t i = 0; i < size; ++i){
        if(out[i] == expected[i]){
            acc++;
        }
    }

    return double(acc)/double(size);
}



DNA initGenome(const size_t size)
{
    DNA genes;

    for(size_t i = 0; i < size; ++i){
        auto g = Board::Cell::fromRandom();
        genes.push_back(g);

    }
    return genes;
}

void mutate(Evo::DNA &genes, const double prob)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    for(auto &gene: genes){
        double rand = dist(gen);
        if(rand >= prob){
            gene.mutate();
        }
    }
}

void populate(Population *pop, const Vector &fit, int n_winners)
{
    if(pop->size() != fit.size()){
        return;
    }

    Population winners;
    const int size = fit.size();
    Vector fit_c(fit);

    for(int i = 0; i < n_winners; ++i){
        int max = i;
        for(int j = 0; j < size; ++j){
            if(fit_c[j] > fit_c[max]){
                max = j;

            }

        }
        fit_c[max] = 0;
        winners.push_back(pop->at(max));
    }

    for(int i = 0; i < size; ++i){
        pop->at(i) = winners.at(i % n_winners);
    }
}

std::function<double()> evolve(DNA *genes, size_t pop, evFunc &eval, const Vector &out)
{
    const size_t size = genes->size();

    Population_PTR population = std::make_shared<Population>();
    for(size_t i = 0; i < pop; ++i){
        population->push_back(initGenome(size));
    }


    return [=]{
         Vector fit;

        for(size_t i = 0; i < pop; ++i){
            mutate(population->at(i), 0.5);
            Vector result = eval(population->at(i));
            fit.push_back(fitness(result, out));
        }
        populate(population.get(), fit, 10);
        *genes = population->at(0);
        return fit[0];
    };
}

}
