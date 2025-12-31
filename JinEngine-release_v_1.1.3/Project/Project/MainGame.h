#pragma once
#include <GameState.h>

#include "RealPlayer.h"
#include "BulletSpawnConfig.h"

struct SpawnData
{
    float spawnTime;
    float posX;
    float posY;
};

struct SpawnPattern
{
    float loopTime;
    std::vector<SpawnData> datum;
    BulletSpawnConfig config;
    
};

class MainGame : public GameState
{
public:
    void Load(const EngineContext& engineContext) override;

    void Init(const EngineContext& engineContext) override;

    void LateInit(const EngineContext& engineContext) override;

    void Update(float dt, const EngineContext& engineContext) override;

    void LateUpdate(float dt, const EngineContext& engineContext) override;

    void Draw(const EngineContext& engineContext) override;

    void Free(const EngineContext& engineContext) override;

    void Unload(const EngineContext& engineContext) override;

    void LoadConfigFromFile(BulletSpawnConfig& config, const std::string& str);

    SpawnPattern LoadPatternsFromFile(const std::string& filepath);

    void RunPattern(const SpawnPattern& p, float prevElapsed, float elapsedTime);

private:
    RealPlayer* player;
    float elapsedTime;
    float endGameTime = 30;
    class WillDisplayObject* willDisplayObject;
    bool configReadPos;

    std::vector<SpawnPattern> patterns;
};
