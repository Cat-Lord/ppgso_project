#include <iostream>
#include "scene.h"
#include "cube.h"

Scene::Scene(){
	std::cout << "Scene created\n";
}

void Scene::update(float dt){
	if(end){
//		objects.clear();
		if(endSuccess == false){
			if(! addedCube){
				auto cube = std::make_unique<Cube>("data/loss.bmp");
				cube->scale = glm::vec3(3.0f, 3.0f, 3.0f);
				cube->position = glm::vec3(0.0f, 15.5f, 0.0f);
				cube->finishCube = true;
				objects.push_back(move(cube));
				addedCube = true;
			}

			// player lost
			if(camera->eye != camera->finishEyeLoss)
				if(camera->zoomOut() == true)
					finished = true;
		}
		else{
			// player has won
			if(! addedCube){
				auto cube = std::make_unique<Cube>("data/win.bmp");
				cube->scale = glm::vec3(1.0f, 1.0f, 1.0f);
				cube->position = glm::vec3(camera->finishTargetWin);
				cube->position.y = 8.0f;
				cube->finishCube = true;
				objects.push_back(move(cube));
				addedCube = true;
			}
				
			if(camera->eye != camera->finishEyeWin)
				if(camera->zoomIn() == true)
					finished = true;
		}
	}

	camera->update();

	auto i = std::begin(objects);

	while(i != std::end(objects)){
		auto obj = i->get();
		if( ! obj->update(*this, dt) )
			i = objects.erase(i);
		else
			i++;
	}
}

void Scene::render(){
	for( auto &obj : objects)
		obj->render(*this);
}
