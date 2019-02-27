#include QMK_KEYBOARD_H
#include "debug.h"
#include "led.h"
#include "action_layer.h"
#include "action_util.h"
#include "eeconfig.h"
#include "version.h"

#ifdef SUBPROJECT_infinity
#include "ergodox_infinity.h"
#include "infinity.h"
#endif

#define TODO KC_NO

#define F_BROWSER M(BROWSER)

#define BASE 0
#define QWERTY 1
#define DVORAK 3 
#define STARCRAFT 4 
#define NUMPAD_L 5 // media keys
#define NUMPAD_R 6 // media keys
#define MOTION 7
#define ADMIN 8
#define QUOTE 9

//#define V_SMC LT(MOTION, KC_SCLN)
/* #define V_SMC MT(MOD_RSFT, KC_SCLN) */
#define V_SMC KC_SCLN
/* #define V_A MT(MOD_LSFT, KC_A) */
#define V_A KC_A
/* #define V_U KC_U */
#define V_U LT(MOTION, KC_U)
/* #define V_E KC_U */
#define V_E LT(NUMPAD_R, KC_E)
#define V_DOT LT(MOTION, KC_DOT)
/* #define V_X LT(NUMPAD_R, KC_X) */
#define V_X KC_X
#define V_COMM LT(NUMPAD_R, KC_COMM)
/* #define V_COMM KC_COMM */
#define V_ESC MT(MOD_LGUI, KC_ESC)
/* #define V_CTRL MT(MOD_LCTL, OSL(NUMPAD)) */
#define V_CTRL KC_LCTL
// Shift on both last bottom row
// Left hand gets symbols when ' is held
#define V_QUOT MT(MOD_MEH, KC_QUOT)
/* #define V_QUOT KC_QUOT */
#define V_MINS LT(QUOTE, KC_MINS)
#define V_EQL MT(MOD_HYPR, KC_ESC)
// Left, right FNx becomes LGUI
// Right hand LGUI equivalent becomes setting symbol layer
// Left current CAPS becomes NUMPAD
#define V_LSFT OSM(MOD_LSFT)
#define V_RSFT MT(MOD_LSFT, KC_SPC)
#define V_MC MT((MOD_LCTL | MOD_LALT), KC_ESC)
#define V_CTL OSM(MOD_LCTL)
#define V_ALT OSM(MOD_LALT)
#define V_SFT OSM(MOD_LSFT)
#define V_TAB MT(MOD_LGUI, KC_TAB)
#define V_BSLS MT(MOD_LGUI, KC_BSLS)

#define Adiae UC(0x00e4)
#define Aring UC(0x00e5)


