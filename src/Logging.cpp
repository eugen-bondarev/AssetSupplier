#include "Logging.h"

#include <iostream>

namespace Asu
{
	void ConsoleOut(const String& message)
	{
		std::cout << message << '\n';
	}
}