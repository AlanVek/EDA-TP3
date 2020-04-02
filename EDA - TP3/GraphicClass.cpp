#include "GraphicClass.h"
//#include <allegro5/allegro_primitives.h>
//#include <allegro5/allegro_ttf.h>


#define babyBitmap "babyblob.png"
#define grownBitmap "grownblob.png"
#define goodOldBitmap "goodoldblob.png"
#define foodBitmap "food.png"
#define backgrBitmap "background.jpg"



//GraphicClass constructor.
GraphicClass::GraphicClass(unsigned int width_, unsigned int height_) :
	
    height(height_), width(width_){

    this->display = nullptr;
    this->backgroundBit = nullptr;

    this->babyBit = nullptr;
    this->grownBit = nullptr;

    this->goodOldBit= nullptr;
    this->foodBit = nullptr;
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
    if (this->backgroundBit)
        al_destroy_bitmap(this->backgroundBit);

    if (this->babyBit)
        al_destroy_bitmap(this->babyBit);
    if (this->grownBit)
        al_destroy_bitmap(this->grownBit);
    if (this->goodOldBit)
        al_destroy_bitmap(this->goodOldBit);
    if (this->foodBit)
        al_destroy_bitmap(this->foodBit);
}

/*//Attempts to load font. Returns false if unsuccessful.
bool GraphicClass::loadFont(void) {  
    return (this->font = al_load_ttf_font(this->fontName, FONTSIZE, 0));
}*/

//Creates a bitmap, stores it in thisBit and loads it with bitName.
bool GraphicClass::createBitmap(unsigned int W, unsigned int H, const char* bitName, ALLEGRO_BITMAP*& thisBit){
    bool result = true;

    if (!(thisBit = al_create_bitmap(W, H)))
        result = false;
    else if (!(thisBit = al_load_bitmap(bitName)))
        result = false;
    return result;
}

//Frees memory taken up by bitmap.
void GraphicClass::deleteBitmap(ALLEGRO_BITMAP* thisBit) {
    if (thisBit)
        al_destroy_bitmap(thisBit);
}

//Draw a bitmap at position (x,y).
void GraphicClass::drawBitmap(ALLEGRO_BITMAP*& thisBit, float X, float Y) { al_draw_bitmap(thisBit,X,Y, 0); }


//Bitmap getters.
ALLEGRO_BITMAP*& GraphicClass::getBabyBit(void) { return this->babyBit; }
ALLEGRO_BITMAP*& GraphicClass::getGrownBit(void) { return this->grownBit; }
ALLEGRO_BITMAP*& GraphicClass::getGoodBit(void) { return this->goodOldBit; }
ALLEGRO_BITMAP*& GraphicClass::getBackgrBit(void) { return this->backgroundBit; }
ALLEGRO_BITMAP*& GraphicClass::getFoodBit(void) { return this->foodBit; }


//Creates and loads all bitmaps.
bool GraphicClass::initializeBitmaps(unsigned int width_, unsigned int height_) {
    bool result = true;
    
    if (!this->createBitmap(width_, height_, babyBitmap, this->babyBit))
        result = false;
    else if (!this->createBitmap(width_, height_, grownBitmap, this->grownBit))
        result = false;
    else if (!(this->createBitmap(width_, height_, goodOldBitmap, this->goodOldBit)))
        result = false;
    else if (!(this->createBitmap(width_, height_, foodBitmap, this->foodBit)))
        result = false;
    else if (!(this->createBitmap(width_, height_, backgrBitmap,  this->backgroundBit)))
        result = false;

    return result;
}