#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define screen_height 500
#define screen_width 500

#define particles_limit 10000

/*void repulsion(double *q_x, double *q_y, double Q_x, double Q_y, size_t j) {
    if (q_x[j] > Q_x)
        q_x[j] += 0.01;
    else if (q_x[j] < Q_x)
        q_x[j] -= 0.01;

    double a = (q_x[j] - Q_x) / (q_y[j] - Q_y);
    q_y[j] = Q_y - Q_x * a;
}

void attraction(double *q_x, double *q_y, double Q_x, double Q_y, size_t j) {
    if (q_x[j] > Q_x)
        q_x[j] -= 0.01;
    else if (q_x[j] < Q_x)
        q_x[j] += 0.01;

    double a = (q_x[j] - Q_x) / (q_y[j] - Q_y);
    q_y[j] = Q_y - Q_x * a;
}*/

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window =
        SDL_CreateWindow("Screen", screen_height, screen_width, 0);

    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, NULL);

    bool running = true;

    double Q_x = 10;
    double Q_y = 300;

    double q_x[100];
    double q_y[100];

    int particles_amount = 0;

    double tick = 0;

    double a[100] = {0};

    double Q = 4, q = -4;

    while (running)
    {
        SDL_Event event;

        SDL_FRect particle_Q = {
            Q_x,
            Q_y,
            30,
            30
        };

        SDL_FRect proof_particle[particles_limit];

        /* INPUT */
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }
        
        /* UPDATE */
        const bool *keys = SDL_GetKeyboardState(NULL);

        if (keys[SDL_SCANCODE_A] && tick > 1000) {
            q_x[particles_amount] = arc4random_uniform(471);
            q_y[particles_amount] = arc4random_uniform(471);

            ++particles_amount;
            tick = 0;
        }

        for (size_t j = particles_limit; j > 0; j--) {
            proof_particle[j] = (SDL_FRect){q_x[j], q_y[j], 5, 5};
        }

        /* MATH */
        for (size_t j = 0; j < particles_amount; j++) {
            if (q_x[j] > Q_x)
                q_x[j] -= 0.01;
            else if (q_x[j] < Q_x)
                q_x[j] += 0.01;

            a[j] = (q_x[j] - Q_x) / (q_y[j] - Q_y);
            q_y[j] = Q_y - Q_x * a[j];
        }

        /* RENDER */
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(renderer, &particle_Q);

        for (size_t j = 0; j < particles_amount; j++) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
            SDL_RenderFillRect(renderer, &proof_particle[j]);
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &proof_particle[4]);

        ++tick;

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
