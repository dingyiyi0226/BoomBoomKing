//
//  Charachter.hpp
//  lol
//
//  Created by Oscar Bror Sjöberg on 2017-12-13.
//  Copyright © 2017 Oscar Bror Sjöberg. All rights reserved.
//

#ifndef Charachter_hpp
#define Charachter_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>
#include "LTexture.hpp"

enum player
{
    playerone = 0,
    playertwo = 1,
    
};


//The Charachter that will move around on the screen
class Charachter
{
public:
    //The dimensions of the Charachter
    static const int CHAR_WIDTH = 32;//
    static const int CHAR_HEIGHT = 32;//
    
    //Maximum axis velocity of the Charachter
    static const double CHAR_VEL = 1;//
    
    //Initializes the variables
    Charachter(enum player playable);
    
    //Takes key presses and adjusts the dot's velocity
    void handleEventFrame( SDL_Event& e);
    
    //Get current frame
    int GetcurretFrame(){ return currentFrame; };
    
    void IncreaseFrame(){
        currentFrame++;
        if(currentFrame>=9) {currentFrame=0;}
    }
    
    
    //Moves the Charachter
    void move(SDL_Rect*);
    
    //Shows the Charachter on the screen
    void render();
    
    
    //Loads the media to charachter class
    bool loadMedia();
    
    bool checkCollision( SDL_Rect a, SDL_Rect* b );
    double getposx();
    double getposy();
    int get_index_x();
    int get_index_y();
    void set_character_status(int);
    void reset_character_status();
    int get_character_status();
    void initialize(int);
//    Charachter& operator= (const Charachter& a) = default;

    
private:
    //Player number 1 or 2
    int player;
    
    //The X and Y offsets of the Charachter
    double mPosX, mPosY;//
    
    //The velocity of the Charachter
    double mVelX, mVelY;//
    
    int character_status;
    //Current display rectangle
    SDL_Rect* currentClip;
    
    //Current frame
    int currentFrame;
    
    //Walking animation
    const int WALKING_ANIMATION_FRAMES = 3;
    SDL_Rect gSpriteClipsUp[ 3 ];
    SDL_Rect gSpriteClipsDown[ 3 ];
    SDL_Rect gSpriteClipsLeft[ 3 ];
    SDL_Rect gSpriteClipsRight[ 3 ];
    
    SDL_Rect mCollider;
    
    //Size per frame x and y direction
    int WALKING_ANIMATION_SIZE = 32;
    
    enum player Currentplayer;
};

#endif /* Charachter_hpp */
