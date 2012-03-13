#include "ColorPalette.h"
#include <stdio.h>

// Here goes member definition


//---------------------------------------------------------------
// Slot to subscribe for event.
// Expects to receive array of pointers on quadrilaterals instances which were recognized
//---------------------------------------------------------------

void ColorPalette::ProcessSquares (const vector*<Square*> recognizedSquares)
{
	//int number_of_elements = sizeof(recognizedSquares)/sizeof(Square *);

	//printf("number of squares: %d",number_of_elements);


}


//---------------------------------------------------------------
// Destructor.
// Releases used resources.
//---------------------------------------------------------------

ColorPalette::~ColorPalette ()
{

}

//void GetColor()
