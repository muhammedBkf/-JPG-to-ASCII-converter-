#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>

#define RED 0.2126
#define Green 0.587
#define Blue 0.114

int main()
{
  std::string inputPath;
  std::string outputPath = "";
  //We choose the ascii characters we want to use 
  std::string ascii = "@#$=+|:. ";
 
  //We read the path to the image we want to convert
  //And we create the output .txt at the same location
  std::cout << "Write the path of the picture you want to convert : ";
  std::cin >> inputPath;
  for (char c : inputPath)
  {
    outputPath += c;
  }
  outputPath += ".txt";

  int scaleX;
  std::cout << "Choose the size (in px) that an ASCII character will represent : : ";
  std::cin >> scaleX;

 //We covert the image to grayscale
 //We consider the image as 2x2 matrix
 //we extract every pixel using a nested loop 
 //We turn each pixel into black and white using the RBG colors values in the greyscale system
  std::cout << "Conversion to black and white..." << std::endl;
  sf::Image img;
  img.loadFromFile(inputPath);
  sf::Image grayImg(img);
  int c;
  for (int i = 0; i < img.getSize().x; i++)
  {
    for (int j = 0; j < img.getSize().y; j++)
    {
      c = img.getPixel(i, j).r * RED + img.getPixel(i, j).g * Green + img.getPixel(i, j).b * Blue;
      grayImg.setPixel(i, j, sf::Color(c, c, c));
    }
  }
  grayImg.saveToFile("gray.png");
  std::cout << "Done !" << std::endl;

//We convert the image to lowRes
  std::cout << "Conversion to low resolution..." << std::endl;
  int scaleY = 2 * scaleX;  
  sf::Image greyLowResImg(img);
  int grey = 0;
  for (int i(0); i < img.getSize().x - scaleX; i += scaleX)
  {
    for (int j(0); j < img.getSize().y - scaleY; j += scaleY)
    {
      for (int x(0); x < scaleX; x++)
      {
        for (int y(0); y < scaleY; y++)
        {
          grey += grayImg.getPixel(i + x, j + y).r;
        }
      }
      grey /= scaleX * scaleY + 1;
      for (int x(0); x < scaleX; x++)
      {
        for (int y(0); y < scaleY; y++)
        {
          greyLowResImg.setPixel(i + x, j + y, sf::Color(grey, grey, grey));
        }
      }
    }
  }
  std::cout << "Done !" << std::endl;

//We convert it to ascii code according to the lowRes image
  std::cout << "Conversion to ASCII..." << std::endl;
  std::string asciiArt;

  for (int j(0); j < greyLowResImg.getSize().y; j += scaleY)
  {
    for (int i(0); i < greyLowResImg.getSize().x; i += scaleX)
    {
      asciiArt += ascii[(int)(greyLowResImg.getPixel(i, j).r / 255.f * ascii.size())];
    }
    asciiArt += "\n";
  }
  
  std::ofstream output(outputPath);
  if (output)
    output << asciiArt;
  std::cout << "Finished ! You will find the result at : " << outputPath << std::endl;
  return 0;
}
