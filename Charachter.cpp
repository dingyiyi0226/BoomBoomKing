//
//  Charachter.cpp
//  lol
//
//  Created by Oscar Bror Sjöberg on 2017-12-13.
//  Copyright © 2017 Oscar Bror Sjöberg. All rights reserved.
//

#include "Charachter.hpp"

//Screen dimension constants
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

//Scene textures
extern LTexture gCharachterTexture;

Charachter::Charachter(enum player playable)
{
    character_status = 0;
    Currentplayer = playable;
    if(Currentplayer == playerone){
        
        //Initialize the offsets
        mPosX = SCREEN_WIDTH-3*WALKING_ANIMATION_SIZE/2;
        mPosY = SCREEN_HEIGHT/2 - WALKING_ANIMATION_SIZE;
        
        //Initialize the velocity
        mVelX = 0;
        mVelY = 0;
        
        mCollider.w=WALKING_ANIMATION_SIZE;
        mCollider.h=WALKING_ANIMATION_SIZE;
        
        //Initialize the current frame
        currentFrame = 0;
        currentClip = &gSpriteClipsLeft[ currentFrame ];
    }
    
    //player two
    
    else if(Currentplayer == playertwo){
        
        //Initialize the offsets
        mPosX = WALKING_ANIMATION_SIZE/2;
        mPosY = SCREEN_HEIGHT/2 - WALKING_ANIMATION_SIZE;
        
        //Initialize the velocity
        mVelX = 0;
        mVelY = 0;
        
        mCollider.w=WALKING_ANIMATION_SIZE;
        mCollider.h=WALKING_ANIMATION_SIZE;
        
        //Initialize the current frame
        currentFrame = 0;
        currentClip = &gSpriteClipsRight[ currentFrame ];
    }
}
void Charachter::initialize(int a){
    character_status = 0;
    switch (a) {
        case playerone:
            //Initialize the offsets
            mPosX = SCREEN_WIDTH-3*WALKING_ANIMATION_SIZE/2;
            mPosY = SCREEN_HEIGHT/2 - WALKING_ANIMATION_SIZE;

            //Initialize the velocity
            mVelX = 0;
            mVelY = 0;

            mCollider.w=WALKING_ANIMATION_SIZE;
            mCollider.h=WALKING_ANIMATION_SIZE;

            //Initialize the current frame
            currentFrame = 0;
            currentClip = &gSpriteClipsLeft[ currentFrame ];
            break;
        case playertwo:
            //Initialize the offsets
            mPosX = WALKING_ANIMATION_SIZE/2;
            mPosY = SCREEN_HEIGHT/2 - WALKING_ANIMATION_SIZE;
            
            //Initialize the velocity
            mVelX = 0;
            mVelY = 0;
            
            mCollider.w=WALKING_ANIMATION_SIZE;
            mCollider.h=WALKING_ANIMATION_SIZE;
            
            //Initialize the current frame
            currentFrame = 0;
            currentClip = &gSpriteClipsRight[ currentFrame ];
            break;
    }
}


