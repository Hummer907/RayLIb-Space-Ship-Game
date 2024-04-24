// Sprite.h
#include "raylib.h"

class Sprite
{
public:
    Texture2D texture;
    Rectangle sourceRec; // Sprite Frame
    Rectangle destRec;   // Screen Rec Dest
    Vector2 origin;
    float rotation;
    Color tint;
    float* frameWidths; // Array of frame widths
    float FrameHeight;
    float ScaleWidht ;
    float ScaleHeight;
    int quantityFrames;
    int currentFrame;
    float TIMER = 0;
    float INTERVAL_ANIMATION = 0.5f;
    Sprite();
    Sprite(const char* texture, int quantityFrames, float ANIMATION_SPEED, float* frameWidths, float ScaleWidth, float ScaleHeight);
    void Draw(float x, float y);
};
