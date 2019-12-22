#include <iostream>
#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

#include "menuWindow.h"
#include "menu.h"

void MenuWindow::initWindow(){
	scene.objects.clear();

	// create a camera
	auto camera = std::make_unique<Camera>(110.0f, 1.0f, 0.1f, 700.0f);
	scene.camera = move(camera);
	
	scene.objects.push_back(std::make_unique<Menu>());
}

MenuWindow::MenuWindow() : Window("MenuWindow", MW_SIZE, MW_SIZE) {
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

	initWindow();
	std::cout << "MenuWindow window created\n";
}

void MenuWindow::onIdle() {
	static auto time = (float) glfwGetTime();

    float dt = (float) glfwGetTime() - time;
    time - (float) glfwGetTime();

    glClearColor(0.5f, 0.5f, 0.5f, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene.update(dt);
    scene.render();
}

void MenuWindow::onKey(int key, int scanCode, int action, int mods) {
	if(key == 'S'  &&  action == GLFW_PRESS){
		std::cout << "Start game\n";
		gameStart = true;
	}

	if(key == 'Q' && action == GLFW_PRESS){
		std::cout << "Quit\n";
		exit(0);
		return;
	}
}
