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

Profile physical and virtual memory with `pmap`.

```bash
pmap -X <pid>
```

Trace memory allocations with `valgrind`.

```bash
valgrind --tool=massif ./dist/dev

ms_print massif.out.<pid>
```