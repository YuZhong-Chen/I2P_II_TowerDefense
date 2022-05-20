#include <cmath>
#include <string>

#include "IceEffect.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "PlayScene.hpp"
#include "Resources.hpp"

PlayScene *IceEffect::getPlayScene() {
	return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}
IceEffect::IceEffect(Engine::Point pt) : Sprite("play/IceFlower.png", pt.x, pt.y), timeTicks(0) {
}
void IceEffect::Update(float deltaTime) {
	timeTicks += deltaTime;
	if (timeTicks >= timeSpan) {
		getPlayScene()->EffectGroup->RemoveObject(objectIterator);
		return;
	}
	Sprite::Update(deltaTime);
}
