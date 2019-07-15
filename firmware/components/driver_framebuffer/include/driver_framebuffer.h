#ifndef _DRIVER_FRAMEBUFFER_H_
#define _DRIVER_FRAMEBUFFER_H_
#include "include/driver_ssd1306.h"
#include "include/driver_erc12864.h"
#include "include/driver_eink.h"

#ifdef CONFIG_DRIVER_SSD1306_ENABLE
	#define FB_SIZE SSD1306_BUFFER_SIZE
	#define FB_WIDTH SSD1306_WIDTH
	#define FB_HEIGHT SSD1306_HEIGHT
	#define FB_TYPE_1BPP
	#define FB_1BPP_VERT
	#define FB_FLUSH(buffer,flags) driver_ssd1306_write(buffer);
	#define COLOR_BLACK 0
	#define COLOR_WHITE 1
#endif

#ifdef CONFIG_DRIVER_ERC12864_ENABLE
	#define FB_SIZE ERC12864_BUFFER_SIZE
	#define FB_WIDTH ERC12864_WIDTH
	#define FB_HEIGHT ERC12864_HEIGHT
	#define FB_TYPE_1BPP
	#define FB_1BPP_VERT
	#define FB_FLUSH(buffer,flags) driver_erc12864_write(buffer);
	#define COLOR_BLACK 0
	#define COLOR_WHITE 1
#endif

#ifdef CONFIG_DRIVER_EINK_ENABLE
	#define FB_SIZE EINK_BUFFER_SIZE
	#define FB_WIDTH DRIVER_EINK_WIDTH
	#define FB_HEIGHT DRIVER_EINK_HEIGHT
	#define FB_TYPE_8BPP
	#define FB_FLUSH(buffer,flags) driver_eink_display(buffer,flags);
	#define COLOR_BLACK 0
	#define COLOR_WHITE 255
#endif

#include "gfxfont.h"

#ifndef PROGMEM //We don't use PROGMEM.
	#define PROGMEM
#endif

/* Fonts */
#include "include/fonts/freesans9pt7b.h"
#include "include/fonts/freesansbold12pt7b.h"
#include "include/fonts/freesansbold9pt7b.h"
#include "include/fonts/fairlight8pt7b.h"
#include "include/fonts/org_018pt7b.h"

#ifdef CONFIG_DRIVER_FRAMEBUFFER_DOUBLE_BUFFERED
bool currentFb;
uint8_t* framebuffer1, framebuffer2;
#else
uint8_t* framebuffer;
#endif

esp_err_t driver_framebuffer_init();
void driver_framebuffer_setCursor(int16_t x, int16_t y);
void driver_framebuffer_getCursor(int16_t* x, int16_t* y);
void driver_framebuffer_write(uint8_t c);
void driver_framebuffer_print(const char* str);
void driver_framebuffer_setScale(int16_t x, int16_t y);
void driver_framebuffer_setFont(const GFXfont *font);
void driver_framebuffer_flush();

#ifdef FB_TYPE_1BPP
void driver_framebuffer_fill(bool value);
void driver_framebuffer_pixel(uint16_t x, uint16_t y, bool value);
void driver_framebuffer_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, bool value);
void driver_framebuffer_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool fill, bool value);
void driver_framebuffer_circle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t a0, uint16_t a1, bool fill, bool value);
void driver_framebuffer_char(uint16_t x0, uint16_t y0, unsigned char c, uint8_t xScale, uint8_t yScale, bool value);
void driver_framebuffer_setTextColor(bool value);
#endif
#ifdef FB_TYPE_8BPP
void driver_framebuffer_fill(uint8_t value);
void driver_framebuffer_pixel(uint16_t x, uint16_t y, uint8_t value);
void driver_framebuffer_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t value);
void driver_framebuffer_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool fill, uint8_t value);
void driver_framebuffer_circle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t a0, uint16_t a1, bool fill, uint8_t value);
void driver_framebuffer_char(uint16_t x0, uint16_t y0, unsigned char c, uint8_t xScale, uint8_t yScale, uint8_t value);
void driver_framebuffer_setTextColor(uint8_t value);
#endif
#ifdef FB_TYPE_24BPP
void driver_framebuffer_fill(uint8_t r, uint8_t g, uint8_t b);
void driver_framebuffer_pixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b);
void driver_framebuffer_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t r, uint8_t g, uint8_t b);
void driver_framebuffer_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool fill, uint8_t r, uint8_t g, uint8_t b);
void driver_framebuffer_circle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t a0, uint16_t a1, bool fill, uint8_t r, uint8_t g, uint8_t b);
void driver_framebuffer_char(uint16_t x0, uint16_t y0, unsigned char c, uint8_t xScale, uint8_t yScale, uint8_t r, uint8_t g, uint8_t b);
void driver_framebuffer_setTextColor(uint8_t r, uint8_t g, uint8_t b);
#endif

#endif //_DRIVER_FRAMEBUFFER_H_
