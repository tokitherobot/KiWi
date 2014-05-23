#include "SDL.h"
#include "KW_gui.h"
#include "KW_button.h"
#include "SDL_image.h"


void DragStart(KW_Widget * widget, int mousex, int mousey) {
  printf("Drag has started at %dx%d\n", mousex, mousey);
}

void DragStop(KW_Widget * widget, int x, int y) {
  printf("Drag has stopped at %dx%d\n", x, y);
}

void Drag(KW_Widget * widget, int x, int y, int xrel, int yrel) {
  SDL_Rect g;
  KW_GetWidgetGeometry(widget, &g);
  printf("Drag happened, moved %dx%d\n", xrel, yrel);
  g.x += xrel;
  g.y += yrel;
  KW_SetWidgetGeometry(widget, &g);
}


int main(int argc, char ** argv) {
  
  /* initialize window and renderer */
  SDL_Window * window;
  SDL_Renderer * renderer;
  SDL_Texture * set;
  KW_GUI * gui;
  TTF_Font * font;
  SDL_Rect framegeom, labelgeom;
  KW_Widget * frame;
  int i = 0;  
  
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(320, 240, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 200, 100, 100, 1);
  TTF_Init();
  
  /* load tileset */
  set = IMG_LoadTexture(renderer, "tileset.png");
  
  /* initialize gui */
  gui = KW_Init(renderer, set);
  font = TTF_OpenFont("Fontin-Regular.ttf", 12);
  KW_SetFont(gui, font);
  
  framegeom.x = 10, framegeom.y = 10, framegeom.w = 300, framegeom.h = 220;
  labelgeom = framegeom; labelgeom.x = labelgeom.y = 0;

  /* create 10 frames and 10 labels */
  frame = KW_CreateFrame(gui, NULL, &framegeom);
  framegeom.x = 10, framegeom.y = 10, framegeom.w = 160, framegeom.h = 120;
  labelgeom = framegeom; labelgeom.x = labelgeom.y = 0;
  for (i = 0; i < 10; i++) {
    frame = KW_CreateButton(gui, frame, "Yay", &framegeom);
      KW_AddWidgetDragStartHandler(frame, DragStart);
      KW_AddWidgetDragStopHandler(frame, DragStop);
      KW_AddWidgetDragHandler(frame, Drag);
  }
  
  while (!SDL_QuitRequested()) {
    SDL_RenderClear(renderer);
    KW_Paint(gui);
    SDL_RenderPresent(renderer);
    SDL_Delay(1);
  }
  
  /* free stuff */
  KW_Quit(gui);
  TTF_CloseFont(font);
  SDL_DestroyTexture(set);
  TTF_Quit();
  SDL_Quit();
  
  return 0;
}