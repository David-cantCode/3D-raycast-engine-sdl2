//compile gcc main.c -o window -lSDL3 -lm 
// ./window


#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <stdio.h>
#include <sys/types.h>
#define SDL_MAIN_USE_CALLBACKS 1  //use call back instead of main()
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <math.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

const int screen_w = 900;
const int screen_h = 800;
int map[9][8] =  {
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1}
};


const int rows = 9;
const int cols = 8;

const int TILE_SIZE = 100;


struct Player{
    int player_x;
    int player_y;
    int new_x;
    int new_y;

    double angle;
    int speed;
    double rot_speed;

    int ray_length;
    int max_depth;
    int num_rays;

    float fov;



};


struct Player player;

void draw_map(){
    
    

    for (int row = 0; row < rows; row ++){
    for (int col = 0; col < cols; col++){
      

        if (map[row][col] == 1){
            SDL_FRect square = {col*TILE_SIZE, row*TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  
            SDL_RenderFillRect(renderer, &square);

            }

        }
    }


   
}



void draw_player(){
    SDL_FRect square = {player.player_x, player.player_y, 100, 100};
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  
        SDL_RenderFillRect(renderer, &square);
        printf("\n %d" ,player.player_x);


}






//on startup
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
 
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("window", screen_h, screen_w, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }



    player.angle=0;player.player_x=350;player.player_y=250;
    player.speed=10;player.rot_speed=0.10;player.ray_length=100;
    player.fov = 3.13 /3;player.num_rays=800;player.max_depth=10000;

    return SDL_APP_CONTINUE; 
}



//called on event (mouse input, keypresses, etc) 
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS; 
    }

        //********************************
        //******PLAYER CONTROLLER**********
        // *********************************


    if (event->type == SDL_EVENT_KEY_DOWN) {

        player.new_x = player.player_x;
        player.new_y = player.player_y;


        switch (event->key.key){

            case SDLK_A:
                player.angle -= player.rot_speed;
                break;

            case SDLK_D:
                player.angle -= player.rot_speed;
                break;

            case SDLK_W:
                player.new_x += cos(player.angle) * player.speed;
                player.new_y += sin(player.angle) * player.speed;
                break;

            case SDLK_S:
                player.new_x -= cos(player.angle) * player.speed;
                player.new_y -= sin(player.angle) * player.speed;
                break;
        
            }
        
            //add constraints
            player.player_x = player.new_x;
            player.player_y = player.new_y;


}


    return SDL_APP_CONTINUE;
}




//once everyframe
SDL_AppResult SDL_AppIterate(void *appstate)
{
    //clear window
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black background
    SDL_RenderClear(renderer);
    draw_map();
    draw_player();





    SDL_RenderPresent(renderer);


    return SDL_APP_CONTINUE; 
}



//run on shutdown
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    //nothing needs to be here i guess.
}





