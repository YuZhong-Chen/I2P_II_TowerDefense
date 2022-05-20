#ifndef IceEffect_HPP
#define IceEffect_HPP
#include <allegro5/bitmap.h>
#include <memory>
#include <vector>

#include "Sprite.hpp"
#include "Point.hpp"

class PlayScene;

class IceEffect : public Engine::Sprite {
protected:
	PlayScene *getPlayScene();
	float timeTicks = 0.0;
	std::vector<std::shared_ptr<ALLEGRO_BITMAP>> bmps;
	float timeSpan = 2.0;
public:
	IceEffect(Engine::Point pt);
	void Update(float deltaTime) override;
};
#endif // IceEffect_HPP
