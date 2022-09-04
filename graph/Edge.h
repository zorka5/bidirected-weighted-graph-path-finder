#pragma once

#include <memory>

#include "Vertex.h"
/// <summary>
/// Klasa reprezentująca krawędź grafu.
/// Krawędź reprezentowana jest w postaci pary wierzchołków oraz wagi. 
/// </summary>
/// <typeparam name="T">Typ wierzchołków grafu.</typeparam>
template<typename T>
class Edge {
private:
	/// <summary>
	/// Wierzchołek początkowy
	/// </summary>
	const VertexSPtr<T> from;
	/// <summary>
	/// Wierzchołek końcowy
	/// </summary>
	const VertexSPtr<T> to;

public:
	/// <summary>
	/// Konstruktor klasy Edge
	/// </summary>
	/// <param name="from">Wierzchołek początkowy</param>
	/// <param name="to">Wierzchołek końcowy</param>
	Edge(
		const VertexSPtr<T>& from,
		const VertexSPtr<T>& to
	) : from(from), to(to) {}

public:
	/// <summary>
	/// Getter wierzchołka początkowego
	/// </summary>
	/// <returns>Wierchołek początkowy</returns>
	const VertexSPtr<T>& get_from() const { return from; }
	/// <summary>
	/// Getter wierzchołka końcowy
	/// </summary>
	/// <returns>Wierchołek końcowy</returns>
	const VertexSPtr<T>& get_to() const { return to; }
};

template <typename T>
using EdgeSPtr = std::shared_ptr<Edge<T>>;
