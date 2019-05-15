#include "stdafx.h"
#include "VideoCtrlFun.h"


BOOL VideoFuncClass::VideoOpen(const std::string fileName)
{
	cap.open(fileName);
	if (!cap.isOpened()) {
		AfxMessageBox(_T("Can't open File"));	
		return FALSE;
	}

	return TRUE;
}

void VideoFuncClass::VideoPlay()
{
	video_thread.numDetect = detectFrame;
	video_thread.run(cap, vImg, hDCForVideo, videoRect, detector);
}


void VideoFuncClass::VideoStop()
{
	video_thread.stop();
}
