#include "sysex/messages.h"

const u8 syx_device_inquiry[syx_device_inquiry_length] = {0xF0, 0x7E, 0x7F, 0x06, 0x01, 0xF7};
const u8 syx_device_inquiry_response[syx_device_inquiry_response_length] = {0xF0, 0x7E,
                                                                      0x00,                                                  // Device ID
                                                                      0x06, 0x02, 0x00, 0x20, 0x29, 0x51, 0x00, 0x00, 0x00,  // Constant
                                                                      0x00, 0x63, 0x66, 0x77,                                // Firmware rev. (4 bytes) - CFW
                                                                      0xF7};

const u8 syx_challenge[syx_challenge_length] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x10, 0x40}; // Also Live quit message!
u8 syx_challenge_response[syx_challenge_response_length] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x10, 0x40, 0xFF, 0xFF, 0xF7};

const u8 syx_mode_selection[syx_mode_selection_length] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x10, 0x21};
u8 syx_mode_selection_response[syx_mode_selection_response_length] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x10, 0x2D, 0xFF, 0xF7};

const u8 syx_live_layout_selection[syx_live_layout_selection_length] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x10, 0x22};
u8 syx_live_layout_selection_response[syx_live_layout_selection_response_length] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x10, 0x2E, 0xFF, 0xF7};

const u8 syx_standalone_layout_selection[syx_standalone_layout_selection_length] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x10, 0x2C};
u8 syx_standalone_layout_selection_response[syx_standalone_layout_selection_response_length] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x10, 0x2F, 0xFF, 0xF7};

const u8 syx_led_single[syx_led_single_length] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x10, 0x0A};
const u8 syx_led_column[syx_led_column_length] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x10, 0x0C};
const u8 syx_led_row[syx_led_row_length] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x10, 0x0D};
const u8 syx_led_all[syx_led_all_length] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x10, 0x0E};

const u8 syx_led_flash[syx_led_flash_length] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x10, 0x23};
const u8 syx_led_pulse[syx_led_pulse_length] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x10, 0x28};

const u8 syx_led_rgb[syx_led_rgb_length] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x10, 0x0B};
const u8 syx_led_grid[syx_led_grid_length] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x10, 0x0F};

const u8 syx_text[syx_text_length] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x10, 0x14};
const u8 syx_text_response[syx_text_response_length] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x10, 0x15, 0xF7};

const u8 syx_palette_start[syx_palette_start_length] = {0xF0, 0x52, 0x45, 0x54, 0x49, 0x4E, 0x41, 0x7B, 0xF7};
const u8 syx_palette_write[syx_palette_write_length] = {0xF0, 0x52, 0x45, 0x54, 0x49, 0x4E, 0x41, 0x3D};
u8 syx_palette_export[syx_palette_export_length] = {0xF0, 0x52, 0x45, 0x54, 0x49, 0x4E, 0x41, 0x23, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7};
const u8 syx_palette_end[syx_palette_end_length] = {0xF0, 0x52, 0x45, 0x54, 0x49, 0x4E, 0x41, 0x7D, 0xF7};

// Not const since we need a pointer to it
u8 syx_palette_text[syx_palette_text_length] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x10, 0x14, 0x03, 0x01, 0x04, 0x44, 0x6f, 0x77, 0x6E, 0x6C, 0x6F, 0x61, 0x64, 0x69, 0x6E, 0x67, 0x20, 0x70, 0x61, 0x6C, 0x65, 0x74, 0x74, 0x65, 0x2E, 0x2E, 0x2E, 0xF7};

const u8 syx_fader[syx_fader_length] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x10, 0x2B};