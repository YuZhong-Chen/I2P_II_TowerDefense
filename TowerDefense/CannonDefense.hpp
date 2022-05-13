#ifndef CannonDefense_hpp
#define CannonDefense_hpp

#include "Defense.hpp"

class CannonDefense: public Defense {
public:
    CannonDefense(float x, float y);
    void CreateBullet(Engine::Point pt) override;
};

#endif /* CannonDefense_hpp */
