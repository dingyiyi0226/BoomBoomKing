//
//  background.hpp
//  background
//
//  Created by dingyiyi on 2017/12/12.
//  Copyright © 2017年 dingyiyi. All rights reserved.
//

#ifndef background_hpp
#define background_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "LTexture.hpp"

class Background{

public:
    Background();
    bool loadMedia();
    void background_rendering();
    void box_rendering();
    void box_rerendering(int, int);
    bool check_character_behind_box(int, int);
    SDL_Rect blockwall[15][15];//-----blockwall[y-axis][x-axis]
private:
    //block size
    int BLOCK_WIDTH;
    int BLOCK_HEIGHT;
    int BOX_WIDTH;
    int BOX_HEIGHT;
};

#endif /* background_hpp */
