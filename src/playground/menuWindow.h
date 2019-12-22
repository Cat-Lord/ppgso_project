#pragma once

#include <ppgso/ppgso.h>
#include "scene.h"

const unsigned int MW_SIZE = 850;	// menu window size

class MenuWindow : public ppgso::Window {
	private:
		Scene scene;
		void initWindow();
	public:
		bool gameStart = false;
		MenuWindow();
		void onIdle() override;
		void onKey(int key, int scanCode, int action, int mods) override;
};
