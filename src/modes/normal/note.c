#include "modes/normal/note.h"
#include "note_defs.h"

#define note_octave_start 3
#define note_transpose_start 0

#define note_color_invalid_r 0x07
#define note_color_invalid_g 0x00
#define note_color_invalid_b 0x00

#define note_color_base_r 0x3f
#define note_color_base_g 0x00
#define note_color_base_b 0x3f

#define note_color_transposed_r 0x14
#define note_color_transposed_g 0x00
#define note_color_transposed_b 0x3f

#define note_color_white_r 0x3f
#define note_color_white_g 0x29
#define note_color_white_b 0x3f

#define note_color_trans_white_r 0x29
#define note_color_trans_white_g 0x29
#define note_color_trans_white_b 0x3f

#define note_color_scale_base_r 0x14
#define note_color_scale_base_g 0x00
#define note_color_scale_base_b 0x3f

#define note_color_scale_r 0x3f
#define note_color_scale_g 0x00
#define note_color_scale_b 0x3f

#define note_color_pressed_r 0x00
#define note_color_pressed_g 0x3f
#define note_color_pressed_b 0x00

#define note_color_pressed_oct_r 0x0a
#define note_color_pressed_oct_g 0x14
#define note_color_pressed_oct_b 0x00

#define note_length 12
#define note_segment 5

#define note_color_white {0x29, 0x29, 0x3f}
#define note_color_black {0x00, 0x00, 0x00}

const u8 note_scale_colors[12][3] = {
    {0x37, 0x00, 0x09}, // unison / octave
    {0x37, 0x04, 0x00}, // minor second
    {0x2b, 0x18, 0x00}, // major second
    {0x24, 0x1c, 0x00}, // minor third
    {0x1b, 0x20, 0x00}, // major third
    {0x00, 0x23, 0x10}, // perfect fourth
    {0x00, 0x22, 0x1e}, // tritone
    {0x00, 0x21, 0x25}, // perfect fifth
    {0x00, 0x1f, 0x2e}, // minor sixth
    {0x11, 0x17, 0x3f}, // major sixth
    {0x25, 0x09, 0x3f}, // minor seventh
    {0x2c, 0x00, 0x38}  // major seventh
};

const u8 note_accidental_colors[12][3] = {
    {0x37 >> 4, 0x00 >> 4, 0x09 >> 4}, // unison / octave
    {0x37 >> 4, 0x04 >> 4, 0x00 >> 4}, // minor second
    {0x2b >> 4, 0x18 >> 4, 0x00 >> 4}, // major second
    {0x24 >> 4, 0x1c >> 4, 0x00 >> 4}, // minor third
    {0x1b >> 4, 0x20 >> 4, 0x00 >> 4}, // major third
    {0x00 >> 4, 0x23 >> 4, 0x10 >> 4}, // perfect fourth
    {0x00 >> 4, 0x22 >> 4, 0x1e >> 4}, // tritone
    {0x00 >> 4, 0x21 >> 4, 0x25 >> 4}, // perfect fifth
    {0x00 >> 4, 0x1f >> 4, 0x2e >> 4}, // minor sixth
    {0x11 >> 4, 0x17 >> 4, 0x3f >> 4}, // major sixth
    {0x25 >> 4, 0x09 >> 4, 0x3f >> 4}, // minor seventh
    {0x2c >> 4, 0x00 >> 4, 0x38 >> 4}  // major seventh
};

const u8* note_pitchclass_colors[12] = {
    &note_scale_colors[0],
    &note_scale_colors[1],
    &note_scale_colors[2],
    &note_scale_colors[3],
    &note_scale_colors[4],
    &note_scale_colors[5],
    &note_scale_colors[6],
    &note_scale_colors[7],
    &note_scale_colors[8],
    &note_scale_colors[9],
    &note_scale_colors[10]
    &note_scale_colors[11]
};

const u8 note_cmajor_colors[12][3] = {
    {0x37, 0x00, 0x09}, // unison / octave
    note_color_black,   // minor second
    note_color_white,   // major second
    {0x04, 0x03, 0x00}, // minor third
    {0x1b, 0x20, 0x00}, // major third
    note_color_white,   // perfect fourth
    note_color_black,   // tritone
    {0x00, 0x21, 0x25}, // perfect fifth
    note_color_black,   // minor sixth
    note_color_white,   // major sixth
    note_color_black,   // minor seventh
    note_color_white    // major seventh
};

