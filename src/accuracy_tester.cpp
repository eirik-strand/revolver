#include "opencv2/imgproc/imgproc.hpp"
#include <bitset>
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
  int deviceID = 1;        // 0 = open default camera
  int apiID = cv::CAP_ANY; // 0 = autodetect default API
  // open selected camera using selected API
  cap.open(deviceID, apiID);
  // check if we succeeded
  if (!cap.isOpened()) {
    cerr << "ERROR! Unable to open camera\n";
    return -1;
  }

  std::cout << "MJPG: "
            << cap.set(cv::CAP_PROP_FOURCC,
                       cv::VideoWriter::fourcc('M', 'J', 'P', 'G'))
            << std::endl;
  cap.set(CV_CAP_PROP_FRAME_WIDTH, 4208);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, 3120);
  cap.set(CV_CAP_PROP_FPS, 30);
  // cap.set(CV_CAP_PROP_AUTO_EXPOSURE, true);
  // cap.set(CV_CAP_PROP_EXPOSURE, 25000);
  // cap.set(CV_CAP_PROP_XI_AUTO_WB, true);

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
    int64_t counter = 0;

    for (int x = 0; x < frame.rows; x++) {
      for (int y = 0; y < frame.cols; y++) {
        counter += (int)frame.at<uchar>(x, y) - 1.0 / 3.0;
      }
    }
    counter -= frame.rows * frame.cols;
    cout << counter << endl;
    imshow("Live", frame);

    if (waitKey(5) >= 0)
      break;
  }

  return 0;
}
