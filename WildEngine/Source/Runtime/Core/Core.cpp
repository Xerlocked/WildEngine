#include "CorePrivate.h"

#define LOCTEXT_NAMESPACE "Core"

float					GNearClippingPlane				= 10.0f;					/* Near clipping plane */
/** Timestep if a fixed delta time is wanted.																*/
double					GFixedDeltaTime					= 1 / 30.f;
/** Current delta time in seconds.																			*/
double					GDeltaTime						= 1 / 30.f;
/** Current unclamped delta time in seconds.																*/
double					GUnclampedDeltaTime				= 1 / 30.f;
/* Current time																								*/
double					GCurrentTime					= 0;						
/* Last GCurrentTime																						*/
double					GLastTime						= 0;						

bool					GExitPurge						= false;

#undef LOCTEXT_NAMESPACE