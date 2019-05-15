#pragma once
#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>
#include<minwindef.h>
#include <mutex>
#include <Windows.h>
#include "CvvImage.h"
#include "yolo_v2_class.hpp"
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include "imgCrawling.h"
using namespace std;
using namespace cv;
static std::mutex mtx;

static int outputidx = 0;

class Dass {

public:
	std::thread thread;
	
public:
	Rect RangeCheck(int width, int height, Rect InTagetRect)
	{
		int x = InTagetRect.x;
		int y = InTagetRect.y;
		int rectWidth = InTagetRect.width;
		int rectHeight = InTagetRect.height;

		if (x < 0)
			x = 0;

		if (y < 0)
			y = 0;

		if (width - 1 <= x + rectWidth)
			rectWidth = rectWidth - ((x + rectWidth) - width);

		if (height - 1 <= y + rectHeight)
			rectHeight = rectHeight - ((y + rectHeight) - height);

		return Rect(x, y, rectWidth, rectHeight);
	}
	void MakeCellFrameImage(cv::Mat &InSourceImageFileName, Rect InTagetRect)
	{
		Mat subImage = InSourceImageFileName(RangeCheck(InSourceImageFileName.cols, InSourceImageFileName.rows, InTagetRect));
		imwrite("./result/copy_" + to_string(outputidx) + ".png", subImage);		
	}

	void imgToText(cv::Mat &frame, std::vector<bbox_t> &result_temp) {
		for (auto &v : result_temp)
		{
			MakeCellFrameImage(frame, Rect(v.x, v.y, v.w, v.h));
		}
	}

	void run(cv::Mat &frame, std::vector<bbox_t> &result_temp) {
			thread = std::thread{ &Dass::imgToText, this, frame, result_temp };
	}

	inline void join() { if (thread.joinable()) thread.join(); };
	inline void stop() {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		if (thread.joinable()) {
			thread.join();
		}
	}
};


class Capture {
private:
	int count = 0;
	void draw_boxes(cv::Mat mat_img, std::vector<bbox_t> result_vec) {
		for (auto &i : result_vec) {
			if (i.prob > 0.50) {
				cv::rectangle(mat_img, cv::Rect(i.x, i.y, i.w, i.h), cv::Scalar(255, 0, 0), 3);				
			}
		}
	}

private:
	bool running;
	std::thread thread;
	Dass dass;
	Crawling crawling;

	void loop(cv::VideoCapture &cap, CvvImage &vImg, HDC hDCForVideo, RECT &videoRect, Detector &det) {		
		bool out = false;
		while (running) {
			count++;
			cv::Mat frame;
			cap >> frame; // get a new frame from camera
			if (frame.empty())
			{
				break;
				out = true;
			}				

			std::vector<bbox_t> result_vec = det.detect(frame, 0.9);

			cv::Mat output;
			frame.copyTo(output);
			draw_boxes(output, result_vec);

			IplImage* image = new IplImage(output);

			vImg.CopyOf(image);
			vImg.DrawToHDC(hDCForVideo, &videoRect);

			if (count % (numDetect / 2) == 0)
			{
				dass.stop();
				cv::Mat temp;
				frame.copyTo(temp);
				std::vector<bbox_t> result_temp;
				for (auto a : result_vec)
					result_temp.push_back(a);				
				dass.run(temp, result_temp);				
			}

			if (count % numDetect == 0)
			{
				crawling.run();
			}
		}	

		if (out)
			stop();
	}
public:
	int numDetect;
	Capture() :
		running{ false },
		thread{}
	{
		crawling.Init();
	}
	inline ~Capture() {
		if (running) stop(); // stop and join the thread
	}
	void run(cv::VideoCapture &cap, CvvImage &vImg, HDC hDCForVideo, RECT &videoRect, Detector &det) {
		if (!running) {
			running = true;
			thread = std::thread{ &Capture::loop, this, cap, vImg, hDCForVideo, videoRect, det };
		}
	}
	inline void join() { if (thread.joinable()) thread.join(); };
	inline void stop() {
		running = false;
		dass.stop();
		crawling.stop();
		crawling.Print();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		if (thread.joinable()) {
			thread.join();
		}
	}
};
