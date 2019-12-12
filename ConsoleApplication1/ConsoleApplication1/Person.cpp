#include "pch.h"
#include <iostream>
#include "Person.h"
#include <sstream>


using namespace std;

Person::Person() {
	name = "undefined";
	age = 0;
}

string Person::toString() {
	stringstream ss;
	ss << "Name is: ";
	ss << name;
	ss << " and Age is: ";
	ss << age;
	ss << "\n";
	return ss.str();
}