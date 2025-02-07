#version 330 core

// uniform vec3 color;
// in vec4 fragColor;
in vec4 vertexColor;

out vec4 FragColor;

void main() {
	// vec3 color_mix = vertexColor.xyz * gl_FragCoord.xyz / 800.0f;
	// FragColor = vec4(color_mix, 1.0);
	FragColor = vertexColor;
}
