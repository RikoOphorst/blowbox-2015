#pragma once

#include "../../blowbox/logging.h"
#include "../../blowbox/d3d11/d3d11.h"
#include <Windows.h>
#include <xnamath.h>

namespace blowbox
{
	/**
	* @struct blowbox::ConstantBufferGlobal
	* @brief Contains data for the global constant buffer
	*/
	struct ConstantBufferGlobal
	{
		float time;
		XMMATRIX view;
		XMMATRIX projection;
	};

	/**
	* @struct blowbox::ConstantBufferObject
	* @brief Contains data for the per object constant buffer
	*/
	struct ConstantBufferObject
	{
		XMMATRIX world;
		float alpha;
	};

	/**
	* @enum blowbox::CONSTANT_BUFFER_TYPE
	* @brief The type of constant buffer
	*/
	enum CONSTANT_BUFFER_TYPE
	{
		CONSTANT_BUFFER_GLOBAL,
		CONSTANT_BUFFER_OBJECT
	};

	/**
	* @todo Make seperate classes for every constant buffer, which are derived from a constant buffer base class
	*/

	/**
	* @class blowbox::D3D11ConstantBuffer
	* @brief Handles a specific kind of constant buffer
	*/
	class D3D11ConstantBuffer
	{
	public:
		/**
		* @brief Default D3D11ConstantBuffer constructor
		*/
		D3D11ConstantBuffer();

		/**
		* @brief Default D3D11ConstantBuffer destructor
		*/
		~D3D11ConstantBuffer();

		/**
		* @brief Creates the constant buffer
		* @param[in] type (const CONSTANT_BUFFER_TYPE&) the type of constant buffer to be made
		*/
		void Create(const CONSTANT_BUFFER_TYPE& type);

		/**
		* @brief Maps a per object constant buffer
		* @param[in] context (ID3D11DeviceContext*) the context
		* @param[in] data (const ConstantBufferObject&) the data of the per object constant buffer
		*/
		void Map(ID3D11DeviceContext* context, const ConstantBufferObject& data);

		/**
		* @brief Maps a global constant buffer
		* @param[in] context (ID3D11DeviceContext*) the context
		* @param[in] data (const ConstantBufferGlobal&) the data of the global constant buffer
		*/
		void Map(ID3D11DeviceContext* context, const ConstantBufferGlobal& data);

		/**
		* @brief Sets the shader constant buffer
		* @param[in] context (ID3D11DeviceContext*) the context
		* @param[in] index (const int&) the index at which the shader should be placed
		*/
		void Set(ID3D11DeviceContext* context, const int& index);
	private:
		CONSTANT_BUFFER_TYPE type_;
		ID3D11Buffer* constant_buffer_;
	};
}