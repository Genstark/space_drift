#include "raylib.h"
#include <iostream>
#include <vector>
#include <math.h>

class Button {
public:
    Button(int p_radiusType)
    {
        radiusType = p_radiusType;
    }
    int getType()
    {
        return radiusType;
    }
    void setType(int radius)
    {
        radiusType = radius;
    }
    float getWidth()
    {
        return width;
    }
    float getHeight()
    {
        return width;
    }
private:
    int radiusType = 30;
    float width = 55;
    float height = 55;
};

class Spike {
public:
    Spike(float p_x, float p_y)
    {
        x = p_x;
        y = p_y;
    }
    float getX()
    {
        return x;
    }
    float getY()
    {
        return y;
    }
    float getWidth()
    {
        return width;
    }
    float getHeight()
    {
        return width;
    }
private:
    float x = 0;
    float y = 0;
    float width = 34;
    float height = 34;

};

class Star {
public:
    Star(float p_x, float p_y)
    {
        x = p_x;
        y = p_y;
    }
    float getX()
    {
        return x;
    }
    float getY()
    {
        return y;
    }
    float getWidth()
    {
        return width;
    }
    float getHeight()
    {
        return width;
    }
private:
    float x = 0;
    float y = 0;
    float width = 64;
    float height = 61;

};

class Wall {
public:
    Wall(float p_x, float p_y)
    {
        x = p_x;
        y = p_y;
    }
    float getX()
    {
        return x;
    }
    float getY()
    {
        return y;
    }
    float getWidth()
    {
        return width;
    }
    float getHeight()
    {
        return width;
    }
private:
    float x = 0;
    float y = 0;
    float width = 32;
    float height = 32;

};

bool checkCollisions(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
    return x1 + w1 > x2 && x1 < x2 + w2 && y1 + h1 > y2 && y1 < y2 + h2;
}  

class Player {
public:
    void update(float deltaTime, std::vector<Wall> walls)
    {
        float newX = x + velocityX*deltaTime;
        float newY = y + velocityY*deltaTime;
        bool flipX = false;
        bool flipY = false;
        for (Wall w : walls)
        {
            if (checkCollisions(newX, y, width, height, w.getX(), w.getY(), w.getWidth(), w.getHeight()))
            {
                flipX = true;
            }
            if (checkCollisions(x, newY, width, height, w.getX(), w.getY(), w.getWidth(), w.getHeight()))
            {
                flipY = true;
            }
        }
        if (flipX || newX < 0 || newX + 28 > 640)
        {
            velocityX *= -1;
        }
        else
        {
            x = newX;
        }
        if (flipY || newY < 0 || newY + 32 > 480 - 64)
        {
            velocityY *= -1;
        }
        else
        {
            y = newY;
        }
    }
    void reset()
    {
        x = 60;
        y = 60;
        setVelocity(0,0);
    }
    void setPosition(float p_x, float p_y)
    {
        x = p_x;
        y = p_y;
    }
    void setX(int p_x)
    {
        x = p_x;
    }
    void setY(int p_y)
    {
        y = p_y;
    }
    void setVelocity(float p_velocityX, float p_velocityY)
    {
        velocityX = p_velocityX;
        velocityY = p_velocityY;
    }
    float getX()
    {
        return x;
    }
    float getY()
    {
        return y;
    }
    float getVelocityX()
    {
        return velocityX;
    }
    float getVelocityY()
    {
        return velocityY;
    }
private:
    float x = 0;
    float y = 0;
    int width = 24;
    int height = 32;
    float velocityX = 0;
    float velocityY = 0;
};

class Planet {
public:
    void setX(int p_x)
    {
        x = p_x;
    }
    void setY(int p_y)
    {
        y = p_y;
    }
    void setRadius(int p_radius)
    {
        radius = p_radius;
    }
    float getX()
    {
        return x;
    }
    float getY()
    {
        return y;
    }
    float getRadius()
    {
        return radius;
    }
private:
    float x = 0;
    float y = 0;
    float radius;
};

