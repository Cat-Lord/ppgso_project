#pragma once

#include <ppgso/ppgso.h>
#include <glm/glm.hpp>
#include "object.h"

class Axis final : public Object {
	static std::unique_ptr<ppgso::Mesh> mesh;
	std::unique_ptr<ppgso::Shader> shader;
	std::unique_ptr<ppgso::Texture> texture;
	
	float width = 2.0f;

	public:
		glm::vec3 color{0.1f, 1.0f, 0.1f};
		Axis();
		Axis(const std::string &textureBMP);
		bool update(Scene &scene, float dt) override;
		void render(Scene &scene) override;
};
