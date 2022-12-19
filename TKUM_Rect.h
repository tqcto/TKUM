#pragma once

#ifndef TKUM_RECT_H
#define TKUM_RECT_H

#include "TKUM.h"

#define RECT2INT4(_RECT_)	{ _RECT_.left, _RECT_.top, _RECT_.right, _RECT_.bottom }

/**
* @fn
* @brief				[Only to use in FrameSetup] Set to new a layer data size
* @param	in_data		>> input data
* @param	params		>> parameter data
* @param	new_size	>> [not need to consider down sample] set size by this param
* @param	out_data	<< output data
* @return				Error data
*/
PF_Err SetRect(PF_InData* in_data, PF_ParamDef** params, PF_Rect new_size, PF_OutData* out_data) {

	double dx = static_cast<double>(in_data->downsample_x.num) / in_data->downsample_x.den;
	double dy = static_cast<double>(in_data->downsample_y.num) / in_data->downsample_y.den;

	new_size.left	*= dx;
	new_size.right	*= dx;
	new_size.top	*= dy;
	new_size.bottom	*= dy;

	out_data->width		= new_size.left	+ new_size.right	+ params[0]->u.ld.width;
	out_data->height	= new_size.top	+ new_size.bottom	+ params[0]->u.ld.height;

	out_data->origin.h = new_size.left;
	out_data->origin.v = new_size.top;

	return PF_Err_NONE;

}
/**
* @fn
* @brief				[Only to use in FrameSetup] Set to new a layer data size
* @param	in_data		>> input data
* @param	params		>> parameter data
* @param	new_size	>> [not need to consider down sample] set size by this param
* @param	out_data	<< output data
* @return				Error data
*/
PF_Err SetRect(PF_InData* in_data, PF_ParamDef** params, int new_size, PF_OutData* out_data) {

	int sx = static_cast<int>(static_cast<double>(new_size) * static_cast<double>(in_data->downsample_x.num) / in_data->downsample_x.den);
	int sy = static_cast<int>(static_cast<double>(new_size) * static_cast<double>(in_data->downsample_y.num) / in_data->downsample_y.den);

	out_data->width		= (sx << 1) + params[0]->u.ld.width;
	out_data->height	= (sy << 1) + params[0]->u.ld.height;

	out_data->origin.h = sx;
	out_data->origin.v = sy;

	return PF_Err_NONE;

}
/**
* @fn
* @brief				[Only to use in FrameSetup] Set to new a layer data size
* @param	in_data		>> input data
* @param	new_size	>> [not need to consider down sample] set size by this param
* @param	out_data	<< output data
* @return				Error data
*/
PF_Err SetRect(PF_InData* in_data, int new_size, PF_OutData* out_data) {

	double dx = static_cast<double>(in_data->downsample_x.num) / in_data->downsample_x.den;
	double dy = static_cast<double>(in_data->downsample_y.num) / in_data->downsample_y.den;

	int sx = static_cast<int>(static_cast<double>(new_size) * dx);
	int sy = static_cast<int>(static_cast<double>(new_size) * dy);

	out_data->width		= (sx << 1) + static_cast<int>(static_cast<double>(in_data->width)	* dx);
	out_data->height	= (sy << 1) + static_cast<int>(static_cast<double>(in_data->height)	* dy);

	out_data->origin.h = sx;
	out_data->origin.v = sy;

	return PF_Err_NONE;

}

/**
* @fn
* @brief				Get source rectangle and dest rectangle
* @param	in_data		>> input data
* @param	input		>> input layer data
* @param	output		>> output layer data
* @param	in_rect		<< store source rectangle
* @param	in_rect		<< store dest rectangle
* @return				Error data
*/
PF_Err GetRect(PF_InData* in_data, PF_LayerDef* input, PF_LayerDef* output, PF_Rect* in_rect, PF_Rect* out_rect) {

	in_rect->left		= input->origin_x;
	in_rect->top		= input->origin_y;
	in_rect->right		= input->width;
	in_rect->bottom		= input->height;

	out_rect->left		= in_data->output_origin_x;
	out_rect->top		= in_data->output_origin_y;
	out_rect->right		= in_data->output_origin_x + output->width;
	out_rect->bottom	= in_data->output_origin_y + output->height;

	return PF_Err_NONE;

}

#endif // TKUM_RECT_H
