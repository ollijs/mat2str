#pragma once

#include "mat2str.h"
//#include <linalg/linalg.h>


namespace m2s
{

	template<typename T, int numRows, int numCols>
	inline matstream::InternalMat make_internal_mat(const linalg::mat<T, numRows, numCols>& mat, matstream& s)
	{
		matstream::InternalMat im(numRows, numCols);
		for (int r = 0; r < numRows; ++r) 
		{
			for (int c = 0; c < numCols; ++c) 
			{
				// linalg matrices are column-major, our internal is row-major
				im(r, c) = s.to_string(mat[c][r]);
			}
		}
		return im;
	}

} // namespace m2s