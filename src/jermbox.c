#include <janet.h>
#include <stdio.h>
#include "../termbox_next/src/termbox.h"

/* types */
static const JanetAbstractType tb_event_jermbox = {
  "tb_event",
  JANET_ATEND_NAME
};

static const JanetAbstractType tb_cell_jermbox = {
  "tb_cell",
  JANET_ATEND_NAME
};

/* Event Initialization and Handlers */
static Janet
cfun_init_event (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 0);
  (void) argv;
  struct tb_event *event = janet_abstract(&tb_event_jermbox, sizeof(struct tb_event));
  return janet_wrap_abstract(event);
}

static Janet
cfun_event_type (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  struct tb_event *event = ((struct tb_event *) janet_getabstract(argv, 0, &tb_event_jermbox));
  return janet_wrap_integer((int)event->type);
}

static Janet
cfun_event_modifier (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  struct tb_event *event = ((struct tb_event *) janet_getabstract(argv, 0, &tb_event_jermbox));
  return janet_wrap_integer((int) event->mod);
}

static Janet
cfun_event_key (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  struct tb_event *event = ((struct tb_event *) janet_getabstract(argv, 0, &tb_event_jermbox));
  return janet_wrap_integer((int) event->key);
}

static Janet
cfun_event_character (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  struct tb_event *event = ((struct tb_event *) janet_getabstract(argv, 0, &tb_event_jermbox));
  return janet_wrap_integer((int)event->ch);
}

static Janet
cfun_event_width (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  struct tb_event *event = ((struct tb_event *) janet_getabstract(argv, 0, &tb_event_jermbox));
  return janet_wrap_integer((int)event->w);
}

static Janet
cfun_event_height (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  struct tb_event *event = ((struct tb_event *) janet_getabstract(argv, 0, &tb_event_jermbox));
  return janet_wrap_integer((int)event->h);
}

static Janet
cfun_event_x (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  struct tb_event *event = ((struct tb_event *) janet_getabstract(argv, 0, &tb_event_jermbox));
  return janet_wrap_integer((int)event->x);
}

static Janet
cfun_event_y (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  struct tb_event *event = ((struct tb_event *) janet_getabstract(argv, 0, &tb_event_jermbox));
  return janet_wrap_integer((int)event->y);
}

/* c function wrappers */
static Janet
cfun_init (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 0);
  (void) argv;

  int code = tb_init();
  if (code < 0) {
    janet_panicf("jermbox init failed, code: %d\n", code);
  }

  return janet_wrap_nil();
}

static Janet
cfun_init_file (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  const char *f = janet_getcstring(argv, 0);
  int code = tb_init_file(f);
  if (code < 0) {
    janet_panicf("jermbox init-file failed, code: %d", code);
  }
  return janet_wrap_nil();
}

static Janet
cfun_shutdown (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 0);
  (void)argv;

  tb_shutdown();
  return janet_wrap_nil();
}

static Janet
cfun_tb_width (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 0);
  (void)argv;
  return janet_wrap_integer(tb_width());
}

static Janet
cfun_tb_height (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 0);
  (void)argv;
  return janet_wrap_integer(tb_height());
}

static Janet
cfun_tb_clear (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 0);
  (void)argv;

  tb_clear();
  return janet_wrap_nil();
}

static Janet
cfun_tb_set_clear_attributes (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  uint16_t fg = (uint16_t) janet_getinteger(argv, 0);
  uint16_t bg = (uint16_t) janet_getinteger(argv, 1);

  tb_set_clear_attributes(fg, bg);
  return janet_wrap_nil();
}

static Janet
cfun_tb_present (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 0);
  (void)argv;

  tb_present();
  return janet_wrap_nil();
}

static Janet
cfun_tb_set_cursor (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  int cx = janet_getinteger(argv, 0);
  int cy = janet_getinteger(argv, 1);

  tb_set_cursor(cx, cy);
  return janet_wrap_nil();
}

static Janet
cfun_tb_put_cell (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  int x = janet_getinteger(argv, 0);
  int y = janet_getinteger(argv, 1);

  const struct tb_cell *cell = ((struct tb_cell *)janet_getabstract(argv, 2, &tb_cell_jermbox));
  tb_put_cell(x, y, cell);

  return janet_wrap_nil();
}

static Janet
cfun_tb_change_cell (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 5);
  int x = janet_getinteger(argv, 0);
  int y = janet_getinteger(argv, 1);
  uint32_t ch = janet_getinteger(argv, 2);
  uint32_t fg = janet_getinteger(argv, 3);
  uint32_t bg = janet_getinteger(argv, 4);

  tb_change_cell(x, y, ch, fg, bg);
  return janet_wrap_nil();
}

