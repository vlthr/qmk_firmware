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

#define TODO KC_NO

#define F_BROWSER M(BROWSER)

#define BASE 0
#define DVORAK 1 // symbols
#define NUMPAD_L 2 // media keys
#define NUMPAD_R 3 // media keys
#define MOTION 4
#define QUOTE 5
#define LANG 6

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
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   Q  |   W  |   E  |   R  |   T  |      |           |   _  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | = NUMPD|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |'       |
 * |--------+------+------+------+------+------| ~L2  |           |   -  |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LGUI | GRV  | NUMP | LCTL |MOTION|                                       | ALtGr| LCTL |      | SYM  | LGUI   |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | LALT | LGUI |       | PGUP | LALT |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 | SHFT | BKSP |------|       |------|  ENTER | [ ]  |
 *                                 |      |      | DEL  |       | Esc  |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_EQL,  KC_1,    KC_2,    KC_3,      KC_4,       KC_5,     TODO,
        V_TAB,  KC_Q,    KC_W,    KC_E,      KC_R,       KC_T,     KC_DEL,
         V_EQL,  V_A,     KC_S,    KC_D,      KC_F,       KC_G,
         KC_NO,  KC_Z,    KC_X,    KC_C,      KC_V,       KC_B,     V_SFT,
        KC_LGUI, KC_GRV,  KC_LGUI,V_ALT,V_CTL,
                                                        MO(MOTION),KC_LGUI,
                                                                   TODO,
                                              V_LSFT,     V_MC,    TODO,
        // right hand
        TODO,         KC_6,    KC_7,     KC_8,      KC_9,      KC_0,     KC_MINS,
        KC_BSPC,      KC_Y,    KC_U,     KC_I,      KC_O,      KC_P,     V_BSLS,
                      KC_H,    KC_J,     KC_K,      KC_L,      V_SMC,    KC_QUOT,
        V_SFT,        KC_N,    KC_M,     V_COMM,    KC_DOT,    KC_SLSH,  MO(QUOTE),
                      V_CTL,  V_ALT,     KC_RGUI,   OSM(KC_RALT),  KC_RGUI,
        KC_LGUI,      TODO,
        TODO,
        KC_DEL,       KC_ENT, KC_SPC
    ),
/* Keymap 1: Motion Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  | Mute |           | App  |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      | Lclk | MsUp | Rclk |      | Vol+ |           |      |      |      | INS  |      | PRSC |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | CAPSLCK |      |MsLeft|MsDown|MsRght|      |------|           |------| Left | Down |  Up  | Rght |      |        |
 * |---------+------+------+------+------+------| Vol- |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      | Calc | SRCH | Mail | WWW  | Edit |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | MPLY | MNXT |       | Pwr  | Slp  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      | Del  |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Motion
[MOTION] = KEYMAP(
       // left hand
       TG(DVORAK),KC_F1,    KC_F2,       KC_F3,     KC_F4,      KC_F5,          KC_MUTE,
       KC_TRNS,   KC_NO,    KC_NO,       KC_TRNS,   KC_NO,    KC_NO,          KC_NO,
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
/* Keymap 2: Symbol and Numpad
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |      |      |      |      |      |      |           |      |      | NMLK |  P=  |  P/  |  P*  |        |
 * |---------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |  \   |   7  |   8  |   9  |  P-  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | CAPSLCK |   #  |   $  |   (  |   )  |   `  |------|           |------|  *   |   4  |   5  |   6  |  P+  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [   |  ]  |   ~  |      |           |      |  &   |   1  |   2  |   3  | PEnt |        |
 * `---------+------+------+------+------+------+------'           `------+------+------+------+------+------+--------'
 *    |      |      |      |      |      |                                       |      |   0  |  P.  |      |      |
 *    `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Symbol and Numpad
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

/* Keymap 4: Semicolon mod
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  | Mute |           | App  |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   ~  |  &   |           |      |      |      | INS  |      | PRSC |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   ^  |   #  |   (  |   )  |   $  |------|           |------| Left | Down |  Up  | Rght |      |        |
 * |---------+------+------+------+------+------|  |   |           |      |------+------+------+------+------+--------|
 * |         |   #  |   %  |   [   |  ]  |   `  |      |           |      | Calc | SRCH | Mail | WWW  | Edit |        |
 * `---------+------+------+------+------+------+------'           `-------------+------+------+------+------+--------'
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
// Motion
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
       M(FLSH),    KC_TRNS,     KC_TRNS,      KC_TRNS,     KC_TRNS,      KC_TRNS,     KC_TRNS,
       KC_TRNS,   KC_TRNS,     KC_TRNS,      KC_TRNS,    KC_TRNS,      KC_TRNS,    KC_TRNS,
                  KC_TRNS,   KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,      KC_TRNS,
       KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,
                             KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_TRNS,    KC_TRNS,
       KC_TRNS,
       KC_TRNS,   KC_TRNS,   KC_TRNS
       ),
[LANG] = KEYMAP(
       // left hand
       KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS, KC_TRNS,
       KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS, KC_TRNS,
       KC_TRNS,   LALT(KC_A),LALT(KC_SCLN), LALT(KC_E),     KC_TRNS,    KC_TRNS,
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
};
const uint16_t PROGMEM fn_actions[] = {
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    case FLSH:
      if (record->event.pressed) { // For resetting EEPROM
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
