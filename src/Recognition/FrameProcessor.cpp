#include "FrameProcessor.h"


// Here goes member definition


//---------------------------------------------------------------
// Expects there are subscribers on "QuadrilateralsRecognized" signal,
// otherwise set error.
// Gets web camera id which from which to read.
// Gets frames per second to read.
// If stream is not already opened and if it is possible to start
// reading stream for specified camera, starts reading.
//---------------------------------------------------------------

void FrameProcessor::BeginRead (int webCamId, int fps)
{
	// TIP: Launch Run () method on separate thread
}


//---------------------------------------------------------------
// Stops reading stream if was reading.
// Releases used resources.
//---------------------------------------------------------------

void FrameProcessor::EndRead ()
{
	// TIP: Close all streams, stop thread
}


//---------------------------------------------------------------
// Destructor.
// Releases used resources.
//---------------------------------------------------------------

FrameProcessor::~FrameProcessor ()
{

}
