#ifndef WEAPON_TYPE_H_
#define WEAPON_TYPE_H_

enum class WeaponType : char {
    BLASTER,      // Default weapon
    BOUNCER,      // Bouncing projectiles
    TOASTER,      // Flamethrower-like weapon
    RF_MISSILES,  // Rapid-fire missiles
    LAUNCHER,     // Single large missile
    TNT,          // Timed explosive
    FREEZER,      // Ice gun to freeze enemies
    SEEKER        // Homing missiles
};

#endif  // WEAPON_TYPE_H_