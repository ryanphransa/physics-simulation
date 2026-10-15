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

    double Q_x = 250, Q_y = 250;
    double q_x[10000], q_y[10000];
    int amount_q = 0;
    double tick = 0;
    double a[1000] = {0}, b[1000] = {0};

    while (running)
    {
        SDL_Event event;

        SDL_FRect particle_Q = {
            Q_x,
            Q_y,
            30,
            30
        };

        SDL_FRect particle_q[1000];

        /* INPUT */
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }
        
        /* UPDATE */
        const bool *keys = SDL_GetKeyboardState(NULL);

        if (keys[SDL_SCANCODE_A] && tick > 2000) {
            q_x[amount_q] = arc4random_uniform(471);
            q_y[amount_q] = arc4random_uniform(471);

            a[amount_q] = (Q_x - q_x[amount_q]) / (Q_y - q_y[amount_q]);

            ++amount_q;

            tick = 0;
        }

        /* RENDER */
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(renderer, &particle_Q);

        for (size_t j = 0; j < amount_q; j++) {
            if (q_x[j] > Q_x)
                q_x[j] -= 0.01;
            else if (q_x[j] < Q_x)
                q_x[j] += 0.01;

            q_y[j] = a[j] * q_x[j] + Q_y - Q_x * a[j];

            particle_q[j] = (SDL_FRect){q_x[j], q_y[j], 5, 5};

            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
            SDL_RenderFillRect(renderer, &particle_q[j]);
        }

        SDL_RenderPresent(renderer);
        ++tick;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
