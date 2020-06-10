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

    for (int r = 0; r < out.rows; r++) {
      for (int c = 0; c < out.cols; c++) {
        if (c > out.cols / 2 - 20 && c < out.cols / 2 + 20) {
        } else {
          out.at<uchar>(r, c) = 255; // white
        }
      }
    }

    imshow("Live", out);
    if (waitKey(5) >= 0)
      break;
  }
  return 0;
}
