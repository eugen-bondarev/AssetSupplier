#include "Logging.h"

#include <iostream>

namespace srm
{
	void ConsoleOut(const String& message)
	{
		std::cout << message << '\n';
	}
}