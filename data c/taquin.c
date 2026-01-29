#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define WINDOW_SIZE 700
#define TILE_MARGIN 6
#define SHADOW_OFFSET 3

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
            SDL_Rect r = {x + (i % 3) * pix, y + (i / 3) * pix, pix, pix};
            SDL_RenderFillRect(renderer, &r);
        }
    }
}

void draw_board(SDL_Renderer *renderer, Game *g) {
    int tile_size = (WINDOW_SIZE - 60) / g->size;
    int offset = 30;

    // Fond dégradé subtil (gris foncé avec teinte bleue)
    SDL_SetRenderDrawColor(renderer, 30, 35, 45, 255);
    SDL_RenderClear(renderer);

    // Bordure décorative autour du plateau
    SDL_SetRenderDrawColor(renderer, 60, 70, 85, 255);
    SDL_Rect border = {offset - 5, offset - 5, g->size * tile_size + 10, g->size * tile_size + 10};
    SDL_RenderFillRect(renderer, &border);

    for (int i = 0; i < g->size * g->size; i++) {
        int row = i / g->size, col = i % g->size;
        int base_x = offset + col * tile_size;
        int base_y = offset + row * tile_size;

        if (g->board[i] == 0) {
            // Case vide avec effet de profondeur
            SDL_SetRenderDrawColor(renderer, 25, 30, 35, 255);
            SDL_Rect r = {base_x + TILE_MARGIN, base_y + TILE_MARGIN, 
                          tile_size - TILE_MARGIN*2, tile_size - TILE_MARGIN*2};
            SDL_RenderFillRect(renderer, &r);
            
            // Bordure subtile pour la case vide
            SDL_SetRenderDrawColor(renderer, 40, 45, 50, 255);
            SDL_RenderDrawRect(renderer, &r);
        } else {
            // Ombre portée pour effet 3D
            SDL_SetRenderDrawColor(renderer, 15, 20, 30, 200);
            SDL_Rect shadow = {base_x + TILE_MARGIN + SHADOW_OFFSET, 
                               base_y + TILE_MARGIN + SHADOW_OFFSET,
                               tile_size - TILE_MARGIN*2, tile_size - TILE_MARGIN*2};
            SDL_RenderFillRect(renderer, &shadow);

            // Tuile principale avec dégradé simulé (couleur vibrante)
            int hue_variation = (g->board[i] * 37) % 60; // Variation de couleur basée sur le numéro
            SDL_SetRenderDrawColor(renderer, 
                                   60 + hue_variation, 
                                   140 + hue_variation/2, 
                                   220 - hue_variation/3, 
                                   255);
            SDL_Rect r = {base_x + TILE_MARGIN, base_y + TILE_MARGIN, 
                          tile_size - TILE_MARGIN*2, tile_size - TILE_MARGIN*2};
            SDL_RenderFillRect(renderer, &r);

            // Bordure claire en haut et à gauche (effet relief)
            SDL_SetRenderDrawColor(renderer, 120, 180, 255, 255);
            SDL_RenderDrawLine(renderer, r.x, r.y, r.x + r.w, r.y);
            SDL_RenderDrawLine(renderer, r.x, r.y, r.x, r.y + r.h);

            // Bordure sombre en bas et à droite (effet relief)
            SDL_SetRenderDrawColor(renderer, 30, 70, 150, 255);
            SDL_RenderDrawLine(renderer, r.x + r.w, r.y, r.x + r.w, r.y + r.h);
            SDL_RenderDrawLine(renderer, r.x, r.y + r.h, r.x + r.w, r.y + r.h);

            // Numéro en blanc avec ombre légère
            int n = g->board[i];
            int px = (tile_size - TILE_MARGIN*2) / 12;
            if (px < 3) px = 3;
            if (px > 8) px = 8;

            // Ombre du texte
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
            if (n < 10) {
                draw_glyph(renderer, n, (int)(r.x + r.w/2 - 1.5*px) + 1, (int)(r.y + r.h/2 - 2.5*px) + 1, px);
            } else {
                draw_glyph(renderer, n/10, (int)(r.x + r.w/2 - 3.5*px) + 1, (int)(r.y + r.h/2 - 2.5*px) + 1, px);
                draw_glyph(renderer, n%10, (int)(r.x + r.w/2 + 0.5*px) + 1, (int)(r.y + r.h/2 - 2.5*px) + 1, px);
            }

            // Texte principal en blanc brillant
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            if (n < 10) {
                draw_glyph(renderer, n, (int)(r.x + r.w/2 - 1.5*px), (int)(r.y + r.h/2 - 2.5*px), px);
            } else {
                draw_glyph(renderer, n/10, (int)(r.x + r.w/2 - 3.5*px), (int)(r.y + r.h/2 - 2.5*px), px);
                draw_glyph(renderer, n%10, (int)(r.x + r.w/2 + 0.5*px), (int)(r.y + r.h/2 - 2.5*px), px);
            }
        }
    }

    if (g->won) {
        // Overlay semi-transparent pour assombrir le fond
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
        SDL_Rect overlay = {0, 0, WINDOW_SIZE, WINDOW_SIZE};
        SDL_RenderFillRect(renderer, &overlay);

        // Bandeau de victoire avec bordure (agrandi pour le message)
        SDL_SetRenderDrawColor(renderer, 0, 200, 100, 255);
        SDL_Rect banner = {WINDOW_SIZE/2 - 180, WINDOW_SIZE/2 - 90, 360, 180};
        SDL_RenderFillRect(renderer, &banner);

        // Bordure dorée autour du bandeau
        SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);
        SDL_Rect gold_border = {WINDOW_SIZE/2 - 182, WINDOW_SIZE/2 - 92, 364, 184};
        SDL_RenderDrawRect(renderer, &gold_border);
        SDL_Rect gold_border2 = {WINDOW_SIZE/2 - 181, WINDOW_SIZE/2 - 91, 362, 182};
        SDL_RenderDrawRect(renderer, &gold_border2);

        // Ombre du texte "VICTOIRE"
        int word[] = {10, 11, 12, 13, 14, 11, 15, 16}; // VICTOIRE
        int px = 14;
        int start_x = (WINDOW_SIZE - (8 * 4 * px)) / 2;
        SDL_SetRenderDrawColor(renderer, 0, 100, 50, 255);
        for(int i=0; i<8; i++) {
            draw_glyph(renderer, word[i], start_x + i * 4 * px + 2, WINDOW_SIZE/2 - 35 + 2, px);
        }

        // Texte "VICTOIRE" principal en blanc
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for(int i=0; i<8; i++) {
            draw_glyph(renderer, word[i], start_x + i * 4 * px, WINDOW_SIZE/2 - 35, px);
        }

        // Message "Appuyez sur R pour rejouer"
        // Lettres disponibles: R(15), O(14), U(non disponible), E(16), I(11), O(14), I(11), E(16)
        // On va utiliser "R" suivi d'un texte simple ou utiliser les lettres disponibles
        // Pour simplifier, on affiche juste "R" en grand avec une indication
        int px_small = 8;
        int r_x = WINDOW_SIZE/2 - 12;
        int r_y = WINDOW_SIZE/2 + 25;
        
        // Ombre de "R"
        SDL_SetRenderDrawColor(renderer, 0, 100, 50, 255);
        draw_glyph(renderer, 15, r_x + 1, r_y + 1, px_small); // R
        
        // "R" en jaune/or
        SDL_SetRenderDrawColor(renderer, 255, 220, 0, 255);
        draw_glyph(renderer, 15, r_x, r_y, px_small); // R
        
        // Ligne de séparation
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
        SDL_RenderDrawLine(renderer, WINDOW_SIZE/2 - 100, WINDOW_SIZE/2 + 10, WINDOW_SIZE/2 + 100, WINDOW_SIZE/2 + 10);
        
        // Petit rectangle pour indiquer que c'est cliquable
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 150);
        SDL_Rect hint = {WINDOW_SIZE/2 - 80, WINDOW_SIZE/2 + 35, 160, 3};
        SDL_RenderFillRect(renderer, &hint);
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

    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
    SDL_Window *win = SDL_CreateWindow("Taquin - Puzzle Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_SIZE, WINDOW_SIZE, SDL_WINDOW_SHOWN);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) quit = true;
                if (e.key.keysym.sym == SDLK_r) {
                    shuffle_board(&game);
                }
                if (!game.won) {
                    if (e.key.keysym.sym == SDLK_UP) move_tile(&game, 0);
                    if (e.key.keysym.sym == SDLK_DOWN) move_tile(&game, 1);
                    if (e.key.keysym.sym == SDLK_LEFT) move_tile(&game, 2);
                    if (e.key.keysym.sym == SDLK_RIGHT) move_tile(&game, 3);
                }
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (game.won) {
                    // Si on a gagné, cliquer n'importe où relance une nouvelle partie
                    shuffle_board(&game);
                } else {
                    // Sinon, gestion normale des clics sur les tuiles
                    int ts = (WINDOW_SIZE - 60) / game.size;
                    int col = (int)((e.button.x - 30) / ts), row = (int)((e.button.y - 30) / ts);
                    if (col >= 0 && col < game.size && row >= 0 && row < game.size) {
                        int er = game.empty_pos / game.size, ec = game.empty_pos % game.size;
                        if (row == er + 1 && col == ec) move_tile(&game, 0);
                        else if (row == er - 1 && col == ec) move_tile(&game, 1);
                        else if (row == er && col == ec + 1) move_tile(&game, 2);
                        else if (row == er && col == ec - 1) move_tile(&game, 3);
                    }
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