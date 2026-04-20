#pragma once

#include "mat2str.h"
#include <glm/glm.hpp>
#include <sstream>
#include <iomanip>

namespace m2s
{

	template<typename T, int numRows, int numCols>
	inline matstream::InternalMat make_internal_mat(const glm::mat<numRows, numCols, T>& mat, matstream& s)
	{
		matstream::InternalMat im(numRows, numCols);
		for (int r = 0; r < numRows; ++r) 
		{
			for (int c = 0; c < numCols; ++c) 
			{
				// glm matrices are column-major, our internal is row-major
				im(r, c) = s.to_string(mat[c][r]);
			}
		}
		return im;
	}

} // namespace m2s