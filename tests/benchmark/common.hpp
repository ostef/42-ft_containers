#ifndef FT_BENCHMARK_COMMON_HPP
#define FT_BENCHMARK_COMMON_HPP

#include "../common.hpp"
#include <sys/time.h>
#include <iomanip>
#include <cstdlib>

struct benchmark
{
	std::string name;
	double average;
	size_t lowest;
	size_t highest;
	size_t total;
	size_t number_of_samples;

	timeval start_time;

	benchmark (const std::string &name) : name (name), average (0), lowest (0xffffffffffffffff), highest (0), total (0), number_of_samples (0)
	{}

	void start ()
	{
		gettimeofday (&start_time, NULL);
	}

	void end (size_t n = 1)
	{
		timeval now;

		gettimeofday (&now, NULL);
		long long a = start_time.tv_sec * 1000000 + start_time.tv_usec;
		long long b = now.tv_sec * 1000000 + now.tv_usec;
		size_t elapsed = (size_t)(b - a);

		if (elapsed < lowest)
			lowest = elapsed;
		if (elapsed > highest)
			highest = elapsed;

		total += elapsed;
		number_of_samples += n;
		average = total / (double)number_of_samples;
	}
};

std::ostream &operator<< (std::ostream &os, const benchmark &bench)
{
	os << std::setw (8) << bench.name << ": " << bench.average << " on avg, for " << bench.number_of_samples << " samples, lowest is " << bench.lowest
		<< ", highest is " << bench.highest;
	#ifdef TEST_STD
	
		os << ". 20 * avg == " << 20 * bench.average; 

	#endif
	
	return os;
}

#endif
