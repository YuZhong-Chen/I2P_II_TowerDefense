#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "SphealDefense.hpp"
#include "AudioHelper.hpp"
#include "SphealBullet.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Army.hpp"

//Defense(std::string imgDefense, float x, float y, float radius, float coolDown, int hp, int id, float shootRadius);
SphealDefense::SphealDefense(float x, float y) :
    Defense("play/Spheal.png", x, y, 20, 0.3, 50, 2, 550) {
    // Move center downward, since our turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}

void SphealDefense::CreateBullet(Engine::Point pt) {
    int dx = pt.x - Position.x;
    int dy = pt.y - Position.y;
    double len = sqrt(pow(dx, 2) + pow(dy, 2));
    Engine::Point diff = Engine::Point(dx / len, dy / len);
    Engine::Point rotateDiff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(rotateDiff.y, rotateDiff.x) + ALLEGRO_PI / 2;
    getPlayScene()->BulletGroup->AddNewObject(new SphealBullet(Position, diff, rotation, this));
    AudioHelper::PlayAudio("gun.wav");
}
