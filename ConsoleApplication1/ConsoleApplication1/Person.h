#pragma once

#ifndef PERSON_H_
#define PERSON_H_

#include <iostream>
using namespace std;

class Person {
private:
	string name;
	int age;
public:
	Person();
	Person(const Person& other) { name = other.name; age = other.age; };
	Person(string personName) { name = personName; age = 0; };
	Person(string personName, int personAge) { name = personName; age = personAge; };
	~Person() { cout << "Person destroyed" << endl; };
	string toString();

};

#endif;