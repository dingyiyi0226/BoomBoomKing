//
//  background.cpp
//  background
//
//  Created by dingyiyi on 2017/12/12.
//  Copyright © 2017年 dingyiyi. All rights reserved.
//

#include <iostream>
#include "background.hpp"
#include "LTexture.hpp"
#include <string>
#include <cmath>

//Scene textures
extern LTexture box;
extern LTexture background;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

Background::Background(){
    //Initialize
    BLOCK_WIDTH=0;
    BLOCK_HEIGHT=0;
    BOX_WIDTH=0;
    BOX_HEIGHT=0;
}

//Render background to the screen
void Background::background_rendering(){
    background.render_fourint( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}
//Render blocks to the screen
void Background::box_rendering(){
    //block size
    BLOCK_WIDTH = SCREEN_WIDTH/16;
    BLOCK_HEIGHT = SCREEN_HEIGHT/16;
    //box size
    BOX_WIDTH=BLOCK_WIDTH;
    BOX_HEIGHT=BLOCK_HEIGHT*4/3;
    
    for(int i=0;i<15;i++){
        if((i!=1)&&(i!=3)&&(i!=5)&&(i!=9)&&(i!=11)&&(i!=13)) continue;
        for(int j=0;j<15;j++){
            if((j!=1)&&(j!=3)&&(j!=5)&&(j!=9)&&(j!=11)&&(j!=13)) continue;
            box.render_fourint((BLOCK_WIDTH/2+j*BLOCK_WIDTH), (BLOCK_HEIGHT/2+i*BLOCK_HEIGHT-BLOCK_HEIGHT/3), BOX_WIDTH, BOX_HEIGHT);
            blockwall[i][j].x=j*BLOCK_WIDTH+BLOCK_WIDTH/2.+BLOCK_WIDTH/6.;
            blockwall[i][j].y=i*BLOCK_HEIGHT+BLOCK_HEIGHT/2.+BLOCK_HEIGHT/6.;
            blockwall[i][j].w=BLOCK_WIDTH*2/3.;
            blockwall[i][j].h=BLOCK_HEIGHT/2.;
        }
    }
}
void Background::box_rerendering(int x_index , int y_index){
    
    y_index += 1;
    //block size
    BLOCK_WIDTH = SCREEN_WIDTH/16;
    BLOCK_HEIGHT = SCREEN_HEIGHT/16;
    //box size
    BOX_WIDTH=BLOCK_WIDTH;
    BOX_HEIGHT=BLOCK_HEIGHT*4/3;
    
    box.render_fourint((BLOCK_WIDTH/2+x_index*BLOCK_WIDTH), (BLOCK_HEIGHT/2+y_index*BLOCK_HEIGHT-BLOCK_HEIGHT/3), BOX_WIDTH, BOX_HEIGHT);
}
bool Background::check_character_behind_box(int x_index, int y_index){
 
    y_index += 1;

    for(int i=0;i<15;i++){
        if((i!=1)&&(i!=3)&&(i!=5)&&(i!=9)&&(i!=11)&&(i!=13)) continue;
        for(int j=0;j<15;j++){
            if((j!=1)&&(j!=3)&&(j!=5)&&(j!=9)&&(j!=11)&&(j!=13)) continue;
            if(i==x_index&&j==y_index) return true;
        }
    }
    
    return false;
}

bool Background::loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Load background image
    if( !background.loadFromFile( "elements/bg.bmp" ) )
    {
        printf( "Failed to load background image!\n" );
        success = false;
    }
    
    //Load block texture
    if( !box.loadFromFile( "elements/box.bmp" ) )
    {
        printf( "Failed to load box image!\n" );
        success = false;
    }
    
    return success;
}
