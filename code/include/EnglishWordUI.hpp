#pragma once
#include <SFML/Graphics.hpp>
#include "RoundWordUI.hpp"

class EnglishWordUI : public RoundWordUI {
public:
	// Default constructor
	EnglishWordUI(int x);

public:
	std::string palabra="";
	const char* word = "";
	int length=1;
};