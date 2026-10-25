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
