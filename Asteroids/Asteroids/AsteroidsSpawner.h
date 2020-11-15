#ifndef _ASTEROID_SPAWNER_H_
#define _ASTEROID_SPAWNER_H_

#include <vector>

class Asteroid;

class AsteroidsSpawner
{
public:
	void Update(float deltaTime, std::vector<Asteroid>& asteroids);
};

#endif

