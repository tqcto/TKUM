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

	PF_InData*					in_data				= nullptr;
	PF_OutData*					out_data			= nullptr;
	PF_SmartRenderExtra*		extra				= nullptr;

	bool						is_input_checkouted	= false;
	std::vector<int>			layer_datas;

	void init(void) {
		err = PF_Err_NONE;
	}

public:

	SmartFXManager(PF_InData* in, PF_OutData* out, PF_SmartRenderExtra* ex) {

		in_data = in;
		out_data = out;
		extra = ex;

		init();

	}
	~SmartFXManager(void) {

		if (layer_datas.size()) {
			for (auto &itr:layer_datas) {
				CheckinLayer(itr);
			}
		}

		in_data = nullptr;
		out_data = nullptr;
		extra = nullptr;

	}

	template<typename T> T* GetPreRenderData(void) const {

		return reinterpret_cast<T*>(extra->input->pre_render_data);

	}

	PF_Err CheckoutLayer(int id, PF_EffectWorld** world) {

		init();

		err = extra->cb->checkout_layer_pixels(in_data->effect_ref, id, world);

		if (!err) layer_datas.push_back(id);

		return err;

	}

	PF_Err CheckoutOutput(PF_EffectWorld** output) {

		return extra->cb->checkout_output(in_data->effect_ref, output);

	}

	PF_Err CheckinLayer(int id) {

		init();

		while (layer_datas.size()) {

		}

		for (auto itr = layer_datas.begin(); itr != layer_datas.end();) {
			if (*itr == id) {
				err = extra->cb->checkin_layer_pixels(in_data->effect_ref, id);
				if (!err) layer_datas.erase(itr);
			}
		}

		return err;

	}

};

#endif
