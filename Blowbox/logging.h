#pragma once

#include <iostream>
#include <Windows.h>

#define BLOW_BREAK(str) std::string m = ##str; std::cout << m.c_str() << std::endl; OutputDebugStringA(m.c_str()); while(true){ __debugbreak(); }
#define BLOW_ASSERT(expr, str) if (!(expr)) { BLOW_BREAK(str) }
#define BLOW_ASSERT_HR(hr, str) if (hr != S_OK) { BLOW_BREAK(str); }