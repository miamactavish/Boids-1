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

int Flock::predCount()
{
	return flock.size();
}

void Flock::addDesSep()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setDesSep(1);
	}
}

void Flock::subDesSep()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setDesSep(-1);
	}
}

void Flock::addDesAli()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setDesAli(1);
	}
}

void Flock::subDesAli()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setDesAli(-1);
	}
}

void Flock::addDesCoh()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setDesCoh(1);
	}
}

void Flock::subDesCoh()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setDesCoh(-1);
	}
}

void Flock::addSepW()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setSepW(.1);
	}
}

void Flock::subSepW()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setSepW(-.1);
	}
}

void Flock::addAliW()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setAliW(.1);
	}
}

void Flock::subAliW()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setAliW(-.1);
	}
}

void Flock::addCohW()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setCohW(.1);
	}
}

void Flock::subCohW()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setCohW(-.1);
	}
}
