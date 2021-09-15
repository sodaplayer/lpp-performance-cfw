#include "modes/special/gol.h"

u8 gol_board[8][8];
u8 old_board[8][8];
u8 fade[8][8];
const u8 brightness[10] = {0, 1, 2, 3, 5, 8, 13, 18, 25, 64};
const u8 degree[7] = {0, 2, 4, 5, 7, 9, 11};

u8 index = 0;
u16 stepper = 0;

void gol_init() {
    for (u8 i = 0; i < 8; i++) {
        for (u8 j = 0; j < 8; j++) {
            gol_board[i][j] = 0;
        }
    }

    gol_board[4][4] = 1;
    gol_board[5][3] = 1;
    gol_board[5][2] = 1;
    gol_board[4][2] = 1;
    gol_board[3][2] = 1;

    for (u8 x = 0; x < 8; x++) {
        for (u8 y = 0; y < 8; y++) {
            u8 state = gol_board[x][y];
            if (state != 0) {
                rgb_led((x + 1) * 10 + (y + 1), 20, 20, 20);
            }
        }
    }
}

void gol_timer_event() {
    if (stepper++ > 300) {
        stepper = 0;
        step_board();
        draw_board();
    }
}

u8 sum_neighbors(u8 x, u8 y, u8 (*board)[8]) {
    u8 sum = 0;
    for (s8 i = 0; i <= 2; i++) {
        for (s8 j = 0; j <= 2; j++) {
            if (i != 1 || j != 1) {
                sum += board[(i + x + 7) % 8][(j + y + 7) % 8];
            }
        }
    }

    return sum;
}

void step_board() {
    for (u8 i = 0; i < 8; i++) {
        for (u8 j = 0; j < 8; j++) {
            old_board[i][j] = gol_board[i][j];
        }
    }

    for (u8 i = 0; i < 8; i++) {
        for (u8 j = 0; j < 8; j++) {
            switch(sum_neighbors(i, j, old_board)) {
                case 2:
                    gol_board[i][j] = old_board[i][j];
                    break;

                case 3:
                    gol_board[i][j] = 1;
                    break;

                default:
                    gol_board[i][j] = 0;
                    break;
            }
        }
    }

    for (u8 i = 0; i < 8; i++) {
        for (u8 j = 0; j < 8; j++) {
            u8 state = gol_board[i][j];
            send_midi(2 - mode_default, (state? 0x90 : 0x80) | note_channel(), (j + 3) * 12 + degree[i], state * 60);
        }
    }
}

void draw_board() {
    for (u8 x = 0; x < 8; x++) {
        for (u8 y = 0; y < 8; y++) {
            u8 state = gol_board[x][y];
            if (state != 0) {
                fade[x][y] = 10;
            } else {
                fade[x][y] = fade[x][y] + !(fade[x][y]) - 1;
            }
        }
    }

    for (u8 x = 0; x < 8; x++) {
        for (u8 y = 0; y < 8; y++) {
            rgb_led((x + 1) * 10 + (y + 1), brightness[fade[x][y]], (fade[x][y] == 10) ? 63 : 0, (fade[x][y] == 10) ? 63 : 0);
        }
    }
}


void gol_surface_event(u8 p, u8 v, u8 x, u8 y) {
    if (p == 0 && v) {
        mode_update(mode_setup);
        return;
    } else {
        gol_board[(x - 1) + 8 % 8][(y - 1) + 8 % 8] = 1;
        draw_board();
    }
}

void gol_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v) {}
void gol_aftertouch_event(u8 v) {}
void gol_poly_event(u8 p, u8 v) {}
