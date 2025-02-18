#ifndef MULTIOCTAVE_NOISE_H
#define MULTIOCTAVE_NOISE_H

#include "Random.h"
#include "PerlinNoise.h"
#include <cmath>
#include <vector>
#include <memory>
#include <stdexcept>
#include <string>

class MultiOctaveNoise {
public:
	// Vector holding a noise generator for each octave.
	std::vector<std::unique_ptr<PerlinNoise>> noiseLevels;
	// The amplitude (weight) for each octave.
	std::vector<double> amplitudes;
	// Factor used to scale input coordinates for the lowest-frequency octave.
	double lowestFreqInputFactor;
	// Factor used to scale the noise value contribution from the lowest-frequency octave.
	double lowestFreqValueFactor;
	// Maximum possible noise value, computed from edgeValue().
	double maxValue;
	
	MultiOctaveNoise(void);
	
	/**
	 * Constructor.
	 *
	 * @param rng Pointer to a Random instance.
	 * @param firstOctave The base octave (often a negative number, e.g. -15).
	 * @param amps Vector of amplitude values (one per octave).
	 * @param modern If true, uses a forked RNG for each octave; if false, uses the legacy branch.
	 */
	MultiOctaveNoise(Random* rng, int firstOctave, const std::vector<double>& amps, bool modern = true);

	MultiOctaveNoise &operator=(const MultiOctaveNoise &other);

	/**
	 * Samples the combined multi–octave noise at the given 3D coordinates.
	 *
	 * @param x The x coordinate.
	 * @param y The y coordinate.
	 * @param z The z coordinate.
	 * @param param An extra parameter (not used by PerlinNoise but kept for signature compatibility).
	 * @param param2 Another extra parameter (ditto).
	 * @param flag If true, uses a negative value for y (mimicking the original branch logic).
	 * @return The noise value.
	 */
	double sample(double x, double y, double z, double param = 0, double param2 = 0, bool flag = false);

	/**
	 * Returns the PerlinNoise instance for a specific octave.
	 * Note that octave 0 corresponds to the highest-frequency (last) octave.
	 *
	 * @param index The octave index (0 is the highest octave).
	 * @return Pointer to the PerlinNoise instance.
	 */
	PerlinNoise* getOctaveNoise(size_t index);

	/**
	 * Computes an "edge value" based on the given parameter.
	 * This can be used for normalization or determining the maximum possible output.
	 *
	 * @param t A parameter (for example, 2.0).
	 * @return The computed edge value.
	 */
	double edgeValue(double t);

	/**
	 * Wraps the coordinate t into a finite range.
	 * This keeps the values bounded (similar to the JS version using 33554432).
	 *
	 * @param t The coordinate value.
	 * @return The wrapped coordinate.
	 */
	static double wrap(double t);
};

#endif // MULTIOCTAVE_NOISE_H
