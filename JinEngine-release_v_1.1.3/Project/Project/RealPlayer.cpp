#include "RealPlayer.h"
#include "Engine.h"

RealPlayer::RealPlayer(const glm::vec2& boundaryMin_, const glm::vec2& boundaryMax_)
    : boundaryMin(boundaryMin_), boundaryMax(boundaryMax_)
{
}

void RealPlayer::Init(const EngineContext& engineContext)
{
    windowManager = engineContext.windowManager;
    transform2D.SetScale(glm::vec2(100.f));
    transform2D.SetPosition(glm::vec2(-300, 0));
    SetMesh(engineContext, "[EngineMesh]default");
    SetMaterial(engineContext, "[Material]Animation");
    SpriteSheet* sheet = engineContext.renderManager->GetSpriteSheetByTag("[SpriteSheet]MainCharacter");
    sheet->AddClip("[Clip]IdleFront", { 0,1 }, 0.15f, true);
    sheet->AddClip("[Clip]RunningRight", {16,17,18,19}, 0.08f, true);
    sheet->AddClip("[Clip]RunningFront", { 12,13,14,15 }, 0.08f, true);
    sheet->AddClip("[Clip]RunningBack", { 20, 21, 22 ,23 }, 0.08f, true);
    AttachAnimator(sheet, 0.08f);
    auto collider = std::make_unique<AABBCollider>(this, glm::vec2(1.0, 1.0));
    collider->SetUseTransformScale(false);
    collider->SetSize({ 90,70 });
    collider->SetOffset({ glm::vec2(0,10.f) });
    SetCollider(std::move(collider));
    SetCollision(engineContext.stateManager->GetCurrentState()->GetObjectManager(), "[CollisionTag]player",
        { "[CollisionTag]bullet" });
}

void RealPlayer::LateInit(const EngineContext& engineContext)
{

}

void RealPlayer::Update(float dt, const EngineContext& engineContext)
{
 
    //TODO : 대각선 이동속도 변경

    checkIdle = true;

    if (engineContext.inputManager->IsKeyDown(KEY_A))
    {
        checkIdle = false;
        checkIdle_prevFrame = false;
        transform2D.AddPosition(glm::vec2(-350 * dt, 0));
    }
    if (engineContext.inputManager->IsKeyDown(KEY_D))
    {
        checkIdle = false;
        checkIdle_prevFrame = false;
        transform2D.AddPosition(glm::vec2(350 * dt, 0));
    }

    if (engineContext.inputManager->IsKeyDown(KEY_W))
    {
        checkIdle = false;
        checkIdle_prevFrame = false;
        transform2D.AddPosition(glm::vec2(0, 350 * dt));
    }
    if (engineContext.inputManager->IsKeyDown(KEY_S))
    {
        checkIdle = false;
        checkIdle_prevFrame = false;
        transform2D.AddPosition(glm::vec2(0, -350 * dt));
    }

    glm::vec2 colliderHalfSize = static_cast<AABBCollider*>(GetCollider())->GetHalfSize();
    {
        glm::vec2 pos = transform2D.GetPosition();
        if (pos.x - colliderHalfSize.x < boundaryMin.x) // left
        {
            transform2D.SetPosition(glm::vec2(boundaryMin.x + colliderHalfSize.x, pos.y));
        }
        else if (pos.x + colliderHalfSize.x > boundaryMax.x) // right
        {
            transform2D.SetPosition(glm::vec2(boundaryMax.x - colliderHalfSize.x, pos.y));
        }
    }
    {
        glm::vec2 pos = transform2D.GetPosition();

        if (pos.y + colliderHalfSize.y > boundaryMax.y) // top
        {
            transform2D.SetPosition(glm::vec2(pos.x, boundaryMax.y - colliderHalfSize.y));
        }
        else if (pos.y - colliderHalfSize.y < boundaryMin.y) // bot
        {
            transform2D.SetPosition(glm::vec2(pos.x, boundaryMin.y + colliderHalfSize.y));
        }
    }

    if (spriteAnimator && engineContext.inputManager->IsKeyPressed(KEY_A))
    {
        SetFlipUV_X(true);
        spriteAnimator->PlayClip("[Clip]RunningRight");
    }
    if (spriteAnimator && engineContext.inputManager->IsKeyPressed(KEY_D))
    {
        SetFlipUV_X(false);
        spriteAnimator->PlayClip("[Clip]RunningRight");
    }

    if (spriteAnimator && engineContext.inputManager->IsKeyPressed(KEY_W))
    {
  
        spriteAnimator->PlayClip("[Clip]RunningBack");
    }
    if (spriteAnimator && engineContext.inputManager->IsKeyPressed(KEY_S))
    {

        spriteAnimator->PlayClip("[Clip]RunningFront");
    }

    if (spriteAnimator && checkIdle && !checkIdle_prevFrame)
    {
        checkIdle_prevFrame = true;
        spriteAnimator->PlayClip("[Clip]IdleFront");
    }

}

void RealPlayer::Draw(const EngineContext& engineContext)
{


}

void RealPlayer::Free(const EngineContext& engineContext)
{
  
}

void RealPlayer::LateFree(const EngineContext& engineContext)
{

}

void RealPlayer::OnCollision(Object* other)
{
   
}

bool RealPlayer::CheckIdle()
{
    return checkIdle;
}
