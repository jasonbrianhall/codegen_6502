#include <nes.h>
#include <peekpoke.h>

// Simple palette data
const unsigned char palette[16] = {
    0x0F, 0x00, 0x10, 0x30,  // Background palette 0
    0x0F, 0x06, 0x16, 0x26,  // Background palette 1
    0x0F, 0x09, 0x19, 0x29,  // Background palette 2
    0x0F, 0x02, 0x12, 0x22   // Background palette 3
};

// Function to wait for VBlank
void wait_for_vblank(void) {
    while (!(PEEK(0x2002) & 0x80));
}

// Function to load palette
void load_palette(void) {
    unsigned char i;
    
    // Set PPU address to palette RAM
    POKE(0x2006, 0x3F);
    POKE(0x2006, 0x00);
    
    // Load palette data
    for (i = 0; i < 16; i++) {
        POKE(0x2007, palette[i]);
    }
}

// Function to clear screen
void clear_screen(void) {
    unsigned int i;
    
    // Set PPU address to nametable
    POKE(0x2006, 0x20);
    POKE(0x2006, 0x00);
    
    // Fill screen with spaces (tile 0)
    for (i = 0; i < 960; i++) {
        POKE(0x2007, 0x00);
    }
}

// Function to draw a simple pattern
void draw_pattern(void) {
    unsigned char x, y;
    
    // Set PPU address to center of screen
    POKE(0x2006, 0x21);
    POKE(0x2006, 0x4A);
    
    // Draw a simple 8x8 block pattern
    for (y = 0; y < 8; y++) {
        for (x = 0; x < 8; x++) {
            POKE(0x2007, 0x01);  // Use tile 1
        }
        // Skip to next row (32 tiles per row - 8 tiles drawn = 24 tiles to skip)
        POKE(0x2006, 0x21);
        POKE(0x2006, 0x4A + ((y + 1) * 32));
    }
}

int main(void) {
    // Disable interrupts
    __asm__("sei");
    
    // Wait for PPU to be ready
    wait_for_vblank();
    wait_for_vblank();
    
    // Disable PPU rendering
    POKE(0x2001, 0x00);
    
    // Load palette
    load_palette();
    
    // Clear screen
    clear_screen();
    
    // Draw pattern
    draw_pattern();
    
    // Reset PPU scroll
    POKE(0x2005, 0x00);
    POKE(0x2005, 0x00);
    
    // Enable PPU rendering (background only)
    POKE(0x2001, 0x08);
    
    // Main loop
    while (1) {
        wait_for_vblank();
        // Game logic would go here
    }
    
    return 0;
}
