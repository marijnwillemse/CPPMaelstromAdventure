#pragma once

#include <memory>

#include "levelsystem.h"
#include "../model/world.h"
#include "../model/player.h"

class GameSystem {
public:
  explicit GameSystem();

  void Init();

  void Update();
  void Quit() { finished_ = true; }

  bool is_finished() { return finished_; }
  LevelSystem levelSystem() { return level_system_; }
  shared_ptr<Player> player() { return player_; }

private:
  bool finished_;

  LevelSystem level_system_;

  shared_ptr<World> world_;
  shared_ptr<Player> player_;

  shared_ptr<Level> NewLevel(int columns, int row);
};