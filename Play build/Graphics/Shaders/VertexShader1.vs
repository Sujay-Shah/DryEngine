#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) uniform mat4 uTrans;
layout (location = 2) in vec2 texCoord;

out vec2 texPos;
void main() 
{
	gl_Position = uTrans*vec4(aPos,1.0);
	texPos=texCoord;

}

