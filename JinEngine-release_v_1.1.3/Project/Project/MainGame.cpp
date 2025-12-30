#include "MainGame.h"
#include "BulletObject.h"
#include "MainGameUtils.h"

void MainGame::Load(const EngineContext& engineContext)
{
	RenderManager* rm = engineContext.renderManager;
	rm->RegisterTexture("[Texture]MainCharacter", "Textures/MainCharacter/prototype_character.png");
	rm->RegisterSpriteSheet("[SpriteSheet]MainCharacter", "[Texture]MainCharacter", 32, 32);

	rm->RegisterTexture("[Texture]BulletBackground", "Textures/leaf.png"); 
	rm->RegisterMaterial("[Material]Bullet", "[EngineShader]default_texture", { {"u_Texture","[Texture]BulletBackground"} });


	SoundManager* sm = engineContext.soundManager;
	sm->LoadSound("[Sound]MainGameBGM", "Sounds/test.mp3");
	sm->LoadSound("[Sound]OuchSound", "Sounds/8bitsound.wav");
	sm->LoadSound("[Sound]ClickSound", "Sounds/poka.mp3");
}

void MainGame::Init(const EngineContext& engineContext)
{
	player = static_cast<RealPlayer*>(objectManager.AddObject(std::make_unique<RealPlayer>(), "[Object]player"));
	player->SetRenderLayer("[Layer]Player");
	player->GetTransform2D().SetDepth(00.0f);
	player->GetTransform2D().SetPosition(glm::vec2(0, 0));

	GameObjectUtils::CreateBulletObject(objectManager, glm::vec2(0, 0), glm::vec2(32, 32), glm::vec2(1, 0));

	engineContext.soundManager->Play("[Sound]MainGameBGM", 1, 0);
}

void MainGame::LateInit(const EngineContext& engineContext)
{
}

void MainGame::Update(float dt, const EngineContext& engineContext)
{
	if (engineContext.inputManager->IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		glm::vec2 mouseWorldPos = engineContext.inputManager->GetMouseWorldPos(GetActiveCamera());
		BulletSpawnConfig config;
		config.InitPos = mouseWorldPos;
		config.CircleRadius = 50;
		config.Delay = 3;
		config.Lifetime = 10;
		config.PatternAngleSpacing = 30;
		config.SpawnInterval = 1;
		config.AngleVariance = 2;
		GameObjectUtils::CreateBulletSpawnerObject(objectManager, config);
		engineContext.soundManager->Play("[Sound]ClickSound");
	}
	
	if (engineContext.inputManager->IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	{
		glm::vec2 mouseWorldPos = engineContext.inputManager->GetMouseWorldPos(GetActiveCamera());
		BulletSpawnConfig config;
		config.InitPos = mouseWorldPos;
		config.CircleRadius = 50;
		config.Delay = 3;
		config.Lifetime = 10;
		config.PatternAngleSpacing = 30;
		config.SpawnInterval = 1;
		config.AngleVariance = 2;
		config.StartAngle = 210;
		config.EndAngle = 301;
		GameObjectUtils::CreateBulletSpawnerObject(objectManager, config);
		engineContext.soundManager->Play("[Sound]ClickSound");
	}

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
