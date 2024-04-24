// Sprite.cpp
#include "Sprite.h"
#include <iostream>
Sprite::Sprite() {}

Sprite::Sprite(const char* textureFile, int quantityFrames, float ANIMATION_SPEED, float* frameWidths,float ScaleWidth,float ScaleHeight)
{
    this->texture = LoadTexture(textureFile);
    this->FrameHeight = this->texture.height;
    this->sourceRec = { 0, 0, frameWidths[0], this->FrameHeight }; // Sprite Frame
    this->origin = { 0, 0 };
    this->rotation = 0;
    this->tint = WHITE;
    this->currentFrame = 0;
    this->quantityFrames = quantityFrames;
    this->INTERVAL_ANIMATION = ANIMATION_SPEED;
    this->frameWidths = frameWidths;
    this->ScaleHeight = ScaleHeight;
    this->ScaleWidht = ScaleWidht;
}


void Sprite::Draw(float x, float y)
{
    if (this->currentFrame >= this->quantityFrames) {
        this->currentFrame = 0;
        this->sourceRec.x = 0;
    }
    this->destRec = { x, y, this->frameWidths[currentFrame] * ScaleWidht, this->FrameHeight * ScaleHeight }; // Screen Location
    TIMER += GetFrameTime();
    this->sourceRec.width = this->frameWidths[currentFrame]; // Update frame width
 
    DrawTexturePro(this->texture, this->sourceRec, this->destRec, this->origin, this->rotation, this->tint);

    if (TIMER > INTERVAL_ANIMATION)
    {
        
        
        this->sourceRec.x += this->frameWidths[this->currentFrame]; // Update sourceRec.x
        this->currentFrame += 1;
        std::cout << currentFrame << " x:   " << sourceRec.x <<"   width:  " <<sourceRec.width << "   height:"<<destRec.height<<"     " << destRec.y + destRec.height << "    " << "\n";
        TIMER = 0;
    }
    
    
    
}

