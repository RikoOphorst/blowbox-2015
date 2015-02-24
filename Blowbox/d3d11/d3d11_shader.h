#pragma once

#include "../../blowbox/d3d11/d3d11.h"

namespace blowbox
{
	/**
	* @class blowbox::D3D11Shader
	* @brief Creates a shader
	* @author Riko Ophorst
	*/
	class D3D11Shader
	{
	public:
		/**
		* Default D3D11Shader constructor
		*/
		D3D11Shader();

		/**
		* Default D3D11Shader destructor
		*/
		~D3D11Shader();
	private:
		ID3D11ShaderResourceView* resource_;
	};
}