#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include "Boid.h"
#include "SFML/Window.hpp"

// Global Variables for borders()
const int window_height = 1000;
const int window_width = 1204;

// =============================================== //
// ======== Boid Functions from Boid.h =========== //
// =============================================== //

Boid::Boid(float x, float y)
{
	acceleration = Pvector(0, 0);

	// Give Boids a random initial velocity
	velocity = Pvector(rand() % 10 / 10.0, rand() % 10 / 10.0);

	velocity.setMagnitude(maxVelocity);

	// places boid in a random location in the window
	location = Pvector((rand() % window_width), (rand() % window_height));
}

// Modifies velocity, location, and resets acceleration with values that
// are given by the three laws.
void Boid::update()
{
	acceleration.mulScalar(0.35);
	//acceleration.limit(maxAcceleration);

	velocity.addVector(acceleration);
	velocity.limit(maxVelocity);

	location.addVector(velocity);
}

// Update the boid's position and velocity. Called each frame for each boid in the flock. 
void Boid::run(vector <Boid> v)
{
	// YOUR CODE HERE
	// Add method calls to apply the three rules of Boids simulations. 
	Pvector alignment = getAlignment(v);
	Pvector separation = getSeparation(v);
	Pvector cohesion = getCohesion(v);

	alignment.mulScalar(alignmentInf);
	cohesion.mulScalar(cohesionInf);
	separation.mulScalar(separationInf);


	acceleration = Pvector(0.0, 0.0);
	acceleration.addVector(alignment);
	acceleration.addVector(cohesion);
	acceleration.addVector(separation);

	// Either leave this method call here or update it to improve it - this is 
	// what prevents boids from moving out of bounds of the simulation
	borders();

	// The results of these method calls should be added to the 'acceleration' vector, which is used to
	// change the boid's velocity and position in the update() method.
	update();
}


Pvector Boid::getAlignment(vector<Boid> flock) {

	Pvector sum = Pvector(0, 0);
	int count = 0;
	// Get the average heading of each Boid in the flock
	for (int i = 0; i < flock.size(); i++) {

		float distance = location.distance(flock[i].location);
		if (distance > alignmentRad || distance <= 0) {
			continue;
		}
		
		Pvector cur = flock[i].velocity;
		sum.addVector(cur);
		count++;
	}

	if (count > 0) {
		// Get the average velocity of surrounding Boids
		sum.divScalar(count);

		// Clamp to maximum velocity
		sum.setMagnitude(maxVelocity);

		// Move this boid towards that average heading
		sum.subVector(velocity);

		// Cap the acceleration
		sum.limit(maxAcceleration);
	}

	return sum;
}


Pvector Boid::getSeparation(vector<Boid> flock) {
	
	Pvector sum = Pvector(0.0, 0.0);
	int count = 0;

	int count = 0;

	for (int i = 0; i < flock.size(); i++) 
	{ 
		float distance = location.distance(flock[i].location);
		if (distance > separationRad || distance <= 0) {
			continue;
		}
		
		Pvector diff;
		diff = diff.subTwoVector(location, flock[i].location);
		diff.normalize();

		diff.divScalar(distance);
		sum.addVector(diff);
		count++;
	}

	if (count > 0) {
		// Get the average separation vector
		sum.divScalar(count);

		// Clamp the desired velocity by our maximum acceleration
		sum.setMagnitude(maxVelocity);

		// Get the vector pointing from our current velocity to our desired velocity
		sum.subVector(velocity);

		// Cap the acceleration
		sum.limit(maxAcceleration);
	}
	
	return sum;
}


Pvector Boid::getCohesion(vector<Boid> flock) 
{
	Pvector sum = Pvector(0, 0);
	int count = 0;
	// Get the average heading of each Boid in the flock

	int count = 0;

	for (int i = 0; i < flock.size(); i++) 
	{
		float distance = location.distance(flock[i].location);


		if (distance > cohesionRad || distance <= 0) {
			continue;
		}

		Pvector cur = flock[i].location;
		sum.addVector(cur);
		
		count++;
	}

	if (count > 0) {
		// Sum contains the average position of the surrounding boids
		sum.divScalar(count);

		// Get the vector pointing from the current boid to the average location of surrounding boids
		sum.subVector(location);

		// Clamp this vector to our maximum velocity
		sum.setMagnitude(maxVelocity);

		// Get the difference between the current velocity and the desired velocity
		sum.subVector(velocity);

		sum.limit(maxAcceleration);
	}
	
	return sum;
}

// Checks if boids go out of the window and if so, flips their velocity.
void Boid::borders()
{
	if (location.x < 0 && velocity.x < 0) {
		velocity.x = -velocity.x;
	}
	if (location.x > window_width && velocity.x > 0) {
		velocity.x = -velocity.x;
	}
	if (location.y < 0 && velocity.y < 0) {
		velocity.y = -velocity.y;
	}
	if (location.y > window_height && velocity.y > 0) {
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
