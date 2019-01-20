//
//  tools.hpp
//  boomboomking
//
//  Created by dingyiyi on 2017/12/27.
//  Copyright © 2017年 dingyiyi. All rights reserved.
//

#ifndef tools_hpp
#define tools_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cstdlib>
#include "LTexture.hpp"

class tools{
private:
    int tools_map[15][15];
    int big_cross_posx;
    int big_cross_posy;
    int immortal_spell_posx;
    int immortal_spell_posy;
    
public:
    tools();

    enum tools_number{
        DEFAULT    =0,
        BIG_CROSS  =1,
        IMMORTAL   =2
    };
    void set_tool();
    int pick_up_tools(int, int);
    void big_cross_rendering();
    bool loadMedia();
    void immortal_spell_rendering();
};






#endif /* tools_hpp */
