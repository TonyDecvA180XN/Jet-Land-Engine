#define MAX_LIGHTS_PER_LOCATION_COUNT 8

Texture2D my_texture;
SamplerState my_sampler;

cbuffer cbLightBuffer : register (b0)
{
	struct LightSrc
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
	} lights[MAX_LIGHTS_PER_LOCATION_COUNT];
};

cbuffer cbMaterialBuffer : register (b1)
{
	float4 mDiffuse;
	float4 mAmbient;
	float4 mSpecular;
	float mRoughness;
	float mTransparency;
	float mMirror;
	float mIOR;
}

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

	float f_intensity = 0.0f;
	float4 f_textureColor = my_texture.Sample(my_sampler, inputPixel.texcoords);
	float4 f_lightColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float4 outputColor;


	for (uint iL = 0; iL < MAX_LIGHTS_PER_LOCATION_COUNT; ++iL)
	{
		float intensity = 0.0f;
		float3 lightColor = lights[iL].lColor.rgb;
		switch (lights[iL].lType)
		{
		case 1: // sun
		{
			float3 inputRay = -lights[iL].lDirection;
			intensity = dot(inputRay, inputPixel.normal);
			intensity = saturate(intensity); // optimize ifn't need
			break;
		}
		case 2: // point
		{
			float3 inputRay = normalize(lights[iL].lPosition - inputPixel.positionW);
			intensity = dot(inputRay, inputPixel.normal);
			intensity = saturate(intensity); // optimize ifn't need
			break;
		}
		case 3: // spot
		{
			break;
		}
		default:
		{
			break;
		}
		}
		if (intensity > f_intensity) f_intensity = intensity;
		if (lightColor.r > f_lightColor.r) f_lightColor.r = lightColor.r;
		if (lightColor.g > f_lightColor.g) f_lightColor.g = lightColor.g;
		if (lightColor.b > f_lightColor.b) f_lightColor.b = lightColor.b;
	}
	outputColor = f_textureColor * (mDiffuse * f_lightColor * f_intensity + mAmbient);
	return outputColor;
}