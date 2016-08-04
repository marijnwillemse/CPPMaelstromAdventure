#include "debugcommands.h"

#include <math.h>

#include "gamesystem.h"
#include "../model/area.h"
#include "../graph/GraphAlgorithms.h"

void PrintPositionCommand::Execute(GameSystem* game_system, vector<string> words) {
  auto player = game_system->unit_system()->player();
  auto area = player->area;
  auto graph = area->level->graph;
  int index = area->node_index;
  Vector2D position = graph->GetNode(index).Pos();
  cout << "You are at node[" << index << "], positioned at {"
    << position.x << ", " << position.y << "}\n";
}

void PrintPathsCommand::Execute(GameSystem* game_system, vector<string> words) {
  auto player = game_system->unit_system()->player();
  auto area = player->area;
  auto graph = area->level->graph;
  auto neighbors = game_system->level_system()->NeighboringNodeIndexes(area);
  vector<int>::iterator it;
  for (it = neighbors.begin(); it != neighbors.end(); ++it) {
    Vector2D position = graph->GetNode(*it).Pos();
    cout << "Path leading to node[" << *it << "], positioned at {"
      << position.x << ", " << position.y << "}\n";
  }
}


void PrintMapCommand::Execute(GameSystem* game_system, vector<string> words) {
  auto player = game_system->unit_system()->player();
  auto graph = player->area->level->graph;

  game_system->level_system()->PrintMap(graph, player, true);
}

void DistanceToGatewayCommand::Execute(GameSystem* game_system, vector<string> words) {
  auto player = game_system->unit_system()->player();
  auto graph = player->area->level->graph;
  int source = player->area->node_index;
  int target = -1;

  // Find a node with a gateway leading towards another level.
  // Retrieve all graph nodes.
  auto nodes = graph->GetNodeVector();
  // For every node.
  vector<NavGraphNode<shared_ptr<Area>>>::iterator it;
  for (it = nodes.begin(); it != nodes.end(); ++it) {
    if (it->ExtraInfo()->gateway) {
      // Node has gateway.
      if (it->ExtraInfo()->gateway->from == it->ExtraInfo()) {
        // Gateway is leading from.
        target = it->Index();
      }
    }
  }
  if (target == -1) {
    // Not found in level
    cout << "Unable to find area with whirlpool in current level.\n";
    return;
  }

  cout << "Whirlpool found.\n";

  auto searcher = Graph_SearchBFS<SparseGraph<NavGraphNode<shared_ptr<Area>>, NavGraphEdge>>(*graph, source, target);
  auto list = searcher.GetPathToTarget();
  
  //auto to = from->level->graph->
  cout << "Distance to whirlpool is: " << list.size() << ".\n";
}

void SpanningTreeCommand::Execute(GameSystem* game_system, vector<string> words) {
  auto graph = game_system->unit_system()->player()->area->level->graph;
  auto searcher = Graph_MinSpanningTree<SparseGraph<NavGraphNode<shared_ptr<Area>>, NavGraphEdge>>(*graph);
  auto tree = searcher.GetSpanningTree();
  
  vector<const NavGraphEdge*>::iterator it;
  for (it = tree.begin(); it != tree.end(); ++it) {
    cout << "Edge " << (*it)->From() << "-" << (*it)->To() << "\n";
  }
}