#include "../../blowbox/d3d11/d3d11_input_layout.h"

#include "../../blowbox/d3d11/d3d11_render_device.h"
#include "../../blowbox/d3d11/d3d11_shader.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11InputLayout::D3D11InputLayout(D3D11_INPUT_ELEMENT_DESC* input_layout_desc, UINT stride, D3D11Shader* shader) :
		input_layout_(nullptr)
	{
		UINT amount_elements = stride / sizeof(D3D11_INPUT_ELEMENT_DESC);

		HRESULT hr = S_OK;
		hr = D3D11RenderDevice::Instance()->GetDevice()->CreateInputLayout(&input_layout_desc[0], amount_elements, shader->GetVertexShaderBuffer()->GetBufferPointer(), shader->GetVertexShaderBuffer()->GetBufferSize(), &input_layout_);
		BLOW_ASSERT_HR(hr, "Error while creating input layout");
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11InputLayout::Set(ID3D11DeviceContext* context)
	{
		ID3D11InputLayout* current_layout;
		context->IAGetInputLayout(&current_layout);

		if (current_layout != input_layout_)
		{
			context->IASetInputLayout(input_layout_);
		}
	}

	//------------------------------------------------------------------------------------------------------
	D3D11InputLayout::~D3D11InputLayout()
	{
		BLOW_SAFE_RELEASE(input_layout_);
	}
}