Texture2D my_texture;
SamplerState my_sampler;

cbuffer LightBuffer
{
	
	float4 color;                           // 4*4=16 bytes
	float3 position;                        // 4*3=12 bytes
	float radius;                           // 4 bytes
	float3 direction1;                      // 4*3=12 bytes
	float angle;                            // 4 bytes
	int type;                               // 4 bytes
	int falloff;                            // 4 bytes
	float2 _padding;                        // (8) bytes
	//                                      Total: 56(64)
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	//float4 color : VERTEXCOLOR;
	float2 texcoords : TEXCOORDS;
	float3 normal : NORMAL;
};

float4 PS(PixelInputType inputPixel) : SV_TARGET
{
	float4 texColor = my_texture.Sample(my_sampler, inputPixel.texcoords);
	float3 inputRay = normalize(-direction1);
	float3 l = saturate(direction1);
	float i = saturate(dot(inputRay, normalize(inputPixel.normal)));
	return saturate(0.2f + 0.8f * i) * texColor;
	//return saturate(float4(position / 9, 1));
		/*if (color.x == 3)
			return float4(1, 1, 1, 1);
		else
			return float4(0, 0, 0, 1);*/
}