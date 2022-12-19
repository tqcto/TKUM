#pragma once

#ifndef TKUM_SMART_FX_MANAGER_H
#define TKUM_SMART_FX_MANAGER_H

#include "TKUM.h"

/**
@brief		management for SmartFx Render
*/
class SmartFXManager {

private:

	PF_Err						err					= PF_Err_NONE;
	PF_ParamDef					param;

	PF_InData*					in_data				= nullptr;
	PF_OutData*					out_data			= nullptr;
	PF_SmartRenderExtra*		extra				= nullptr;

	PF_EffectWorld				*input				= nullptr,
								*output				= nullptr;

	bool						is_input_checkouted	= false;
	std::vector<PF_ParamDef*>	layer_datas;

	void init(void) {
		err = PF_Err_NONE;
		AEFX_CLR_STRUCT(param);
	}

public:

	SmartFXManager(PF_InData* in, PF_OutData* out, PF_SmartRenderExtra* ex) {

		in_data = in;
		out_data = out;
		extra = ex;

		init();

	}
	~SmartFXManager(void) {

		in_data = nullptr;
		out_data = nullptr;
		extra = nullptr;

		if (is_input_checkouted) CheckinInput();

		if (layer_datas.size()) {



		}

	}

	PF_Err CheckoutInput(PF_EffectWorld* input) {

		AEFX_SuiteScoper<PF_WorldSuite2> world_suite = AEFX_SuiteScoper<PF_WorldSuite2>(in_data,
			kPFWorldSuite,
			kPFWorldSuiteVersion2,
			out_data);

		PF_PixelFormat	pixel_format = PF_PixelFormat_INVALID;
		ERR(world_suite->PF_GetPixelFormat(input, &pixel_format));

		return extra->cb->checkout_layer_pixels(in_data->effect_ref, 0, &input);

	}

	PF_Err CheckoutOutput(PF_EffectWorld* output) {

		return extra->cb->checkout_output(in_data->effect_ref, &output);

	}

	PF_Err CheckoutLayer(int id, int frame, PF_EffectWorld* world) {

		init();

		err = PF_CHECKOUT_PARAM(
			in_data,
			id,
			frame * in_data->time_step,
			in_data->time_step,
			in_data->time_scale,
			&param
		);

		if (err) return err;

		*world = param.u.ld;
		layer_datas.push_back(&(param.u.ld));

		return err;

	}

	PF_Err CheckinInput(void) {

		return extra->cb->checkin_layer_pixels(in_data->effect_ref, 0);

	}

};

#endif
