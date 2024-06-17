#ifndef __CLIENT_CONFIG_H__
#define __CLIENT_CONFIG_H__

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <unistd.h>

#include "../logger.h"
#include <yaml-cpp/yaml.h>


class ClientConfig {
private:
    static ClientConfig* instance;
    YAML::Node root;
    ClientConfig();
    static std::string getLogFile();

public:
    static ClientConfig* getInstance();
    // Logger& getLogger();
    // Characters from Font File
    static std::vector<int> getGreaterThan();
    static std::vector<int> getLessThan();
    // Refresh Interval
    static int getGamesListRefreshInterval();
    // Files
    static std::string getEpisodeFile();
    static std::string getCharacterSelectFile();
    static std::string getJazzFile();
    static std::string getSpazFile();
    static std::string getLoriFile();
    static std::string getTurtleFile();
    static std::string getSFXFile();
    static std::string getItemsFile();
    static std::string getInterfaceFontFile();
    // Colour Keys
    static std::tuple<int, int, int> getEpisodesColourKey();
    static std::tuple<int, int, int> getCharacterSelectColourKey();
    static std::tuple<int, int, int> getJazzColourKey();
    static std::tuple<int, int, int> getSpazColourKey();
    static std::tuple<int, int, int> getLoriColourKey();
    static std::tuple<int, int, int> getTurtleColourKey();
    static std::tuple<int, int, int> getSFXColourKey();
    static std::tuple<int, int, int> getItemsColourKey();
    static std::tuple<int, int, int> getInterfaceFontColourKey();
    // Rectangular Sprites
    static std::vector<std::vector<int>> getEpisodesSprites();
    //Levels sounds and sprites
    //Sounds
    static std::vector<std::string> getSoundsFiles();
    //Beach
    static std::vector<std::string> getBeachFiles();
    static std::string getBeachBacksound();
    static std::vector<std::vector<int>> getBeachSprites();
    //Colonius
    static std::vector<std::string> getColoniusFiles();
    static std::string getColoniusBacksound();
    static std::vector<std::vector<int>> getColoniusSprites();

    // Enemies Sprites
    // Turtle
    static int getTurtleWidth();
    static int getTurtleHeight();
    static std::vector<std::vector<int>> getTurtleWalkingSprites();
    static std::vector<std::vector<int>> getTurtleAttackingSprites();
    static std::vector<std::vector<int>> getTurtleDyingSprites();
    // Schwartzenguard
    static std::vector<std::vector<int>> getSchwartzenguardWalkingSprites();
    static std::vector<std::vector<int>> getSchwartzenguardAttackingSprites();
    static std::vector<std::vector<int>> getSchwartzenguardDyingSprites();
    // YellowMons
    static std::vector<std::vector<int>> getYellowMonsWalkingSprites();
    static std::vector<std::vector<int>> getYellowMonsAttackingSprites();
    static std::vector<std::vector<int>> getYellowMonsDyingSprites();
    // Players Sprites
    static int getPlayerWidth();
    static int getPlayerHeight();
    // Jazz
    static std::vector<std::vector<int>> getJazzIdleSprites();
    static std::vector<std::vector<int>> getJazzWalkingSprites();
    static std::vector<std::vector<int>> getJazzRunningSprites();
    static std::vector<std::vector<int>> getJazzShootingSprites();
    static std::vector<std::vector<int>> getJazzJumpingSprites();
    static std::vector<std::vector<int>> getJazzDashingSprites();
    static std::vector<std::vector<int>> getJazzSpecialAttackSprites();
    static std::vector<std::vector<int>> getJazzIntoxicatedSprites();
    static std::vector<std::vector<int>> getJazzTakingDamageSprites();
    static std::vector<std::vector<int>> getJazzDeadSprites();
    static std::vector<std::vector<int>> getJazzIconSprites();
    // Spaz
    static std::vector<std::vector<int>> getSpazIdleSprites();
    static std::vector<std::vector<int>> getSpazWalkingSprites();
    static std::vector<std::vector<int>> getSpazRunningSprites();
    static std::vector<std::vector<int>> getSpazShootingSprites();
    static std::vector<std::vector<int>> getSpazJumpingSprites();
    static std::vector<std::vector<int>> getSpazDashingSprites();
    static std::vector<std::vector<int>> getSpazSpecialAttackSprites();
    static std::vector<std::vector<int>> getSpazIntoxicatedSprites();
    static std::vector<std::vector<int>> getSpazTakingDamageSprites();
    static std::vector<std::vector<int>> getSpazDeadSprites();
    static std::vector<std::vector<int>> getSpazIconSprites();
    // Lori
    static std::vector<std::vector<int>> getLoriIdleSprites();
    static std::vector<std::vector<int>> getLoriWalkingSprites();
    static std::vector<std::vector<int>> getLoriRunningSprites();
    static std::vector<std::vector<int>> getLoriShootingSprites();
    static std::vector<std::vector<int>> getLoriJumpingSprites();
    static std::vector<std::vector<int>> getLoriDashingSprites();
    static std::vector<std::vector<int>> getLoriSpecialAttackSprites();
    static std::vector<std::vector<int>> getLoriIntoxicatedSprites();
    static std::vector<std::vector<int>> getLoriTakingDamageSprites();
    static std::vector<std::vector<int>> getLoriDeadSprites();
    static std::vector<std::vector<int>> getLoriIconSprites();
    // Items Sprites
    static int getItemsWidth();
    static int getItemsHeight();
    static std::vector<std::vector<int>> getRedGemSprites();
    static std::vector<std::vector<int>> getGoldCoinSprites();
    static std::vector<std::vector<int>> getSilverCoinSprites();
    // Projectiles
    static int getProjWidth();
    static int getProjHeight();
    static std::vector<std::vector<int>> getNormalProjectileSprites();
    static std::vector<std::vector<int>> getBlueBulletSprites();
    static std::vector<std::vector<int>> getVioletBulletSprites();
    static std::vector<std::vector<int>> getRedBombSprites();
    static std::vector<std::vector<int>> getVioletBombSprites();
    // Projectile fire
    static int getFireX();
    static int getFireY();
    static int getFireWidth();
    static int getFireHeight();
    // Interface font
    static std::vector<std::vector<int>> getInterfaceFontSprites();
    static int getWidthFont();
    static int getHeightFont();

    // Sprites
    static std::vector<std::vector<std::pair<int, int>>> getJazzSelectNameSprites();
    static std::vector<std::vector<std::pair<int, int>>> getJazzSelectSprites();
    static std::vector<std::vector<std::pair<int, int>>> getSpazSelectNameSprites();
    static std::vector<std::vector<std::pair<int, int>>> getSpazSelectSprites();
    static std::vector<std::vector<std::pair<int, int>>> getLoriSelectNameSprites();
    static std::vector<std::vector<std::pair<int, int>>> getLoriSelectSprites();
    // Delete Instance
    static void deleteInstance();
};

#endif  // __CLIENT_CONFIG_H__
