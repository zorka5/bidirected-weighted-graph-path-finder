#pragma once

#include <memory>
/// <summary>
/// Klasa reprezentująca wierchołek grafu
/// </summary>
/// <typeparam name="T">Typ danych wierzchołka</typeparam>
template <typename T>
class Vertex
{
private:
	/// <summary>
	/// Dane wierchołka
	/// </summary>
	T data;

public:
	/// <summary>
	/// Konstrukt klasy Vertex
	/// </summary>
	/// <param name="data">dane wierzchołka</param>
	Vertex(T&& data) : data(data) {}

public:
	/// <summary>
	/// Getter danych wierzchołka
	/// </summary>
	/// <returns></returns>
	const T & get_data() const { return data; }

public:
	/// <summary>
	/// Funkcja pozwalająca na wyznaczenie heurystyki na podstawie danych wierzchołka, znając wierzchołek docelowy.
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	double heuristic_distance(const Vertex& other) const {
		return data.heuristic_distance(other.data);
	}
};

template <typename T>
using VertexSPtr = std::shared_ptr<Vertex<T>>;