cbuffer ConstantBuffer
{
    float4x4 WVP;
	float4x4 World;  
	float4x4 WorldView;
	float4x4 WVPInverse;
	float4x4 WVPLight;
	float4	 LightPositions[128];
	float4	 LightColors[128];
	float4   CameraPosition;
	float4 	 CameraInfo;
	float4	 LightCameraPosition;
	float4 	 LightCameraInfo;
}

struct VS_OUTPUT
{
    float4 hposition	: SV_POSITION;
    float2 texture0		: TEXCOORD;
	float4 Pos			: TEXCOORD1;
	float4 PosCorner	: VPOS;
};

SamplerState SS;

#ifdef DEFERRED_PASS
Texture2D tex0 : register(t0);
Texture2D tex1 : register(t1);
Texture2D tex2 : register(t2);
Texture2D tex3 : register(t3);
Texture2D tex4 : register(t4);
Texture2D tex5 : register(t5);

float4 FS( VS_OUTPUT input ) : SV_TARGET
{
	float4 Final	= float4(0.0,0.0,0.0,1.0);
	float4 color	= tex0.Sample( SS, input.texture0);
	float4 matId	= tex3.Sample( SS, input.texture0);
 	
	if(matId.r == 1.0 && matId.g == 0.0)
	{
		Final = color;
	}
	else
	{
		////////////////////////////////////77
		Final = color*0.2;
		////////////////////////////////////77

		float Rad = 15.0;
		float cutoff = 0.8;
		float4 Lambert = float4(1.0,1.0,1.0,1.0);
		float4 Specular = float4(1.0,1.0,1.0,1.0);
		float4 Fresnel	 =  float4(1.0,1.0,1.0,1.0);
		float4 normalmap = tex1.Sample( SS, input.texture0);
		float4 normal = normalmap*2.0 - 1.0;
		
		float2 distor = float2(normalmap.xy);	

		if(matId.b == 1.0)
		{
			distor = float2(1.0,1.0);
		}	

		float4 ReflectCol = tex0.Sample( SS, input.texture0*distor);
		
		float4 specularmap = tex2.Sample( SS, input.texture0);
		normal	= normalize(normal);

		float depth = tex4.Sample( SS, input.texture0 );
		float4 position = CameraPosition + input.PosCorner*depth;
		
		float3  EyeDir   = normalize(CameraPosition-position).xyz;
		
		int NumLights = (int)CameraInfo.w;
		for (int i = 0; i < NumLights; i++)
			{
				float dist = distance(LightPositions[i], position);
				if(dist < Rad*2.0)
				{
					Lambert  = LightColors[i];
					Specular = LightColors[i];
					Fresnel	 =  LightColors[i];			
					
					float3	LightDir = normalize(LightPositions[i]-position).xyz;
					float   att		 = 1.0;
					att		 	     = dot(normal.xyz,LightDir)*0.5 + 0.5;;
					att				 = pow( att , 2.0 );	
					att				 = clamp( att , 0.0 , 1.0 );
					Lambert			*= color*att;
					
					float  specular  = 0.0;
					float specIntesivity = 1.5;
					float shinness = 4.0;	
					shinness = normal.a + shinness;
					
					float3 ReflectedLight = normalize(EyeDir+LightDir); 
					specular = max ( dot(ReflectedLight,normal.xyz)*0.5 + 0.5, 0.0);	
					specular = pow( specular ,shinness);	

					specular *= att;
					specular *= specIntesivity;
					Specular *= specular;
					Specular.xyz *= specularmap.xyz;
									
					float d = max(dist - Rad, 0.0);
					float denom = d/Rad + 1.0;
					
					float attenuation = 1.0 / (denom*denom);
					 
					attenuation = (attenuation - cutoff) / (1.0 - cutoff);
					attenuation = max(attenuation, 0.0);
						
					Final += Lambert*attenuation;
					Final += Specular*attenuation;
				}
			}
		if(matId.b == 0.0)
		{
			float  FresnelAtt	= dot(normal.xyz,EyeDir);
			float  FresnelIntensity = 1.0f;
			float4 FresnelCol = float4(ReflectCol.xyz,1.0);

			FresnelAtt		= abs(FresnelAtt);
			FresnelAtt 		= 1.0 - FresnelAtt;
			FresnelAtt 		= clamp( FresnelAtt , 0.0 , 1.0 );
			FresnelAtt		= pow( FresnelAtt , 4.0 );	
			FresnelAtt 		= clamp(FresnelAtt , 0.0 , 1.0 );
			Fresnel 		= FresnelCol*FresnelIntensity*FresnelAtt;
		
			Final += Fresnel;
		}
		
		Final.xyz *= tex5.Sample( SS, input.texture0).xyz;
	}

	return Final;

}

#elif defined(SHADOW_COMP_PASS)
Texture2D tex0 : register(t0);
Texture2D tex1 : register(t1);

