#include "MainGame.h"
#include "BulletObject.h"
#include "MainGameUtils.h"
#include "WallObject.h"

// temp code below
#include <fstream>

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
	LoadConfigFromFile();

	player = static_cast<RealPlayer*>(objectManager.AddObject(std::make_unique<RealPlayer>(), "[Object]player"));
	player->SetRenderLayer("[Layer]Player");
	player->GetTransform2D().SetDepth(00.0f);
	player->GetTransform2D().SetPosition(glm::vec2(0, 0));

	engineContext.soundManager->Play("[Sound]MainGameBGM", 1, 0);

	engineContext.windowManager->SetCursorVisible(true);


	elapsedTime = 0;
	float borderSize = 10;
	float posOffset = 100;
	float posLeft = -(engineContext.windowManager->GetWidth() + borderSize) * 0.5f;
	float posRight = (engineContext.windowManager->GetWidth() + borderSize) * 0.5f;
	float posTop = (engineContext.windowManager->GetHeight() + borderSize) * 0.5f ;
	float posBot = -(engineContext.windowManager->GetHeight() + borderSize) * 0.5f;

	WallObject* wallLeft = static_cast<WallObject*>(objectManager.AddObject(std::make_unique<WallObject>(), "[Object]wall"));
	wallLeft->GetTransform2D().SetScale(glm::vec2(borderSize, engineContext.windowManager->GetHeight() + borderSize));
	wallLeft->GetTransform2D().SetPosition(glm::vec2(posLeft - posOffset, 0));

	WallObject* wallRight = static_cast<WallObject*>(objectManager.AddObject(std::make_unique<WallObject>(), "[Object]wall"));
	wallRight->GetTransform2D().SetScale(glm::vec2(borderSize, engineContext.windowManager->GetHeight() + borderSize));
	wallRight->GetTransform2D().SetPosition(glm::vec2(posRight + posOffset, 0));
	
	WallObject* wallTop = static_cast<WallObject*>(objectManager.AddObject(std::make_unique<WallObject>(), "[Object]wall"));
	wallTop->GetTransform2D().SetScale(glm::vec2(engineContext.windowManager->GetWidth() + borderSize, borderSize));
	wallTop->GetTransform2D().SetPosition(glm::vec2(0, posTop + posOffset));

	WallObject* wallBot = static_cast<WallObject*>(objectManager.AddObject(std::make_unique<WallObject>(), "[Object]wall"));
	wallBot->GetTransform2D().SetScale(glm::vec2(engineContext.windowManager->GetWidth() + borderSize, borderSize));
	wallBot->GetTransform2D().SetPosition(glm::vec2(0, posBot - posOffset));
}

void MainGame::LateInit(const EngineContext& engineContext)
{
}

void MainGame::Update(float dt, const EngineContext& engineContext)
{
	elapsedTime += dt;

	if (engineContext.inputManager->IsKeyPressed(KEY_F))
	{
		LoadConfigFromFile();
	}

	if (engineContext.inputManager->IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		glm::vec2 mouseWorldPos = engineContext.inputManager->GetMouseWorldPos(GetActiveCamera());
		BulletSpawnConfig config = configLoadedFromFile;
		config.InitPos = mouseWorldPos;
		GameObjectUtils::CreateBulletSpawnerObject(objectManager, config);
		engineContext.soundManager->Play("[Sound]ClickSound");
		JIN_LOG(elapsedTime << "(s) LEFT: (" << mouseWorldPos.x << ", " << mouseWorldPos.y << ")");
	}
	
	if (engineContext.inputManager->IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	{
		glm::vec2 mouseWorldPos = engineContext.inputManager->GetMouseWorldPos(GetActiveCamera());
		BulletSpawnConfig config = configLoadedFromFile;
		config.InitPos = mouseWorldPos;
		GameObjectUtils::CreateBulletSpawnerObject(objectManager, config);
		engineContext.soundManager->Play("[Sound]ClickSound");
		JIN_LOG(elapsedTime << "(s) RIGHT: (" << mouseWorldPos.x << ", " << mouseWorldPos.y << ")");
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

void MainGame::LoadConfigFromFile()
{
	std::ifstream inputFile("data/SpawnConfig.txt");

	if (!inputFile.is_open()) {
		return;
	}

	std::string str;
	inputFile >> str >> configLoadedFromFile.CircleRadius;
	inputFile >> str >> configLoadedFromFile.Delay;
	inputFile >> str >> configLoadedFromFile.Lifetime;
	inputFile >> str >> configLoadedFromFile.PatternAngleSpacing;
	inputFile >> str >> configLoadedFromFile.SpawnInterval;
	inputFile >> str >> configLoadedFromFile.AngleVariance;
	inputFile >> str >> configLoadedFromFile.WordDataFilepath;

	inputFile.close();
}
