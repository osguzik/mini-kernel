# mini-kernel

A minimal operating system kernel for x86-64

## Dependencies

- GNU make
- GCC or Clang (x86-64 ELF)
- xorriso
- QEMU

### Installation

Debian/Ubuntu:

```
sudo apt install build-essential xorriso qemu-system-x86
```

## Build and run

```
make run        # BIOS
make run-uefi   # UEFI
```

## Debugging

Requires GDB (`sudo apt install gdb`)

Start QEMU paused, waiting for GDB:

```
make debug          # BIOS
make debug-uefi     # UEFI
```

In a second terminal (from the project root):

```
gdb kernel/bin/kernel
(gdb) target remote :1234
(gdb) break kmain           # use hbreak if the breakpoint is not hit
(gdb) continue
```

For easier stepping, build without optimizations: `make debug CFLAGS="-g -O0 -pipe"`

In VS Code, run `make debug` and then use **Run->Start Debugging** (configured in `.vscode/launch.json`)

See also: https://www.qemu.org/docs/master/system/gdb.html
