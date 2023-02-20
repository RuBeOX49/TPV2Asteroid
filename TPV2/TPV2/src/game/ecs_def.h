#pragma once
#ifndef ECS_H_
#define ECS_H_

using cmpId_type = int;
enum cmpId : cmpId_type {
	_TRANSFORM = 0,
	_DEACCELERATION,
	_IMAGE,
	_HEALTH,
	_FIGHTERCTRL,
	_GUN,
	_SHOWATOPPOSITESIDE,
	_FRAMED_IMG,
	_GENERATIONS,
	_FOLLOW,
	_DISABLEONEXIT,
	// ... (compoment ids)

	// do not remove this
	_LAST_CMP_ID
};
constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

#endif // !ECS_H_