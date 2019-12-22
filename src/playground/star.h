#pragma once

#include <ppgso/ppgso.h>
#include <glm/glm.hpp>
#include "object.h"

class Star final : public Object {
	float animationSpeed = 3;
	float animationValue = 0;
	public:
		Star();
		void updateModelMatrix(glm::vec3 pointPos, glm::mat4 modelMatrix, glm::vec3 dir);
		bool update(Scene &scene, float dt) override;
		void render(Scene &scene) override;
};
