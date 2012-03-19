#include "FrameProcessor.h"

//---------------------------------------------------------------
// Expects there are subscribers on "QuadrilateralsRecognized" signal.
// If stream is not already opened and if it is possible to start
// reading stream for specified camera, starts reading.
//---------------------------------------------------------------

void FrameProcessor::BeginRead (int webCamId, int fps)
{
	if (fps <= 0)
		return;

	if (isRunning ())
		return;

	m_cameraId = webCamId;
	m_sleepTimeBetweenFramesMs = 1000 / fps;
	start ();
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

void FrameProcessor::run ()
{
  CvCapture* capture = cvCaptureFromCAM (m_cameraId);
  vector <Square> cubes;

  while (true)
  {
    IplImage* img = cvQueryFrame (capture);
    if (!img)
    {
      printf("Capture failed!\n");
      sleep(1);
      continue;
    }

    DetectAndDrawQuads (img, cubes);
    Square* squareArr = new Square [cubes.size()];

    for (unsigned int i = 0; i < cubes.size(); i++)
    {
      squareArr [i] = cubes [i];
    }

    printf("Squares recognized: %d\n", cubes.size());

    if (cubes.size() == 0) {
    	continue;
    }

    emit SquaresRecognized (&(cubes [0]), cubes.size ());
    msleep (m_sleepTimeBetweenFramesMs);

    cubes.clear ();
    delete [] squareArr;
  }
  cvReleaseCapture (&capture);
}

//---------------------------------------------------------------

void FrameProcessor::DetectAndDrawQuads(IplImage* img, vector <Square>& cubes)
{
	CvSeq* contours;
	CvSeq* result;
	CvMemStorage *storage = cvCreateMemStorage(0);

	IplImage* ret = cvCreateImage(cvGetSize(img), 8, 3);
	IplImage* temp = cvCreateImage(cvGetSize(img), 8, 1);

	cvCvtColor(img, temp, CV_BGR2GRAY);

	IplImage* Img = cvCreateImage (cvGetSize (img), 8, 1);
	cvThreshold(temp, Img, 0, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);

	cvFindContours(Img, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
	CvSeq* contours1 = contours;
	while(contours)
    {
		result = cvApproxPoly (contours, sizeof (CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter (contours) * 0.02, 0);

		if((result->total==4)  && (fabs(cvContourArea(result, CV_WHOLE_SEQ)) > 30) && cvCheckContourConvexity (result))
        {
	  int countTriang = 0;   
	  CvSeq* contours2 = contours1;
	  
	  while(contours2){
	    
	    CvSeq* result2 = cvApproxPoly(contours2, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours2)*0.02, 0);
	    if((result2->total==3) && (fabs(cvContourArea(result2, CV_WHOLE_SEQ)) > 50) && cvCheckContourConvexity(result2)) 
	      {
		CvPoint *pt[3];
		for(int i=0;i<3;i++)
		  pt[i] = (CvPoint*)cvGetSeqElem(result2, i);
		
		CvPoint ptCent[1];
		ptCent[0].x = (pt[0]->x + pt[1]->x + pt[2]->x)/3;
		ptCent[0].y = (pt[0]->y + pt[1]->y + pt[2]->y)/3;
		
		//cvCircle(ret, ptCent[0], 5, cvScalar(255));
		
		CvPoint2D32f triang;
		triang.x = ptCent[0].x;
		triang.y = ptCent[0].y;
		
		if(cvPointPolygonTest(result, triang, 0)  > 0){
		  countTriang++;
		  cvLine(ret, *pt[0], *pt[1], cvScalar(30, 50, 50));
		  cvLine(ret, *pt[1], *pt[2], cvScalar(30, 50, 50));
		  cvLine(ret, *pt[2], *pt[0], cvScalar(30, 50, 50));
		  
		}
	      }
	    
	    contours2 = contours2->h_next;
	  }
	  
	  if(countTriang == 1){
	    CvPoint *pt[4];
	    for(int i=0;i<4;i++)
	      pt[i] = (CvPoint*)cvGetSeqElem(result, i);
	    
	    cvLine(ret, *pt[0], *pt[1], cvScalar(255));
	    cvLine(ret, *pt[1], *pt[2], cvScalar(255));
	    cvLine(ret, *pt[2], *pt[3], cvScalar(255));
	    cvLine(ret, *pt[3], *pt[0], cvScalar(255));
	    
	    CvSeq* contours3 = contours1;
	    int countSquare = 0;
	    while(contours3){
	      CvSeq* result3 = cvApproxPoly(contours3, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours3)*0.02, 0);
	      if((result3->total==4) && (fabs(cvContourArea(result3, CV_WHOLE_SEQ)) > 50) && cvCheckContourConvexity(result3)) 
		{
		  CvPoint *pt[4];
		  for(int i=0;i<4;i++)
		    pt[i] = (CvPoint*)cvGetSeqElem(result3, i);
		  
		  CvPoint ptCent[1];
		  ptCent[0].x = (pt[0]->x + pt[1]->x + pt[2]->x + pt[3]->x)/4;
		  ptCent[0].y = (pt[0]->y + pt[1]->y + pt[2]->y + pt[3]->y)/4;
		  
		  //cvCircle(ret, ptCent[0], 5, cvScalar(255));
		  
		  CvPoint2D32f square;
		  square.x = ptCent[0].x;
		  square.y = ptCent[0].y;
		  
		  //cout << cvPointPolygonTest(result, triang, 0);
		  if(cvPointPolygonTest(result, square, 0)  > 0){
		    countSquare++;
		    cvLine(ret, *pt[0], *pt[1], cvScalar(90, 50, 50));
		    cvLine(ret, *pt[1], *pt[2], cvScalar(90, 50, 50));
		    cvLine(ret, *pt[2], *pt[3], cvScalar(90, 50, 50));
		    cvLine(ret, *pt[3], *pt[0], cvScalar(90, 50, 50));
		    
		  }
		}
	      contours3 = contours3->h_next;
	    }
	    countSquare--;
	    
	    CvPoint *pt1[4];
	    for(int i=0;i<4;i++)
	      pt1[i] = (CvPoint*)cvGetSeqElem(result, i);
	    
	    CvPoint ptCent[1];
	    ptCent[0].x = (pt1[0]->x + pt1[1]->x + pt1[2]->x + pt1[3]->x)/4;
	    ptCent[0].y = (pt1[0]->y + pt1[1]->y + pt1[2]->y + pt1[3]->y)/4;
	    
	    cvCircle(ret, ptCent[0], 5, cvScalar(255));
	    
	    CvPoint pC[1];
	    pC[0].x = ptCent[0].x;
	    pC[0].y = ptCent[0].y;
	    
	    Square test3 (countSquare, pC [0], abs(pt1[0]->x - pC[0].x) * 1.5, abs(pt1[0]->x - pC[0].x) * 1.5);
	    cubes.push_back(test3);
	  }
        }
      
      contours = contours->h_next;
    }

	cvReleaseImage(&temp);
	cvReleaseImage(&ret);
	cvReleaseImage(&Img);
	cvReleaseMemStorage(&storage);
}


//---------------------------------------------------------------
// Destructor.
// Releases used resources.
//---------------------------------------------------------------

FrameProcessor::~FrameProcessor ()
{
  EndRead ();
}
