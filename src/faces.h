#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <SDL2/SDL.h>

#define SPR_H 14
#define SPR_W 14

typedef struct graphics{
  char* name;
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* texture;
  uint32_t *pixel_buffer;
}graphics;

#ifdef MAIN

extern const char Face_Idle_1[SPR_H * SPR_W -1];
extern const char Face_Idle_2[SPR_H * SPR_W -1];
extern const char Face_Talking_1[SPR_H * SPR_W -1];
extern const char Face_Talking_2[SPR_H * SPR_W -1];
extern const char Face_Talking_3[SPR_H * SPR_W -1];

#endif

#endif
