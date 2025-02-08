#version 330 core

in vec3 aPos;

out vec3 color;

void main() {
	gl_Position = vec4(aPos, 1.0);
	color = vec3(0.0, 0.0, 1.0);
}
