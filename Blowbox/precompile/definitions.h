#pragma once

#include <string>
#include <iostream>
#include <Windows.h>

#define BLOW_BREAK(msg) std::string m = ##msg; std::cout << m << std::endl; OutputDebugStringA("Assertion failed!\n\n"); OutputDebugStringA(m.c_str()); OutputDebugStringA("\n"); while(true){ __debugbreak(); }
#define BLOW_ASSERT(expr, msg) if (!(expr)) { BLOW_BREAK(msg) }
#define BLOW_ASSERT_HR(hr, msg) if (hr != S_OK) { BLOW_BREAK(msg); } 
#define BLOW_ASSERT_NOT_NULL(obj, msg) if (obj == NULL) { BLOW_BREAK(msg); }
#define BLOW_ASSERT_NULL(obj, msg) if (obj != NULL) { BLOW_BREAK(msg); }
#define BLOW_LOG(msg) std::string m = ##msg; std::cout << m << std::endl;