//
//  main.cpp
//  background
//
//  Created by dingyiyi on 2017/12/9.
//  Copyright © 2017年 dingyiyi. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_thread.h>
#include "LTexture.hpp"
#include "background.hpp"
#include "Charachter.hpp"
#include "show_bomb1.h"
#include "tools.hpp"
#include "LMenu.hpp"
#include "dead.h"
#include "landmine.hpp"


//Screen dimension constants
int SCREEN_WIDTH = 560;
int SCREEN_HEIGHT = 560;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();


//Scene textures
LTexture gCharachterTexture;
LTexture box;
LTexture background;
LTexture big_cross;
LTexture immortal_spell;
LTexture gButtonQuit;
LTexture gButtonGame;
LTexture gMenuBackground;
//LTexture landmine_texture;

//Background class
Background bg;
//character class
Charachter charachter1(playerone);
Charachter charachter2(playertwo);

#define MAX_TOOL 25
tools tool[MAX_TOOL]={};

LMenu ButtonQuit;
LMenu ButtonGame;
LMenu menu;

Dead dead;

#define MAX_LANDMINE 2
Landmine landmine[2][MAX_LANDMINE]={};


#define MAX_BOMB 50
//bombs array (allowing to show MAX_BOMB bombs at the same time)
Bomb bomb_array[MAX_BOMB]={};
//threads array
SDL_Thread* bomb_showing_threads[MAX_BOMB];
SDL_Thread* dead_showing_thread;

//bomb thread function, which enables bombs to display simultaneously
int show_bomb_thread(void*);

int dead_thread(void*);
int dead_thread2(void*);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;


