#include <SDL2/SDL.h>
#include <stdbool.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Window* window = SDL_CreateWindow("Paint on C", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Rect wp, bp;
    wp.w = 10;
    wp.h = 10;
    bp.w = 10;
    bp.h = 10;

    SDL_Event event;
    bool running = true;
    int mX, mY;
    bool lb = false, rb = false;

    while(running) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                    }
                    else if(event.key.keysym.sym == SDLK_c) {
                        SDL_RenderClear(renderer);
                    }
                    else if(event.key.keysym.sym == SDLK_1) {
                        wp.w = 5;
                        wp.h = 5;
                        bp.w = 5;
                        bp.h = 5;
                    }
                    else if(event.key.keysym.sym == SDLK_2) {
                        wp.w = 10;
                        wp.h = 10;
                        bp.w = 10;
                        bp.h = 10;
                    }
                    else if(event.key.keysym.sym == SDLK_3) {
                        wp.w = 15;
                        wp.h = 15;
                        bp.w = 15;
                        bp.h = 15;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT) {
                        lb = true;
                        wp.x = mX;
                        wp.y = mY;
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                        SDL_RenderFillRect(renderer, &wp);
                    }
                    else if(event.button.button == SDL_BUTTON_RIGHT) {
                        rb = true;
                        bp.x = mX;
                        bp.y = mY;
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderFillRect(renderer, &bp);
                    }
                    break;

                    case SDL_MOUSEBUTTONUP:
                        if(event.button.button == SDL_BUTTON_LEFT) {
                            lb = false;
                        }
                        else if(event.button.button == SDL_BUTTON_RIGHT) {
                            rb = false;
                        }
                        break;

                    case SDL_MOUSEMOTION:
                        mX = event.motion.x - 5;
                        mY = event.motion.y - 5;
                        if(lb) {
                            wp.x = mX;
                            wp.y = mY;
                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                            SDL_RenderFillRect(renderer, &wp);
                        }
                        else if(rb) {
                            bp.x = mX;
                            bp.y = mY;
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                            SDL_RenderFillRect(renderer, &bp);
                        }
                        break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
} 
