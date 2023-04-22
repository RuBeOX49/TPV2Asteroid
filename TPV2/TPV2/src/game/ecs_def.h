#pragma once
#include "../utils/Vector2D.h"
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
	state_DEAD,
	state_WIN,
	state_MAINMENU,
	state_MULTIPLAYER
};

enum msgId : msgId_type {
	_m_DESTROY_ASTEROID,
	_m_SPAWN_ASTEROIDS,
	_m_CHANGE_STATE,
	_m_BATTLE_STATE_SETUP,
	_m_COLLISION_AST_SHIP,
	_m_COLLISION_AST_BULLET,
	_m_SHOOT_BULLET,
	_m_BATTLE_RESTART,
	_m_SEND_FIGHTER,
	_m_DESTROY_ALL_ASTEROIDS,
	_m_ASTEROIDS_EXTINCTION,


	_m_CONNECTION_REQUEST, 
	_m_REQUEST_ACCEPTED,
	_m_REQUEST_REFUSED,
	_m_FIGHTER_POS,
	_m_BULLETS_REC,
	_m_START_ROUND_REQUEST,
	_START_GAME_REQUEST,

	_m_UPDATE_ENEMY_TRANSFORM,

	_m_SEND_NET_MESSAGE,

	_m_NET_OTHER_FIGHTER_FORWARD,
	_m_NET_OTHER_FIGHTER_LEFT,
	_m_NET_OTHER_FIGHTER_RIGHT,
	_m_NET_OTHER_FIGHTER_SHOOTS,
	_m_NET_OTHER_FIGHTER_WINS,
	_m_NET_OTHER_FIGHTER_LOSES,
	_m_NET_OTHER_FIGHTER_DISCONNECTS,


	_m_SETUP_MULTIPLAYER


};

struct Message {
	msgId_type id;
	// _m_DESTROY_ASTEROID
	struct {
		Entity* e = nullptr;
	} destroy_asteroid_data;
	// _m_SPAWN_ASTEROID
	struct {
		Entity* b = nullptr;
	} destroy_bullet_data;
	//_m_CHANGE_STATE
	struct {
		stateID state;
	}new_state_ID;
	struct {
		Entity* f = nullptr;
	}fighter_address;
	//_m_COLLISION_AST_SHIP
	int remainingHealth {-1};
	
	//_m_SETUP_MULTIPLAYER
	bool isHost;

	//_m_SEND_NET_MESSAGE
	msgId_type netMessageID;

	Message() {}
	Message(msgId_type id) : id(id) {}
};

struct NetMessage {
	msgId_type id;

	int nameSize;
	char name[11];

	

	NetMessage() {}
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
	_grp_ENEMY_BULLETS,
	_grp_FIGHTER,
	_grp_ENEMY_FIGHTER,
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
	sys_NET,

	//DO NOT DELETE FOR THE LOVE OF THAT WOMAN
	sys_LAST_SYSTEM_ID
};
constexpr sysId_type maxSystemId = sys_LAST_SYSTEM_ID;

constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

#endif // !ECS_H_