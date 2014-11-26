#include "mouse.h"

namespace blowbox
{
	Mouse::Mouse()
		: pos_(0.0f, 0.0f)
	{
		for (unsigned int i = 0; i < 3; ++i)
		{
			mouseStates_[i].down = false;
			mouseStates_[i].pressed = false;
			mouseStates_[i].dbl = false;
		}
	}

	Mouse* Mouse::Instance()
	{
		static SharedPtr<Mouse> ptr(new Mouse());
		return ptr.get();
	}

	XMFLOAT2& Mouse::GetPosition()
	{
		return pos_;
	}

	bool& Mouse::IsDown(MouseButton btn)
	{
		return mouseStates_[btn].down;
	}

	bool& Mouse::IsPressed(MouseButton btn)
	{
		return mouseStates_[btn].pressed;
	}

	bool& Mouse::IsDbl(MouseButton btn)
	{
		return mouseStates_[btn].dbl;
	}

	void Mouse::ResetStates()
	{
		for (unsigned int i = 0; i < 3; ++i)
		{
			mouseStates_[i].pressed = false;
			mouseStates_[i].dbl = false;
		}
	}

	void Mouse::ReceiveEvent(MouseMoveEvent evt)
	{
		moveQueue_.push(evt);
	}

	void Mouse::ReceiveEvent(MouseButtonEvent button)
	{
		clickQueue_.push(button);
	}

	void Mouse::Update()
	{
		ResetStates();

		while (!moveQueue_.empty())
		{
			const MouseMoveEvent& evt = moveQueue_.front();

			pos_.x = evt.x;
			pos_.y = evt.y;

			moveQueue_.pop();
		}

		while (!clickQueue_.empty())
		{
			const MouseButtonEvent& evt = clickQueue_.front();

			switch (evt.type)
			{
			case MouseDownEvent:
				mouseStates_[evt.button].pressed = true;
				mouseStates_[evt.button].down = true;
				break;
			case MouseUpEvent:
				mouseStates_[evt.button].down = false;
				break;
			case MouseDblEvent:
				mouseStates_[evt.button].dbl = true;
				break;
			}

			clickQueue_.pop();
		}
	}

	Mouse::~Mouse()
	{

	}
}