#include"dead.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern SDL_Renderer* gRenderer;

Dead::Dead(){
    dead_x_index=0;
    dead_y_index=0;
    dead_x=0;
    dead_y=0;
    //Modulation component
    a = 0;
};
bool Dead::loadMedia(){
    bool success=true;
    dead_texture= loadTexture ( "elements/figure_dead.png" );
    player1_win= loadTexture ( "elements/player1_win.png" );
    player2_win= loadTexture ( "elements/player2_win.png" );
    
    //Set standard alpha blending
    setBlendMode( SDL_BLENDMODE_BLEND,player1_win );
    setBlendMode( SDL_BLENDMODE_BLEND,player2_win );
    
    if( dead_texture == NULL )
    {
        printf( "Failed to load dead_texture image!\n" );
        success = false;
    }
    else if( player1_win == NULL )
    {
        printf( "Failed to load player1_win image!\n" );
        success = false;
    }
    else if( player2_win == NULL )
    {
        printf( "Failed to load player2_win image!\n" );
        success = false;
    }
    return success;
} 

bool Dead::set_dead_position(Charachter& x){
    bool success=true;
    dead_x=x.getposx()-Charachter::CHAR_WIDTH/2;
    dead_y=x.getposy()-Charachter::CHAR_HEIGHT/2;
    if(dead_x==0||dead_y==0) success=false;
    return success;
}

bool Dead::show_figure(Charachter &x){
    bool complete=false;
    if(set_dead_position(x)){
        SDL_Rect topLeftViewport;
        topLeftViewport.x = dead_x;
        topLeftViewport.y = dead_y;
        topLeftViewport.w = SCREEN_WIDTH/16;
        topLeftViewport.h = SCREEN_HEIGHT/16;
        //Render texture to screen
        SDL_RenderCopy( gRenderer, dead_texture, NULL, &topLeftViewport );
        SDL_RenderPresent( gRenderer );
        complete=true;
    }
    else{
        printf("Failed to show dead_texture image!\n");
    }
    return complete;
}

void Dead::show_title1(){
    for(int i=0;i<=10;i++){
        a+=32;
        setAlpha(a,player1_win);
        SDL_Rect topLeftViewport;
        topLeftViewport.x = 2*SCREEN_WIDTH/11;
        topLeftViewport.y =SCREEN_HEIGHT/4;
        topLeftViewport.w = 2*SCREEN_WIDTH/3;
        topLeftViewport.h = SCREEN_HEIGHT/2;
        //Render texture to screen
        SDL_RenderCopy( gRenderer, player1_win, NULL, &topLeftViewport );
        //Update screen
        SDL_RenderPresent( gRenderer );
        SDL_Delay(200);
    }
    SDL_Delay(2000);
}
void Dead::show_title2(){
    for(int i=0;i<=10;i++){
        a+=32;
        setAlpha(a,player2_win);
        SDL_Rect topLeftViewport;
        topLeftViewport.x = 2*SCREEN_WIDTH/11;
        topLeftViewport.y =SCREEN_HEIGHT/4;
        topLeftViewport.w = 2*SCREEN_WIDTH/3;
        topLeftViewport.h = SCREEN_HEIGHT/2;
        //Render texture to screen
        SDL_RenderCopy( gRenderer, player2_win, NULL, &topLeftViewport );
        //Update screen
        SDL_RenderPresent( gRenderer );
        SDL_Delay(200);
    }
    SDL_Delay(2000);
}
void Dead::setBlendMode( SDL_BlendMode blending,SDL_Texture* x )
{	
    //Set blending function
    SDL_SetTextureBlendMode( x, blending );
}

void Dead::setAlpha( Uint8 alpha,SDL_Texture* x )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod(x, alpha );
}	 

SDL_Texture* Dead::loadTexture( std::string path )
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

void Dead::free(){
    if(dead_texture!=NULL)   {SDL_DestroyTexture(dead_texture);}
}