bool Charachter::loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Load Charachter texture
    if( !gCharachterTexture.loadFromFile( "elements/figure.png"  ) )
    {
        printf( "Failed to load Charachter texture!\n" );
        success = false;
    }
    else{
        if(Currentplayer== playerone){
            //Set sprite clips
            gSpriteClipsDown[ 0 ].x = 0;
            gSpriteClipsDown[ 0 ].y = 0;
            gSpriteClipsDown[ 0 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsDown[ 0 ].h =   WALKING_ANIMATION_SIZE;
            
            gSpriteClipsDown[ 1 ].x =   WALKING_ANIMATION_SIZE;
            gSpriteClipsDown[ 1 ].y = 0;
            gSpriteClipsDown[ 1 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsDown[ 1 ].h =   WALKING_ANIMATION_SIZE;
            
            gSpriteClipsDown[ 2 ].x = 2*WALKING_ANIMATION_SIZE;
            gSpriteClipsDown[ 2 ].y = 0;
            gSpriteClipsDown[ 2 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsDown[ 2 ].h =   WALKING_ANIMATION_SIZE;
            
            
            gSpriteClipsLeft[ 0 ].x = 0;
            gSpriteClipsLeft[ 0 ].y =   WALKING_ANIMATION_SIZE;
            gSpriteClipsLeft[ 0 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsLeft[ 0 ].h =   WALKING_ANIMATION_SIZE;
            
            gSpriteClipsLeft[ 1 ].x =   WALKING_ANIMATION_SIZE;
            gSpriteClipsLeft[ 1 ].y =   WALKING_ANIMATION_SIZE;
            gSpriteClipsLeft[ 1 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsLeft[ 1 ].h =   WALKING_ANIMATION_SIZE;
            
            gSpriteClipsLeft[ 2 ].x = 2*WALKING_ANIMATION_SIZE;
            gSpriteClipsLeft[ 2 ].y =   WALKING_ANIMATION_SIZE;
            gSpriteClipsLeft[ 2 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsLeft[ 2 ].h =   WALKING_ANIMATION_SIZE;
            
            
            gSpriteClipsRight[ 0 ].x = 0;
            gSpriteClipsRight[ 0 ].y = 2*WALKING_ANIMATION_SIZE;
            gSpriteClipsRight[ 0 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsRight[ 0 ].h =   WALKING_ANIMATION_SIZE;
            
            gSpriteClipsRight[ 1 ].x =   WALKING_ANIMATION_SIZE;
            gSpriteClipsRight[ 1 ].y = 2*WALKING_ANIMATION_SIZE;
            gSpriteClipsRight[ 1 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsRight[ 1 ].h =   WALKING_ANIMATION_SIZE;
            
            gSpriteClipsRight[ 2 ].x = 2*WALKING_ANIMATION_SIZE;
            gSpriteClipsRight[ 2 ].y = 2*WALKING_ANIMATION_SIZE;
            gSpriteClipsRight[ 2 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsRight[ 2 ].h =   WALKING_ANIMATION_SIZE;
            
            
            gSpriteClipsUp[ 0 ].x = 0;
            gSpriteClipsUp[ 0 ].y = 3*WALKING_ANIMATION_SIZE;
            gSpriteClipsUp[ 0 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsUp[ 0 ].h =   WALKING_ANIMATION_SIZE;
            
            gSpriteClipsUp[ 1 ].x =   WALKING_ANIMATION_SIZE;
            gSpriteClipsUp[ 1 ].y = 3*WALKING_ANIMATION_SIZE;
            gSpriteClipsUp[ 1 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsUp[ 1 ].h =   WALKING_ANIMATION_SIZE;
            
            gSpriteClipsUp[ 2 ].x = 2*WALKING_ANIMATION_SIZE;
            gSpriteClipsUp[ 2 ].y = 3*WALKING_ANIMATION_SIZE;
            gSpriteClipsUp[ 2 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsUp[ 2 ].h =   WALKING_ANIMATION_SIZE;
        }
        else if(Currentplayer==playertwo){
            
            //Set sprite clips
            gSpriteClipsDown[ 0 ].x = 0;
            gSpriteClipsDown[ 0 ].y = 4*WALKING_ANIMATION_SIZE;
            gSpriteClipsDown[ 0 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsDown[ 0 ].h =   WALKING_ANIMATION_SIZE;
            
            gSpriteClipsDown[ 1 ].x =   WALKING_ANIMATION_SIZE;
            gSpriteClipsDown[ 1 ].y = 4*WALKING_ANIMATION_SIZE;
            gSpriteClipsDown[ 1 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsDown[ 1 ].h =   WALKING_ANIMATION_SIZE;
            
            gSpriteClipsDown[ 2 ].x = 2*WALKING_ANIMATION_SIZE;
            gSpriteClipsDown[ 2 ].y = 4*WALKING_ANIMATION_SIZE;
            gSpriteClipsDown[ 2 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsDown[ 2 ].h =   WALKING_ANIMATION_SIZE;
            
            
            gSpriteClipsLeft[ 0 ].x = 0;
            gSpriteClipsLeft[ 0 ].y = 5*WALKING_ANIMATION_SIZE;
            gSpriteClipsLeft[ 0 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsLeft[ 0 ].h =   WALKING_ANIMATION_SIZE;
            
            gSpriteClipsLeft[ 1 ].x =   WALKING_ANIMATION_SIZE;
            gSpriteClipsLeft[ 1 ].y = 5*WALKING_ANIMATION_SIZE;
            gSpriteClipsLeft[ 1 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsLeft[ 1 ].h =   WALKING_ANIMATION_SIZE;
            
            gSpriteClipsLeft[ 2 ].x = 2*WALKING_ANIMATION_SIZE;
            gSpriteClipsLeft[ 2 ].y = 5*WALKING_ANIMATION_SIZE;
            gSpriteClipsLeft[ 2 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsLeft[ 2 ].h =   WALKING_ANIMATION_SIZE;
            
            
            gSpriteClipsRight[ 0 ].x = 0;
            gSpriteClipsRight[ 0 ].y = 6*WALKING_ANIMATION_SIZE;
            gSpriteClipsRight[ 0 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsRight[ 0 ].h =   WALKING_ANIMATION_SIZE;
            
            gSpriteClipsRight[ 1 ].x =   WALKING_ANIMATION_SIZE;
            gSpriteClipsRight[ 1 ].y = 6*WALKING_ANIMATION_SIZE;
            gSpriteClipsRight[ 1 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsRight[ 1 ].h =   WALKING_ANIMATION_SIZE;
            
            gSpriteClipsRight[ 2 ].x = 2*WALKING_ANIMATION_SIZE;
            gSpriteClipsRight[ 2 ].y = 6*WALKING_ANIMATION_SIZE;
            gSpriteClipsRight[ 2 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsRight[ 2 ].h =   WALKING_ANIMATION_SIZE;
            
            
            gSpriteClipsUp[ 0 ].x = 0;
            gSpriteClipsUp[ 0 ].y = 7*WALKING_ANIMATION_SIZE;
            gSpriteClipsUp[ 0 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsUp[ 0 ].h =   WALKING_ANIMATION_SIZE;
            
            gSpriteClipsUp[ 1 ].x =   WALKING_ANIMATION_SIZE;
            gSpriteClipsUp[ 1 ].y = 7*WALKING_ANIMATION_SIZE;
            gSpriteClipsUp[ 1 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsUp[ 1 ].h =   WALKING_ANIMATION_SIZE;
            
            gSpriteClipsUp[ 2 ].x = 2*WALKING_ANIMATION_SIZE;
            gSpriteClipsUp[ 2 ].y = 7*WALKING_ANIMATION_SIZE;
            gSpriteClipsUp[ 2 ].w =   WALKING_ANIMATION_SIZE;
            gSpriteClipsUp[ 2 ].h =   WALKING_ANIMATION_SIZE;
        }
        
    }
    
    return success;
}

void Charachter::handleEventFrame( SDL_Event& e)
{
    
    if(Currentplayer == playerone){
        //If a key was pressed
        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
        {
            
            //Adjust the velocity and choose moving frame direction
            switch( e.key.keysym.sym )
            {
                case SDLK_UP:
                    mVelY -=CHAR_VEL;
                    break;
                case SDLK_DOWN:
                    mVelY += CHAR_VEL;
                    break;
                case SDLK_LEFT:
                    mVelX -= CHAR_VEL;
                    break;
                case SDLK_RIGHT:
                    mVelX += CHAR_VEL;
                    break;
            }

        }
        //If a key was released
            else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
        {
            //Adjust the velocity
            switch( e.key.keysym.sym )
            {
                case SDLK_UP:
                    mVelY += CHAR_VEL;
                    break;
                case SDLK_DOWN:
                    mVelY -= CHAR_VEL;
                    break;
                case SDLK_LEFT:
                    mVelX += CHAR_VEL;
                    break;
                case SDLK_RIGHT:
                    mVelX -= CHAR_VEL;
                    break;
            }
        }
    }
    else if(Currentplayer == playertwo){
        
        //If a key was pressed
        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
        {
            //Adjust the velocity and choose moving frame direction
            switch( e.key.keysym.sym )
            {
                case SDLK_e:
                    mVelY -=CHAR_VEL;
                    break;
                case SDLK_d:
                    mVelY += CHAR_VEL;
                    break;
                case SDLK_s:
                    mVelX -= CHAR_VEL;
                    break;
                case SDLK_f:
                    mVelX += CHAR_VEL;
                    break;
            }
        }
        //If a key was released
        else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
        {
            
            //Adjust the velocity
            switch( e.key.keysym.sym )
            {
                case SDLK_e:
                    mVelY += CHAR_VEL;
                    break;
                case SDLK_d:
                    mVelY -= CHAR_VEL;
                    break;
                case SDLK_s:
                    mVelX += CHAR_VEL;
                    break;
                case SDLK_f:
                    mVelX -= CHAR_VEL;
                    break;
            }
        }
    }
}

void Charachter::move( SDL_Rect* walls )
{
    currentFrame++;
    if(currentFrame>=9){currentFrame=0;}

    if(mVelX>0){  currentClip = &gSpriteClipsRight[ currentFrame/3];}
    if(mVelX<0){  currentClip = &gSpriteClipsLeft[ currentFrame/3 ]; }

    //Move the Charachter left or right
    mPosX += mVelX;
    mCollider.x = mPosX;

    //If the Charachter went too far to the left or right
    if( ( mPosX < SCREEN_WIDTH*1/64. ) || ( mPosX + CHAR_WIDTH > SCREEN_WIDTH*63/64. ) ||(checkCollision(mCollider, walls)) )
    {
        //Move back
        mPosX -= mVelX;
        mCollider.x = mPosX;
    }

    //Move the Charachter up or down
    if(mVelY>0){  currentClip = &gSpriteClipsDown[ currentFrame/3  ]; }
    if(mVelY<0){  currentClip = &gSpriteClipsUp[ currentFrame/3 ];  }

    mPosY += mVelY;
    mCollider.y = mPosY;

    //If the Charachter went too far up or down
    if( ( mPosY < SCREEN_HEIGHT*1/128. ) || ( mPosY + CHAR_HEIGHT > SCREEN_HEIGHT*31/32. ) ||(checkCollision(mCollider, walls)))
    {
        //Move back
        mPosY -= mVelY;
        mCollider.y = mPosY;
    }
}

void Charachter::render()
{
    //Show the Charachter
    gCharachterTexture.render( mPosX, mPosY, currentClip);
}

bool Charachter::checkCollision( SDL_Rect a, SDL_Rect *b )
{
    SDL_Rect temp[15][15];
    
    bool overallcollide=false;
    bool collide[15][15];
    for(int i=0;i<15;i++){
        for(int j=0 ;j<15;j++){

            temp[i][j] = *(b+15*i+j);
            //The sides of the rectangles
            int leftA, leftB;
            int rightA, rightB;
            int topA, topB;
            int bottomA, bottomB;
            
            //Calculate the sides of rect A
            leftA = a.x;
            rightA = a.x + a.w;
            topA = a.y;
            bottomA = a.y + a.h;
            
            //Calculate the sides of rect B
            leftB = temp[i][j].x;
            rightB = temp[i][j].x + temp[i][j].w;
            topB = temp[i][j].y;
            bottomB = temp[i][j].y + temp[i][j].h;
            
            //If any of the sides from A are outside of B
            if( bottomA <= topB )
            {
                collide[i][j] =  false;
            }
            else if( topA >= bottomB )
            {
                collide[i][j] =  false;
            }
            
            else if( rightA <= leftB )
            {
                collide[i][j] =  false;
            }
            else if( leftA >= rightB )
            {
                collide[i][j] =  false;
            }
            else collide[i][j] =  true;
        }
    }
    
    //If none of the sides from every A are outside B
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            overallcollide = overallcollide||collide[i][j];
        }
    }
    return overallcollide;
}

double Charachter::getposx(){
    return mPosX+CHAR_WIDTH/2;
//    return mPosX;
}
double Charachter::getposy(){
    return mPosY+CHAR_HEIGHT/2;
//    return mPosY;
}
int Charachter::get_index_x(){
    int x_index = floor(((getposx()*32/SCREEN_WIDTH)-1)/2);
    return x_index;
}
int Charachter::get_index_y(){
    int y_index = floor(((getposy()*32/SCREEN_HEIGHT)-1)/2);
    return y_index;
}
void Charachter::set_character_status(int a){
    character_status = a;
}
void Charachter::reset_character_status(){
    character_status = 0;
}
int Charachter::get_character_status(){
    return character_status;
}




