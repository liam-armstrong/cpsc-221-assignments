#include "borderColorPicker.h"

borderColorPicker::borderColorPicker(HSLAPixel fillColor, PNG & img, double tolerance,HSLAPixel center)
{
    color = fillColor;
    im = img;
    tol = tolerance;
    ctr = center;
}

HSLAPixel borderColorPicker::operator()(int x, int y)
{
    for(int a = -3; a <= 3; a++){
        for(int b = -3; b <= 3; b++){
            if(((b*b) + (a*a)) > 9) {
                continue;
            }
            if((x + a) >= (int)im.width() || (x + a) < 0 || (y + b) >= (int)im.height() || (y + b) < 0){
                return color;
            } else {
                HSLAPixel * p = im.getPixel((x + a),(y + b));
                if(p->h == color.h && p->l == color.l && p->s == color.s){
                    return color;
                }
            }
        }
    }
    return *im.getPixel(x, y);
}
