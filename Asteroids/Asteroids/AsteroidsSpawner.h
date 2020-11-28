#ifndef _ASTEROID_SPAWNER_H_
#define _ASTEROID_SPAWNER_H_

#include <vector>

class Asteroid;

class AsteroidsSpawner
{
private:
	struct SpawnInfo
	{
		int asteroidCount;
		float spawnDuration;
	};

public:

	AsteroidsSpawner();
	void Update(float deltaTime, std::vector<Asteroid>& asteroids);
	void StartWave(int difficulty);
	bool HasFinished() const;

private:

	static SpawnInfo dificultySpawnerAsteroids[];

	int dificultyIndex = 0;
	int asteroidSpawned = 0;
	float nextSpawnTimeRemaining = 0.0f;
	float totalTime;
};

#endif

