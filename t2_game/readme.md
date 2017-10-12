#### Know required packages
There is a know list of packages required to build the GLFW library and the game, execute the command that follows to install them.

	sudo apt-get install cmake xorg-dev glee-dev freeglut3-dev libsoil-dev libao-dev

More packages may be need.

#### Installing GLFW
The version of GLFW used in this project was not available in the standard Ubuntu repositories, so it needs to be build from source. In a folder of your preference, execute the following commands:

	wget https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip
	unzip glfw-3.2.1.zip
	cd glfw-3.2.1/
	cmake .
	make
	sudo make install

#### Building the game
In the game root folder (the one with the makefile). Build the game with the following command, it should build without errors.

	make

To play the game, simply run:

	./play.sh 
