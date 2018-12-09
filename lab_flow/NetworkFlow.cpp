/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
    g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

    residual_ = g_;
    flow_ = residual_;
    maxFlow_ = 0;

    for (const Edge & edge : flow_.getEdges()) {
        flow_.setEdgeWeight(edge.source, edge.dest, 0);
    }

    for (const Edge & edge : residual_.getEdges()) {
        residual_.insertEdge(edge.dest, edge.source);
        residual_.setEdgeWeight(edge.dest, edge.source, 0);
        residual_.setEdgeLabel(edge.dest, edge.source, "r");
    }
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   * @@params: visited -- A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink,
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @@params: path   -- The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
    // YOUR CODE HERE
    int minCapacity = INT_MAX;

    for (int i = 0; i < (int) path.size() - 1; i++) {
        int edgeWeight = residual_.getEdgeWeight(path[i], path[i + 1]);
        if (edgeWeight == INT_MIN)
            return 0;
        else if (edgeWeight < minCapacity)
            minCapacity = edgeWeight;
    }
    return minCapacity;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @@outputs: The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
    // YOUR CODE HERE
    std::vector<Vertex> path;

    while (findAugmentingPath(source_, sink_, path)) {
        int maxFlow = pathCapacity(path);

        for (int i = 0; i < (int) path.size() - 1; i++) {
            int edgeWeight = residual_.getEdgeWeight(path[i], path[i + 1]);
            int edgeWeight2 = residual_.getEdgeWeight(path[i + 1], path[i]);

            residual_.setEdgeWeight(path[i], path[i + 1], edgeWeight - maxFlow);
            residual_.setEdgeWeight(path[i + 1], path[i], edgeWeight2 + maxFlow);

            if (residual_.getEdgeLabel(path[i], path[i + 1]) == "r") {
                flow_.setEdgeWeight(path[i + 1], path[i], flow_.getEdgeWeight(path[i + 1], path[i]) - maxFlow);
            } else {
                flow_.setEdgeWeight(path[i], path[i + 1], flow_.getEdgeWeight(path[i], path[i + 1]) + maxFlow);
            }
        }
    }

    for (const Edge & edge : flow_.getEdges()) {
        if (edge.dest == sink_) {
            maxFlow_ += edge.getWeight();
        }
    }

    return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}
