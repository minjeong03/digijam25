#include "BulletSpawnerObject.h"
#include "Engine.h"
#include "ObjectManager.h"
#include "MainGameUtils.h"

BulletSpawnerObject::BulletSpawnerObject(const BulletSpawnConfig& config_)
	:config(config_)
{
}

void BulletSpawnerObject::Init(const EngineContext& engineContext)
{
	transform2D.SetPosition(config.InitPos);
	lifetimeTimer = 0;
	delayTimer = 0;
	spawnTimer = 0;
	activated = false;
}

void BulletSpawnerObject::LateInit(const EngineContext& engineContext)
{
	
}

void BulletSpawnerObject::Update(float dt, const EngineContext& engineContext)
{
	if (!activated)
	{
		delayTimer += dt;
		if (delayTimer >= config.Delay)
		{
			lifetimeTimer += delayTimer - config.Delay;
			activated = true;
		}
	}
	else
	{
		lifetimeTimer += dt;
		if (lifetimeTimer >= config.Lifetime)
		{
			Kill();
		}

		spawnTimer += dt;
		if (spawnTimer >= config.SpawnInterval)
		{
			SpawnBullets(engineContext);
			spawnTimer = 0;
		}
	}	
}

void BulletSpawnerObject::SpawnBullets(const EngineContext& engineContext) const
{
	const float rad = (6.28318530717958647693f / 360.f);
	ObjectManager& om = engineContext.stateManager->GetCurrentState()->GetObjectManager();

	int numBulletsToSpawn = 360.0f / config.PatternAngleSpacing;
	float currAngle = 0;
	const float patternAngleSpacingRadian = config.PatternAngleSpacing * rad;

	if (config.StartAngle < config.EndAngle)
	{
		numBulletsToSpawn = (config.EndAngle - config.StartAngle) / config.PatternAngleSpacing;
		currAngle = config.StartAngle * rad;
	}

	for (int i = 0; i < numBulletsToSpawn; ++i)
	{
		float dirX = std::cos(currAngle);
		float dirY = std::sin(currAngle);
		GameObjectUtils::CreateBulletObject(om, config.CircleRadius * glm::vec2(dirX, dirY), glm::vec2(32, 32), glm::vec2(dirX, dirY));
		currAngle += patternAngleSpacingRadian;
	}
}

void BulletSpawnerObject::Draw(const EngineContext& engineContext)
{

}

void BulletSpawnerObject::Free(const EngineContext& engineContext)
{
	
}

void BulletSpawnerObject::LateFree(const EngineContext& engineContext)
{
	
}

void BulletSpawnerObject::OnCollision(Object* other)
{
	
	
}