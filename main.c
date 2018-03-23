#include <stdio.h>
#include "functions.h"

int main() {
  Image img;
  img = readImage(img);

  int n_opcoes;
  scanf("%d", &n_opcoes);

  for(int i = 0; i < n_opcoes; ++i) {
      int opcao;
      scanf("%d", &opcao);

      switch(opcao) {
          case 1: {
              img = grayScale(img);
              break;
          }
          case 2: {
              img = sepia(img);
              break;
          }
          case 3: {
              img = blur(img);
              break;
          }
          case 4: {
              img = numberOfRotations(img);
              break;
          }
          case 5: {
              img = mirroring(img);
              break;
          }
          case 6: {
              img = negativeColors(img);
              break;
          }
          case 7: {
              img = cutImage(img);
              break;
          }
      }

  }

  printImage(img);
  return 0;
}


Image readImage(Image img){

  // Read type of image.
  char p3[4];
  scanf("%s", p3);

  // Read width, height and color of image.
  int max_color;
  scanf("%u %u %d", &img.width, &img.height, &max_color);

  // read all pixels of image
  for (unsigned int i = 0; i < img.height; ++i) {
      for (unsigned int j = 0; j < img.width; ++j) {
          scanf("%hu %hu %hu", &img.pixel[i][j][0],
                               &img.pixel[i][j][1],
                               &img.pixel[i][j][2]);
      }
  }
  return img;
}

void printImage(Image img){
  // print type of image
  printf("P3\n");
  // print width height and color of image
  printf("%u %u\n255\n", img.width, img.height);

  // print pixels of image
  for (unsigned int i = 0; i < img.height; ++i) {
      for (unsigned int j = 0; j < img.width; ++j) {
          printf("%hu %hu %hu ", img.pixel[i][j][0],
                                 img.pixel[i][j][1],
                                 img.pixel[i][j][2]);

      }
      printf("\n");
  }
}


Image grayScale(Image img) {
    
    for (unsigned int i = 0; i < img.height; ++i) {
        for (unsigned int j = 0; j < img.width; ++j) {
            int media = img.pixel[i][j][0] +
                        img.pixel[i][j][1] +
                        img.pixel[i][j][2];
            media /= 3;
            img.pixel[i][j][0] = media;
            img.pixel[i][j][1] = media;
            img.pixel[i][j][2] = media;
        }
    }

    return img;
}

Image blur(Image img) {
  int size = 0;
  scanf("%d", &size);

  for (unsigned int i = 0; i < img.height; ++i) {
    for (unsigned int j = 0; j < img.width; ++j) {
      Pixel media = {0, 0, 0};

      unsigned int min_height = (img.height - 1 > i + size/2) ? i + size/2 : img.height - 1;
      unsigned int min_width = (img.width - 1 > j + size/2) ? j + size/2 : img.width - 1;
      for(int x = (0 > i - size/2 ? 0 : i - size/2); x <= min_height; ++x) {
          for(int y = (0 > j - size/2 ? 0 : j - size/2); y <= min_width; ++y) {
              media.r += img.pixel[x][y][0];
              media.g += img.pixel[x][y][1];
              media.b += img.pixel[x][y][2];
          }
      }

      // printf("%u", media.r)
      media.r /= size * size;
      media.g /= size * size;
      media.b /= size * size;

      img.pixel[i][j][0] = media.r;
      img.pixel[i][j][1] = media.g;
      img.pixel[i][j][2] = media.b;
    }
  }
  return img;
}

Image rotate90Right(Image img) {
  Image rotated;

  rotated.width = img.height;
  rotated.height = img.width;

  for (unsigned int i = 0, y = 0; i < rotated.height; ++i, ++y) {
    for (int j = rotated.width - 1, x = 0; j >= 0; --j, ++x) {
      rotated.pixel[i][j][0] = img.pixel[x][y][0];
      rotated.pixel[i][j][1] = img.pixel[x][y][1];
      rotated.pixel[i][j][2] = img.pixel[x][y][2];
    }
  }
  return rotated;
}

Image numberOfRotations(Image img){
  int numbers = 0;
  scanf("%d", &numbers);
  numbers %= 4;
  for (int j = 0; j < numbers; ++j) {
      img = rotate90Right(img);
  }
  return img;
}

Image mirroring(Image img){
  int horizontal = 0;
  scanf("%d", &horizontal);

  int width = img.width, height = img.height;

  if (horizontal == 1) width /= 2;
  else height /= 2;

  for (int i2 = 0; i2 < height; ++i2) {
      for (int j = 0; j < width; ++j) {
          int x = i2, y = j;

          if (horizontal == 1) y = img.width - 1 - j;
          else x = img.height - 1 - i2;

          Pixel aux1;
          aux1.r = img.pixel[i2][j][0];
          aux1.g = img.pixel[i2][j][1];
          aux1.b = img.pixel[i2][j][2];

          img.pixel[i2][j][0] = img.pixel[x][y][0];
          img.pixel[i2][j][1] = img.pixel[x][y][1];
          img.pixel[i2][j][2] = img.pixel[x][y][2];

          img.pixel[x][y][0] = aux1.r;
          img.pixel[x][y][1] = aux1.g;
          img.pixel[x][y][2] = aux1.b;
      }
  }
  return img;
}

Image negativeColors(Image img) {
    for (unsigned int i = 0; i < img.height; ++i) {
        for (unsigned int j = 0; j < img.width; ++j) {
            img.pixel[i][j][0] = 255 - img.pixel[i][j][0];
            img.pixel[i][j][1] = 255 - img.pixel[i][j][1];
            img.pixel[i][j][2] = 255 - img.pixel[i][j][2];
      }
    }
    return img;
}

Image cutImage(Image img){

    int x, y;
    scanf("%d %d", &x, &y);
    int w, h;
    scanf("%d %d", &w, &h);

    Image cutted;
    cutted.width = w;
    cutted.height = h;

    for(int i = 0; i < h; ++i) {
      for(int j = 0; j < w; ++j) {
          cutted.pixel[i][j][0] = img.pixel[i + y][j + x][0];
          cutted.pixel[i][j][1] = img.pixel[i + y][j + x][1];
          cutted.pixel[i][j][2] = img.pixel[i + y][j + x][2];
      }
    }
    return cutted;
}

Image sepia(Image img){

  for (unsigned int x = 0; x < img.height; ++x) {
      for (unsigned int j = 0; j < img.width; ++j) {
          unsigned short int pixel[3];
          pixel[0] = img.pixel[x][j][0];
          pixel[1] = img.pixel[x][j][1];
          pixel[2] = img.pixel[x][j][2];

          int p =  pixel[0] * .393 + pixel[1] * .769 + pixel[2] * .189;
          int menor_r = (255 >  p) ? p : 255;
          img.pixel[x][j][0] = menor_r;

          p =  pixel[0] * .349 + pixel[1] * .686 + pixel[2] * .168;
          menor_r = (255 >  p) ? p : 255;
          img.pixel[x][j][1] = menor_r;

          p =  pixel[0] * .272 + pixel[1] * .534 + pixel[2] * .131;
          menor_r = (255 >  p) ? p : 255;
          img.pixel[x][j][2] = menor_r;
      }
  }
  return img;
}
