#include "opencv2/imgproc/imgproc.hpp"
#include <bitset>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

uint GrayToBinary32(uint num) {

  num ^= num >> 16;
  num ^= num >> 8;
  num ^= num >> 4;
  num ^= num >> 2;
  num ^= num >> 1;
  return num;
}

int main(int, char **) {
  Mat frame;
  //--- INITIALIZE VIDEOCAPTURE
  VideoCapture cap;
  // open the default camera using default API
  // cap.open(0);
  // OR advance usage: select any API backend
  int deviceID = 1;        // 0 = open default camera
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

    std::vector<int> calibration{0, 65, 125, 180, 252, 314, 380, 445, 500};
    int width = 45;
    int separation = 20;
    for (int r = 0; r < out.rows; r++) {
      for (int c = 0; c < out.cols; c++) {
        if (c > out.cols / 2 - width && c < out.cols / 2 + width) {
          // Row1
          if (r < calibration[1] - separation / 2 &&
              r > calibration[0] + separation / 2) {
            if (out.at<bool>(r, c) == 255)
              row1.push_back(true);
          }
          // Row2
          if (r < calibration[2] - separation / 2 &&
              r > calibration[1] + separation / 2) {
            if (out.at<bool>(r, c) == 255)
              row2.push_back(true);
          }
          // Row3
          if (r < calibration[3] - separation / 2 &&
              r > calibration[2] + separation / 2) {
            if (out.at<bool>(r, c) == 255)
              row3.push_back(true);
          }
          // Row4
          if (r < calibration[4] - separation / 2 &&
              r > calibration[3] + separation / 2) {
            if (out.at<bool>(r, c) == 255)
              row4.push_back(true);
          }
          // row5
          if (r < calibration[5] - separation / 2 &&
              r > calibration[4] + separation / 2) {
            if (out.at<bool>(r, c) == 255)
              row5.push_back(true);
          }
          // row6
          if (r < calibration[6] - separation / 2 &&
              r > calibration[5] + separation / 2) {
            if (out.at<bool>(r, c) == 255)
              row6.push_back(true);
          }
          // row7
          if (r < calibration[7] - separation / 2 &&
              r > calibration[6] + separation / 2) {
            if (out.at<bool>(r, c) == 255)
              row7.push_back(true);
          }
          // row8
          if (r < calibration[8] - separation / 2 &&
              r > calibration[7] + separation / 2) {
            if (out.at<bool>(r, c) == 255)
              row8.push_back(true);
          }

        } else {
          out.at<uchar>(r, c) = 255; // white
        }
      }
    }
    bool r1 = row1.size() < 1300;
    bool r2 = row2.size() < 1300;
    bool r3 = row3.size() < 1300;
    bool r4 = row4.size() < 1300;
    bool r5 = row5.size() < 1300;
    bool r6 = row6.size() < 1300;
    bool r7 = row7.size() < 1300;
    bool r8 = row8.size() < 600;

    std::cout << row1.size() << std::endl;
    std::cout << row2.size() << std::endl;
    std::cout << row3.size() << std::endl;
    std::cout << row4.size() << std::endl;
    std::cout << row5.size() << std::endl;
    std::cout << row6.size() << std::endl;
    std::cout << row7.size() << std::endl;
    std::cout << row8.size() << std::endl << std::endl;

    std::cout << r1 << std::endl;
    std::cout << r2 << std::endl;
    std::cout << r3 << std::endl;
    std::cout << r4 << std::endl;
    std::cout << r5 << std::endl;
    std::cout << r6 << std::endl;
    std::cout << r7 << std::endl;
    std::cout << r8 << std::endl << std::endl;

    double rot = 360.0;
    double angle = rot / 2 * r1 + rot / 4 * r2 + rot / 8 * r3 + rot / 16 * r4 +
                   rot / 32 * r5 + rot / 64 * r6 + rot / 128 * r7 +
                   rot / 256 * r8;

    angle = rot - angle;

    Rect Rec1(out.cols / 2 - width, calibration[0], width * 2,
              calibration[1] - calibration[0]);
    Rect Rec2(out.cols / 2 - width, calibration[1], width * 2,
              calibration[2] - calibration[1]);
    Rect Rec3(out.cols / 2 - width, calibration[2], width * 2,
              calibration[3] - calibration[2]);
    Rect Rec4(out.cols / 2 - width, calibration[3], width * 2,
              calibration[4] - calibration[3]);
    Rect Rec5(out.cols / 2 - width, calibration[4], width * 2,
              calibration[5] - calibration[4]);
    Rect Rec6(out.cols / 2 - width, calibration[5], width * 2,
              calibration[6] - calibration[5]);
    Rect Rec7(out.cols / 2 - width, calibration[6], width * 2,
              calibration[7] - calibration[6]);
    Rect Rec8(out.cols / 2 - width, calibration[7], width * 2,
              calibration[8] - calibration[7]);

    rectangle(out, Rec1, Scalar(180), separation, 8, 0);
    rectangle(out, Rec2, Scalar(180), separation, 8, 0);
    rectangle(out, Rec3, Scalar(180), separation, 8, 0);
    rectangle(out, Rec4, Scalar(180), separation, 8, 0);
    rectangle(out, Rec5, Scalar(180), separation, 8, 0);
    rectangle(out, Rec6, Scalar(180), separation, 8, 0);
    rectangle(out, Rec7, Scalar(180), separation, 8, 0);
    rectangle(out, Rec8, Scalar(180), separation, 8, 0);

    putText(out, to_string(r1),
            Point(out.cols / 2 + width + 10, calibration[1] - 25),
            FONT_HERSHEY_SIMPLEX, 1, Scalar(180), 8);
    putText(out, to_string(r2),
            Point(out.cols / 2 + width + 10, calibration[2] - 25),
            FONT_HERSHEY_SIMPLEX, 1, Scalar(180), 8);
    putText(out, to_string(r3),
            Point(out.cols / 2 + width + 10, calibration[3] - 25),
            FONT_HERSHEY_SIMPLEX, 1, Scalar(180), 8);
    putText(out, to_string(r4),
            Point(out.cols / 2 + width + 10, calibration[4] - 25),
            FONT_HERSHEY_SIMPLEX, 1, Scalar(180), 8);
    putText(out, to_string(r5),
            Point(out.cols / 2 + width + 10, calibration[5] - 25),
            FONT_HERSHEY_SIMPLEX, 1, Scalar(180), 8);
    putText(out, to_string(r6),
            Point(out.cols / 2 + width + 10, calibration[6] - 25),
            FONT_HERSHEY_SIMPLEX, 1, Scalar(180), 8);
    putText(out, to_string(r7),
            Point(out.cols / 2 + width + 10, calibration[7] - 25),
            FONT_HERSHEY_SIMPLEX, 1, Scalar(180), 8);
    putText(out, to_string(r8),
            Point(out.cols / 2 + width + 10, calibration[8]),
            FONT_HERSHEY_SIMPLEX, 1, Scalar(180), 8);

    std::string bitstring = to_string(r1) + to_string(r2) + to_string(r3) +
                            to_string(r4) + to_string(r5) + to_string(r6) +
                            to_string(r7) + to_string(r8);

    uint8_t bits = std::stoi(bitstring, nullptr, 2);
    angle = GrayToBinary32(bits) * 360 / 256;
    double perc = row8.size() / 1200.0;
    if (!r8)
      angle += perc;

    std::cout << "angle: " << angle << std::endl << std::endl;

    putText(out, "Angle: " + to_string(angle), Point(out.cols - 200, 30),
            FONT_HERSHEY_SIMPLEX, 1, Scalar(0), 2);

    imshow("Live", out);

    if (waitKey(5) >= 0)
      break;
  }
  return 0;
}
