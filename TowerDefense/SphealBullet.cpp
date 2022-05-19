#include <allegro5/base.h>
#include <random>
#include <string>

#include "DirtyEffect.hpp"
#include "SphealBullet.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"

class Defense;

//Bullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Defense* defenseParent);
SphealBullet::SphealBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Defense *parent) :
    Bullet("play/bullet-13.png", 300, 2, position, forwardDirection, rotation, parent) {}
