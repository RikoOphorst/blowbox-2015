#include <memory>
#include <iostream>
#include "d3d11/d3d11_display_device.h"
#include "d3d11/d3d11_camera.h"
#include "d3d11/d3d11_render_element.h"
#include "win32/window.h"
#include "memory/shared_ptr.h"
#include "input/keyboard.h"
#include "input/mouse.h"
#include "geom/quad.h"
#include "geom/cube.h"
#include <math.h>
#include <chrono>

using namespace blowbox;
using namespace std::chrono;

namespace memory
{
	AllocatedMemory& allocated_memory();
}

int main (int argc, char** argv)
{	
	AllocatedMemory* memory = allocated_memory();
	SharedPtr<Window> window(new Window());
	SharedPtr<D3D11Camera> camera(new D3D11Camera(CAM_ORTHOGRAPHIC));

	D3D11DisplayDevice* d3d11DisplayDevice = D3D11DisplayDevice::Instance();
	d3d11DisplayDevice->SetCamera(camera.get());
	
	window->Make("Blowbox", 640, 480);
	d3d11DisplayDevice->Create(window->getHandle());
	d3d11DisplayDevice->InitScene();

	Mouse::Instance();
	Keyboard::Instance();

	high_resolution_clock::time_point lastTime_ = high_resolution_clock::now();

	SharedPtr<Quad> quad1(new Quad());

	d3d11DisplayDevice->AddElement(quad1.get());

	quad1->SetTexture("tex1.png");

	camera->SetPosition(0.0f, 0.0f, -8.0f);

	camera->SetTarget(0.0f, 0.0f, 0.0f);

	float r = 0.0f;

	while (window->started())
	{
		high_resolution_clock::time_point now = high_resolution_clock::now();

		std::cout << duration_cast<duration<double, std::milli>>(now - lastTime_).count() * 1e-3f << std::endl;

		auto dt = duration_cast<duration<double, std::milli>>(now - lastTime_).count() * 1e-3f;

		lastTime_ = now;

		window->ProcessMessages();
		Keyboard::Instance()->Update();
		Mouse::Instance()->Update();

		quad1->SetPosition(XMVectorGetX(quad1->GetPosition()) - 20.0f * dt, 0.0f, 0.0f);

		
		if (Mouse::Instance()->IsDown(MouseLeft))
		{
			quad1->SetPosition(XMVectorGetX(quad1->GetPosition()) - 0.1f, XMVectorGetY(quad1->GetPosition()), 0.0f);
		}

		if (Mouse::Instance()->IsDown(MouseRight))
		{
			quad1->SetPosition(XMVectorGetX(quad1->GetPosition()) + 0.1f, XMVectorGetY(quad1->GetPosition()), 0.0f);
		}


		if (Keyboard::Instance()->IsDown(kLeft))
		{
			quad1->SetPosition(XMVectorGetX(quad1->GetPosition()) - 0.1f, XMVectorGetY(quad1->GetPosition()), 0.0f);
		}

		if (Keyboard::Instance()->IsDown(kRight))
		{
			quad1->SetPosition(XMVectorGetX(quad1->GetPosition()) + 0.1f, XMVectorGetY(quad1->GetPosition()), 0.0f);
		}

		d3d11DisplayDevice->BeginDraw();

		d3d11DisplayDevice->Draw();

		d3d11DisplayDevice->EndDraw();
	}

	d3d11DisplayDevice->Release(); 
	return EXIT_SUCCESS;
}