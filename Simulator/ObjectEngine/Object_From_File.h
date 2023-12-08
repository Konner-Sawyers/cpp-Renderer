#ifndef Object_From_File_h
#define Object_From_File_h
#define SDL_MAIN_HANDLED //Need this to avoid SDL error. Idk why tho :)
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <SDL.h>
#include <cstring>


class Object_From_File
{
public:
	std::vector<SDL_Vertex> VERTEX_ARRAY;
	std::vector<int> INDICIES_ARRAY;

	Object_From_File(std::string FileName) {
		int vertCount = 0;
		int indCount = 0;

		std::string v = "v ";
		std::string f = "f ";
		std::string vt = "vt ";

		std::string currentLine;

		std::cout << "ATTEMPTING TO OPEN : " << FileName << std::endl;

		std::fstream theFile(FileName);
		if (theFile.is_open()) {
			while (std::getline(theFile, currentLine)) {
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

		const int VERTICIES_COUNT = vertCount;
		const int INDICIES_COUNT = indCount * 3;

		VERTEX_ARRAY.resize(VERTICIES_COUNT);
		INDICIES_ARRAY.resize(INDICIES_COUNT);

		theFile.open(FileName);

		std::vector<std::vector<std::string>> vecLines;
		std::vector<std::string> initVecLines;

		std::vector<std::string> indLines;

		std::vector<std::vector<std::string>> texLines;
		std::vector<std::string> initTexLines;


		if (theFile.is_open()) {
			while (std::getline(theFile, currentLine)) {
				std::stringstream ss(currentLine);
				if (std::strstr(currentLine.c_str(), v.c_str())) {
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

			INDICIES_ARRAY[IND_INDEX] = std::stoi(indLines[i + 1]) - 1;
			IND_INDEX++;
			INDICIES_ARRAY[IND_INDEX] = std::stoi(indLines[i + 3]) - 1;
			IND_INDEX++;
			INDICIES_ARRAY[IND_INDEX] = std::stoi(indLines[i + 5]) - 1;
			IND_INDEX++;

			VERTEX_ARRAY[stoi(indLines[i + 1]) - 1] = SDL_Vertex{
				{std::stof(vecLines[std::stoi(indLines[i + 1]) - 1][1]), std::stof(vecLines[std::stoi(indLines[i + 1]) - 1][2])},
				{255, 255, 255, 255},
				{std::stof(texLines[std::stoi(indLines[i + 2]) - 1][1]), std::stof(texLines[std::stoi(indLines[i + 2]) - 1][2])} };

			VERTEX_ARRAY[stoi(indLines[i + 3]) - 1] = SDL_Vertex{
				{std::stof(vecLines[std::stoi(indLines[i + 3]) - 1][1]), std::stof(vecLines[std::stoi(indLines[i + 3]) - 1][2])},
				{255, 255, 255, 255},
				{std::stof(texLines[std::stoi(indLines[i + 4]) - 1][1]), std::stof(texLines[std::stoi(indLines[i + 4]) - 1][2])} };

			VERTEX_ARRAY[stoi(indLines[i + 5]) - 1] = SDL_Vertex{
				{std::stof(vecLines[std::stoi(indLines[i + 5]) - 1][1]), std::stof(vecLines[std::stoi(indLines[i + 5]) - 1][2])},
				{255, 255, 255, 255},
				{std::stof(texLines[std::stoi(indLines[i + 6]) - 1][1]), std::stof(texLines[std::stoi(indLines[i + 6]) - 1][2])} };
		}

		for (int i = 0; i < VERTEX_ARRAY.size(); i++) {
			std::cout << i << std::endl;
		}
	};

};

#endif
