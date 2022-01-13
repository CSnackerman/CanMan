#include <iostream>
#include <string>

#include <SDL.h>
#undef main

// *** GLOBAL CONSTANTS *** //
constexpr auto WIDTH = 800;
constexpr auto HEIGHT = 600;
auto RUNNING = true;


// ~~~ Forward Declarations a.k.a Function Prototypes ~~~ //
void setColor (SDL_Renderer* renderer, int r, int g, int b);
void setColor (SDL_Renderer* renderer, std::string hexColor);
void clampColors(int& r, int& g, int& b);


// ### Primary Function Definitions ### //
void
initialize () {
    if (SDL_Init (SDL_INIT_EVERYTHING != 0)) {
        SDL_Log ("Unable to initialize SDL: %s", SDL_GetError ());
        exit (1);
    }
}

void 
setup(SDL_Window* w, SDL_Surface* wSurf, SDL_Renderer* r) {
    w = SDL_CreateWindow (
        "Can Man",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        0
    );

    wSurf = SDL_GetWindowSurface(w);

    r = SDL_CreateRenderer (w, -1, 0);
}

void handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_QUIT: RUNNING = false;
            break;
        }
    }
}

void 
run(SDL_Window* w, SDL_Renderer* r) {

    SDL_Rect wRect = { 0, 0, 100, 100 };

    while (RUNNING) {

        handleEvents();

        SDL_SetRenderDrawColor(r, 0, 255, 255, 255);
        SDL_RenderClear (r);

        /*SDL_SetRenderDrawColor(r, 0, 255, 0, 255);  
        SDL_RenderFillRect(r, &wRect);*/

        SDL_RenderPresent(r);
    }
}



// ----- MAIN FUNCTION ----- //

int 
main () {

    SDL_Window* window = nullptr;
    SDL_Surface* wSurface = nullptr;
    SDL_Renderer* render = nullptr;

    initialize ();
    setup (window, wSurface, render);
    run (window, render);

    SDL_DestroyRenderer (render);
    SDL_DestroyWindow (window);

    SDL_Quit ();

	return 0;
}





// $ UTILITY $ //

void 
setColor(SDL_Renderer* renderer, int r, int g, int b) {

    // clamp the color values between the range [0, 255]
    clampColors(r, g, b);

    // makes call to the SDL2 library function
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

void 
setColor(SDL_Renderer* renderer, std::string hexColor) {

    // Extract Colors

    // need each pair of hex numbers converted
    // to decimal integers in the range [0, 255]

    // cut up the string using substrings (string within a string)
    //  e.g. "ABC" -> "B" is a substring of "ABC"
    std::string red   = hexColor.substr (1, 2);
    std::string green = hexColor.substr (3, 2);
    std::string blue  = hexColor.substr (5, 2);

    /*std::cout << red << " " << green << " " << blue << std::endl;*/

    // convert to integer
    int r = std::stoi (red,   nullptr, 16);
    int g = std::stoi (green, nullptr, 16);
    int b = std::stoi (blue,  nullptr, 16);
    
    /*std::cout << r << " " << g << " " << b << std::endl;*/

    clampColors (r, g, b);

    // execute SDL2 library function
    SDL_SetRenderDrawColor (renderer, r, g, b, 255);

    //std::cout << "Set color to [" << r << ", " << g << ", " << b << "]" << std::endl;
}

void 
clampColors (int& r, int& g, int& b) {

    // clamp colors within the range [0, 255]
    bool redTooLow   = r < 0;   bool redTooHigh   = r > 255;
    bool greenTooLow = g < 0;   bool greenTooHigh = g > 255;
    bool blueTooLow  = g < 0;   bool blueTooHigh  = b > 255;

    if (redTooLow)   r = 0;     if (redTooHigh)   r = 255;
    if (greenTooLow) g = 0;     if (greenTooHigh) g = 255;
    if (blueTooLow)  b = 0;     if (blueTooHigh)  b = 255;
}