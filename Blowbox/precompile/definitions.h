#pragma once

#include <string>
#include <iostream>
#include <Windows.h>
#include "../console/console.h"

#define BLOW_BREAK(msg) std::string m = ##msg; std::cout << m << std::endl; BLOW_CONSOLE_FATAL("Assertion failed!\n\n" + m); while(true){ __debugbreak(); }
#define BLOW_ASSERT(expr, msg) if (!(expr)) { BLOW_BREAK(msg) }
#define BLOW_ASSERT_HR(hr, msg) if (hr != S_OK) { BLOW_BREAK(msg); }
#define BLOW_ASSERT_NOT_NULL(obj, msg) if (obj == NULL || obj == nullptr) { BLOW_BREAK(msg); }
#define BLOW_ASSERT_NULL(obj, msg) if (obj != NULL) { BLOW_BREAK(msg); }
#define BLOW_LOG(msg) {std::string m = ##msg; std::cout << m << std::endl;}
#define BLOW_SAFE_RELEASE(ptr) BLOW_ASSERT_NOT_NULL(ptr, "Trying to release a D3D11 object which is null!"); ptr->Release(); ptr = NULL;
#define BLOW_SAFE_RELEASE_NB(ptr) if (ptr != NULL && ptr != nullptr) { ptr->Release(); ptr = NULL; }
#define BLOW_BOOL_TO_WBOOL(boolean, output) BOOL output; if (boolean == true) { output = 1; } else { output = 0; }

#define BLOW_CONSOLE_LOG(msg) if (blowbox::Console::DEBUG == true) { std::string m = "[LOG]\t"; std::string m2 = ##msg; blowbox::Console::Instance()->Log(std::string(m + m2).c_str()); }
#define BLOW_CONSOLE_INPUT(msg) if (blowbox::Console::DEBUG == true) { std::string m = "[INPUT]\t"; std::string m2 = ##msg; blowbox::Console::Instance()->Log(std::string(m + m2).c_str()); }
#define BLOW_CONSOLE_ERROR(msg) if (blowbox::Console::DEBUG == true) { std::string m = "[ERROR]\t"; std::string m2 = ##msg; blowbox::Console::Instance()->Log(std::string(m + m2).c_str()); }
#define BLOW_CONSOLE_FATAL(msg) if (blowbox::Console::DEBUG == true) { std::string m = "[FATAL]\t"; std::string m2 = ##msg; blowbox::Console::Instance()->Log(std::string(m + m2).c_str()); }