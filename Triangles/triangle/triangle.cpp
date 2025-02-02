#include "pch.h"
#include <iostream>
#include <string>

const int PARAMETERS_NUMBER = 4;
const std::string MESSAGE_UNKNOWN_ERROR = "Unknown error";
const std::string MESSAGE_NOT_TRIANGLE = "This is not a triangle";
const std::string MESSAGE_USUAL_TRIANGLE = "This is a usual triangle";
const std::string MESSAGE_ISOSCELES_TRIANGLE = "This is a isosceles triangle";
const std::string MESSAGE_EQUILATERAL_TRIANGLE = "This is a equilateral triangle";

bool AreParametersPositiveNumbers(char** argv, double &a, double &b, double &c) {
	try 
	{
		a = std::stod(argv[1]);
		b = std::stod(argv[2]);
		c = std::stod(argv[3]);
	}
	catch (...) 
	{
		return false;
	}
	if (a > 0 && b > 0 && c > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsParametersNumberCorrect(int argc) {
	return argc == PARAMETERS_NUMBER;
}

bool DoesTriangleExist(double a, double b, double c) {
	return (a < b + c) && (b < a + c) && (c < a + b);
}

bool IsTriangleEquilateral(double a, double b, double c) {
	return a == b && b == c;
}

bool IsTriangleIsosceles(double a, double b, double c) {
	return (a != b && (b == c || c == a)) || (a == b && a != c);
}

std::string GetTriangleMessage(double a, double b, double c) {
	if (DoesTriangleExist(a, b, c)) {
		if (IsTriangleEquilateral(a, b, c)) {
			return MESSAGE_EQUILATERAL_TRIANGLE;
		}
		else if (IsTriangleIsosceles(a, b, c)) {
			return MESSAGE_ISOSCELES_TRIANGLE;
		}
		else {
			return MESSAGE_USUAL_TRIANGLE;
		}
	}
	else {
		return MESSAGE_NOT_TRIANGLE;
	}
}

int main(int argc, char** argv)
{
	double a = 0, b = 0, c = 0;

	if (!IsParametersNumberCorrect(argc) || !AreParametersPositiveNumbers(argv, a, b, c)) {
		std::cout << MESSAGE_UNKNOWN_ERROR;
		return 1;
	}

	std::cout << GetTriangleMessage(a, b, c);

	return 0;
}
