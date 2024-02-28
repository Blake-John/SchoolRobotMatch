#include "readcolor.h"
#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <vector>

int main() {
  std::string path = "../../ColorRange.txt";
  std::vector<std::vector<cv::Scalar>> colors;
  colors = readcolor(path);
  /* for (auto i : colors) { */
  /*   for (auto j : i) { */
  /*     std::cout << j << std::endl; */
  /*   } */
  /* } */

  return 0;
}
