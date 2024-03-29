#include "../../blowbox/d3d11/d3d11_render_element.h"

#include "../../blowbox/d3d11/d3d11_texture.h"
#include "../../blowbox/d3d11/d3d11_vertex_buffer.h"
#include "../../blowbox/d3d11/d3d11_sampler_state.h"
#include "../../blowbox/d3d11/d3d11_shader.h"
#include "../../blowbox/d3d11/d3d11_rasterizer_state.h"
#include "../../blowbox/d3d11/d3d11_blend_state.h"
#include "../../blowbox/d3d11/d3d11_render_queue.h"
#include "../../blowbox/content/content_manager.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11RenderElement::D3D11RenderElement() :
		position_(0.0f, 0.0f, 0.0f),
		v_position_(XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f)),
		rotation_(0.0f, 0.0f, 0.0f),
		v_rotation_(XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f)),
		scaling_(1.0f, 1.0f, 1.0f),
		v_scaling_(XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f)),
		offset_(0.0f, 0.0f, 0.0f),
		v_offset_(XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f)),
		alpha_(1),
		texture_filtering_(TEXTURE_FILTERING_TYPE::TEXTURE_ANISOTROPIC),
		type_(RENDER_ELEMENT_TYPE::RENDER_ELEMENT_MISC),
		render_queue_(nullptr)
	{
		rasterizer_state_ = new D3D11RasterizerState();
		blend_state_ = new D3D11BlendState();

		SetShader(BLOW_BASE_SHADER);
		SetTexture(BLOW_BASE_TEXTURE);
	}

	//------------------------------------------------------------------------------------------------------
	D3D11RenderElement::D3D11RenderElement(lua_State* L) :
		position_(0.0f, 0.0f, 0.0f),
		v_position_(XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f)),
		rotation_(0.0f, 0.0f, 0.0f),
		v_rotation_(XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f)),
		scaling_(1.0f, 1.0f, 1.0f),
		v_scaling_(XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f)),
		offset_(0.0f, 0.0f, 0.0f),
		v_offset_(XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f)),
		alpha_(1),
		texture_filtering_(TEXTURE_FILTERING_TYPE::TEXTURE_ANISOTROPIC),
		type_(RENDER_ELEMENT_TYPE::RENDER_ELEMENT_MISC),
		render_queue_(nullptr)
	{
		rasterizer_state_ = new D3D11RasterizerState();
		blend_state_ = new D3D11BlendState();

		SetShader(BLOW_BASE_SHADER);
		SetTexture(BLOW_BASE_TEXTURE);
	}

	//------------------------------------------------------------------------------------------------------
	D3D11RenderElement::~D3D11RenderElement()
	{
		render_queue_->Remove(this);
	}

	//------------------------------------------------------------------------------------------------------
	const XMVECTOR& D3D11RenderElement::GetPosition() const
	{
		return v_position_;
	}

	//------------------------------------------------------------------------------------------------------
	const float& D3D11RenderElement::GetX() const
	{
		return position_.x;
	}

	//------------------------------------------------------------------------------------------------------
	const float& D3D11RenderElement::GetY() const
	{
		return position_.y;
	}

	//------------------------------------------------------------------------------------------------------
	const float& D3D11RenderElement::GetZ() const
	{
		return position_.z;
	}

	//------------------------------------------------------------------------------------------------------
	const XMVECTOR& D3D11RenderElement::GetRotation() const
	{
		return v_rotation_;
	}

	//------------------------------------------------------------------------------------------------------
	const XMVECTOR& D3D11RenderElement::GetScale() const
	{
		return v_scaling_;
	}

	//------------------------------------------------------------------------------------------------------
	const XMVECTOR& D3D11RenderElement::GetOffset() const
	{
		return v_offset_;
	}

	//------------------------------------------------------------------------------------------------------
	const double& D3D11RenderElement::GetAlpha() const
	{
		return alpha_;
	}

	//------------------------------------------------------------------------------------------------------
	D3D11Texture* D3D11RenderElement::GetTexture()
	{
		return texture_;
	}

	//------------------------------------------------------------------------------------------------------
	D3D11Shader* D3D11RenderElement::GetShader()
	{
		return shader_;
	}

	//------------------------------------------------------------------------------------------------------
	D3D11VertexBuffer* D3D11RenderElement::GetVertexBuffer()
	{
		return vertex_buffer_.get();
	}

	//------------------------------------------------------------------------------------------------------
	const RENDER_ELEMENT_TYPE& D3D11RenderElement::GetType()
	{
		return type_;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetPosition(float x, float y, float z)
	{
		position_.x = x;
		position_.y = y;
		position_.z = z;

		CalculatePosition();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetPosition(double x, double y, double z)
	{
		position_.x = static_cast<float>(x);
		position_.y = static_cast<float>(y);
		position_.z = static_cast<float>(z);

		CalculatePosition();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetX(float x)
	{
		position_.x = x;
		CalculatePosition();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetX(double x)
	{
		position_.x = static_cast<float>(x);
		CalculatePosition();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetY(float y)
	{
		position_.y = y;
		CalculatePosition();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetY(double y)
	{
		position_.y = static_cast<float>(y);
		CalculatePosition();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetZ(float z)
	{
		position_.z = z;
		CalculatePosition();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetZ(double z)
	{
		position_.z = static_cast<float>(z);
		CalculatePosition();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetRotation(float x, float y, float z)
	{
		rotation_.x = x;
		rotation_.y = y;
		rotation_.z = z;
		CalculateRotation();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetRotation(double x, double y, double z)
	{
		rotation_.x = static_cast<float>(x);
		rotation_.y = static_cast<float>(y);
		rotation_.z = static_cast<float>(z);
		CalculateRotation();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetScale(float x, float y, float z)
	{
		scaling_.x = x;
		scaling_.y = y;
		scaling_.z = z;
		CalculateScaling();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetScale(double x, double y, double z)
	{
		scaling_.x = static_cast<float>(x);
		scaling_.y = static_cast<float>(y);
		scaling_.z = static_cast<float>(z);
		CalculateScaling();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetOffset(float x, float y, float z)
	{
		offset_.x = x;
		offset_.y = y;
		offset_.z = z;
		CalculateOffset();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetOffset(double x, double y, double z)
	{
		offset_.x = static_cast<float>(x);
		offset_.y = static_cast<float>(y);
		offset_.z = static_cast<float>(z);
		CalculateOffset();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetAlpha(double alpha)
	{
		alpha_ = alpha;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetAlpha(float alpha)
	{
		alpha_ = static_cast<double>(alpha);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetTexture(std::string path)
	{
		texture_ = ContentManager::Instance()->GetTexture(path);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetShader(std::string path)
	{
		shader_ = ContentManager::Instance()->GetShader(path);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::CalculatePosition()
	{
		v_position_ = XMVectorSet(position_.x, position_.y, position_.z, 1.0f);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::CalculateRotation()
	{
		v_rotation_ = XMVectorSet(rotation_.x, rotation_.y, rotation_.z, 1.0f);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::CalculateScaling()
	{
		v_scaling_ = XMVectorSet(scaling_.x, scaling_.y, scaling_.z, 1.0f);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::CalculateOffset()
	{
		v_offset_ = XMVectorSet(offset_.x, offset_.y, offset_.z, 1.0f);
	}

	//------------------------------------------------------------------------------------------------------
	XMMATRIX& D3D11RenderElement::GetWorld()
	{
		world_matrix_ =
			XMMatrixScalingFromVector(v_scaling_) *
			XMMatrixTranslationFromVector(v_offset_ * v_scaling_) *
			XMMatrixRotationRollPitchYawFromVector(v_rotation_) *
			XMMatrixTranslationFromVector(v_position_);

		return world_matrix_;
	}

	//------------------------------------------------------------------------------------------------------
	const TEXTURE_FILTERING_TYPE& D3D11RenderElement::GetFilteringType() const
	{
		return texture_filtering_;
	}

	//------------------------------------------------------------------------------------------------------
	D3D11RasterizerState* D3D11RenderElement::GetRasterizerState()
	{
		return rasterizer_state_.get();
	}

	//------------------------------------------------------------------------------------------------------
	D3D11BlendState* D3D11RenderElement::GetBlendState()
	{
		return blend_state_.get();
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaSetPosition(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		self->SetPosition(
			LuaWrapper::Instance()->Get<double>(L, 2),
			LuaWrapper::Instance()->Get<double>(L, 3),
			LuaWrapper::Instance()->Get<double>(L, 4)
			);

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaGetPosition(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		XMFLOAT4 pos;
		XMStoreFloat4(&pos, self->GetPosition());

		return LuaWrapper::Instance()->Push(L, pos.x, pos.y, pos.z);
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaSetPosition2D(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		self->SetPosition(
			LuaWrapper::Instance()->Get<double>(L, 2),
			LuaWrapper::Instance()->Get<double>(L, 3),
			0
			);

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaGetPosition2D(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		XMFLOAT4 pos;
		XMStoreFloat4(&pos, self->GetPosition());

		return LuaWrapper::Instance()->Push(L, pos.x, pos.y, pos.z);
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaSetX(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		self->SetX(LuaWrapper::Instance()->Get<double>(L, 2));

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaGetX(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);
		return LuaWrapper::Instance()->Push(L, self->GetX());
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaSetY(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		self->SetY(LuaWrapper::Instance()->Get<double>(L, 2));

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaGetY(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);
		return LuaWrapper::Instance()->Push(L, self->GetY());
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaSetZ(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		self->SetZ(LuaWrapper::Instance()->Get<double>(L, 2));

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaGetZ(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);
		return LuaWrapper::Instance()->Push(L, self->GetZ());
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaSetRotation(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		self->SetRotation(
			LuaWrapper::Instance()->Get<double>(L, 2),
			LuaWrapper::Instance()->Get<double>(L, 3),
			LuaWrapper::Instance()->Get<double>(L, 4)
			);

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaGetRotation(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		XMFLOAT4 rot;
		XMStoreFloat4(&rot, self->GetRotation());

		return LuaWrapper::Instance()->Push(L, rot.x, rot.y, rot.z);
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaSetRotation2D(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		self->SetRotation(
			0,
			0,
			LuaWrapper::Instance()->Get<double>(L, 2)
			);

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaGetRotation2D(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		XMFLOAT4 rot;
		XMStoreFloat4(&rot, self->GetRotation());

		return LuaWrapper::Instance()->Push(L, rot.z);
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaSetScale(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		self->SetScale(
			LuaWrapper::Instance()->Get<double>(L, 2),
			LuaWrapper::Instance()->Get<double>(L, 3),
			LuaWrapper::Instance()->Get<double>(L, 4)
			);

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaGetScale(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		XMFLOAT4 pos;
		XMStoreFloat4(&pos, self->GetScale());

		return LuaWrapper::Instance()->Push(L, pos.x, pos.y, pos.z);
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaSetScale2D(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		self->SetScale(
			LuaWrapper::Instance()->Get<double>(L, 2),
			LuaWrapper::Instance()->Get<double>(L, 3),
			1
			);

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaGetScale2D(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		XMFLOAT4 pos;
		XMStoreFloat4(&pos, self->GetScale());

		return LuaWrapper::Instance()->Push(L, pos.x, pos.y, pos.z);
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaSetOffset(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		self->SetOffset(
			LuaWrapper::Instance()->Get<double>(L, 2),
			LuaWrapper::Instance()->Get<double>(L, 3),
			LuaWrapper::Instance()->Get<double>(L, 4)
			);

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaGetOffset(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		XMFLOAT4 pos;
		XMStoreFloat4(&pos, self->GetOffset());

		return LuaWrapper::Instance()->Push(L, pos.x, pos.y, pos.z);
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaSetOffset2D(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		self->SetOffset(
			LuaWrapper::Instance()->Get<double>(L, 2),
			LuaWrapper::Instance()->Get<double>(L, 3),
			0
			);

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaGetOffset2D(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		XMFLOAT4 pos;
		XMStoreFloat4(&pos, self->GetOffset());

		return LuaWrapper::Instance()->Push(L, pos.x, pos.y, pos.z);
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaSetAlpha(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		self->SetAlpha(LuaWrapper::Instance()->Get<double>(L, 2));

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaGetAlpha(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);
		return LuaWrapper::Instance()->Push(L, self->GetAlpha());
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaSetTexture(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		self->SetTexture(LuaWrapper::Instance()->Get<std::string>(L, 2));

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaGetTexture(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);
		return LuaWrapper::Instance()->Push(L, "");
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaSetShader(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		self->SetShader(LuaWrapper::Instance()->Get<std::string>(L, 2));

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaGetShader(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);
		return LuaWrapper::Instance()->Push(L, "");
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaSetFiltering(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		// @todo Implement filter setting on D3D11RenderElement::LuaSetFiltering

		//self->S(LuaWrapper::Instance()->Get<std::string>(L, -1));

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaGetFiltering(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);
		return LuaWrapper::Instance()->Push(L, "");
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaSetBlend(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);

		// @todo Implement blend setting on D3D11RenderElement::LuaSetBlend

		//self->S(LuaWrapper::Instance()->Get<std::string>(L, -1));

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderElement::LuaGetBlend(lua_State* L)
	{
		D3D11RenderElement* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 1);
		return LuaWrapper::Instance()->Push(L, "");
	}
}