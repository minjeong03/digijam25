#pragma once
#include "GameObject.h"
#include "TextObject.h"

class BulletObject : public GameObject
{
public:
    void Init(const EngineContext& engineContext) override;
    void LateInit(const EngineContext& engineContext) override;
    void Update(float dt, const EngineContext& engineContext) override;
    void Draw(const EngineContext& engineContext) override;
    void Free(const EngineContext& engineContext) override;
    void LateFree(const EngineContext& engineContext) override;
    void OnCollision(Object* other) override;

private:
  
    TextObject* BulletTextObject;
    std::string BulletText = u8"æ»≥Á«œººø‰";
    float BulletActiveTimer = 0.0f;
};
