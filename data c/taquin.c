#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define WINDOW_SIZE 600
#define TILE_MARGIN 4

// --- STRUCTURES ET GLOBALES ---
typedef struct {
    int size;          
    int *board;        
    int empty_pos;     
    bool won;
} Game;

// Police bitmap 3x5 (Chiffres 0-9 puis Lettres V,I,C,T,O,R,E)
const uint16_t FONT_MAP[] = {
    0x7B6F, // 0
    0x2492, // 1
    0x73E7, // 2
    0x73CF, // 3
    0x5BC9, // 4
    0x79CF, // 5
    0x79EF, // 6
    0x7249, // 7
    0x7BEF, // 8
    0x7BCF, // 9
    0x5AD2, // V (10)
    0x7497, // I (11)
    0x7897, // C (12)
    0x7492, // T (13)
    0x7B6F, // O (14) - Identique au 0
    0x7B6D, // R (15)
    0x7997  // E (16)
};

// --- LOGIQUE DE JEU ---

bool is_solvable(int size, int *board) {
    int inversions = 0;
    int total_cells = size * size;
    for (int i = 0; i < total_cells; i++) {
        if (board[i] == 0) continue;
        for (int j = i + 1; j < total_cells; j++) {
            if (board[j] != 0 && board[i] > board[j]) inversions++;
        }
    }
    if (size % 2 != 0) return (inversions % 2 == 0);
    int empty_row_from_bottom = 0;
    for(int i=0; i<total_cells; i++) if(board[i] == 0) empty_row_from_bottom = size - (i / size);
    return (inversions + empty_row_from_bottom) % 2 == 0;
}

bool is_solved(Game *g) {
    for (int i = 0; i < g->size * g->size - 1; i++) {
        if (g->board[i] != i + 1) return false;
    }
    return g->board[g->size * g->size - 1] == 0;
}

void shuffle_board(Game *g) {
    int n = g->size * g->size;
    do {
        for (int i = 0; i < n; i++) g->board[i] = i;
        for (int i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            int temp = g->board[i];
            g->board[i] = g->board[j];
            g->board[j] = temp;
        }
        for (int i = 0; i < n; i++) if (g->board[i] == 0) g->empty_pos = i;
    } while (!is_solvable(g->size, g->board) || is_solved(g));
    g->won = false;
}

void move_tile(Game *g, int direction) {
    int row = g->empty_pos / g->size;
    int col = g->empty_pos % g->size;
    int target_pos = -1;
    if (direction == 0 && row < g->size - 1) target_pos = g->empty_pos + g->size;
    if (direction == 1 && row > 0) target_pos = g->empty_pos - g->size;
    if (direction == 2 && col < g->size - 1) target_pos = g->empty_pos + 1;
    if (direction == 3 && col > 0) target_pos = g->empty_pos - 1;

    if (target_pos != -1) {
        g->board[g->empty_pos] = g->board[target_pos];
        g->board[target_pos] = 0;
        g->empty_pos = target_pos;
        if (is_solved(g)) g->won = true;
    }
}

// --- RENDU ---

void draw_glyph(SDL_Renderer *renderer, int index, int x, int y, int pix) {
    uint16_t bitmap = FONT_MAP[index];
    for (int i = 0; i < 15; i++) {
        if (bitmap & (1 << (14 - i))) {
            SDL_FRect r = {(float)(x + (i % 3) * pix), (float)(y + (i / 3) * pix), (float)pix, (float)pix};
            SDL_RenderFillRect(renderer, &r);
        }
    }
}

void draw_board(SDL_Renderer *renderer, Game *g) {
    int tile_size = (WINDOW_SIZE - 40) / g->size;
    int offset = 20;

    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < g->size * g->size; i++) {
        int row = i / g->size, col = i % g->size;
        SDL_FRect r = {(float)(offset + col*tile_size + TILE_MARGIN), (float)(offset + row*tile_size + TILE_MARGIN), 
                       (float)(tile_size - TILE_MARGIN*2), (float)(tile_size - TILE_MARGIN*2)};

        if (g->board[i] == 0) {
            SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
            SDL_RenderFillRect(renderer, &r);
        } else {
            SDL_SetRenderDrawColor(renderer, 40, 120, 200, 255);
            SDL_RenderFillRect(renderer, &r);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            int n = g->board[i];
            int px = tile_size / 10;
            if (n < 10) draw_glyph(renderer, n, (int)(r.x + r.w/2 - 1.5*px), (int)(r.y + r.h/2 - 2.5*px), px);
            else {
                draw_glyph(renderer, n/10, (int)(r.x + r.w/2 - 3.5*px), (int)(r.y + r.h/2 - 2.5*px), px);
                draw_glyph(renderer, n%10, (int)(r.x + r.w/2 + 0.5*px), (int)(r.y + r.h/2 - 2.5*px), px);
            }
        }
    }

    if (g->won) {
        // Bandeau de victoire
        SDL_SetRenderDrawColor(renderer, 0, 180, 0, 255);
        SDL_FRect banner = {0, WINDOW_SIZE/2 - 60, WINDOW_SIZE, 120};
        SDL_RenderFillRect(renderer, &banner);
        
        // Texte "VICTOIRE" (V=10, I=11, C=12, T=13, O=14, R=15, E=16)
        int word[] = {10, 11, 12, 13, 14, 11, 15, 16};
        int px = 12; // Taille des "pixels" du texte de victoire
        int start_x = (WINDOW_SIZE - (8 * 4 * px)) / 2;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for(int i=0; i<8; i++) draw_glyph(renderer, word[i], start_x + i * 4 * px, WINDOW_SIZE/2 - 2.5*px, px);
    }
    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[]) {
    srand((unsigned int)time(NULL));
    int size = 0;
    while (size < 3 || size > 5) {
        printf("Taille du plateau (3, 4 ou 5) : ");
        if (scanf("%d", &size) != 1) while (getchar() != '\n');
    }

    Game game;
    game.size = size;
    game.board = malloc(size * size * sizeof(int));
    shuffle_board(&game);

    if (!SDL_Init(SDL_INIT_VIDEO)) return 1;
    SDL_Window *win = SDL_CreateWindow("Taquin SDL3", WINDOW_SIZE, WINDOW_SIZE, 0);
    SDL_Renderer *ren = SDL_CreateRenderer(win, NULL);

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) quit = true;
            if (e.type == SDL_EVENT_KEY_DOWN) {
                if (e.key.key == SDLK_ESCAPE) quit = true;
                if (e.key.key == SDLK_R) shuffle_board(&game);
                if (!game.won) {
                    if (e.key.key == SDLK_UP) move_tile(&game, 0);
                    if (e.key.key == SDLK_DOWN) move_tile(&game, 1);
                    if (e.key.key == SDLK_LEFT) move_tile(&game, 2);
                    if (e.key.key == SDLK_RIGHT) move_tile(&game, 3);
                }
            }
            if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN && !game.won) {
                int ts = (WINDOW_SIZE - 40) / game.size;
                int col = (int)((e.button.x - 20) / ts), row = (int)((e.button.y - 20) / ts);
                if (col >= 0 && col < game.size && row >= 0 && row < game.size) {
                    int er = game.empty_pos / game.size, ec = game.empty_pos % game.size;
                    if (row == er + 1 && col == ec) move_tile(&game, 0);
                    else if (row == er - 1 && col == ec) move_tile(&game, 1);
                    else if (row == er && col == ec + 1) move_tile(&game, 2);
                    else if (row == er && col == ec - 1) move_tile(&game, 3);
                }
            }
        }
        draw_board(ren, &game);
        SDL_Delay(16);
    }

    free(game.board);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}