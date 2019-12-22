#include <glm/gtc/random.hpp>
#include "scene.h"
#include "cube.h"
#include "player.h"
#include "star.h"
#include "explosion.h"

Player::Player(){
	if(!mesh) mesh = std::make_unique<ppgso::Mesh>("data/tron.obj");
	if(!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
	if(!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("corsair.bmp"));
	
	scale = {0.3f, 0.3f, 0.3f};
	rotation.x = toRads(-90);
	rotation.z = toRads(-90);
	for(int i = 0;i < 3; i++){
		auto sphere = std::make_unique<Sphere>();
		sphere->position.x = 0.4f;
		sphere->scale = {1.0f, 1.0f, 1.0f};
		things.push_back(move(sphere));
	}
}

Player::Player(const std::string &textureBMP){
if(!mesh) mesh = std::make_unique<ppgso::Mesh>("data/tron.obj");
	if(!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
	if(!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(textureBMP));
}

bool Player::update(Scene &scene, float dt){
	if(outOfBounds(scene)){
		std::cout << "falling" << std::endl;
		position.y -= GRAVITY;
		if(position.y < -6.0f){
			std::cout << "Ka-BOOM\n";
			explode(scene);
			scene.end = true;
			scene.endSuccess =false;
			return false;
		}
	}
	else{
		float rot = currentTurn * dt;
		if(scene.keys['S'])		// Stop
			currentSpeed = 0;
		
		if(scene.keys['G'])		// Go
			currentSpeed = 3.5f;
		
		if(scene.keys[GLFW_KEY_RIGHT]){
			currentTurn = -TURN_SPEED;
			if(vehicleYaw < maxYaw)
				vehicleYaw += yawAmount;
		}
		else if(scene.keys[GLFW_KEY_LEFT]){
			currentTurn = TURN_SPEED;
			if(vehicleYaw > -maxYaw)
				vehicleYaw -= yawAmount;
		}
		else{
			currentTurn = 0;
			if(vehicleYaw > 0.1f){
				vehicleYaw -= yawAmount;
			}
			else if(vehicleYaw < -0.1f){
				vehicleYaw += yawAmount;
			}
			else
				vehicleYaw = 0;
		}
		increaseRotation({0, currentTurn * dt, 0});
		float dist = currentSpeed * dt;	// current speed ?
		float dx = (float) (dist * std::sin((rotation.y)));
		float dz = (float) (dist * std::cos((rotation.y)));
		
		direction = { dx, 0.0f, dz};
		for(int i = 0; i < (int)tiles.size() - 10; i++){
			auto &obj = tiles[i];
				if(distance(position, obj->position) < (obj->scale.y + scale.y) + 0.1f){
				currentSpeed = 0;
				scene.camera->zoomOut();
				explode(scene);
				scene.end = true;
				scene.endSuccess =false;
				return false;
			}
		}
	
		auto i = std::begin(scene.objects);
		while(i != std::end(scene.objects)){
			auto obj = i->get();
			auto star = dynamic_cast<Star *>(obj);
			if(! star){
				i++;
				continue;
			}

			if(distance(position, obj->position) < 
				(obj->scale.y + scale.y) + 0.8f){
				toCollect--;
				std::cout << "sphere++ (to collect " << toCollect << ")\n";
				if(toCollect <= 0){
					scene.end = true;
					scene.endSuccess = true;
					scene.camera->finishEyeWin = glm::vec3(position.x + 1.0f, position.y + 2.0f, position.z + 1.0f);
					scene.camera->finishTargetWin = position;
				}
				auto sphere = std::make_unique<Sphere>();
				sphere->position.x = 0.4f;
				sphere->scale = {1.0f, 1.0f, 1.0f};

				things.push_back(move(sphere));
				int x = scene.minX + random()%(int)(scene.maxX - scene.minX);
				int z = scene.minZ + random()%(int)(scene.maxZ - scene.minZ);

				// change the star position
				obj->position.x = x;
				obj->position.z = z;
				break;
			}

			i++;
		}

		if(toCollect > 0){
			addTile(scene);
			increasePosition({dx, 0, dz});
		}
	}

	updateTiles(scene, dt);
	generateModelMatrix();
	glm::mat4 rotVehicle = glm::rotate(glm::mat4(1.0f), vehicleYaw, direction);
	modelMatrix =  modelMatrix *rotVehicle ;

	for(auto &obj : things)
		obj->updateModel(modelMatrix, dt);

	return true;
}

void Player::render(Scene &scene){
	shader->use();

	setupUniforms(scene);

	shader->setUniform("ModelMatrix", modelMatrix);
	shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
	shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
	shader->setUniform("Texture", *texture);
	mesh->render();

	drawTiles(scene);
	for(auto &obj : things)
		obj->render(scene);
}

// linear interpolation
float Player::lerp(float from, float to, float percent){
	return (from + (to - from) * percent);
}

// player is now shifted and rotated, we need to add a tile just behind 
// the player withthe same atributes as of now.
void Player::addTile(Scene &scene){
	auto tile = std::make_unique<Cube>("data/rblock.bmp");
	tile->scale = { 0.1f, 0.2f, 0.5f};		// modify the tile parameters
	tile->rotation = { rotation.x, rotation.y + toRads(90), rotation.z };
	tile->position = position;
	tile->position.y += 0.5f;	// lift the tile a bit so it's not in ground
	tiles.push_back(move(tile));

	if(tiles.size() >= TILES_LIMIT)
		tiles.erase(tiles.begin());
}

bool Player::outOfBounds(Scene &scene){
	if(position.x > scene.maxX || position.x < scene.minX-1)
		return true;

	if(position.z > scene.maxZ || position.z < scene.minZ-1)
		return true;

	return false;
}

void Player::updateTiles(Scene &scene, float dt){
	for(int i = 0; i < (int)tiles.size() - 6; i++){
		tiles[i]->update(scene, dt);
	}
	for(int i = tiles.size() - 1; i >= 0  && i > (int)tiles.size() - 7; i--){
		if(tiles[i]->transparency > 0)
			tiles[i]->transparency -= 0.03f;
		else
			tiles[i]->transparency = 0.0f;
	}
}

void Player::drawTiles(Scene &scene){
	for(int i = 0; i < (int)tiles.size() - 6; i++){
		tiles.at(i)->render(scene);
	}
}

void Player::explode(Scene &scene){
	auto explosion = std::make_unique<Explosion>();
	explosion->position = position;
	scene.objects.push_back(move(explosion));
}
