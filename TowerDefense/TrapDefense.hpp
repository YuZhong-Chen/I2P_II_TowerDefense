#ifndef TrapDefense_hpp
#define TrapDefense_hpp

#include "Defense.hpp"

class TrapDefense : public Defense {
public:
    TrapDefense(float x, float y);
    void CreateBullet(Engine::Point pt) {}
    void Update(float deltaTime) override;
};

#endif /* TrapDefense_hpp */
