#ifndef TRACKS_HPP
#define TRACKS_HPP

#include <iostream>
#include "graph.hpp"
#include "myDS.hpp"
#include "utils.hpp"
using namespace MyDataStructures;

/**
 * @brief Function to get the Eulerian properties of a graph
 * @param graph The graph to analyze
 * @return An EulerianTrailProperties struct containing the "eulerian properties" of the graph
 */
EulerianTrailProperties getEulerianPropetiesOfGraph(const Graph &graph);

/**
 * @brief Fleury's algorithm to find an Eulerian trail in a graph
 * @param graph The graph to analyze
 * @param properties The EulerianTrailProperties struct containing the "eulerian properties" of the graph
 * @return A vector of edges representing the Eulerian trail
 */
vector<Edge> fleury_algorithm(const Graph &graph, EulerianTrailProperties &properties);

#endif // TRACKS_HPP

