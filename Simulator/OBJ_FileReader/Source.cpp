#define SDL_MAIN_HANDLED //Need this to avoid SDL error. Idk why tho :)
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <SDL.h>
#include <cstring>

int main() {


	int vertCount = 0;
	int indCount = 0;

	std::string v = "v ";
	std::string f = "f ";
	std::string vt = "vt ";
	
	std::string currentLine;
	std::fstream theFile("untitled.obj");
	if (theFile.is_open()) {
		while (std::getline(theFile, currentLine)) {
			//std::cout << currentLine << '\n';
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

	//std::cout << "VERT: " << vertCount << std::endl;
	//std::cout << "IND: " << indCount << std::endl;

	const int VERTICIES_COUNT = vertCount;
	const int INDICIES_COUNT = indCount * 3;

	SDL_Vertex *VERTEX_ARRAY = new SDL_Vertex[VERTICIES_COUNT];
	int *INDICIES_ARRAY =  new int[INDICIES_COUNT];
	
	theFile.open("untitled.obj");

	std::vector<std::vector<std::string>> vecLines;
	std::vector<std::string> initVecLines;

	std::vector<std::string> indLines;

	std::vector<std::vector<std::string>> texLines;
	std::vector<std::string> initTexLines;
	

	if (theFile.is_open()) {
		while (std::getline(theFile, currentLine)) {
			std::stringstream ss(currentLine);
			if (std::strstr(currentLine.c_str(),v.c_str())) {
				//std::cout << "VERTEX: " << currentLine << std::endl;
				
				while (std::getline(ss, currentLine, ' ')) {
					initVecLines.push_back(currentLine);
					//std::cout << "HERE";
				}
				vecLines.push_back(initVecLines);
				initVecLines.pop_back();
				initVecLines.pop_back();
				initVecLines.pop_back();
				initVecLines.pop_back();

			}
			else if (std::strstr(currentLine.c_str(), f.c_str())) {
				//std::cout << "INDICIES: " << currentLine << std::endl;
				while (std::getline(ss, currentLine, '/')) {
					std::stringstream sss(currentLine);
					while (std::getline(sss, currentLine, ' ')) {
						indLines.push_back(currentLine);
					}
					

				}
			}

			else if (std::strstr(currentLine.c_str(), vt.c_str())) {
				//std::cout << "TEXTURE: " << currentLine << std::endl;
				while (std::getline(ss, currentLine, ' ')) {
					initTexLines.push_back(currentLine);
				}
				texLines.push_back(initTexLines);
				initTexLines.pop_back();
				initTexLines.pop_back();
				initTexLines.pop_back();
			}
		}
		theFile.close();
	}

	int IND_INDEX = 0;

	for (int i = 0; i < vecLines.size(); i++) { 
		for (int j = 0; j < vecLines[i].size(); j++) {
			//std::cout << vecLines[i][j] << " ";
		}
		//std::cout << " END LINE " << std::endl;
	}

	for (int i = 0; i < texLines.size(); i++) {
		for (int j = 0; j < texLines[i].size(); j++) {
			//std::cout << texLines[i][j] << " ";
		}
		//std::cout << " END LINE " << std::endl;
	}

	for (int i = 0; i < indLines.size(); i += 7) {



		/*
		std::cout << indLines[i] << std::endl;
		std::cout << "VERT INDEX: " << indLines[i + 1] << "TEX INDEX" << indLines[i + 2] << std::endl;
		std::cout << "VERT INDEX: " << indLines[i + 3] << "TEX INDEX" << indLines[i + 4] << std::endl;
		std::cout << "VERT INDEX: " << indLines[i + 5] << "TEX INDEX" << indLines[i + 6] << std::endl;

		std::cout << "Vertex at index " << (std::stoi(indLines[i + 1]) - 1) << " /// " << vecLines[std::stoi(indLines[i + 1]) - 1][1] << " : " << vecLines[std::stoi(indLines[i + 1]) - 1][2] << std::endl;
		std::cout << "Tex at index " << (std::stoi(indLines[i + 2]) - 1) << " /// " << texLines[std::stoi(indLines[i + 2]) - 1][1] << " : " << texLines[std::stoi(indLines[i + 2]) - 1][2] << std::endl;
		*/



		INDICIES_ARRAY[IND_INDEX] = std::stoi(indLines[i + 1]) - 1;
		IND_INDEX++;
		INDICIES_ARRAY[IND_INDEX] = std::stoi(indLines[i + 3]) - 1;
		IND_INDEX++;
		INDICIES_ARRAY[IND_INDEX] = std::stoi(indLines[i + 5]) - 1;
		IND_INDEX++;

		VERTEX_ARRAY[stoi(indLines[i + 1])-1] = SDL_Vertex{
			{std::stof(vecLines[std::stoi(indLines[i + 1]) - 1][1]), std::stof(vecLines[std::stoi(indLines[i + 1]) - 1][2])},
			{255, 255, 255, 255}, 
			{std::stof(texLines[std::stoi(indLines[i + 2]) - 1][1]), std::stof(texLines[std::stoi(indLines[i + 2]) - 1][2])} };

		VERTEX_ARRAY[stoi(indLines[i + 3])-1] = SDL_Vertex{
			{std::stof(vecLines[std::stoi(indLines[i + 3]) - 1][1]), std::stof(vecLines[std::stoi(indLines[i + 3]) - 1][2])},
			{255, 255, 255, 255},
			{std::stof(texLines[std::stoi(indLines[i + 4]) - 1][1]), std::stof(texLines[std::stoi(indLines[i + 4]) - 1][2])} };

		VERTEX_ARRAY[stoi(indLines[i + 5])-1] = SDL_Vertex{
			{std::stof(vecLines[std::stoi(indLines[i + 5]) - 1][1]), std::stof(vecLines[std::stoi(indLines[i + 5]) - 1][2])},
			{255, 255, 255, 255},
			{std::stof(texLines[std::stoi(indLines[i + 6]) - 1][1]), std::stof(texLines[std::stoi(indLines[i + 6]) - 1][2])} };
	}


	/*
	for (int i = 0; i < VERTICIES_COUNT; i++) {
		std::cout << "INDEX " << i << " " << VERTEX_ARRAY[i].position.x << " : " << VERTEX_ARRAY[i].position.y << std::endl;
	}

	std::cout << "INDICIES :";
	for (int i = 0; i < INDICIES_COUNT; i++) {
		std::cout << INDICIES_ARRAY[i] << " ";
	}
	*/
	return 0;
}


/*
TODO
Delim the currentLine and feed the imputs into arrays
*/