#pragma once

#include <dxgi.h>
#include <d3d11.h>
#include <d3dcommon.h>
#include <D3DX10.h>
#include <D3DX11.h>

#define BLOW_SAFE_RELEASE(ptr) if (ptr != NULL && ptr != nullptr) { ptr->Release(); } else { BLOW_BREAK("Trying to release an object which is already NULL or nullptr"); }
#define BLOW_RELEASE(ptr) if (ptr != NULL && ptr != nullptr) { ptr->Release(); }