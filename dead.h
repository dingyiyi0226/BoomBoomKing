#ifndef dead_h
#define dead_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include "Charachter.hpp"

extern int SCREEN_WIDTH ;
extern int SCREEN_HEIGHT;
extern SDL_Renderer* gRenderer;
extern SDL_Window* gWindow ;

class Dead{
private:
    int dead_x_index,dead_y_index;
    double dead_x,dead_y;
    
public:
    Dead();
    //Modulation component
    Uint8 a;
    bool loadMedia();
    void free();
    bool set_dead_position(Charachter& );
    bool show_figure(Charachter& );
    void show_title1();
    void show_title2();
    
    //Set blending
    void setBlendMode( SDL_BlendMode blending,SDL_Texture* );
    
    //Set alpha modulation
    void setAlpha( Uint8 alpha ,SDL_Texture*);
    
    //Loads individual image as texture
    SDL_Texture* loadTexture( std::string path );
    
    SDL_Texture* dead_texture;
    SDL_Texture* player1_win;
    SDL_Texture* player2_win;
    
}; 
#endif