const u8* major_colors[7] = {
    &note_scale_colors[0],
    &note_scale_colors[2],
    &note_scale_colors[4],
    &note_scale_colors[5],
    &note_scale_colors[7],
    &note_scale_colors[9],
    &note_scale_colors[11]
};

const u8 note_octave_colors[10][3] = {
    {0x3f, 0x00, 0x3f},
    {0x14, 0x00, 0x3f},
    {0x00, 0x1f, 0x3f},
    {0x00, 0x00, 0x1f},
    {0x00, 0x00, 0x07},
    {0x00, 0x00, 0x1f},
    {0x00, 0x1f, 0x3f},
    {0x14, 0x00, 0x3f},
    {0x28, 0x00, 0x3f},
    {0x3f, 0x00, 0x3f}
};
const u8 note_transpose_colors[13][3] = {
    {0x00, 0x07, 0x00},
    {0x00, 0x15, 0x00},
    {0x00, 0x1f, 0x00},
    {0x00, 0x2a, 0x00},
    {0x00, 0x34, 0x00},
    {0x00, 0x3f, 0x00},
    {0x0f, 0x3f, 0x00},
    {0x17, 0x3f, 0x00},
    {0x1f, 0x3f, 0x00},
    {0x27, 0x3f, 0x00},
    {0x2f, 0x3f, 0x00},
    {0x37, 0x3f, 0x00},
    {0x3f, 0x3f, 0x00}
};

s8 note_octave = 5;
s8 note_transpose = note_transpose_start;

u8 note_shift = 0;
u8 note_program_shift = 0;
u8 note_bank_shift = 0;
u8 note_root_shift = 0;

u8 note_nav_pressed[4] = {};

u8 note_channel() {
    return mode_default == mode_note? settings.mode[mode_note].channel : 0;
}

void note_single(u8 *p, u8 l, u8 r, u8 g, u8 b) {
    for (u8 i = 0; i < l; i++) { // Used to update LEDs on buttons that trigger the same actual note
        rgb_led(*(p + i), r, g, b);
    }
}

