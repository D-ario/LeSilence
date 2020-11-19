#include "AsteroidsSpawner.h"

#include "Asteroid.h"

#include <SFML/Graphics.hpp>

#include <iostream>

using namespace std;
using namespace sf;

AsteroidsSpawner::SpawnInfo AsteroidsSpawner::dificultySpawnerAsteroids[] = {
	{3, 3.0f},
	{5, 4.0f},
	{8, 6.0f},
	{10, 7.0f},
	{15, 9.0f},
	{25, 12.0f},
	{40, 16.0f},
	{70, 27.0f},
	{150, 32.0f},
	{360, 50.0f},
	{500, 150.0f},
};	

AsteroidsSpawner::AsteroidsSpawner()
{
	totalTime = 0;
	dificultyIndex = 3;
	asteroidSpawned = 0;

	SpawnInfo spawnInfo = dificultySpawnerAsteroids[dificultyIndex];

	nextSpawnTimeRemaining = 2.0f;
	if (totalTime + nextSpawnTimeRemaining > spawnInfo.spawnDuration)
	{
		nextSpawnTimeRemaining = spawnInfo.spawnDuration - totalTime;
	}
	cout << "Prochain spawn dans " << nextSpawnTimeRemaining << " secondes" << endl;
}

void AsteroidsSpawner::Update(float deltaTime, vector<Asteroid>& asteroids)
{
	totalTime += deltaTime;

	SpawnInfo spawnInfo = dificultySpawnerAsteroids[dificultyIndex];
	if (asteroidSpawned < spawnInfo.asteroidCount)
	{
		nextSpawnTimeRemaining -= deltaTime;
		if (nextSpawnTimeRemaining <= 0.0f)
		{
			nextSpawnTimeRemaining = (float)(rand() % (int)(spawnInfo.spawnDuration * 1000.0f * 0.25f)) * 0.001f;
			if (totalTime + nextSpawnTimeRemaining > spawnInfo.spawnDuration)
			{
				nextSpawnTimeRemaining = spawnInfo.spawnDuration - totalTime;
			}
			cout << "Prochain spawn dans " << nextSpawnTimeRemaining << " secondes" << endl;

			int asteroidNeeded = (int)((float)spawnInfo.asteroidCount / spawnInfo.spawnDuration * totalTime);

			cout << "Spawn " << asteroidNeeded - asteroidSpawned << " asteroids" << endl;

			while (asteroidSpawned < asteroidNeeded)
			{
				Asteroid asteroid(Vector2f(50000.0f, 50000.0f), (rand() % 300 + 50) * 0.01f);
				FloatRect bounds = asteroid.asteroidShape.getGlobalBounds();

				float x = 0;
				float y = 0;

				if (rand() % 2 == 0)
				{
					x = rand() % (1280 + 1);

					if (rand() % 2 == 0) // Haut
					{
						y = 0 - bounds.height/2;
					}
					else // Bas
					{
						y = 720 + bounds.height/2;
					}
				}
				else
				{
					y = rand() % (720 + 1);

					if (rand() % 2 == 0) // gauche
					{
						x = 0 - bounds.width/2;
					}
					else // droite
					{
						x = 1280 + bounds.width/2;
					}
				}

				asteroid.asteroidShape.setPosition(x, y);

				asteroids.push_back(asteroid);

				asteroidSpawned++;
			}
		}
	}
	else if (asteroids.empty())
	{
		dificultyIndex++;
		totalTime = 0;
		asteroidSpawned = 0;
		nextSpawnTimeRemaining = 2.0f;
		if (totalTime + nextSpawnTimeRemaining > spawnInfo.spawnDuration)
		{
			nextSpawnTimeRemaining = spawnInfo.spawnDuration - totalTime;
		}
		cout << "Prochain spawn dans " << nextSpawnTimeRemaining << " secondes" << endl;
	}
}
