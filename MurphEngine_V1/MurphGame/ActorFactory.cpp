#include "ActorFactory.h"

#include <random>

/////////////////////////////
//// GAME LEVEL INCLUDES ////
/////////////////////////////
#include "BulletCollider.h"
#include "EnemyMove.h"
#include "EnemyShipCollider.h"
#include "PlayerShipMove.h"
#include "FiringComponent.h"
#include "EnemyBulletCollider.h"
#include "EnemyFiringComponent.h"
#include "PlayerShipCollider.h"
#include "ShieldCollider.h"

///////////////////////////////
//// ENGINE LEVEL INCLUDES ////
///////////////////////////////
#include "../MurphEngine/ActorManager.h"
#include "../MurphEngine/SpriteComponent.h"
#include "../MurphEngine/Source/Middleware/Bleach_New/BleachNew.h"

ActorFactory::ActorFactory(MurphEngine::ActorManager* pManager)
    : m_pActorManager(pManager)
    , m_objectCount(0)
{
}

MurphEngine::IActor* ActorFactory::CreatePlayer(float x, float y, float w, float h)
{
    const auto newPlayer = m_pActorManager->AddPlayer(x, y, "Assets/Player.png");
    newPlayer->SetSize(w, h);
    const auto collider = newPlayer->AddComponent(BLEACH_NEW(PlayerShipCollider(newPlayer)));
    collider->Initialize();
    const auto movement = newPlayer->AddComponent(BLEACH_NEW(PlayerShipMove(newPlayer)));
    static_cast<PlayerShipMove*>(movement)->SetNewMovementSpeed(0.75);
    const auto firingComponent = newPlayer->AddComponent(BLEACH_NEW(FiringComponent(newPlayer, this)));
    firingComponent->Initialize();
    // Testing functionality of adjusting fire-rate for tuning.
    static_cast<FiringComponent*>(firingComponent)->SetShotDelayMs(1000.0);
    return newPlayer;
}

MurphEngine::IActor* ActorFactory::CreateEnemyShip(float x, float y, float patrolWidth, float dropHeight, float shipWidth)
{
    ++m_objectCount;

    const char* filepath = nullptr;
    static thread_local std::mt19937 generator; // it's random enough for this use case.
    std::uniform_int_distribution distribution(1, 8);
    switch (distribution(generator))
    {
    case 1:
        filepath = "Assets/BlueAlien.png";
        break;
    case 2:
        filepath = "Assets/PastelPurpleAlien.png";
        break;
    case 3:
        filepath = "Assets/CyanAlien.png";
        break;
    case 4:
        filepath = "Assets/GreenAlien.png";
        break;
    case 5:
        filepath = "Assets/OrangeAlien.png";
        break;
    case 6:
        filepath = "Assets/PinkAlien.png";
        break;
    case 7:
        filepath = "Assets/YellowAlien.png";
        break;
    case 8:
        filepath = "Assets/DarkPurpleAlien.png";
        break;
    default:
        filepath = "Assets/RedAlien.png";
        break;
    }

    const auto newEnemyShip = m_pActorManager->AddActor(m_objectCount, x, y);
    newEnemyShip->GetSpriteComponent()->GetTexture(filepath);
    newEnemyShip->SetSize(shipWidth, shipWidth);
    auto componentToInitialize = newEnemyShip->AddComponent(BLEACH_NEW(EnemyMove(newEnemyShip, patrolWidth, dropHeight)));
    static_cast<EnemyMove*>(componentToInitialize)->SetNewMovementSpeed(.17);
    componentToInitialize = newEnemyShip->AddComponent(BLEACH_NEW(EnemyShipCollider(newEnemyShip)));
    componentToInitialize->Initialize();
    const auto firingComponent = newEnemyShip->AddComponent(BLEACH_NEW(EnemyFiringComponent(newEnemyShip, this)));
    firingComponent->Initialize();
    static_cast<EnemyFiringComponent*>(firingComponent)->SetChanceToFire(2.3f);

    return newEnemyShip;
}

void ActorFactory::CreateConcaveShield(float x, float y, float w, float h, size_t elementCount)
{
    ++m_objectCount;
    //Create offset values
    const auto localXOffset = w;
    const auto localYOffset = h / 2;

    // Create variables that will update if additional elements are required.
    float newX = x;
    float newY = y;
    float newNegX = x;

    auto shieldElement = m_pActorManager->AddActor(m_objectCount, newX, newY, w, h);
    auto componentToInit = shieldElement->AddComponent(BLEACH_NEW(ShieldCollider(shieldElement)));
    componentToInit->Initialize();
    shieldElement->GetSpriteComponent()->SetSpriteColor(0, 255, 0, 255);

    if (elementCount > 0)
    {
        for (size_t i = 0; i < elementCount; ++i)
        {
            // update local offset values
            newX += localXOffset;
            newNegX -= localXOffset;
            newY += localYOffset;

            // Create an additional shield to the right, and down half the height of previous.
            ++m_objectCount;
            shieldElement = m_pActorManager->AddActor(m_objectCount, newX, newY, w, h);
            componentToInit = shieldElement->AddComponent(BLEACH_NEW(ShieldCollider(shieldElement)));
            componentToInit->Initialize();
            shieldElement->GetSpriteComponent()->SetSpriteColor(0, 255, 0, 255);

            // Create an additional shield to the left, and down half the height of previous.
            ++m_objectCount;
            shieldElement = m_pActorManager->AddActor(m_objectCount, newNegX, newY, w, h);
            componentToInit = shieldElement->AddComponent(BLEACH_NEW(ShieldCollider(shieldElement)));
            componentToInit->Initialize();
            shieldElement->GetSpriteComponent()->SetSpriteColor(0, 255, 0, 255);
        }
    }
}