s8 note_press(u8 x, u8 y, u8 v, s8 out_p) {
    u8 length = (settings.scale.enabled)? scales_length(settings.scale.selected) : note_length;
    u8 segment = (settings.scale.enabled)? settings.scale.segment : note_segment;

    u8 offset = (x - 1) * segment + (y - 1); // Note pressed in relation to lowest
    u8 up = offset / length; // Octaves above lowest

    offset %= length; // Note pressed in relation to its octave
    if (settings.scale.enabled) offset = scales(settings.scale.selected, offset); // Translate for Scale mode

    s8 c = (note_octave + up) * 12 + offset; // Note in relation to C
    s8 n = c + note_transpose + ((settings.scale.enabled)? settings.scale.root : 0); // Actual note (transposition applied)

    if (n == out_p || out_p < 0) {
        u8 p[8] = {x * 10 + y}; // Pitches to update on the Launchpad
        u8 l = 1;

        for (u8 i = 0; i < 7; i++) { // Add pitches above
            s8 e = x + i;
            s8 f = y - segment * i;

            if (1 <= e && e <= 8 && 1 <= f && f <= 8) {
                p[l++] = e * 10 + f; // Append to array
            } else {
                break;
            }
        }

        for (u8 i = 0; i < 7; i++) { // Add pitches below
            s8 e = x - i;
            s8 f = y + segment * i;

            if (1 <= e && e <= 8 && 1 <= f && f <= 8) {
                p[l++] = e * 10 + f;
            } else {
                break;
            }
        }

        if (n < 0) { // Invalid note - also affects notes larger than 127 due to overflow!
            note_single(&p[0], l, note_color_invalid_r, note_color_invalid_g, note_color_invalid_b);

        } else { // Valid note
            if (v == 0) { // Note released
                u8 m = modulo(c, 12); // Note without octave

                if (settings.scale.enabled) {
                    note_single(&p[0], l, note_scale_colors[m][0], note_scale_colors[m][1], note_scale_colors[m][2]);
                } else {

                    if (settings.scale.note_translate) { // Yellow Pad On
                        // Color notes in relation to SCALE, not absolute!
                        u8 local_m = modulo(12 + m - settings.scale.root, 12); // Move relative to root note
                        if (local_m == 0) { // Base note
                            note_single(&p[0], l, note_scale_colors[local_m][0], note_scale_colors[local_m][1], note_scale_colors[local_m][2]);
                            note_draw_scale_degree(v, 0, local_m);
                        } else {
                            u8 out_of_scale = 1;
                            for (u8 i = 0; i < scales_length(settings.scale.selected); i++) {
                                u8 s = scales(settings.scale.selected, i);

                                if (local_m == s) {
                                    note_single(&p[0], l, note_scale_colors[local_m][0], note_scale_colors[local_m][1], note_scale_colors[local_m][2]);
                                    out_of_scale = 0;
                                    note_draw_scale_degree(v, i, local_m);
                                    break;

                                } else if (local_m < s) {
                                    break;
                                }
                            }

                            if (out_of_scale) {
                                note_single(&p[0], l, note_accidental_colors[local_m][0], note_accidental_colors[local_m][1], note_accidental_colors[local_m][2]);
                            }
                        }
                    } else { // Absolute Mode: Yellow Pad Off
                        // Previous mode, simple C major colors
                        note_single(&p[0], l, note_cmajor_colors[m][0], note_cmajor_colors[m][1], note_cmajor_colors[m][2]);

                        // Color notes in relation to SCALE, not absolute!
                        u8 local_m = modulo(12 + m - settings.scale.root, 12); // Move relative to root note
                        if (local_m == 0) { // Base note
                            note_draw_scale_degree(v, 0, local_m);
                        } else {
                            u8 out_of_scale = 1;
                            for (u8 i = 0; i < scales_length(settings.scale.selected); i++) {
                                u8 s = scales(settings.scale.selected, i);

                                if (local_m == s) {
                                    out_of_scale = 0;
                                    note_draw_scale_degree(v, i, local_m);
                                    break;

                                } else if (local_m < s) {
                                    break;
                                }
                            }
                        }
                    }

                    // u8 b = modulo(note_transpose, length); // Base note of scale
                    // if (b != 0 && b == m) note_single(&p[0], l, note_color_transposed_r, note_color_transposed_g, note_color_transposed_b); // Scale base note
                }

            } else { // Note pressed
                if (out_p < 0) {
                    note_single(&p[0], l, note_color_pressed_r, note_color_pressed_g, note_color_pressed_b);
                } else {
                    note_single(&p[0], l, note_color_white_r, note_color_white_g, note_color_white_b);
                }

                u8 m = modulo(c, 12); // Note without octave
                u8 local_m = modulo(12 + m - settings.scale.root, 12); // Move relative to root note
                for (u8 i = 0; i < scales_length(settings.scale.selected); i++) {
                    u8 s = scales(settings.scale.selected, i);

                    if (local_m == s) {
                        note_draw_scale_degree(v, i, local_m);
                        break;
                    } else if (local_m < s) {
                        break;
                    }
                }
            }
        }
    }

    return n;
}

void note_draw_scale_degree(u8 v, u8 deg, u8 interval) {
    send_midi(2 - mode_default, 0xB0 | note_channel(), 80, deg);

    if (v == 0) {
        rgb_led(19 + deg * 10, note_accidental_colors[interval][0], note_accidental_colors[interval][1], note_accidental_colors[interval][2]);
    } else {
        rgb_led(19 + deg * 10, note_scale_colors[interval][0], note_scale_colors[interval][1], note_scale_colors[interval][2]);
    }
}

void note_draw_transpose_view() {
    u8 root = modulo((settings.scale.note_translate ? settings.scale.root : 0) + note_transpose, 12);

    u8 r = note_pitchclass_colors[root][0];
    u8 g = note_pitchclass_colors[root][1];
    u8 b = note_pitchclass_colors[root][2];

    for (u8 i = 0; i < 8; i++) {
        rgb_led(i + 1, 0, 0, 0);
    }

    switch(root) {
        case 0: // C
            rgb_led(1, r, g, b);
            break;
        case 1: // C#
            rgb_led(1, r, g, b);
            rgb_led(2, r, g, b);
            break;
        case 2: // D
            rgb_led(2, r, g, b);
            break;
        case 3: // D#
            rgb_led(2, r, g, b);
            rgb_led(3, r, g, b);
            break;
        case 4: // E
            rgb_led(3, r, g, b);
            break;
        case 5: // F
            rgb_led(4, r, g, b);
            break;
        case 6: // F#
            rgb_led(4, r, g, b);
            rgb_led(5, r, g, b);
            break;
        case 7: // G
            rgb_led(5, r, g, b);
            break;
        case 8: // G#
            rgb_led(5, r, g, b);
            rgb_led(6, r, g, b);
            break;
        case 9: // A
            rgb_led(6, r, g, b);
            break;
        case 10: // A#
            rgb_led(6, r, g, b);
            rgb_led(7, r, g, b);
            break;
        case 11: // B
            rgb_led(7, r, g, b);
            break;
    }
}

