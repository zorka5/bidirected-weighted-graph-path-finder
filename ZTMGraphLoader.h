#pragma once

#include <string>
#include <fstream>

#include "ZTMGraphData.h"
#include "./graph/Graph.h"
/// <summary>
/// Funkcja zamieniająca numer na typ transportu.
/// </summary>
/// <param name="value"></param>
/// <returns></returns>
TransportType transport_type_from_int(const unsigned int& value) {
	switch (value) {
	case 1: return TransportType::BUS;
	case 2: return TransportType::TRAM;
	case 3: return TransportType::TRAIN;
	}

	throw std::runtime_error("unknown transport type");
}

/// <summary>
/// Funkcja pozwalajaca na wczytanie danych o przystankach z pliku tekstowego.
/// </summary>
/// <param name="stations_path">Ścieżka do pliku z stacjami</param>
/// <returns>Wierzchołki grafu</returns>
Graph<Station>::Vertices load_stations(
	const std::string& stations_path
) {
	// line - id,loc_x,loc_y,transport_type
	std::ifstream file(stations_path);
	if (!file.is_open()) {
		throw std::runtime_error("cannot open stations file");
	}

	typename Graph<Station>::Vertices vertices;

	while (file.good()) {
		std::string item;

		if (!std::getline(file, item, ','))
			throw std::runtime_error("cannot read #1 item");
		const unsigned int id = std::stoi(item);

		if (!std::getline(file, item, ','))
			throw std::runtime_error("cannot read #2 item");
		const double loc_x = std::stod(item);

		if (!std::getline(file, item, ','))
			throw std::runtime_error("cannot read #3 item");
		const double loc_y = std::stod(item);

		if (!std::getline(file, item))
			throw std::runtime_error("cannot read #4 item");
		const unsigned int transport_type_id = std::stoi(item);

		const Localization localization(loc_x, loc_y);
		const TransportType transport_type = transport_type_from_int(transport_type_id);

		Station station(id, localization, transport_type);
		VertexSPtr<Station> vertex(new Vertex<Station>(std::move(station)));

		vertices.push_back(std::move(vertex));
	}

	return vertices;
}
/// <summary>
/// Funkcja pozwalajaca na wczytanie danych o połączeniach między przystankami z pliku tekstowego.
/// </summary>
/// <param name="stations_path">Ścieżka do pliku z połączeniami</param>
/// <returns>Krawędzie grafu</returns>
Graph<Station>::Edges load_routes(
	const Graph<Station>::Vertices& vertices,
	const std::string& routes_path
) {
	// station_from_id,station_to_id,wieght
	std::ifstream file(routes_path);
	if (!file.is_open()) {
		throw std::runtime_error("cannot open routes file");
	}

	std::unordered_map<unsigned int, VertexSPtr<Station>> stations_by_id;
	for (const auto& vertex : vertices) {
		const unsigned int id = vertex->get_data().get_id();
		const auto [_, inserted] = stations_by_id.insert(std::make_pair(id, vertex));
		if (!inserted) {
			throw std::runtime_error("duplicate station with id " + std::to_string(id));
		}
	}

	typename Graph<Station>::Edges edges;
	
	while (file.good()) {
		std::string item;

		if(!std::getline(file, item, ','))
			throw std::runtime_error("cannot read #1 item");
		const unsigned int station_from_id = std::stoi(item);
		const auto station_from_it = stations_by_id.find(station_from_id);
		if (station_from_it == stations_by_id.cend()) {
			throw std::runtime_error("station from not found: " + std::to_string(station_from_id));
		}
		const VertexSPtr<Station>& station_from = station_from_it->second;

		if (!std::getline(file, item, ','))
			throw std::runtime_error("cannot read #2 item");
		const unsigned int station_to_id = std::stoi(item);
		const auto station_to_it = stations_by_id.find(station_to_id);
		if (station_to_it == stations_by_id.cend()) {
			throw std::runtime_error("station to not found: " + std::to_string(station_to_id));
		}
		const VertexSPtr<Station>& station_to = station_to_it->second;

		EdgeSPtr<Station> edge(new Edge<Station>(station_from, station_to));

		if (!std::getline(file, item))
			throw std::runtime_error("cannot read #3 item");
		const double weight = std::stod(item);

		const auto & [_, inserted] = edges.insert(std::make_pair(std::move(edge), std::move(weight)));
		if (!inserted) {
			throw std::runtime_error("duplicate route");
		}
	}

	return edges;
}

/// <summary>
/// Funkcja pozwalająca załadować stacje i połączenia z pliku tekstowego
/// </summary>
/// <param name="stations_path">Ścieżka do pliku ze stacjami</param>
/// <param name="routes_path">Ścieżka do pliku z połączeniami</param>
/// <returns>Graf wygenerowany na podstawie danych z pliku teksotwego</returns>
Graph<Station> load_graph(
	const std::string& stations_path,
	const std::string& routes_path
) {
	auto vertices = load_stations(stations_path);
	auto edges = load_routes(vertices, routes_path);
	return Graph<Station>(std::move(vertices), std::move(edges));
}
