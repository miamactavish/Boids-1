#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include "Boid.h"
#include "SFML/Window.hpp"

// Global Variables for borders()
const int window_height = 768;
const int window_width = 1204;

// =============================================== //
// ======== Boid Functions from Boid.h =========== //
// =============================================== //

Boid::Boid(float x, float y)
{
	// Give Boids a random initial velocity
	velocity = Pvector(rand() % 10 / 10.0, rand() % 10 / 10.0);

	// places boid in a random location in the window
	location = Pvector((rand() % window_width), (rand() % window_height));

}

// Modifies velocity, location, and resets acceleration with values that
// are given by the three laws.
void Boid::update()
{
	location.addVector(velocity);
}

// Update the boid's position and velocity. Called each frame for each boid in the flock. 
void Boid::run(vector <Boid> v)
{
	// YOUR CODE HERE
	// Add method calls to apply the three rules of Boids simulations. 
	// 
	// 
	// The results of these method calls should be added to the 'acceleration' vector, which is used to
	// change the boid's velocity and position in the update() method.
	update();

	// Either leave this method call here or update it to improve it - this is 
	// what prevents boids from moving out of bounds of the simulation
	borders();
}


// Checks if boids go out of the window and if so, flips their velocity.
void Boid::borders()
{
	if (location.x < 0 || location.x > window_width) {
		velocity.x = -velocity.x;
	}
	if (location.y < 0 || location.y > window_height) {
		velocity.y = -velocity.y;
	}
}

// You can leave this code alone - it's used to get the direction a boid is facing, so the triangle representing it on the screen
// can be rotated in the proper direction. It's called in Game.cpp.
float Boid::getAngle(Pvector v) const
{
	// From the definition of the dot product
	float angle = static_cast<float>(atan2(v.x, -v.y) * 180 / M_PI);
	return angle;
}
