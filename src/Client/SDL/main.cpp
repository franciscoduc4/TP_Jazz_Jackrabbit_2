#include "gamescreen.h"

#include <string>


int main(int argc, char* argv[]) {
 	
 	int jazz = std::stoi(argv[1]);
 	std::string a = "HOLA";
 	
 	GameScreen p(jazz, a);
   	p.run();
    	
    return 0;
}
