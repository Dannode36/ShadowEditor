#pragma once
#include <string>
#include <vector>
#include "imgui.h"
#include "ValuePair.h"

struct Meta {

};

struct Interactable {

};

struct MultiPage {

};

struct Citizen {
	ValuePair<int> humanID;
	ValuePair<int> home;
	ValuePair<int> job;
	ValuePair<std::string> birthday;
	ValuePair<float> societalClass;

};

struct Criminal {

};

struct Group {

};

struct Pipe {

};

struct Street {
	ValuePair<std::string> name;
	ValuePair<int> residenceNumber;
	ValuePair<bool> isLobby;
	ValuePair<bool> isMainLobby;
	ValuePair<bool> isOutside;
	ValuePair<int> access;
};

struct Block {
	ValuePair<std::string> name;
	ValuePair<int> id;
	ValuePair<float> averageDensity;
	ValuePair<float> averageLandValue;
};

struct District {
	ValuePair<std::string> name;
	ValuePair<std::string> preset;
	ValuePair<int> id;
	ValuePair<std::vector<Block>> blocks;
	ValuePair<float> averageLandValue;
	ValuePair<std::vector<ImVec2>> dominantEthnicities;
};

struct CityTile {

};

struct City
{
	ValuePair<std::string> name;
	ValuePair<ImVec2> size;
	//Population should reflect citizen array size
	ValuePair<int> playerAppartment;
	ValuePair<std::vector<District>> districts;
	ValuePair<std::vector<Street>> streets;
	ValuePair<std::vector<CityTile>> cityTiles;
	ValuePair<std::vector<Citizen>> cityTiles;
	ValuePair<std::vector<Interactable>> interactables;
	ValuePair<std::vector<Group>> groups;
	ValuePair<std::vector<Pipe>> pipes;
	ValuePair<std::vector<Criminal>> criminals;
	ValuePair<std::vector<MultiPage>> multiPage;
	ValuePair<std::vector<Meta>> metas;
};
