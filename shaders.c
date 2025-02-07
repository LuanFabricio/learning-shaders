#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <raylib.h>

typedef struct {
	Shader shader;
	int fsColorLoc;
} ShaderData;

ShaderData initShader(char* vsFile, char* fsFile)
{
	Shader shader = LoadShader(vsFile, fsFile);

	int fsColorLoc = GetShaderLocationAttrib(shader, "aPos");
	// SetShaderValue(shader, fsColorLoc, (float[3]){1.0, 0.0, 0.0}, SHADER_UNIFORM_VEC3);
	SetShaderValue(shader, fsColorLoc, (float[3]){1.0, 0.0, 0.0}, SHADER_UNIFORM_VEC3);
	shader.locs[SHADER_LOC_VERTEX_POSITION] = fsColorLoc;

	float vertexPos[12] = {
		100.0f, 0.0f, 0.0f,
		500.0f, 0.0f, 0.0f,
		500.0f, 500.0f, 0.0f,
		100.0f, 500.0f, 0.0f,
	};
	SetShaderValueV(shader, fsColorLoc, vertexPos, SHADER_UNIFORM_VEC3, 4);


	ShaderData shader_data = {
		.shader = shader,
		.fsColorLoc = fsColorLoc,
	};
	if (IsShaderValid(shader_data.shader)) {
		printf("This shader is valid.\n");
	}

	return shader_data;
}

int main(void) {
	InitWindow(800, 600, "Learning shaders");

	char *vsPath = "shaders/vs.glsl";
	char *fsPath = "shaders/fs.glsl";
	ShaderData shader_data = initShader(vsPath, fsPath);

	int i = 100;
	int posx = 200;

	SetTargetFPS(75);
	while (!WindowShouldClose()) {
		if (IsKeyPressed(KEY_R)) {
			UnloadShader(shader_data.shader);
			shader_data = initShader(vsPath, fsPath);
		}

		ClearBackground(BLUE);
		BeginDrawing();
			BeginShaderMode(shader_data.shader);

			DrawRectangle(100, 100, 400, 400, WHITE);

			EndShaderMode();
		EndDrawing();


		// SetShaderValue(shader, timeLoc, (float[1]){i}, SHADER_UNIFORM_FLOAT);

		float dt = GetFrameTime();
		posx += i * dt;
		// printf("Pos x: %i (%i)\n", posx, posx + i);
		// printf("Frame Time: %lf (%lf)\n", dt, i*dt);
		if ((posx + 400 >= 800) || (posx < 0)) i = -i;
	}

	return 0;
}
