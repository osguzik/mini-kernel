#ifndef KPRINTF_H

__attribute__ ((format(printf, 1, 2)))
void kprintf(const char *fmt, ...);

#endif // !KPRINTF_H
