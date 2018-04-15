//BEGIN HEAD
//BEGIN DESCRIPTION
/* Re-Render a part of the screen
 */
//END   DESCRIPTION


//BEGIN INCLUDES
//local headers
#include "helper.h"
//END   INCLUDES

//BEGIN CPP DEFINITIONS
//END   CPP DEFINITIONS

//BEGIN DATASTRUCTURES
//END	DATASTRUCTURES

//BEGIN GLOBALS
//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
SDL_Texture 	*LoadTexture(char *fileName);
//END	FUNCTION PROTOTYPES

/* DEFINED PROGRESS GOALS
 * 
 * I am not entirely sure of the viewport role and
 * if I could make use of it in this case.
 *
 */
//END 	HEAD

//BEGIN MAIN FUNCTION
int main(int argc, char *argv[])
{

(void)argc;
(void)argv;

//BEGIN INIT
init();

SDL_Texture *background_Texture=NULL;
background_Texture = LoadTexture("ISO_12233.png");
int tw, th;
SDL_QueryTexture(background_Texture, NULL, NULL, &tw, &th);
int nw, nh;
nw = tw/7;
nh = th/7;
SDL_Rect dst_rect = {(540/2)-(nw/2),(540/2)-(nh/2),nw,nh};

SDL_Rect src_part = {0,0,540/2,540/2};
SDL_Rect dst_part = {(540/2),(540/2),540/2,540/2};

SDL_SetWindowPosition(Window,0,0);
SDL_SetWindowSize(Window,540,540);
SDL_SetWindowTitle(Window, "SDL 2 - Renderer");
SDL_ShowWindow(Window);

Uint32 fmt;
fmt=SDL_GetWindowPixelFormat(Window);

//BEGIN COPY OF RENDER ON TEXTURE
//Flag in helper.c SDL_RENDERER_TARGETTEXTURE
SDL_Texture *win_part=NULL;
win_part=SDL_CreateTexture(Renderer, fmt, SDL_TEXTUREACCESS_TARGET, 540/2, 540/2);

SDL_SetRenderTarget(Renderer, win_part);

/* Top left corner viewport
SDL_Rect topLeftViewport;
topLeftViewport.x = 0;
topLeftViewport.y = 0;
topLeftViewport.w = 540 / 2;
topLeftViewport.h = 540 / 2;
SDL_RenderSetViewport( Renderer, &topLeftViewport );
*/

SDL_SetRenderDrawColor(Renderer, 111, 111, 111, 255);
SDL_RenderClear(Renderer);
SDL_RenderCopy(Renderer, background_Texture, NULL, &dst_rect);
SDL_RenderPresent(Renderer);
//END 	COPY OF RENDER ON TEXTURE

SDL_SetRenderTarget(Renderer, NULL);

SDL_Event event;
int running = 1;
//END   INIT

//BEGIN MAIN LOOP
while(running){
//BEGIN EVENT LOOP
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			running = 0;
		}
		if(event.type == SDL_MOUSEBUTTONDOWN){
			if(event.button.button == SDL_BUTTON_LEFT){
				;
			}
		}
	}
//END   EVENT LOOP

//BEGIN RENDERING
SDL_Delay(66);//~15fps
SDL_SetRenderDrawColor(Renderer, 111, 111, 111, 255);
SDL_RenderClear(Renderer);

SDL_RenderCopy(Renderer, background_Texture, NULL, &dst_rect);
SDL_RenderCopy(Renderer, win_part, &src_part, &dst_part);

SDL_RenderPresent(Renderer);
//END   RENDERING

}
//END    MAIN LOOP

SDL_DestroyTexture(background_Texture);
SDL_DestroyTexture(win_part);
exit_();
return EXIT_SUCCESS;

}
//END   MAIN FUNCTION

//BEGIN FUNCTIONS
SDL_Texture *LoadTexture(char *fileName)
{
	
	SDL_Surface *Surface    = NULL;
	SDL_Texture *Texture    = NULL;
	
	Surface = IMG_Load(fileName);
	if(Surface != NULL){
		Texture = SDL_CreateTextureFromSurface(Renderer, Surface);
		if(Texture == NULL){
			SDL_Log("texture creation failed!\n");
		}
		SDL_FreeSurface(Surface);
	}
	
	return Texture;
	
}
//END   FUNCTIONS