enum custom_keycodes {
  PLACE_HOLDER = 0, // can always be here
  FLSH,
  VRSN,
  KDBG,
  BROWSER,
  TSKSWCH,
  EDITOR,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = KEYMAP( 
        // left hand
        KC_EQL,  KC_1,    KC_2,    KC_3,      KC_4,       KC_5,     MO(ADMIN),
        KC_TAB,  KC_Q,    KC_W,    KC_E,      KC_R,       KC_T,     KC_DEL,
        KC_CAPS, KC_A,    KC_S,    KC_D,      KC_F,       KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,      KC_V,       KC_B,     TODO,
        KC_LGUI, KC_GRV,  KC_LGUI, KC_LALT, KC_LCTL,
                                                        MO(MOTION),KC_LGUI,
                                                                   TODO,
                                              KC_LALT,     V_MC,    TODO,
        // right hand
        MO(ADMIN),    KC_6,    KC_7,     KC_8,      KC_9,          KC_0,      KC_MINS,
        KC_BSPC,      KC_Y,    KC_U,     KC_I,      KC_O,          KC_P,      KC_BSLS,
                      KC_H,    KC_J,     KC_K,      KC_L,          KC_SCLN,   KC_QUOT,
        V_SFT,        KC_N,    KC_M,     KC_COMM,   KC_DOT,        KC_SLSH,   KC_RSFT,
                      KC_RCTL, KC_RALT,  KC_RGUI,   OSM(KC_RALT),  KC_RGUI,
        KC_LGUI,      TODO,
        TODO,
        KC_DEL,       KC_ENT, KC_SPC
    ),
[MOTION] = KEYMAP(
       // left hand
       TG(DVORAK),KC_F1,    KC_F2,       KC_F3,     KC_F4,      KC_F5,          KC_MUTE,
       TG(STARCRAFT),KC_NO,    KC_NO,       KC_TRNS,   KC_NO,    KC_NO,          KC_NO,
       KC_TRNS,   KC_NO,    KC_NO,       KC_NO,     KC_TRNS,    KC_NO,
       KC_TRNS,   KC_NO,    KC_NO,       KC_NO,     KC_NO,      KC_NO,          KC_VOLD,
       KC_TRNS,   KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS,
                                                                KC_TRNS,        KC_MNXT,
                                                                                KC_TRNS,
                                                    KC_TRNS,    KC_TRNS,         KC_TRNS,
       // right hand
       KC_APP,    KC_F6,     KC_F7,      KC_F8,     KC_F9,      KC_F10,     KC_F11,
       KC_TRNS,   KC_NO,     LCTL(KC_LEFT),KC_UP,   LCTL(KC_RIGHT),KC_PSCR,    KC_F12,
                  KC_LEFT,   KC_LEFT,    KC_DOWN,     KC_RGHT,    KC_NO,      KC_NO,
       KC_TRNS,   KC_CALC,   KC_WSCH,    KC_MAIL,   KC_TRNS,    KC_TRNS,    KC_TRNS,
                             KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_TRNS,   KC_TRNS,
       KC_TRNS,
       KC_TRNS,   KC_TRNS,   KC_TRNS
       ),
[NUMPAD_L] = KEYMAP(
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  M(FLSH),
  KC_TRNS,  KC_EXLM,  KC_AT,    KC_LCBR,  KC_RCBR,  KC_PIPE,  KC_NO,
            KC_TRNS,  KC_HASH,  KC_DLR,   KC_LPRN,  KC_RPRN,  KC_GRV,
  KC_TRNS,  KC_PERC,  KC_CIRC,  KC_LBRC,  KC_RBRC,  KC_TILD,  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,
  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,
       // right hand
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,
  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS
                    ),
[NUMPAD_R] = KEYMAP(
                    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  M(FLSH),
                    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                              KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                    KC_TRNS,  KC_TRNS,
                    KC_TRNS,
                    KC_TRNS,  KC_TRNS,  KC_TRNS,
                    // right hand
                    KC_TRNS,  KC_TRNS,  KC_NLCK,  KC_EQL,  KC_PSLS,  KC_PAST,  KC_NO,
                    KC_NO,    KC_BSLS,  KC_7,     KC_8,    KC_9,     KC_PMNS,  KC_DQT,
                              KC_ASTR,  KC_4,     KC_5,     KC_6,    KC_PPLS,  KC_QUOT,
                    KC_NO,    KC_AMPR,  KC_1,     KC_2,    KC_3,     KC_PSLS,  KC_PSLS,
                    KC_TRNS,  KC_0,     KC_0,     KC_0,    KC_TRNS,
                    KC_TRNS,  KC_TRNS,
                    KC_TRNS,
                    KC_TRNS,  KC_TRNS,  KC_0
                    ),
[DVORAK] = KEYMAP(
       // left hand
       KC_EQL,    KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS, KC_TRNS,
       KC_TRNS,   V_QUOT,   V_COMM,    V_DOT,       KC_P,       KC_Y,    KC_TRNS,
       KC_TRNS,   KC_A,     KC_O,      KC_E,        KC_U,       KC_I,
       KC_TRNS,   KC_SCLN,  KC_Q,      KC_J,        KC_K,       V_X,     KC_TRNS,
       KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,
                                                                KC_TRNS, KC_TRNS,
                                                                         KC_TRNS,
                                                    KC_TRNS,    KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS,   KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS,
       KC_TRNS,   KC_F,     KC_G,        KC_C,      KC_R,       KC_L,    V_BSLS,
                  KC_D,     KC_H,        KC_T,      KC_N,       KC_S,    KC_SLSH,
       KC_TRNS,   KC_B,     KC_M,        KC_W,      KC_V,       KC_Z,    KC_TRNS,
                            KC_TRNS,     KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS,
       KC_TRNS,   KC_TRNS,
       KC_TRNS,
       KC_TRNS,   KC_TRNS,  KC_TRNS
       ),
[STARCRAFT] = KEYMAP( 
       // left hand
       KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS, KC_TRNS,
       KC_TRNS,   KC_QUOT,  KC_COMM,   KC_DOT,      KC_TRNS,    KC_TRNS, KC_TRNS,
       KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS,
       KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS, KC_TRNS,
       KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,
                                                                KC_TRNS, KC_TRNS,
                                                                         KC_TRNS,
                                                    KC_TRNS,    KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS,   KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS,
       KC_TRNS,   KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS,
                  KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS,
       KC_TRNS,   KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS,
                            KC_TRNS,     KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS,
       KC_TRNS,   KC_TRNS,
       KC_TRNS,
       KC_TRNS,   KC_TRNS,  KC_TRNS
    ),
[QUOTE] = KEYMAP(
       // left hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_TILD, KC_NO,
       KC_TRNS, KC_CIRC, KC_HASH, KC_LPRN, KC_RPRN, KC_DLR,
       KC_TRNS, KC_PERC, KC_DLR,  KC_LBRC, KC_RBRC, KC_GRV, KC_TRNS,
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                    KC_TRNS, KC_TRNS,
                                                             KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       FLSH,    KC_TRNS,     KC_TRNS,      KC_TRNS,     KC_TRNS,      KC_TRNS,     KC_TRNS,
       KC_TRNS,   KC_TRNS,     KC_TRNS,      KC_TRNS,    KC_TRNS,      KC_TRNS,    KC_TRNS,
                  KC_TRNS,   KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,      KC_TRNS,
       KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,
                             KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_TRNS,    KC_TRNS,
       KC_TRNS,
       KC_TRNS,   KC_TRNS,   KC_TRNS
       ),
[ADMIN] = KEYMAP(
       // left hand
       KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS, M(FLSH),
       KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS, RGB_VAI,
       KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS,
       KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS, RGB_VAD,
       KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,
                                                                KC_TRNS, KC_TRNS,
                                                                         KC_TRNS,
                                                    KC_TRNS,    KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS,   RGB_TOG,  RGB_MOD,     KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS,
       RGB_HUI,   KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS,
                  KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS,
       RGB_HUD,   KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS,
                            KC_TRNS,     KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS,
       KC_TRNS,   KC_TRNS,
       KC_TRNS,
       KC_TRNS,   KC_TRNS,  KC_TRNS
       ),
};
const uint16_t PROGMEM fn_actions[] = {
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    case FLSH:
      if (record->event.pressed) { // For resetting EEPROM
        ergodox_right_led_3_on();
        ergodox_right_led_2_on();
        ergodox_right_led_1_on();
        reset_keyboard();
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
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    uint8_t layer = biton32(layer_state);
    uint8_t led_3 = (layer & (1 << 1)) > 0;
    uint8_t led_2 = (layer & (1 << 2)) > 0;
    uint8_t led_1 = (layer & (1 << 3)) > 0;
    if (led_3) ergodox_right_led_3_on();
    if (led_2) ergodox_right_led_2_on();
    if (led_1) ergodox_right_led_1_on();
};


bool process_record_user (uint16_t keycode, keyrecord_t *record) {
  if (keycode == KC_ESC && record->event.pressed) {
    bool queue = true;

    if ((get_oneshot_mods ()) && !has_oneshot_mods_timed_out ()) {
      clear_oneshot_mods ();
      queue = false;
    }
    return queue;
  }
  return true;
}

/* 
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |      |             |      |      |                  |             |      |      |      |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------|                  |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
/* [DVORAK] = KEYMAP( */
/*        // left hand */
/*        KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS, KC_TRNS, */
/*        KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS, KC_TRNS, */
/*        KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS, */
/*        KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS, KC_TRNS, */
/*        KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS, */
/*                                                                 KC_TRNS, KC_TRNS, */
/*                                                                          KC_TRNS, */
/*                                                     KC_TRNS,    KC_TRNS, KC_TRNS, */
/*        // right hand */
/*        KC_TRNS,   KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS, */
/*        KC_TRNS,   KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS, */
/*                   KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS, */
/*        KC_TRNS,   KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS, */
/*                             KC_TRNS,     KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS, */
/*        KC_TRNS,   KC_TRNS, */
/*        KC_TRNS, */
/*        KC_TRNS,   KC_TRNS,  KC_TRNS */
/*        ), */
