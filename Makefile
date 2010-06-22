GCC=gcc
INSTALL=/usr/bin/install
LDCONFIG=/sbin/ldconfig

lib:
	$(GCC) -std=c99 -shared -o libxcorr.so src/xcorr.c

install:
	$(INSTALL) include/xcorr.h /usr/local/include/
	$(INSTALL) libxcorr.so /usr/local/lib/
	$(LDCONFIG)

all: lib install