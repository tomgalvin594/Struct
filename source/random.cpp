#include "random.hpp"

Random::Random()
{
    set_seed(time(nullptr));
}

Random::Random(unsigned int seed)
{
    set_seed(seed);
}

Random::~Random()
{

}

void Random::set_seed(unsigned int seed)
{
    m_seed = seed;
    m_engine.seed(m_seed);
}

unsigned int Random::get_seed()
{
    return m_seed;
}

int Random::random(int min, int max)
{
    assert(min <= max);
    std::uniform_int_distribution<int> dist(min, max);
    return dist(m_engine);
}

double Random::random(double min, double max)
{
    assert(min <= max);
    std::uniform_real_distribution<double> dist(min, max);
    return dist(m_engine);
}