float getDistance(float x1, float y1, float x2, float y2)
{
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

std::vector<Planet> planets;
std::vector<Button> buttons;
std::vector<Wall> walls;
std::vector<Spike> spikes;
std::vector<Star> stars;

Player player;
int currentLevel = 0;
int deaths = 0;
int currentIndex = -1;

void loadLevel(int level)
{
    switch(level) 
	{
        case 0:
            buttons.push_back(Button(30)); 
            stars.push_back(Star(580 - 64, 420 - 64 - 61));  
        break;
        case 1:
            buttons.push_back(Button(20));       
            buttons.push_back(Button(60));       
  
            spikes.push_back(Spike(320 -16, 64 + 100)); 
            spikes.push_back(Spike(320 -16, 96 + 100));     
            stars.push_back(Star(580 - 64, 420 - 64 - 61)); 
            //spikes.push_back(Spike(100,100));    
        break;
        case 2:
            buttons.push_back(Button(30));       
            buttons.push_back(Button(60));
            buttons.push_back(Button(60));  
          
            spikes.push_back(Spike(320 -16, 0)); 
            spikes.push_back(Spike(320 -16, 32)); 
            spikes.push_back(Spike(320 -16, 64)); 
            spikes.push_back(Spike(320 -16, 96));     
            stars.push_back(Star(580 - 64, 50)); 
            //spikes.push_back(Spike(100,100));    
        break;
        case 3:
            buttons.push_back(Button(30));       
            buttons.push_back(Button(30));
            buttons.push_back(Button(30)); 
            buttons.push_back(Button(30)); 
            buttons.push_back(Button(30)); 
 
            spikes.push_back(Spike(320 -16, 64 + 116)); 

            spikes.push_back(Spike(320 -16 - 100, 64 + 116 - 50 + 75 + 48)); 
            spikes.push_back(Spike(320 -16 + 100, 64 + 116 + 50 + 100 - 48));  
            spikes.push_back(Spike(320 -16 - 100, 64 + 116 - 50 - 100 + 48)); 
            spikes.push_back(Spike(320 -16 + 100, 64 + 116 + 50 - 75 - 48));  
            
            stars.push_back(Star(580 - 64, 420 - 64 - 61)); 
        break;
        case 4:
            buttons.push_back(Button(20));       
            buttons.push_back(Button(90));  
          
            spikes.push_back(Spike(128 + 16, 0)); 
            spikes.push_back(Spike(128 + 16, 32)); 
            spikes.push_back(Spike(128 + 16, 64)); 
            spikes.push_back(Spike(128 + 16, 96)); 
            spikes.push_back(Spike(128 + 16, 128)); 
            spikes.push_back(Spike(128 + 16, 160)); 
            spikes.push_back(Spike(128 + 16, 192)); 
            spikes.push_back(Spike(128 + 16, 222));     
            stars.push_back(Star(580 - 64, 50)); 
            //spikes.push_back(Spike(100,100));    
        break;
        case 5:
            buttons.push_back(Button(90)); 
            stars.push_back(Star(580 - 64, 420 - 64 - 61));  
            spikes.push_back(Spike(0, 128)); 
            spikes.push_back(Spike(32, 128));
            spikes.push_back(Spike(32*2, 128));
            walls.push_back(Wall(32*3, 128));
            spikes.push_back(Spike(32*4, 128));
            spikes.push_back(Spike(32*5, 128));
            spikes.push_back(Spike(32*6, 128));
            walls.push_back(Wall(32*7, 128));
            spikes.push_back(Spike(32*8, 128));
            spikes.push_back(Spike(32*9, 128));
            spikes.push_back(Spike(32*10, 128));
            walls.push_back(Wall(32*11, 128));
      
            //spikes.push_back(Spike(100,100));    
        break;
        case 6:
            buttons.push_back(Button(30));       
            buttons.push_back(Button(30));      
  
            spikes.push_back(Spike(60  + 100, 60 + (80)+ 60)); 
            spikes.push_back(Spike(60  + 100, 60 - (80)+ 60)); 

            spikes.push_back(Spike(60  + 150, 60 + (80)+ 90)); 
            spikes.push_back(Spike(60  + 150, 60 - (80)+ 90)); 

            spikes.push_back(Spike(60  + 200, 60 + (80)+ 120)); 
            spikes.push_back(Spike(60  + 200, 60 - (80)+ 120)); 

            spikes.push_back(Spike(60  + 250, 60 + (80)+ 150)); 
            spikes.push_back(Spike(60  + 250, 60 - (80) + 150)); 

            spikes.push_back(Spike(60  + 300, 60 + (80)+ 180)); 
            spikes.push_back(Spike(60  + 300, 60 - (80) + 180));

            spikes.push_back(Spike(60  + 350, 60 + (80)+ 210)); 
            spikes.push_back(Spike(60  + 350, 60 - (80) + 210));  

            spikes.push_back(Spike(60  + 400, 60 + (80)+ 240)); 
            spikes.push_back(Spike(60  + 400, 60 - (80) + 240));  

            spikes.push_back(Spike(60  + 450, 60 + (80)+ 270)); 
            spikes.push_back(Spike(60  + 450, 60 - (80) + 270));  

            spikes.push_back(Spike(60  + 500, 60 + (80)+ 300)); 
            spikes.push_back(Spike(60  + 500, 60 - (80) + 300));  

            spikes.push_back(Spike(60  + 550, 60 + (80)+ 330)); 
            spikes.push_back(Spike(60  + 550, 60 - (80) + 330));

            stars.push_back(Star(60  + 550, 60 + 330));   
        break;

    }
      
    

    
    
    
}

void reset()
{
    currentIndex = -1;
    player.reset();
    planets.clear();
    buttons.clear();
    spikes.clear();
    walls.clear();
    stars.clear();
    loadLevel(currentLevel); 
}

int main(void)
{

    const int screenWidth = 640;
    const int screenHeight = 480;

    
    
    InitWindow(screenWidth, screenHeight, "Digmoid Drift");
    InitAudioDevice();
    SetMasterVolume(0.3f);

    Texture2D playerTex = LoadTexture("res/gfx/player.png");
    Texture2D planet30Tex = LoadTexture("res/gfx/planet_30.png"); 
    Texture2D planet60Tex = LoadTexture("res/gfx/planet_60.png"); 
    Texture2D planet20Tex = LoadTexture("res/gfx/planet_20.png"); 
    Texture2D planet90Tex = LoadTexture("res/gfx/planet_90.png"); 
    Texture2D UIBarTex = LoadTexture("res/gfx/ui_bar.png");  
    Texture2D buttonTex = LoadTexture("res/gfx/button.png");  
    Texture2D button20Tex = LoadTexture("res/gfx/button_20.png");
    Texture2D button30Tex = LoadTexture("res/gfx/button_30.png");
    Texture2D button60Tex = LoadTexture("res/gfx/button_60.png");
    Texture2D button90Tex = LoadTexture("res/gfx/button_90.png");
    Texture2D wallTex = LoadTexture("res/gfx/wall.png");
    Texture2D spikeTex = LoadTexture("res/gfx/spike.png");
    Texture2D starTex = LoadTexture("res/gfx/star.png");
    Texture2D levelTex = LoadTexture("res/gfx/level_border.png");
    Texture2D deathsTex = LoadTexture("res/gfx/deaths_border.png");
    Texture retryButton = LoadTexture("res/gfx/retry_button.png");
    Texture skipButton = LoadTexture("res/gfx/skip_button.png");
    Texture logo = LoadTexture("res/gfx/logo.png");
    Texture endScreenTex = LoadTexture("res/gfx/endScreen.png");

    Font font32 = LoadFontEx("res/font/font.otf", 32, 0, NULL);
    Font font24 = LoadFontEx("res/font/font.otf", 24, 0, NULL);
    Font font48 = LoadFontEx("res/font/font.otf", 48, 0, NULL);
    Font font64 = LoadFontEx("res/font/font.otf", 64, 0, NULL);

    Sound fxEarth = LoadSound("res/sfx/earth.wav"); 
    Sound fxMars = LoadSound("res/sfx/mars.wav"); 
    Sound fxPluto = LoadSound("res/sfx/pluto.wav"); 
    Sound fxWhat = LoadSound("res/sfx/what.wav"); 
    Sound fxPlace = LoadSound("res/sfx/place.wav"); 
    Sound fxClick = LoadSound("res/sfx/click.wav"); 
    Sound fxWin = LoadSound("res/sfx/win.wav"); 
    Sound fxDie = LoadSound("res/sfx/dead.wav"); 

    SetTargetFPS(60);    

    reset();
    bool titleScreen = true;
    float splashTimer = 0;
    bool playedSelect = false;
    bool playedSplash = false;
    while (!WindowShouldClose())   
    {
        if (currentLevel > 6)
        {
            BeginDrawing();
                ClearBackground(Color{30, 30, 30, 255});

                DrawTexture(endScreenTex, 0,0,WHITE);
                DrawTextEx(font48, "YOU FOUND YOUR HOME!",Vector2{screenWidth/2 - 348/2, screenHeight/2 - 15 - 30}, 48, 0, ColorFromNormalized((Vector4){0,0,0, 1.0})); 
                DrawTextEx(font32, TextFormat("(AFTER %00i DEATHS...)", deaths), Vector2{screenWidth/2 -195/2, screenHeight/2 -13 + 30}, 32, 0, BLACK);        
                EndDrawing();
        }
        else if (titleScreen)
        {   if (splashTimer > 120)
            {
                if (!playedSelect)
                {
                    PlaySound(fxDie);
                    playedSelect = true;
                }
                BeginDrawing();
                ClearBackground(Color{30, 30, 30, 255});
                DrawTexture(logo, 0,-50, WHITE);
                DrawTextEx(font32, "CLICK ANYWHERE TO BEGIN",Vector2{screenWidth/2 - 134, (float)screenHeight/2 + 100 + sin(GetTime()*5)*2}, 32, 0, ColorFromNormalized((Vector4){0,0,0,1})); 
                EndDrawing();
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                {
                    PlaySound(fxDie);
                    titleScreen = false;
                }
            } else {
                if (!playedSplash)
                {
                    PlaySound(fxClick);
                    playedSplash = true;
                }
                BeginDrawing();
                ClearBackground(Color{30, 30, 30, 255});
                DrawTextEx(font32, "SOMEBODY",Vector2{screenWidth/2 - 107/2, screenHeight/2 - 10}, 32, 0, ColorFromNormalized((Vector4){0,0,0, 1.0})); 
                EndDrawing();
                splashTimer += GetFrameTime()*60;
            }
        } 
        else{
        float deltaTime = GetFrameTime()*60;

        if (IsMouseButtonPressed(0))
        {
            if (GetMouseY() < 480 - 64 && ((currentIndex > -1) && (currentIndex < buttons.size())))
            {
                PlaySound(fxPlace);
                if (buttons.at(currentIndex).getType() == 20)
                {
                   PlaySound(fxPluto);
                }
                if (buttons.at(currentIndex).getType() == 30)
                {
                    PlaySound(fxMars);
                }
                if (buttons.at(currentIndex).getType() == 60)
                {
                    PlaySound(fxEarth);
                }
                if (buttons.at(currentIndex).getType() == 90)
                {
                    PlaySound(fxWhat);
                }

                planets.push_back(Planet());
                
                planets.at(planets.size() - 1).setRadius(buttons.at(currentIndex).getType());
                planets.at(planets.size() - 1).setX(GetMouseX() - planets.at(planets.size() - 1).getRadius());
                planets.at(planets.size() - 1).setY(GetMouseY() - planets.at(planets.size() - 1).getRadius());
                buttons.erase(buttons.begin() + currentIndex);
                currentIndex = -1;
            }
            else
            {
                for (int i = 0; i < buttons.size(); i++)
                {
                    if (checkCollisions(GetMouseX(), GetMouseY(), 2, 2, 3 + i*62, 480 - 58, buttons.at(i).getWidth(), buttons.at(i).getHeight()))
                    {
                        PlaySound(fxClick);
                        currentIndex = i;
                    }
                }
            }
        }

        float forceX = 0;
        float forceY = 0;
        
        for (Planet p : planets)
        {
            float distance = getDistance(player.getX() + 12, player.getY() + 16, p.getX() + p.getRadius(), p.getY() + p.getRadius());
            //radius determines "mass" of planet
            //if (distance < 500)
            //{
                forceX += (p.getRadius()*0.05 * (p.getX() + p.getRadius() - player.getX() + 12))/(distance*distance);
                forceY += (p.getRadius()*0.05 * (p.getY() + p.getRadius() - player.getY() + 12))/(distance*distance);
            //}

            //collisions
            if (distance < p.getRadius())
            {
                reset();
                deaths++;
                PlaySound(fxDie);
                forceX = 0;
                forceY = 0;
                break;
            }
        }
        player.setVelocity(player.getVelocityX() + forceX*deltaTime, player.getVelocityY() + forceY*deltaTime);
        player.update(deltaTime, walls);

         if (IsMouseButtonPressed(0) && checkCollisions (GetMouseX(), GetMouseY(), 2, 2, 560, 422, 77, 28))
            {
                PlaySound(fxDie);
                deaths++;
                reset();
            }
        if (IsMouseButtonPressed(0) && checkCollisions (GetMouseX(), GetMouseY(), 2, 2, 576, 451, 61, 28))
            {
                PlaySound(fxWin);
                currentLevel++;
                reset();
            }

        for (Spike s : spikes)
        {
            if (checkCollisions(player.getX(), player.getY(), 28, 32, s.getX(), s.getY(), s.getWidth(), s.getHeight()))
            {
                reset();
                deaths++;
                PlaySound(fxDie);
            }
        }

        for (Star s : stars)
        {
            if (checkCollisions(player.getX(), player.getY(), 28, 32, s.getX(), s.getY(), s.getWidth(), s.getHeight()))
            {
                currentLevel++;
                PlaySound(fxWin);
                reset();
            }
        }

        BeginDrawing();

            ClearBackground(Color{30, 30, 30, 255});
            if (GetMouseY() < 480 - 64 && ((currentIndex > -1) && (currentIndex < buttons.size()))) //translucent planet preview
            {
                if (buttons.at(currentIndex).getType() == 20)
                {
                    DrawTexture(planet20Tex, GetMouseX() - 20, GetMouseY() - 20, GRAY);
                }
                if (buttons.at(currentIndex).getType() == 30)
                {
                    DrawTexture(planet30Tex, GetMouseX() - 30, GetMouseY() - 30, GRAY);
                }
                if (buttons.at(currentIndex).getType() == 60)
                {
                    DrawTexture(planet60Tex, GetMouseX() - 60, GetMouseY() - 60, GRAY);
                }
                if (buttons.at(currentIndex).getType() == 90)
                {
                    DrawTexture(planet90Tex, GetMouseX() - 90, GetMouseY() - 90, GRAY);
                }
            }

            for (Wall w : walls)
            {
                DrawTexture(wallTex, w.getX(), w.getY(), WHITE);
            }

            for (Spike s : spikes)
            {
                DrawTexture(spikeTex, s.getX(), s.getY(), WHITE);
            }

            for (Star s : stars)
            {
                DrawTexture(starTex, s.getX(), s.getY(), WHITE);
            }
    
            for (Planet p : planets)
            {
                if (p.getRadius() == 20)
                {
                    DrawTexture(planet20Tex, p.getX(), p.getY(), WHITE);
                }
                else if (p.getRadius() == 30)
                {
                    DrawTexture(planet30Tex, p.getX(), p.getY(), WHITE);
                }
                else if (p.getRadius() == 60)
                {
                    DrawTexture(planet60Tex, p.getX(), p.getY(), WHITE);
                }
                else if (p.getRadius() == 90)
                {
                    DrawTexture(planet90Tex, p.getX(), p.getY(), WHITE);
                }
            }
            DrawTexture(playerTex, player.getX(), player.getY(), WHITE);
            DrawTexture(UIBarTex, 0, 480 - 64, WHITE);
            for (int i = 0; i < buttons.size(); i++)
            {
                if (i == currentIndex)
                {
                    if (buttons.at(i).getType() == 20)
                    {
                        DrawTexture(button20Tex, 3 + i*62, 480 - 58, WHITE);
                    }
                    else if (buttons.at(i).getType() == 30)
                    {
                        DrawTexture(button30Tex, 3 + i*62, 480 - 58, WHITE);
                    }
                    else if (buttons.at(i).getType() == 60)
                    {
                        DrawTexture(button60Tex, 3 + i*62, 480 - 58, WHITE);
                    }
                    else if (buttons.at(i).getType() == 90)
                    {
                        DrawTexture(button90Tex, 3 + i*62, 480 - 58, WHITE);
                    }
                    else 
                    {
                        DrawTexture(buttonTex, 3 + i*62, 480 - 58, WHITE);
                    }
                }
                else
                {
                    if (buttons.at(i).getType() == 20)
                    {
                        DrawTexture(button20Tex, 3 + i*62, 480 - 58, GRAY);
                    }
                    else if (buttons.at(i).getType() == 30)
                    {
                        DrawTexture(button30Tex, 3 + i*62, 480 - 58, GRAY);
                    }
                    else if (buttons.at(i).getType() == 60)
                    {
                        DrawTexture(button60Tex, 3 + i*62, 480 - 58, GRAY);
                    }
                    else if (buttons.at(i).getType() == 90)
                    {
                        DrawTexture(button90Tex, 3 + i*62, 480 - 58, GRAY);
                    }
                    else 
                    {
                        DrawTexture(buttonTex, 3 + i*62, 480 - 58, WHITE);
                    }
                }
            }
            DrawTexture(levelTex, 0, 480 - 64 - 31, WHITE);
            DrawTexture(deathsTex, 640 - 152, 480 - 64 - 31, WHITE);
            DrawTexture(retryButton, 560, 422, WHITE);
            DrawTexture(skipButton, 576, 451, WHITE);
            DrawTextEx(font32, TextFormat("LEVEL: %01i/7", currentLevel + 1), Vector2{8, 480 - 64 - 31 + 2}, 32, 0, WHITE);  
            DrawTextEx(font32, TextFormat("DEATHS: %03i", deaths), Vector2{640 - 152 + 8, 480 - 64 - 31 + 2}, 32, 0, WHITE);        

        EndDrawing();
    }
    };

    CloseAudioDevice();
    CloseWindow();

    return 0;
}