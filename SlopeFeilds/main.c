#include <stdio.h>
#include <raylib.h>
#include <math.h>
#include "include/raymath.h"
#include "include/rlgl.h"

#define SCREENWIDTH 800
#define SCREENHEIGHT 450

#define ONE (SCREENWIDTH/16)


float differential(float x, float y){

    return x + y;
}

int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Euler's Method Sim - John Lins");
    
    float x;
    float y;

    x = 2;
    y = 0;

    //float x_new;
   // float y_new;
    //scanf("%f", x)

    const float dx = .2;
    float dy = 0;

    float target = 3;
    //while(x != target){
    int a = (int)(((target - x)/dx) + 3);
    for(int i = 0; i < a; i++){
        printf("x: %f, y: %f\n", x, y);
        dy = differential(x, y) * dx;
        
        y = y + dy;
        x = x + dx;

    }
    
   

    SetTargetFPS(60);    
    while (!WindowShouldClose())   
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            rlPushMatrix();
            rlTranslatef(GetScreenWidth()/2, GetScreenHeight()/2, 0);
            rlScalef(1, -1, 1);
            rlDisableBackfaceCulling();

            DrawLine(0, -SCREENHEIGHT, 0, SCREENHEIGHT, BLACK);
            DrawLine(-SCREENWIDTH, 0, SCREENWIDTH, 0, BLACK);
            
            int startHorizontal = -SCREENWIDTH;
            int startVertical = -SCREENHEIGHT;
            
            for(int i = -SCREENWIDTH; i <= SCREENWIDTH; i+=ONE){
                for(int j = -SCREENHEIGHT; j <= SCREENHEIGHT; j+=ONE){
                    float theta = atan(differential(i, j));
                    float r = ONE/2;
                    DrawLine(i, j,(i+r*cos(theta)), (j + r*sin(theta)), BLUE);
                    //DrawLine(i, 0,(i+ONE), (0 + differential(i, 0)), BLUE);
                }
            }
            

        EndDrawing();
        
        rlPopMatrix();
    }

    CloseWindow();        


    return 0;
}