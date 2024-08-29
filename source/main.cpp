#include <citro2d.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 240;

const int SPEED = 10;

typedef struct
{
	float x;
	float y;
	float z;
	float w;
	float h;
	unsigned int color;
} Rectangle;

int main(int argc, char *argv[])
{
	// Init libs
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);

	// Create screens
	C3D_RenderTarget *top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	// Create colors
	u32 whiteColor = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);

	u32 blackColor = C2D_Color32(0x00, 0x00, 0x00, 0x00);

	Rectangle bounds = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 32, 32, whiteColor};

	// Main loop
	while (aptMainLoop())
	{
		printf("\x1b[1;1HSimple citro2d shapes example");

		hidScanInput();

		// Respond to user input
		u32 keyDown = hidKeysDown();
		u32 keyHeld = hidKeysHeld();

		if (keyDown & KEY_START)
			break; // break in order to return to hbmenu

		if (keyHeld & KEY_LEFT && bounds.x > 0)
		{
			bounds.x -= SPEED;
		}
		if (keyHeld & KEY_RIGHT && bounds.x < SCREEN_WIDTH - bounds.w)
		{
			bounds.x += SPEED;
		}
		if (keyHeld & KEY_UP && bounds.y > 0)
		{
			bounds.y -= SPEED;
		}
		if (keyHeld & KEY_DOWN && bounds.y < SCREEN_HEIGHT - bounds.h)
		{
			bounds.y += SPEED;
		}

		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, blackColor);
		C2D_SceneBegin(top);

		// (float x, float y, float z, float  w, float h, u32 clr)
		C2D_DrawRectSolid(bounds.x, bounds.y, bounds.z, bounds.w, bounds.h, bounds.color);

		C3D_FrameEnd(0);
	}

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}
