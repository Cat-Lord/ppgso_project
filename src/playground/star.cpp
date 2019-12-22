#include <math.h>
#include "scene.h"
#include "star.h"

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

Star::Star(){
	if(!mesh) mesh = std::make_unique<ppgso::Mesh>("star/star.obj");
	if(!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
	if(!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("star/star.bmp"));

	reflectivity = 2.4f;
	scale = { 0.2f, 0.4f, 0.2f };
	rotation.y = toRads(-90);
}

bool Star::update(Scene &scene, float dt){
	position.y = 0.3f + 0.5f * (float)sin(animationValue);
	
	if(animationValue > animationSpeed)
		animationValue = 0;
	else
		animationValue += 0.05f;

	generateModelMatrix();
	return true;
}

void Star::updateModelMatrix(glm::vec3 pointPos, glm::mat4 dependantMatrix, glm::vec3 dir){
	rotation.x += 0.3f;//TODO
	glm::mat4 rotx = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 roty = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotz = glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 tran = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 3.0f));
	glm::mat4 scal = glm::scale(dependantMatrix, scale);

	modelMatrix = roty * rotx * rotz * tran * scal * dependantMatrix;
	//modelMatrix = dependantMatrix;
}

void Star::render(Scene &scene){
	shader->use();

   // Set up light
//   shader->setUniform("LightDirection", scene.lightDirection);

   // use camera
   shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
   shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

   // render mesh
   shader->setUniform("ModelMatrix", modelMatrix);
   shader->setUniform("Texture", *texture);
   mesh->render();

}