void note_draw_navigation() {
    u8 o = note_octave + 1; // Octave navigation
    if (o < 5) {
        rgb_led(91, note_octave_colors[4][0], note_octave_colors[4][1], note_octave_colors[4][2]);
        rgb_led(92, note_octave_colors[o][0], note_octave_colors[o][1], note_octave_colors[o][2]);
    } else {
        rgb_led(91, note_octave_colors[o][0], note_octave_colors[o][1], note_octave_colors[o][2]);
        rgb_led(92, note_octave_colors[4][0], note_octave_colors[4][1], note_octave_colors[4][2]);
    }

    if (settings.scale.enabled && note_shift) {
        rgb_led(93, 7 + 56 * note_nav_pressed[2], 7 + 56 * note_nav_pressed[2], 7 + 56 * note_nav_pressed[2]);
        rgb_led(94, 7 + 56 * note_nav_pressed[3], 7 + 56 * note_nav_pressed[3], 7 + 56 * note_nav_pressed[3]);

    } else {
        if (note_transpose > 0) { // Transpose navigation
            rgb_led(93, note_transpose_colors[0][0], note_transpose_colors[0][1], note_transpose_colors[0][2]);
            rgb_led(94, note_transpose_colors[note_transpose][0], note_transpose_colors[note_transpose][1], note_transpose_colors[note_transpose][2]);
        } else {
            rgb_led(93, note_transpose_colors[-note_transpose][0], note_transpose_colors[-note_transpose][1], note_transpose_colors[-note_transpose][2]);
            rgb_led(94, note_transpose_colors[0][0], note_transpose_colors[0][1], note_transpose_colors[0][2]);
        }
    }

    note_draw_transpose_view();
}

void note_root_button() {
    if (note_root_shift) { // root button pressed
        rgb_led(B_STOP, 63, 63, 0);
    } else { // root button released
        rgb_led(B_STOP, 7, 7, 0);
    }

    note_draw_transpose_view();
}

void note_scale_button() {
    if (note_shift) { // Shift button pressed
        rgb_led(B_SHIFT, 63, 63, 63);
        rgb_led(B_NOTE, 7, 7, 7);

        for (u8 i = 0; i < 7; i++) {
            rgb_led(i + 1, major_colors[i][0] >> 2, major_colors[i][1] >> 2, major_colors[i][2] >> 2);
        }

    } else { // Shift button released
        rgb_led(B_SHIFT, 7, 7, 7);
        note_draw_transpose_view();

        if (mode_default == mode_ableton) {
            rgb_led(B_NOTE, 0, 63, 63);
        } else if (mode_default == mode_note) {
            u8 root = modulo(note_transpose + settings.scale.root, 12);

            u8 r = note_pitchclass_colors[root][0];
            u8 g = note_pitchclass_colors[root][1];
            u8 b = note_pitchclass_colors[root][2];

            rgb_led(B_NOTE, r, g, b);
        }
    }

    if (settings.scale.enabled) {
        note_draw_navigation();
    }
}

void note_draw() {
    for (u8 x = 1; x < 9; x++) { // Regular notes
        for (u8 y = 1; y < 9; y++) {
            note_press(x, y, 0, -1);
        }
    }

    for (u8 i = 0; i < 128; i++) { // Turn off all notes
        send_midi(2 - mode_default, 0x80 | note_channel(), i, 0);
    }

    note_draw_navigation();
}

void note_init() {
    note_draw();
    note_scale_button();
    if (mode == mode_note) rgb_led(99, mode_note_r, mode_note_g, mode_note_b); // Note mode LED

    active_port = USBSTANDALONE;
}

void note_timer_event() {}

