#pragma once

#include <ppgso/ppgso.h>
#include <glm/glm.hpp>
#include "object.h"

class Sphere final : public Object {
	public:
		glm::vec3 shift;

		Sphere();
		Sphere(const std::string &textureBMP);
		bool update(Scene &scene, float dt) override;
		void updateModel(glm::mat4 modelMatrix, float dt);
		void render(Scene &scene) override;
};
