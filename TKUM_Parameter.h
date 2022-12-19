#pragma once

#ifndef TKUM_PARAMETER_H
#define TKUM_PARAMETER_H

#include "AE_Effect.h"
#include "AE_EffectSuites.h"

#define TKUM_CHECKOUT_PARAM(IN_DATA, ID, PARAM)		PF_CHECKOUT_PARAM(IN_DATA, ID, IN_DATA->current_time, IN_DATA->time_step, IN_DATA->time_scale, PARAM)

#define COUDNT_LOAD_SUITE_STR	"can't load suite"

/* responsible for set/get parameters */
class Parameter {

protected:

	PF_InData*	in_data		= nullptr;
	PF_OutData*	out_data	= nullptr;

	PF_Err		err			= PF_Err_NONE;
	PF_ParamDef	param;

	void init(void) {
		err = PF_Err_NONE;
		AEFX_CLR_STRUCT(param);
	}

	PF_Err checkOutParam(int id) {
		return TKUM_CHECKOUT_PARAM(in_data, id, &param);
	}

public:

	Parameter(PF_InData* in, PF_OutData* out) {

		in_data		= in;
		out_data	= out;
		init();

	}
	~Parameter(void) {

		in_data		= nullptr;
		out_data	= nullptr;

	}

	PF_Err GetPoint(int id, A_FloatPoint* value) {

		init();
		ERR(checkOutParam(id));

		PF_PointParamSuite1* suite;
		ERR(AEFX_AcquireSuite(
			in_data,
			out_data,
			kPFPointParamSuite,
			kPFPointParamSuiteVersion1,
			COUDNT_LOAD_SUITE_STR,
			(void**)&suite)
		);

		ERR(suite->PF_GetFloatingPointValueFromPointDef(in_data->effect_ref, &param, value));

		ERR(PF_CHECKIN_PARAM(in_data, &param));

		return err;

	}

	PF_Err GetAngle(int id, double* value) {

		init();
		ERR(checkOutParam(id));

		PF_AngleParamSuite1* suite;
		ERR(AEFX_AcquireSuite(
			in_data, out_data,
			kPFAngleParamSuite,
			kPFAngleParamSuiteVersion1,
			COUDNT_LOAD_SUITE_STR,
			(void**)&suite)
		);

		ERR(suite->PF_GetFloatingPointValueFromAngleDef(in_data->effect_ref, &param, value));

		ERR(PF_CHECKIN_PARAM(in_data, &param));

		return err;

	}

	PF_Err GetPopup(int id, int* value) {

		init();
		ERR(checkOutParam(id));

		*value = param.u.pd.value;

		ERR(PF_CHECKIN_PARAM(in_data, &param));

		return err;

	}

	PF_Err GetFloatSlider(int id, double* value) {

		init();
		ERR(TKUM_CHECKOUT_PARAM(in_data, id, &param));

		*value = param.u.fs_d.value;

		ERR(PF_CHECKIN_PARAM(in_data, &param));

		return err;

	}

	PF_Err GetIntSlider(int id, int* value) {

		init();
		ERR(TKUM_CHECKOUT_PARAM(in_data, id, &param));

		*value = param.u.sd.value;

		ERR(PF_CHECKIN_PARAM(in_data, &param));

		return err;

	}

	PF_Err GetCheckbox(int id, bool* value) {

		init();
		ERR(TKUM_CHECKOUT_PARAM(in_data, id, &param));

		*value = param.u.bd.value;

		ERR(PF_CHECKIN_PARAM(in_data, &param));

		return err;

	}

	PF_Err GetColor(int id, PF_Pixel32* value) {

		init();
		ERR(TKUM_CHECKOUT_PARAM(in_data, id, &param));
		AEGP_SuiteHandler suites(in_data->pica_basicP);

		ERR(suites.ColorParamSuite1()->PF_GetFloatingPointColorFromColorDef(
			in_data->effect_ref,
			&param,
			value
		));

		ERR(PF_CHECKIN_PARAM(in_data, &param));

		return err;

	}

};

#endif // TKUM_PARAMETER_H
