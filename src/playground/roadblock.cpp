#include "scene.h"
#include "roadblock.h"

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

RBlock::RBlock(){
	if(!mesh) mesh = std::make_unique<ppgso::Mesh>("data/roadblock.obj");
	if(!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
	if(!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("bricks.bmp"));
}

RBlock::RBlock(const std::string &textureBMP){
	if(!mesh) mesh = std::make_unique<ppgso::Mesh>("data/roadblock.obj");
	if(!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
	if(!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(textureBMP));
}

bool RBlock::update(Scene &scene, float dt){
	glm::mat4 rot = glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0,0,1));
	glm::mat4 tran = glm::translate(glm::mat4(1.0f), -position);
	glm::mat4 tranBack = glm::translate(glm::mat4(1.0f), position);
	generateModelMatrix();
	modelMatrix = tranBack * rot * tran * modelMatrix;
	return true;
}

void RBlock::render(Scene &scene){
	shader->use();

//	shader->setUniform("OverallColor", color);
	
//	shader->setUniform("TextureOffset", textureOffset);
	shader->setUniform("ModelMatrix", modelMatrix);
	shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
	shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
	shader->setUniform("Texture", *texture);
	mesh->render();
}
