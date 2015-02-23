#include <chrono>
#include <iostream>
#include <math.h>

#include "memory/shared_ptr.h"

namespace blowbox
{
	/**
	* @class blowbox::Game
	* @brief Manages the Game
	* @author Riko Ophorst
	*/
	class Game
	{
	public:
		/**
		* @brief Default constructor
		*/
		Game();
		/**
		* @brief Default destructor
		*/
		~Game();

		/**
		* @brief Retrieves a pointer to the Game instance
		* @return A pointer to the Game's instance
		*/
		static Game* Instance();
	private:
		
	};
}