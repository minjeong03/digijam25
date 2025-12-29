#include "MainGame.h"



void MainGame::Load(const EngineContext& engineContext)
{
	RenderManager* rm = engineContext.renderManager;
	rm->RegisterTexture("[Texture]MainCharacter", "Textures/MainCharacter/prototype_character.png");
	rm->RegisterSpriteSheet("[SpriteSheet]MainCharacter", "[Texture]MainCharacter", 32, 32);

}

void MainGame::Init(const EngineContext& engineContext)
{
	player = static_cast<RealPlayer*>(objectManager.AddObject(std::make_unique<RealPlayer>(), "[Object]player"));
	player->SetRenderLayer("[Layer]Player");
	player->GetTransform2D().SetDepth(00.0f);
	player->GetTransform2D().SetPosition(glm::vec2(0, 0));
}

void MainGame::LateInit(const EngineContext& engineContext)
{
}

void MainGame::Update(float dt, const EngineContext& engineContext)
{

	objectManager.UpdateAll(dt, engineContext);
}

void MainGame::LateUpdate(float dt, const EngineContext& engineContext)
{
}

void MainGame::Draw(const EngineContext& engineContext)
{
	objectManager.DrawAll(engineContext);
}

void MainGame::Free(const EngineContext& engineContext)
{
}

void MainGame::Unload(const EngineContext& engineContext)
{
}
