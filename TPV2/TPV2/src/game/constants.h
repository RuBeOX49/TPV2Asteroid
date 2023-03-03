#ifndef CONSTANTS_H
#define CONSTANTS_H
using uint = unsigned int;

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;

// FRAME TIMES
const double FRAME_TIME = 30;
const int DELAY_TIME = 17;

// PLAYER VALUES

const int STARTING_HEALTH = 3;

// GAME SIGNALS

using sig_type = int;

enum sig : sig_type {

	_SIG_PAUSE,
	_SIG_RESUME,
	_SIG_DEATH,
	_SIG_DAMAGE,
	_SIG_START

};

#endif // !CONSTANTS_H
