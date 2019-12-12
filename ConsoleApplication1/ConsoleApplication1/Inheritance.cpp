#include "pch.h"
#include "Inheritance.h"
#include <iostream>
#include <sstream>

using namespace std;

string Mammal::sound() {
	Animal::sound();
	stringstream ss;
	ss << ", and my name is " << name;
	return ss.str();
}
