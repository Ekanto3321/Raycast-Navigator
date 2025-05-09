#include "const.h"
#include "raylib.h"
#include "rlgl.h"
#include <fstream>


void drawGrid(){

    for (int i = 0; i < screenWidth; i+=cellSize){
        DrawLine(i,0,i,screenHeight,DARKGRAY);
    }

    for (int i = 0; i < screenHeight; i+=cellSize){
        DrawLine(0,i,screenWidth,i,DARKGRAY);
    }

}

void drawMap(){

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < row; j++)
        {   
            if(mp[i][j]==1)
            DrawRectangle(j*cellSize,i*cellSize,cellSize,cellSize,DARKGRAY);
        }
        
    }
}
