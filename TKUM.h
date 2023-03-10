#pragma once

/**
* @file		TKUM.h
* @brief	include all managers header files.
* @author	Takt
*/

#ifndef TKUM_H
#define TKUM_H

//#define _TEST_SMART_FX_LAYER_

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "..\Headers\AE_Effect.h"
#include "..\Headers\AE_EffectSuites.h"
#include "..\Headers\AE_Macros.h"
#include "..\Headers\AE_EffectPixelFormat.h"
#include "..\Headers\AE_EffectCBSuites.h"
#include "..\Headers\AEFX_SuiteHandlerTemplate.h"

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

#ifndef TKUM_SMART_FX_MANAGER_H
#include "TKUM_SmartFXManager.h"
#endif

}

#endif // TKUM_H
