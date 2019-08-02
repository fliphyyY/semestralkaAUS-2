#include <stdexcept>
#include <string>


#include "DSRoutines.h"

using namespace DS;

DSRoutines::DSRoutines()
{
}

bool DSRoutines::rangeCheck(const int index, const size_t size, bool throwException, const std::string* message)
{
	if (index >= 0 && (size_t)index < size)
		return true;
	else if (throwException)
		throw std::out_of_range(*message);
	else
		return false;
}
