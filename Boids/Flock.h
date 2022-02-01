#include <vector>
#include "Boid.h"
#include "SFML/Graphics.hpp"

#pragma once

// Brief description of Flock Class:
// This file contains the class needed to create a flock of boids. It utilizes
// the boids class and initializes boid flocks with parameters that can be
// specified. This class will be utilized in main.

class Flock {
public:
	vector<Boid> flock;
	//Constructors
	Flock() {}
	// Accessor functions
	int getSize() const;
	Boid getBoid(int i);
	
	// Mutator Functions
	void addBoid(Boid b);

	// flocking() gets called every frame to update the simulation
	void flocking();

	// For accessing & modifying values in Game.cpp
	int flockCount();

	void modifyAcceleration(float amount);
	void modifyVelocity(float amount);

	void addObstacle(int x, int y);

	vector<Pvector> obstacles;
};

