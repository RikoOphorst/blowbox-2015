#pragma once

#include <Windows.h>
#include <xnamath.h>

#include "../../blowbox/memory/shared_ptr.h"
#include "../../blowbox/d3d11/d3d11.h" 
#include "../../blowbox/lua/lua_class.h"

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
	class D3D11RenderElement : public LuaClass
	{
	public:
		/**
		* @brief Default D3D11RenderElement constructor
		*/
		D3D11RenderElement();

		/**
		* @brief D3D11RenderElement lua constructor
		* @param[in] L (lua_State* L)
		*/
		D3D11RenderElement(lua_State* L);

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
		* @brief Sets the position of the element
		* @param[in] x (double) The x position
		* @param[in] y (double) The y position
		* @param[in] z (double) The z position
		*/
		void SetPosition(double x, double y, double z);

		/**
		* @brief Sets the x position of the element
		* @param[in] x (float) The x position
		*/
		void SetX(float x);

		/**
		* @brief Sets the x position of the element
		* @param[in] x (double) The x position
		*/
		void SetX(double x);

		/**
		* @brief Sets the x position of the element
		* @param[in] y (float) The y position
		*/
		void SetY(float y);

		/**
		* @brief Sets the x position of the element
		* @param[in] y (double) The y position
		*/
		void SetY(double y);

		/**
		* @brief Sets the x position of the element
		* @param[in] z (float) The z position
		*/
		void SetZ(float z);

		/**
		* @brief Sets the x position of the element
		* @param[in] z (double) The z position
		*/
		void SetZ(double z);

		/**
		* @brief Sets the rotation of the element
		* @param[in] x (float) The x rotation of the element
		* @param[in] y (float) The y rotation of the element
		* @param[in] z (float) The z rotation of the element
		*/
		void SetRotation(float x, float y, float z);

		/**
		* @brief Sets the rotation of the element
		* @param[in] x (double) The x rotation of the element
		* @param[in] y (double) The y rotation of the element
		* @param[in] z (double) The z rotation of the element
		*/
		void SetRotation(double x, double y, double z);

		/**
		* @brief Sets the scaling of the element
		* @param[in] x (float) The x scaling of the element
		* @param[in] y (float) The y scaling of the element
		* @param[in] z (float) The z scaling of the element
		*/
		void SetScale(float x, float y, float z);

		/**
		* @brief Sets the scaling of the element
		* @param[in] x (double) The x scaling of the element
		* @param[in] y (double) The y scaling of the element
		* @param[in] z (double) The z scaling of the element
		*/
		void SetScale(double x, double y, double z);

		/**
		* @brief Sets the offset of the element
		* @param[in] x (float) The x offset of the element
		* @param[in] y (float) The y offset of the element
		* @param[in] z (float) The z offset of the element
		*/
		void SetOffset(float x, float y, float z);

		/**
		* @brief Sets the offset of the element
		* @param[in] x (double) The x offset of the element
		* @param[in] y (double) The y offset of the element
		* @param[in] z (double) The z offset of the element
		*/
		void SetOffset(double x, double y, double z);
		
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

		/**
		* @brief Sets the position of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaSetPosition(lua_State* L);

		/**
		* @brief Gets the position of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaGetPosition(lua_State* L);

		/**
		* @brief Sets the position of this object in 2D space
		* @param[in] L (lua_State* L)
		*/
		static int LuaSetPosition2D(lua_State* L);
		
		/**
		* @brief Gets the position of this object in 2D space
		* @param[in] L (lua_State* L)
		*/
		static int LuaGetPosition2D(lua_State* L);

		/**
		* @brief Sets the x position of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaSetX(lua_State* L);

		/**
		* @brief Gets the x position of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaGetX(lua_State* L);

		/**
		* @brief Sets the y position of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaSetY(lua_State* L);
		
		/**
		* @brief Gets the y position of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaGetY(lua_State* L);

		/**
		* @brief Sets the z position of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaSetZ(lua_State* L);

		/**
		* @brief Gets the z position of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaGetZ(lua_State* L);

		/**
		* @brief Sets the rotation of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaSetRotation(lua_State* L);

		/**
		* @brief Gets the rotation of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaGetRotation(lua_State* L);

		/**
		* @brief Sets the rotation of this object in 2D space
		* @param[in] L (lua_State* L)
		*/
		static int LuaSetRotation2D(lua_State* L);

		/**
		* @brief Gets the rotation of this object in 2D space
		* @param[in] L (lua_State* L)
		*/
		static int LuaGetRotation2D(lua_State* L);

		/**
		* @brief Sets the scale of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaSetScale(lua_State* L);

		/**
		* @brief Gets the scale of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaGetScale(lua_State* L);

		/**
		* @brief Sets the scale of this object in 2D space
		* @param[in] L (lua_State* L)
		*/
		static int LuaSetScale2D(lua_State* L);

		/**
		* @brief Gets the scale of this object in 2D space
		* @param[in] L (lua_State* L)
		*/
		static int LuaGetScale2D(lua_State* L);

		/**
		* @brief Sets the offset of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaSetOffset(lua_State* L);

		/**
		* @brief Gets the offset of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaGetOffset(lua_State* L);

		/**
		* @brief Sets the offset of this object in 2D space
		* @param[in] L (lua_State* L)
		*/
		static int LuaSetOffset2D(lua_State* L);

		/**
		* @brief Gets the offset of this object in 2D space
		* @param[in] L (lua_State* L)
		*/
		static int LuaGetOffset2D(lua_State* L);

		/**
		* @brief Sets the alpha of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaSetAlpha(lua_State* L);

		/**
		* @brief Gets the alpha of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaGetAlpha(lua_State* L);

		/**
		* @brief Sets the texture of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaSetTexture(lua_State* L);

		/**
		* @brief Gets the texture of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaGetTexture(lua_State* L);

		/**
		* @brief Sets the texture of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaSetShader(lua_State* L);

		/**
		* @brief Gets the texture of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaGetShader(lua_State* L);

		/**
		* @brief Sets the filtering of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaSetFiltering(lua_State* L);

		/**
		* @brief Gets the filtering of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaGetFiltering(lua_State* L);

		/**
		* @brief Sets the blend of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaSetBlend(lua_State* L);

		/**
		* @brief Gets the blend of this object
		* @param[in] L (lua_State* L)
		*/
		static int LuaGetBlend(lua_State* L);
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

		D3D11Texture* texture_;
		D3D11Shader* shader_;

		SharedPtr<D3D11VertexBuffer> vertex_buffer_;

		SharedPtr<D3D11RasterizerState> rasterizer_state_;
		SharedPtr<D3D11BlendState> blend_state_;

		TEXTURE_FILTERING_TYPE texture_filtering_;
	};
}