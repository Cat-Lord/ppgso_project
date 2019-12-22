#pragma once

#include <ppgso/ppgso.h>
#include <glm/glm.hpp>
#include "object.h"

class RBlock final : public Object {
	std::unique_ptr<ppgso::Mesh> mesh;
	std::unique_ptr<ppgso::Shader> shader;
	std::unique_ptr<ppgso::Texture> texture;

	float width = 1.0f;	// from central point to its edges
	public:
		glm::vec3 color{0.1f, 1.0f, 0.1f};
		RBlock();
		RBlock(const std::string &textureBMP);
		bool update(Scene &scene, float dt) override;
		void render(Scene &scene) override;
};
