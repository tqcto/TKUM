#pragma once

#ifndef TKUM_PRE_MANAGER_H
#define TKUM_PRE_MANAGER_H

#include <stdio.h>
#include <stdlib.h>

#include "TKUM_Parameter.h"

/**
@brief		management for SmartFx PreRender
@param	T	use to parameter struct in SmartFx
*/
template<typename T>
class PreManager : public Parameter {

private:
	PF_PreRenderExtra*	extra = nullptr;
	PF_RenderRequest*	req;

public:

	PreManager(PF_InData* in, PF_OutData* out, PF_PreRenderExtra* ex) : Parameter(in, out) {
	
		extra									= ex;
		req										= &extra->input->output_request;
		ex->output->delete_pre_render_data_func	= DisposeParameterStruct;

	}
	~PreManager(void) {

		extra	= nullptr;
		req		= nullptr;

	}

	PF_RenderRequest* GetRenderRequestP(void) const {
		return req;
	}

	void UseGPURender(void) {
		extra->output->flags |= PF_RenderOutputFlag_GPU_RENDER_POSSIBLE;
	}

	T* MallocParameterStruct(void) const {
		return reinterpret_cast<T*>(malloc(sizeof(T)));
	}

	static void	DisposeParameterStruct(void* pre_render_dataPV) {
		if (pre_render_dataPV) {
			T* infoP = reinterpret_cast<T*>(pre_render_dataPV);
			free(infoP);
		}
	}

	void SetParameterToPreRenderData(T* info) {
		extra->output->pre_render_data = info;
	}

	PF_Err CheckoutLayer(int id, PF_CheckoutResult* result) {
		return extra->cb->checkout_layer(
			in_data->effect_ref,
			id,
			id,
			req,
			in_data->current_time,
			in_data->time_step,
			in_data->time_scale,
			result
		);
	}

};

#endif // TKUM_PRE_MANAGER_H
