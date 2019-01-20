#ifndef show_bomb1_h
#define show_bomb1_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <cstdlib>
#include <iostream>
extern int SCREEN_WIDTH ;
extern int SCREEN_HEIGHT;
extern SDL_Renderer* gRenderer;
extern SDL_Window* gWindow ;

class Bomb{
private:
    double bomb_x,bomb_y;
    int bomb_x_index, bomb_y_index;
    double *tool2_x,*tool2_y;
    int bomb_length;



public:
    Bomb();
    int bomb_character;

    void free();
    int bomb_index[15][15];//--------bomb_index[y-axis][x-axis]
    bool show_bomb_completely;
    bool show_bomb_begin;
    enum bomb_index_number{
        DEFAULT_BACKGROUND                = 0,
        BOMB_DISPLAY_INDEX                = 1,
        FIRE_MIDDLE_DISPLAY_INDEX         = 2,
        FIRE_UP_DISPLAY_INDEX             = 3,
        FIRE_DOWN_DISPLAY_INDEX           = 4,
        FIRE_LEFT_DISPLAY_INDEX           = 5,
        FIRE_RIGHT_DISPLAY_INDEX          = 6,
        FIRE_VTCL_DISPLAY_INDEX           = 7,
        FIRE_HZTL_DISPLAY_INDEX           = 8
    };
    
    enum KeyPressSurfaces
    {
        KEY_PRESS_SURFACE_DEFAULT,
        KEY_PRESS_SURFACE_UP,
        KEY_PRESS_SURFACE_DOWN,
        KEY_PRESS_SURFACE_LEFT,
        KEY_PRESS_SURFACE_RIGHT,
        KEY_PRESS_SURFACE_TOTAL
    };
    //Loads media
    bool loadMedia();
    void load_bomb(SDL_Texture* a,int ,int );
    void load_tool2();
    void set_bomb_position(double &,double &);
    bool show_bomb();
    
    void bomb_display(int, int);
    void fire_middle_display(int, int);
    void fire_up_display(int, int);
    void fire_down_display(int, int);
    void fire_left_display(int, int);
    void fire_right_display(int, int);
    void fire_vtcl_display(int, int);
    void fire_hztl_display(int, int);
    
    bool detect(double x,double y);
    
    //Loads individual image as texture
    SDL_Texture* loadTexture( std::string path );

    
    //Current displayed texture
    SDL_Texture* texture_bomb ;
    SDL_Texture* fire_middle ;
    SDL_Texture* fire_up ;
    SDL_Texture* fire_down ;
    SDL_Texture* fire_left ;
    SDL_Texture* fire_right ;
    SDL_Texture* fire_vtcl;
    SDL_Texture* fire_hztl;
    SDL_Texture* texture_add_bomb ;
    SDL_Texture* texture_add_length ;
    //The sound effects that will be used
    //Mix_Chunk *gBomb ;
};
#endif
