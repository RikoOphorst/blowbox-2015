#pragma once

#include <string>
#include <iostream>
#include <Windows.h>

#include "../../blowbox/input/mouse.h"

namespace blowbox
{
	/**
	* @class blowbox::Window
	* @brief Handles the window
	* @author Riko Ophorst
	*/
	class Window
	{
	public:
		/**
		* @brief Default Window constructor
		*/
		Window();

		/**
		* @brief Default Window destructor
		*/
		~Window();

		/**
		* @brief Creates a window
		* @param[in] name (std::string) The name of the window in the title bar
		* @param[in] width (int) The width of the window
		* @param[in] height (int) The height of the window
		*/
		void Create(std::string name, int width, int height);

		/**
		* @brief Sets the resolution
		*/
		void SetResolution(const float& width, const float& height);

		/**
		* @brief Processes the Window's messages
		*/
		void ProcessMessages();

		/**
		* @brief Retrieves whether the window is started
		* @return bool is the window started?
		*/
		bool GetStarted();

		/**
		* @brief Sets the started property
		* @param[in] started (bool) is it started
		*/
		void SetStarted(bool val);

		/**
		* @brief Gets this window's HINSTANCE
		* @return HINSTANCE of this window
		*/
		HINSTANCE GetInstance();

		/**
		* @brief Gets this window's HWND
		* @return The handle of this window
		*/
		HWND GetHandle();

		/**
		* @brief Get this window's dimensions
		* @return RECT a struct holding the window's dimensions
		*/
		RECT GetDimensions();

		/**
		* @brief Handler for when the window gets focusses
		*/
		void OnSetFocus();
		
		/**
		* @brief Handler for when the window loses focus
		*/
		void OnKillFocus();
		
		/**
		* @brief Handler for when the window gets closed
		*/
		void OnClose();

		/**
		* @brief Handler for when the mouse moves
		*/
		void OnMouseMove(float x, float y);

		/**
		* @brief Handler for when a mouse button gets down
		* @param[in] MouseButton button
		*/
		void OnMouseDown(MouseButton button);

		/**
		* @brief Handler for when a mouse button gets released
		* @param[in] MouseButton button
		*/
		void OnMouseUp(MouseButton button);

		/**
		* @brief Handler for when a mouse button gets double clicked
		* @param[in] MouseButton button
		*/
		void OnMouseDbl(MouseButton button);

		/**
		* @brief Handler for when a key on the keyboard is pressed
		* @param[in] LMPARAM lParam
		*/
		void OnKeyDown(LPARAM lParam, WPARAM wParam);
		
		/**
		* @brief Handler for when a key on the keyboard is released
		* @param[in] LMPARAM lParam
		*/
		void OnKeyUp(LPARAM lParam, WPARAM wParam);
		
		/**
		* @brief Handler for when the mouse wheel gets scrolled
		* @param[in] LMPARAM lParam
		*/
		void OnWheel(LPARAM lParam, WPARAM wParam);

	private:
		HWND handle_;
		HINSTANCE instance_;
		bool started_;
	};

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
}