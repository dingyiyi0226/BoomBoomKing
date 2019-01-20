//
//  mine.hpp
//  boomboomking
//
//  Created by dingyiyi on 2017/12/29.
//  Copyright © 2017年 dingyiyi. All rights reserved.
//

#ifndef landmine_hpp
#define landmine_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

extern int SCREEN_WIDTH ;
extern int SCREEN_HEIGHT;
extern SDL_Renderer* gRenderer;

class Landmine{
private:
    int landmine_index_x,landmine_index_y;
    
public:
    Landmine();
    int landmine_index[15][15];
    
    int get_landmine_index_x();
    int get_landmine_index_y();
    void set_landmine(int&, int&);
    void reset_landmine(int, int);

    void landmine_rendering(int, int);
    bool landmine_detect(int, int);
    
    
    void load_landmine(SDL_Texture*, int ,int );
    void landmine_display(int, int);
    void fire_display(int, int);
  
    SDL_Texture* loadTexture( std::string path );
    SDL_Texture* landmine_texture;
    SDL_Texture* fire_middle ;
    SDL_Texture* fire_up ;
    SDL_Texture* fire_down ;
    SDL_Texture* fire_left ;
    SDL_Texture* fire_right ;
    
    bool loadMedia();
    void free();
};

#endif /* landmine_hpp */