float4 FS( VS_OUTPUT input ) : SV_TARGET
{
	float4	Fcolor	 = float4(1.0,1.0,1.0,1.0);
	float	depth	 = tex0.Sample( SS, input.texture0 );
	float4	position = CameraPosition + input.PosCorner*depth;
	
	float4 LightPos	 = mul(WVPLight, position);
	LightPos.xy		/= LightPos.w;
	LightPos.z		/= LightCameraInfo.y;
	float2 SHTC		 = LightPos.xy*0.5 + 0.5;
	
	if (SHTC.x < 1.0 && SHTC.y < 1.0 && SHTC.x  > 0.0 && SHTC.y > 0.0 && LightPos.w > 0.0 && LightPos.z < 1.0)
	{
		SHTC.y = 1.0 - SHTC.y;
		float depthSM = tex1.Sample( SS, SHTC );
		float depthPos = LightPos.z;
		depthSM += 0.000005;
		if (depthPos > depthSM)
			Fcolor = 0.25*float4(1.0, 1.0, 1.0, 1.0);
	}
	else
	{
		Fcolor = float4(1.0,1.0,1.0,1.0);
	}
	
	return Fcolor;
}
#elif defined(VERTICAL_BLUR_PASS)
Texture2D tex0 : register(t0);
float4 FS(VS_OUTPUT input) : SV_TARGET{
	float offset = 1.0 / 720.0;
	int pix = 3;
	float blur[7];
	blur[0] = 0.00038771*2.2;
	blur[1] = 0.01330373*2.2;
	blur[2] = 0.11098164*2.2;
	blur[3] = 0.22508352*2.2;
	blur[4] = 0.11098164*2.2;
	blur[5] = 0.01330373*2.2;
	blur[6] = 0.00038771*2.2;
	float4 color = 0;
	for (int i = pix; i > 0; i--)
	{
		float4 tempcolor = 0;
		float2 temp = float2(input.texture0.r, input.texture0.g - i * offset);
		tempcolor = tex0.Sample(SS, temp);
		color += tempcolor *blur[i - 1];

	}

	for (int i = pix; i > 0; i--)
	{
		float4 tempcolor = 0;
		float2 temp = float2(input.texture0.r, input.texture0.g + i * offset);
		tempcolor = tex0.Sample(SS, temp);
		color += tempcolor *blur[i - 1];

	}
	color += tex0.Sample(SS, input.texture0);
	color = color *blur[3];

	//color = tex0.Sample(SS, input.texture0);
	return color;
}
#elif defined(HORIZONTAL_BLUR_PASS)
Texture2D tex0 : register(t0);
float4 FS(VS_OUTPUT input) : SV_TARGET{
	float offset = 1.0 / 1280.0;
	int pix = 3;
	float blur[7];
	blur[0] = 0.00038771*2.2;
	blur[1] = 0.01330373*2.2;
	blur[2] = 0.11098164*2.2;
	blur[3] = 0.22508352*2.2;
	blur[4] = 0.11098164*2.2;
	blur[5] = 0.01330373*2.2;
	blur[6] = 0.00038771*2.2;

	float4 color = 0;
	for (int i = pix; i > 0; i--)
	{
		float4 tempcolor = 0;
		float2 temp = float2(input.texture0.r - i * offset, input.texture0.g);
		tempcolor = tex0.Sample(SS, temp);
		color += tempcolor *blur[i - 1];
	}

	for (int i = pix; i > 0; i--)
	{
		float4 tempcolor = 0;
		float2 temp = float2(input.texture0.r + i * offset, input.texture0.g);
		tempcolor = tex0.Sample(SS, temp);
		color += tempcolor *blur[i - 1];
	}
	color += tex0.Sample(SS, input.texture0);
	color = color *blur[3];

	return color;
}
#elif defined(BRIGHT_PASS)
Texture2D tex0 : register(t0);
float4 FS(VS_OUTPUT input) : SV_TARGET{
	float4 color = tex0.Sample(SS, input.texture0);
	float FLum = dot(color.rgb, float3(0.299f, 0.587f, 0.114f));

	if (FLum < 0.2)
		color = float4(0.0,0.0,0.0,1.0);

	return color;


}
#elif defined(FSQUAD_1_TEX)
Texture2D tex0 : register(t0);

float4 FS( VS_OUTPUT input ) : SV_TARGET
{
	return tex0.Sample( SS, input.texture0);
}
#elif defined(HDR_COMP_PASS)
Texture2D tex0 : register(t0);
Texture2D tex1 : register(t1);
float4 FS(VS_OUTPUT input) : SV_TARGET{
	int mip = 10;
	float4 color = tex0.Sample(SS, input.texture0);
	float avgLuminance = dot(tex0.SampleLevel(SS, input.texture0 , mip).rgb , float3(0.299f, 0.587f, 0.114f));
	float exposure = 0;

	avgLuminance = max(avgLuminance, 0.001f);
	float keyValue = 0;
	keyValue = 1.03f - (2.0f / (2 + log10(avgLuminance + 1)));

	float linearExposure = (keyValue / avgLuminance);
	exposure = log2(max(linearExposure, 0.0001f));
	color = exp2(exposure) * color;


	float pixelLuminance = max(dot(color.rgb, float3(0.299f, 0.587f, 0.114f)), 0.0001f);
	
	float toneMappedLuminance = log10(1 + pixelLuminance) / log10(1.0 + 0.3);
	color = toneMappedLuminance * pow(color / pixelLuminance, 1.0f);
	color.a = 1.0;
	return color + 1.1*tex1.Sample(SS, input.texture0);
}
#elif defined(FSQUAD_2_TEX)
Texture2D tex0 : register(t0);
Texture2D tex1 : register(t1);

float4 FS( VS_OUTPUT input ) : SV_TARGET
{
	return tex0.Sample( SS, input.texture0) + tex1.Sample(SS, input.texture0);
}

#elif defined(FSQUAD_3_TEX)
Texture2D tex0 : register(t0);
Texture2D tex1 : register(t1);
Texture2D tex2 : register(t2);

float4 FS( VS_OUTPUT input ) : SV_TARGET
{
	return tex0.Sample( SS, input.texture0);
}

#else
Texture2D tex0 : register(t0);

float4 FS( VS_OUTPUT input ) : SV_TARGET
{
	return tex0.Sample( SS, input.texture0);
}
#endif