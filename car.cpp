#include "gfx.h"
#include <bits/stdc++.h>

using namespace std;

class car{

    public:
        pair<float,float> dist[3];
        float rot;
        Rectangle rect;
        Vector2 position;
        Vector2 origin;
        Color color;
        float angleRad[3];

        car(Rectangle rect, Vector2 position, Vector2 origin, Color color){

            this->rot = 0.0f;  
            this->color = color;
            this->rect = rect;
            this->position = position;
            this->origin = origin;

        }    

        void updateCar(float x, float y, float rot) {
            this->position.x = x;
            this->position.y = y;
            this->origin.x = this->rect.width / 2;
            this->origin.y = this->rect.height / 2;
            this->rot = rot;
            this->rect = { this->position.x, this->position.y, rect.width, rect.height };
        
        
            for (int i = 0; i < 3; i++) {
                angleRad[i] = (rot + angleOffset[i]) * DEG2RAD;
                float n = 0;

                float tx = x, ty = y;
                while (n < maxDistance) {

                    tx = x + n*cosf(angleRad[i]);
                    ty = y + n*sinf(angleRad[i]);
        
                    int gx = (int)(tx / cellSize);
                    int gy = (int)(ty / cellSize);
                    if ( gx<0 || gy<0 || gx >= screenWidth / cellSize || gy >= screenHeight / cellSize )break;
                    if (mp[gy][gx] == 1) break;
                    n += 1;
                }
        
                dist[i].first = x + n*cosf(angleRad[i]);
                dist[i].second = y + n*sinf(angleRad[i]);

                if(n==maxDistance)cutoff[i]=1;
                else cutoff[i]=0;
            }
        
            rlSetLineWidth(3.0f);
            
            if(show){
                for (int i = 0; i < 3; i++){
                
                    if(cutoff[i])this->color=GREEN;
                    else this->color=RED;
                    DrawLine(this->rect.x, this->rect.y, dist[i].first, dist[i].second, color);
                    DrawCircle(dist[i].first,dist[i].second,rad,color);
                }
            }
            

            this->color=color;
            
            DrawRectanglePro(this->rect, this->origin, this->rot, ORANGE);
        
            rlSetLineWidth(1.0f);
        }
        
        
    
};