#include "modes/special/scale.h"

const u8 scale_points[33] = {0, 4, 8, 12, 19, 26, 31, 35, 42, 48, 54, 58, 64, 71, 78, 84, 88, 93, 97, 103, 109, 115, 121, 126, 137, 143, 149, 155, 161, 167, 173, 179, 186};
const u8 scale_data[186] = {
    1, 5, 7, 10, // In Sen
    2, 5, 7, 9, // Yo scale
    1, 5, 6, 10, // Iwato
    2, 3, 5, 6, 8, 9, 11, // Whole Half
    2, 3, 5, 7, 8, 10, 11, // BeBop Minor
    2, 3, 4, 7, 9, // Major blues
    2, 3, 7, 9, // Kumoi
    2, 4, 5, 7, 8, 9, 11, // BeBop Major
    2, 3, 5, 7, 9, 11, // Melodic Minor (ascending)
    2, 3, 5, 7, 8, 11, // Harmonic Minor
    2, 4, 7, 9, // Major Pentatonic
    1, 4, 5, 7, 8, 10, // Phyrigian Dominant
    1, 3, 4, 6, 7, 9, 10, // Half-Whole Diminished
    2, 4, 5, 7, 9, 10, 11, // Mixolydian BeBop
    1, 3, 4, 6, 8, 10, // Super Locrian
    2, 3, 7, 8, // Hirajoshi
    3, 5, 6, 7, 10, // Blues
    3, 5, 7, 10, // Minor Pentatonic
    2, 3, 6, 7, 8, 11, // Hungarian Minor
    2, 3, 6, 7, 9, 10, // Ukrainian Dorian
    1, 4, 6, 7, 9, 11, // Marva
    1, 3, 6, 7, 8, 11, // Todi
    2, 4, 6, 8, 10, // Whole Tone
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, // Chromatic
    2, 4, 5, 7, 9, 11, // Major Ionian
    2, 3, 5, 7, 9, 10, // Dorian
    1, 3, 5, 7, 8, 10, // Phrygian
    2, 4, 6, 7, 9, 11, // Lydian
    2, 4, 5, 7, 9, 10, // Mixolydian
    2, 3, 5, 7, 8, 10, // Minor Aeolian
    1, 3, 5, 6, 8, 10, // Locrian
    2, 3, 4, 5, 7, 9, 10 // BeBop Dorian
};
const u8 scale_keys[12] = {51, 62, 52, 63, 53, 54, 65, 55, 66, 56, 67, 57};

u8 scales(u8 s, u8 i) {
    if (i == 0) return 0;
    return scale_data[scale_points[s] + i - 1];
}

u8 scales_length(u8 s) {
    return scale_points[s + 1] - scale_points[s] + 1; 
}

#define scale_setup_color_enabled_r 20
#define scale_setup_color_enabled_g 63
#define scale_setup_color_enabled_b 0

#define scale_setup_color_translate_r 63
#define scale_setup_color_translate_g 63
#define scale_setup_color_translate_b 0

#define scale_setup_color_segment_r 63
#define scale_setup_color_segment_g 20
#define scale_setup_color_segment_b 0

#define scale_setup_color_notes_r 0
#define scale_setup_color_notes_g 63
#define scale_setup_color_notes_b 63

#define scale_setup_color_root_r 0
#define scale_setup_color_root_g 0
#define scale_setup_color_root_b 63

#define scale_setup_color_scale_r 63 >> 4
#define scale_setup_color_scale_g 0
#define scale_setup_color_scale_b 63 >> 4

#define scale_setup_color_selected_r 20
#define scale_setup_color_selected_g 0
#define scale_setup_color_selected_b 63

