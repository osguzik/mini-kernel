#include "kprintf.h"

#include "serial.h"

#include <stdarg.h>

void kprintf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    while (*fmt) {
        if (*fmt != '%') {
            serial_putc(*fmt);
            continue;
        }

        fmt++;
        if (*fmt == '\0') {
            break;
        }

        switch (*fmt) {
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
            serial_putc('%');
            serial_putc(*fmt);
            break;
        }
    }

    va_end(args);
}