void note_surface_event(u8 p, u8 v, u8 x, u8 y) {
    if (p == 0) { // Enter Setup mode
        if (v != 0) mode_update(mode_setup);

    } else if (p == B_NOTE && note_shift && v != 0) { // Shift+Note button
        mode_update(mode_scale_setup); // Enter Setup for Scale mode
        rgb_led(p, 63, 63, 63);
    } else if (p == B_P1 && note_shift && v != 0) { // Shift+Note button
        settings.scale.note_translate = 1 - settings.scale.note_translate;
        note_transpose *= settings.scale.note_translate;
        mode_update(mode_note);
    } else if (p == B_NOTE && v == 0) {
        note_scale_button();
    } else if (y == 9 || (x == 9 && y > 4)) { // Unused side buttons
        // send_midi(2 - mode_default, 0xB0 | note_channel(), p, v);
        rgb_led(p, 0, (v == 0) ? 0 : 63, 0);
    } else if (y == 0 && x < 8) { // Left Mod Wheel
        if (note_shift) {
            send_midi(2 - mode_default, MD_CC | note_channel(), 1, (x - 1) * 18);
            rgb_led(p, 0, (v == 0)? 0 : x * 8 - 8, 0);
        } else {
            send_midi(2 - mode_default, MD_CC | note_channel(), 1, ((x - 1) - 3) * 18);
            rgb_led(p, (v == 0)? 0 : x * 8 - 8, 0, 0);
        }
    } else if (p == B_SHIFT) { // Shift button
        // send_midi(2 - mode_default, MD_CC | note_channel(), p, v);
        note_shift = v;
        note_scale_button();
    } else if (p == B_STOP) { // Root Shift
        note_root_shift = v;
        note_root_button();
    } else if (x == 0 && note_shift && v != 0) { // Scale Buttons
        settings.scale.selected = y + 24 - 1;
        mode_update(mode_note);
    } else if (x == 0) { // Scale Buttons
        note_root_button();
    } else if (x == 9 && y < 5) { // Navigation buttons
        if (v != 0) {
            if (settings.scale.enabled && note_shift) {
                switch (p) {
                    case B_LEFT: // Segment down
                        if (settings.scale.segment > 1) settings.scale.segment--;
                        break;

                    case B_RIGHT: // Segment up
                        if (settings.scale.segment < 8) settings.scale.segment++;
                        break;
                }
            } else {
                if (note_shift) {
                    switch (p) {
                        case B_UP:
                            break;

                        case B_DOWN:
                            break;

                        case B_LEFT: // Transpose down
                            if (note_transpose > -12) note_transpose--;
                            break;

                        case B_RIGHT: // Transpose up
                            if (note_transpose < 12) note_transpose++;
                            break;
                    }
                } else {
                    switch (p) {
                        case B_UP: // Octave up
                            if (note_octave < 8) note_octave++;
                            break;

                        case B_DOWN: // Octave down
                            if (note_octave > -1) note_octave--;
                            break;

                        case B_LEFT:
                            settings.scale.root = modulo(settings.scale.root - 1, 12);
                            note_scale_button();
                            break;

                        case B_RIGHT:
                            settings.scale.root = modulo(settings.scale.root + 1, 12);
                            note_scale_button();
                            break;
                    }
                }
            }
        }

        note_nav_pressed[p - 91] = (v)? 1 : 0;

        if (note_nav_pressed[0] && note_nav_pressed[1]) { // Reset offset. Note: Undocumented in Programmer's reference
            note_octave = note_octave_start;
        } else if (note_nav_pressed[2] && note_nav_pressed[3]) { // Reset transpose
            note_transpose = note_transpose_start;
        }

        note_draw();
        note_draw_transpose_view();

    } else { // Main grid
        s8 n = note_press(x, y, v, -1);
        if (n >= 0) send_midi(2 - mode_default, (v ? MD_ON : MD_OFF) | note_channel(), n, v);
    }
}

void note_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v) {
    if (port == 2 - mode_default && ch == note_channel()) {
        u8 x = p / 10;
        u8 y = p % 10;

        switch (t) {
            case 0x8:
                v = 0;

            case 0x9:
                for (u8 x = 1; x < 9; x++) { // I'm lazy
                    for (u8 y = 1; y < 9; y++) {
                        note_press(x, y, v, p);
                    }
                }
                break;

            case 0xB:
                if (x == 0 || (x == 9 && y > 4) || y == 0 || y == 9) {
                    novation_led(p, v);
                }
                break;
        }
    }
}

void note_aftertouch_event(u8 v) {
    aftertouch_send(USBSTANDALONE, MD_CH_AT | note_channel(), v);
}

void note_poly_event(u8 p, u8 v) {
    s8 n = note_press(p / 10, p % 10, v, -1);
    if (n >= 0) send_midi(USBSTANDALONE, MD_POLY_AT | note_channel(), n, v);
}
