
#include "car.cpp"

using namespace std;

string s;

string fname = "map4";

string ip = "maps/"+fname+".ppm";
double t = 0;

std::ifstream f(ip);

//initial values 
Vector2 position = { screenWidth-70, screenHeight-20 };
Rectangle rect = { position.x,position.y, 30, 15 };
Vector2 origin = { rect.width / 2, rect.height / 2 };

int readFile(){
    if (!f.is_open()) {
        cout << "File can't be opened"<<endl;
        return 1;
    }
    cout<<"File opened successfully"<<endl;

    string s,h,w,wh,disc,flt;

    getline(f, s);
    getline(f,disc);
    getline(f, wh);
    istringstream(wh) >> w >> h;

    row = stoi(w);

    getline(f, disc);

    for (int i = 0; i < stoi(w)*stoi(h) ; i++)
    {   
        getline(f, s);
        s.erase(remove(s.begin(), s.end(), '\n'), s.end());
        a = stoi(s);

        getline(f, s);
        s.erase(remove(s.begin(), s.end(), '\n'), s.end());
        b = stoi(s);

        getline(f, s);
        s.erase(remove(s.begin(), s.end(), '\n'), s.end());
        c = stoi(s);
        
        img[i] = a;
        len++;
    }
    cout<<int(img[0])<<endl;
    cout<<len<<endl;

    int index = 0;
    for (int i = 0; i < stoi(h); i++)
    {
        for (int j = 0; j < stoi(w); j++)
        {
           mp[i][j] = img[index];
           if(mp[i][j]==255)mp[i][j]=1;
           else mp[i][j]=0;
           index++;
        }
    }
    return 0;
}

void forward(){
    float angleRad = rot * DEG2RAD;
    position.x += cosf(angleRad) * speed;
    position.y += sinf(angleRad) * speed;
}
void backward(){
    float angleRad = rot * DEG2RAD;
    position.x -= cosf(angleRad) * speed;
    position.y -= sinf(angleRad) * speed;
}
void right(){
    rot-=rotAm;
}
void left(){
    rot+=rotAm;
}
void shakeIt(){
    if ((dX == position.x && dY == position.y)||abs(dR-rot)==rotAm) {
        if (t == 0) t = GetTime();
        if (GetTime() - t > wTime) {
            if(togg){
                rot+=20;
                backward();
                backward();
                backward();
                backward();
                
                togg=!togg;
            } else {
                rot-=20;
                backward();
                backward();
                backward();
                backward();

                togg=!togg;
            }
        }
    } else {
        t = 0;
    }
}


int main()
{     

    if(readFile())return 1;

    

    car c(rect,position,origin,RED);

    SetTargetFPS(fps);
    InitWindow(screenWidth, screenHeight, "AI race");

    while(!WindowShouldClose())
    {   
        
        BeginDrawing();
        ClearBackground(BLACK);

        
        
        drawMap();

        //manual control;
        if(IsKeyDown(KEY_A))right();
        if(IsKeyDown(KEY_D))left();
        if(IsKeyDown(KEY_W))forward();
        if(IsKeyDown(KEY_S))backward();
        if(IsKeyPressed(KEY_SPACE))show=!show;

        if(IsKeyDown(KEY_R)){
            position.x = GetMouseX();
            position.y = GetMouseY();
        }



        //Autonomous logic 

        dX = position.x;
        dY = position.y; 
        dR = rot;

        if(cutoff[1]){
            forward();
            if(!cutoff[0]&&cutoff[2])left();
            if(cutoff[0]&&!cutoff[2])right();
        } else {
            if(!cutoff[0])left();
            else if(!cutoff[2])right();
            else if(!cutoff[1]){
                if(togg){
                    right();
                    togg=!togg;
                } else {
                    left();
                    togg=!togg;
                }
            
            }
        }

        //if all rays are blocked, SHAKE THAT BOOTIEEE till it recovers

        if(!cutoff[0]&&!cutoff[1]&&!cutoff[2]){
            if(togg){
                rot+=rotAm;
                togg=!togg;
            }else{
                rot-=rotAm;
                togg=!togg;
            }
        }
        
        // if stuck then shake it aggressively
        shakeIt();
        
        c.updateCar(position.x,position.y,rot);

        EndDrawing();
    }
    
    CloseWindow();


    return 0;
}
