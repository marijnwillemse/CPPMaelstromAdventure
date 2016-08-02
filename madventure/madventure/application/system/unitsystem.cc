#include "unitsystem.h"

using namespace std;

shared_ptr<Enemy> UnitSystem::SpawnEnemy(shared_ptr<Area> destination) {
  auto enemy = make_shared<Enemy>(destination);
  return enemy;
}

shared_ptr<Player> UnitSystem::SpawnPlayer(shared_ptr<Area> area) {
  auto player = make_shared<Player>(area);
  return player;
}

void UnitSystem::MoveUnit(shared_ptr<Unit> unit, shared_ptr<Area> destination) {
  unit->area = destination;
}
