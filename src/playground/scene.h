#pragma once

#include <map>
#include <list>
#include "camera.h"
#include "object.h"

class Object;

class Scene {
	public:
		bool addedCube = false;
		bool finished = false; 		// finished informs about post-game animations status
		bool end = false;
		bool endSuccess = false;
		float minX = -6, maxX = 6;
		float minZ = -6, maxZ = 6;

		std::unique_ptr<Camera> camera;
		std::list< std::unique_ptr<Object> > objects;
		std::map<int, int> keys;

		Scene();
		void update(float dt);
		void render();
};
