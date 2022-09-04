#pragma once

#include <utility>



/// <summary>
/// Funkcja reprezentujaca lokalizację obiektu
/// </summary>
class Localization
{
public:
	/// <summary>
	/// Współrzędna x
	/// </summary>
	double x = 0;
	/// <summary>
	/// Współrzędna y
	/// </summary>
	double y = 0;

public:
	/// <summary>
	/// Konstruktor domyślny
	/// </summary>
	Localization() {};
	/// <summary>
	/// Konstruktor klasy Localization
	/// </summary>
	/// <param name="x_">współrzędna x</param>
	/// <param name="y_">współrzędna y</param>
	Localization(double x_, double y_) : x(x_), y(y_) {};
	/// <summary>
	/// Setter lokalizacji
	/// </summary>
	/// <param name="x_">współrzędna x</param>
	/// <param name="y_">współrzędna y</param>
	
public:
	/// <summary>
	/// Funkcja pozwalajaca obliczyć heurystykę lokalizacji
	/// </summary>
	/// <param name="other">Docelowa lokalizacja</param>
	/// <returns>Heurystyka</returns>
	double heuristic_distance(const Localization& other) const {
		return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
	}
	/// <summary>
	/// Setter lokalizacji
	/// </summary>
	/// <param name="x_">Współrzędna x</param>
	/// <param name="y_">Współrzędna y</param>
	void set_localization(double x_, double y_) { x = x_; y = y_; };
	/// <summary>
	/// Getter współrzędnej x
	/// </summary>
	/// <returns>współrzędna x</returns>
	const double& get_x() { return x; };
	/// <summary>
	/// Getter współrzędnej y
	/// </summary>
	/// <returns>współrzędna y</returns>
	const double& get_y() { return y; };
};