int main(int argc, const char * argv[]) {

    //Start up SDL and create window
    if( !init() ){
        printf( "Failed to initialize!\n" );
    }
    else {
        //Load media
        if( !bg.loadMedia() ){
            printf( "Failed to load background media!\n" );
        }
        else if( !charachter1.loadMedia() ){
            printf( "Failed to load character1 media!\n" );
        }
        else if( !charachter2.loadMedia() ){
            printf( "Failed to load character2 media!\n" );
        }
        else if( !menu.loadMedia() ){
            printf( "Failed to load menu media!\n" );
        }
        else if( !dead.loadMedia() ){
            printf( "Failed to load dead media!\n" );
        }
        else{
            //Main loop flag
            bool quit = false;

            /////MENUPLACE/////
            
        menulabel:
            
            //Event handler
            SDL_Event f;
      
            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &f ) != 0 )
                {
                    //User requests quit
                    if( f.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    if(menu.handleEvent(&f)==1){
                        quit = true;
                        goto gamelabel;
                    }
                    if(menu.GameBool() == true){
                        menu.set_gamebool(false);
                        goto gamelabel;
                    }
                }
                
                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                
                menu.render();
          
                //Update screen
                SDL_RenderPresent( gRenderer );
                
                menu.handleEvent(&f);
                if(menu.GameBool() == false){goto menulabel;}
            }
            /////END OF MENUPLACE/////
            
    
            /////GAMEPLACE/////
        gamelabel:

            //Event handler
            SDL_Event e;
            
            //count the numbers of bombs and tools
            int count = 0;
            int tool_count = 0;
            int landmine_count1=0,landmine_count2=0;
            
            //display tools
            bool show_big_cross[MAX_TOOL], show_immortal_spell[MAX_TOOL];
            for (int i=0; i<MAX_TOOL; i++) {
                show_big_cross[i] = show_immortal_spell[i] = false;
            }

            
            clock_t start_big_cross[2]={0,0}, start_immortal[2]={0,0};
            clock_t set_tools_time={0};
            clock_t start_landmine[2][MAX_LANDMINE];
            for(int i=0;i<2;i++){
                for(int j=0;j<MAX_LANDMINE;j++){
                    start_landmine[i][j]=0;
                }
            }
            
            //set tool
            set_tools_time = clock();
            
            bool first_set_tool = true ;
            
            double big_cross_lasting_time = 2.5;
            double immortal_lasting_time = 2.5;
            double reset_tools_time = 4;
            double landmine_lasting_time = 0.00001;
            double landmine_setup_time = 0.1;
     
            bool landmine_ready_setup[2][MAX_LANDMINE]={};
            
            bool landmine_explode1=false, landmine_explode2=false;
            
            //initialize charachter and landmine
            charachter1.initialize(playerone);
            charachter2.initialize(playertwo);
            for(int i=0;i<2;i++){
                for(int j=0;j<MAX_LANDMINE;j++){
                    landmine[i][j] = Landmine();
                }
            }
            
            //While application is running
            while( !quit )
            {
                
                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    charachter1.handleEventFrame(e);
                    charachter2.handleEventFrame(e);

                    if( e.type == SDL_KEYDOWN ){
                        
                        if(e.key.keysym.sym==SDLK_l){
                            double x = charachter1.getposx(), y=charachter1.getposy();
                            Bomb a;
                            a.bomb_character=1;
                            if( !a.loadMedia() ) { printf( "Failed to load bombs media!\n" );}
                            else{
                                bomb_array[count % MAX_BOMB] = a;
                                bomb_array[count % MAX_BOMB].set_bomb_position(x,y);
                                bomb_showing_threads[count % MAX_BOMB] = SDL_CreateThread( show_bomb_thread, "show_bomb",(void*)(bomb_array+ (count % MAX_BOMB)));
                                count++;
                            }
                        }
                        if(e.key.keysym.sym==SDLK_z){
                            double x2 = charachter2.getposx(), y2=charachter2.getposy();
                            Bomb a;
                            a.bomb_character=2;
                            if( !a.loadMedia() ) { printf( "Failed to load bombs media!\n" );}
                            else{

                                bomb_array[count % MAX_BOMB] = a;
                                bomb_array[count % MAX_BOMB].set_bomb_position(x2,y2);
                                bomb_showing_threads[count % MAX_BOMB] = SDL_CreateThread( show_bomb_thread, "show_bomb",(void*)(bomb_array+ (count % MAX_BOMB)));
                                count++;
                            }
                        }
                        if(e.key.keysym.sym==SDLK_o){
                            int x3 = charachter1.get_index_x(), y3 = charachter1.get_index_y();
                            if(landmine_count1<MAX_LANDMINE){
                                Landmine a;
                                if( !a.loadMedia() ) { printf( "Failed to load landmine media!\n" );}
                                landmine[0][landmine_count1] = a;
                                landmine[0][landmine_count1].set_landmine(x3, y3);
                                start_landmine[0][landmine_count1] = clock();
                                landmine_count1++;
                            }
                        }
                        if(e.key.keysym.sym==SDLK_a){
                            int x4 = charachter2.get_index_x(), y4 = charachter2.get_index_y();
                            if(landmine_count2<MAX_LANDMINE){
                                Landmine a;
                                if( !a.loadMedia() ) { printf( "Failed to load landmine media!\n" );}
                                landmine[1][landmine_count2] = a;
                                landmine[1][landmine_count2].set_landmine(x4, y4);
                                start_landmine[1][landmine_count2] = clock();
                                landmine_count2++;
                            }
                        }
                    }
                }
                bg.background_rendering();

                for(int k=((count+1)%MAX_BOMB);k!=(count%MAX_BOMB);k=((k+1)%MAX_BOMB)){
                    if(bomb_array[k].show_bomb_completely) {continue;}
                    for(int i=0;i<15;i++){
                        for(int j=0;j<15;j++){
                            switch (bomb_array[k].bomb_index[i][j]) {
                                case Bomb::BOMB_DISPLAY_INDEX:
                                    bomb_array[k].bomb_display(j,i);
                                    break;
                                case Bomb::FIRE_MIDDLE_DISPLAY_INDEX:
                                    bomb_array[k].fire_middle_display(j,i);
                                    break;
                                case Bomb::FIRE_UP_DISPLAY_INDEX:
                                    bomb_array[k].fire_up_display(j,i);
                                    break;
                                case Bomb::FIRE_DOWN_DISPLAY_INDEX:
                                    bomb_array[k].fire_down_display(j,i);
                                    break;
                                case Bomb::FIRE_LEFT_DISPLAY_INDEX:
                                    bomb_array[k].fire_left_display(j,i);
                                    break;
                                case Bomb::FIRE_RIGHT_DISPLAY_INDEX:
                                    bomb_array[k].fire_right_display(j,i);
                                    break;
                                case Bomb::FIRE_VTCL_DISPLAY_INDEX:
                                    bomb_array[k].fire_vtcl_display(j, i);
                                    break;
                                case Bomb::FIRE_HZTL_DISPLAY_INDEX:
                                    bomb_array[k].fire_hztl_display(j, i);
                                    break;
                            }
                        }
                    }
                }
     
                if((clock()-set_tools_time)>reset_tools_time*CLOCKS_PER_SEC||first_set_tool){
                    tools t;
                    if( !t.loadMedia() ){
                        printf( "Failed to load tool media!\n" );
                    }
                    else {
                        tool[tool_count%MAX_TOOL] = t;
                        tool[tool_count%MAX_TOOL].set_tool();
                        show_big_cross[tool_count%MAX_TOOL] = true;
                        show_immortal_spell[tool_count%MAX_TOOL] = true;
                    }
                    set_tools_time = clock();
                    first_set_tool = false;
                    tool_count++;
                }
                
                int tmp1[MAX_TOOL]={},tmp2[MAX_TOOL]={};
                
                for(int i=((tool_count+1)%MAX_TOOL);i!=tool_count%MAX_TOOL;i=(i+1)%MAX_TOOL){
                    if(show_big_cross[i]) {
                        tool[i].big_cross_rendering();
                    }
                    if(show_immortal_spell[i]) {
                        tool[i].immortal_spell_rendering();
                    }
                    tmp1[i] =tool[i].pick_up_tools(charachter1.get_index_x(), charachter1.get_index_y());
                    tmp2[i] =tool[i].pick_up_tools(charachter2.get_index_x(), charachter2.get_index_y());
                    if(tmp1[i]!=0){
                        charachter1.set_character_status( tmp1[i] );
                        if(tmp1[i]==tools::BIG_CROSS) {
                            show_big_cross[i] = false;
                            start_big_cross[0] = clock();
                        }
                        if(tmp1[i]==tools::IMMORTAL) {
                            show_immortal_spell[i] = false;
                            start_immortal[0] = clock();
                        }
                    }
                    if(tmp2[i]!=0){
                        charachter2.set_character_status( tmp2[i] );
                        if(tmp2[i]==tools::BIG_CROSS) {
                            show_big_cross[i] = false;
                            start_big_cross[1] = clock();
                        }
                        if(tmp2[i]==tools::IMMORTAL) {
                            show_immortal_spell[i] = false;
                            start_immortal[1] = clock();
                        }
                    }
                }
                for(int i=0;i<2;i++){
                    for(int j=0;j<MAX_LANDMINE;j++){
                        if(start_landmine[i][j]!=0){
                            if(clock()-start_landmine[i][j]<landmine_lasting_time*CLOCKS_PER_SEC){
                                landmine[i][j].landmine_display(landmine[i][j].get_landmine_index_x(), landmine[i][j].get_landmine_index_y());
                            }
                        }
                    }
                }

                bg.box_rendering();
                //a pointer pointing to blockwalls
                SDL_Rect* totalblock = &bg.blockwall[0][0];
                charachter1.move(totalblock);
                charachter2.move(totalblock);
            
                
                if(charachter1.get_character_status()==1){
                    if((clock()-start_big_cross[0])>big_cross_lasting_time*CLOCKS_PER_SEC){
                        charachter1.reset_character_status();
                    }
                }
                if(charachter1.get_character_status()==2){
                    if((clock()-start_immortal[0])>immortal_lasting_time*CLOCKS_PER_SEC){
                        charachter1.reset_character_status();
                    }
                }
                if(charachter2.get_character_status()==1){
                    if((clock()-start_big_cross[1])>big_cross_lasting_time*CLOCKS_PER_SEC){
                        charachter2.reset_character_status();
                    }
                }
                if(charachter2.get_character_status()==2){
                    if((clock()-start_immortal[1])>immortal_lasting_time*CLOCKS_PER_SEC){
                        charachter2.reset_character_status();
                    }
                }
                for(int i=0;i<2;i++){
                    for (int j=0;j<MAX_LANDMINE;j++){
                        if(start_landmine[i][j]!=0){
                            if(clock()-start_landmine[i][j]>landmine_setup_time*CLOCKS_PER_SEC){
                                landmine_ready_setup[i][j] = true;
                            }
                            if(landmine[i][j].landmine_index[charachter1.get_index_y()][charachter1.get_index_x()]==1&&landmine_ready_setup[i][j]){
                                landmine[i][j].fire_display(charachter1.get_index_x(), charachter1.get_index_y());
                                for(int k=0;k<15;k++){
                                    if(k%2==1) continue;
                                    for(int l=0;l<15;l++){
                                        if(l!=0&&l!=2&&l!=4&&l!=8&&l!=10&&l!=12) continue;
                                        if(charachter1.get_index_x()==k&&charachter1.get_index_y()==l){
                                            if(k!=0&&k!=8)  bg.box_rerendering(k-1, l);
                                            if(k!=6&&k!=14) bg.box_rerendering(k+1, l);
                                        }
                                    }
                                }
                                landmine[i][j].reset_landmine(charachter1.get_index_y(), charachter1.get_index_x());
                                landmine_explode1 = true;
                            }
                            if(landmine[i][j].landmine_index[charachter2.get_index_y()][charachter2.get_index_x()]==1&&landmine_ready_setup[i][j]){
                                landmine[i][j].fire_display(charachter2.get_index_x(), charachter2.get_index_y());
                                for(int k=0;k<15;k++){
                                    if(k%2==1) continue;
                                    for(int l=0;l<15;l++){
                                        if(l!=0&&l!=2&&l!=4&&l!=8&&l!=10&&l!=12) continue;
                                        if(charachter2.get_index_x()==k&&charachter2.get_index_y()==l){
                                            if(k!=0&&k!=8)  bg.box_rerendering(k-1, l);
                                            if(k!=6&&k!=14) bg.box_rerendering(k+1, l);
                                        }
                                    }
                                }
                                landmine[i][j].reset_landmine(charachter2.get_index_y(), charachter2.get_index_x());
                                landmine_explode2 = true;
                            }
                        }
                    }
                }

                charachter1.render();
                charachter2.render();
                
                if(bg.check_character_behind_box(charachter1.get_index_x(), charachter1.get_index_y())){
                    bg.box_rerendering(charachter1.get_index_x(), charachter1.get_index_y());
                }
                if(bg.check_character_behind_box(charachter2.get_index_x(), charachter2.get_index_y())){
                    bg.box_rerendering(charachter2.get_index_x(), charachter2.get_index_y());
                }
                // lose detection for bombs
                for(int k=((count+1)%MAX_BOMB);k!=(count%MAX_BOMB);k=((k+1)%MAX_BOMB)){
                    
                    if(bomb_array[k].detect(charachter1.getposx(), charachter1.getposy())&&charachter1.get_character_status()!=tools::IMMORTAL){
                        
                        dead_showing_thread = SDL_CreateThread( dead_thread, "dead",(void*)&dead);
                        SDL_Delay(500);
                        dead.show_figure(charachter1);
                        dead.show_title2();
//                        SDL_Delay(1000);
                        goto menulabel;
                    }
                    if(bomb_array[k].detect(charachter2.getposx(), charachter2.getposy())&&charachter2.get_character_status()!=tools::IMMORTAL){
                        dead_showing_thread = SDL_CreateThread( dead_thread2, "dead",(void*)&dead);
                        SDL_Delay(500);
                        dead.show_figure(charachter2);
                        dead.show_title1();
//                        SDL_Delay(1000);
                        goto menulabel;
                    }
                }
                // lose detection for landmines
                if(landmine_explode1){
                    dead_showing_thread = SDL_CreateThread( dead_thread, "dead",(void*)&dead);
                    SDL_Delay(500);
                    dead.show_figure(charachter1);
                    dead.show_title2();
//                    SDL_Delay(1000);
                    landmine_explode1=false;
                    goto menulabel;
                }
                if(landmine_explode2){
                    dead_showing_thread = SDL_CreateThread( dead_thread2, "dead",(void*)&dead);
                    SDL_Delay(500);
                    dead.show_figure(charachter2);
                    dead.show_title1();
//                    SDL_Delay(1000);
                    landmine_explode2=false;
                    goto menulabel;
                }
                
                
                //Update screen
                SDL_RenderPresent( gRenderer );
                
                /////END OF GAME/////
            }
        }
    }
    close();

    return 0;
}

int show_bomb_thread( void* a){
    
    if(!((Bomb*) a)->show_bomb()) {printf("fail to show_bomb");}
    return 0;
}
int dead_thread( void* a){
    
    if(!((Dead*) a)->show_figure(charachter1)) {printf("fail to show_bomb");}
    return 0;
}
int dead_thread2( void* a){
    
    if(!((Dead*) a)->show_figure(charachter2)) {printf("fail to show_bomb");}
    return 0;
}

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "boomboomking", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else{
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    return success;
}

void close()
{
    //Free loaded images
    background.free();
    box.free();
    gButtonQuit.free();
    gButtonGame.free();
    gMenuBackground.free();
    gCharachterTexture.free();
    dead.free();
    for(int i=0;i<MAX_BOMB;i++){
        bomb_array[i].free();
    }
    for(int i=0;i<2;i++){
        for(int j=0;j<MAX_LANDMINE;j++){
            landmine[i][j].free();
        }
    }
    //close thread
    for(int i=0;i<MAX_BOMB;i++){
        SDL_WaitThread(bomb_showing_threads[i], NULL);
    }
    SDL_WaitThread(dead_showing_thread, NULL);
    
    //Deallocate surface
    SDL_DestroyRenderer( gRenderer );
    gRenderer = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

