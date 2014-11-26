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

using namespace blowbox;

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

	SharedPtr<Quad> quad1(new Quad());

	d3d11DisplayDevice->AddElement(quad1.get());

	quad1->SetTexture("penis.png");

	camera->SetPosition(0.0f, 0.0f, -8.0f);

	camera->SetTarget(0.0f, 0.0f, 0.0f);

	float r = 0.0f;

	while (window->started())
	{
		window->ProcessMessages();
		Keyboard::Instance()->Update();
		Mouse::Instance()->Update();

		//std::cout << "Mouse X: " << Mouse::Instance()->GetPosition().x << " Mouse Y: " << Mouse::Instance()->GetPosition().y << " Mouse Left Down: " << Mouse::Instance()->IsDown(MouseLeft) << " Left key down: " << Keyboard::Instance()->IsDown(kLeft) << " Right key down: " << Keyboard::Instance()->IsDown(kRight) << std::endl;
		
		
		
		std::cout << KeyToString(Keyboard::Instance()->LastKey());

		
		
		
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