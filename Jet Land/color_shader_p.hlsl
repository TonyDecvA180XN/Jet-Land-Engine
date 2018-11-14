#define LIMIT_AMOUNT_OF_LIGHTS 8

// --------------------------------- CB Types Definition ----------------------

#define LIGHT_TYPE_SUN 1
#define LIGHT_TYPE_POINT 2
#define LIGHT_TYPE_SPOT 3

struct LightSourceType
{
    float4 lColor; // 4*4=16 bytes
    float3 lPosition; // 4*3=12 bytes
    float lRadius; // 4 bytes
    float3 lDirection; // 4*3=12 bytes
    float lAngle; // 4 bytes
    int lType; // 4 bytes
    int lFalloff; // 4 bytes
    bool lActive; // 4 bytes
    float _padding; // (4) bytes
	//                                   Total: 56(64)
};

struct MaterialType
{
    float4 mDiffuse;
    float4 mAmbient;
    float4 mSpecular;
    float mShininess;
    float mTransparency;
    float mMirror;
    float mIOR;
};

struct AuxiliaryBufferType
{
    float4 eyePosition;
};

// --------------------------------- CB Registration --------------------------

Texture2D my_texture;
SamplerState my_sampler;

cbuffer cbLightBuffer : register(b0)
{
    LightSourceType LightsArray[LIMIT_AMOUNT_OF_LIGHTS];
};

cbuffer cbMaterialBuffer : register(b1)
{
    MaterialType Material;
}

cbuffer cbAuxiliaryBuffer : register(b2)
{
    AuxiliaryBufferType AuxBuffer;
}

struct PixelInputType
{
    float4 positionWVP : SV_POSITION;
    float4 positionW : POSITION;
    float2 texcoords : TEXCOORDS;
    float3 normal : NORMAL;
};

// --------------------------------- Light Helper Functions -------------------

float ComputeDiffuse(float3 fallRay, float3 pixelNormal)
{
    float intensity = dot(fallRay, pixelNormal);
    return saturate(intensity);
}

float ComputeSpecular(float3 pixelPos, float3 pixelNormal, float3 fallRay, float3 eyePos, float glossiness)
{
    if (dot(fallRay, pixelNormal) > 0.0f)
    {
        float3 eyeRay = normalize(eyePos - pixelPos);
        float3 reflectedRay = normalize(-fallRay - 2 * dot(-fallRay, pixelNormal) * pixelNormal);
        float intensity = saturate(dot(eyeRay, reflectedRay));
        intensity = pow(intensity, glossiness);
        return intensity;
    }
    return 0.0f;
}

struct LightResult
{
    float4 Diffuse;
    float4 Specular;
};

LightResult SolveDirectionalLight(LightSourceType light, float3 pixelPos, float3 pixelNormal, float3 eyePos)
{
    float3 fallRay = normalize(-light.lDirection);

    LightResult result;
    result.Diffuse = light.lColor * ComputeDiffuse(fallRay, pixelNormal);
    result.Specular = light.lColor * ComputeSpecular(pixelPos, pixelNormal, fallRay, eyePos.xyz, Material.mShininess);

    return result;
}

LightResult SolvePointLight(LightSourceType light, float3 pixelPos, float3 pixelNormal, float3 eyePos)
{
    float3 fallRay = normalize(light.lPosition - pixelPos);

    LightResult result;
    result.Diffuse = light.lColor * ComputeDiffuse(fallRay, pixelNormal);
    result.Specular = light.lColor * ComputeSpecular(pixelPos, pixelNormal, fallRay, eyePos.xyz, Material.mShininess);

    return result;
}

float4 main(PixelInputType inputPixel) : SV_TARGET
{
    LightResult lightingResult;
    for (uint i = 0; i < LIMIT_AMOUNT_OF_LIGHTS; ++i)
    {
        if (LightsArray[i].lActive)
        {
            LightResult current;
            current.Diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
            current.Specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

            switch (LightsArray[i].lType)
            {
                case LIGHT_TYPE_SUN:
			{
                        current = SolveDirectionalLight(LightsArray[i], inputPixel.positionW.xyz, inputPixel.normal, AuxBuffer.eyePosition.xyz);
                        break;
                    }
                case LIGHT_TYPE_POINT:
			{
                        current = SolvePointLight(LightsArray[i], inputPixel.positionW.xyz, inputPixel.normal, AuxBuffer.eyePosition.xyz);
                        break;
                    }
                default:
			{
                        break;
                    }
            }
            lightingResult.Diffuse += current.Diffuse;
            lightingResult.Specular += current.Specular;
        }
    }

    float4 textureColor = my_texture.Sample(my_sampler, inputPixel.texcoords);
    float4 finalDiffuse = saturate(lightingResult.Diffuse) * Material.mDiffuse;
    float4 finalSpecular = saturate(lightingResult.Specular) * Material.mSpecular;
    float4 finalAmbient = Material.mAmbient;

    float4 finalColor = finalDiffuse + finalSpecular + finalAmbient;
    if (any(textureColor))
    {
        finalColor *= textureColor;
    }

    return finalColor;
}