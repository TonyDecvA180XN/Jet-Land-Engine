Texture2D my_texture;
SamplerState my_sampler;

cbuffer LightBuffer
{
	
	float4 lColor;                           // 4*4=16 bytes
	float3 lPosition;                        // 4*3=12 bytes
	float lRadius;                           // 4 bytes
	float3 lDirection;                       // 4*3=12 bytes
	float lAngle;                            // 4 bytes
	int lType;                               // 4 bytes
	int lFalloff;                            // 4 bytes
	float2 _padding;                         // (8) bytes
	//                                   Total: 56(64)
};

struct PixelInputType
{
	float4 positionWVP : SV_POSITION;
	float3 positionW : POSITION;
	float2 texcoords : TEXCOORDS;
	float3 normal : NORMAL;
};

float4 PS(PixelInputType inputPixel) : SV_TARGET
{
	/*float4 texColor = my_texture.Sample(my_sampler, inputPixel.texcoords);
	float3 inputRay = normalize(-direction1);
	float3 l = saturate(direction1);
	float i = saturate(dot(inputRay, normalize(inputPixel.normal)));
	return saturate(0.2f + 0.8f * i) * texColor;*/

	float intensity = 1.0f;
	float4 textureColor;
	float4 lightColor;
	float4 outputColor;

	lightColor = lColor;
	textureColor = my_texture.Sample(my_sampler, inputPixel.texcoords);
	switch (lType)
	{
	case 0: // sun
	{
		float3 inputRay = -lDirection;
		intensity = dot(inputRay, inputPixel.normal);
		intensity = saturate(intensity); // optimize ifn't need
		break;
	}
	case 1: // point
	{
		float3 inputRay = normalize(inputPixel.positionW - lPosition);
		intensity = dot(inputRay, inputPixel.normal);
		intensity = saturate(intensity); // optimize ifn't need
		break;
	}
	case 2: // spot
	{
		break;
	}
	}

	outputColor = textureColor * lightColor * intensity;
	return outputColor;
}