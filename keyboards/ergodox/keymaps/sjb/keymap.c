#include "ergodox.h"
#include "debug.h"
#include "led.h"
#include "action_layer.h"
#include "action_util.h"
#include "eeconfig.h"
#include "version.h"

#ifdef SUBPROJECT_infinity
#include "infinity.h"
#endif

#define DEFAULT_EDITOR "emacs"

// unsupported hid comsumer id
#define AL_INTERNET_BROWSER 0x0196
#define AL_EDITOR 0x185

#define LCA(kc) (kc | QK_LCTL | QK_LALT)

#define LCA_T(kc) MT((MOD_LCTL | MOD_LALT), kc)
#define LSS_T(kc) MT((MOD_LSFT | MOD_LGUI), kc)  // Shift-Super
#define LCS_T(kc) MT((MOD_LCTL | MOD_LGUI), kc)  // Ctrl-Super

#define F_TERM  LCA(KC_T)
#define F_TGAPP LGUI(KC_TAB)      // switch to last app
#define F_TGWIN LALT(KC_F6)       // switch to last window
#define F_FSMOD KC_F11            // Toggle fullscreen mode
#define F_MAXST LALT(KC_F10)     // Toggle maximazation state

//#define F_SYMB OSL(SYMB)
//#define F_LSFT OSM(MOD_LSFT)
//#define F_LCTL OSM(MOD_LCTL)
//#define F_LALT OSM(MOD_LALT)
//#define F_ENT LCS_T(KC_ENT)
//#define F_SPC LALT_T(KC_SPC)
//#define F_BSPC LSS_T(KC_BSPC)
//#define F_DELT LSS_T(KC_DELT)

#define F_SYMB KC_FN1
#define F_NUMPAD KC_FN2
#define F_LSFT KC_FN3
#define F_LCTL KC_FN4
#define F_LALT KC_FN5
#define F_ENT KC_FN6
#define F_SPC KC_FN7
#define F_BSPC KC_FN8
#define F_DELT KC_FN9
#define F_RALT KC_RALT
#define F_RCTL KC_RCTL

#define TAP_ONCE_CONSUMER_HID_CODE(code) \
  host_consumer_send(code); \
  host_consumer_send(0)

#define TAP_ONCE(code) \
  register_code(code); \
  unregister_code(code)

enum keymaps_layers {
  BASE = 0, // default layer
  SYMB,     // symbols
  NUMPAD,   // numpad 
};

