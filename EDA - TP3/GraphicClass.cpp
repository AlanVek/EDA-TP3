#include "GraphicClass.h"
//#include <allegro5/allegro_primitives.h>
//#include <allegro5/allegro_ttf.h>


#define FONTSIZE 40
#define backgrBit "background.jpg"

//GraphicClass constructor.
GraphicClass::GraphicClass(unsigned int width_, unsigned int height_) :
	
    height(height_), width(width_){

    this->display = nullptr;
    this->backgroundBitmap = nullptr;
    //this->font = nullptr;
}

//Attempts to create display. Returns true if successful. 
bool GraphicClass::createDisplay(void) {
    return (this->display = al_create_display(width, height));
}

//Sets font name.
//void GraphicClass::setFontName(const char* fontName_) { this->fontName = fontName_; }

//Gets display.
ALLEGRO_DISPLAY* GraphicClass::getDisplay(void) { return this->display; }

//Frees memory.
void GraphicClass::destroyGraphics(void) {
    /*if (this->font)
        al_destroy_font(this->font);*/
    if (this->display)
        al_destroy_display(this->display);
    if (this->backgroundBitmap)
        al_destroy_bitmap(this->backgroundBitmap);
}

/*//Attempts to load font. Returns false if unsuccessful.
bool GraphicClass::loadFont(void) {  
    return (this->font = al_load_ttf_font(this->fontName, FONTSIZE, 0));
}*/



bool GraphicClass::setBackground(unsigned int width_,unsigned int height_) {
    bool result = true;
    if (!(this->backgroundBitmap = al_create_bitmap(width_, height_))) {
        std::cout << "Failed to create background bitmap\n";
        result = false;
    }
    else if (!(this->backgroundBitmap = al_load_bitmap(backgrBit))) {
        std::cout << "Failed to load background bitmap\n";
        result = false;
    }
    return result;
}
void GraphicClass::drawBackgrBit(void) {
    al_draw_bitmap(this->backgroundBitmap, 0, 0, 0);
}
