#ifndef VIDEO_STREAM_PROCESSOR_H
#define VIDEO_STREAM_PROCESSOR_H

#include "Square.h"
#include <qobject.h>
#include <qthread.h> 
#include <vector>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "../Logic/ModuleColorPalette/ColorPalette.h"

using namespace std;

//---------------------------------------------------------------
// Represents web camera stream reader, processor.
//---------------------------------------------------------------

class FrameProcessor : public QThread
{
	Q_OBJECT

	public:
		void BeginRead(int webCamId, int fps);
		void EndRead();

		void run();

		void DetectAndDrawQuads(IplImage* img, vector <Square>& squares);

		~FrameProcessor ();

	signals:
		// squares recognized
		void SquaresRecognized(const Square*, int);

	private:
		int m_sleepTimeBetweenFramesMs;
		int m_cameraId;

		float Euclid_dist(CvPoint*, CvPoint*);
		float GetAngle(CvPoint **);
};

#endif
