#include <iostream>
#include "camera.h"

Camera::Camera(float fov = 110.0f, float ratio = 1.0f, float near = 0.1f, float far = 700.0f){
	std::cout << "Camera created\n";
	float fovRads = (ppgso::PI / 180.0f) * fov;

	projectionMatrix = glm::perspective(fovRads, ratio, near, far);
	for(int i = 0; i < 4; i++){
		lightPosition[i] = glm::vec3(0.0f, -5.0f, 0.0f);
		lightColor[i] = glm::vec3(0.7f, 0.7f, 0.7f);
	}
}

void Camera::update(){
	viewMatrix = lookAt(eye, target, up);
}

float lerp(float from, float to, float percent){
	return (from + (to - from) * percent);
}

bool Camera::zoomOut(){
	if(currentLerp >= 0.5)
		return true;

	eye.x = lerp(eye.x, finishEyeLoss.x, currentLerp);
	eye.y = lerp(eye.y, finishEyeLoss.y, currentLerp);
	eye.z = lerp(eye.z, finishEyeLoss.z, currentLerp);

	currentLerp += 0.002f;
	return false;
}

bool Camera::zoomIn(){
	if(currentLerp >= 0.5)
		return true;

	eye.x = lerp(eye.x, finishEyeWin.x, currentLerp);
	eye.y = lerp(eye.y, finishEyeWin.y, currentLerp);
	eye.z = lerp(eye.z, finishEyeWin.z, currentLerp);
	target.x = lerp(target.x, finishTargetWin.x, currentLerp);
	target.y = lerp(target.y, finishTargetWin.y, currentLerp);
	target.z = lerp(target.z, finishTargetWin.z, currentLerp);

	currentLerp += 0.002f;
	return false;
}

glm::vec3 Camera::cast(double u, double v){
	
}
