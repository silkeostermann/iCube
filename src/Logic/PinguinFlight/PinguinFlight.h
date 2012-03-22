#ifndef PINGUIN_FLIGHT_H
#define PINGUIN_FLIGHT_H

#include "../../Recognition/Square.h"
#include "../Image.h"

#include <opencv/highgui.h>

#include <cstdio>

#include <QtGui/QImage>
#include <QtGui/QColor>
#include <QtGui/QPainter>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <QtGui/QTransform>
#include <QtCore/QRect>
#include <QThread>
#include <qobject.h>

//---------------------------------------------------------------
// Represents flying punguin. Punguing flapping the wings each next frame.
// By changing cube orientation (rotating cube), pinguin changes flight direction.  
//---------------------------------------------------------------

class PinguinFlight : public QObject
{
	Q_OBJECT

  	public:
		PinguinFlight();

	public slots:
		void ProcessSquares (const Square* squares, int size);

	signals:
		void SquaresProcessed (const Image* image, int size);

  	private:
    		Image m_background;

		QImage m_inclined0penguin_1, m_inclined0penguin_2,
			m_inclined90penguin_1, m_inclined90penguin_2, m_inclined180penguin_1,
			m_inclined180penguin_2, m_inclined270penguin_1, m_inclined270penguin_2;

    		int m_penguinWingsUp;

		static const int SCREEN_WIDTH = 600;
		static const int SCREEN_HEIGHT = 350;
};

#endif
