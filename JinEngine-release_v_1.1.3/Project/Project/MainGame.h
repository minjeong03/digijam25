#pragma once
#include <GameState.h>

#include "RealPlayer.h"
#include "BulletSpawnConfig.h"

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

    void LoadConfigFromFile();
private:
    BulletSpawnConfig configLoadedFromFile;
    RealPlayer* player;
    float elapsedTime;
    float endGameTime = 30;
    class WillDisplayObject* willDisplayObject;
    bool configReadPos;
};
