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

	bool						is_input_checkouted	= false;
	std::vector<PF_EffectWorld*>	layer_datas;

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

		if (is_input_checkouted) CheckinInput();

		if (layer_datas.size()) {
			for (auto itr = layer_datas.begin(); itr != layer_datas.end(); itr++) {
				CheckinLayer(*itr);
			}
		}

		in_data = nullptr;
		out_data = nullptr;
		extra = nullptr;

	}

	template<typename T> T* GetPreRenderData(void) const {

		return reinterpret_cast<T*>(extra->input->pre_render_data);

	}

	PF_Err CheckoutInput(PF_EffectWorld** input, PF_PixelFormat* format) {

		err = extra->cb->checkout_layer_pixels(in_data->effect_ref, 0, input);

		if (err) return err;

		is_input_checkouted = true;

		AEFX_SuiteScoper<PF_WorldSuite2> world_suite = AEFX_SuiteScoper<PF_WorldSuite2>(
			in_data,
			kPFWorldSuite,
			kPFWorldSuiteVersion2,
			out_data
		);

		ERR(world_suite->PF_GetPixelFormat(*input, format));

		return err;

	}

	PF_Err CheckoutOutput(PF_EffectWorld** output) {

		return extra->cb->checkout_output(in_data->effect_ref, output);

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
		layer_datas.push_back(&param.u.ld);

		return err;

	}

	PF_Err CheckinInput(void) {

		init();

		err = extra->cb->checkin_layer_pixels(in_data->effect_ref, 0);
		if (err) return err;

		is_input_checkouted = false;

		return err;

	}

	PF_Err CheckinLayer(PF_EffectWorld* checkouted_param) {

		init();

		for (auto itr = layer_datas.begin(); itr != layer_datas.end(); itr++) {
			if ((*itr) == checkouted_param) {
				layer_datas.erase(itr);
			}
		}

		param.u.ld = *checkouted_param;
		err = PF_CHECKIN_PARAM(in_data, &param);

		return err;

	}

};

#endif
