#include <iostream>
#include <time.h>
#include "mwindow.h"
#include "menuWindow.h"

int main(){
	srand(time(NULL));
	while(true){
		MenuWindow menu;
		while(menu.pollEvents()) {
		  	if(menu.gameStart){
				menu.close();
				MWindow window;
				window.initMWindow();
			  	while(window.pollEvents()) {
					// game loop
  				}
				window.close();
			}
	 	}
	}
	return EXIT_SUCCESS;
}
