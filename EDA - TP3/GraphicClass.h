#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>


class GraphicClass {
public:

	//GraphicClass constructor.
	GraphicClass(unsigned int width, unsigned int height);

	bool createDisplay(void);

	ALLEGRO_DISPLAY* getDisplay(void);

	void destroyGraphics(void);
	void setFontName(const char* fontName_);
	bool loadFont(void);;

private:

	ALLEGRO_DISPLAY* display;
	ALLEGRO_FONT* font;
	ALLEGRO_COLOR fontColor;
	unsigned int width;
	unsigned int height;
	const char* fontName;
};