static Janet
cfun_tb_blit (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 5);
  int x = janet_getinteger(argv, 0);
  int y = janet_getinteger(argv, 1);
  int w = janet_getinteger(argv, 2);
  int h = janet_getinteger(argv, 3);
  const struct tb_cell *cells = ((struct tb_cell *)janet_getabstract(argv, 4, &tb_cell_jermbox));

  tb_blit(x, y, w, h, cells);
  return janet_wrap_nil();
}

static Janet
cfun_tb_select_input_mode (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  int mode = janet_getinteger(argv, 0);

  int code = tb_select_input_mode(mode);
  if (code < 0) {
    janet_panicf("jermbox select-input-mode failed, code: %d", code);
  }

  return janet_wrap_integer(mode);
}

static Janet
cfun_tb_select_output_mode (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  int mode = janet_getinteger(argv, 0);

  int code = tb_select_output_mode(mode);
  if (code < 0) {
    janet_panicf("jermbox select-input-mode failed, code: %d", code);
  }

  return janet_wrap_integer(mode);
}

static Janet
cfun_tb_peek_event (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  struct tb_event *event = ((struct tb_event *) janet_getabstract(argv, 0, &tb_event_jermbox));
  int timeout = janet_getinteger(argv, 1);

  int result = tb_peek_event(event, timeout);

  if (result == -1 || result == 0) {
    return janet_wrap_false();
  }
  return janet_wrap_true();
}

static Janet
cfun_tb_poll_event (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);

  struct tb_event *event = ((struct tb_event *) janet_getabstract(argv, 0, &tb_event_jermbox));
  if (tb_poll_event(event) == -1) {
    return janet_wrap_false();
  }
  return janet_wrap_true();
}

static Janet
cfun_utf8_char_length (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  
  const char *c = janet_getcstring(argv, 0);
  
  int result = utf8_char_length(*c);
  return janet_wrap_integer(result);
}

static Janet
cfun_utf8_char_to_unicode (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);

  uint32_t out = (uint32_t) janet_getinteger(argv, 0);
  char *c = (char *) janet_getcstring(argv, 1);

  int result = utf8_char_to_unicode(&out, c);
  return janet_wrap_integer(result);
}

static Janet
cfun_utf8_unicode_to_char (int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
 
  char *out = (char *) janet_getcstring(argv, 0);
  uint32_t c = (uint32_t) janet_getinteger(argv, 1);

  int result = utf8_unicode_to_char(out, c);

  return janet_wrap_integer(result);
}

