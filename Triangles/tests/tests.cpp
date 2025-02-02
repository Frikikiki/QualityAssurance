#include "pch.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <fstream>
#include <stdexcept>
#include <string>
#include <array>

const std::string TRIANGLE_WAY = "V:\\Code\\SoftwareQuality\\Triangles\\triangle\\Debug\\triangle.exe";


std::string exec(std::string str) {
	const char* cmd = str.c_str();
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	return result;
}


void RunTests(std::ifstream &inputFile)
{
	std::ofstream outputFile("tests_results.txt");
	std::string parameters;
	std::string expectedOutput;
	std::string output;
	while (!inputFile.eof())
	{
		std::getline(inputFile, parameters);
		std::getline(inputFile, expectedOutput);
		output = exec(TRIANGLE_WAY + " " + parameters);
		if (expectedOutput == output)
		{
			outputFile << "SUCCSESS.\n";
			outputFile << "Parametres: " << parameters << std::endl;
			outputFile << "Output: " << output << std::endl;
			outputFile << std::endl;
		}
		else
		{
			outputFile << "FAILED.\n";
			outputFile << "Parameters: " << parameters << std::endl;
			outputFile << "Expected output: " << expectedOutput << std::endl;
			outputFile << "Output: " << output << std::endl;
			outputFile << std::endl;
		}
	}
}



int main()
{
	std::ifstream inputFile("tests_cases.txt");
	RunTests(inputFile);
}
