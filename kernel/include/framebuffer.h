#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <limine.h>
#include <stdint.h>

void fb_init(struct limine_framebuffer *fb);
uint32_t fb_rgb(uint8_t r, uint8_t g, uint8_t b);
void fb_putpixel(uint32_t x, uint32_t y, uint32_t color);
void fb_fillrect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);
void fb_drawchar(char c, uint32_t x, uint32_t y, uint32_t fg, uint32_t bg);

#endif // !FRAMEBUFFER_H