#include "raylib.h"

#include <cstdlib>
#include <ctime>
#include "Meteor.h"
#include <vector>
#include <string>
#include "missile.h"
#include "functionality.h"
#include "Asteroid.h"



//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    //Screen
     //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - mouse input");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------
    float starShipPosX = screenWidth / 2;
    float starShipPosY = screenHeight - 150;
    float width = 25;
    float height = 50;

    //Meteor
    std::vector<Meteor*> meteors;
    const float meteorSpawnInterval = 0.1f; // Time interval between meteor spawns in seconds
    float meteorTimer = 0.0f;

    //Fire Bullets
    std::vector<missile*> missiles;
    float missileTimer = 0.0f;

    const float missileSpawnInterval = 0.5f;
    //Asteroids
    std::vector<Asteroid*> asteroids;
    float asteroidTimer = 0.0f;
    const float asteroidSpawnInterval = 1.0f;

    //Game Properties
    int lifePoints = 5;
    bool gameOver = false;






    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        if (lifePoints == 0) gameOver = true;


        if (!gameOver) {

            DrawText((std::to_string(lifePoints)).c_str(), 100, 10, 40, DARKGRAY);
            missileTimer += GetFrameTime();
            meteorTimer += GetFrameTime();
            asteroidTimer += GetFrameTime();


            //StarShip Keys
            if (IsKeyDown(KEY_RIGHT)) starShipPosX += 5.0f;
            if (IsKeyDown(KEY_LEFT))    starShipPosX -= 5.0f;
            if (IsKeyDown(KEY_UP))  starShipPosY -= 5.0f;
            if (IsKeyDown(KEY_DOWN))  starShipPosY += 5.0f;


            //Missiles
            if (IsKeyDown(KEY_SPACE)) {

                if (missileTimer >= missileSpawnInterval)
                {
                    missile* newMissile = new missile((int)starShipPosX, (int)starShipPosY);
                    missiles.push_back(newMissile);
                    missileTimer = 0.0f; // Reset the timer
                }
            }

            //Move Missiles
            for (size_t i = 0; i < missiles.size(); ++i) {
                missiles[i]->move();
            }
            for (size_t i = 0; i < asteroids.size(); ++i) {
                asteroids[i]->move();
            }

            //Meteors

            if (meteorTimer >= meteorSpawnInterval)
            {
                int randomNum = std::rand() % 801;
                Meteor* meteor = new Meteor(randomNum);
                meteors.push_back(meteor);
                meteorTimer = 0.0f; // Reset the timer
            }


            //Move Meteors
            for (size_t i = 0; i < meteors.size(); ++i) {
                meteors[i]->move();
            }
            //Asteroids
            if (asteroidTimer >= asteroidSpawnInterval)
            {
                int randomNum = std::rand() % 801;
                Asteroid* asteroid = new Asteroid(randomNum);
                asteroids.push_back(asteroid);
                asteroidTimer = 0.0f; // Reset the timer
            }

            // Update
            //----------------------------------------------------------------------------------
            //Coordinates of Star Ship
            Vector2 v1 = { starShipPosX,starShipPosY };
            Vector2 v2 = { starShipPosX - width,starShipPosY + height };
            Vector2 v3 = { starShipPosX + width,starShipPosY + height };



            // Draw
            //----------------------------------------------------------------------------------

            BeginDrawing();
            // draw triangle
            //StarShip
            DrawTriangle(
                v1, v2, v3, MAROON       // triangle color
            );
            //Drawing All Meteors
            for (size_t i = 0; i < meteors.size(); ++i) {
                DrawRectangle(meteors[i]->x, meteors[i]->y, 5, 5, DARKBLUE);
                Vector2 mTopLeft = { meteors[i]->x, meteors[i]->y };
                Vector2 mTopRight = { meteors[i]->x + 5, meteors[i]->y };
                Vector2 mBottomLeft = { meteors[i]->x, meteors[i]->y + 5 };
                Vector2 mBottomRight = { meteors[i]->x + 5, meteors[i]->y + 5 };

                if (meteors[i]->y > screenHeight || CheckTriangleRectangleCollision(v1, v2, v3, mTopLeft, mTopRight, mBottomLeft, mBottomRight))
                {
                    delete meteors[i];
                    meteors.erase(meteors.begin() + i);
                    --i; // Adjust the loop counter since we removed an element

                }
                if (CheckTriangleRectangleCollision(v1, v2, v3, mTopLeft, mTopRight, mBottomLeft, mBottomRight))lifePoints--;
            }




            //Asteroids
            for (size_t i = 0; i < asteroids.size(); ++i) {
                DrawCircle(asteroids[i]->x, asteroids[i]->y, 40, GRAY);


                if (asteroids[i]->y > screenHeight)
                {
                    delete asteroids[i];
                    asteroids.erase(asteroids.begin() + i);
                    --i; // Adjust the loop counter since we removed an element

                }

            }



            for (size_t i = 0; i < missiles.size(); ++i) {
                DrawRectangle(missiles[i]->x, missiles[i]->y, 10, 20, RED);
                if (missiles[i]->y < 0) {
                    delete missiles[i];
                    missiles.erase(missiles.begin() + i);
                    --i;
                }
            }


        }
        else
        {
            DrawText("GameOver", 270, 400, 50, BLACK);
        }
        ClearBackground(RAYWHITE);


        EndDrawing();

    }

    for (size_t i = 0; i < meteors.size(); ++i) {
        delete meteors[i];
    }
    meteors.clear();

    for (size_t i = 0; i < missiles.size(); ++i) {
        delete missiles[i];
    }
    missiles.clear();
    for (size_t i = 0; i < asteroids.size(); ++i) {
        delete asteroids[i];
    }
    asteroids.clear();


    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


