/* random_generator.hpp - Copyright 2014 Andrew Schwartzmeyer
 *
 * Header file for random generator setup
 */

#ifndef _RANDOM_GENERATOR_H_
#define _RANDOM_GENERATOR_H_

#include <random>

namespace random_generator
{
  typedef std::uniform_real_distribution<double> real_dist;
  typedef std::uniform_int_distribution<> int_dist;
  typedef std::normal_distribution<> normal_dist;

  class RandomGenerator
  {
    std::random_device rd;
  public:
    RandomGenerator();
    std::mt19937_64 engine;
  };

  extern RandomGenerator rg;
}

#endif /* _RANDOM_GENERATOR_H_ */
