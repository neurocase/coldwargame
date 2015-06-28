#include "SDL2/SDL.h"
#include <stdio.h>
#include <string>


enum KeyPressSurfaces
{
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];
SDL_Surface* gCurrentSurface = NULL;

SDL_Event e;

SDL_Surface* loadSurface(std::string path)
{
  SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
  if(loadedSurface == NULL)
  {
    printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
  }
  return loadedSurface;
}

void QuitGame(SDL_Window *gWindow){

  SDL_FreeSurface(gHelloWorld);
  gHelloWorld=NULL;  
  SDL_DestroyWindow( gWindow );
  gWindow=NULL;
  SDL_Quit();
}

bool init()
{
  bool success = true;
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
		printf("failed to itialize: %s\n", SDL_GetError());
    success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Daz Civ", SDL_WINDOWPOS_UNDEFINED, 
		  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if (gWindow == NULL)
		{
		  printf("Window could not be created: SDL ERROR: %s\n", SDL_GetError());     
      success = false;
		}
    else
    {
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
   }
  return success;
}
bool loadMedia(){

  bool success = true;
  gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface("./gfx/press.bmp");
  gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ]      = loadSurface("./gfx/up.bmp");
  gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ]      = loadSurface("./gfx/down.bmp"); 
  gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ]    = loadSurface("./gfx/left.bmp");
  gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ]   = loadSurface("./gfx/right.bmp");
  for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++){
    if (gKeyPressSurfaces[i] == NULL)
    {
      printf("loadKeypressImages failed");
      success = false;
    }else{
      printf("loaded:");
      printf("%d,", i);
      printf("\n");
    }
  }
  SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB( gScreenSurface->format, 0x00, 0x00, 0x00));
  gHelloWorld = SDL_LoadBMP( "./gfx/testimage.bmp");
  if (gHelloWorld == NULL)
  {
    printf( "Unable to load image %s SDL ERR: %s\n", "TESTIMAGE", SDL_GetError());
    success = false;
  }
  return success;
}

int main(int argc, char* argv[])
{
  printf("starting game \n");
  bool startupSuccess = true;
  bool quit = false;
  if (!init())
  {
    startupSuccess = false;
    printf("failed on init ");
  } 
  else
  { 
    if (!loadMedia()){
      startupSuccess = false;
      printf("failed to load loadMedia");
    }
  }
  if (startupSuccess)
  {
    printf("startup successfull \n");

  gHelloWorld = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

    while(!quit)
    {
      while(SDL_PollEvent(&e))
      {
        if(e.type == SDL_QUIT)
        {
          quit = true;
        } 
        else if(e.type == SDL_KEYDOWN )
        {
          switch( e.key.keysym.sym)
          {
           case SDLK_UP:
             gHelloWorld = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP];
             break;
           case SDLK_DOWN:
             gHelloWorld = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
             break;
           case SDLK_LEFT:
             gHelloWorld = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
             break;
           case SDLK_RIGHT:
             gHelloWorld = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
             break;
          }
        }
      }
    SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL);
    SDL_UpdateWindowSurface(gWindow);
    }
  }
  QuitGame(&*gWindow);
}
