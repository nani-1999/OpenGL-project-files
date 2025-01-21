#version 330

layout (location = 0) in vec3 pos;
out vec4 vCol;

uniform mat4 Projection;
uniform mat4 Model;
uniform mat4 View;

void main()
{
    gl_Position = Projection * View * Model * vec4(pos, 1.0f);
	vCol = vec4(clamp(pos, 0.f, 1.f), 1.f);
}