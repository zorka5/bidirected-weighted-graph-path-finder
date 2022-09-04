#pragma once

#include <utility>
#include <optional>

#include "../graph/Graph.h"

/// <summary>
/// Klasa reprezentująca wynik przeszukiwania grafu. 
/// Jeśli ścieżka została znaleziona, wynik przechowywany jest jako wektor wskaźników na wierzchołki oraz całkowity koszt.
/// </summary>
/// <typeparam name="T">Typ danych wierzchołka grafu</typeparam>

template <typename T>
class SolveResult {
public:
	using Path = std::vector<VertexSPtr<T>>;
	using Cost = double;

private:
	/// <summary>
	/// Stała przechowująca wierzchołki ściezki.
	/// </summary>
	const Path path;
	/// <summary>
	/// Stała przechowująca całkowity koszt ścieżki.
	/// </summary>
	const Cost cost;

public:
	/// <summary>
	/// Konstruktor klasy SolveResult.
	/// </summary>
	/// <param name="path"></param>
	/// <param name="cost"></param>
	SolveResult(Path&& path, Cost&& cost) :
		path(std::move(path)),
		cost(std::move(cost))
	{}

public:
	/// <summary>
	/// Getter na ścieżkę. 
	/// </summary>
	/// <returns>Ścieżka jako wektor wierzchołków. </returns>
	const Path& get_path() const { return path; }
	/// <summary>
	/// Getter na koszt całkowity.
	/// </summary>
	/// <returns>Koszt bedący sumą wag krawędzi między wierzchołkami ścieżki.</returns>
	const Cost& get_cost() const { return cost; }
};

/// <summary>
/// Interfejs algorytmu do wyszukiwania najkrótszej ścieżki w grafie.
/// Interfejs pozwalający na wywołanie róznych algorytmów przeszukiania na grafie. Klasa abstrakcyjna.  
/// </summary>
/// <typeparam name="T">Typ wierzchołków grafu.</typeparam>
template <typename T>
class Algorithm {
public:
	/// <summary>
	/// Metoda zwracająca nazwę agorytmu. 
	/// </summary>
	/// <returns>Nazwa algorytmu</returns>
	virtual const char* name() const = 0;

	/// <summary>
	/// Funkcja pozwalajaca znaleźć najkrótszą ścieżkę w grafie. 
	/// </summary>
	/// <param name="graph">Graf, w którym będzie szukana ścieżka. </param>
	/// <param name="start">Wierzchołek początkowy.</param>
	/// <param name="end">Wierzchołek końcowy.</param>
	/// <returns>W przypadku powodzenia zwraca SolveResult, w przecwnym std::nullopt.</returns>
	virtual std::optional<SolveResult<T>> solve(
		const Graph<T>& graph,
		const VertexSPtr<T>& start,
		const VertexSPtr<T>& end
	) const = 0;
};