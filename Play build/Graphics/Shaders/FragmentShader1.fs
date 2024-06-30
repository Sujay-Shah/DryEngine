#version 440 core

out vec4 FragColor;
in vec2 texPos;
uniform vec4 shapeColor;
uniform sampler2D myTexture;
uniform int is_debug;

void main()
{
	FragColor = texture(myTexture,texPos);

	if(is_debug==1) {
	
		FragColor = vec4(1.0,1.0,1.0,1.0);
	} 
}