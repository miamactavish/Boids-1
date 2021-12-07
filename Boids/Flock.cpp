#include "Boid.h"
#include "Flock.h"

// =============================================== //
// ======== Flock Functions from Flock.h ========= //
// =============================================== //

int Flock::getSize() const { return flock.size(); }

Boid Flock::getBoid(int i) { return flock[i]; }


void Flock::addBoid(Boid b) { flock.push_back(b); }

// Runs the run function for every boid in the flock checking against the flock
// itself. Which in turn applies all the rules to the flock.
void Flock::flocking()
{
	for (int i = 0; i < flock.size(); i++)
	{
		//Only checks in a certain range instead of checking through the whole flock in an attempt to reduce time complexity
		for (int j = 0; j < flock.size(); j++) 
		{
			if (flock[i].location.distance(flock[j].location) <= abs(20)) // Not sure if distance is 1:1 with SFML window size or if it is even working
			{
				flock[i].run(flock);
			}
		}
	}
}

int Flock::flockCount()
{
	return flock.size();
}
