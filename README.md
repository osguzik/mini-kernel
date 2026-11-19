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

## Debug with GDB

### Dependencies for debugging

- GDB
- C/C++ extension (for debugging in Visual Studio Code)

### Debugging in another session in terminal

First session in terminal
```
make debug          #BIOS
make debug-uefi     #UEFI
```
Second session in terminal (also in project's root directory)
```
gdb kernel/bin/kernel
target remote localhost:1234    # connection with debug data sent by QEMU
break kmain     # setting breakpoint in kmain(). Use hbreak if break fails.
c               # program continues until the next breakpoint
layout src      # showing code 
layout regs     # showing registers
next            # one instuction
step            # also one instruction, but includes entering to other functions
c               # the same as continue
quit            # after closing QEMU (you may start another debugging session 
                # without quitting by using target remote localhost:1234)
```
For more information about gdb use ```man gdb``` or visit https://www.qemu.org/docs/master/system/gdb.html

### Debugging with VS Code

```
make debug          #BIOS
make debug-uefi     #UEFI
```

VS Code (after launching QEMU!):
1. Choose project's .c file in VS Code
2. Upper panel->Run->Start Debugging
3. Set breakpoint in .c file
4. Use standard VS Code GUI for debugging