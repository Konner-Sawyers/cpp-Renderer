#define SDL_MAIN_HANDLED //Need this to avoid SDL error. Idk why tho :)
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <SDL.h>

int main() {


	int vertCount = 0;
	int indCount = 0;

	std::string v = "v ";
	std::string f = "f ";
	
	std::string currentLine;
	std::fstream theFile("test_object.obj");
	if (theFile.is_open()) {
		while (std::getline(theFile, currentLine)) {
			std::cout << currentLine << '\n';
			std::stringstream ss(currentLine);
			while (std::getline(ss, currentLine, ' ')) {
				if (currentLine == "v") {
					vertCount += 1;
				}
				else if (currentLine == "f") {
					indCount += 1;
				}
			}
		}
		theFile.close();
		theFile.clear();
	}


	else std::cout << "File not opened";

	std::cout << "VERT: " << vertCount << std::endl;
	std::cout << "IND: " << indCount << std::endl;

	const int VERTICIES_COUNT = vertCount;
	const int INDICIES_COUNT = indCount;



	std::cout << "SECOND RUN" << std::endl;

	SDL_Vertex *VERTEX_ARRAY = new SDL_Vertex[VERTICIES_COUNT];
	int *INDICIES_ARRAY =  new int[INDICIES_COUNT];
	
	theFile.open("test_object.obj");

	std::vector<std::string> lineVec;

	if (theFile.is_open()) {
		while (std::getline(theFile, currentLine)) {
			std::stringstream ss(currentLine);
			while (std::getline(ss, currentLine, ' ')) {
				lineVec.push_back(currentLine);
			}
		}
		theFile.close();
	}

	

	else std::cout << "FAILED TO OPEN FILE";


	int vertIndex = 0;
	int indIndex = 0;

	for (int i = 0; i < lineVec.size(); i++) {
		std::cout << "What im checking : " << lineVec[i] << std:: endl;
		//std::cout << lineVec[i] << std::endl;
		if (lineVec[i] == "v") {
			VERTEX_ARRAY[vertIndex] = SDL_Vertex{ {std::stof(lineVec[i + 1]), std::stof(lineVec[i + 2])},{255, 255, 255, 255}, {0,0} };
			vertIndex += 1;
		}

		if (lineVec[i] == "f") {
			INDICIES_ARRAY[indIndex + 0] = std::stoi(lineVec[i + 1]);
			INDICIES_ARRAY[indIndex + 1] = std::stoi(lineVec[i + 2]);
			INDICIES_ARRAY[indIndex + 2] = std::stoi(lineVec[i + 3]);
		}
	}
	for (int i = 0; i < VERTICIES_COUNT; i++) {
		std::cout << "RUN " << i << ": " << VERTEX_ARRAY[i].position.x << " : " << VERTEX_ARRAY[i].position.y << std::endl;
	}

	for (int i = 0; i < INDICIES_COUNT*3; i++) {
		std::cout << INDICIES_ARRAY[i] << " ";
	}

	return 0;
}


/*
TODO

Delim the currentLine and feed the imputs into arrays
*/