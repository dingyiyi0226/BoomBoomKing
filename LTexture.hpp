//
//  LTexture.hpp
//  background
//
//  Created by dingyiyi on 2017/12/13.
//  Copyright © 2017年 dingyiyi. All rights reserved.
//

#ifndef LTexture_hpp
#define LTexture_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture();
    
    //Deallocates memory
    ~LTexture();
    
    //Loads image at specified path
    bool loadFromFile( std::string path );
    
    //Deallocates texture
    void free();
    
    //Renders texture at given point
    void render_fourint( int x, int y , int w, int h);
    
    void render( int x, int y, SDL_Rect* clip );
    
    //Gets image dimensions
    int getWidth();
    int getHeight();
    
private:
    //The actual hardware texture
    SDL_Texture* mTexture;
    
    //Image dimensions
    int mWidth;
    int mHeight;
};

#endif /* LTexture_hpp */
