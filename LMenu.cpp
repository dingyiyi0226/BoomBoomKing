//
//  LMenu.cpp
//  lol
//
//  Created by Oscar Bror Sjöberg on 2017-12-25.
//  Copyright © 2017 Oscar Bror Sjöberg. All rights reserved.
//

#include "LMenu.hpp"

extern LMenu ButtonQuit;
extern LMenu ButtonGame;
extern LTexture gMenuBackground;



bool LMenu::loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Load Charachter texture
    if( !gButtonGame.loadFromFile( "elements/buttons.png"  ) )
    {
        printf( "Failed to load Charachter texture!\n" );
        success = false;
    }
    else{
        
        
        gSpritePlayGame[ 0 ].x =0;
        gSpritePlayGame[ 0 ].y =0;
        gSpritePlayGame[ 0 ].w =WIDTH;
        gSpritePlayGame[ 0 ].h =HEIGHT;
        
        gSpritePlayGame[ 1 ].x =0;
        gSpritePlayGame[ 1 ].y =HEIGHT;
        gSpritePlayGame[ 1 ].w =WIDTH;
        gSpritePlayGame[ 1 ].h =HEIGHT;
        
        
    }
    
    //Load Charachter texture
    if( !gButtonQuit.loadFromFile( "elements/buttons.png"  ) )
    {
        printf( "Failed to load Charachter texture!\n" );
        success = false;
    }
    else{
        
        gSpriteQuit[ 0 ].x = 0;
        gSpriteQuit[ 0 ].y =   2*HEIGHT;
        gSpriteQuit[ 0 ].w =  WIDTH;
        gSpriteQuit[ 0 ].h = HEIGHT;
        
        
        gSpriteQuit[ 1 ].x =   0;
        gSpriteQuit[ 1 ].y =   3*HEIGHT;
        gSpriteQuit[ 1 ].w =  WIDTH;
        gSpriteQuit[ 1 ].h = HEIGHT;}
    
    
    //Load Charachter texture
    if( !gMenuBackground.loadFromFile( "elements/Blast-Pic.jpg"  ) )
    {
        printf( "Failed to load Menu Background texture!\n" );
        success = false;
    }
    
    
    return success;
};

LMenu::LMenu()
{
    
    
    mPositionGame.x = (SCREEN_WIDTH-WIDTH)/2;
    mPositionGame.y = (SCREEN_HEIGHT/2)-HEIGHT;
    mPositionQuit.x = (SCREEN_WIDTH-WIDTH)/2;
    mPositionQuit.y = (SCREEN_HEIGHT)/2;
    
    mCurrentSpriteGame = BUTTON_SPRITE_MOUSE_OUT;
    mCurrentSpriteGame = BUTTON_SPRITE_MOUSE_OUT;
    
//    gameBool;
};

void LMenu::setPositionGame( int x, int y )
{
    mPositionGame.x = x;
    mPositionGame.y = y;
};

void LMenu::setPositionQuit( int x, int y )
{
    mPositionQuit.x = x;
    mPositionQuit.y = y;
};
void LMenu::set_gamebool(bool a){
    gameBool = a;
}


int LMenu::handleEvent( SDL_Event* e )
{
    //If mouse event happened
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );
        
        //Check if mouse is in button
        bool game_inside = true;
        
        //Mouse is left of the button
        if( x < mPositionGame.x )
        {
            game_inside = false;
        }
        //Mouse is right of the button
        else if( x > mPositionGame.x + WIDTH )
        {
            game_inside = false;
        }
        //Mouse above the button
        else if( y < mPositionGame.y )
        {
            game_inside = false;
        }
        //Mouse below the button
        else if( y > mPositionGame.y + HEIGHT )
        {
            game_inside = false;
        }
        
        //Mouse is outside button
        if( !game_inside )
        {
            mCurrentSpriteGame = BUTTON_SPRITE_MOUSE_OUT;
            
            
            //Check if mouse is in button
            bool quit_inside = true;
            
            //Mouse is left of the button
            if( x < mPositionQuit.x )
            {
                quit_inside = false;
            }
            //Mouse is right of the button
            else if( x > mPositionQuit.x + WIDTH )
            {
                quit_inside = false;
            }
            //Mouse above the button
            else if( y < mPositionQuit.y )
            {
                quit_inside = false;
            }
            //Mouse below the button
            else if( y > mPositionQuit.y + HEIGHT )
            {
                quit_inside = false;
            }
            
            //Mouse is outside button
            if( !quit_inside )
            {
                mCurrentSpriteQuit = BUTTON_SPRITE_MOUSE_OUT;
            }
            //Mouse is inside button
            else
            {
                //Set mouse over sprite
                switch( e->type )
                {
                    case SDL_MOUSEMOTION:
                        mCurrentSpriteQuit = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                        break;
                        
                    case SDL_MOUSEBUTTONDOWN:
                        mCurrentSpriteQuit = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                        break;
                        
                    case SDL_MOUSEBUTTONUP:
                        mCurrentSpriteQuit = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                        return 1;
//                        SDL_Quit();
                        break;
                }
            }
        }
        //Mouse is inside button
        else
        {
            mCurrentSpriteQuit = BUTTON_SPRITE_MOUSE_OUT;
            //Set mouse over sprite
            switch( e->type )
            {
                case SDL_MOUSEMOTION:
                    mCurrentSpriteGame = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    mCurrentSpriteGame = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    gameBool=true;
                    break;
                    
                case SDL_MOUSEBUTTONUP:
                    mCurrentSpriteGame = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    gameBool=true;
                    break;
            }
        }
    }
    return 0;
}


