#pragma once


#include "Algorithm.h"

#include <limits>
#include <optional>

/// <summary>
/// Klasa reprezentująca algorytm BellmanaForda.
/// Klasa pozwala na znalezienie najkrótszej ścieżki w grafie przy pomocy algorytmu BellmanaForda.
/// </summary>
/// <typeparam name="T">Typ wierzchołka grafu.</typeparam>
template <typename T>
class BellmanFord :
	public Algorithm<T>
{
public:
	/// <summary>
	/// Funkcja zwracajaca nazwę algorytmu.
	/// </summary>
	/// <returns>Nazwa algorytmu.</returns>
	const char* name() const override {
		return "BellmanFord";
	};
	/// <summary>
	/// Funkcja szukająca najkrótszej ścieżki w grafie zgodnie z algorytmem BellmanaForda. 
	/// </summary>
	/// <param name="graph">Graf, w którym będzie szukana ścieżka.</param>
	/// <param name="start">Wierzchołek początkowy.</param>
	/// <param name="end">Wierzchołek końcowy.</param>
	/// <returns>Zwraca znalezioną ścieżkę i całkowity koszt, w przypadku braku istnienia ścieżki std::nullopt.</returns>
	std::optional<SolveResult<T>> solve(
		const Graph<T>& graph,
		const VertexSPtr<T>& start,
		const VertexSPtr<T>& end
	) const override {
		std::unordered_map<VertexSPtr<T>, double> d;
		d.insert(std::make_pair(start, 0.0));
		for (auto const& vertex : graph.get_vertices()) {
			d.insert(std::make_pair(vertex, std::numeric_limits<double>::max()));
		}

		std::unordered_map<VertexSPtr<T>, VertexSPtr<T>> p;

		for (unsigned int v = 0; v < graph.get_vertices().size() - 1; ++v) {
			for (auto const& [edge, weight] : graph.get_edges()) {
				const auto& d_from = d.at(edge->get_from());
				const auto& d_to = d.at(edge->get_to());

				if (d_from + weight < d_to) {
					d.insert_or_assign(edge->get_to(), d_from + weight);
					p.insert_or_assign(edge->get_to(), edge->get_from());
				}
			}
		}

		typename SolveResult<T>::Path path;
		path.push_back(end);

		VertexSPtr<T> path_temp = end;
		while (path_temp != start) {
			const auto& path_prev_it = p.find(path_temp);
			if (path_prev_it == p.cend()) {
				return std::nullopt;
			}
			const auto& path_prev = path_prev_it->second;

			path.push_back(path_prev);

			path_temp = path_prev;
		}
		std::reverse(path.begin(), path.end());

		typename SolveResult<T>::Cost cost = d.at(end);

		return SolveResult<T>(
			std::move(path),
			std::move(cost)
			);
	}
};