#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  // TODO: Part 2
  return vertexMap.size();
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
    // TODO: Part 2
    //int deg = 0;
    return adjList[v.key()].size();
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
    // TODO: Part 2
    V & v = *(new V(key));
    vertexMap.emplace(key, v);
    std::list<edgeListIter> temp;
    adjList[key] = temp;
    return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
    // TODO: Part 2
    vertexMap.erase(key);

    for (typename std::list<E_byRef>::iterator it = edgeList.begin();
            it != edgeList.end(); it++) {
        if ((*it).get().source().key() == key || (*it).get().dest().key() == key) {
            edgeList.erase(it);
        }
    }
}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
    // TODO: Part 2
    E & e = *(new E(v1, v2));
    edgeList.push_front(e);
    adjList[v1.key()].push_back(edgeList.begin());
    adjList[v2.key()].push_back(edgeList.begin());
    return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the ource Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
    // TODO: Part 2
    edgeListIter toRemove = edgeList.end();
    for (typename std::list<edgeListIter>::iterator it = adjList[key1].begin();
            it != adjList[key1].end(); it++) {
        if ((*(*it)).get().source().key() == key2 || (*(*it)).get().dest().key() == key2) {
            toRemove = *it;
            adjList[key1].erase(it);
            break;
        }
    }
    for (typename std::list<edgeListIter>::iterator it = adjList[key2].begin();
            it != adjList[key2].end(); it++) {
        if ((*(*it)).get().source().key() == key1 || (*(*it)).get().dest().key() == key1) {
            toRemove = *it;
            adjList[key2].erase(it);
            break;
        }
    }
    edgeList.erase(toRemove);
}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
    // TODO: Part 2
    removeEdge((*it).get().source().key(), (*it).get().dest().key());
}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  for (const auto & ref : edgeList) {
      if (ref.get().source().key() == key || ref.get().dest().key() == key) {
          edges.push_back(ref);
      }
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
    // TODO: Part 2
    for (const auto & ref : edgeList) {
        //|| (ref.get().source().key() == key2 && ref.get().dest().key() == key1)
        if ((ref.get().source().key() == key1 && ref.get().dest().key() == key2)) {
            return true;
        }
    }
    return false;
}
