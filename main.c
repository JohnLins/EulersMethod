#include <stdio.h>
#include <raylib.h>
#include <math.h>
#include "include/raymath.h"
#include "include/rlgl.h"

#define DEN 30

#define SCREENWIDTH DEN * 50
#define SCREENHEIGHT DEN * 20
#define ONE (SCREENWIDTH/DEN)

float differential(float x, float y){
    return x;
}

void initMx();

int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Euler's Method Sim - John Lins");

    float x = 1;
    float y = 3;

    const float dx = .1;
    float dy = 0;

    float target = 1.3;
    const int times = (int)(ceil((target - x)/dx) + 1);
    float pastCoordinates[times-1][2];
     
    for(int i = 0; i < times; i++){
        printf("x: %f, y: %f\n", x, y);
        dy = differential(x, y) * dx;
        
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
                DrawText(FormatText("(%f, %f)", pastCoordinates[i][0], pastCoordinates[i][1]), (pastCoordinates[i][0] * ONE + (ONE/10)) + SCREENWIDTH/2, SCREENHEIGHT/2 -  pastCoordinates[i][1] * ONE + (ONE/10) , 10, BLACK);
              initMx();
                
                
                //if(i != times){
                    //DrawLine(pastCoordinates[i][0], pastCoordinates[i][1], pastCoordinates[i+1][0], pastCoordinates[i+1][1], GREEN);
                //}
            }
            
            
            for(int i = -SCREENWIDTH; i <= SCREENWIDTH; i+=ONE){
                for(int j = -SCREENHEIGHT; j <= SCREENHEIGHT; j+=ONE){
                    float theta = atan(differential(i, j));
                    
                  if(i < 0){theta += PI;}
                  if(j < 0 && i > 0){theta += 2*PI;}
                   
                    
                    float r = ONE/2;
                   DrawCircle(i, j, 2, BLUE);
                   //DrawLine(i, j,(i + r*cos(theta)), (j + r*sin(theta)), BLUE);
                 
                 
                 //  float norm = 1;//sqrtf( powf(ONE,2) + powf(ONE * differential(i,j),2));
                   //DrawLine(i, j, i + ONE/norm, j + ONE*differential(i,j)/norm, RED)
;                   
                    
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