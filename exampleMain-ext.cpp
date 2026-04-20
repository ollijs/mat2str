#include "mat2str/mat2str.h"

// glm and linalg are not provided by this lib, you have to provide them yourself if you want to print their matrices
#include <glm/glm.hpp>
#include "mat2str/mat2str-glm.h"	
#include <linalg/linalg.h>
#include "mat2str/mat2str-linalg.h"	

#include "mat2str/mat2str-cout.h"

#include <iostream>


int main()
{
	// Some dependency free "matrices"
	std::vector<std::vector<int>> intMat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	
	// GLM matrices
	glm::mat4 glmMat(1.0f);

	std::cout << std::endl << "GLM matrix:" << std::endl << std::endl;
	m2s::matout << PRINT_BY_NAME(glmMat) << std::endl;



	// Linalg.h matrices
	linalg::aliases::float4x4 linalgMat;
	linalgMat[3][1] = 10.0;
	linalgMat[3][2] = 11.0;
	linalgMat[3][3] = 12.0;


	std::cout << std::endl << "linalg.h matrix:" << std::endl << std::endl;

	m2s::matout << PRINT_BY_NAME(linalgMat) << std::endl;

	// Different sizes
	std::cout << std::endl << "Different sized matrices partially with labels:" << std::endl << std::endl;
	m2s::matout << PRINT_BY_NAME(glmMat) << "*" << intMat << std::endl;


	std::cout << std::endl << "(Yes that is invalid math. This is for printing matrices, not for linear algebra)" << std::endl << std::endl;



	return 0;
}