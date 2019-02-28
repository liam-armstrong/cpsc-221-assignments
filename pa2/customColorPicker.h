#ifndef CUSTOMCOLORPICKER_H
#define CUSTOMCOLORPICKER_H

#include <stdint.h>
#include <map>
#include <utility>
#include "colorPicker.h"
#include "rainbowColorPicker.h"

/**
 * rainbowColorPicker: a functor that determines the color that should be used
 * given an x and a y coordinate using a rainbow pattern.
 *
 */
class customColorPicker : public colorPicker
{
  public:
    /**
     * Constructs a new rainbowColorPicker.
     *
     */
    customColorPicker();

    /**
     * Picks the color for pixel (x, y).
     *
     * @param x The x coordinate to pick a color for.
     * @param y The y coordinat to pick a color for.
     * @return The color chosen for (x, y).
     */
    virtual HSLAPixel operator()(int x, int y);

  private:
    rainbowColorPicker rcp = rainbowColorPicker(1.0/1000.0);
};

#endif
