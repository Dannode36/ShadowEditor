#include "CityData.h"
#include "rapidjson/rapidjson.h"

inline void City::LoadCitizens(rapidjson::Document& doc) {
	rapidjson::Value* citizenJson = rapidjson::Pointer("citizens").Get(doc);
	citizens.jsonValue = citizenJson;
	citizens.value = std::vector<Citizen>(citizenJson->Size());

	for (int i = 0; i < citizenJson->Size(); i++) {
		/*citizens.value[i].agreeableness;
		citizens.value[i];
		citizens.value[i].anniversary;
		citizens.value[i].attractedTo;
		citizens.value[i].bGender;
		citizens.value[i].birthday;
		citizens.value[i].breathRecovery;
		citizens.value[i].combatHeft;
		citizens.value[i].combatSkill;
		citizens.value[i].conscientiousness;
		citizens.value[i].creativity;
		citizens.value[i].descriptors;
		citizens.value[i].emotionality;
		citizens.value[i].extraversion;
		citizens.value[i].favCol;*/
		//citizens.value[i].citizenName.jsonValue = citizenJson->GetArray()[i].GetObject()[""];
		citizens.value[i].casualName;
		citizens.value[i].firstName;
		citizens.value[i].surName;
		citizens.value[i].blood;
	}
}