/* Constants Registery */
void janet_cdefs(JanetTable *env) {
  /* TB_KEYS */
  janet_def(env, "key-f1", janet_wrap_integer(TB_KEY_F1), "f1");
  janet_def(env, "key-f2", janet_wrap_integer(TB_KEY_F2), "f2");
  janet_def(env, "key-f3", janet_wrap_integer(TB_KEY_F3), "f3");
  janet_def(env, "key-f4", janet_wrap_integer(TB_KEY_F4), "f4");
  janet_def(env, "key-f5", janet_wrap_integer(TB_KEY_F5), "f5");
  janet_def(env, "key-f6", janet_wrap_integer(TB_KEY_F6), "f6");
  janet_def(env, "key-f7", janet_wrap_integer(TB_KEY_F7), "f7");
  janet_def(env, "key-f8", janet_wrap_integer(TB_KEY_F8), "f8");
  janet_def(env, "key-f9", janet_wrap_integer(TB_KEY_F9), "f9");
  janet_def(env, "key-f10", janet_wrap_integer(TB_KEY_F10), "f10");
  janet_def(env, "key-f11", janet_wrap_integer(TB_KEY_F11), "f11");
  janet_def(env, "key-f12", janet_wrap_integer(TB_KEY_F12), "f12");
  janet_def(env, "key-insert", janet_wrap_integer(TB_KEY_INSERT), "insert");
  janet_def(env, "key-delete", janet_wrap_integer(TB_KEY_DELETE), "delete");
  janet_def(env, "key-home", janet_wrap_integer(TB_KEY_HOME), "home");
  janet_def(env, "key-end", janet_wrap_integer(TB_KEY_END), "end");
  janet_def(env, "key-pgup", janet_wrap_integer(TB_KEY_PGUP), "pgup");
  janet_def(env, "key-pgdn", janet_wrap_integer(TB_KEY_PGDN), "pgdn");
  janet_def(env, "key-arrow-up", janet_wrap_integer(TB_KEY_ARROW_UP), "arrow up");
  janet_def(env, "key-arrow-down", janet_wrap_integer(TB_KEY_ARROW_DOWN), "arrow down");
  janet_def(env, "key-arrow-left", janet_wrap_integer(TB_KEY_ARROW_LEFT), "arrow left");
  janet_def(env, "key-arrow-right", janet_wrap_integer(TB_KEY_ARROW_RIGHT), "arrow right");
  janet_def(env, "key-mouse-left", janet_wrap_integer(TB_KEY_MOUSE_LEFT), "mouse left");
  janet_def(env, "key-mouse-right", janet_wrap_integer(TB_KEY_MOUSE_RIGHT), "mouse right");
  janet_def(env, "key-mouse-middle", janet_wrap_integer(TB_KEY_MOUSE_MIDDLE), "mouse middle");
  janet_def(env, "key-mouse-release", janet_wrap_integer(TB_KEY_MOUSE_RELEASE), "mouse release");
  janet_def(env, "key-mouse-wheel-up", janet_wrap_integer(TB_KEY_MOUSE_WHEEL_UP), "mouse wheel up");
  janet_def(env, "key-mouse-wheel-down", janet_wrap_integer(TB_KEY_MOUSE_WHEEL_DOWN), "mouse wheel down");

  janet_def(env, "key-ctrl-tilde", janet_wrap_integer(TB_KEY_CTRL_TILDE), "ctrl tilde");
  janet_def(env, "key-ctrl-2", janet_wrap_integer(TB_KEY_CTRL_2), "ctrl 2");
  janet_def(env, "key-ctrl-a", janet_wrap_integer(TB_KEY_CTRL_A), "ctrl a");
  janet_def(env, "key-ctrl-b", janet_wrap_integer(TB_KEY_CTRL_B), "ctrl b");
  janet_def(env, "key-ctrl-c", janet_wrap_integer(TB_KEY_CTRL_C), "ctrl c");
  janet_def(env, "key-ctrl-d", janet_wrap_integer(TB_KEY_CTRL_D), "ctrl d");
  janet_def(env, "key-ctrl-e", janet_wrap_integer(TB_KEY_CTRL_E), "ctrl e");
  janet_def(env, "key-ctrl-f", janet_wrap_integer(TB_KEY_CTRL_F), "ctrl f");
  janet_def(env, "key-ctrl-g", janet_wrap_integer(TB_KEY_CTRL_G), "ctrl g");
  janet_def(env, "key-backspace", janet_wrap_integer(TB_KEY_BACKSPACE), "backspace");
  janet_def(env, "key-ctrl-h", janet_wrap_integer(TB_KEY_CTRL_H), "ctrl h");
  janet_def(env, "key-tab", janet_wrap_integer(TB_KEY_TAB), "tab");
  janet_def(env, "key-ctrl-i", janet_wrap_integer(TB_KEY_CTRL_I), "ctrl i");
  janet_def(env, "key-ctrl-j", janet_wrap_integer(TB_KEY_CTRL_J), "ctrl j");
  janet_def(env, "key-ctrl-k", janet_wrap_integer(TB_KEY_CTRL_K), "ctrl k");
  janet_def(env, "key-ctrl-l", janet_wrap_integer(TB_KEY_CTRL_L), "ctrl l");
  janet_def(env, "key-enter", janet_wrap_integer(TB_KEY_ENTER), "enter");
  janet_def(env, "key-ctrl-m", janet_wrap_integer(TB_KEY_CTRL_M), "ctrl m");
  janet_def(env, "key-ctrl-n", janet_wrap_integer(TB_KEY_CTRL_N), "ctrl n");
  janet_def(env, "key-ctrl-o", janet_wrap_integer(TB_KEY_CTRL_O), "ctrl o");
  janet_def(env, "key-ctrl-p", janet_wrap_integer(TB_KEY_CTRL_P), "ctrl p");
  janet_def(env, "key-ctrl-q", janet_wrap_integer(TB_KEY_CTRL_Q), "ctrl q");
  janet_def(env, "key-ctrl-r", janet_wrap_integer(TB_KEY_CTRL_R), "ctrl r");
  janet_def(env, "key-ctrl-s", janet_wrap_integer(TB_KEY_CTRL_S), "ctrl s");
  janet_def(env, "key-ctrl-t", janet_wrap_integer(TB_KEY_CTRL_T), "ctrl t");
  janet_def(env, "key-ctrl-u", janet_wrap_integer(TB_KEY_CTRL_U), "ctrl u");
  janet_def(env, "key-ctrl-v", janet_wrap_integer(TB_KEY_CTRL_V), "ctrl v");
  janet_def(env, "key-ctrl-w", janet_wrap_integer(TB_KEY_CTRL_W), "ctrl w");
  janet_def(env, "key-ctrl-x", janet_wrap_integer(TB_KEY_CTRL_X), "ctrl x");
  janet_def(env, "key-ctrl-y", janet_wrap_integer(TB_KEY_CTRL_Y), "ctrl y");
  janet_def(env, "key-ctrl-z", janet_wrap_integer(TB_KEY_CTRL_Z), "ctrl z");
  janet_def(env, "key-esc", janet_wrap_integer(TB_KEY_ESC), "esc");
  janet_def(env, "key-ctrl-lsq-bracket", janet_wrap_integer(TB_KEY_CTRL_LSQ_BRACKET), "ctrl lsq bracket");
  janet_def(env, "key-ctrl-3", janet_wrap_integer(TB_KEY_CTRL_3), "ctrl 3");
  janet_def(env, "key-ctrl-4", janet_wrap_integer(TB_KEY_CTRL_4), "ctrl 4");
  janet_def(env, "key-ctrl-backslash", janet_wrap_integer(TB_KEY_CTRL_BACKSLASH), "ctrl backslash");
  janet_def(env, "key-ctrl-5", janet_wrap_integer(TB_KEY_CTRL_5), "ctrl 5");
  janet_def(env, "key-ctrl-rsq-bracket", janet_wrap_integer(TB_KEY_CTRL_RSQ_BRACKET), "ctrl rsq bracket");
  janet_def(env, "key-ctrl-6", janet_wrap_integer(TB_KEY_CTRL_6), "ctrl 6");
  janet_def(env, "key-ctrl-7", janet_wrap_integer(TB_KEY_CTRL_7), "ctrl 7");
  janet_def(env, "key-ctrl-slash", janet_wrap_integer(TB_KEY_CTRL_SLASH), "ctrl slash");
  janet_def(env, "key-ctrl-underscore", janet_wrap_integer(TB_KEY_CTRL_UNDERSCORE), "ctrl underscore");
  janet_def(env, "key-space", janet_wrap_integer(TB_KEY_SPACE), "space");
  janet_def(env, "key-backspace2", janet_wrap_integer(TB_KEY_BACKSPACE2), "backspace2");
  janet_def(env, "key-ctrl-8", janet_wrap_integer(TB_KEY_CTRL_8), "ctrl 8");

  /* MODIFIERS */
  janet_def(env, "mod-alt", janet_wrap_integer(TB_MOD_ALT), "mod alt");
  janet_def(env, "mod-motion", janet_wrap_integer(TB_MOD_MOTION), "mod motion");

  /* ATTRIBUTES */
  janet_def(env, "bold", janet_wrap_integer(TB_BOLD), "bold");
  janet_def(env, "underline", janet_wrap_integer(TB_UNDERLINE), "underline");
  janet_def(env, "reverse", janet_wrap_integer(TB_REVERSE), "reverse");

  /* EVENTS */
  janet_def(env, "jb-event-key", janet_wrap_integer(TB_EVENT_KEY), "event key");
  janet_def(env, "jb-event-resize", janet_wrap_integer(TB_EVENT_RESIZE), "event resize");
  janet_def(env, "jb-event-mouse", janet_wrap_integer(TB_EVENT_MOUSE), "event mouse");

  /* ERROR CODES RETURNED BY tb_init */
  janet_def(env, "eunsupported-terminal", janet_wrap_integer(TB_EUNSUPPORTED_TERMINAL), "unsupported terminal");
  janet_def(env, "efailed-to-open-tty", janet_wrap_integer(TB_EFAILED_TO_OPEN_TTY), "failed to open tty");
  janet_def(env, "epipe-trap-error", janet_wrap_integer(TB_EPIPE_TRAP_ERROR), "pipe trap error");

  /* COLORS */
  janet_def(env, "default", janet_wrap_integer(TB_DEFAULT), "default");
  janet_def(env, "black", janet_wrap_integer(TB_BLACK), "black");
  janet_def(env, "red", janet_wrap_integer(TB_RED), "red");
  janet_def(env, "green", janet_wrap_integer(TB_GREEN), "green");
  janet_def(env, "yellow", janet_wrap_integer(TB_YELLOW), "yellow");
  janet_def(env, "blue", janet_wrap_integer(TB_BLUE), "blue");
  janet_def(env, "magenta", janet_wrap_integer(TB_MAGENTA), "magenta");
  janet_def(env, "cyan", janet_wrap_integer(TB_CYAN), "cyan");
  janet_def(env, "white", janet_wrap_integer(TB_WHITE), "white");

  /* TB_INPUT_MODE */
  janet_def(env, "input-current", janet_wrap_integer(TB_INPUT_CURRENT), "termbox input current");
  janet_def(env, "input-esc", janet_wrap_integer(TB_INPUT_ESC), "termbox input esc");
  janet_def(env, "input-alt", janet_wrap_integer(TB_INPUT_ALT), "termbox input alt");
  janet_def(env, "input-mouse", janet_wrap_integer(TB_INPUT_MOUSE), "termbox input mouse");

  /* TB_OUTPUT_MODE */
  janet_def(env, "output-current", janet_wrap_integer(TB_OUTPUT_CURRENT), "termbox output current");
  janet_def(env, "output-normal", janet_wrap_integer(TB_OUTPUT_NORMAL), "termbox output normal");
  janet_def(env, "output-256", janet_wrap_integer(TB_OUTPUT_256), "termbox output 256");
  janet_def(env, "output-216", janet_wrap_integer(TB_OUTPUT_216), "termbox output 216");
  janet_def(env, "output-grayscale", janet_wrap_integer(TB_OUTPUT_GRAYSCALE), "termbox output grayscale");
  janet_def(env, "output-truecolor", janet_wrap_integer(TB_OUTPUT_TRUECOLOR), "termbox output truecolor");

  janet_def(env, "hide-cursor", janet_wrap_integer(TB_HIDE_CURSOR), "hide cursor");
  janet_def(env, "eof", janet_wrap_integer(TB_EOF), "end of file");
}

