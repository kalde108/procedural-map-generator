#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <memory>
#include <string>
#include <functional>

class Random {
public:
	// Default constructor: seeds the generator with a random seed.
	Random(void);

	// Constructor with explicit seed.
	Random(unsigned int seed);

	// Copy constructor (copies the engine's state).
	Random(const Random& other);

	/**
	 * Creates a forked copy of this random generator.
	 * The new generator will have the same state as the current one.
	 */
	std::unique_ptr<Random> forkPositional() const;

	/**
	 * Creates a new Random generator seeded from a hash of the provided string.
	 * This can be used to generate a new, but deterministic, random generator for an octave.
	 */
	std::unique_ptr<Random> fromHashOf(const std::string& s) const;

	/**
	 * Consumes (discards) n random numbers, advancing the internal state.
	 * This is used in the legacy branch when an octave is skipped.
	 */
	void consume(int n);

	/**
	 * Returns a random double in the range [0, 1).
	 */
	double nextDouble();

	/**
	 * Returns a random integer in the range [0, bound-1].
	 * If bound is less than or equal to 0, behavior is undefined.
	 */
	int nextInt(int bound);

private:
	// The underlying random number engine.
	std::mt19937 engine;
};

#endif // RANDOM_H
