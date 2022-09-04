#pragma once


#include "Algorithm.h"

#include <algorithm>
#include <limits>
#include <optional>
#include <unordered_set>

/// <summary>
/// Klasa reprezentująca algorytm A*.
/// Klasa pozwala na znalezienie najkrótszej ścieżki w grafie przy pomocy algorytmu A*.
/// </summary>
/// <typeparam name="T">Typ wierzchołka grafu.</typeparam>
template <typename T>
class AStar :
	public Algorithm<T>
{
public:
	/// <summary>
	/// Funkcja zwracajaca nazwę algorytmu.
	/// </summary>
	/// <returns>Nazwa algorytmu.</returns>
	const char* name() const override {
		return "AStar";
	};
	/// <summary>
	/// Funkcja szukająca najkrótszej ścieżki w grafie zgodnie z algorytmem A*. 
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
		const auto h = [&](const VertexSPtr<T>& vertex) {
			return vertex->heuristic_distance(*end);
		};

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

		std::unordered_set<VertexSPtr<T>> open_set;
		open_set.insert(start);

		std::unordered_map< VertexSPtr<T>, VertexSPtr<T>> came_from;

		std::unordered_map< VertexSPtr<T>, double> g_score;
		g_score.insert(std::make_pair(start, 0.0));
		for (const auto& vertex : graph.get_vertices()) {
			g_score.insert(std::make_pair(vertex, std::numeric_limits < double>::max()));
		}

		std::unordered_map< VertexSPtr<T>, double> f_score;
		f_score.insert(std::make_pair(start, h(start)));
		for (const auto& vertex : graph.get_vertices()) {
			f_score.insert(std::make_pair(vertex, std::numeric_limits < double>::max()));
		}

		while (true)
		{
			if (open_set.empty()) {
				break;
			}

			const auto current_it = std::min_element(
				open_set.cbegin(), open_set.cend(),
				[&](const auto& a, const auto& b) {
					return f_score.at(a) < f_score.at(b);
				}
			);
			const auto current = std::move(*current_it);
			open_set.erase(current_it);

			if (current == end) {
				break;
			}

			const auto neighbours_its = neighbours.equal_range(current);
			for (auto neighbours_it = neighbours_its.first; neighbours_it != neighbours_its.second; ++neighbours_it) {
				const auto& [neighbour, weight] = neighbours_it->second;

				const double tentative_gscore = g_score.at(current) + weight;

				if (tentative_gscore < g_score.at(neighbour)) {
					came_from.insert_or_assign(neighbour, current);
					g_score.insert_or_assign(neighbour, tentative_gscore);
					f_score.insert_or_assign(neighbour, tentative_gscore + h(neighbour));
					open_set.insert(neighbour);
				}
			}
		}

		typename SolveResult<T>::Path path;
		path.push_back(end);

		VertexSPtr<T> current = end;
		while (current != start) {
			const auto& previous_it = came_from.find(current);
			if (previous_it == came_from.cend()) {
				return std::nullopt;
			}
			const auto& previous = previous_it->second;

			path.push_back(previous);

			current = previous;
		}
		std::reverse(path.begin(), path.end());

		typename SolveResult<T>::Cost cost = g_score.at(end);

		return SolveResult<T>(
			std::move(path),
			std::move(cost)
			);
	}
};