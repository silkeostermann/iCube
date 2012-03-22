#include "PinguinFlight.h"

PinguinFlight::PinguinFlight()
{
	m_penguinWingsUp = true;

	m_background = Image (QImage ("./Logic/PinguinFlight/northpole.jpg"), 
					QPoint (1, 1));

	m_inclined0penguin_1 = QImage ("./Logic/PinguinFlight/pinguin0a.png");
	m_inclined0penguin_2 = QImage ("./Logic/PinguinFlight/pinguin0b.png");

	m_inclined90penguin_1 = QImage ("./Logic/PinguinFlight/pinguin90a.png");
	m_inclined90penguin_2 = QImage ("./Logic/PinguinFlight/pinguin90b.png");

	m_inclined180penguin_1 = QImage ("./Logic/PinguinFlight/pinguin180a.png");
	m_inclined180penguin_2 = QImage ("./Logic/PinguinFlight/pinguin180b.png");

	m_inclined270penguin_1 = QImage ("./Logic/PinguinFlight/pinguin270a.png");
	m_inclined270penguin_2 = QImage ("./Logic/PinguinFlight/pinguin270b.png");
}

//---------------------------------------------------------------

void PinguinFlight::ProcessSquares (const Square *recognizedSquares, int size)
{
  	printf ("[PinguinFlight] ProcessSquares\n");
  
	Image* images = new Image [size];
	for (int i = 0; i < size; i++)
	{
		QImage* img;
		if (recognizedSquares [i].GetAngle () == 0)
		{
			if (m_penguinWingsUp)
				img = &m_inclined0penguin_1;
			else
				img = &m_inclined0penguin_2;
		}
		else if (recognizedSquares [i].GetAngle () == 90)
		{
			if (m_penguinWingsUp)
				img = &m_inclined90penguin_1;
			else
				img = &m_inclined90penguin_2;
		}
		else if (recognizedSquares [i].GetAngle () == 180)
		{
			if (m_penguinWingsUp)
				img = &m_inclined180penguin_1;
			else
				img = &m_inclined180penguin_2;
		}
		else if (recognizedSquares [i].GetAngle () == 270)
		{
			if (m_penguinWingsUp)
				img = &m_inclined270penguin_1;
			else 
				img = &m_inclined270penguin_2;
		}

		CvPoint coord = recognizedSquares [i].GetCenterCoordinates ();
		coord.x = coord.x  * (SCREEN_WIDTH / 100);
		coord.y = coord.y * (SCREEN_HEIGHT / 100);

		images [i] = Image (*img, QPoint (coord.x, coord.y));

		printf ("[PinguinFlight] Image number %d (%d;%d)\n", i,
			images [i].imageRelativeCoordinates.x (),
			images [i].imageRelativeCoordinates.y ());
	}

	m_penguinWingsUp = !m_penguinWingsUp;

	emit SquaresProcessed (&m_background, 1);
	emit SquaresProcessed (images, size);

	delete [] images;
}
