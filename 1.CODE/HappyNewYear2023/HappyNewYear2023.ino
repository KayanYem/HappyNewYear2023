#include "U8g2lib.h"

/**************OLED初始化*********************/
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE, /* clock=*/18, /* data=*/19);  // ESP32 Thing, HW I2C with pin remapping

int frame = 0;
const int sprite_count = 10;
int sprite_x[sprite_count];
int sprite_y[sprite_count];
int sprite_img[sprite_count];

// 'frame_01', 8x8px
const unsigned char epd_bitmap_frame_01 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00
};
// 'frame_02', 8x8px
const unsigned char epd_bitmap_frame_02 [] PROGMEM = {
	0x00, 0x00, 0x28, 0x10, 0x28, 0x00, 0x00, 0x00
};
// 'frame_03', 8x8px
const unsigned char epd_bitmap_frame_03 [] PROGMEM = {
	0x00, 0x44, 0x28, 0x10, 0x28, 0x44, 0x00, 0x00
};
// 'frame_04', 8x8px
const unsigned char epd_bitmap_frame_04 [] PROGMEM = {
	0x82, 0x44, 0x28, 0x00, 0x28, 0x44, 0x82, 0x00
};
// 'frame_05', 8x8px
const unsigned char epd_bitmap_frame_05 [] PROGMEM = {
	0x82, 0x44, 0x00, 0x10, 0x00, 0x44, 0x82, 0x00
};
// 'frame_06', 8x8px
const unsigned char epd_bitmap_frame_06 [] PROGMEM = {
	0x82, 0x00, 0x10, 0x38, 0x10, 0x00, 0x82, 0x00
};
// 'frame_07', 8x8px
const unsigned char epd_bitmap_frame_07 [] PROGMEM = {
	0x00, 0x10, 0x10, 0x6c, 0x10, 0x10, 0x00, 0x00
};
// 'frame_08', 8x8px
const unsigned char epd_bitmap_frame_08 [] PROGMEM = {
	0x10, 0x10, 0x00, 0xc6, 0x00, 0x10, 0x10, 0x00
};
// 'frame_09', 8x8px
const unsigned char epd_bitmap_frame_09 [] PROGMEM = {
	0x10, 0x00, 0x00, 0x82, 0x00, 0x00, 0x10, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 288)
const int epd_bitmap_allArray_LEN = 9;
const unsigned char* epd_bitmap_allArray[9] = {
	epd_bitmap_frame_01,
	epd_bitmap_frame_02,
	epd_bitmap_frame_03,
	epd_bitmap_frame_04,
	epd_bitmap_frame_05,
	epd_bitmap_frame_06,
	epd_bitmap_frame_07,
	epd_bitmap_frame_08,
	epd_bitmap_frame_09
};


void setup() {
  u8g2.begin();
  u8g2.enableUTF8Print();  // enable UTF8 support for the Arduino print() function
  delay(10);
  
  for (int i = 0; i < sprite_count; i++){
    sprite_x[i] = random(0, 128-8);
    sprite_y[i] = random(0, 64-8);
    sprite_img[i] = i % 9;
  }
  
}

void loop() {
  u8g2.firstPage();
  do {

    // u8g2.drawBitmap( 0, 0, 8/8, 8, epd_bitmap_allArray[frame]);

    for (int i = 0; i < sprite_count; i++){
      u8g2.drawBitmap( sprite_x[i], sprite_y[i], 8/8, 8, epd_bitmap_allArray[sprite_img[i]]);
        
      u8g2.setFont(u8g_font_9x18B);
      u8g2.drawStr(128/2-u8g2.getStrWidth("HAPPY NEW YEAR")/2,25,"HAPPY NEW YEAR");
      u8g2.setFont(u8g_font_profont22);
      u8g2.drawStr(128/2-u8g2.getStrWidth("2023")/2, 50,"2023");

    }
    
  } while ( u8g2.nextPage() );

  for (int i = 0; i < sprite_count; i++){
    sprite_img[i]++;
    if(sprite_img[i] >= epd_bitmap_allArray_LEN){
      sprite_x[i] = random(0, 128-8);
      sprite_y[i] = random(0, 64-8);
      sprite_img[i] = 0;
    }
  }

  delay(10);
}
