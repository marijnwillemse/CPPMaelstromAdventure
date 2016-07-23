#include <iostream>
#include <string>

#include "gamesystem.h"
#include "../event/createlevelevent.h"
#include "../component/level.h"
#include "../component/area.h"
#include "../component/player.h"
#include "../component/location.h"

using namespace std;

void GameSystem::configure(ex::EventManager &events) {
  events.subscribe<GameQuit>(*this);
}

void GameSystem::initialize(ex::EntityManager &es, ex::EventManager &events) {
  std::cout << "Welcome to Maelstrom Adventure.\n";
  events.emit<CreateLevelEvent>(es);
  
  ex::ComponentHandle<Level> level;
  for (ex::Entity entity : es.entities_with_components(level)) {
    NavGraphNode<ex::Entity*> first_node = level->graph->GetNode(0);

    // Create player entity.
    ex::Entity player = es.create();
    player.assign<Player>();
    player.assign<Location>(first_node.ExtraInfo());

    ex::ComponentHandle<Player> player_handle = player.component<Player>();
    std::cout << "Your name is " << player_handle->name << std::endl;

    break;
  }
}

void GameSystem::update(ex::EntityManager &es, ex::EventManager &events,
                        ex::TimeDelta dt) {
  if (initialized_ == false) {
    initialize(es, events);
  }
}

void GameSystem::receive(const GameQuit &gamequit) {
  std::cout << "Thank you for playing.\n" << std::endl;
  finished_ = true;
}