require "mkmf"

$LDFLAGS << " -lX11 -lcrypto -lssl"

abort "missing malloc()" unless have_func "malloc"
abort "missing free()"   unless have_func "free"

create_makefile "khanh/khanh"