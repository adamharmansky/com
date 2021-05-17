#include <stdio.h>
#include <raylib.h>

#define RES 32
#define S 30

typedef enum { START=-1, OBJECT_NONE=0, FULL, HU, HR, HD, HL, SR, SD, SL, SU, REPEAT } object;

object objects[RES][RES];

int
main()
{
	int i, j;
	long int x, y, v;
	int mx, my;
	int rx=0, ry=0;
	char t[64];

	InitWindow(S*RES, S*RES, "ťažisko");

	/* Main Loop */
	while(!WindowShouldClose()) {

		x = 0;
		y = 0;
		v = 0;

		mx = GetMouseX();
		my = GetMouseY();

		BeginDrawing();

			ClearBackground(RAYWHITE);

			for(i = 0; i < RES; i++) {
				for(j = 0; j < RES; j++) {

					/* God forgive me for this inefficiency it's
					 * just a program for school I know I am
					 * drawing each line at least two times */
					DrawRectangleLines(i*S, j*S, S, S, (Color){0,0,0,10});

					/* I know this looks awful, but whatever */
					switch(objects[i][j]) {
						case FULL:
							DrawRectangle(i*S, j*S, S, S, RED);
							x += (i*S + S/2)*S*S;
							y += (j*S + S/2)*S*S;
							v += S*S;
							break;
						case HU:
							DrawTriangle((Vector2){i*S+S, j*S},(Vector2){i*S, j*S},(Vector2){i*S, j*S+S}, RED);
							x += (i*S + S/3)*S*S/2;
							y += (j*S + S/3)*S*S/2;
							v += S*S/2;
							break;
						case HR:
							DrawTriangle((Vector2){i*S+S, j*S},(Vector2){i*S, j*S},(Vector2){i*S+S, j*S+S}, RED);
							x += (i*S + S/3*2)*S*S/2;
							y += (j*S + S/3)*S*S/2;
							v += S*S/2;
							break;
						case HD:
							DrawTriangle((Vector2){i*S+S, j*S},(Vector2){i*S, j*S+S},(Vector2){i*S+S, j*S+S}, RED);
							x += (i*S + S/3*2)*S*S/2;
							y += (j*S + S/3*2)*S*S/2;
							v += S*S/2;
							break;
						case HL:
							DrawTriangle((Vector2){i*S, j*S},(Vector2){i*S, j*S+S},(Vector2){i*S+S, j*S+S}, RED);
							x += (i*S + S/3)*S*S/2;
							y += (j*S + S/3*2)*S*S/2;
							v += S*S/2;
							break;
						case SR:
							DrawTriangle((Vector2){i*S+S, j*S+S/2},(Vector2){i*S, j*S},(Vector2){i*S, j*S+S}, RED);
							x += (i*S + S/3)*S*S/2;
							y += (j*S + S/2)*S*S/2;
							v += S*S/2;
							break;
						case SD:
							DrawTriangle((Vector2){i*S+S, j*S},(Vector2){i*S, j*S},(Vector2){i*S+S/2, j*S+S}, RED);
							x += (i*S + S/2)*S*S/2;
							y += (j*S + S/3)*S*S/2;
							v += S*S/2;
							break;
						case SL:
							DrawTriangle((Vector2){i*S, j*S+S/2},(Vector2){i*S+S, j*S+S},(Vector2){i*S+S, j*S}, RED);
							x += (i*S + S/3*2)*S*S/2;
							y += (j*S + S/2)*S*S/2;
							v += S*S/2;
							break;
						case SU:
							DrawTriangle((Vector2){i*S+S, j*S+S},(Vector2){i*S+S/2, j*S},(Vector2){i*S, j*S+S}, RED);
							x += (i*S + S/2)*S*S/2;
							y += (j*S + S/3*2)*S*S/2;
							v += S*S/2;
							break;
					}

					if((int)(mx/S) == i && (int)(my/S) == j) {
						DrawRectangleLines(i*S, j*S, S, S, BLACK);
						if(IsMouseButtonPressed(0)) {
							objects[i][j]++;
							if(objects[i][j] == REPEAT) objects[i][j] = 0;
						} else if(IsMouseButtonPressed(1)) {
							objects[i][j]--;
							if(objects[i][j] == START) objects[i][j] = REPEAT - 1;
						} else if(IsMouseButtonPressed(2)) {
							rx = i*S;
							ry = j*S;
						}
					}

				}
			}

			if(v) {
				DrawCircle(x/v, y/v, 5, YELLOW);
				sprintf(t,"[%2.2f,%2.2f]", (float)(x/v - rx)/S, (float)(y/v - ry)/S);
				DrawText(t, x/v, y/v-20, 20, BLACK);
			}
			DrawTriangle((Vector2){rx+S*3+5, ry},(Vector2){rx+S*3-5, ry-5},(Vector2){rx+S*3-5, ry+5}, RED);
			DrawRectangle(rx, ry-2, S*3, 4, RED);
			DrawTriangle((Vector2){rx, ry+S*3+5},(Vector2){rx+5, ry+S*3-5},(Vector2){rx-5, ry+S*3-5}, GREEN);
			DrawRectangle(rx-2, ry, 4, S*3, GREEN);
			DrawCircle(rx, ry, 5,  BLUE);
			DrawText("[0,0]",rx,ry-20,20, BLACK);

		EndDrawing();

	}
	CloseWindow();
}
