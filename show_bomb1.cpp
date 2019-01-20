
#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "show_bomb1.h"
#include "Charachter.hpp"


extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern SDL_Renderer* gRenderer;
//character class
extern Charachter charachter1;
extern Charachter charachter2;


Bomb::Bomb(){
    bomb_x=0;
    bomb_y=0;
    bomb_x_index=0;
    bomb_y_index=0;
    tool2_x=NULL;
    tool2_y=NULL;
    bomb_length=1;
    bomb_character=0;

    show_bomb_completely=false;
    show_bomb_begin=false;

    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            bomb_index[i][j]=0;
        }
    }
}

void Bomb::set_bomb_position(double &x,double &y){

    bomb_x_index = floor(((x*32/SCREEN_WIDTH)-1)/2);
    bomb_y_index = floor(((y*32/SCREEN_HEIGHT)-1)/2);
    bomb_x = bomb_x_index*SCREEN_WIDTH/16 + SCREEN_WIDTH/32;
    bomb_y = bomb_y_index*SCREEN_HEIGHT/16 + SCREEN_HEIGHT/32;
}
void Bomb::load_bomb(SDL_Texture* a,int x,int y){

    SDL_Rect topLeftViewport;
    topLeftViewport.x = x*SCREEN_WIDTH/16+SCREEN_WIDTH/32;
    topLeftViewport.y = y*SCREEN_HEIGHT/16+SCREEN_HEIGHT/32;
    topLeftViewport.w = SCREEN_WIDTH/16;
    topLeftViewport.h = SCREEN_HEIGHT/16;
    //Render texture to screen
    SDL_RenderCopy( gRenderer, a, NULL, &topLeftViewport );
}
void Bomb::bomb_display(int x,int y)        {load_bomb(texture_bomb,x,y);}
void Bomb::fire_middle_display(int x,int y) {load_bomb(fire_middle,x,y);}
void Bomb::fire_up_display(int x,int y)     {load_bomb(fire_up,x,y);}
void Bomb::fire_down_display(int x,int y)   {load_bomb(fire_down,x,y);}
void Bomb::fire_left_display(int x,int y)   {load_bomb(fire_left,x,y);}
void Bomb::fire_right_display(int x,int y)  {load_bomb(fire_right,x,y);}
void Bomb::fire_vtcl_display(int x, int y)  {load_bomb(fire_hztl, x, y);}
void Bomb::fire_hztl_display(int x, int y)  {load_bomb(fire_vtcl, x, y);}

