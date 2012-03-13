Project includes partial interface implementation.
Only basic public methods and events are declared.
It is up to you how much private methods you will define, what processing logic you will use.
It is strongly recommended to make conversation with colleagues before making serius changes to public interface.

Little bit about idea of how it shoud work.
At program launch, ICUBES instance is created. in ICUBES class constructor there is all module initialization.
Recognition module routines are started by invoking BEGIN_READ () which launches separate thread on which to
read from video stream. This is made so to separate GUI and processing routines.
Signals (Events) are used to notify other classes about quadrilaterals recognized/processed.
It is strongly recommended to make conversation with colleagues before extending/changing basic interface.

Simple process scheme:

App. launch:
	1) Main window created
	2) Logic/Recognition modules initialized

Frames processing routines:
	1) Reading video stream on separate thread
	2) After quadrilaterls recognized, according signal must be invoked (passing to it recognized quadrilaterals),
	to notify other classes.
	
Object processing routines:
	1) After being notified about recognized quadrilaterals, start to process them according described logic.
	2) Compute realtive size, coordinates, link object with required image to show.
	3) Notify GUI module about processed quadrilaterals, which are now replaced with virtual objects, representing
	physical objects.
	
Object display routines:
	1) After being notified, start to display virtua objects one by one