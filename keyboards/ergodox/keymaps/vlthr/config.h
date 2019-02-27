#ifndef CONFIG_SJB_H
#define CONFIG_SJB_H

#include "../../config.h"

#undef MOUSEKEY_TIME_TO_MAX
#undef MOUSEKEY_MAX_SPEED

#define MOUSEKEY_TIME_TO_MAX 7
#define MOUSEKEY_MAX_SPEED 4

#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 0

#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY 0

#define ONESHOT_TAP_TOGGLE 3
#define ONESHOT_TIMEOUT 1000

#undef TAPPING_TERM
#define TAPPING_TERM 180
#define PERMISSIVE_HOLD

// Consumes extra memory, but prevents modifiers from getting stuck if they are held while switching to another layer that redefines the mod key
#define PREVENT_STUCK_MODIFIERS
// this makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.)
#define IGNORE_MOD_TAP_INTERRUPT
// (Together with IGNORE_MOD_TAP_INTERRUPT?) this prevents the behavior of tap/hold modifiers where a tap->hold is interpreted as the TAP key being held, rather than the modifier
#define TAPPING_FORCE_HOLD

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

#ifdef DEBUG_ENABLE
#undef NO_PRINT
#undef NO_DEBUG
#endif

#endif
