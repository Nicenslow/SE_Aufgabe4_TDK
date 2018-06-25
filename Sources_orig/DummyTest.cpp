//
// Created by Jan-Niklas Jacobson on 21.06.18.
//

#include <fstream>
#include <cstdio>
#include <iostream>
#include <vector>
#include <sstream>

#include "DummyTest.h"

/**
* Constructor
*/
DummyTest::DummyTest(/*FestoProcessImage* processImage, Plugin* plugin =0*/) {
}

/**
* Destructor
*/
DummyTest::~DummyTest() = default;

void DummyTest::eval() {
}

void DummyTest::evalStates() {
}

void DummyTest::testPlugin() {
	char* log = const_cast<char *>("C:\\Users\\user\\CLionProjects\\sep34\\Logs\\processlog1.txt");
	testLog(log);

}

void split(const std::string &s, char delim, std::vector<int> &elems) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(stoi(item));
	}
}

std::vector<int> split(const std::string &s, char delim) {
	std::vector<int> elems;
	split(s, delim, elems);
	return elems;
}

void DummyTest::testLog(char* fileName) {

	std::string line;
	std::ifstream infile;
	infile.open(fileName);

	while (getline(infile, line)) {
		std::vector<int> parts = split(line, ';');

		cout << "Höhe: " << parts.at(2) << endl;
		if (parts.empty()) {
			continue;
		}

		//TODO: FSM STUFF HERE

	}

}

bool isDriveRight() {
	return true; // FIXME!
}