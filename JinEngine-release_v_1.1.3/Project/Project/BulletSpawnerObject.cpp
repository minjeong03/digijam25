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
	ObjectManager& om = engineContext.stateManager->GetCurrentState()->GetObjectManager();

	if (config.StartAngle == config.EndAngle)
	{
		int numBulletsToSpawn = 360.0f / config.PatternAngleSpacing;
		float patternAngleSpacingRadian = config.PatternAngleSpacing * (6.28318530717958647693f /360.f);
		float currAngle = 0;
		for (int i = 0; i < numBulletsToSpawn; ++i)
		{
			float x = config.CircleRadius * std::cos(currAngle);
			float y = config.CircleRadius * std::sin(currAngle);
			GameObjectUtils::CreateBulletObject(om, glm::vec2(x, y), glm::vec2(32, 32));
			currAngle += patternAngleSpacingRadian;
		}
	}
	else
	{

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