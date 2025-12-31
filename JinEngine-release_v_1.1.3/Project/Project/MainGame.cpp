#include "MainGame.h"
#include "BulletObject.h"
#include "MainGameUtils.h"
#include "WallObject.h"
#include "WillDisplayObject.h"
#include "BulletSpawnerObject.h"

// temp code below
#include <fstream>

void MainGame::Load(const EngineContext& engineContext)
{
	RenderManager* rm = engineContext.renderManager;
	rm->RegisterTexture("[Texture]MainCharacter", "Textures/MainCharacter/prototype_character.png");
	rm->RegisterTexture("[Texture]WillBackground", "Textures/whitebox.png");
	rm->RegisterSpriteSheet("[SpriteSheet]MainCharacter", "[Texture]MainCharacter", 32, 32);

	rm->RegisterTexture("[Texture]BulletBackground", "Textures/leaf.png"); 
	rm->RegisterMaterial("[Material]Bullet", "[EngineShader]default_texture", { {"u_Texture","[Texture]BulletBackground"} });
	rm->RegisterMaterial("[Material]WillDisplay", "[EngineShader]default_texture", { {"u_Texture","[Texture]WillBackground"} });


	SoundManager* sm = engineContext.soundManager;
	sm->LoadSound("[Sound]MainGameBGM", "Sounds/test.mp3");
	sm->LoadSound("[Sound]OuchSound", "Sounds/8bitsound.wav");
	sm->LoadSound("[Sound]ClickSound", "Sounds/poka.mp3");
}

void MainGame::Init(const EngineContext& engineContext)
{
	LoadConfigFromFile();


	elapsedTime = 0;
	float borderSize = 10;
	float posOffset = 100;
	const float windowWidthHalf = engineContext.windowManager->GetWidth() * 0.5f;
	const float windowHeightHalf = engineContext.windowManager->GetHeight() * 0.5f;
	float posRight = windowWidthHalf + borderSize * 0.5f;
	float posTop = windowHeightHalf + borderSize * 0.5f;
	float willDisplayHeight = 200;

	player = static_cast<RealPlayer*>(objectManager.AddObject(std::make_unique<RealPlayer>(glm::vec2(-windowWidthHalf, -windowHeightHalf), glm::vec2(windowWidthHalf, windowHeightHalf-willDisplayHeight)), "[Object]player"));
	player->SetRenderLayer("[Layer]Player");
	player->GetTransform2D().SetDepth(00.0f);
	player->GetTransform2D().SetPosition(glm::vec2(0, 0));

	engineContext.soundManager->Play("[Sound]MainGameBGM", 1, 0);

	engineContext.windowManager->SetCursorVisible(true);

	WallObject* wallLeft = static_cast<WallObject*>(objectManager.AddObject(std::make_unique<WallObject>(), "[Object]wall"));
	wallLeft->GetTransform2D().SetScale(glm::vec2(borderSize, engineContext.windowManager->GetHeight() + borderSize));
	wallLeft->GetTransform2D().SetPosition(glm::vec2(-posRight - posOffset, 0));

	WallObject* wallRight = static_cast<WallObject*>(objectManager.AddObject(std::make_unique<WallObject>(), "[Object]wall"));
	wallRight->GetTransform2D().SetScale(glm::vec2(borderSize, engineContext.windowManager->GetHeight() + borderSize));
	wallRight->GetTransform2D().SetPosition(glm::vec2(posRight + posOffset, 0));
	
	WallObject* wallTop = static_cast<WallObject*>(objectManager.AddObject(std::make_unique<WallObject>(), "[Object]wall"));
	wallTop->GetTransform2D().SetScale(glm::vec2(engineContext.windowManager->GetWidth() + borderSize, borderSize));
	wallTop->GetTransform2D().SetPosition(glm::vec2(0, posTop + posOffset - willDisplayHeight));

	WallObject* wallBot = static_cast<WallObject*>(objectManager.AddObject(std::make_unique<WallObject>(), "[Object]wall"));
	wallBot->GetTransform2D().SetScale(glm::vec2(engineContext.windowManager->GetWidth() + borderSize, borderSize));
	wallBot->GetTransform2D().SetPosition(glm::vec2(0, -posTop - posOffset));

	willDisplayObject = static_cast<WillDisplayObject*>(objectManager.AddObject(std::make_unique<WillDisplayObject>(), "[Object]WillDisplay"));
	willDisplayObject->GetTransform2D().SetScale(glm::vec2(engineContext.windowManager->GetWidth(), willDisplayHeight));
	willDisplayObject->GetTransform2D().SetPosition(glm::vec2(0, (engineContext.windowManager->GetHeight() - willDisplayHeight) *0.5f));
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
		BulletSpawnerObject* Obj = GameObjectUtils::CreateBulletSpawnerObject(objectManager, config);
		Obj->OnCollectedWord = [this](const std::string& str) {
			this->willDisplayObject->PushWord(str);
			};

		engineContext.soundManager->Play("[Sound]ClickSound");
		JIN_LOG(elapsedTime << "(s) LEFT: (" << mouseWorldPos.x << ", " << mouseWorldPos.y << ")");
	}
	
	if (engineContext.inputManager->IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	{
		glm::vec2 mouseWorldPos = engineContext.inputManager->GetMouseWorldPos(GetActiveCamera());
		BulletSpawnConfig config = configLoadedFromFile;
		config.InitPos = mouseWorldPos;
		BulletSpawnerObject* Obj = GameObjectUtils::CreateBulletSpawnerObject(objectManager, config);
		Obj->OnCollectedWord = [this](const std::string& str) {
			this->willDisplayObject->PushWord(str);
			};
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
	inputFile >> str >> configLoadedFromFile.StartAngle;
	inputFile >> str >> configLoadedFromFile.EndAngle;
	inputFile >> str >> configLoadedFromFile.BulletSpeed;

	inputFile.close();
}
