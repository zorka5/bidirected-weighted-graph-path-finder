#pragma once

#include "Algorithm.h"

#include <algorithm>
#include <limits>
#include <optional>
#include <unordered_set>

/// <summary>
/// Klasa reprezentująca algorytm A*.
/// Klasa pozwala na znalezienie najkrótszej ścieżki w grafie przy pomocy algorytmu Dijkstry.
/// </summary>
/// <typeparam name="T">Typ wierzchołka grafu.</typeparam>
template <typename T>
class Dijkstra :
	public Algorithm<T>
{
public:
	/// <summary>
	/// Funkcja zwracajaca nazwę algorytmu.
	/// </summary>
	/// <returns>Nazwa algorytmu.</returns>
	const char* name() const override {
		return "Dijkstra";
	};
	/// <summary>
	/// Funkcja szukająca najkrótszej ścieżki w grafie zgodnie z algorytmem Dijkstry.
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
		std::unordered_multimap<VertexSPtr<T>, std::pair<VertexSPtr<T>, double>> neighbours;
		for (const auto& [edge, weight] : graph.get_edges()) {
			neighbours.insert(
				std::make_pair(
					edge->get_from(),
					std::make_pair(
						edge->get_to(),
						weight
					)
				)
			);
		}

		std::unordered_map< VertexSPtr<T>, double> dist;
		dist.insert(std::make_pair(start, 0.0));
		for (const auto& vertex : graph.get_vertices()) {
			dist.insert(std::make_pair(vertex, std::numeric_limits < double>::max()));
		}

		std::unordered_map< VertexSPtr<T>, VertexSPtr<T>> prev;

		std::unordered_set<VertexSPtr<T>> Q;
		for (const auto& vertex : graph.get_vertices()) {
			Q.insert(vertex);
		}

		while (true)
		{
			if (Q.empty()) {
				break;
			}

			const auto u_it = std::min_element(
				Q.cbegin(), Q.cend(),
				[&](const auto& a, const auto& b) {
					return dist.at(a) < dist.at(b);
				}
			);
			const auto u = std::move(*u_it);
			Q.erase(u_it);

			const auto neighbours_its = neighbours.equal_range(u);
			for (auto neighbours_it = neighbours_its.first; neighbours_it != neighbours_its.second; ++neighbours_it) {
				const auto& [v, weight] = neighbours_it->second;
				if (Q.count(v) <= 0) {
					continue;
				}

				const double dist_u = dist.at(u);
				if (dist_u == std::numeric_limits < double>::max()) {
					continue;
				}

				const double alt = dist_u + weight;
				if (alt < dist.at(v)) {
					dist.insert_or_assign(v, alt);
					prev.insert_or_assign(v, u);
				}
			}
		}

		typename SolveResult<T>::Path path;
		path.push_back(end);

		VertexSPtr<T> current = end;
		while (current != start) {
			const auto& previous_it = prev.find(current);
			if (previous_it == prev.cend()) {
				return std::nullopt;
			}
			const auto& previous = previous_it->second;

			path.push_back(previous);

			current = previous;
		}
		std::reverse(path.begin(), path.end());

		typename SolveResult<T>::Cost cost = dist.at(end);

		return SolveResult<T>(
			std::move(path),
			std::move(cost)
			);
	}
};