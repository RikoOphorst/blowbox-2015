#pragma once
#include <string>
#include <iostream>
#include "../precompile/definitions.h"
#include "../input/keyboard.h"
#include "../input/key.h"
#include "../input/mouse.h"

namespace blowbox 
{
	class Window
	{
	public:
		Window();
		~Window();

		void Make(std::string name, int width, int height);
		void ProcessMessages();
		bool started();
		void set_started(bool val);
		HINSTANCE getInstance();
		HWND getHandle();

		void OnSetFocus();
		void OnKillFocus();
		void OnClose();
		void OnMouseMove(float x, float y);
		void OnMouseDown(MouseButton button);
		void OnMouseUp(MouseButton button);
		void OnMouseDbl(MouseButton button);
		void OnKeyDown(LPARAM lParam, WPARAM wParam);
		void OnKeyUp(LPARAM lParam, WPARAM wParam);
		void OnWheel(LPARAM lParam, WPARAM wParam);

	private:
		HWND handle_;
		HINSTANCE instance_;
		bool started_;
	};

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
}