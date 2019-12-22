#include <iostream>
#include "mwindow.h"
#include "cube.h"
#include "player.h"
#include "lamppost.h"
#include "star.h"
#include "quad.h"

void MWindow::initMWindow(){
	scene.objects.clear();

	auto player = std::make_unique<Player>();
	player->position = glm::vec3(0,0,0);
	scene.objects.push_back(move(player));

	// create a camera
	auto camera = std::make_unique<Camera>(110.0f, 1.0f, 0.1f, 700.0f);
	camera->lightPosition[0] = glm::vec3(scene.minX, 1.8f, scene.minZ);
	camera->lightColor[0] = glm::vec3(0.1f, 1.0f, 0.1f);

	camera->lightPosition[1] = glm::vec3(scene.maxX, 1.8f, scene.minZ);
	camera->lightColor[1] = glm::vec3(1.0f, 1.0f, 1.0f);

	camera->lightPosition[2] = glm::vec3(scene.minX, 1.8f, scene.maxZ);
	camera->lightColor[2] = glm::vec3(0.1f, 0.1f, 1.0f);

	camera->lightPosition[3] = glm::vec3(scene.maxX, 1.8f, scene.maxZ);
	camera->lightColor[3] = glm::vec3(1.0f, 0.1f, 0.1f);

	scene.camera = move(camera);
	
	float scaleMin = 0.08f;
	float scaleMax = 18.0f;

	auto lamp1 = std::make_unique<LampPost>();
	lamp1->scale = {0.1f, 0.1f, 0.1f};
	lamp1->position = { scene.minX, 0.0f, scene.minZ };
	scene.objects.push_back(move(lamp1));

	auto lamp2 = std::make_unique<LampPost>();
	lamp2->scale = {0.1f, 0.1f, 0.1f};
	lamp2->position = { scene.maxX, 0.0f, scene.minZ };
	scene.objects.push_back(move(lamp2));

	auto lamp3 = std::make_unique<LampPost>();
	lamp3->scale = {0.1f, 0.1f, 0.1f};
	lamp3->position = { scene.minX, 0.0f, scene.maxZ };
	scene.objects.push_back(move(lamp3));

	auto lamp4 = std::make_unique<LampPost>();
	lamp4->scale = {0.1f, 0.1f, 0.1f};
	lamp4->position = { scene.maxX, 0.0f, scene.maxZ };
	scene.objects.push_back(move(lamp4));

	// GROUND
	for(int i = scene.minX; i <= scene.maxX; i++){
		for(int j = scene.minZ; j <= scene.maxZ; j++){
			std::unique_ptr<Quad> ground;
			if(i == scene.minX  ||  i == scene.maxX  ||  j == scene.minZ  || j ==scene.maxZ){
				ground = std::make_unique<Quad>("data/edgegrid.bmp");	
			}
			else{
				ground = std::make_unique<Quad>("data/grid.bmp");
			}

			ground->reflectivity = 5;
			ground->shineDamper = 10;
			ground->scale = { 0.5f, 0.5f, 0.5f};
			ground->rotation.z = ground->toRads(-90);
			ground->position.x = (float) i;		// times two, because we are centered
			ground->position.z = (float) j;
			scene.objects.push_back(move(ground));	
		}
	}

	int x = scene.minX + random()%(int)(scene.maxX - scene.minX);
	int z = scene.minZ + random()%(int)(scene.maxZ - scene.minZ);
	auto star = std::make_unique<Star>();
	star->position = glm::vec3(x, 0.5f, z);
	star->scale = glm::vec3(0.05f, 0.15f, 0.05f);
	scene.objects.push_back(move(star));
}

MWindow::MWindow() : Window("Main window", SIZE, SIZE) {
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	glClearColor(0.5f, 0.5f, 0.5f, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::cout << "MWindow created\n";
}

void MWindow::onIdle() {
	static auto time = (float) glfwGetTime();

	float dt = (float) glfwGetTime() - time;
	time = (float) glfwGetTime();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(scene.finished){
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		return;
	}
	scene.update(dt);
	scene.render();
}

void MWindow::onKey(int key, int scanCode, int action, int mods) {
	scene.keys[key] = action;

    if(scene.keys['U'] != GLFW_RELEASE){
        scene.camera->eye.x = scene.camera->eye.x + 1;
        std::cout << "eye.x++ " << std::endl;
	std::cout << scene.camera->eye.x << ", " 
			  << scene.camera->eye.y << ", "
			  << scene.camera->eye.z << std::endl << std::endl;
    }
    if(scene.keys['Y'] != GLFW_RELEASE){
        scene.camera->eye.x = scene.camera->eye.x - 1;
        std::cout << "eye.x-- " << std::endl;
	std::cout << scene.camera->eye.x << ", " 
			  << scene.camera->eye.y << ", "
			  << scene.camera->eye.z << std::endl << std::endl;
    }

    if(scene.keys['J'] != GLFW_RELEASE){
        scene.camera->eye.y = scene.camera->eye.y + 1;
        std::cout << "eye.y++ " << std::endl;
	std::cout << scene.camera->eye.x << ", " 
			  << scene.camera->eye.y << ", "
			  << scene.camera->eye.z << std::endl << std::endl;
    }
    if(scene.keys['H'] != GLFW_RELEASE){
        scene.camera->eye.y = scene.camera->eye.y - 1;
        std::cout << "eye.y--" << std::endl;
	std::cout << scene.camera->eye.x << ", " 
			  << scene.camera->eye.y << ", "
			  << scene.camera->eye.z << std::endl << std::endl;
    }

    if(scene.keys['M'] != GLFW_RELEASE){
        scene.camera->eye.z = scene.camera->eye.z + 1;
        std::cout << "eye.z++ " << std::endl;
	std::cout << scene.camera->eye.x << ", " 
			  << scene.camera->eye.y << ", "
			  << scene.camera->eye.z << std::endl << std::endl;
    }
    if(scene.keys['N'] != GLFW_RELEASE){
        scene.camera->eye.z = scene.camera->eye.z - 1;
        std::cout << "eye.z-- " << std::endl;
	std::cout << scene.camera->eye.x << ", " 
			  << scene.camera->eye.y << ", "
			  << scene.camera->eye.z << std::endl << std::endl;
    }
}

/*
	std::cout << "X: stars, Y: bricks, Z: catty" << std::endl;
	auto xaxis = std::make_unique<Axis>("stars.bmp");
	xaxis->scale = {scaleMax, scaleMin, scaleMin};

	auto yaxis = std::make_unique<Axis>("bricks.bmp");
	yaxis->scale = {scaleMin, scaleMax, scaleMin};

	auto zaxis = std::make_unique<Axis>();
	zaxis->scale = {scaleMin, scaleMin, scaleMax};

	scene.objects.push_back(move(xaxis));
	scene.objects.push_back(move(yaxis));
	scene.objects.push_back(move(zaxis));
*/
