#pragma once
#include "mat2str.h"
#include <iostream>

namespace m2s
{
	class matostream : public matstream
	{
	public:
		matostream(std::ostream& out = std::cout) : out_(&out) {}

		using matstream::operator<<;

		virtual matostream& operator<<(std::ostream& (*manip)(std::ostream&)) override
		{
			// If the manipulator is std::endl, emit the current buffered matrices and reset.
			if (manip == static_cast<std::ostream & (*)(std::ostream&)>(std::endl))
			{
				*out_ << this->getAndReset();
				*out_ << std::endl;
			}
			else
			{
				// Forward other ostream manipulators (e.g., std::flush).
				*out_ << manip;
			}
			return *this;
		}

	private:
		std::ostream* out_;
	};

	static matostream matout;






}