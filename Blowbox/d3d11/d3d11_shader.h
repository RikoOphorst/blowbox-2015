#pragma once

#include <string>

#include "../../blowbox/d3d11/d3d11.h"

#define BLOW_BASE_SHADER "shaders/base.fx"

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
		* @brief Default D3D11Shader constructor
		* @param[in] path (const std::string&) the path to the shader
		*/
		D3D11Shader(const std::string& path);

		/**
		* @brief Default D3D11Shader destructor
		*/
		~D3D11Shader();

		/**
		* @brief Reloads & recompiles its shader
		*/
		void Reload();

		/**
		* @return ID3D11VertexShader* The vertex shader
		*/
		ID3D11VertexShader* GetVertexShader() const;

		/**
		* @return ID3D10Blob* The vertex shader buffer
		*/
		ID3D10Blob* GetVertexShaderBuffer() const;

		/**
		* @return ID3D11PixelShader* The pixel shader
		*/
		ID3D11PixelShader* GetPixelShader() const;

		/**
		* @return ID3D10Blob* The pixel shader buffer
		*/
		ID3D10Blob* GetPixelShaderBuffer() const;

		/**
		* @brief Sets the shader
		* @param[in] context (ID3D11DeviceContext*) the context
		*/
		void Set(ID3D11DeviceContext* context);
	private:
		ID3D11PixelShader*			pixel_shader_;
		ID3D10Blob*					pixel_shader_buffer_;
		ID3D11VertexShader*			vertex_shader_;
		ID3D10Blob*					vertex_shader_buffer_;
		std::string					path_;
	};
}