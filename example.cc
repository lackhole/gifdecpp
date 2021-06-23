//
// Created by YongGyu Lee on 2021/06/22.
//

#include <iostream>
#include <string>

#include "opencv2/opencv.hpp"

#include "gifdec/gifdec.h"

#ifdef WIN32
#define EXAMPLE_SEP '\\'
#else
#define EXAMPLE_SEP '/'
#endif

# define PWD                                                  \
[](){                                                         \
  std::string $13vlaae_dummy_str = __FILE__;                  \
  return $13vlaae_dummy_str.substr(                           \
    0, $13vlaae_dummy_str.find_last_of(EXAMPLE_SEP)); \
}()


int main() {
  gif::GIFDecoder dec(PWD + EXAMPLE_SEP + "parrot.gif");
  if (!dec.is_open()) {
    std::cerr << "Failed to open file\n";
    return EXIT_FAILURE;
  }

  cv::Mat buffer(dec.height(), dec.width(), CV_8UC3);
  cv::Mat frame;

  std::vector<cv::Mat> frames;
  while(dec.grab_next_rgb(buffer.data)) {
    cv::cvtColor(buffer, frame, cv::COLOR_RGB2BGR);
    frames.emplace_back(frame.clone());
  }

  for(int i=0;; i = (i + 1) % frames.size()) {
    cv::imshow("PARTY PARROT", frames[i]);

    if (cv::waitKey(33) == 27 /* ESC */)
      break;
  }
  return 0;

  /*
  while(true) {
    if (!dec.grab_next_rgb(buffer.data))
      dec.rewind();

    cv::cvtColor(buffer, frame, cv::COLOR_RGB2BGR);
    cv::imshow("PARTY PARROT", frame);

    if (cv::waitKey(33) == 27)
      break;
  }
  */

  return 0;
}

