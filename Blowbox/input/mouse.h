#pragma once

#include "../memory/shared_ptr.h"
#include <xnamath.h>
#include <queue>

namespace blowbox
{
	struct MouseMoveEvent
	{
		float x;
		float y;
	};

	enum MouseButtonType
	{
		MouseDownEvent,
		MouseUpEvent,
		MouseDblEvent
	};

	enum MouseButton
	{
		MouseLeft,
		MouseMiddle,
		MouseRight
	};

	struct MouseState
	{
		bool down;
		bool pressed;
		bool dbl;
	};

	struct MouseButtonEvent
	{
		MouseButtonType type;
		MouseButton button;
	};

	class Mouse
	{
	public:
		Mouse();
		~Mouse();

		static Mouse*					Instance();

		XMFLOAT2&						GetPosition();
		bool&							IsDown(MouseButton btn);
		bool&							IsPressed(MouseButton btn);
		bool&							IsDbl(MouseButton btn);

		void							ResetStates();
		void							Update();

		void							ReceiveEvent(MouseMoveEvent moveEvent);
		void							ReceiveEvent(MouseButtonEvent buttonEvent);
	private:
		XMFLOAT2						pos_;
		std::queue<MouseMoveEvent>		moveQueue_;
		std::queue<MouseButtonEvent>	clickQueue_;
		MouseState						mouseStates_[3];
	};
}