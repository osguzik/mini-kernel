#include "kprintf.h"

#include "serial.h"

#include <stdarg.h>
#include <stdint.h>

static const char digits[] = "0123456789abcdef";

static void print_uint(uint64_t val, int base) {
    char buf[20]; // max decimal digits of uint64_t is 20
    int i = 0;

    do {
        buf[i++] = digits[val % base];
        val /= base;
    } while (val);

    while (i > 0) {
        serial_putc(buf[--i]);
    }
}

static void print_int(int64_t val) {
    if (val < 0) {
        serial_putc('-');
        print_uint(-(uint64_t)val, 10);
    } else {
        print_uint(val, 10);
    }
}

void kprintf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    while (*fmt) {
        if (*fmt != '%') {
            serial_putc(*fmt);
            continue;
        }

        fmt++;
        int is_long = 0;
        while (*fmt == 'l') { // %l or %ll (both 64-bit on x86-64)
            is_long = 1;
            fmt++;
        }
        if (*fmt == '\0') {
            break;
        }

        switch (*fmt) {
        case 'd':
            print_int(is_long ? va_arg(args, int64_t) : va_arg(args, int));
            break;
        case 'u':
            print_uint(is_long ? va_arg(args, uint64_t) : va_arg(args, unsigned int), 10);
            break;
        case 'x':
            print_uint(is_long ? va_arg(args, uint64_t) : va_arg(args, unsigned int), 16);
            break;
        case 'c':
            serial_putc((char)va_arg(args, int));
            break;
        case 's': {
            const char *s = va_arg(args, const char *);
            serial_puts(s ? s : "(null)");
            break;
        }
        case '%':
            serial_putc('%');
            break;
        default:
            // print unknown % sequence to draw attention
            serial_putc('%');
            serial_putc(*fmt);
            break;
        }
    }

    va_end(args);
}
