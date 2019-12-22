#pragma once

#include <ppgso/ppgso.h>
#include <glm/glm.hpp>
#include "object.h"

// Position of light is at 1.8f offset from center (y direction)
class LampPost final : public Object {
	public:
		LampPost();
		LampPost(const std::string &textureBMP);
		bool update(Scene &scene, float dt) override;
		void render(Scene &scene) override;
};
