#include "scene.h"
#include "cube.h"

Cube::Cube(){
	if(!mesh) mesh = std::make_unique<ppgso::Mesh>("cube.obj");
	if(!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
	if(!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("stars.bmp"));
}

Cube::Cube(const std::string &textureBMP){
	if(!mesh) mesh = std::make_unique<ppgso::Mesh>("cube.obj");
	if(!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
	if(!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(textureBMP));
}

bool Cube::update(Scene &scene, float dt){
	generateModelMatrix();
	if(finishCube)
		if(position.y > 0.5f)
			position.y -= 0.05f;
	return true;
}

void Cube::render(Scene &scene){
	shader->use();

	if(finishCube){
		reflectivity = 5;
		shineDamper = 10;
	}

	setupUniforms(scene);

	shader->setUniform("Transparency", transparency);
	shader->setUniform("ModelMatrix", modelMatrix);
	shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
	shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
	shader->setUniform("Texture", *texture);
	
	mesh->render();
}
