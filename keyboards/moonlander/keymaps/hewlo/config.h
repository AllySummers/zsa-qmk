#pragma once

#define ORYX_CONFIGURATOR
#define FIRMWARE_VERSION u8"default/latest"
#define RAW_USAGE_PAGE 0xFF60
#define RAW_USAGE_ID 0x61
#define MOONLANDER_USER_LEDS

#define LETTER_RGB 0x00, 0xC2, 0xFF // #00c2ff rgb(0,194,255)
#define NUMBER_RGB 0xB0, 0x0C, 0xDF // #b00cdf rgb(176,12,223)
#define SYMBOL_RGB 0xFF, 0x57, 0x57 // #ff5757 rgb(255,87,87)
#define SHIFT_SYMBOL_RGB 0xFF, 0x00, 0x00 // #ff0000 rgb(255,0,0)
#define MODIFIERS_RGB 0xEA, 0xFF, 0x99 // #eaff99 rgb(234,255,153)
#define FUNCTION_KEY_RGB 0xFF, 0xA2, 0x29 // #ffa229 rgb(255,162,41)
#define LAYER_KEYS_RGB 0x00, 0x08, 0xFF // #0008ff rgb(0,8,255)
#define SPC_DEL_ENTR_RGB 0x00, 0xFF, 0x2A // #00ff2a rgb(0,255,42)
#define NAV_KEYS_RGB 0xFF, 0xFB, 0x00 // #fffb00 rgb(255,251,0)
#define OTHER_KEY_RGB 0x00, 0xFF, 0xAA // #00ffaa rgb(0,255,170)
