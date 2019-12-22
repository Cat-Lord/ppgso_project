#include "scene.h"
#include "axis.h"

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Axis::mesh;
/*
std::unique_ptr<ppgso::Shader> Axis::shader;
std::unique_ptr<ppgso::Texture> Axis::texture;
*/
Axis::Axis(){
	if(!mesh) mesh = std::make_unique<ppgso::Mesh>("cube.obj");
	if(!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
	if(!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("catty.bmp"));

	width = width * scale.x;	// if we scale the cube, we scale the width
}

Axis::Axis(const std::string &textureBMP){
	if(!mesh) mesh = std::make_unique<ppgso::Mesh>("cube.obj");
	if(!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
	if(!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(textureBMP));

	width = width * scale.x;	// if we scale the cube, we scale the width
}

bool Axis::update(Scene &scene, float dt){
	generateModelMatrix();
	return true;
}

void Axis::render(Scene &scene){
	shader->use();

//	shader->setUniform("OverallColor", color);
	
//	shader->setUniform("TextureOffset", textureOffset);
	shader->setUniform("ModelMatrix", modelMatrix);
	shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
	shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
	shader->setUniform("Texture", *texture);
	mesh->render();
}
