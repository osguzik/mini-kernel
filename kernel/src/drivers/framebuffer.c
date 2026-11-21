#include "framebuffer.h"
#include "font.h"

static struct limine_framebuffer *current_fb;

void fb_init(struct limine_framebuffer *fb) {
    current_fb = fb;
}

// Scale an 8-bit colour channel value to the size the framebuffer gives the
// channel and move it into place within a pixel.
static uint32_t fb_channel(uint8_t value, uint8_t mask_size, uint8_t mask_shift) {
    uint64_t max = ((uint64_t)1 << mask_size) - 1;
    return (uint32_t)((value * max / 255) << mask_shift);
}

uint32_t fb_rgb(uint8_t r, uint8_t g, uint8_t b) {
    if (!current_fb) {
        return 0;
    }
    return fb_channel(r, current_fb->red_mask_size, current_fb->red_mask_shift)
         | fb_channel(g, current_fb->green_mask_size, current_fb->green_mask_shift)
         | fb_channel(b, current_fb->blue_mask_size, current_fb->blue_mask_shift);
}

void fb_putpixel(uint32_t x, uint32_t y, uint32_t color) {
    if (!current_fb || x >= current_fb->width || y >= current_fb->height) {
        return;
    }
    volatile uint32_t *fb_ptr = current_fb->address;
    fb_ptr[y * (current_fb->pitch / 4) + x] = color;
}

void fb_fillrect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color) {
    for (uint32_t dy = 0; dy < h; dy++) {
        for (uint32_t dx = 0; dx < w; dx++) {
            fb_putpixel(x + dx, y + dy, color);
        }
    }
}

void fb_drawchar(char c, uint32_t x, uint32_t y, uint32_t fg, uint32_t bg) {
    const uint8_t *glyph = font[(uint8_t)c];

    for (uint32_t row = 0; row < FONT_HEIGHT; row++) {
        for (uint32_t col = 0; col < FONT_WIDTH; col++) {
            if (glyph[row] & (0x80 >> col)) {
                fb_putpixel(x + col, y + row, fg);
            } else {
                fb_putpixel(x + col, y + row, bg);
            }
        }
    }
}
