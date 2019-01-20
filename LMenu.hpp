//
//  LMenu.hpp
//  lol
//
//  Created by Oscar Bror Sjöberg on 2017-12-25.
//  Copyright © 2017 Oscar Bror Sjöberg. All rights reserved.
//

#ifndef LButton_hpp
#define LButton_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "LTexture.hpp"


//Screen dimension constants
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;


//Texture for Menu
extern LTexture gButtonQuit;
extern LTexture gButtonGame;
extern LTexture gMenuBackground;

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    
};

//The mouse button
class LMenu
{
public:
    //Initializes internal variables button type 1 = gamebutton 2 = quitbutton
    LMenu();
    
    //Sets top left position
    void setPositionGame( int x, int y );
    
    void setPositionQuit( int x, int y );
    
    //Handles mouse event
    int handleEvent( SDL_Event* e );
    
    //Shows button sprite
    void render()
    {
        
        gMenuBackground.render_fourint(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);///////////this line
        
        //Show current button sprite
        gButtonGame.render( mPositionGame.x, mPositionGame.y, &gSpritePlayGame[ mCurrentSpriteGame ] );
        
        
        gButtonQuit.render(mPositionQuit.x, mPositionQuit.y, &gSpriteQuit[ mCurrentSpriteQuit ] );
        
        
        
    }
    
    //Loader of images to texture
    
    bool loadMedia();
    
    bool GameBool() {return gameBool;};
    void set_gamebool(bool);
    
private:
    
    
    SDL_Point mPositionGame;
    SDL_Point mPositionQuit;
    
    //SDL rectangle
    LButtonSprite mCurrentSpriteGame;
    LButtonSprite mCurrentSpriteQuit;
    
    
    //Sprites for mouse hoovering
    SDL_Rect gSpritePlayGame[ 2 ];
    SDL_Rect gSpriteQuit[ 2 ];
    
    //Button constants
    //Dimensions
    int HEIGHT = 105;
    int WIDTH = 230;
    
    bool gameBool;
    
    
    
    
};




#endif /* LButton_hpp */
