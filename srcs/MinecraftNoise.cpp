#include "MinecraftNoise.h"

#include <numeric>
#include <random>
#include <algorithm>
#include <cmath>

# include <iostream>

MinecraftNoise::MinecraftNoise(void) : startFrequency(1) {
	// Initialize the permutation vector with the reference values
	p = {
		6, 119, 52, 224, 161, 63, 89, 255, 93, 178, 68, 30, 236, 127, 183, 104, 86, 232, 133, 233,
		220, 41, 205, 144, 58, 67, 191, 149, 96, 231, 97, 209, 71, 49, 113, 2, 120, 235, 166, 223,
		46, 11, 216, 158, 15, 44, 112, 130, 27, 25, 136, 69, 196, 122, 8, 84, 227, 22, 143, 101, 3,
		51, 32, 64, 253, 13, 225, 56, 201, 230, 107, 140, 137, 204, 254, 74, 87, 19, 176, 165, 66,
		17, 207, 249, 197, 211, 54, 123, 128, 105, 202, 252, 239, 121, 181, 186, 40, 208, 146, 251,
		210, 92, 138, 79, 162, 29, 91, 83, 106, 43, 244, 21, 215, 141, 47, 95, 7, 73, 152, 241, 42,
		31, 134, 117, 156, 85, 237, 124, 172, 23, 175, 245, 33, 238, 90, 188, 203, 187, 1, 37, 38,
		14, 110, 200, 24, 229, 35, 234, 217, 16, 206, 214, 174, 60, 222, 154, 111, 116, 12, 212,
		102, 169, 177, 28, 228, 194, 147, 192, 242, 61, 193, 240, 168, 72, 213, 98, 45, 103, 114,
		53, 26, 62, 129, 248, 34, 247, 50, 153, 135, 226, 246, 88, 199, 151, 9, 65, 189, 157, 198,
		125, 132, 70, 173, 185, 180, 76, 221, 115, 81, 80, 219, 39, 145, 243, 150, 179, 148, 82,
		163, 100, 48, 160, 36, 164, 5, 118, 155, 99, 75, 170, 18, 131, 167, 139, 77, 190, 94, 195,
		218, 78, 57, 159, 4, 10, 109, 184, 182, 171, 250, 59, 142, 108, 20, 55, 126
	};
	// Duplicate the permutation vector.
	p.insert(p.end(), p.begin(), p.end());
	this->amplitudes.push_back(1.0);
	this->stipAmplitude();
}

MinecraftNoise::MinecraftNoise(unsigned int seed) : startFrequency(1) {
	this->pInit(seed);
	this->amplitudes.push_back(1.0);
	this->stipAmplitude();
}

MinecraftNoise::MinecraftNoise(unsigned int seed, int firstOctave) : startFrequency(pow(2, -firstOctave)) {
	this->pInit(seed);
	this->amplitudes.push_back(1.0);
	this->stipAmplitude();
}

MinecraftNoise::MinecraftNoise(unsigned int seed, int firstOctave, double *amplitudes, size_t size) : startFrequency(pow(2, -firstOctave)) {
	this->pInit(seed);
    this->amplitudes = std::vector<double>(amplitudes, amplitudes + size);
	this->stipAmplitude();
}

MinecraftNoise::MinecraftNoise(unsigned int seed, int firstOctave, std::vector<double> &amplitudes) : startFrequency(pow(2, -firstOctave)), amplitudes(amplitudes) {
	this->pInit(seed);
	this->stipAmplitude();
	std::cerr << "startFrequency: " << startFrequency << " ; number of amplitudes: " << this->amplitudes.size() << " ; ampStrip: " << this->ampStrip << std::endl;
}

MinecraftNoise::MinecraftNoise(unsigned int seed, int firstOctave, const std::vector<double>& amplitudes) : startFrequency(pow(2, -firstOctave)), amplitudes(amplitudes) {
	this->pInit(seed);
	this->stipAmplitude();
	std::cerr << "startFrequency: " << startFrequency << " ; number of amplitudes: " << this->amplitudes.size() << " ; ampStrip: " << this->ampStrip << std::endl;
}

void MinecraftNoise::pInit(unsigned int seed) {
	p.resize(256);
	// Fill p with values from 0 to 255
	std::iota(p.begin(), p.end(), 0);
	// Initialize a random engine with seed
	std::default_random_engine engine(seed);
	// Suffle  using the random engine
	std::shuffle(p.begin(), p.end(), engine);
	// Duplicate the permutation vector
	p.insert(p.end(), p.begin(), p.end());
}

