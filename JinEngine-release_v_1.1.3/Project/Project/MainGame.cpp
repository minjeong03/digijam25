#include "MainGame.h"
#include "BulletObject.h"


void MainGame::Load(const EngineContext& engineContext)
{
	RenderManager* rm = engineContext.renderManager;
	rm->RegisterTexture("[Texture]MainCharacter", "Textures/MainCharacter/prototype_character.png");
	rm->RegisterSpriteSheet("[SpriteSheet]MainCharacter", "[Texture]MainCharacter", 32, 32);

	rm->RegisterTexture("[Texture]BulletBackground", "Textures/leaf.png"); 
	rm->RegisterMaterial("[Material]Bullet", "[EngineShader]default_texture", { {"u_Texture","[Texture]BulletBackground"} });

}

void MainGame::Init(const EngineContext& engineContext)
{
	player = static_cast<RealPlayer*>(objectManager.AddObject(std::make_unique<RealPlayer>(), "[Object]player"));
	player->SetRenderLayer("[Layer]Player");
	player->GetTransform2D().SetDepth(00.0f);
	player->GetTransform2D().SetPosition(glm::vec2(0, 0));


	BulletObject* LocalBullet;

	LocalBullet = static_cast<BulletObject*>(objectManager.AddObject(std::make_unique<BulletObject>(), "[Object]player"));
	LocalBullet->SetRenderLayer("[Layer]Player");
	LocalBullet->GetTransform2D().SetDepth(00.0f);
	LocalBullet->GetTransform2D().SetScale(glm::vec2(32, 32));
	LocalBullet->GetTransform2D().SetPosition(glm::vec2(0, 0));




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
