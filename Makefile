CC=gcc
CFLAGS=-Wall -I.
HEADERS=$(shell find . -maxdepth 1 -type f -name '*.h')
SRC=$(shell find . -maxdepth 1 -type f -name '*.c')
OBJ=$(SRC:.c=.o)

DEPS_PATH=-Llibuiohook/dist/lib -Wl,-rpath=libuiohook/dist/lib
DEPS=-luiohook

main: deps $(OBJ)
	$(CC) $(DEPS_PATH) -o $@ $(OBJ) $(CFLAGS) $(DEPS)

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: deps
deps: libuiohook

libuiohook:
	git clone https://github.com/kwhat/libuiohook.git libuiohook; \
	cd libuiohook; \
	mkdir build && cd build; \
	cmake -S .. -D BUILD_SHARED_LIBS=ON -D BUILD_DEMO=ON -DCMAKE_INSTALL_PREFIX=../dist; \
	cmake --build . --parallel 2 --target install

.PHONY: clean-libuiohook
clean-libuiohook:
	rm -rf libuiohook

.PHONY: clean
clean:
	rm -f *.o *~ core *~ 

.PHONY: clean-deps
clean-deps: clean-libuiohook