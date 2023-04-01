#pragma once
#ifndef ECS_H_
#define ECS_H_

using cmpId_type = int;
using grpId_type = int;
using sysId_type = int;
using msgId_type = int;

class Entity;

enum stateID : int {
	state_BATTLE,
	state_PAUSED,
	state_DAMAGED,
	state_DEAD
};

enum msgId : msgId_type {
	_m_DESTROY_ASTEROID,
	_m_SPAWN_ASTEROIDS,
	_m_CHANGE_STATE,
	_m_BATTLE_STATE_SETUP,
	_m_COLLISION_AST_SHIP,
	_m_COLLISION_AST_BULLET,
	_m_SHOOT_BULLET,
	_m_DESTROY_ALL_ASTEROIDS
};

struct Message {
	msgId_type id;
	// _m_DESTROY_ASTEROID
	struct {
		Entity* e;
	} destroy_asteroid_data;
	// _m_SPAWN_ASTEROID
	struct {
		Entity* b;
	} destroy_bullet_data;
	//_m_CHANGE_STATE
	struct {
		stateID state;
	}new_state_ID;
	//_m_COLLISION_AST_SHIP
	int remainingHealth;

	Message() {}
	Message(msgId_type id): id(id) {}
};

enum cmpId : cmpId_type {
	_TRANSFORM,
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

enum grpId : grpId_type {

	_grp_ASTEROIDS,
	_grp_BULLETS,
	_grp_FIGHTER,
	_grp_UI,

	_grp_NONE

};

enum sysId : sysId_type {
	sys_ASTEROIDS,
	sys_BULLET,
	sys_COLLISION,
	sys_FIGHTER,
	sys_SCENECTRL,
	sys_RENDER,

	//DO NOT DELETE FOR THE LOVE OF THAT WOMAN
	sys_LAST_SYSTEM_ID
};
constexpr sysId_type maxSystemId = sys_LAST_SYSTEM_ID;

constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

#endif // !ECS_H_