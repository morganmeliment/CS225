#include <queue>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <iostream>
//#include "Graph.h"
//#include "Edge.h"
//#include "Vertex.h"

/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */

template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
    std::vector<std::string> keys;
    std::unordered_map<std::string, std::list<std::string>> paths;
    std::unordered_map<std::string, int> distances;
    std::unordered_map<std::string, bool> visited;

    for (auto it = vertexMap.begin(); it != vertexMap.end(); it++) {
        distances[it->first] = INT_MAX;
        std::list<std::string> path;
        path.push_back(start);
        paths[it->first] = path;
        keys.push_back(it->first);
        visited[it->first] = false;
    }

    distances[start] = 0;

    for (int i = 0; i < (int) vertexMap.size() - 1; i++) {
        int min = INT_MAX;
        std::string u = keys[0];

        for (std::string & key : keys) {
            if (visited[key] == false && distances[key] <= min) {
                min = distances[key];
                u = key;
            }
        }

        if (u == end)
            return paths[end];

        visited[u] = true;

        for (int j = 0; j < (int) vertexMap.size(); j++){
            std::string v = keys[j];

            if (!visited[v] && (isAdjacent(u, v) || isAdjacent(v, u))
                && distances[u] != INT_MAX && distances[u] + 1 < distances[v]) {
                distances[v] = distances[u] + 1;
                paths[v] = paths[u];
                paths[v].push_back(v);
            }
        }
    }

    return paths[end];
}
