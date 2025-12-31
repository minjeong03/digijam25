#pragma once
#include "GameObject.h"
#include "TextObject.h"
#include <queue>
#include <vector>

class WillDisplayObject : public GameObject
{
public:
    void Init(const EngineContext& engineContext) override;
    void LateInit(const EngineContext& engineContext) override;
    void Update(float dt, const EngineContext& engineContext) override;
    void Draw(const EngineContext& engineContext) override;
    void Free(const EngineContext& engineContext) override;
    void LateFree(const EngineContext& engineContext) override;
    void OnCollision(Object* other) override;
    void PushWord(const std::string& str);

    std::queue<std::string> pendingCollectedWords;
    std::vector<std::string> appliedCollectedWords;
private:
    TextObject* textObject;
    std::string currLineText;
    std::string currWholeText;
    int maxCharCountPerLine;
    int maxLinesPerDisplay;
};
