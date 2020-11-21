#ifndef _ENEMY_SPAWNER_H_
#define _ENEMY_SPAWNER_H_

#include <vector>

class Enemy;

class EnemySpawner
{
private:
	struct SpawnInfo
	{
		int enemiesCount;
		float spawnDuration;
	};

public:

	EnemySpawner();
	void Update(float deltaTime, std::vector<Enemy>& enemies);

private:

	static SpawnInfo dificultySpawnerEnemies[];

	int dificultyIndex = 0;
	int enemiesSpawned = 0;
	float nextSpawnTimeRemaining = 0.0f;
	float totalTime;
};

#endif

