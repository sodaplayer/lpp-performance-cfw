#ifndef GOL_H
#define GOL_H

#include "app.h"
#include "modes/mode.h"

#include "string.h"

void gol_init();
void gol_timer_event();
void gol_surface_event(u8 p, u8 v, u8 x, u8 y);
void gol_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v);
void gol_aftertouch_event(u8 v);
void gol_poly_event(u8 p, u8 v);

#endif
