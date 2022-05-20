#ifndef StrengthenSpell_hpp
#define StrengthenSpell_hpp

#include "Army.hpp"
#include "PlayScene.hpp"

class StrengthenSpell : public Army {
public:
    float timeTicks = 0.0;
    float timeSpan = 2.0;
    bool isPlace = false;
    StrengthenSpell(int x, int y);
    void CreateBullet(Engine::Point pt) {}
    void OnExplode() {}
    void Update(float deltaTime) override;
    float GetShootRadius();
};

#endif /* StrengthenSpell_hpp */