void scale_setup_init() {
    switch (mode_default) {
        case mode_ableton:
            rgb_led(99, mode_ableton_r, mode_ableton_g, mode_ableton_b); // Note mode LED
            break;

        case mode_note:
            rgb_led(99, mode_note_r, mode_note_g, mode_note_b); // Note mode LED
            break;

        case mode_chord:
            rgb_led(99, mode_chord_r, mode_chord_g, mode_chord_b); // Chord mode LED
            break;
    }

    if (settings.scale.enabled) {
        rgb_led(88, scale_setup_color_enabled_r, scale_setup_color_enabled_g, scale_setup_color_enabled_b); // Scale mode enabled
    } else {
        rgb_led(88, scale_setup_color_enabled_r / 5, scale_setup_color_enabled_g / 5, scale_setup_color_enabled_b / 5); // Scale mode disabled
    }

    if (settings.scale.note_translate) {
        rgb_led(58, scale_setup_color_translate_r, scale_setup_color_translate_g, scale_setup_color_translate_b); // Translate mode enabled
    } else {
        rgb_led(58, scale_setup_color_translate_r / 5, scale_setup_color_translate_g / 5, scale_setup_color_translate_b / 5); // Translate mode disabled
    }

    for (u8 i = 81; i < 88; i++) {
        rgb_led(i, scale_setup_color_segment_r / 3, scale_setup_color_segment_g / 3, scale_setup_color_segment_b / 3); // Segment length options
    }

    if (settings.scale.segment < 8)
        rgb_led(88 - settings.scale.segment, scale_setup_color_segment_r, scale_setup_color_segment_g, scale_setup_color_segment_b); // Selected segment

    for (u8 i = 0; i < 12; i++) {
        rgb_led(scale_keys[i], scale_setup_color_notes_r >> 3, scale_setup_color_notes_g >> 3, scale_setup_color_notes_b >> 3); // Root note selector and scale preview
    }
    for (u8 i = 1; i < scales_length(settings.scale.selected); i++) {
        rgb_led(scale_keys[modulo(scales(settings.scale.selected, i) + settings.scale.root, 12)], scale_setup_color_notes_r, scale_setup_color_notes_g, scale_setup_color_notes_b); // Notes in current scale
    }
    rgb_led(scale_keys[settings.scale.root], scale_setup_color_root_r, scale_setup_color_root_g, scale_setup_color_root_b); // Scale root note

    for (u8 x = 1; x <= 4; x++) {
        for (u8 y = 1; y <= 8; y++) {
            u8 p = x * 10 + y;
            u8 scale = (x - 1) * 8 + (y - 1);
            // Select scale
            switch (scale) {
                case 25: // Ionian
                    rgb_led(p, 0x37 >> 4, 0x00 >> 4, 0x09 >> 4);
                    break;
                case 26: // Dorian
                    rgb_led(p, 0x2b >> 4, 0x18 >> 4, 0x00 >> 4);
                    break;
                case 27: // Phrygian
                    rgb_led(p, 0x1b >> 4, 0x20 >> 4, 0x00 >> 4);
                    break;
                case 28: // Lydian
                    rgb_led(p, 0x00 >> 4, 0x23 >> 4, 0x10 >> 4);
                    break;
                case 29: // Mixolydian
                    rgb_led(p, 0x00 >> 4, 0x21 >> 4, 0x25 >> 4);
                    break;
                case 30: // Aeolian
                    rgb_led(p, 0x11 >> 4, 0x17 >> 4, 0x3f >> 4);
                    break;
                case 31: // Locrian
                    rgb_led(p, 0x2c >> 4, 0x00 >> 4, 0x38 >> 4);
                    break;
                default:
                    rgb_led(p, scale_setup_color_scale_r, scale_setup_color_scale_g, scale_setup_color_scale_b); // Select scale
            }
        }
    }

    u8 p = ((settings.scale.selected >> 3) + 1) * 10 + (settings.scale.selected % 8) + 1;
    // Select scale
    switch (settings.scale.selected) {
        case 25: // Ionian
            rgb_led(p, 0x37, 0x00, 0x09);
            break;
        case 26: // Dorian
            rgb_led(p, 0x2b, 0x18, 0x00);
            break;
        case 27: // Phrygian
            rgb_led(p, 0x1b, 0x20, 0x00);
            break;
        case 28: // Lydian
            rgb_led(p, 0x00, 0x23, 0x10);
            break;
        case 29: // Mixolydian
            rgb_led(p, 0x00, 0x21, 0x25);
            break;
        case 30: // Aeolian
            rgb_led(p, 0x11, 0x17, 0x3f);
            break;
        case 31: // Locrian
            rgb_led(p, 0x2c, 0x00, 0x38);
            break;
        default:
            rgb_led(p, scale_setup_color_selected_r, scale_setup_color_selected_g, scale_setup_color_selected_b); // Selected scale
    }
}

void scale_setup_timer_event() {}

void scale_setup_surface_event(u8 p, u8 v, u8 x, u8 y) {
    if (p == 0) { // Enter Setup mode
        if (v != 0) mode_update(mode_setup);

    } else if (p == 96) {
        if (v == 0) {
            novation_led(96, 39);
        } else {
            mode_update(mode_default); // Enter Note/Live mode
        }

    } else if (p == 80) { // Shift button
        send_midi(2 - mode_default, 0xB0, p, v);
        note_shift = v;
        chord_shift = v;

    } else if (v != 0) {
        if (p == 88) { // Enable or disable Scale mode
            settings.scale.enabled = 1 - settings.scale.enabled;
            dirty = 1;
            scale_setup_init();  // instead of mode_refresh skips clear LED, not necessary here (top note key)

        } else if (p == 58) { // Enable or disable translate mode
            settings.scale.note_translate = 1 - settings.scale.note_translate;
            dirty = 1;
            scale_setup_init();

        } else if (81 <= p && p <= 87) { // Select segment length
            u8 t = 88 - p;
            settings.scale.segment = t == settings.scale.segment? 8 : t;
            dirty = 1;
            scale_setup_init();

        } else if (1 <= x && x <= 4 && 1 <= y && y <= 8) { // Select scale
            settings.scale.selected = (x - 1) * 8 + (y - 1);

            dirty = 1;
            scale_setup_init();

        } else {
            u8 i = 0;
            do {
                if (scale_keys[i] == p) break;
            } while (++i < 12);

            if (i < 12) {
                if (i != settings.scale.root) {
                    note_octave = 5;
                }

                settings.scale.root = i;
                dirty = 1;
                scale_setup_init();
            }
        }
    }
}

void scale_setup_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v) {}

void scale_setup_aftertouch_event(u8 v) {}

void scale_setup_poly_event(u8 p, u8 v) {}
