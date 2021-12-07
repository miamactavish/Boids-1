#include "Pvector.h"
#include <vector>

#ifndef BOID_H_
#define BOID_H_

// The Boid Class

class Boid {
public:
	Pvector location;
	Pvector velocity;

	Boid(float x, float y);

	void run(vector <Boid> v);
	void update();
	void borders();
	float getAngle(Pvector v) const;
};

#endif
