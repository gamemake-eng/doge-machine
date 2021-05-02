#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

typedef struct Player {
			Vector2 pos;
			Vector2 size;
			bool up;
	} Player;
typedef struct Wall{
			Vector2 pos;
			Vector2 size;
	}Wall;

int main()
{
    // Init
    int points = 0;
    char pointsS[50];
    int screenWidth = 800;
    int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "doge machine");
    SetTargetFPS(60);
    //player init
    Player player = {0};
    player.pos = (Vector2){(float)60,(float)60};
    player.size = (Vector2){(float)29,(float)29};
    player.up = false;
    Rectangle playerR = {player.pos.x,player.pos.y,player.size.x,player.size.y};
    //wall init
    Wall wall = {0};
    wall.pos = (Vector2){(float)800,(float)0};
    wall.size = (Vector2){(float)30,(float)200};
    Rectangle wallR = {wall.pos.x,wall.pos.y,wall.size.x,wall.size.y};
    //time init
    time_t t;
    srand((unsigned) time(&t));
    //scene init
    int scene = 0;
	HideCursor(); 
    //game loop
    while (!WindowShouldClose())    // check if window close button or ESC is pressed
    {
        // Update
        if(scene == 0){
			if(IsKeyPressed(KEY_M)){
				points = 0;
				player.pos.y = 60;
				wall.pos.x = 800;
				scene = 1;
			}
		}
        if(scene == 2){
			if(IsKeyPressed(KEY_M)){
				points = 0;
				player.pos.y = 60;
				wall.pos.x = 800;
				scene = 1;
			}
		}
        //variables
        sprintf(pointsS, "%d", points);
        if(scene == 1){
		//wall
        wallR.x = wall.pos.x;
        wallR.y = wall.pos.y;
        wallR.width = wall.size.x;
        wallR.height = wall.size.y;
        //player
		playerR.x = player.pos.x;
        playerR.y = player.pos.y;
        playerR.width = player.size.x;
        playerR.height = player.size.y;
        //movement
        if(IsKeyDown(KEY_SPACE)){
			player.up = true;
		}
		if(IsKeyUp(KEY_SPACE)){
			player.up = false;
		}
		if(player.up){
			player.pos.y -= 3;
		}
		if(!player.up){
			player.pos.y += 3;
		}
		//wall
		if(wall.pos.x > -29){
			wall.pos.x -= 6;
		}
		if (wall.pos.x < -29){
			points += 1;
			wall.pos.x = 800;
			wall.pos.y = rand() % 200 + 1;
			wall.size.y = (rand() %(170 - 400 + 1)) + 160;
		}
		
		//collision
		if(player.pos.y > 456 || player.pos.y < -6){
				scene = 2;
		}
		if(CheckCollisionRecs(playerR, wallR)){
			scene = 2;
		}
	}
		
		
        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
			DrawFPS(0,0);
			if(scene == 1){
			DrawRectangleV(player.pos,player.size,RED);
			DrawRectangleV(wall.pos,wall.size,RED);
			DrawText(pointsS, 0,20,30,SKYBLUE);
		}
			if(scene == 2){
				DrawText("PRESS [M] TO START OVER", GetScreenWidth()/2 - MeasureText("PRESS [M] TO START OVER", 20)/2, GetScreenHeight()/2 - 50, 20, SKYBLUE);
				DrawText(pointsS, GetScreenWidth()/2 - MeasureText(pointsS, 20)/2, 60, 40, SKYBLUE);
			}
			if(scene == 0){
				DrawText("PRESS [M] TO START THE GAME", GetScreenWidth()/2 - MeasureText("PRESS [M] TO START THE GAME", 20)/2, GetScreenHeight()/2 - 50, 20, SKYBLUE);
			}
        EndDrawing();
    }

    // exiting
  
    CloseWindow();        // Close window
   

    return 0;
}
