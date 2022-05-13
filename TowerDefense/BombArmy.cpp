#include <allegro5/base.h>
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Collider.hpp"
#include "Army.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "BombArmy.hpp"
#include "Defense.hpp"


//Army(std::string img, float x, float y, float radius, float coolDown, float speed, float hp, int id, float shootRadius);
BombArmy::BombArmy(float x, float y) :
    Army("play/bombs.png", x, y, 20, 0, 80, 15, 1, 0) {
    // Move center downward, since we the army head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void BombArmy::Update(float deltaTime) {
    // PlayScene
    PlayScene* scene = getPlayScene();

    if (isPreview) return ;
    
    // position
    int x = static_cast<int>(floor(Position.x / PlayScene::BlockSize));
    int y = static_cast<int>(floor(Position.y / PlayScene::BlockSize));
    
    if (!Target) {
        // Lock closet target
        // Can be improved by Spatial Hash, Quad Tree, ...
        // However simply loop through all enemies is enough for this program.
        
        // TODO 2 (6/8): Lock the closet wall. If there's no wall on the map, it will lock the closet defense.
        // For the simplicity, we use manHattan distance to measure the distance bewteen objects. You can use the ManHattanDistance() function in Army class directly for calculation.

        
        // TODO 2 (7/8): Store the closet target in Target, and update lockedArmyIterator. You can imitate the same part in Defense::Update().
        // Also, record the target is wall or a noraml defense.

    }
    if (Target) {
        Rotation = UpdateRotation(deltaTime, Target->Position);
        // Bomb cannot shoot, so the reload time just set as coolDown.
        reload = coolDown;
        
        // TODO 2 (8/8): If bomb army is on the same block with target. Explode itself to deal damage to the target. Otherwise, move toward the target.
        if (false /* need to modify */) {
            // Notice that bomb army deals different damage to wall and normal target.
            Hit(INFINITY);
        }
        else {
            int dx = Target->Position.x - Position.x;
            int dy = Target->Position.y - Position.y;
            double len = sqrt(pow(dx, 2) + pow(dy, 2));
            Velocity = speed * Engine::Point(dx / len, dy / len);
        }
        
    }

    Position.x += Velocity.x * deltaTime;
    Position.y += Velocity.y * deltaTime;
}

// Since the bomb army cannot shoot, the function doesn't need to do anything.
void BombArmy::CreateBullet(Engine::Point pt) {}

// TODO 2 (5/8): You can imitate the hit function in Army class. Notice that the bomb army won't have explosion effect.
void BombArmy::Hit(float damage) {

}
