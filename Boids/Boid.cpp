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
	maxSpeed = 1.0;
	maxForce = 0.5;

	velocity = Pvector(rand() % 10 / 10.0, rand() % 10 / 10.0);

	acceleration = Pvector(0, 0);

	// places boid in a random location in the window
	location = Pvector((rand() % window_width), (rand() % window_height));

	//location = Pvector(x, y);

	desSep = 20;
	desAli = 70;
	desCoh = 25;
	SepW = 1.5;
	AliW = 1.0;
	CohW = 1.0;
}

// Adds force Pvector to current force Pvector
void Boid::applyForce(Pvector force)
{
	acceleration.addVector(force);
}

// Separation
// Keeps boids from getting too close to one another
Pvector Boid::Separation(vector<Boid> boids)
{
	// Distance of field of vision for separation between boids
	float desiredseparation = desSep;
	Pvector steer(0, 0);
	int count = 0;
	// For every boid in the system, check if it's too close
	for (int i = 0; i < boids.size(); i++) {
		// Calculate distance from current boid to boid we're looking at
		float d = location.distance(boids[i].location);
		// If this is a fellow boid and it's too close, move away from it
		if ((d > 0) && (d < desiredseparation)) {
			Pvector diff(0, 0);
			diff = diff.subTwoVector(location, boids[i].location);
			diff.normalize();
			diff.divScalar(d);      // Weight by distance
			steer.addVector(diff);
			count++;
		}
	}
	// Adds average difference of location to acceleration
	if (count > 0)
		steer.divScalar(static_cast<float>(count));
	if (steer.magnitude() > 0) {
		// Steering = Desired - Velocity
		steer.normalize();
		steer.mulScalar(maxSpeed);
		steer.subVector(velocity);
		steer.limit(maxForce);
	}
	return steer;
}

// Alignment
// Calculates the average velocity of boids in the field of vision and
// manipulates the velocity of the current boid in order to match it
Pvector Boid::Alignment(vector<Boid> Boids)
{
	float neighbordist = desAli; // Field of vision

	Pvector sum(0, 0);
	int count = 0;
	for (int i = 0; i < Boids.size(); i++) {
		float d = location.distance(Boids[i].location);

		if ((d > 0) && (d < neighbordist)) { // 0 < d < 50
			sum.addVector(Boids[i].velocity);
			count++;
		}
	}
	// If there are boids close enough for alignment...
	if (count > 0) {
		sum.divScalar(static_cast<float>(count));// Divide sum by the number of close boids (average of velocity)
		sum.normalize();            // Turn sum into a unit vector, and
		sum.mulScalar(maxSpeed);    // Multiply by maxSpeed
		// Steer = Desired - Velocity
		Pvector steer;
		steer = steer.subTwoVector(sum, velocity); //sum = desired(average)
		steer.limit(maxForce);
		return steer;
	}
	else {
		Pvector temp(0, 0);
		return temp;
	}
}

// Cohesion
// Finds the average location of nearby boids and manipulates the
// steering force to move in that direction.
Pvector Boid::Cohesion(vector<Boid> Boids)
{
	float neighbordist = desCoh;
	Pvector sum(0, 0);
	int count = 0;
	for (int i = 0; i < Boids.size(); i++) {
		float d = location.distance(Boids[i].location);

		neighbordist = 15;

		if ((d > 0) && (d < neighbordist)) {
			sum.addVector(Boids[i].location);
			count++;
		}
	}
	if (count > 0) {
		sum.divScalar(count);
		return seek(sum);
	}
	else {
		Pvector temp(0, 0);
		return temp;
	}
}

// Limits the maxSpeed, finds necessary steering force and
// normalizes vectors
Pvector Boid::seek(Pvector v)
{
	Pvector desired;
	desired.subVector(v);  // A vector pointing from the location to the target
	// Normalize desired and scale to maximum speed
	desired.normalize();
	desired.mulScalar(maxSpeed);
	// Steering = Desired minus Velocity
	acceleration.subTwoVector(desired, velocity);
	acceleration.limit(maxForce);  // Limit to maximum steering force
	return acceleration;
}

// Modifies velocity, location, and resets acceleration with values that
// are given by the three laws.
void Boid::update()
{
	//To make the slow down not as abrupt
	acceleration.mulScalar(.35);
	// Update velocity
	velocity.addVector(acceleration);
	// Limit speed
	velocity.limit(maxSpeed);
	location.addVector(velocity);
	// Reset accelertion to 0 each cycle
	acceleration.mulScalar(0);
}

// Run flock() on the flock of boids.
// This applies the three rules, modifies velocities accordingly, updates data,
// and corrects boids which are sitting outside of the SFML window
void Boid::run(vector <Boid> v)
{
	//flock(v);
	update();
	borders();
}

// Applies the three laws to the flock of boids
void Boid::flock(vector<Boid> v)
{
	Pvector sep = Separation(v);
	Pvector ali = Alignment(v);
	Pvector coh = Cohesion(v);
	// Arbitrarily weight these forces
	sep.mulScalar(SepW);
	ali.mulScalar(AliW); // Might need to alter weights for different characteristics
	coh.mulScalar(CohW);
	// Add the force vectors to acceleration
	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
}

// Checks if boids go out of the window and if so, wraps them around to
// the other side.
void Boid::borders()
{
	if (location.x < 0 || location.x > window_width) {
		velocity.x = -velocity.x;
		acceleration.x = -acceleration.x;
	}
	if (location.y < 0 || location.y > window_height) {
		velocity.y = -velocity.y;
		acceleration.y = -acceleration.y;
	}

	/*
	if (location.x < 0)    location.x += window_width;
	if (location.y < 0)    location.y += window_height;
	if (location.x > window_width) location.x -= window_width;
	if (location.y > window_height) location.y -= window_height;
	*/
}

// Calculates the angle for the velocity of a boid which allows the visual
// image to rotate in the direction that it is going in.
float Boid::getAngle(Pvector v) const
{
	// From the definition of the dot product
	float angle = static_cast<float>(atan2(v.x, -v.y) * 180 / M_PI);
	return angle;
}

float Boid::getDesSep() const { return desSep; }

float Boid::getDesAli() const { return desAli; }

float Boid::getDesCoh() const { return desCoh; }

float Boid::getSepW() const { return SepW; }

float Boid::getAliW() const { return AliW; }

float Boid::getCohW() const { return CohW; }

void Boid::setDesSep(float x) { desSep += x; }

void Boid::setDesAli(float x) { desAli += x; }

void Boid::setDesCoh(float x) { desCoh += x; }

void Boid::setSepW(float x) { SepW += x; }

void Boid::setAliW(float x) { AliW += x; }

void Boid::setCohW(float x) { CohW += x; }