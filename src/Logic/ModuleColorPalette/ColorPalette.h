#ifndef OBJECT_PROCESSOR_H
#define OBJECT_PROCESSOR_H

#include <cstdio>

#include "../Image.h"
#include "../../Recognition/Square.h"

#include <qobject.h>
#include <QtGui/QImage>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <QtGui/QPainter>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <QtCore/QRect>

//---------------------------------------------------------------
// Represents logic implementation, such strange name because no concrete logic chosen yet
//---------------------------------------------------------------

class ColorPalette : public QObject
{
	Q_OBJECT

	private:
		QImage *m_interface;
		QImage *m_ball;
		QImage *m_redBar;
		QImage *m_greenBar;
		QImage *m_blueBar;

	public:
		ColorPalette();
		~ColorPalette();

	public slots:
		void ProcessSquares (const Square*, int size);

	signals:
		void SquaresProcessed (const Image*, int size);

};

#endif
