#pragma once

#ifndef INHERITANCE_H_
#define INHERITANCE_H_

#include <iostream>
using namespace std;

class Animal {
private:
	int age;
	string commonName;
	string cientficName;
public:
	Animal() {};
	Animal(int animalAge, string animalCommonName, string animalCientificName) : age(animalAge), commonName(animalCommonName), cientficName(animalCientificName) {};
	void sound() { cout << "I'm an Animal" << ", My age is " << age; };
};

class Mammal :public Animal {
private:
	string name;
public:
	Mammal() {};
	Mammal(int animalAge, string animalCommonName, string animalCientificName, string animalName) : Animal(animalAge, animalCommonName, animalCientificName), name(animalName){};
	string sound();
};

#endif;