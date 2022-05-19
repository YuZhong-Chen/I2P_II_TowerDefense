#ifndef SphealDefense_hpp
#define SphealDefense_hpp

#include "Defense.hpp"

class SphealDefense : public Defense {
public:
    SphealDefense(float x, float y);
    void CreateBullet(Engine::Point pt) override;
};

#endif /* SphealDefense_hpp */
