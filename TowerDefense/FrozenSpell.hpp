#ifndef FrozenSpell_hpp
#define FrozenSpell_hpp

#include "Army.hpp"

class FrozenSpell : public Army {
public:
    float timeTicks = 0.0;
    float timeSpan = 2.0; 
    bool isPlace = false;
    FrozenSpell(int x, int y);
    void CreateBullet(Engine::Point pt) {}
    void OnExplode() {}
    void Update(float deltaTime) override;
};

#endif /* FrozenSpell_hpp */