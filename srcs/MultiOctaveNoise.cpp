#include "MultiOctaveNoise.h"

MultiOctaveNoise::MultiOctaveNoise(void) 
	: lowestFreqInputFactor(0.0),
	  lowestFreqValueFactor(0.0),
	  maxValue(0.0)
{}

MultiOctaveNoise::MultiOctaveNoise(Random* rng, int firstOctave, const std::vector<double>& amps, bool modern)
: amplitudes(amps)
{
	if (modern) {
		// Modern branch: fork a new positional RNG.
		std::unique_ptr<Random> forked = rng->forkPositional();
		this->noiseLevels.resize(amps.size());
		for (size_t o = 0; o < amps.size(); o++) {
			if (amps[o] != 0) {
				int octave = firstOctave + static_cast<int>(o);
				// Create a new RNG based on a hash of the octave identifier.
				std::unique_ptr<Random> rngA = forked->fromHashOf("octave_" + std::to_string(octave) + "_a" + std::to_string(forked->nextInt(1000000000)));
				std::unique_ptr<Random> rngB = forked->fromHashOf("octave_" + std::to_string(octave) + "_b" + std::to_string(forked->nextInt(1000000000)));
				// Obtain a seed from the new RNG. The bound here is arbitrary.
				unsigned int seedA = rngA->nextInt(1000000000);
				unsigned int seedB = rngB->nextInt(1000000000);
				this->noiseLevels[o].first = PerlinNoise(seedA);
				this->noiseLevels[o].second = PerlinNoise(seedB);
			} else {
				// Amplitude zero: assign a default-constructed noise (its value won’t be used).
				noiseLevels[o].first = PerlinNoise();
				noiseLevels[o].second = PerlinNoise();
			}
		}
	} else {
		// Legacy branch: only nonpositive octaves are allowed.
		if (1 - firstOctave < static_cast<int>(amps.size())) {
			throw std::runtime_error("Positive octaves are not allowed when using LegacyRandom");
		}
		this->noiseLevels.resize(amps.size());
		// Iterate over octaves (note: in legacy branch, we loop from -firstOctave down to 0)
		for (int s = -firstOctave; s >= 0; s--) {
			if (s < static_cast<int>(amps.size()) && amps[s] != 0) {
				// Use the provided RNG directly to create the PerlinNoise instance.
				unsigned int seedA = rng->nextInt(1000000000);
				unsigned int seedB = rng->nextInt(1000000000);
				this->noiseLevels[s].first = PerlinNoise(seedA);
				this->noiseLevels[s].second = PerlinNoise(seedB);
			} else {
				noiseLevels[s].first = PerlinNoise();
				noiseLevels[s].second = PerlinNoise();
				// Consume random numbers to maintain RNG state consistency.
				rng->consume(262);
			}
		}
	}
	this->lowestFreqInputFactor = std::pow(2.0, firstOctave);
	this->lowestFreqValueFactor = std::pow(2.0, static_cast<double>(amps.size() - 1)) /
								(std::pow(2.0, static_cast<double>(amps.size())) - 1);
	this->maxValue = edgeValue(2.0);
}

double MultiOctaveNoise::sample(double x, double y, double z, double param, double param2, bool flag) {
	double value = 0.0;
	double freqFactor = this->lowestFreqInputFactor;
	double ampFactor = this->lowestFreqValueFactor;
	for (size_t i = 0; i < this->noiseLevels.size(); i++) {
		if (this->amplitudes[i] != 0) {
			double sampleX = MultiOctaveNoise::wrap(x * freqFactor);
			// In the original code, the y value might be negated based on a flag.
			double sampleY = flag ? -MultiOctaveNoise::wrap(y * freqFactor) : MultiOctaveNoise::wrap(y * freqFactor);
			double sampleZ = MultiOctaveNoise::wrap(z * freqFactor);
			// Use the PerlinNoise::noise() method for a 3D noise value.
			double noiseA = this->noiseLevels[i].first.noise(sampleX, sampleY, sampleZ);
			// double noiseB = this->noiseLevels[i].second.noise(sampleX, sampleY, sampleZ);

			// double octaveValue = (noiseA + noiseB) / 2.0;

			value += this->amplitudes[i] * ampFactor * noiseA;
		}
		freqFactor *= 2.0;
		ampFactor /= 2.0;
	}
	return value;
}

PerlinNoise &MultiOctaveNoise::getOctaveNoise(size_t index) {
	if (index >= this->noiseLevels.size()) {
		throw std::out_of_range("Octave index out of range");
	}
	// Reverse the order so that index 0 corresponds to the highest-frequency octave.
	return this->noiseLevels[this->noiseLevels.size() - 1 - index].first;
}

double MultiOctaveNoise::edgeValue(double t) {
	double sum = 0.0;
	double factor = this->lowestFreqValueFactor;
	for (size_t i = 0; i < this->noiseLevels.size(); i++) {
		sum += this->amplitudes[i] * t * factor;
		factor /= 2.0;
	}
	return sum;
}

double MultiOctaveNoise::wrap(double t) {
	const double WRAP_VALUE = 33554432.0;
	return t - std::floor(t / WRAP_VALUE + 0.5) * WRAP_VALUE;
}
