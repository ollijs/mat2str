#include "mat2str.h"


#include "mat2str-cout.h"

#include <iostream>


int main()
{
	// Some dependency free "matrices"
	std::vector<std::vector<int>> intMat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	std::vector<std::vector<float>> floatMat = {{1.f, 2.f, 3.f}, {4.f, 5.f, 6.f}, {7.f, 8.f, 9.f}};
	std::vector<std::vector<double>> doubleMat = {{2.0, 4.0, 6.0}, {8.0, 10.0, 12.0}, {14.0, 16.0, 18.0}};
	
	std::cout << "Just a lone matrix:" << std::endl << std::endl;

	m2s::matout << intMat << std::endl;



	// In the style of cout
	std::cout << "Matrices printed with explicit labels:" << std::endl << std::endl;
	m2s::matout << "Ints" << intMat << "Floats" << floatMat << "doubleMat" << doubleMat << std::endl << std::endl;

	std::cout << "Matrices printed with operators in between:" << std::endl;
	m2s::matout << "Ints" << intMat << "+" << "Floats" << floatMat << "=" << " Result" << doubleMat << std::endl;


	std::cout << std::endl << "Matrices with variable names as labels:" << std::endl << std::endl;
	// Shortcut for inputting a variable with its name as the label
	m2s::matout << PRINT_BY_NAME(intMat) << "+" << PRINT_BY_NAME(floatMat) << "=" << PRINT_BY_NAME(doubleMat) << std::endl;

	// In the style of stringstream
	m2s::matstream ms;
	ms << "Ints" << intMat << "+";
	ms << "Floats" << floatMat << "=";
	ms << "Result" << doubleMat;

	std::cout << std::endl << "Matrices printed through a matstream object:" << std::endl << std::endl;
	std::cout << ms.str() << std::endl;
	ms.wipe();

	return 0;
}