#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

#include <ppgso/ppgso.h>
#include "object.h"

float Object::toRads(float angle){
    return (ppgso::PI/180.0f) * angle;
}

float Object::toAngle(float rads){
    return (rads * 180.0f)/ppgso::PI;
}

void Object::increasePosition(glm::vec3 increase){
	position += increase;
}

void Object::increaseRotation(glm::vec3 increase){
	rotation += increase;
}

void Object::increaseScale(glm::vec3 increase){
	scale += increase;
}

void Object::setupUniforms(Scene &scene){
	for(int i = 0; i < 4; i++){
		std::string currentPosition = "lightPosition[" + std::to_string(i);
		currentPosition += "]";
		std::string currentColor = "lightColor[" + std::to_string(i);
		currentColor += "]";
			
		shader->setUniform(currentPosition.c_str(), scene.camera->lightPosition[i]);
		shader->setUniform(currentColor.c_str(), scene.camera->lightColor[i]);
	}
	shader->setUniform("reflectivity", reflectivity);
	shader->setUniform("shineDamper", shineDamper);
}

void Object::generateModelMatrix() {
  modelMatrix =
          glm::translate(glm::mat4(1.0f), position)
          * glm::orientate4(rotation)
          * glm::scale(glm::mat4(1.0f), scale);
}
