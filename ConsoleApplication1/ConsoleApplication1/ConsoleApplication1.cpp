#include "pch.h"
#include "Header.h";
#include "Person.h";
#include "Inheritance.h";
#include "FireParticle.h";
#include "SDL.h";
#include "Particle.h";
#include "Swarm.h";
#include <math.h>;
#include <iomanip>;
#include <algorithm>;
#include <iostream>;
#include <string>;
#include <stdlib.h>;
using namespace std;

void sum() {
	int sum = 0;
	int a = 9;
	int b = a++;
	int * c = &a;
	//a = 10, b = 9, c = 10
	cout << "First: " << endl << a << endl << b << endl << *c << endl;
	a++;
	//a = 11, b = 9, c = 11
	cout << "Second: " << endl << a << endl << b << endl << *c << endl;
}

void arrays() {
	int arrayA[10];
	for (int i = 0; i < 10; i++) {
		arrayA[i] = i;
		cout << arrayA[i];
	}
	cout << endl;
	int arrayB[10];
	copy(begin(arrayA), end(arrayA), begin(arrayB));
	arrayB[0] = 10;
	cout << "A" << "\n";
	for (int i = 0; i < 10; i++) {		
		cout << arrayA[i];
	}
	cout << endl;
	cout << "B" << "\n";
	for (int i = 0; i < 10; i++) {		
		cout << arrayB[i];
	}
}

void readKeyboard() {
	cout << "Enter your name: " << flush;
	string input;
	getline(cin, input);
	cout << "Your name is: " << input << endl;
}

void askForPassword() {
	string password = "123Secure";
	string input;
	bool notFirstTry = false;
	do {
		if (!notFirstTry) {
			cout << "Enter your password: " << flush;
			getline(cin, input);
			notFirstTry = true;
		}
		else {
			cout << "That's not your password" << endl;
			cout << "Try Again" << endl;
			cout << "Enter your password: " << flush;
			getline(cin, input);
		}
	} while (input != password);
	cout << "That's your password" << endl;
}

void modifyDValue(int *dValue) {
	cout << "2.- Value in modify " << *dValue << endl;
	*dValue = 40;
	cout << "3.- Value after modify " << *dValue << endl;
}

void pointer() {
	int dValue = 90;
	int *dValuePointer = &dValue;
	cout << dValue << endl;
	cout << &dValue << endl;
	cout << dValuePointer << endl;
	cout << *dValuePointer << endl;
	cout << &dValuePointer << endl;
	cout << "1.- Original Value: " << dValue << endl;
	modifyDValue(dValuePointer);
	cout << "4.- Final Value " << dValue;
}

void vectors() {

}

void person() {
	Person firstUser;
	Person secondUser("Pedro");
	Person thirdUser("Almudena", 58);
	Person fourthUser = secondUser;
	cout << firstUser.toString();
	cout << secondUser.toString();
	cout << thirdUser.toString();
	cout << fourthUser.toString();
}

void animals() {
	Animal cat(5, "Cat", "MrTickles");
	Mammal dog(10, "Dog", "LoyalFriend", "OldDogLogan");

	cat.sound();
	cout << endl;
	cout << dog.sound();
}

int sdl() {

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		cout << "SDL failed";
		return 1;
	}
	cout << "SDL succeeded";

	SDL_Window * sdlWindow = SDL_CreateWindow("Particle Explosion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (sdlWindow == NULL) {
		SDL_Quit();
		return 2;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture *texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

	if (renderer == NULL) {
		SDL_DestroyTexture(texture);
		SDL_DestroyWindow(sdlWindow);
		SDL_Quit();
		return 3;
	}

	if (texture == NULL) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(sdlWindow);
		SDL_Quit();
		return 4;
	}

	Uint32 * buffer = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];

	memset(buffer, 255, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		buffer[i] = 0xFFFFFFFF;
	}

	SDL_UpdateTexture(texture, NULL, buffer, SCREEN_WIDTH*sizeof(Uint32));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);

	bool quit = false;

	SDL_Event event;

	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

	delete[] buffer;
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();

}

void fireParticles() {
	FireParticle screen;
	
	if (!screen.init()) {
		cout << "Error initialising SDL" << endl;
	}


	while (true) {
		int elapsed = SDL_GetTicks();
		unsigned char green = (1 + sin(elapsed * 0.001)) * 128;

		for (int y = 0; y < FireParticle::SCREEN_HEIGHT; y++) {
			for (int x = 0; x < FireParticle::SCREEN_WIDTH; x++) {
				screen.setPixel(x,y,0,green,0);
			}
		}



		screen.update();

		if (!screen.processEvent()) {
			break;
		}
	}

}

void getSwarm() {

	FireParticle screen;
	Swarm swarm;

	if (!screen.init()) {
		cout << "Error initialising SDL" << endl;
	}
	while (true) {
		int elapsed = SDL_GetTicks();
		//screen.clear();
		swarm.update(elapsed);
		unsigned char red = (unsigned char) ((1 + sin(elapsed * 0.002)) * 128);
		unsigned char green = (unsigned char)((1 + sin(elapsed * 0.001)) * 128);
		unsigned char blue = (unsigned char) ((1 + sin(elapsed * 0.003)) * 128);
		const Particle * const pParticles = swarm.getParticles();

		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle p = pParticles[i];

			int x = (p.sdl_x + 1) * FireParticle::SCREEN_WIDTH / 2;
			int y = (p.sdl_y + 1) * FireParticle::SCREEN_HEIGHT / 2;
			screen.setPixel(x,y,red,green,blue);
		}

		screen.boxBlur();

		screen.update();

		if (!screen.processEvent()) {
			break;
		}
	}

}

void shiftingColors() {
	unsigned char alpha = 0xFF;
	unsigned char red = 0x12;
	unsigned char green = 0x34;
	unsigned char blue = 0x56;

	unsigned int color = 0;

	color += alpha;
	color = color << 8;
	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;

	cout << setfill('0') << setw(8) << hex << color << endl;

}

static bool exists(int ints[], int size, int k)
{
	cout << ints;
	return 0;
}

int	main(int argc, char *argv[]) {
	//sum();
	//arrays();
	//readKeyboard();
	//askForPassword();
	//lists();
	//person();
	//pointer();
	//animals();
	//sdl();
	//fireParticles();
	//shiftingColors();
	srand(time(NULL));
	getSwarm();
	return 0;
}


void lists() {
	cout << "Hello World";
}