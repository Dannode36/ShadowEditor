#pragma once
#include <string>
#include <vector>
#include "ValuePair.h"

struct Descriptors {
	ValuePair<float> visualDistinctiveness;
	ValuePair<int> build;
	ValuePair<int> height;
	ValuePair<float> heightCM;
	ValuePair<float> weightKG;
	ValuePair<int> shoeSizes;
	ValuePair<int> footwear;

};

struct Citizen {
	ValuePair<int> humanID;
	ValuePair<int> home;
	ValuePair<int> job;
	ValuePair<std::string> birthday;
	ValuePair<float> societalClass;
	ValuePair<Descriptors> descriptors;
	ValuePair<int> blood;
	ValuePair<std::string> citizenName;
	ValuePair<std::string> firstName;
	ValuePair<std::string> casualName;
	ValuePair<std::string> surName;
	ValuePair<bool> homeless;
	ValuePair<float> slangUsage;
	ValuePair<float> genderScale;
	ValuePair<int> gender;
	ValuePair<int> bGender;
	ValuePair<float> sexuality;
	ValuePair<float> homosexuality;
	ValuePair<std::vector<int>> attractedTo;
	ValuePair<int> partner;
	ValuePair<int> paramour;
	ValuePair<std::string> anniversary;
	ValuePair<float> sleepNeedMultiplier;
	ValuePair<float> snoring;
	ValuePair<float> snoreDelay;
	ValuePair<float> humility;
	ValuePair<float> emotionality;
	ValuePair<float> extraversion;
	ValuePair<float> agreeableness;
	ValuePair<float> conscientiousness;
	ValuePair<float> creativity;

	//TODO traits and shit
	ValuePair<float> maxHealth;
	ValuePair<float> recoveryRate;
	ValuePair<float> combatSkill;
	ValuePair<float> combatHeft;
	ValuePair<float> maxNerve;
	ValuePair<float> breathRecovery;
	ValuePair<std::string> handwriting;
	ValuePair<int> sightingMemory;

	//TODO fav items and shite
	ValuePair<int> favCol;

};
