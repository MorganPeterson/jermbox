(declare-project
  :name "jermbox"
  :author "Morgan Peterson <lastyearsmodel@gmail.com"
  :license "MIT"
  :url "https://github.com/MorganPeterson/jermbox"
  :repo "https://github.com/MorganPeterson/jermbox")

(def cflags
  '["-std=c99"
    "-Wall"
    "-Werror"
    "-D_POSIX_C_SOURCE=200809L"
    "-D_XOPEN_SOURCE"])

(declare-native
  :name "jermbox"
  :cflags cflags
  :source ["src/jermbox.c"
           "termbox_next/src/termbox.c"
           "termbox_next/src/utf8.c"
           "termbox_next/src/term.c"
           "termbox_next/src/ringbuffer.c"
           "termbox_next/src/input.c"
           "termbox_next/src/memstream.c"])

