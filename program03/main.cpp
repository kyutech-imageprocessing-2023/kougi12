#include <iostream>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

void display(cv::Mat image, std::string windowName = "Image") {
    cv::namedWindow(windowName);
    cv::imshow(windowName, image);
    cv::waitKey(1000 * 100);
    cv::destroyWindow(windowName);
}

int main(int argc, char* argv[]){

  if( argc != 2 ){
    std::cout << "main <filename>" << std::endl;
    exit(0);
  }

  cv::Mat src = cv::imread(argv[1], 0);
  display(src, "src");

  cv::Mat edge; 
  cv::Canny(src, edge, 500, 200, 3);

  display(edge, "edge");

  std::vector<cv::Vec2f> lines;
  cv::HoughLines(edge, lines, 0.7, CV_PI / 180, 50);

  cv::Mat dst;
  cv::cvtColor(src, dst, cv::COLOR_GRAY2BGR);

  for (auto line : lines){
    // line[0]: rho
    // line[1]: theta
    std::cout << line << std::endl;
    //
    float rho = line[0];
    float theta = line[1];
    cv::Point pt1, pt2;
    float a = cos(theta), b = sin(theta);
    float x0 = a * rho, y0 = b * rho;
    pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
    pt1.y = cv::saturate_cast<int>(y0 + 1000 * (a));
    pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
    pt2.y = cv::saturate_cast<int>(y0 - 1000 * (a));
    cv::line(dst, pt1, pt2, cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
  }
  display(dst, "dst");

  return 0;
}

