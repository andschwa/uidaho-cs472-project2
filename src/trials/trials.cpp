/* trials.cpp - CS 472 Project #2: Genetic Programming
 * Copyright 2014 Andrew Schwartzmeyer
 *
 * Source file for the trials namespace
 */

#include <algorithm>
#include <cassert>
#include <ctime>
#include <future>
#include <tuple>

#include "trials.hpp"
#include "../algorithm/algorithm.hpp"
#include "../individual/individual.hpp"
#include "../options/options.hpp"

namespace trials
{
  // Spawn trials number of threads in blocks.
  const std::tuple<int, individual::Individual>
  run(const options::Options& options, const std::time_t& time)
  {
    using individual::Individual;

    const unsigned long hardware_threads = std::thread::hardware_concurrency();
    const unsigned long blocks = (hardware_threads != 0) ? hardware_threads : 2;
    assert(options.trials % blocks == 0);

    unsigned int trial = 0;
    std::vector<Individual> candidates;
    // Spawn trials in chunks of size blocks.
    for (unsigned long t = 0; t < options.trials / blocks; ++t)
      {
	std::vector<std::future<const Individual>> results;
	// Spawn blocks number of async threads.
	for (unsigned long i = 0; i < blocks; ++i)
	  results.emplace_back(std::async(std::launch::async,
					  algorithm::genetic, options, time,
					  ++trial));
	// Gather future results.
	for (std::future<const Individual>& result : results)
	  candidates.emplace_back(result.get());
      }
    std::vector<Individual>::iterator best
      = std::min_element(candidates.begin(), candidates.end(),
			 algorithm::compare_fitness);
    /* Get which trial was best.  Filenames are not zero-indexed so
       increase by one. */
    int distance = std::distance(candidates.begin(), best) + 1;
    return std::make_tuple(distance, *best);
  }
}
