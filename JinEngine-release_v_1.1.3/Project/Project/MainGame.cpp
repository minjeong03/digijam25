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

	rm->RegisterTexture("[Texture]BulletBackground", "Textures/bluebox.png"); 
	rm->RegisterMaterial("[Material]Bullet", "[EngineShader]default_texture", { {"u_Texture","[Texture]BulletBackground"} });
	rm->RegisterMaterial("[Material]WillDisplay", "[EngineShader]default_texture", { {"u_Texture","[Texture]WillBackground"} });

	rm->RegisterTexture("[Texture]Background", "Textures/BackGround.jpeg");

	SoundManager* sm = engineContext.soundManager;
	sm->LoadSound("[Sound]MainGameBGM", "Sounds/test.mp3");
	sm->LoadSound("[Sound]OuchSound", "Sounds/8bitsound.wav");
	sm->LoadSound("[Sound]ClickSound", "Sounds/poka.mp3");

	patterns.push_back(LoadPatternsFromFile("data/Patterns/p1.txt"));
	patterns.push_back(LoadPatternsFromFile("data/Patterns/p2.txt"));
	patterns.push_back(LoadPatternsFromFile("data/Patterns/p3.txt"));
}

void MainGame::Init(const EngineContext& engineContext)
{
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
	float prev = elapsedTime;
	elapsedTime += dt;

	if (elapsedTime >= endGameTime)
	{
		engineContext.stateManager->ChangeState(std::make_unique<MainMenu>());
	}

	for (int i = 0; i < patterns.size(); ++i)
	{
		RunPattern(patterns[i], prev, elapsedTime);
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

void MainGame::LoadConfigFromFile(BulletSpawnConfig& config, const std::string& path)
{
	std::ifstream inputFile(path);

	if (!inputFile.is_open()) {
		return;
	}

	std::string str;
	bool readPos;
	int howmanyfiles;
	inputFile >> str >> config.CircleRadius;
	inputFile >> str >> config.Delay;
	inputFile >> str >> config.Lifetime;
	inputFile >> str >> config.PatternAngleSpacing;
	inputFile >> str >> config.SpawnInterval;
	inputFile >> str >> config.AngleVariance;
	inputFile >> str >> howmanyfiles;
	config.WordDataFilepaths.reserve(howmanyfiles);
	for (int i = 0; i < howmanyfiles; ++i)
	{
		inputFile >> str;
		config.WordDataFilepaths.push_back(str);
	}
	inputFile >> str >> config.StartAngle;
	inputFile >> str >> config.EndAngle;
	inputFile >> str >> config.BulletSpeed;
	inputFile >> str >> readPos;
	if (readPos)
	{
		inputFile >> str >> config.InitPos.x >> config.InitPos.y;
	}
	configReadPos = readPos;

	inputFile.close();
}

SpawnPattern MainGame::LoadPatternsFromFile(const std::string& filepath)
{
	SpawnPattern pattern;
	pattern.loopTime = 0.0f;

	std::ifstream file(filepath);
	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << filepath << std::endl;
		return pattern;
	}

	file >> pattern.loopTime; 
	std::string path;
	file >> path;
	LoadConfigFromFile(pattern.config, path);
	int count;
	file >> count;
	char c;
	for (int i = 0; i < count; ++i)
	{
		SpawnData data;
		file >> data.spawnTime >> data.posX >> c >> data.posY;

		pattern.datum.push_back(data);
	}

	file.close();
	return pattern;
}

void MainGame::RunPattern(const SpawnPattern& p, float prevElapsed, float elapsedTime)
{
	BulletSpawnConfig config = p.config;
	float eTimePrev = std::fmod(prevElapsed, p.loopTime);
	float eTime = std::fmod(elapsedTime, p.loopTime);
	
	for (int i = 0; i < p.datum.size(); ++i)
	{
		if (eTimePrev < p.datum[i].spawnTime  && p.datum[i].spawnTime <= eTime)
		{
			JIN_LOG(p.datum[i].spawnTime << " spawn " << elapsedTime);
			config.InitPos.x = p.datum[i].posX;
			config.InitPos.y = p.datum[i].posY;
			BulletSpawnerObject* Obj = GameObjectUtils::CreateBulletSpawnerObject(objectManager, config);
			Obj->OnCollectedWord = [this](const std::string& str) {
				this->willDisplayObject->PushWord(str);
				};
		}
	}
}
