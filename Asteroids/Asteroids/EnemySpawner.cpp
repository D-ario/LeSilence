#include "EnemySpawner.h"

#include "Enemy.h"

#include <SFML/Graphics.hpp>

#include <iostream>

using namespace std;
using namespace sf;

EnemySpawner::SpawnInfo EnemySpawner::dificultySpawnerEnemies[] = {
	{1, 3.0f},
	{2, 4.0f},
	{4, 6.0f},
	{6, 7.0f},
	{8, 9.0f},
	{12, 12.0f},
	{20, 16.0f},
	{25, 27.0f},
	{50, 32.0f},
	{75, 50.0f},
	{100, 150.0f},
};

EnemySpawner::EnemySpawner()
{
	totalTime = 0;
	dificultyIndex = 0;
	enemiesSpawned = 0;

	SpawnInfo spawnInfo = dificultySpawnerEnemies[dificultyIndex];

	nextSpawnTimeRemaining = 2.0f;
	if (totalTime + nextSpawnTimeRemaining > spawnInfo.spawnDuration)
	{
		nextSpawnTimeRemaining = spawnInfo.spawnDuration - totalTime;
	}
	cout << "Prochain enemy dans " << nextSpawnTimeRemaining << " secondes" << endl;
}

void EnemySpawner::Update(float deltaTime, vector<Enemy>& enemies)
{
	totalTime += deltaTime;

	SpawnInfo spawnInfo = dificultySpawnerEnemies[dificultyIndex];
	if (enemiesSpawned < spawnInfo.enemiesCount)
	{
		nextSpawnTimeRemaining -= deltaTime;
		if (nextSpawnTimeRemaining <= 0.0f)
		{
			nextSpawnTimeRemaining = (float)(rand() % (int)(spawnInfo.spawnDuration * 1000.0f * 0.25f)) * 0.001f;
			if (totalTime + nextSpawnTimeRemaining > spawnInfo.spawnDuration)
			{
				nextSpawnTimeRemaining = spawnInfo.spawnDuration - totalTime;
			}
			cout << "Prochain enemy dans " << nextSpawnTimeRemaining << " secondes" << endl;

			int asteroidNeeded = (int)((float)spawnInfo.enemiesCount / spawnInfo.spawnDuration * totalTime);

			cout << "Spawn " << asteroidNeeded - enemiesSpawned << " enemies" << endl;

			while (enemiesSpawned < asteroidNeeded)
			{
				//Enemy enemy(Vector2f(600.0f, 300.0f), (rand() % 300 + 100) * 0.01f, 3);
				Enemy enemy(Vector2f(600.0f, 300.0f));
				FloatRect bounds = enemy.enemyShape.getGlobalBounds();

				float x = 0;
				float y = 0;

				if (rand() % 2 == 0)
				{
					x = rand() % (1280 + 1);

					/*if (rand() % 2 == 0) // Haut
					{
						y = 0 - bounds.height / 2;
					}
					else // Bas
					{
						y = 720 + bounds.height / 2;
					}*/
				}
				else
				{
					y = rand() % (720 + 1);

					/*if (rand() % 2 == 0) // gauche
					{
						x = 0 - bounds.width / 2;
					}
					else // droite
					{
						x = 1280 + bounds.width / 2;
					}*/
				}

				enemy.enemyShape.setPosition(x, y);

				enemies.push_back(enemy);

				enemiesSpawned++;
			}
		}
	}
	else if (enemies.empty())
	{
		dificultyIndex++;
		totalTime = 0;
		enemiesSpawned = 0;
		nextSpawnTimeRemaining = 2.0f;
		if (totalTime + nextSpawnTimeRemaining > spawnInfo.spawnDuration)
		{
			nextSpawnTimeRemaining = spawnInfo.spawnDuration - totalTime;
		}
		cout << "Prochain enemy dans " << nextSpawnTimeRemaining << " secondes" << endl;
	}
}
