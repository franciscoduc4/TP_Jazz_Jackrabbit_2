#ifndef PLAYER_COMMANDS_H_
#define PLAYER_COMMANDS_H_

// Acciones comunes
#define SHOOT 0x06 //"shoot"
#define RUN 0x07 //"run"
#define RUN_FAST 0x08 //"run fast"
#define JUMP 0x09 //"jump"

// Estados
#define INTOXICATED 0x10 //"intoxicated"
#define TAKE_DAMAGE 0x11 //"take damage"
#define DEATH 0x12 //"death"
#define REVIVE 0x13 //"revive" //revive cada x segundos
#define HEAL 0x14 //"heal"

// Acciones especiales
#define UPPERCUT 0x15 //"uppercut"        // Jazz
#define SHORT_KICK 0x16 //"short kick"    // Lori
#define SIDE_KICK 0x17 //"side kick"      // Spazz

#endif  // PLAYER_COMMANDS_H_
