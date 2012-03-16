#include "Image.h"


// Here goes member definition


//---------------------------------------------------------------
// Constructor.
// Expects to receive valid image relative path, otherwise set error.
// Expects to receive valid coordinates on palette, otherwise set error.
// Expects to receive valid image width and height, otherwise set error.
// Initializes members.
//---------------------------------------------------------------

Image::Image ()
{
	QImage image;
	QPoint imageRelativeCoordinates; 
}

//---------------------------------------------------------------

Image::Image (QImage img, QPoint imgRelativeCoordinates)
{
	image = img;
	imageRelativeCoordinates = imgRelativeCoordinates;
}

//---------------------------------------------------------------

Image& Image::operator=(const Image& img)
{
	image = img.image;
	imageRelativeCoordinates = img.imageRelativeCoordinates;
	return *this;
} 


//---------------------------------------------------------------
// Destructor.
// Releases used resoruces.
//---------------------------------------------------------------

Image::~Image ()
{

}
