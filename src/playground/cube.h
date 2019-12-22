#pragma once

#include <ppgso/ppgso.h>
#include <glm/glm.hpp>
#include "object.h"

class Cube final : public Object {
	public:
		float transparency = 1.0f;
		bool finishCube = false;
		Cube();
		Cube(const std::string &textureBMP);
		bool update(Scene &scene, float dt) override;
		void render(Scene &scene) override;
};
