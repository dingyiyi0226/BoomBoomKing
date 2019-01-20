//
//  mine.cpp
//  boomboomking
//
//  Created by dingyiyi on 2017/12/29.
//  Copyright © 2017年 dingyiyi. All rights reserved.
//

#include "landmine.hpp"
#include "LTexture.hpp"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern SDL_Renderer* gRenderer;
//extern LTexture landmine_texture;

Landmine::Landmine(){
    landmine_index_x = 0;
    landmine_index_y = 0;
    
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            landmine_index[i][j]=0;
        }
    }

}
int Landmine::get_landmine_index_x(){
    return landmine_index_x;
}
int Landmine::get_landmine_index_y(){
    return landmine_index_y;
}

void Landmine::set_landmine(int &x, int &y){
    landmine_index_x = x;
    landmine_index_y = y;
    landmine_index[y][x] = 1;
}
void Landmine::reset_landmine(int x, int y){
    landmine_index_x = 0;
    landmine_index_y = 0;
    landmine_index[y][x] = 0;
}

void Landmine::load_landmine(SDL_Texture *a, int x, int y){
    SDL_Rect topLeftViewport;
    topLeftViewport.x = x*SCREEN_WIDTH/16+SCREEN_WIDTH/32;
    topLeftViewport.y = y*SCREEN_HEIGHT/16+SCREEN_HEIGHT/32;
    topLeftViewport.w = SCREEN_WIDTH/16;
    topLeftViewport.h = SCREEN_HEIGHT/16;
    //Render texture to screen
    SDL_RenderCopy( gRenderer, a, NULL, &topLeftViewport );
}
void Landmine::landmine_display(int x,int y)    {load_landmine(landmine_texture,x,y);}

void Landmine::fire_display(int x, int y){
    bool special_case=false;
    load_landmine(fire_middle,x,y);
    
    for(int i=0;i<15;i++){
        if((i!=0)&&(i!=2)&&(i!=4)&&(i!=6)&&(i!=8)&&(i!=10)&&(i!=12)&&(i!=14)) continue;
        for(int j=0;j<15;j++){
            if((j!=1)&&(j!=3)&&(j!=5)&&(j!=9)&&(j!=11)&&(j!=13)) continue;
            if(y==i&&x==j){
                if(x!=0)  {load_landmine(fire_left,x-1,y);}
                if(x!=14) {load_landmine(fire_right,x+1,y);}
                if(i==6)  {load_landmine(fire_down,x,y+1);}
                if(i==8)  {load_landmine(fire_up,x,y-1);}
                special_case=true;
            }
            if(x==i&&y==j){
                if(y!=0)  {load_landmine(fire_up,x,y-1);}
                if(y!=14) {load_landmine(fire_down,x,y+1);}
                if(i==6)  {load_landmine(fire_right,x+1,y);}
                if(i==8)  {load_landmine(fire_left,x-1,y);}
                special_case=true;
            }
        }
    }
    if(!special_case){
        if(y!=0)  {load_landmine(fire_up,x,y-1);}
        if(y!=14) {load_landmine(fire_down,x,y+1);}
        if(x!=0)  {load_landmine(fire_left,x-1,y);}
        if(x!=14) {load_landmine(fire_right,x+1,y);}
    }
}

bool Landmine::landmine_detect(int x, int y){
    bool detect_success=false;
    if (landmine_index[y][x]==1) detect_success=true;
    return detect_success;
}

SDL_Texture* Landmine::loadTexture( std::string path ){
    //The final texture
    SDL_Texture* newTexture = NULL;
    
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0xFF, 0xFF ) );
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    
    return newTexture;
}


bool Landmine::loadMedia(){
    //Loading success flag
    bool success = true;
    
    landmine_texture      = loadTexture( "elements/landmine.png" );
    fire_middle           = loadTexture( "elements/fire_mdl.png" );
    fire_up               = loadTexture( "elements/fire_up.png" );
    fire_down             = loadTexture( "elements/fire_down.png" );
    fire_left             = loadTexture( "elements/fire_left.png" );
    fire_right            = loadTexture( "elements/fire_right.png" );
    
    if( landmine_texture == NULL )
    {
        printf( "Failed to load fire_middle image!\n" );
        success = false;
    }
    if( fire_middle == NULL )
    {
        printf( "Failed to load fire_middle image!\n" );
        success = false;
    }
    if( fire_up == NULL )
    {
        printf( "Failed to load fire_up image!\n" );
        success = false;
    }
    if( fire_down == NULL )
    {
        printf( "Failed to load fire_down image!\n" );
        success = false;
    }
    if( fire_left == NULL )
    {
        printf( "Failed to load fire_left image!\n" );
        success = false;
    }
    if( fire_right == NULL )
    {
        printf( "Failed to load fire_right image!\n" );
        success = false;
    }
    
    return success;
}

void Landmine::free(){
    landmine_index_x = 0;
    landmine_index_y = 0;
    if(landmine_texture!=NULL)         {SDL_DestroyTexture(landmine_texture);}
    if(fire_middle!=NULL)              {SDL_DestroyTexture(fire_middle);}
    if(fire_up!=NULL)                  {SDL_DestroyTexture(fire_up);}
    if(fire_down!=NULL)                {SDL_DestroyTexture(fire_down);}
    if(fire_left!=NULL)                {SDL_DestroyTexture(fire_left);}
    if(fire_right!=NULL)               {SDL_DestroyTexture(fire_right);}
    
}






