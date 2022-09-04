#pragma once

#include <vector>
#include <unordered_map>

#include "Vertex.h"
#include "Edge.h"

/// <summary>
/// Klasa reprezentująca graf.
/// Graf reprezentowny jest jako zbiór wierzchołków oraz krawędzi wraz z wagami.
/// </summary>
/// <typeparam name="T">Typ wierzchołków grafu.</typeparam>
template <typename T>
class Graph
{
public:
	using Vertices = std::vector<VertexSPtr<T>>;
	using Weight = double;
	using Edges = std::unordered_map<EdgeSPtr<T>, Weight>;

private:
	/// <summary>
	/// Zbiór wierzchołków grafu
	/// </summary>
	const Vertices vertices;
	/// <summary>
	/// Zbiór krawędzi grafu
	/// </summary>
	const Edges edges;


public:
	/// <summary>
	/// Konstruktor domyślny
	/// </summary>
	Graph(){}
	/// <summary>
	/// Konstruktor klasy Graph
	/// </summary>
	/// <param name="vertices">Wierzchołki grafu</param>
	/// <param name="edges">Krawędzie grafu</param>
	Graph(Vertices&& vertices, Edges&& edges) :
		vertices(std::move(vertices)),
		edges(std::move(edges))
	{}

public:
	/// <summary>
	/// Getter wierzchołków grafu
	/// </summary>
	/// <returns>Wierzchołki grafu</returns>
	const Vertices& get_vertices() const { return vertices; }
	/// <summary>
	/// Getter krawędzi grafu
	/// </summary>
	/// <returns>Krawędzie grafu</returns>
	const Edges& get_edges() const { return edges; };
};