bool Bomb::show_bomb(){

    //show bomb
    bomb_index[bomb_y_index][bomb_x_index]  = BOMB_DISPLAY_INDEX;
    
    SDL_Delay(1500);
    
    //Play bomb sound effect
    //Mix_PlayChannel( -1, gBomb, 0 );

    show_bomb_begin=true;
    //show fire_middle
    bomb_index[bomb_y_index][bomb_x_index]  = FIRE_MIDDLE_DISPLAY_INDEX;

    SDL_Delay(300);

    
    if((charachter1.get_character_status()!=1&&bomb_character==1)||(charachter2.get_character_status()!=1&&bomb_character==2)){
        if(bomb_x_index >0)  {bomb_index[bomb_y_index][bomb_x_index-1] = FIRE_VTCL_DISPLAY_INDEX;}
        if(bomb_x_index <14) {bomb_index[bomb_y_index][bomb_x_index+1] = FIRE_VTCL_DISPLAY_INDEX;}
        if(bomb_y_index >0)  {bomb_index[bomb_y_index-1][bomb_x_index] = FIRE_HZTL_DISPLAY_INDEX;}
        if(bomb_y_index <14) {bomb_index[bomb_y_index+1][bomb_x_index] = FIRE_HZTL_DISPLAY_INDEX;}
        if(bomb_x_index >1)  {bomb_index[bomb_y_index][bomb_x_index-2] = FIRE_LEFT_DISPLAY_INDEX;}
        if(bomb_x_index <13) {bomb_index[bomb_y_index][bomb_x_index+2] = FIRE_RIGHT_DISPLAY_INDEX;}
        if(bomb_y_index >1)  {bomb_index[bomb_y_index-2][bomb_x_index] = FIRE_UP_DISPLAY_INDEX;}
        if(bomb_y_index <13) {bomb_index[bomb_y_index+2][bomb_x_index] = FIRE_DOWN_DISPLAY_INDEX;}

        
        if((bomb_y_index==1)||(bomb_y_index==3)||(bomb_y_index==5)||(bomb_y_index==9)||(bomb_y_index==11)||(bomb_y_index==13)){
            if((bomb_x_index >0 )&&(bomb_x_index!=8)) {bomb_index[bomb_y_index][bomb_x_index-1] = FIRE_LEFT_DISPLAY_INDEX;}
            if((bomb_x_index <14)&&(bomb_x_index!=6)) {bomb_index[bomb_y_index][bomb_x_index+1] = FIRE_RIGHT_DISPLAY_INDEX;}
            if((bomb_x_index >1 )&&(bomb_x_index!=8)) {bomb_index[bomb_y_index][bomb_x_index-2] = DEFAULT_BACKGROUND;}
            if((bomb_x_index <13)&&(bomb_x_index!=6)) {bomb_index[bomb_y_index][bomb_x_index+2] = DEFAULT_BACKGROUND;}
        }
        if((bomb_x_index==1)||(bomb_x_index==3)||(bomb_x_index==5)||(bomb_x_index==9)||(bomb_x_index==11)||(bomb_x_index==13)){
            if((bomb_y_index >0 )&&(bomb_y_index!=8)) {bomb_index[bomb_y_index-1][bomb_x_index] = FIRE_UP_DISPLAY_INDEX;}
            if((bomb_y_index <14)&&(bomb_y_index!=6)) {bomb_index[bomb_y_index+1][bomb_x_index] = FIRE_DOWN_DISPLAY_INDEX;}
            if((bomb_y_index >1 )&&(bomb_y_index!=8)) {bomb_index[bomb_y_index-2][bomb_x_index] = DEFAULT_BACKGROUND;}
            if((bomb_y_index <13)&&(bomb_y_index!=6)) {bomb_index[bomb_y_index+2][bomb_x_index] = DEFAULT_BACKGROUND;}
        }


        SDL_Delay(500);
        bomb_index[bomb_y_index][bomb_x_index]  = DEFAULT_BACKGROUND;
        if(bomb_x_index!=0)  {bomb_index[bomb_y_index][bomb_x_index-1] = DEFAULT_BACKGROUND;}
        if(bomb_x_index!=14) {bomb_index[bomb_y_index][bomb_x_index+1] = DEFAULT_BACKGROUND;}
        if(bomb_y_index!=0)  {bomb_index[bomb_y_index-1][bomb_x_index] = DEFAULT_BACKGROUND;}
        if(bomb_y_index!=14) {bomb_index[bomb_y_index+1][bomb_x_index] = DEFAULT_BACKGROUND;}
        if(bomb_x_index >1)  {bomb_index[bomb_y_index][bomb_x_index-2] = DEFAULT_BACKGROUND;}
        if(bomb_x_index <13) {bomb_index[bomb_y_index][bomb_x_index+2] = DEFAULT_BACKGROUND;}
        if(bomb_y_index >1)  {bomb_index[bomb_y_index-2][bomb_x_index] = DEFAULT_BACKGROUND;}
        if(bomb_y_index <13) {bomb_index[bomb_y_index+2][bomb_x_index] = DEFAULT_BACKGROUND;}
        SDL_Delay(10);
    }
    else if((charachter1.get_character_status()==1&&bomb_character==1)||(charachter2.get_character_status()==1&&bomb_character==2)){

        for(int i=0;i<15;i++){
            bomb_index[bomb_y_index][i] = FIRE_VTCL_DISPLAY_INDEX;
            bomb_index[i][bomb_x_index] = FIRE_HZTL_DISPLAY_INDEX;
        }
        bomb_index[0][bomb_x_index] = FIRE_UP_DISPLAY_INDEX;
        bomb_index[14][bomb_x_index] = FIRE_DOWN_DISPLAY_INDEX;
        bomb_index[bomb_y_index][0] = FIRE_LEFT_DISPLAY_INDEX;
        bomb_index[bomb_y_index][14] = FIRE_RIGHT_DISPLAY_INDEX;
        
        
        if((bomb_y_index==1)||(bomb_y_index==3)||(bomb_y_index==5)||(bomb_y_index==9)||(bomb_y_index==11)||(bomb_y_index==13)){
            for(int i=0;i<15;i++){
                bomb_index[bomb_y_index][i] = DEFAULT_BACKGROUND;
            }
            if(bomb_x_index==6) {
                bomb_index[bomb_y_index][7] = FIRE_VTCL_DISPLAY_INDEX;
                bomb_index[bomb_y_index][8] = FIRE_RIGHT_DISPLAY_INDEX;
            }
            if(bomb_x_index==7) {
                bomb_index[bomb_y_index][6] = FIRE_LEFT_DISPLAY_INDEX;
                bomb_index[bomb_y_index][8] = FIRE_RIGHT_DISPLAY_INDEX;
            }
            if(bomb_x_index==8) {
                bomb_index[bomb_y_index][6] = FIRE_LEFT_DISPLAY_INDEX;
                bomb_index[bomb_y_index][7] = FIRE_VTCL_DISPLAY_INDEX;
            }
        }
        if((bomb_x_index==1)||(bomb_x_index==3)||(bomb_x_index==5)||(bomb_x_index==9)||(bomb_x_index==11)||(bomb_x_index==13)){
            for(int i=0;i<15;i++){
                bomb_index[i][bomb_x_index] = DEFAULT_BACKGROUND;
            }
            if(bomb_y_index==6) {
                bomb_index[7][bomb_x_index] = FIRE_HZTL_DISPLAY_INDEX;
                bomb_index[8][bomb_x_index] = FIRE_DOWN_DISPLAY_INDEX;
            }
            if(bomb_y_index==7) {
                bomb_index[6][bomb_x_index] = FIRE_UP_DISPLAY_INDEX;
                bomb_index[8][bomb_x_index] = FIRE_DOWN_DISPLAY_INDEX;
            }
            if(bomb_y_index==8) {
                bomb_index[6][bomb_x_index] = FIRE_UP_DISPLAY_INDEX;
                bomb_index[7][bomb_x_index] = FIRE_HZTL_DISPLAY_INDEX;
            }
        }
        bomb_index[bomb_y_index][bomb_x_index] = FIRE_MIDDLE_DISPLAY_INDEX;

        SDL_Delay(500);
        for(int i=0;i<15;i++){
            bomb_index[bomb_y_index][i] = DEFAULT_BACKGROUND;
            bomb_index[i][bomb_x_index] = DEFAULT_BACKGROUND;
        }
        SDL_Delay(10);
    }

    show_bomb_completely = true;

    return show_bomb_completely;
}