enum custom_keycodes {
  PLACE_HOLDER = 0, // can always be here
  EPRM,
  VRSN,
  BROWSER,
  TSKSWCH,
  EDITOR,
  SWIN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ESC  |   1  |   2  |   3  |   4  |   5  | BRWS |           | MYCM |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   Q  |   W  |   E  |   R  |   T  |  [   |           |  ]   |   Y  |   U  |   I  |   O  |   P  |   =    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCTRL  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|  \   |           |  `   |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | ~L1  |  APP | LEFT | MAXST| TGAPP|                                       | TGWIN| FSMOD| RGHT | SWCH | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | HOME | END  |       | PGUP | PGDN |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | LALT |       | RALT |        |      |
 *                                 | LCTRL| BKSP |------|       |------|  ENTER |  [ ] |
 *                                 |      |      | LGUI |       | RCTRL|        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_ESC,   KC_1,          KC_2,    KC_3,      KC_4,       KC_5,    M(BROWSER),
        KC_TAB,   KC_Q,          KC_W,    KC_E,      KC_R,       KC_T,    KC_LBRC,
        F_LCTL,   KC_A,          KC_S,    KC_D,      KC_F,       KC_G,
        F_LSFT,   KC_Z,          KC_X,    KC_C,      KC_V,       KC_B,    KC_BSLASH,
                  F_SYMB,        KC_APP,  KC_LEFT,   F_MAXST,    F_TGAPP,
                                                                 KC_HOME, KC_END,
                                                                          F_LALT,
                                                     F_LCTL,     F_BSPC,  KC_LGUI,
        // right hand
        KC_MYCM,  KC_6,          KC_7,    KC_8,      KC_9,       KC_0,    KC_MINS,
        KC_RBRC,  KC_Y,          KC_U,    KC_I,      KC_O,       KC_P,    KC_EQL,
                  KC_H,          KC_J,    KC_K,      KC_L,       KC_SCLN, KC_QUOT,
        KC_GRAVE, KC_N,          KC_M,    KC_COMM,   KC_DOT,     KC_SLSH, KC_RSFT,
                  F_TGWIN,       F_FSMOD, KC_RGHT,   M(TSKSWCH), F_SYMB,
        KC_PGUP,  KC_PGDN,
        F_RALT,
        F_RCTL,   F_ENT, F_SPC
    ),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |  Up  |      |      |      |      |           |      |      |      | INS  |      | PRSC |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | CAPSLCK | Left | Down | RGHT |      |      |------|           |------| Calc | SRCH | Mail | Term | Edit |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       | LCK2 |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | VOL+ | VOL- |       | Pwr  | Slp  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      | Del  | MUTE |       | MSEL |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = KEYMAP(
       // left hand
       KC_TRNS,   KC_F1,    KC_F2,       KC_F3,     KC_F4,      KC_F5,          KC_TRNS,
       KC_TRNS,   KC_TRNS,  KC_UP,       KC_TRNS,   KC_TRNS,    KC_TRNS,        KC_TRNS,
       KC_CAPS,   KC_LEFT,  KC_DOWN,     KC_RGHT,   KC_TRNS,    KC_TRNS,
       KC_TRNS,   KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS,    KC_TRNS,        KC_TRNS,
                  KC_TRNS,  F_NUMPAD,  KC_TRNS,   KC_TRNS,    KC_TRNS,
                                                                KC_VOLU,        KC_VOLD,
                                                                                KC_MUTE,
                                                    KC_TRNS,    F_DELT,         KC_TRNS,
       // right hand
       KC_TRNS,   KC_F6,     KC_F7,      KC_F8,     KC_F9,      KC_F10,         KC_F11,
       KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_INS,    KC_TRNS,    KC_PSCR,        KC_F12,
                  KC_CALC,   KC_WSCH,    KC_MAIL,   F_TERM,     M(EDITOR),      KC_TRNS,
       KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,        KC_TRNS,
                  KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,
       KC_PWR,    KC_SLEP,
       KC_SELECT,
       KC_TRNS,   KC_TRNS,   KC_TRNS
       ),
/* Keymap 2: Numpad and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      | NMLK |  P/  |  P*  |  P-  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | Lclk | MsUp | Rclk |      |      |      |           |      |      |  P7  |  P8  |  P9  |  P+  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |MsLeft|MsDown|MsRght|      |      |------|           |------|      |  P4  |  P5  |  P6  |  P+  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |  P1  |  P2  |  P3  | PEnt |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      | LCK2 |      |      |      |                                       |      |      |  P.  | PEnt |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |  P0  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[NUMPAD] = KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, M(EPRM),
       KC_TRNS, KC_BTN1, KC_MS_U,     KC_BTN2, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_MS_L, KC_MS_D,     KC_MS_R, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_TRNS, TG(NUMPAD),  KC_TRNS, KC_TRNS, KC_TRNS,
                                                        KC_TRNS, KC_TRNS,
                                                                 KC_TRNS,
                                               KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       M(EPRM), KC_TRNS, KC_NLCK,     KC_PSLS, KC_PAST, KC_PMNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_P7,       KC_P8,   KC_P9,   KC_PPLS, KC_TRNS,
                KC_TRNS, KC_P4,       KC_P5,   KC_P6,   KC_PPLS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_P1,       KC_P2,   KC_P3,   KC_PENT, KC_TRNS,
                KC_TRNS, KC_TRNS,     KC_PDOT, KC_PENT, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_P0
),
};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_ONESHOT(SYMB),
  [2] = ACTION_LAYER_TAP_TOGGLE(NUMPAD),
  [3] = ACTION_MODS_ONESHOT(MOD_LSFT),
  [4] = ACTION_MODS_ONESHOT(MOD_LCTL),
  [5] = ACTION_MODS_ONESHOT(MOD_LALT),
  [6] = ACTION_MODS_TAP_KEY(MOD_LGUI | MOD_LCTL, KC_ENT),
  [7] = ACTION_MODS_TAP_KEY(MOD_LALT, KC_SPC),
  [8] = ACTION_MODS_TAP_KEY(MOD_LGUI | MOD_LSFT, KC_BSPC),
  [9] = ACTION_MODS_TAP_KEY(MOD_LGUI | MOD_LSFT, KC_DELT)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      break;
    case EPRM:
      if (record->event.pressed) { // For resetting EEPROM
        eeconfig_init();
      }
      break;
    case BROWSER:
      if (record->event.pressed) { // send AL_INTERNET_BROWSER to OS
        TAP_ONCE_CONSUMER_HID_CODE(AL_INTERNET_BROWSER);
      }
      break;
    case TSKSWCH: 
      if (record->event.pressed) { 
        TAP_ONCE(KC_LGUI);
        wait_ms(250); 
        register_code(KC_LALT);
      } else {
        unregister_code(KC_LALT);
      }
      break;
    case EDITOR:
      if (record->event.pressed) {
        TAP_ONCE(KC_LGUI);
        wait_ms(250); 
        SEND_STRING(DEFAULT_EDITOR "\n");
      }
      break;
  }
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            break;
    }
};
