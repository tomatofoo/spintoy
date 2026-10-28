#define SDL_MAIN_USE_CALLBACKS 1

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "SDL3_ttf/SDL_ttf.h"


#define APPNAME "Spintoy"
#define APPVERSION "0.1.0"
#define APPIDENTIFIER "com.tomatofu.spintoy"
#define WIDTH 640
#define HEIGHT 480
#define SCALE 1
#define FLAGS 0
#define GAMESPEED 1
#define FONTSIZE 20

static SDL_Window *window;
static SDL_Renderer *renderer;


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    SDL_SetAppMetadata(APPNAME, APPVERSION, APPIDENTIFIER);

    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(
            SDL_LOG_CATEGORY_ERROR,
            "Failed to initialize SDL: %s",
            SDL_GetError()
        );
        return SDL_APP_FAILURE;
    }
    if (!TTF_Init()) {
        SDL_LogError(
            SDL_LOG_CATEGORY_ERROR,
            "Failed to initialize SDL_ttf: %s",
            SDL_GetError()
        );
        return SDL_APP_FAILURE;
    }
    
    if (!SDL_CreateWindowAndRenderer(
        APPNAME " " APPVERSION, WIDTH, HEIGHT, FLAGS, &window, &renderer
    )) {
        SDL_LogError(
            SDL_LOG_CATEGORY_VIDEO,
            "Failed to create window and renderer: %s",
            SDL_GetError()
        );
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
            break;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    if (!SDL_RenderClear(renderer)) {
        SDL_LogError(
            SDL_LOG_CATEGORY_RENDER,
            "Failed to clear renderer: %s",
            SDL_GetError()
        );
        return SDL_APP_FAILURE;
    }

    if (!SDL_RenderPresent(renderer)) {
        SDL_LogError(
            SDL_LOG_CATEGORY_RENDER,
            "Failed to present renderer: %s",
            SDL_GetError()
        );
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();
}