bool Bomb::detect(double x,double y){
    bool loss=false;
    int x_index = floor(((x*32/SCREEN_WIDTH)-1)/2);
    int y_index = floor(((y*32/SCREEN_HEIGHT)-1)/2);
    
    if(show_bomb_begin&&!show_bomb_completely){
        if(bomb_index[y_index][x_index]>1) loss=true;
    }
    return loss;
}


bool Bomb::loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Load texture
    texture_bomb          = loadTexture( "elements/bomb1.png" );
    fire_middle           = loadTexture( "elements/fire_mdl.png" );
    fire_up               = loadTexture( "elements/fire_up.png" );
    fire_down             = loadTexture( "elements/fire_down.png" );
    fire_left             = loadTexture( "elements/fire_left.png" );
    fire_right            = loadTexture( "elements/fire_right.png" );
    fire_vtcl             = loadTexture( "elements/fire_vtcl.png" );
    fire_hztl             = loadTexture( "elements/fire_hztl.png" );

    
    if( texture_bomb == NULL )
    {
        printf( "Failed to load texture_bomb image!\n" );
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
    if( fire_vtcl == NULL )
    {
        printf( "Failed to load fire_vtcl image!\n" );
        success = false;
    }
    if( fire_hztl == NULL )
    {
        printf( "Failed to load fire_hztl image!\n" );
        success = false;
    }
    //gBomb = Mix_LoadWAV( "bomb_sound_effect1.wav" );
    /*if( gBomb == NULL )
     {
     printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
     success = false;
     }*/
    return success;
}


SDL_Texture* Bomb::loadTexture( std::string path )
{
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

void Bomb::free(){
    bomb_x = bomb_y = 0;
    bomb_x_index = bomb_y_index =0;
    if(texture_bomb!=NULL)             {SDL_DestroyTexture(texture_bomb);}
    if(fire_middle!=NULL)              {SDL_DestroyTexture(fire_middle);}
    if(fire_up!=NULL)                  {SDL_DestroyTexture(fire_up);}
    if(fire_down!=NULL)                {SDL_DestroyTexture(fire_down);}
    if(fire_left!=NULL)                {SDL_DestroyTexture(fire_left);}
    if(fire_right!=NULL)               {SDL_DestroyTexture(fire_right);}
    if(fire_vtcl!=NULL)                {SDL_DestroyTexture(fire_vtcl);}
    if(fire_hztl!=NULL)                {SDL_DestroyTexture(fire_hztl);}

}


