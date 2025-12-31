#include "MainGame.h"
#include "BulletObject.h"
#include "MainGameUtils.h"
#include "WallObject.h"
#include "WillDisplayObject.h"
#include "BulletSpawnerObject.h"
#include "MainMenu.h"

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
	const float windowWidthHalf = engineContext.windowManager->GetWidth() * 0.5f;
	const float windowHeightHalf = engineContext.windowManager->GetHeight() * 0.5f;
	float willDisplayHeight = 200;

	player = static_cast<RealPlayer*>(objectManager.AddObject(std::make_unique<RealPlayer>(glm::vec2(-windowWidthHalf, -windowHeightHalf), glm::vec2(windowWidthHalf, windowHeightHalf-willDisplayHeight)), "[Object]player"));
	player->SetRenderLayer("[Layer]Player");
	player->GetTransform2D().SetDepth(00.0f);
	player->GetTransform2D().SetPosition(glm::vec2(0, 0));

	engineContext.soundManager->Play("[Sound]MainGameBGM", 1, 0);

	engineContext.windowManager->SetCursorVisible(true);

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

	if (elapsedTime >= endGameTime)
	{
		engineContext.stateManager->ChangeState(std::make_unique<MainMenu>());
	}

	if (engineContext.inputManager->IsKeyPressed(KEY_F))
	{
		LoadConfigFromFile();
	}

	BulletSpawnConfig config = configLoadedFromFile;
	BulletSpawnerObject* Obj = GameObjectUtils::CreateBulletSpawnerObject(objectManager, config);
	Obj->OnCollectedWord = [this](const std::string& str) {
		this->willDisplayObject->PushWord(str);
		};

	
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
	std::ifstream inputFile("data/Config/SpawnConfig.txt");

	if (!inputFile.is_open()) {
		return;
	}

	std::string str;
	bool readPos;
	int howmanyfiles;
	inputFile >> str >> configLoadedFromFile.CircleRadius;
	inputFile >> str >> configLoadedFromFile.Delay;
	inputFile >> str >> configLoadedFromFile.Lifetime;
	inputFile >> str >> configLoadedFromFile.PatternAngleSpacing;
	inputFile >> str >> configLoadedFromFile.SpawnInterval;
	inputFile >> str >> configLoadedFromFile.AngleVariance;
	inputFile >> str >> howmanyfiles;
	configLoadedFromFile.WordDataFilepaths.reserve(howmanyfiles);
	for (int i = 0; i < howmanyfiles; ++i)
	{
		inputFile >> str;
		configLoadedFromFile.WordDataFilepaths.push_back(str);
	}
	inputFile >> str >> configLoadedFromFile.StartAngle;
	inputFile >> str >> configLoadedFromFile.EndAngle;
	inputFile >> str >> configLoadedFromFile.BulletSpeed;
	inputFile >> str >> readPos;
	if (readPos)
	{
		inputFile >> str >> configLoadedFromFile.InitPos.x >> configLoadedFromFile.InitPos.y;
	}
	configReadPos = readPos;

	inputFile.close();
}
