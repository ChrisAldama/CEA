#include "evo.h"





double Evo::fitness(const Evo::Vector &out, const Evo::Vector &expected)
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
