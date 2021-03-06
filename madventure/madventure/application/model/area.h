#pragma once

#include <memory>
#include <vector>
#include <string>

#include "../graph/GraphNodeTypes.h"
#include "gateway.h"
#include "trap.h"
#include "../system/gameinfoparser.h"
#include "unit.h"

using namespace std;

struct Level; // Forward declaration

struct Area {
  explicit Area(int node_index, shared_ptr<Level> level)
      : node_index(node_index), level(level) {
    climate = rand() % (12);
    visited = false;
  }
  int node_index;
  shared_ptr<Level> level;
  shared_ptr<Gateway> gateway;
  shared_ptr<Trap> trap;
  vector<shared_ptr<Unit>> units;
  int climate;
  bool visited;
};

