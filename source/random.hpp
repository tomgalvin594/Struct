#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <ctime>
#include <cassert>

//random number generator
class Random
{
public:
                            Random();
                            Random(unsigned int seed);
                            ~Random();

    void                    set_seed(unsigned int seed);
    unsigned int            get_seed();
    int                     random(int min, int max);
    double                  random(double min, double max);

private:
    std::mt19937            m_engine;
    unsigned int            m_seed;
};

#endif // RANDOM_HPP
