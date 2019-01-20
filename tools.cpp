//
//  tools.cpp
//  boomboomking
//
//  Created by dingyiyi on 2017/12/27.
//  Copyright © 2017年 dingyiyi. All rights reserved.
//

#include <iostream>
#include <ctime>
#include "tools.hpp"


extern LTexture big_cross;
extern LTexture immortal_spell;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;


tools::tools(){
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            tools_map[i][j]=0;
        }
    }
}

void tools::set_tool(){
    srand((int) time(NULL));
    
    big_cross_posx = rand()%15;
    big_cross_posy = rand()%15;
    immortal_spell_posx =rand()%15;
    immortal_spell_posy =rand()%15;
    for(int i=0;i<15;i++){
        if((i!=1)&&(i!=3)&&(i!=5)&&(i!=9)&&(i!=11)&&(i!=13)) continue;
        for(int j=0;j<15;j++){
            if((j!=1)&&(j!=3)&&(j!=5)&&(j!=9)&&(j!=11)&&(j!=13)) continue;
            if(big_cross_posx==i && big_cross_posy==j){
                big_cross_posx+=1;
                big_cross_posy+=1;
            }
            if(immortal_spell_posx==i && immortal_spell_posy==j){
                immortal_spell_posy+=1;
            }
        }
    }

    tools_map[big_cross_posy][big_cross_posx] = BIG_CROSS;
    tools_map[immortal_spell_posy][immortal_spell_posx] = IMMORTAL;
    
}

int tools::pick_up_tools(int x, int y){
    int return_value=0;
    switch (tools_map[y][x]) {
        case BIG_CROSS:
            tools_map[y][x] = DEFAULT;
            return_value = 1;
            break;
        case IMMORTAL:
            tools_map[y][x] = DEFAULT;
            return_value = 2;
            break;
    }
    return return_value;
}
void tools::big_cross_rendering(){
    int x = big_cross_posx*SCREEN_WIDTH/16 + SCREEN_WIDTH/32;
    int y = big_cross_posy*SCREEN_HEIGHT/16 + SCREEN_HEIGHT/32;
    int w = SCREEN_WIDTH/16;
    int h = SCREEN_HEIGHT/16;
    big_cross.render_fourint(x, y, w, h);
}

void tools::immortal_spell_rendering(){
    int x = immortal_spell_posx*SCREEN_WIDTH/16 + SCREEN_WIDTH/32;
    int y = immortal_spell_posy*SCREEN_HEIGHT/16 + SCREEN_HEIGHT/32;
    int w = SCREEN_WIDTH/16;
    int h = SCREEN_HEIGHT/16;
    immortal_spell.render_fourint(x, y, w, h);
    
}
bool tools::loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Load image
    if( !big_cross.loadFromFile( "elements/add_bomb.png" ) )
    {
        printf( "Failed to load add_bomb image!\n" );
        success = false;
    }
    if( !immortal_spell.loadFromFile( "elements/immortal_spell.png" ) )
    {
        printf( "Failed to load immortal_spell image!\n" );
        success = false;
    }

    return success;
}

