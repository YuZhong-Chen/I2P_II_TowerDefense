#ifndef WobbuffetArmy_hpp
#define WobbuffetArmy_hpp

#include "Army.hpp"

class WobbuffetArmy : public Army {
public:
    WobbuffetArmy(int x, int y);
    void CreateBullet(Engine::Point pt) {}
};

#endif /* WobbuffetArmy_hpp */
