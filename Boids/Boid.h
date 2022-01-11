#include "Pvector.h"
#include <vector>

// These two lines work the same way as #pragma once
#ifndef BOID_H_
#define BOID_H_

// The Boid Class

class Boid {
public:
	Pvector location;
	Pvector velocity;
	Pvector acceleration;

	Boid(float x, float y);

	void run(vector <Boid> v);

	void update();
	void borders();
	float getAngle(Pvector v) const;

private:
	// Three rules for Boids simulations

	// Separation
	Pvector getSeparation(vector<Boid> v);

	// Alignment
	Pvector getAlignment(vector<Boid> v);

	// Cohesion
	Pvector getCohesion(vector<Boid> v);

	float separationRad = 100.f;
	float alignmentRad = 300.f;
	float cohesionRad = 300.f;

};

#endif
