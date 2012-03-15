#ifndef VIDEO_STREAM_PROCESSOR_H
#define VIDEO_STREAM_PROCESSOR_H

#include "Square.h"
#include <qthread.h>

//---------------------------------------------------------------
// Represents web camera stream reader, processor.
//---------------------------------------------------------------

// frame processor
class FrameProcessor : public QThread
{
	Q_OBJECT

	public:
		void BeginRead (int webCamId, int fps);
		void EndRead ();

		void run ();

		~FrameProcessor ();

	signals:
		void SquaresRecognized (const Square**, int);
};

#endif
