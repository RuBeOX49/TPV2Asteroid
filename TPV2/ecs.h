#pragma once
#include <cstdint>
#ifndef ecs
#define ecs
using cmpId_type = int;
enum cmpId : cmpId_type {
	_TRANSFORM = 0,
	_IMAGE,
	_CTRL,
	// do not remove this
	_LAST_CMP_ID
};

#endif // !ecs