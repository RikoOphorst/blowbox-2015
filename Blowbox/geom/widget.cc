#include "widget.h"

namespace blowbox
{
	Widget::Widget()
		: vertexBuffer_(nullptr), indexBuffer_(nullptr), D3D11RenderElement(), parent_(nullptr)
	{
		CreateBuffers();
		SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	};

	Widget::Widget(lua_State* state)
		: vertexBuffer_(nullptr), indexBuffer_(nullptr), D3D11RenderElement(), parent_(nullptr)
	{
		CreateBuffers();
		SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		D3D11DisplayDevice::Instance()->AddUIElement(this);

		void* par = LuaManager::GetValue<void*>(0);

		if (par != NULL)
		{
			LM_GETSELF(void);
			
			Widget* parent = static_cast<Widget*>(self);

			parent->AddChild(this);
			SetParent(parent);
		}
	}

	void Widget::CreateBuffers()
	{
		std::vector<Vertex> verts({
			Vertex(-0.5f, -0.5f, 0.0f, 0, 1, 0, 0, 0, 0, 0, 0),
			Vertex(-0.5f, 0.5f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(0.5f, 0.5f, 0.0f, 1, 0, 0, 0, 0, 0, 0, 0),
			Vertex(0.5f, -0.5f, 0.0f, 1, 1, 0, 0, 0, 0, 0, 0)
		});

		std::vector<int> indices({
			0, 1, 3, 2
		});

		vertexBuffer_ = D3D11DisplayDevice::Instance()->CreateVertexBuffer(verts);
		indexBuffer_ = D3D11DisplayDevice::Instance()->CreateIndexBuffer(indices);
	}

	int Widget::RegisterFunctions(lua_State* state)
	{
		luaL_Reg regist[] =
		{
			{ "getAlpha", LuaGetAlpha },
			{ "setAlpha", LuaSetAlpha },
			{ "getPosition", LuaGetPosition },
			{ "setPosition", LuaSetPosition },
			{ "getRotation", LuaGetRotation },
			{ "setRotation", LuaSetRotation },
			{ "getShader", LuaGetShader },
			{ "setShader", LuaSetShader },
			{ "getTexture", LuaGetTexture },
			{ "setTexture", LuaSetTexture },
			{ "getScale", LuaGetScale },
			{ "setScale", LuaSetScale },
			{ NULL, NULL }
		};

		LM_REGISTER(state, regist);

		return 0;
	}

	void Widget::SetParent(Widget* widget)
	{
		parent_ = widget;
	}

	Widget* Widget::GetParent()
	{
		return parent_;
	}

	void Widget::AddChild(Widget* widget)
	{
		children_.push_back(widget);
	}

	void Widget::RemoveChild(Widget* widget)
	{
		for (unsigned int i = static_cast<unsigned int>(children_.size()) - 1; i >= 0; --i)
		{
			if (children_.at(i) == widget)
			{
				children_.erase(children_.begin() + i);
			}
		}
	}

	XMMATRIX& Widget::GetWorld()
	{
		float sx = XMVectorGetX(scale_) * size_.x;
		float sy = XMVectorGetY(scale_) * size_.y;

		XMMATRIX currentTranslation = XMMatrixTranslationFromVector(position_);
		XMMATRIX currentRotation = XMMatrixRotationRollPitchYawFromVector(rotation_);
		XMMATRIX currentScaling = XMMatrixScaling(sx, sy, XMVectorGetZ(scale_));

		world_ = currentScaling * currentRotation;

		if (parent_ != nullptr)
		{
			Widget* parent = parent_;
			XMVECTOR parentTransV = XMVectorSet(0, 0, 0, 0);
			XMMATRIX parentRotation = XMMatrixIdentity();
			XMMATRIX parentScale = XMMatrixIdentity();

			while (parent->GetParent() != nullptr)
			{
				parentTransV += parent->GetPosition();
				parentRotation *= XMMatrixRotationRollPitchYawFromVector(parent->GetRotation());
				parentScale *= XMMatrixScaling(XMVectorGetX(parent->GetScale()), XMVectorGetY(parent->GetScale()), XMVectorGetZ(parent->GetScale()));
				parent = parent->GetParent();
			}

			XMMATRIX parentTransM = XMMatrixTranslationFromVector(parentTransV);
			XMMATRIX rootTrans = XMMatrixTranslationFromVector(parent->GetPosition());
			XMMATRIX rootRotation = XMMatrixRotationRollPitchYawFromVector(parent->GetRotation());
			XMMATRIX rootScaling = XMMatrixScaling(XMVectorGetX(parent->GetScale()), XMVectorGetY(parent->GetScale()), XMVectorGetZ(parent->GetScale()));

			world_ *= currentTranslation * parentScale * parentRotation * parentTransM * rootScaling * rootRotation * rootTrans;
		}
		else
		{
			world_ *= XMMatrixTranslationFromVector(position_);
		}

		return world_;
	}
	
	void Widget::Draw()
	{
		D3D11DisplayDevice::Instance()->SetVertexBuffer(vertexBuffer_);
		D3D11DisplayDevice::Instance()->SetIndexBuffer(indexBuffer_);
		D3D11DisplayDevice::Instance()->GetContext()->DrawIndexed(4, 0, 0);
	}

	Widget::~Widget()
	{
		D3D11DisplayDevice::Instance()->RemoveUIElement(this);

		vertexBuffer_->Release();
		indexBuffer_->Release();
	};
}