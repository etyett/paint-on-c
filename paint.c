#include <SDL2/SDL.h>
#include <stdbool.h>

int main() {
    printf("\x1b[?1049h\x1b[2J\x1b[H");

    int screen_w, screen_h;
    printf("Enter screen weidth: ");
    scanf("%d", &screen_w);
    printf("Enter screen height: ");
    scanf("%d", &screen_h);

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "error: %s\n", SDL_GetError());
        exit(1);
        return -1;
    }
    
    SDL_Window* window = SDL_CreateWindow("Void Draw", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_w, screen_h, SDL_WINDOW_SHOWN);
    if(!window) {
        fprintf(stderr, "error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {
        fprintf(stderr, "error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
        return -1;
    }

    SDL_Rect leftPixel, rightPixel;
    leftPixel.w = 5;
    leftPixel.h = 5;
    rightPixel.w = 5;
    rightPixel.h = 5;

    SDL_Color leftPixelColor;
    leftPixelColor.r = 255;
    leftPixelColor.g = 255;
    leftPixelColor.b = 255;

    SDL_Event event;
    bool running = true;
    int mouseX, mouseY;
    bool leftButton = false, rightButton = false;

    while(running) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE) running = false;
                    else if(event.key.keysym.sym == SDLK_c) SDL_RenderClear(renderer);

                    if(event.key.keysym.sym == SDLK_1) {
                        leftPixel.w = 5;
                        leftPixel.h = 5;
                        rightPixel.w = 5;
                        rightPixel.h = 5;
                    }
                    else if(event.key.keysym.sym == SDLK_2) {
                        leftPixel.w = 10;
                        leftPixel.h = 10;
                        rightPixel.w = 10;
                        rightPixel.h = 10;
                    }
                    else if(event.key.keysym.sym == SDLK_3) {
                        leftPixel.w = 15;
                        leftPixel.h = 15;
                        rightPixel.w = 15;
                        rightPixel.h = 15;
                    }
                    else if(event.key.keysym.sym == SDLK_4) {
                        leftPixel.w = 20;
                        leftPixel.h = 20;
                        rightPixel.w = 20;
                        rightPixel.h = 20;
                    }
                    else if(event.key.keysym.sym == SDLK_5) {
                        leftPixel.w = 25;
                        leftPixel.h = 25;
                        rightPixel.w = 25;
                        rightPixel.h = 25;
                    }

                    if(event.key.keysym.sym == SDLK_r) {
                        leftPixelColor.r = 255;
                        leftPixelColor.g = 0;
                        leftPixelColor.b = 0;
                    }
                    else if(event.key.keysym.sym == SDLK_g) {
                        leftPixelColor.r = 0;
                        leftPixelColor.g = 255;
                        leftPixelColor.b = 0;
                    }
                    else if(event.key.keysym.sym == SDLK_b) {
                        leftPixelColor.r = 0;
                        leftPixelColor.g = 0;
                        leftPixelColor.b = 255;
                    }
                    else if(event.key.keysym.sym == SDLK_w) {
                        leftPixelColor.r = 255;
                        leftPixelColor.g = 255;
                        leftPixelColor.b = 255;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT) {
                        leftButton = true;
                        leftPixel.x = mouseX;
                        leftPixel.y = mouseY;
                        SDL_SetRenderDrawColor(renderer, leftPixelColor.r, leftPixelColor.g, leftPixelColor.b, 255);
                        SDL_RenderFillRect(renderer, &leftPixel);
                    }
                    else if(event.button.button == SDL_BUTTON_RIGHT) {
                        rightButton = true;
                        rightPixel.x = mouseX;
                        rightPixel.y = mouseY;
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderFillRect(renderer, &rightPixel);
                    }
                    break;

                    case SDL_MOUSEBUTTONUP:
                        if(event.button.button == SDL_BUTTON_LEFT) leftButton = false;
                        else if(event.button.button == SDL_BUTTON_RIGHT) rightButton = false;
                        break;

                    case SDL_MOUSEMOTION:
                        mouseX = event.motion.x - 5;
                        mouseY = event.motion.y - 5;
                        if(leftButton) {
                            leftPixel.x = mouseX;
                            leftPixel.y = mouseY;
                            SDL_SetRenderDrawColor(renderer, leftPixelColor.r, leftPixelColor.g, leftPixelColor.b, 255);
                            SDL_RenderFillRect(renderer, &leftPixel);
                        }
                        else if(rightButton) {
                            rightPixel.x = mouseX;
                            rightPixel.y = mouseY;
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                            SDL_RenderFillRect(renderer, &rightPixel);
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

    printf("\x1b[?1049l");

    return 0;
} 
