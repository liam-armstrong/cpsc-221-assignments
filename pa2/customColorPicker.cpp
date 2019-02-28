#include "customColorPicker.h"
#include <math.h>

using std::pair;
using std::map;

customColorPicker::customColorPicker()
{
}

HSLAPixel customColorPicker::operator()(int x, int y)
{
    if(x % 3 == 0 || y % 3 == 0){
        return rcp(x,y);
    } else {
        HSLAPixel white;
        white.l = 1;
        return white; 
    }
}