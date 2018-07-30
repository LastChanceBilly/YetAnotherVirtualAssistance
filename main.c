#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#define MAIN
#include "faces.h"

#define WIN_X SDL_WINDOWPOS_CENTERED
#define WIN_Y SDL_WINDOWPOS_CENTERED
#define WIN_NAME "YAVA"
#define rend_flags SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
#define WIN_H 280
#define WIN_W 280

int PrintError(char* msg);
void UpdateFace(int mode, graphics* main_face);
void UpdateTexture(graphics* main_face, const char *buffer);

int main(int argc, char **argv){
	//SDL Initialization
	if(SDL_Init(SDL_INIT_EVERYTHING)){
		printf("SDL_Init error:\n%s\n", SDL_GetError());
	}
	//SDL Window Creation
	graphics *main_face = malloc(sizeof(*main_face));
	main_face->window = SDL_CreateWindow(WIN_NAME, WIN_X, WIN_Y, WIN_W, WIN_H, 0);
	if(main_face->window == NULL){
		SDL_DestroyWindow(main_face->window);
		return PrintError(SDL_GetError());
	}
	main_face->renderer = SDL_CreateRenderer(main_face->window, -1, rend_flags);
	if(main_face->renderer == NULL){
		SDL_DestroyRenderer(main_face->renderer);
		return PrintError(SDL_GetError());
	}
	//SDL Texture Creation & Configuration
	main_face->texture = SDL_CreateTexture(main_face->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIN_W, WIN_H);
	main_face->pixel_buffer = (uint32_t *)calloc(WIN_H * WIN_W, sizeof(uint32_t));
	SDL_RenderClear(main_face->renderer);
	//Main loop
	UpdateFace(1, main_face);
	char *command = malloc(1000);
	int loop = 1;
	while(loop){
		SDL_Event main_event;
		if(SDL_PollEvent(&main_event)){
			if(main_event.type == SDL_QUIT){
				printf("quit");
				loop = 0;
			}
		}
		scanf("%1000s", command);
		if(!strcmp("quit", command))
			loop = 0;
	}
	free(command);
	free(main_face);
	return 0;
}
int PrintError(char* msg){
	printf("SDL Error: %s\nExiting... \n", msg);
	SDL_Quit();
	return 1;
}
//It updates the current face been display
void UpdateFace(int mode, graphics* main_face){
	const char *target = NULL;
	switch(mode){
		case 0:
			target = &Face_Idle_1[0];
			break;
		case 1:
			target = &Face_Idle_2[0];
			break;
		case 2:
			target = &Face_Talking_1[0];
			break;
		case 3:
			target = &Face_Talking_2[0];
			break;
		case 4:
			target = &Face_Talking_3[0];
			break;
		default:
			printf("Selection error!");
			break;
	}
	UpdateTexture(main_face, target);
}
//It loads the array selected into the current texture
void UpdateTexture(graphics *main_face, const char *buffer){
	for(int y = 0; y<WIN_H; y++){
		for(int x = 0; x<WIN_W; x++){
			main_face->pixel_buffer[WIN_W * y + x] = buffer[x/(WIN_W/SPR_W) + SPR_W * (y/(WIN_H/SPR_H))] > 0 ? 0xFFFFFFFF: 0x00000000;
		}
	}
	SDL_UpdateTexture(main_face->texture, NULL, main_face->pixel_buffer, WIN_W * sizeof(uint32_t));
	SDL_RenderCopy(main_face->renderer, main_face->texture, NULL, NULL);
	SDL_RenderPresent(main_face->renderer);
}
