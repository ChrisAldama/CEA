#ifndef SIGMOID_H
#define SIGMOID_H

#include <math.h>

template<typename T = double>
T sigmoid(T val)
{
    return 1.0/(1.0 + exp(-val));
}



#endif // SIGMOID_H

