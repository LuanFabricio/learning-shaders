#version 330 core

in vec4 fragColor;
// in vec4 vertexColor;

uniform float time;

out vec4 FragColor;

vec3 colorA = vec3(0.149, 0.141, 0.912);
vec3 colorB = vec3(1.000, 0.833, 0.224);

void main() {
	float t = abs(sin(time));
	vec3 color_mix = t * fragColor.xyz * gl_FragCoord.xyz / 800.0f;
	// float pct = abs(sin(time));
	// vec3 color_mix = mix(colorA, colorB, pct);
	FragColor = vec4(color_mix, 1.0);
}
