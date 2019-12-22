#include "scene.h"
#include "quad.h"

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

Quad::Quad(){
	if(!mesh) mesh = std::make_unique<ppgso::Mesh>("quad.obj");
	if(!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
	if(!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("bricks.bmp"));

	reflectivity = 0.1f;
	shineDamper = 100;
}

Quad::Quad(const std::string &textureBMP){
	if(!mesh) mesh = std::make_unique<ppgso::Mesh>("quad.obj");
	if(!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
	if(!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(textureBMP));
	
	reflectivity = 0.1f;
	shineDamper = 100;
}

bool Quad::update(Scene &scene, float dt){
	glm::mat4 rot = glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0,0,1));
	glm::mat4 tran = glm::translate(glm::mat4(1.0f), -position);
	glm::mat4 tranBack = glm::translate(glm::mat4(1.0f), position);
	generateModelMatrix();
	modelMatrix = tranBack * rot * tran * modelMatrix;
	return true;
}

void Quad::render(Scene &scene){
	shader->use();
	
	setupUniforms(scene);

	shader->setUniform("ModelMatrix", modelMatrix);
	shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
	shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
	shader->setUniform("Texture", *texture);
	mesh->render();
}
