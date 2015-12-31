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

namespace Evo {

template<typename T>
using DNA = std::vector<T>;

template<typename T>
using DNA_PTR = std::shared_ptr<DNA<T>>;

template<typename T>
using Population = std::shared_ptr<std::vector<DNA_PTR<T>>>;

template<typename T>
using evFunc = std::function<Vector (const T&, const Vector &)>;


double fitness(const Vector &out, const Vector &expected);



template<typename T>
DNA_PTR<T> initGenome(const size_t size)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    DNA_PTR<T> genes = std::make_shared<DNA<T>>();

    for(size_t i = 0; i < size; ++i){
        T g = T::fromRandom(gen);
        genes->push_back(g);

    }
    return genes;
}

template<typename T>
void mutate(Evo::DNA<T> &genes, const double prob)
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

template<typename T>
void cross(Evo::DNA<T> &genes){

}


template<typename T>
void populate(Population<T> &pop, const Vector &fit, unsigned n_winners)
{
    if(pop->size() != fit.size()){
        return;
    }

    Population<T> winners;
    const unsigned size = fit.size();
    Vector fit_c(fit);

    for(unsigned i = 0; i < n_winners; ++i){
        int max = i;
        for(unsigned j = 0; j < size; ++j){
            if(fit_c[j] > fit_c[max]){
                max = j;

            }

        }
        fit_c[max] = 0;
        winners->push_back(std::move(pop->at(max)));
    }

    for(unsigned i = 0; i < size; ++i){
        pop->at(i) = winners->at(i % n_winners);
    }

}

template<typename T>
std::function<double()> evolve(DNA<T> &genes, size_t pop, evFunc<T> &eval,const Vector &in, const Vector &out)
{
    const size_t size = genes.size();
    Population<T> population(pop);
    for(auto &ind : *population){
        ind = initGenome<T>(size);
    }

    return [=]{
         Vector fit(size);

        for(size_t i = 0; i < size; ++i){
            Vector result = eval(population[i], in);
            fit.push_back(fitness(result, out));
        }
        populate<T>(population,fit,5);
        genes = population->at(0);
        return fit[0];
    };
}

}


#endif // EVO_H
