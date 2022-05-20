#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "TrapDefense.hpp"
#include "AudioHelper.hpp"
#include "SphealBullet.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Army.hpp"
#include "Collider.hpp"

//Defense(std::string imgDefense, float x, float y, float radius, float coolDown, int hp, int id, float shootRadius);
TrapDefense::TrapDefense(float x, float y) :
    Defense("play/trap.png", x, y, 20, 1, 50, 3, 100) {
    // Move center downward, since our turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
    Visible = false;
}

void TrapDefense::Update(float deltaTime) {
    if (timeTicks <= timeSpan) {
        timeTicks += deltaTime;
        return;
    }
    PlayScene *scene = getPlayScene();
    if (!Enabled)
        return;
    Visible = scene->DebugMode;

    bool isTriggered = false;
    for (auto &it : scene->ArmyGroup->GetObjects()) {
        if (Engine::Collider::IsCircleOverlap(dynamic_cast<Army *>(it)->Position, 0, this->Position, scene->BlockSize / 2)) {
            isTriggered = true;
            break;
        }
    }
    if (isTriggered) {
        for (auto &it : scene->ArmyGroup->GetObjects()) {
            if (Engine::Collider::IsCircleOverlap(dynamic_cast<Army *>(it)->Position, 0, this->Position, this->shootRadius)) {
                dynamic_cast<Army *>(it)->Hit(INFINITY);
            }
        }
        scene->DefenseGroup->RemoveObject(objectIterator);
    }

}
