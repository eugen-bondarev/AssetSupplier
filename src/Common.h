#pragma once


#include <iostream>
#define LOG_OUT(x) std::cout << x << std::endl
#define LOG_OUT_INLINE(x) std::cout << x
#define VAR_OUT(x) LOG_OUT(#x << " = " << x)


#include <assert.h>
#define ASSERT(x) assert(x)

#include <vector>
#include <string>