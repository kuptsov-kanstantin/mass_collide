#version 330 core

// Interpolated values from the vertex shaders
in vec2 outUV;
in vec4 outColor;

// Ouput data
out vec4 finalColor;

uniform sampler2D TextureSampler;

void main(){
	// Output color = color of the texture at the specified UV
    finalColor = texture( TextureSampler, outUV ) * outColor;
    if(finalColor.a < 0.15){
		discard;
	}
}
