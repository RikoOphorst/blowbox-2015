#pragma once

#include "../../blowbox/d3d11/d3d11.h"
#include "../../blowbox/logging.h"

namespace blowbox
{
	class D3D11Shader;

	/**
	* @class blowbox::D3D11InputLayout
	* @brief Handles the input layout
	* @author Riko Ophorst
	*/
	class D3D11InputLayout
	{
	public:
		/**
		* @brief Default D3D11InputLayout constructor
		* @param[in] input_layout_desc (D3D11_INPUT_ELEMENT_DESC*) the description of the input layout
		* @param[in] stride (UINT) the stride size of the input layout description
		* @param[in] shader (D3D11Shader*) a shader for the input layout to be outputted on
		*/
		D3D11InputLayout(D3D11_INPUT_ELEMENT_DESC* input_layout_desc, UINT stride, D3D11Shader* shader);

		/**
		* @brief Default D3D11InputLayout destructor
		*/
		~D3D11InputLayout();

		/**
		* @brief Sets the input layout
		*/
		void Set(ID3D11DeviceContext* context);
	private:
		ID3D11InputLayout* input_layout_;
	};
}