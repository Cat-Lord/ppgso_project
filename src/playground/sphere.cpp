#include "scene.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>
#include "sphere.h"

Sphere::Sphere(){
	if(!mesh) mesh = std::make_unique<ppgso::Mesh>("data/sphere.obj");
	if(!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
	if(!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("data/win.bmp"));

	rotation.x = toRads(50);
	rotation.y = toRads(50);
	rotation.z = toRads(50);
	/*rotation.x = glm::linearRand(-0.2f, 0.35f);
	rotation.y = glm::linearRand(-0.2f, 0.35f);
	rotation.z = glm::linearRand(-0.2f, 0.35f);*/
/*	rotation.x = toRads(90);
	rotation.y = toRads(90);
	rotation.z = toRads(90);*/
	shift.x = 1.0f;
	shift.y = 1.0f;
	shift.z = 0.0f;
}

Sphere::Sphere(const std::string &textureBMP){
	if(!mesh) mesh = std::make_unique<ppgso::Mesh>("data/sphere.obj");
	if(!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
	if(!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(textureBMP));
}

bool Sphere::update(Scene &scene, float dt){
	return true;
}

void Sphere::updateModel(glm::mat4 dependantMatrix, float dt){
	generateModelMatrix();

	rotation += 0.1f;
	modelMatrix = dependantMatrix
            * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, 0.0f))
            * glm::orientate4(rotation)
            * glm::translate(glm::mat4(1.0f), glm::vec3(sin(dt), cos(dt), 1.0f))
            * glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.3f, 0.3f));
}

void Sphere::render(Scene &scene){
	shader->use();

	setupUniforms(scene);

	shader->setUniform("ModelMatrix", modelMatrix);
	shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
	shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
	shader->setUniform("Texture", *texture);
	
	mesh->render();
}
