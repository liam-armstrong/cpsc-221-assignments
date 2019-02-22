#include "block.h"

void Block::build(PNG & im, int column, int width){
  for (int x = column; x < column + width; x++) {
      vector<HSLAPixel> temp;
      for (unsigned y = 0; y < im.height(); y++) {
          HSLAPixel *pixel = im.getPixel(x, y);
          temp.push_back(*pixel);
      }
      data.push_back(temp);
  } 
}
 
void Block::render(PNG & im, int column) const{
  for (int x = 0; x < width(); x++) {
      for (unsigned y = 0; y < im.height(); y++) {
          HSLAPixel *pixel = im.getPixel(column + x, y);
          *pixel = data[x][y];
      }
  } 
}

void Block::greyscale(){
  for (int x = 0; x < width(); x++) {
      for (int y = 0; y < height(); y++) {
          data.at(x).at(y).s = 0;
      }
  } 
}

int Block::width() const{
    return data.size();
}

int Block::height() const{
    if(data.empty()){
      return 0;
    } else {
      return data[0].size();
    }
}