void MinecraftNoise::stipAmplitude(void) {
	this->ampStrip = this->amplitudes.size();
	// std::cerr << "ampStrip 1 : " << this->ampStrip << std::endl;
	int i = 0;
	for (; i < this->amplitudes.size() && this->amplitudes[i] == 0; i++) {}
	this->ampStrip -= i;
	// std::cerr << "ampStrip 2 : " << this->ampStrip << std::endl;
	for (i = this->amplitudes.size(); i > 0 && this->amplitudes[i - 1] == 0; i--) {}
	this->ampStrip -= (this->amplitudes.size() - i);
	// std::cerr << "ampStrip 3 : " << this->ampStrip << std::endl;
}

double MinecraftNoise::noise(double x, double y, double z) const {
	double totalNoise = 0.0;
	double totalAmplitude = 0.0;
	int index = 0;
	double frequency = this->startFrequency;
	for (double amplitude : this->amplitudes) {
		// Find unit cube that contains point.
		int X = static_cast<int>(floor(x * frequency)) & 255;
		int Y = static_cast<int>(floor(y * frequency)) & 255;
		int Z = static_cast<int>(floor(z * frequency)) & 255;

		// Find relative x, y, z of point in cube.
		double fx = x * frequency - floor(x * frequency);
		double fy = y * frequency - floor(y * frequency);
		double fz = z * frequency - floor(z * frequency);

		// Compute fade curves for each of x, y, z.
		double u = fade(fx);
		double v = fade(fy);
		double w = fade(fz);

		// Hash coordinates of the 8 cube corners.
		int A  = p[X  ] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
		int B  = p[X+1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

		// And add blended results from 8 corners of cube.
		double gradAA = grad(AA, 0, 0, fx, fy, fz);
		double gradBA = grad(BA, 0, 0, fx - 1, fy, fz);
		double gradAB = grad(AB, 0, 0, fx, fy - 1, fz);
		double gradBB = grad(BB, 0, 0, fx - 1, fy - 1, fz);
		double gradAA1 = grad(AA + 1, 0, 0, fx, fy, fz - 1);
		double gradBA1 = grad(BA + 1, 0, 0, fx - 1, fy, fz - 1);
		double gradAB1 = grad(AB + 1, 0, 0, fx, fy - 1, fz - 1);
		double gradBB1 = grad(BB + 1, 0, 0, fx - 1, fy - 1, fz - 1);

		double lerpX1 = lerp(gradAA, gradBA, u);
		double lerpX2 = lerp(gradAB, gradBB, u);
		double lerpY1 = lerp(lerpX1, lerpX2, v);

		double lerpX3 = lerp(gradAA1, gradBA1, u);
		double lerpX4 = lerp(gradAB1, gradBB1, u);
		double lerpY2 = lerp(lerpX3, lerpX4, v);

		double currentAmplitude = 1.04 * amplitude * 2.0 * pow(2, this->amplitudes.size() - index - 1) / (pow(2, this->amplitudes.size()) - 1);

		totalNoise += lerp(lerpY1, lerpY2, w) * currentAmplitude;
		totalAmplitude += currentAmplitude;
		frequency *= 2.0;
		++index;
	}
	return 10 * totalNoise / (3 * (1 + 1 / this->ampStrip));
	// return totalNoise / totalAmplitude;
}

double MinecraftNoise::noise(double x, double y) const {
	return noise(x, y, 0.0);
}

double MinecraftNoise::noise(double x) const {
	return noise(x, 0.0, 0.0);
}

double MinecraftNoise::fade(double t) {
	return t * t * t * (t * (t * 6 - 15) + 10);
}

double MinecraftNoise::lerp(double a, double b, double t) {
	return a + t * (b - a);
}

double MinecraftNoise::grad(int ix, int iy, int iz, double x, double y, double z) const {
	// Convert lower 4 bits of hash code into 12 gradient directions.
	int h = p[p[p[ix] + iy] + iz] & 15;
	double u = h < 8 ? x : y;
	double v = h < 4 ? y : (h == 12 || h == 14 ? x : z);
	// Depending on the hash, return a positive or negative contribution.
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}
