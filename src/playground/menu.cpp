#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>
#include <iostream>
#include "menu.h"
#include "scene.h"

Menu::Menu(){
	if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
	if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("menu.bmp"));
	if (!mesh) mesh = std::make_unique<ppgso::Mesh>("quad.obj");
}

bool Menu::update(Scene &scene, float dt){

	generateModelMatrix();
	return true;
}

void Menu::render(Scene &scene){
	glDepthMask(GL_FALSE);

    shader->use();
     // Set up light
//     shader->setUniform("LightDirection", scene.lightDirection);

     // use camera
	 shader->setUniform("TextureOffset", textureOffset);
     shader->setUniform("ModelMatrix", modelMatrix);
     shader->setUniform("ProjectionMatrix", glm::mat4(1.0f));
     shader->setUniform("ViewMatrix", glm::mat4(1.0f));

     // render mesh
     shader->setUniform("Texture", *texture);
     mesh->render();
	
	glDepthMask(GL_TRUE);
}
