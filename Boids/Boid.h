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
	Pvector borders();
	float getAngle(Pvector v) const;

	// Constants for simulation 
	float maxAcceleration = 0.8;
	float maxVelocity = 5.0;

private:

	// How much each rule influences the total
	// acceleration
	float separationInf = 0.4;
	float alignmentInf = 0.3;
	float cohesionInf = 0.3;

	// Radius that we look in for each rule
	float separationRad = 50.0;
	float alignmentRad = 300.0;
	float cohesionRad = 300.0;

	// Radius for checking for borders
	float borderRad = 50.0;

	// Three rules for Boids simulations

	// Separation
	Pvector getSeparation(vector<Boid> v);
	// Alignment
	Pvector getAlignment(vector<Boid> v);
	// Cohesion
	Pvector getCohesion(vector<Boid> v);

};

#endif
