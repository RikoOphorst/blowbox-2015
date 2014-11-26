#include "keyboard.h"

namespace blowbox
{
	Keyboard::Keyboard()
		: lastKey_(kA)
	{
		for (unsigned int i = 0; i < 255; ++i)
		{
			keyStates_[i].down = false;
			keyStates_[i].released = false;
			keyStates_[i].pressed = false;
		}
	}

	Keyboard::~Keyboard()
	{

	}

	Keyboard* Keyboard::Instance()
	{
		static SharedPtr<Keyboard> ptr(new Keyboard());
		return ptr.get();
	}

	bool& Keyboard::IsDown(Key key)
	{
		return keyStates_[key].down;
	}

	bool& Keyboard::IsPressed(Key key)
	{
		return keyStates_[key].pressed;
	}

	bool& Keyboard::IsReleased(Key key)
	{
		return keyStates_[key].released;
	}

	Key Keyboard::LastKey()
	{
		if (lastKey_ != kNULL)
		{
			Key key = lastKey_;
			
			lastKey_ = kNULL;

			return key;
		}

		return kNULL;
	}

	void Keyboard::ReceiveEvent(KeyData evt)
	{
		queue_.push(evt);
	}

	void Keyboard::ResetStates()
	{
		for (unsigned int i = 0; i < 255; ++i)
		{
			keyStates_[i].pressed = false;
			keyStates_[i].released = false;
		}
	}

	void Keyboard::Update()
	{
		ResetStates();

		while (!queue_.empty())
		{
			const KeyData& evt = queue_.front();

			switch (evt.type)
			{
			case kePressed:
				if (!keyStates_[evt.key].down)
					keyStates_[evt.key].pressed = true;

				keyStates_[evt.key].down = true;
				lastKey_ = evt.key;
				break;
			case keReleased:
				keyStates_[evt.key].down = false;
				keyStates_[evt.key].released = true;
				break;
			}

			queue_.pop();
		}
	}

	std::string KeyToString(Key key)
	{
		std::string string;

		if (key == kA) 			string = "a";
		if (key == kB) 			string = "b";
		if (key == kC) 			string = "c";
		if (key == kD) 			string = "d";
		if (key == kE) 			string = "e";
		if (key == kF) 			string = "f";
		if (key == kG) 			string = "g";
		if (key == kH) 			string = "h";
		if (key == kI) 			string = "i";
		if (key == kJ) 			string = "j";
		if (key == kK) 			string = "k";
		if (key == kL) 			string = "l";
		if (key == kM) 			string = "m";
		if (key == kN) 			string = "n";
		if (key == kO) 			string = "o";
		if (key == kP) 			string = "p";
		if (key == kQ) 			string = "q";
		if (key == kR) 			string = "r";
		if (key == kS) 			string = "s";
		if (key == kT) 			string = "t";
		if (key == kU) 			string = "u";
		if (key == kV) 			string = "v";
		if (key == kW) 			string = "w";
		if (key == kX) 			string = "x";
		if (key == kY) 			string = "y";
		if (key == kZ)			string = "z";
		if (key == kSpace)		string = " ";

		return string;
	}
}