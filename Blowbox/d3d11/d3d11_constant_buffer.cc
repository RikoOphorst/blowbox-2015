#include "../../blowbox/d3d11/d3d11_constant_buffer.h"

#include "../../blowbox/d3d11/d3d11_render_device.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11ConstantBuffer::D3D11ConstantBuffer()
	{

	}

	//------------------------------------------------------------------------------------------------------
	D3D11ConstantBuffer::~D3D11ConstantBuffer()
	{

	}

	//------------------------------------------------------------------------------------------------------
	void D3D11ConstantBuffer::Create(const CONSTANT_BUFFER_TYPE& type)
	{
		HRESULT hr = S_OK;

		D3D11_BUFFER_DESC buffer_desc;
		ZeroMemory(&buffer_desc, sizeof(buffer_desc));

		buffer_desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		buffer_desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		buffer_desc.CPUAccessFlags = 0;
		buffer_desc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));

		data.pSysMem = &constant_buffer_;
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;

		if (CONSTANT_BUFFER_TYPE::CONSTANT_BUFFER_GLOBAL == type)
		{
			buffer_desc.ByteWidth = sizeof(ConstantBufferGlobal) * 4;

			hr = D3D11RenderDevice::Instance()->GetDevice()->CreateBuffer(&buffer_desc, &data, &constant_buffer_);
			BLOW_ASSERT_HR(hr, "Error while creating a global constant buffer");
		}
		else if (CONSTANT_BUFFER_TYPE::CONSTANT_BUFFER_OBJECT == type)
		{
			buffer_desc.ByteWidth = sizeof(ConstantBufferObject) * 4;

			hr = D3D11RenderDevice::Instance()->GetDevice()->CreateBuffer(&buffer_desc, &data, &constant_buffer_);
			BLOW_ASSERT_HR(hr, "Error while creating a per object constant buffer");
		}
		else
		{
			BLOW_BREAK("Could not recognize the correct constant buffer type");
		}
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11ConstantBuffer::Map(ID3D11DeviceContext* context, const ConstantBufferGlobal& info)
	{
		ConstantBufferGlobal* mapped_data = nullptr;

		D3D11_MAPPED_SUBRESOURCE data;

		D3D11RenderDevice::Instance()->GetContext()->Map(constant_buffer_, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &data);
		mapped_data = static_cast<ConstantBufferGlobal*>(data.pData);

		mapped_data->time = info.time;
		mapped_data->view = info.view;
		mapped_data->projection = info.projection;

		D3D11RenderDevice::Instance()->GetContext()->Unmap(constant_buffer_, 0);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11ConstantBuffer::Map(ID3D11DeviceContext* context, const ConstantBufferObject& info)
	{
		ConstantBufferObject* mapped_data = nullptr;

		D3D11_MAPPED_SUBRESOURCE data;

		context->Map(constant_buffer_, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &data);
		mapped_data = static_cast<ConstantBufferObject*>(data.pData);

		mapped_data->world = info.world;
		mapped_data->alpha = info.alpha;

		context->Unmap(constant_buffer_, 0);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11ConstantBuffer::Set(ID3D11DeviceContext* context, const int& index)
	{
		context->VSSetConstantBuffers(index, 1, &constant_buffer_);
		context->PSSetConstantBuffers(index, 1, &constant_buffer_);
	}
}