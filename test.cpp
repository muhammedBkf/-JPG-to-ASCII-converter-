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
  int scaleX;
  std::string ascii = "@#$=+|:. ";

  std::cout << "Write the path of the picture you want to convert : ";
  std::cin >> inputPath;
  for (char c : inputPath)
  {
    outputPath += c;
  }
  outputPath += ".txt";

  std::cout << "Choose the size (in px) that an ASCII character will represent : : ";
  std::cin >> scaleX;
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
  std::cout << "Conversion to low resolution..." << std::endl;
  int scaleY = 2 * scaleX;  // letters spacing in notePad works best with these settings
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