MurphEngine::IActor* ActorFactory::CreateSingleShield(float x, float y, float w, float h)
{
    ++m_objectCount;
    const auto shieldElement = m_pActorManager->AddActor(m_objectCount, x, y, w, h);
    const auto componentToInit = shieldElement->AddComponent(BLEACH_NEW(ShieldCollider(shieldElement)));
    componentToInit->Initialize();
    shieldElement->GetSpriteComponent()->SetSpriteColor(0, 255, 0, 255);

    return shieldElement;
}

MurphEngine::IActor* ActorFactory::CreateBullet(float x, float y)
{
    ++m_objectCount;
    const auto bullet = m_pActorManager->AddActor(m_objectCount, x, y);
    bullet->SetSize(4, 8);
    bullet->GetSpriteComponent()->SetSpriteColor(245, 61, 255, 255);
    const auto bulletComponent = bullet->AddComponent(BLEACH_NEW(BulletCollider(bullet)));
    bulletComponent->Initialize();
    return nullptr;
}

MurphEngine::IActor* ActorFactory::CreateEnemyBullet(float x, float y)
{
    ++m_objectCount;
    const auto bullet = m_pActorManager->AddActor(m_objectCount, x, y);
    bullet->SetSize(4, 8);
    bullet->GetSpriteComponent()->SetSpriteColor(255, 0, 0, 255);
    const auto bulletComponent = bullet->AddComponent(BLEACH_NEW(EnemyBulletCollider(bullet)));
    bulletComponent->Initialize();
    return nullptr;
}

void ActorFactory::CreateShipRow(float startY, float startX, float shipSeparation, size_t horizontalCount, float patrolWidth, float dropHeight)
{
    constexpr auto shipWidth = 35.0f;
    //Create offset values
    const float localXOffset = shipWidth + shipSeparation;

    // Create variables that will update if additional elements are required.
    float newX = startX - (shipWidth / 2);
    float newNegX = newX;
    CreateEnemyShip(newX, startY, patrolWidth, dropHeight, shipWidth);

    ++m_objectCount;

    for (size_t i = 0; i < horizontalCount; ++i)
    {
        newX += localXOffset;
        newNegX -= localXOffset;

        ++m_objectCount;
        CreateEnemyShip(newX, startY, patrolWidth, dropHeight, shipWidth);

        ++m_objectCount;
        CreateEnemyShip(newNegX, startY, patrolWidth, dropHeight, shipWidth);
    }
}

void ActorFactory::CreateSpaceInvadersShield(float x, float y)
{
    // this is the size of each block, it will adjust overall size of shield.
    constexpr float width = 8;
    constexpr float height = 6;
    constexpr int sideSize = 2;

    // Create variables that will update if additional elements are required.
    float newX = x;
    float newY = y;
    float newNegX = x;

    CreateSingleShield(newX, newY, width, height);

    newY += height;

    CreateSingleShield(newX, newY, width, height);
    CreateSingleShield(newX, newY + height, width, height);
    CreateSingleShield(newX, newY + height * 2, width, height);

    newX += width;
    newNegX -= width;

    // first "Wings"
    for (int i = 0; i <= sideSize; ++i)
    {
        CreateSingleShield(newX, newY + (height * static_cast<float>(i)), width, height);
        CreateSingleShield(newNegX, newY + (height * static_cast<float>(i)), width, height);
    }

    newY += height / 2;
    newX += width;
    newNegX -= width;

    //second "Wings"
    for (int i = 0; i <= sideSize; ++i) //smell
    {
        CreateSingleShield(newX, newY + (height * static_cast<float>(i)), width, height);
        CreateSingleShield(newNegX, newY + (height * static_cast<float>(i)), width, height);
    }


    newY += height / 2;
    newX += width;
    newNegX -= width;

    //third "Wings"
    for (int i = 0; i <= sideSize; ++i) //smell
    {
        CreateSingleShield(newX, newY + (height * static_cast<float>(i)), width, height);
        CreateSingleShield(newNegX, newY + (height * static_cast<float>(i)), width, height);
    }


    newY += height;
    newX += width;
    newNegX -= width;

    //third "Wings"
    for (int i = 0; i <= sideSize; ++i) //smell
    {
        CreateSingleShield(newX, newY + (height * static_cast<float>(i)), width, height);
        CreateSingleShield(newNegX, newY + (height * static_cast<float>(i)), width, height);
    }
}
