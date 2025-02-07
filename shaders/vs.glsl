#version 330 core

in vec3 aPos;

out vec4 vertexColor;

void main() {
	gl_Position = vec4(aPos, 1.0);
	vertexColor = vec4(0.0, 0.0, 1.0, 1.0);
}
