#pragma once
#include "GameObject.h"
#include "TextObject.h"

class BulletObject : public GameObject
{
public:
    BulletObject(const glm::vec2& Dir);

    void Init(const EngineContext& engineContext) override;
    void LateInit(const EngineContext& engineContext) override;
    void Update(float dt, const EngineContext& engineContext) override;
    void Draw(const EngineContext& engineContext) override;
    void Free(const EngineContext& engineContext) override;
    void LateFree(const EngineContext& engineContext) override;
    void OnCollision(Object* other) override;
    void SetWord(const std::string& word);

private:
    class SoundManager* soundManager;
    TextObject* BulletTextObject;
    std::string BulletText = u8"안녕하세요";
    float BulletActiveTimer = 0.0f;
    float BulletActiveTime = 1.0f;
    float Speed = 150;
    glm::vec2 Direction;
};
