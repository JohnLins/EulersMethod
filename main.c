#include <stdio.h>
#include <raylib.h>
#include <math.h>
#include "include/raymath.h"
#include "include/rlgl.h"

#define DEN 30

#define SCREENWIDTH DEN * 30
#define SCREENHEIGHT DEN * 30
#define ONE (SCREENWIDTH/DEN)

float differential(float x, float y){
    return sin(x * y);
}

void initMx();

int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Euler's Method Sim - John Lins");

    float x = 0;
    float y = 1;

    const float dx = 1.57;
    float dy = 0;

    float target = 7.85398;
    const int times = (int)(ceil((target - x)/dx) );
    float pastCoordinates[times-1][2];
     
    for(int i = 0; i < times; i++){
        
        dy = differential(x, y) * dx;
        printf("x: %f, y: %f ; STEP: (%f, %f) \n", x, y, dx, dy);
        pastCoordinates[i][0] = x; pastCoordinates[i][1] = y;  
        y = y + dy;
        x = x + dx;
    }
  
    SetTargetFPS(60);    
    while (!WindowShouldClose())   
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            initMx();

            DrawLine(0, -SCREENHEIGHT, 0, SCREENHEIGHT, BLACK);
            DrawLine(-SCREENWIDTH, 0, SCREENWIDTH, 0, BLACK);
            

            for(int i = 0; i < times; i++){
                DrawCircle(pastCoordinates[i][0] * ONE, pastCoordinates[i][1] * ONE, 5, GREEN);
                
                
              rlPopMatrix();
                DrawText(FormatText("(%f, %f)", pastCoordinates[i][0], pastCoordinates[i][1]), (pastCoordinates[i][0] * ONE + (ONE/10)) + SCREENWIDTH/2, SCREENHEIGHT/2 -  pastCoordinates[i][1] * ONE + (ONE/10) , 20, BLACK);
              initMx();

            }
            
         
           
           for(int i = -SCREENWIDTH; i <= SCREENWIDTH; i+=ONE){
                for(int j = -SCREENHEIGHT; j <= SCREENHEIGHT; j+=ONE){
                    float theta = atanf(differential(i, j)) / 2;
                    
                    
                  if(i < 0){theta += PI;}
                  if(j < 0 && i > 0){theta += 2*PI;}
                   
                    
                    double r = ONE/2;
                   DrawCircle(i, j, 2, BLUE);
                   DrawLine(i, j,((double)i + (double)r*(double)cos(theta)), ((double)j + (double)r*(double)sin(theta)), BLUE);
   
                    
                }
            }
            

        EndDrawing();
        
        rlPopMatrix();
    }

    CloseWindow();        


    return 0;
}

void initMx(){
     rlPushMatrix();
     rlTranslatef(GetScreenWidth()/2, GetScreenHeight()/2, 0);
     rlScalef(1, -1, 1);
     rlDisableBackfaceCulling();
}