


int screenHeight = 800;
int screenWidth = 800;
int fps = 75;
int row = 400;
int cellSize = screenHeight/row;
int a,b,c;
int len = 0;
float speed = 4.5f;
int n = 0;
int rad = 4;
float cutoff[3];
float angleOffset[3] = { -30.0f, 0.0f, 30.0f };
float maxDistance = 50.0f;
float rot = -120.0f;
bool togg = false;
float dX,dY,dR;
float wTime = 0.7;
bool show = true;

float rotAm = 6.0f;

int mp[400][400];
int img[160000];