#pragma once
#include "GameObject.h"
#include "BulletSpawnConfig.h"

class BulletSpawnerObject : public GameObject
{
public:
    BulletSpawnerObject(const BulletSpawnConfig& config);

    void Init(const EngineContext& engineContext) override;
    void LateInit(const EngineContext& engineContext) override;
    void Update(float dt, const EngineContext& engineContext) override;
    void Draw(const EngineContext& engineContext) override;
    void Free(const EngineContext& engineContext) override;
    void LateFree(const EngineContext& engineContext) override;
    void OnCollision(Object* other) override;

private:
    BulletSpawnConfig config;
    float lifetimeTimer;
    float delayTimer;
    float spawnTimer;
    bool activated;

    void SpawnBullets(const EngineContext& engineContext) const;
};
