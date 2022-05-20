#ifndef SphealBullet_hpp
#define SphealBullet_hpp

#include "Bullet.hpp"

class Army;
class Defense;
namespace Engine {
    struct Point;
}  // namespace Engine

class SphealBullet : public Bullet {
public:
    explicit SphealBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Defense *parent);
    void Update(float deltaTime) override;
};

#endif /* CannonBullet_hpp */
