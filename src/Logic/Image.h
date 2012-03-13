#ifndef OBJECT_H
#define OBJECT_H

#include <qimage.h>
#include <qpoint.h>
#include <qstring.h>

//---------------------------------------------------------------
// Represents object defined by logic
//---------------------------------------------------------------

class Image
{
	public:
		Image (QImage image, const QPoint& imageRelativeCoordinates);

		QPoint GetImageRelativeCoordinates () const;
		QImage image;

		~Image ();
};

#endif
