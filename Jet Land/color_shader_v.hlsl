// globals
cbuffer MatrixBuffer
{
    matrix world;
    matrix view;
    matrix projection;
};


// Typedef for structure which represents vertex data from vertex buffer.
struct VertexInputType
{
    float4 position : POSITION;
    //float4 color : VERTEXCOLOR;
	float2 texcoords : TEXCOORDS;
    float3 normal : NORMAL;
};

// Typedef for structure which represents VertexShader finished for PixelShader
struct PixelInputType
{
    float4 positionWVP : SV_POSITION;
	float3 positionW : POSITION;
    //float4 color : VERTEXCOLOR;
	float2 texcoords : TEXCOORDS;
	float3 normal : NORMAL;
};


PixelInputType VS(VertexInputType input)
{
    PixelInputType output;
    
	// Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
    output.positionW = mul(input.position.xyz, (float3x3)world);
    output.positionWVP = mul(mul(input.position, world), view);
    output.positionWVP = mul(output.positionWVP, projection);
    
	// Store the input color for the pixel shader to use.
    //output.color = input.color;

    output.normal = normalize(mul(input.normal, (float3x3)world));
	output.texcoords = input.texcoords;
    
    return output;
}

