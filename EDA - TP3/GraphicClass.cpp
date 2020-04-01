#include "GraphicClass.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>


#define FONTSIZE 40

//GraphicClass constructor.
GraphicClass::GraphicClass(unsigned int width_, unsigned int height_) :
	
    height(height_), width(width_){

    this->display = nullptr;
    this->font = nullptr;
}

//Attempts to create display. Returns true if successful. 
bool GraphicClass::createDisplay(void) {
    return (this->display = al_create_display(width, height));
}

//Sets font name.
void GraphicClass::setFontName(const char* fontName_) { this->fontName = fontName_; }

//Gets display.
ALLEGRO_DISPLAY* GraphicClass::getDisplay(void) { return this->display; }

//Frees memory.
void GraphicClass::destroyGraphics(void) {
    if (this->font)
        al_destroy_font(this->font);
    if (this->display)
        al_destroy_display(this->display);
}

//Attempts to load font. Returns false if unsuccessful.
bool GraphicClass::loadFont(void) {  
    return (this->font = al_load_ttf_font(this->fontName, FONTSIZE, 0));
}


