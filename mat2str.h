#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include <cstdarg>
#include <algorithm>


#define PRINT_BY_NAME(var) #var << var

namespace m2s
{

	class matstream
	{
	public:

		std::string matrix_delimiter_left{ "[" };
		std::string matrix_delimiter_right{ "]" };
		int precision = 2;


		matstream& operator<<(const std::string& label)
		{
			latestLabel_ += label;
			return *this;
		}

		template<size_t N>
		matstream& operator<<(const char(&label)[N])
		{
			return operator<<(std::string(label, N - 1)); // N includes terminating '\0'
		}

		matstream& operator<<(const char(&operatorChar)[2])
		{
			if ( std::isalnum(operatorChar[0]))
			{
				// If it's alphanumeric, treat it as a label instead of an operator.
				return operator<<(std::string(operatorChar, 1));
			}
			if (std::isspace(operatorChar[0]))
			{
				// Ignore whitespace as an operator.
				return *this;
			}
			latestOperator_ = operatorChar[0];
			return *this;
		}

		template<typename matrix_t>
		matstream& operator<<(const matrix_t& mat)
		{
			cache_.emplace_back(make_internal_mat(mat, *this));
			if (!latestLabel_.empty())
			{
				cache_.back().label = latestLabel_;
				latestLabel_.clear();
			}
			if (!latestOperator_.empty())
			{
				cache_.back().precedingOperator = latestOperator_;
				latestOperator_.clear();

			}

			return *this;
		}

		virtual matstream& operator<<(std::ostream& (*manip)(std::ostream&))
		{

			return *this;
		}

		template <typename T>
		std::string to_string(const T a_value)
		{
			internalConverter_.str("");
			internalConverter_.precision(precision);
			internalConverter_ << std::fixed << a_value;
			return internalConverter_.str();
		}

		std::string getAndReset()
		{
			const auto returnString = str();
			this->wipe();
			return returnString;
		}

		std::string str() const
		{

			size_t maxRows = 0;
			for (const auto& entry : cache_)
			{
				maxRows = std::max(maxRows, entry.numRows);
			}

			std::ostringstream labels;
			std::vector<std::ostringstream> rowstreams(maxRows);



			for (const auto& entry : cache_)
			{

				if (!entry.precedingOperator.empty())
				{

					labels << "  ";
					for (size_t r = 0; r < entry.numRows; ++r)
					{
						if (r == ((maxRows + 1) / 2) - 1) {
							rowstreams[r] << entry.precedingOperator << " ";
						}
						else {
							rowstreams[r] << "  ";
						}
					}
				}


				size_t totalMatrixWidth = 0;

				for (size_t r = 0; r < entry.numRows; ++r)
				{

					rowstreams[r] << matrix_delimiter_left << " ";
				}

				for (size_t c = 0; c < entry.numCols; ++c)
				{
					size_t colWidth = entry.getColumnWidth(c);
					for (size_t r = 0; r < entry.numRows; ++r)
					{
						rowstreams[r] << std::setw(colWidth) << entry.get(r, c);
						rowstreams[r] << (c == (entry.numCols - 1) ? " " : "  ");
					}
					totalMatrixWidth += colWidth + 2;
				}

				for (size_t r = 0; r < entry.numRows; ++r)
				{
					rowstreams[r] << matrix_delimiter_right << " ";
				}


				labels << std::setw(totalMatrixWidth) << entry.label << " ";

			}

			std::ostringstream final_output;


			final_output << labels.str() << std::endl;
			for (const auto& fullrow : rowstreams)
			{
				final_output << fullrow.str() << std::endl;
			}
			return final_output.str();
		}

		void wipe()
		{
			cache_.clear();
			latestLabel_.clear();
			latestOperator_.clear();
			internalConverter_ = std::ostringstream();

		}

		// Row-major internal storage for stringified matrix elements
		class InternalMat
		{
		public:
			InternalMat(const size_t numRows, const size_t numCols) : numRows(numRows), numCols(numCols)
			{
				rows.resize(numRows);
				for (auto& row : rows)
				{
					row.resize(numCols);
				}
			}
			std::string get(const size_t r, const size_t c) const
			{
				return rows.at(r).at(c);
			}
			std::string& operator()(const size_t r, const size_t c)
			{
				return rows.at(r).at(c);
			}

			size_t getColumnWidth(const size_t c) const
			{
				size_t width = 0;
				for (size_t r = 0; r < numRows; ++r) {
					width = std::max(width, rows.at(r).at(c).size());
				}
				return width;
			}
			const size_t numRows;
			const size_t numCols;
			std::string label;
			std::string precedingOperator;

			bool empty() const
			{
				return (numRows == 0) && (numCols == 0);
			}


		private:
			// Is this the most optimized matrix storage ever? No.
			// If you are converting matrices to strings, do you care? Probably not.
			std::vector<std::vector<std::string>> rows;
		};


	private:



		template<typename T>
		friend InternalMat make_internal_mat(const T& mat, matstream& self);


		std::vector<InternalMat> cache_;
		std::string latestLabel_;
		std::string latestOperator_;

		std::ostringstream internalConverter_;


	};

	template<typename value_t>
	matstream::InternalMat make_internal_mat(
		const std::vector<std::vector<value_t>>& mat,
		matstream& self)
	{
		size_t maxRowLength = 0;
		for (const auto& row : mat)
		{
			maxRowLength = std::max(maxRowLength, row.size());
		}

		matstream::InternalMat stringyMat(mat.size(), maxRowLength);

		for (int r = 0; r < mat.size(); ++r)
		{
			for (int c = 0; c < mat.at(r).size(); ++c)
			{
				stringyMat(r, c) = self.to_string(mat.at(r).at(c));
			}
		}

		return stringyMat;
	}

	/*

	template<typename matrix_t>
	std::string to_string(matrix_t mat, ...)
	{

		va_list args;
		va_start(args, count);



		for (size_t  = 0; i < count; ++i) {
			std::cout << va_arg(args, int);
			std::cout << " ";
		}

	}

	template<typename matrix_t>
	std::string to_string(const matrix_t& mat, int precision = 3)
	{
		std::ostringstream oss;
		oss.precision(precision);
		oss << std::fixed;
		print_mat(oss, mat);
		return oss.str();

	}


	template<typename value_t>
	void print_mat(std::ostringstream& ss, const std::vector<std::vector<value_t>>& mat)
	{
		for ( const auto& row : mat)
		{
			for (const auto& val : row)
			{

				ss << val << " ";
			}
			ss << std::endl;
		}
	}

	*/


}