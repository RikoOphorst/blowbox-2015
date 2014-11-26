#pragma once

#include <queue>
#include "../input/key.h"
#include "../memory/shared_ptr.h"

namespace blowbox
{
	enum KeyEvent
	{
		kePressed,
		keDown,
		keReleased
	};

	struct KeyData
	{
		Key key;
		KeyEvent type;
	};

	struct KeyState
	{
		bool pressed;
		bool down;
		bool released;
	};

	class Keyboard
	{
	public:
		Keyboard();
		~Keyboard();

		static Keyboard*		Instance();

		bool&					IsDown(Key key);
		bool&					IsPressed(Key key);
		bool&					IsReleased(Key key);
		Key						LastKey();

		void					ReceiveEvent(KeyData evt);

		void					ResetStates();

		void					Update();
	private:
		KeyState				keyStates_[255];
		Key						lastKey_;
		std::queue<KeyData>		queue_;
	};
}