/* function registry */
static JanetReg cfuns[] = {
  {"init", cfun_init, "Initializes the jermbox library"},
  {"init-file", cfun_init_file, "Initializes jermbox to a file"},
  {"init-event", cfun_init_event, "Initializes an event struct"},
  {"event-type", cfun_event_type, "return type from event"},
  {"event-modifier", cfun_event_modifier, "return modifiers from event"},
  {"event-key", cfun_event_key, "return one of the key constants"},
  {"event-character", cfun_event_character, "return a unicode character"},
  {"event-width", cfun_event_width, "return width if resized"},
  {"event-height", cfun_event_height, "return height if resized"},
  {"event-x", cfun_event_x, "if mouse used, return x coordinate"},
  {"event-y", cfun_event_y, "if mouse used, return y coordinate"},
  {"shutdown", cfun_shutdown, "Shutdown and finalize jermbox"},
  {"width", cfun_tb_width, "Returns size of internal back buffer"},
  {"height", cfun_tb_height, "Returns size of internal back buffer"},
  {"clear", cfun_tb_clear, "Clears internal back buffer using default colors"},
  {"set-clear-attributes", cfun_tb_set_clear_attributes, "Clears internal back buffer using supplied fg/bg colors"},
  {"present", cfun_tb_present, "Synchronizes internal backbuffer with termainal"},
  {"set-cursor", cfun_tb_set_cursor, "Set cursor position"},
  {"put-cell", cfun_tb_put_cell, "Changes cell's parameters"},
  {"change-cell", cfun_tb_change_cell, "Changes cell's parameters"},
  {"blit", cfun_tb_blit, "Copies the buffer from given positions"},
  {"select-input-mode", cfun_tb_select_input_mode, "Set input mode"},
  {"select-output-mode", cfun_tb_select_output_mode, "Set output mode"},
  {"peek-event", cfun_tb_peek_event, "Wait for event for timout length"},
  {"poll-event", cfun_tb_poll_event, "Wait for event forever"},
  {"utf8-char-length", cfun_utf8_char_length, "get length of character"},
  {"utf8-char-to-unicode", cfun_utf8_char_to_unicode, "Convert character"},
  {"utf8-unicode-to-char", cfun_utf8_unicode_to_char, "Convert unicode"},
  {NULL, NULL, NULL}
};

JANET_MODULE_ENTRY (JanetTable *env) {
  janet_cdefs(env);
  janet_cfuns(env, "jermbox", cfuns);
}
