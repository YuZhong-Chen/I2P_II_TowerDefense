#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "StrengthenSpell.hpp"
#include "AudioHelper.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp" 
#include "Army.hpp"

//Army(std::string img, float x, float y, float radius, float coolDown, float speed, float hp, int id, float shootRadius);
StrengthenSpell::StrengthenSpell(int x, int y) : Army("play/StrengthenSpell.png", x, y, 20, 1, 0, 0, 4, 95) {
	// Use bounding circle to detect collision is for simplicity, pixel-perfect collision can be implemented quite easily,
	// and efficiently if we use AABB collision detection first, and then pixel-perfect collision.
}

void StrengthenSpell::Update(float deltaTime) {
	if (!isPlace) return;

	timeTicks += deltaTime;
	if (timeTicks >= timeSpan) {
		getPlayScene()->SpellGroup->RemoveObject(objectIterator);
		return;
	}
}

float StrengthenSpell::GetShootRadius() {
	return shootRadius;
}
