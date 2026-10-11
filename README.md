# FIGHT DA STARZ

## Build Dependencies

- gcc
- make

## Development Build

```bash
make
```
or
```bash
make dev
```

Run the dev build: `./dist/dev`

## Production Build

```bash
make prod
```

Run the prod build: `./dist/prod`

## Debugging

Basic debugging can be done with `gdb`.

Trace memory allocations with `mtrace` or `valgrind`.

mtrace:
```bash
LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libc_malloc_debug.so MALLOC_TRACE=/tmp/mtrace.txt ./dist/dev

mtrace ./dist/dev /tmp/mtrace.txt
```

valgrind:
```bash
valgrind --tool=massif ./dist/dev

ms_print massif.out.<pid>
```