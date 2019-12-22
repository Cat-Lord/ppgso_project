#pragma once

#include <ppgso/ppgso.h>
#include <glm/glm.hpp>
#include <vector>
#include "object.h"
#include "cube.h"
#include "sphere.h"

class Player final : public Object {
	float toCollect = 1;
	float GRAVITY = 0.05f;
	float TURN_SPEED = 2.3f;
	float TILES_LIMIT = 200;
	float currentSpeed = 3.5f;
	float currentTurn = toRads(-90);
	float age = 0.0f;

	glm::vec3 direction;
	float vehicleYaw = 0.0f;
	float maxYaw = 0.5f;
	float yawAmount = 0.1f;
	std::vector<std::unique_ptr<Cube>> tiles = std::vector<std::unique_ptr<Cube>>();
	std::vector<std::unique_ptr<Sphere>> things;
	float widht = 0.5f, length = 1.5f;
	public:
		Player();
		Player(const std::string &textureBMP);
		bool update(Scene &scene, float dt) override;
		void render(Scene &scene) override;
		float lerp(float from, float to, float percent);		// usage ? - animation
		void addTile(Scene &scene);
		void updateTiles(Scene &scene, float dt);
		void drawTiles(Scene &scene);
		bool outOfBounds(Scene &scene);
		void explode(Scene &scene);
};
