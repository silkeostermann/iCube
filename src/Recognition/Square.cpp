#include "Square.h"


// Here goes member definition


//---------------------------------------------------------------
// Constructor.
// Expects to receive valid unique identifier, quadrilateral center coordinates and size.
// Initializes members.
//---------------------------------------------------------------

Square::Square (int id, const CvPoint& centerCoordinates, int width, int height)
{
	this->centerCoordinates = centerCoordinates;
}

//---------------------------------------------------------------

int Square::GetId () const
{

}

//---------------------------------------------------------------

int Square::GetWidth () const
{

}

//---------------------------------------------------------------

int Square::GetHeight () const
{

}


//---------------------------------------------------------------
// Destructor.
// Releases used resources.
//---------------------------------------------------------------

Square::~Square ()
{
}
