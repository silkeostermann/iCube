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
		Image (QImage img, const QPoint& imgRelativeCoordinates);

		QPoint imageRelativeCoordinates;
		QImage image;

		~Image ();
};

#endif
