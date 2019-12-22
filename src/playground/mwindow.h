#pragma once

#include <ppgso/ppgso.h>
#include "scene.h"

const unsigned int SIZE = 800;

class MWindow : public ppgso::Window {
	private:
		Scene scene;

	public:
		void initMWindow();
		MWindow();
		void onIdle() override;
		void onKey(int key, int scanCode, int action, int mods) override;
};
