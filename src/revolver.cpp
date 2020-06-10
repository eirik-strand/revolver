#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <stdio.h>
using namespace cv;
using namespace std;
int main(int, char **) {
  Mat frame;
  //--- INITIALIZE VIDEOCAPTURE
  VideoCapture cap;
  // open the default camera using default API
  // cap.open(0);
  // OR advance usage: select any API backend
  int deviceID = 0;        // 0 = open default camera
  int apiID = cv::CAP_ANY; // 0 = autodetect default API
  // open selected camera using selected API
  cap.open(deviceID, apiID);
  // check if we succeeded
  if (!cap.isOpened()) {
    cerr << "ERROR! Unable to open camera\n";
    return -1;
  }
  //--- GRAB AND WRITE LOOP
  cout << "Start grabbing" << endl << "Press any key to terminate" << endl;
  for (;;) {
    // wait for a new frame from camera and store it into 'frame'
    cap.read(frame);
    // check if we succeeded
    if (frame.empty()) {
      cerr << "ERROR! blank frame grabbed\n";
      break;
    }
    // show live and wait for a key with timeout long enough to show images
    Mat gray;
    cv::cvtColor(frame, frame, CV_BGR2GRAY);
    threshold(frame, gray, 100, 255, CV_THRESH_BINARY);

    Mat out;
    gray.copyTo(out);
    std::vector<bool> row1;
    std::vector<bool> row2;
    std::vector<bool> row3;
    std::vector<bool> row4;
    std::vector<bool> row5;
    std::vector<bool> row6;
    std::vector<bool> row7;
    std::vector<bool> row8;

    for (int r = 0; r < out.rows; r++) {
      for (int c = 0; c < out.cols; c++) {
        if (c > out.cols / 2 - 20 && c < out.cols / 2 + 20) {
          // Row1
          if (r < 100 && r > 50) {
            if (out.at<bool>(r, c) == 255)
              row1.push_back(true);
          }
          // Row2
          if (r < 135 && r > 100) {
            if (out.at<bool>(r, c) == 255)
              row2.push_back(true);
          }
          // Row3
          if (r < 187 && r > 135) {
            if (out.at<bool>(r, c) == 255)
              row3.push_back(true);
          }
          // Row4
          if (r < 233 && r > 187) {
            if (out.at<bool>(r, c) == 255)
              row4.push_back(true);
          }
          // row5
          if (r < 290 && r > 233) {
            if (out.at<bool>(r, c) == 255)
              row5.push_back(true);
          }
          // row6
          if (r < 340 && r > 290) {
            if (out.at<bool>(r, c) == 255)
              row6.push_back(true);
          }
          // row7
          if (r < 390 && r > 340) {
            if (out.at<bool>(r, c) == 255)
              row7.push_back(true);
          }
          // row8
          if (r < 440 && r > 390) {
            if (out.at<bool>(r, c) == 255)
              row8.push_back(true);
          }

        } else {
          out.at<uchar>(r, c) = 255; // white
        }
      }
    }
    bool r1 = row1.size() > 500;
    bool r2 = row2.size() > 500;
    bool r3 = row3.size() > 500;
    bool r4 = row4.size() > 500;
    bool r5 = row5.size() > 500;
    bool r6 = row6.size() > 500;
    bool r7 = row7.size() > 500;
    bool r8 = row8.size() > 500;

    std::cout << row1.size() << std::endl;
    std::cout << row2.size() << std::endl;
    std::cout << row3.size() << std::endl;
    std::cout << row4.size() << std::endl;
    std::cout << row5.size() << std::endl;
    std::cout << row6.size() << std::endl;
    std::cout << row7.size() << std::endl;
    std::cout << row8.size() << std::endl << std::endl;

    double rot = 360.0;
    double angle = rot / 2 * r2 + rot / 4 * r2 + rot / 8 * r3 + rot / 16 * r4 +
                   rot / 32 * r5 + rot / 64 * r6 + rot / 128 * r7 +
                   rot / 256 * r8;

    std::cout << "angle: " << angle << std::endl << std::endl;

    imshow("Live", out);
    if (waitKey(5) >= 0)
      break;
  }
  return 0;
}
