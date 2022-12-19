#pragma once

/**
* @file		TKUM.h
* @brief	include all managers header files.
* @author	Takt
*/

#ifndef TKUM_H
#define TKUM_H

//#include <vector>

#include "..\Headers\AE_Effect.h"
#include "..\Headers\AE_EffectSuites.h"
#include "..\Headers\AE_Macros.h"

/* Takt Utility Manager name space */
namespace TKUM {

#ifndef TKUM_RECT_H
#include "TKUM_Rect.h"
#endif

#ifndef TKUM_PARAMETER_H
#include "TKUM_Parameter.h"
#endif

#ifndef TKUM_PRE_MANAGER_H
#include "TKUM_PreManager.h"
#endif

}

#endif // TKUM_H
