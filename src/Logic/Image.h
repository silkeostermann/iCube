#ifndef OBJECT_H
#define OBJECT_H

#include <qimage.h>
#include <qpoint.h>
#include <qobject.h>

//---------------------------------------------------------------
// Represents object defined by logic
//---------------------------------------------------------------

class Image : public QObject
{
	Q_OBJECT

	public:
		Image();
		Image(QImage img, QPoint imgRelativeCoordinates);

		Image& operator=(const Image& img);

		QPoint imageRelativeCoordinates;
		QImage image;

		~Image ();
};

#endif
