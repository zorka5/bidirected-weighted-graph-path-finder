#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <utility>

#include "algorithm/BellmanFord.h"
#include "algorithm/AStar.h"
#include "algorithm/Dijkstra.h"
#include "ZTMGraphLoader.h"

#include "gui/GUI.h"

void run()
{
	const std::string STATIONS_FILENAME = "C:/Users/zocha/Documents/Projects/ztm-grafika/resources/stations2.txt";
	const std::string ROUTES_FILENAME = "C:/Users/zocha/Documents/Projects/ztm-grafika/resources/routes2.txt";

	const auto graph = load_graph(STATIONS_FILENAME, ROUTES_FILENAME);
	auto gui = GUI(std::move(graph));
	gui.draw_gui();


	//std::unordered_map<unsigned int, VertexSPtr<Station>> stations_by_id;
	//for (const auto& vertex : graph.get_vertices()) {
	//	stations_by_id.insert(std::make_pair(vertex->get_data().get_id(), vertex));
	//}

	//std::vector<std::unique_ptr<Algorithm<Station>>> algorithms;
	//algorithms.push_back(std::unique_ptr<Algorithm<Station>>(new AStar<Station>()));
	//algorithms.push_back(std::unique_ptr<Algorithm<Station>>(new BellmanFord<Station>()));
	//algorithms.push_back(std::unique_ptr<Algorithm<Station>>(new Dijkstra<Station>()));

	//for (const auto& algorithm : algorithms) {
	//	std::cout << "Running: " << algorithm->name() << std::endl;

	//	const auto solution_opt = algorithm->solve(graph, stations_by_id.at(11), stations_by_id.at(315));
	//	if (!solution_opt) {
	//		std::cout << "no solution" << std::endl;
	//		continue;
	//	}

	//	const auto& solution = *solution_opt;
	//	for (const auto& vertex : solution.get_path()) {
	//		std::cout << vertex->get_data().get_id() << " ";
	//	}
	//	std::cout << std::endl;

	//	std::cout << "Total cost: " << solution.get_cost() << std::endl;
	//}
}
int main() {
	try {
		run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "non c++ exception handled" << std::endl;
	}
	return 0;
}
