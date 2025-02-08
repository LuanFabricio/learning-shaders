#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <raylib.h>

typedef struct {
	Shader shader;
	int fsColorLoc;
	int fsTimeLoc;
} ShaderData;

ShaderData initShader(char* vsFile, char* fsFile)
{
	Shader shader = LoadShader(vsFile, fsFile);

	int fsColorLoc = GetShaderLocationAttrib(shader, "vertexColor");
	// SetShaderValue(shader, fsColorLoc, (float[3]){1.0, 0.0, 0.0}, SHADER_UNIFORM_VEC3);
	// SetShaderValue(shader, fsColorLoc, (float[3]){1.0, 0.0, 0.0}, SHADER_UNIFORM_VEC3);

	// float vertexPos[12] = {
	// 	100.0f, 0.0f, 0.0f,
	// 	500.0f, 0.0f, 0.0f,
	// 	500.0f, 500.0f, 0.0f,
	// 	100.0f, 500.0f, 0.0f,
	// };
	// SetShaderValueV(shader, fsColorLoc, vertexPos, SHADER_UNIFORM_VEC3, 4);
	int fsTimeLoc = GetShaderLocation(shader, "time");

	ShaderData shader_data = {
		.shader = shader,
		.fsColorLoc = fsColorLoc,
		.fsTimeLoc = fsTimeLoc,
	};
	if (IsShaderValid(shader_data.shader)) {
		printf("This shader is valid.\n");
	}

	return shader_data;
}

int main(void) {
	InitWindow(800, 600, "Learning shaders");

	char *vsPath = NULL; // "shaders/vs.glsl";
	char *fsPath = "shaders/fs.glsl";
	ShaderData shader_data = initShader(vsPath, fsPath);

	int i = 100;
	int posx = 200;
	int tick = 0;

	SetTargetFPS(75);
	while (!WindowShouldClose()) {
		if (IsKeyPressed(KEY_R)) {
			UnloadShader(shader_data.shader);
			shader_data = initShader(vsPath, fsPath);
		}

		ClearBackground(BLUE);
		BeginDrawing();
			BeginShaderMode(shader_data.shader);

			DrawRectangle(posx, 100, 400, 400, WHITE);

			EndShaderMode();
		EndDrawing();


		SetShaderValue(shader_data.shader,
				shader_data.fsTimeLoc,
				(float[1]){GetTime()}, SHADER_UNIFORM_FLOAT
			);

		float dt = GetFrameTime();
		posx += i * dt;
		// printf("Pos x: %i (%i)\n", posx, posx + i);
		// printf("Frame Time: %lf (%lf)\n", dt, i*dt);
		if ((posx + 400 >= 800) || (posx < 0)) i = -i;
		tick += 1;
	}

	return 0;
}
