#include "scene.h"
#include "lamppost.h"

LampPost::LampPost(){
	if(!mesh) mesh = std::make_unique<ppgso::Mesh>("data/lamp_post/lamp_post.obj");
	if(!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
	if(!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("data/lamp_post.bmp"));

}

LampPost::LampPost(const std::string &textureBMP){
	if(!mesh) mesh = std::make_unique<ppgso::Mesh>("data/lamp_post/lamp_post.obj");
	if(!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
	if(!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(textureBMP));
}

bool LampPost::update(Scene &scene, float dt){
	generateModelMatrix();
	return true;
}

void LampPost::render(Scene &scene){
	shader->use();

	setupUniforms(scene);

	shader->setUniform("ModelMatrix", modelMatrix);
	shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
	shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
	shader->setUniform("Texture", *texture);
	
	mesh->render();
}
