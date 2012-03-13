#ifndef VIDEO_STREAM_PROCESSOR_H
#define VIDEO_STREAM_PROCESSOR_H

#include "Square.h"
#include <qobject.h>
#include <vector>
using namespace std;

//---------------------------------------------------------------
// Represents web camera stream reader, processor.
//---------------------------------------------------------------

// frame processor
class FrameProcessor : public QObject
{
	Q_OBJECT

	public:
		void BeginRead (int webCamId, int fps);
		void EndRead ();

		~FrameProcessor ();

	signals:
	// squares recognized
		void SquaresRecognized (const vector*<Square*> recognizedQuadrilaterals);
};

#endif
