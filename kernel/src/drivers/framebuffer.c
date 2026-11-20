#include "framebuffer.h"

#include <stddef.h>

static struct limine_framebuffer *current_fb = NULL;
void fb_init(struct limine_framebuffer *fb) {
    current_fb = fb;
}