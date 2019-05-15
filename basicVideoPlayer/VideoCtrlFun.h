#pragma once
#include <string>
#include "opencv2\opencv.hpp"
#include "CvvImage.h"
#include "video_Thread.h"
#include "yolo_v2_class.hpp"
class VideoFuncClass
{
private:
	cv::VideoCapture cap;
	HDC hDCForVideo;
	RECT videoRect;
	CvvImage vImg;
	Capture video_thread;
	Detector detector;

public:
	int detectFrame;
	VideoFuncClass() : detector("yolov3.cfg", "yolov3_test_608x352_alpha_114608.weights") {}
	BOOL VideoOpen(const std::string fileName);
	void VideoPlay();
	void VideoStop();

	HDC* GetLPHDC() { return &hDCForVideo; }
	void SetHDC(HDC hdc) {hDCForVideo = hdc; }
	RECT* GetLPRect() { return &videoRect; }
};