#pragma once

#include <cmath>
#include "Localization.h"

/// <summary>
/// Enum z typami środków transportu
/// </summary>
enum class TransportType {
	BUS,
	TRAM,
	TRAIN
};

/// <summary>
/// Klasa reprezentująca przystanek
/// </summary>
class Station {
private:
	const unsigned int id;
	const Localization localization;
	const TransportType transport_type;

public:
	Station(
		const unsigned int& id,
		const Localization& localization,
		const TransportType& transport_type
	) :
		id(id),
		localization(localization),
		transport_type(transport_type)
	{}

public:
	const unsigned int& get_id() const { return id; }
	const Localization& get_localization() const { return localization; }
	const TransportType& get_transport_type() const { return transport_type; }

public:
	double heuristic_distance(const Station& other) const {
		return localization.heuristic_distance(other.localization);
	}
};
