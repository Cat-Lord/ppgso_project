#pragma once

#include <ppgso/ppgso.h>
#include <glm/glm.hpp>
#include <vector>

class Camera {
	public:
		float currentLerp = 0.0f;
		// camera position and direction
		glm::vec3 eye{1, 6, -5};
		glm::vec3 finishEyeLoss{4, 10, 3};
		glm::vec3 finishEyeWin{1, 3, -3};
		glm::vec3 target{0, 0, 0};
		glm::vec3 finishTargetWin{0,0,0};
		glm::vec3 up{0, 1, 0};

		// camera manipulation
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;

		glm::vec3 lightPosition[4];
		glm::vec3 lightColor[4];
		Camera(float fov, float ratio, float near, float far);
		
		void update();
		bool zoomOut();
		bool zoomIn();
		glm::vec3 cast(double u, double v);		// get camera position
};
