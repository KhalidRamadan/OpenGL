#version 330 core
layout(location = 0) in vec3 aPos;

layout(location = 1) in vec3 aColor;

out vec3 ourColor;

uniform float offset1;

void main()
{
	gl_Position = vec4(aPos.x + offset1, aPos.y, aPos.z, 1.0);
	ourColor = vec3(aPos.x + offset1, aPos.y, aPos.z);
}