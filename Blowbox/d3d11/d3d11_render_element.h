#pragma once

#include "../../blowbox/memory/shared_ptr.h"
#include "../../blowbox/d3d11/d3d11.h"
#include <xnamath.h>

namespace blowbox
{	
	class D3D11Texture;
	class D3D11Shader;
	class D3D11VertexBuffer;
	class D3D11SamplerState;
	class D3D11RasterizerState;
	class D3D11BlendState;
	enum TEXTURE_FILTERING_TYPE;
	
	/**
	* @class blowbox::D3D11RenderElement
	* @brief Base class for every element that should be rendered
	* @author Riko Ophorst
	*/
	class D3D11RenderElement
	{
	public:
		/**
		* @brief Default D3D11RenderElement constructor
		*/
		D3D11RenderElement();

		/**
		* @brief Default D3D11RenderElement destructor
		*/
		virtual ~D3D11RenderElement();

		/**
		* @return const XMVECTOR& The position of the element
		*/
		const XMVECTOR& GetPosition() const;

		/**
		* @return const float& The x-coordinate of the element
		*/
		const float& GetX() const;

		/**
		* @return const float& The y-coordinate of the element
		*/
		const float& GetY() const;

		/**
		* @return const float& The z-coordinate of the element
		*/
		const float& GetZ() const;

		/**
		* @return const XMVECTOR& The rotation of the element
		*/
		const XMVECTOR& GetRotation() const;

		/**
		* @return const XMVECTOR& The scale of the element
		*/
		const XMVECTOR& GetScale() const;

		/**
		* @return const XMVECTOR& The offset of the element
		*/
		const XMVECTOR& GetOffset() const;

		/**
		* @return const float& The alpha of the element
		*/
		const double& GetAlpha() const;

		/**
		* @return D3D11Texture* The texture of the element
		*/
		D3D11Texture* GetTexture();

		/**
		* @return D3D11Shader* The texture of the element
		*/
		D3D11Shader* GetShader();

		/**
		* @return D3D11VertexBuffer* The vertex buffer of the element
		*/
		D3D11VertexBuffer* GetVertexBuffer();

		/**
		* @brief Sets the position of the element
		* @param[in] x (float) The x position
		* @param[in] y (float) The y position
		* @param[in] z (float) The z position
		*/
		void SetPosition(float x, float y, float z);

		/**
		* @brief Sets the x position of the element
		* @param[in] x (float) The x position
		*/
		void SetX(float x);

		/**
		* @brief Sets the x position of the element
		* @param[in] y (float) The y position
		*/
		void SetY(float y);

		/**
		* @brief Sets the x position of the element
		* @param[in] z (float) The z position
		*/
		void SetZ(float z);

		/**
		* @brief Sets the rotation of the element
		* @param[in] x (float) The x rotation of the element
		* @param[in] y (float) The y rotation of the element
		* @param[in] z (float) The z rotation of the element
		*/
		void SetRotation(float x, float y, float z);

		/**
		* @brief Sets the scaling of the element
		* @param[in] x (float) The x scaling of the element
		* @param[in] y (float) The y scaling of the element
		* @param[in] z (float) The z scaling of the element
		*/
		void SetScale(float x, float y, float z);

		/**
		* @brief Sets the offset of the element
		* @param[in] x (float) The x offset of the element
		* @param[in] y (float) The y offset of the element
		* @param[in] z (float) The z offset of the element
		*/
		void SetOffset(float x, float y, float z);
		
		/**
		* @brief Set the alpha of the element
		* @param[in] alpha (double) the alpha
		*/
		void SetAlpha(double alpha);

		/**
		* @brief Set the alpha of the element
		* @param[in] alpha (float) the alpha
		*/
		void SetAlpha(float alpha);

		/**
		* @brief Set the texture of the element
		* @param[in] path (std::string) The path to the texture
		*/
		void SetTexture(std::string path);

		/**
		* @brief Set the shader of the element
		* @param[in] path (std::string) The path to the shader
		*/
		void SetShader(std::string path);

		/**
		* @brief Parses the private XMFLOAT3 position_ struct to an XMVECTOR
		*/
		void CalculatePosition();

		/**
		* @brief Parses the private XMFLOAT3 rotation_ struct to an XMVECTOR
		*/
		void CalculateRotation();

		/**
		* @brief Parses the private XMFLOAT3 scaling_ struct to an XMVECTOR
		*/
		void CalculateScaling();

		/**
		* @brief Parses the private XMFLOAT3 offset_ struct to an XMVECTOR
		*/
		void CalculateOffset();

		/**
		* @brief Retrieves the world matrix
		*/
		XMMATRIX& GetWorld();

		/**
		* @brief Retrieves the sampler type
		*/
		const TEXTURE_FILTERING_TYPE& GetFilteringType() const;

		/**
		* @brief Retrieves the D3D11RasterizerState of this object
		*/
		D3D11RasterizerState* GetRasterizerState();

		/**
		* @brief Retrieves the D3D11BlendState of this object
		*/
		D3D11BlendState* GetBlendState();
	protected:
		XMFLOAT3 position_;
		XMVECTOR v_position_;
		
		XMFLOAT3 rotation_;
		XMVECTOR v_rotation_;
		
		XMFLOAT3 scaling_;
		XMVECTOR v_scaling_;
		
		XMFLOAT3 offset_;
		XMVECTOR v_offset_;

		XMMATRIX world_matrix_;
		
		double alpha_;

		SharedPtr<D3D11Texture> texture_;
		SharedPtr<D3D11Shader> shader_;

		SharedPtr<D3D11VertexBuffer> vertex_buffer_;

		SharedPtr<D3D11RasterizerState> rasterizer_state_;
		SharedPtr<D3D11BlendState> blend_state_;

		TEXTURE_FILTERING_TYPE texture_filtering_;
	};
}