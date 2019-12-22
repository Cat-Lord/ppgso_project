#pragma once

#include <ppgso/ppgso.h>
#include "object.h"

class Menu final : public Object {
	private:
		std::unique_ptr<ppgso::Mesh> mesh;
  		std::unique_ptr<ppgso::Shader> shader;
		std::unique_ptr<ppgso::Texture> texture;
	
		glm::vec2 textureOffset;
	public:
		Menu();
        bool update(Scene &scene, float dt) override;
        void render(Scene &scene) override;
};
