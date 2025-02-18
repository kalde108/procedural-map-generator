#include "Random.h"

Random::Random(void) : engine(std::random_device{}()) {}

Random::Random(unsigned int seed) : engine(seed) {}

Random::Random(const Random& other) : engine(other.engine) {}

std::unique_ptr<Random> Random::forkPositional() const {
	return std::make_unique<Random>(*this);
}

std::unique_ptr<Random> Random::fromHashOf(const std::string& s) const {
	std::hash<std::string> hasher;
	unsigned int newSeed = static_cast<unsigned int>(hasher(s));
	return std::make_unique<Random>(newSeed);
}

void Random::consume(int n) {
	for (int i = 0; i < n; i++) {
		engine(); // Advance the engine state.
	}
}

double Random::nextDouble() {
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	return dist(engine);
}

int Random::nextInt(int bound) {
	std::uniform_int_distribution<int> dist(0, bound - 1);
	return dist(engine);
}
