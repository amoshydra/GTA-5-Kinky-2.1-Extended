/*
	-- By the original Author --

	Dear Reader,

	I know you are probably pretty happy to have your hands on a simple peice of work.
	But please do not remove my credits from the menu, i worked hard on this menu and this release is for users to learn.
	Not for you to change the colors and the name and call it yours.

	If you do just note you are probably just a leeching faggot.
	Atleast make something useful out of it.


	AND TO ANYONE WHO IS NOT A LEECHING FAGGOT
	This code might be sloppy or bad, try to not judge me based on it.
	C++ was never my best language and this was the first biggest thing ive done with it.
	Feel free to edit anything you want EXPECT THE CREDITS and PM me on MPGH if you have a question on what does what.


	Love you all <3
	Femboy

	-- By myself, amoshydra --
	08 June 2015
	Additonal features and coding is made by amoshydra.
	Check CHANGELOG.log.

*/

#include <string>
#include <ctime>
#include <fstream>
#include <vector>

#include "onlinebypass.h"
#include "script.h"
#include "databases.h"

#pragma warning(disable : 4244 4305) // double <-> float conversions
int valuef;

//Functions prototypes
void update_features(); // Prototype


void output_writeToLog(std::string message, bool bAppend = true) {
	if (1){
		std::ofstream logfile;
		char* filename = "kinky2.log";
		if (bAppend)
			logfile.open(filename, std::ios_base::app);
		else
			logfile.open(filename);
		logfile << message + "\n";
		logfile.close();
	}
	return;
}

/**************************************/
// Button handling

// Config file
LPCSTR config_path = ".\\kinky2_config.ini";

int key_nav_open = GetPrivateProfileInt("navigation", "key_nav_open", 117, config_path);
int key_nav_open_2 = GetPrivateProfileInt("navigation", "key_nav_open_2", 111, config_path);
int key_nav_up = GetPrivateProfileInt("navigation", "key_nav_up", 104, config_path);
int key_nav_down = GetPrivateProfileInt("navigation", "key_nav_down", 98, config_path);
int key_nav_left = GetPrivateProfileInt("navigation", "key_nav_left", 100, config_path);
int key_nav_right = GetPrivateProfileInt("navigation", "key_nav_right", 102, config_path);
int key_nav_select = GetPrivateProfileInt("navigation", "key_nav_select", 101, config_path);
int key_nav_back = GetPrivateProfileInt("navigation", "key_nav_back", 96, config_path);

int key_veh_boost = GetPrivateProfileInt("vehicle", "key_veh_boost", 105, config_path);
int key_veh_stall = GetPrivateProfileInt("vehicle", "key_veh_stall", 99, config_path);
int key_veh_fire = GetPrivateProfileInt("vehicle", "key_veh_fire", 107, config_path);

DWORD trainerResetTime = 0;
bool get_key_pressed(int nVirtKey){
	return (GetAsyncKeyState(nVirtKey) & 0x8000) != 0; //Key is pressed down
}
bool trainer_switch_pressed() {
	return (GetTickCount() > trainerResetTime + 1000) && (get_key_pressed(key_nav_open) || get_key_pressed(key_nav_open_2));
}
void reset_trainer_switch() {
	trainerResetTime = GetTickCount();
}
void get_button_state(bool *select, bool *back, bool *up, bool *down, bool *left, bool *right) {
	if (select) *select = get_key_pressed(key_nav_select);
	if (back) *back = get_key_pressed(key_nav_back) || trainer_switch_pressed();
	if (up) *up = get_key_pressed(key_nav_up);
	if (down) *down = get_key_pressed(key_nav_down);
	if (left) *left = get_key_pressed(key_nav_left);
	if (right) *right = get_key_pressed(key_nav_right);

}
void get_button_state(bool *arrowLeft, bool *arrowRight) {
	if (arrowLeft) *arrowLeft = get_key_pressed(VK_NUMPAD7);
	if (arrowRight) *arrowRight = get_key_pressed(VK_NUMPAD9);
}

char* get_user_input(char windowTitle[] = "FMMC_KEY_TIP8", char defaultText[] = "", int maxCharacter = 200) {
	//FMMC_KEY_TIP8 = "Enter Message (MAX 60 characters):"

	WAIT(200); // Prevent accidental select input

	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(0, windowTitle, "", defaultText, "", "", "", maxCharacter);
	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0)
		WAIT(0);

	switch (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD()) {
	case 1:
		return GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
	default:
		return "";
	}
}

// Sound effects
void play_sound(char soundFile[15] = "SELECT") {
	// Example
	// 1. NAV_UP_DOWN
	// 2. NAV_LEFT_RIGHT
	// 3. SELECT
	// 4. BACK

	AUDIO::PLAY_SOUND_FRONTEND(-1, soundFile, "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
}
void play_sound(char soundFile[50], char soundLibrary[50]) {
	AUDIO::PLAY_SOUND_FRONTEND(-1, soundFile, soundLibrary, 0);
}


/**************************************/
// Message display

std::string statusText;
DWORD statusTextDrawTicksMax;
bool statusTextGxtEntry;
void update_status_text() {
	if (GetTickCount() < statusTextDrawTicksMax)
	{
		UI::SET_TEXT_FONT(4);
		UI::SET_TEXT_SCALE(0.55f, 0.55f);
		UI::SET_TEXT_COLOUR(243, 23, 84, 255);
		UI::SET_TEXT_WRAP(0.0f, 1.0f);
		UI::SET_TEXT_CENTRE(0);
		UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
		if (statusTextGxtEntry)
		{
			UI::_SET_TEXT_ENTRY((char *)statusText.c_str());
		}
		else
		{
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING((char *)statusText.c_str());
		}
		UI::_DRAW_TEXT(0.5, 0.5);
	}
}
void set_status_text(std::string str, DWORD time = 2500, bool isGxtEntry = false) {
	statusText = str;
	statusTextDrawTicksMax = GetTickCount() + time;
	statusTextGxtEntry = isGxtEntry;
}
void set_permstatus_text(std::string str, bool isGxtEntry = false) {
	statusText = str;
	statusTextGxtEntry = isGxtEntry;
}

// Help Text
void display_message_caption(char* text, int msToDisplay = 2500) {
	UI::_SET_TEXT_ENTRY_2("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_0x9D77056A530643F6(msToDisplay, 1);
}
// Notification
void display_message_notify(char* text) {
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING3(text);
	UI::_DRAW_NOTIFICATION(1, 1);
}
void display_message_notify(std::string text) {
	char textChar[1024];
	strncpy(textChar, text.c_str(), sizeof(textChar));
	textChar[sizeof(textChar) - 1] = 0;
	display_message_notify(textChar);
}
// Loading
bool loading_message_show(char* message = "loading") {
	bool bBack = false;
	get_button_state(NULL, &bBack, NULL, NULL, NULL, NULL);

	display_message_caption(message, 0);
	update_features();
	WAIT(0);

	if (bBack) return true;
	return false;
}
void loading_message_clear() {
	display_message_caption("", 1);
}


/**************************************/
// Menu Functions

bool bFeatureRecheck = false;

// Feature variable
bool featurePlayerInvincible = false;
bool featurePlayerInvincibleUpdated = false;
bool featurePlayerNeverWanted = false;
bool featurePlayerNeverWantedUpdated = false;
bool featurePlayerIgnored = false;
bool featurePlayerIgnoredUpdated = false;
bool featurePlayerUnlimitedAbility = false;
bool featurePlayerNoNoise = false;
bool featurePlayerNoNoiseUpdated = false;
bool featurePlayerFastSwim = false;
bool featurePlayerFastSwimUpdated = false;
bool featurePlayerFastRun = false;
bool featurePlayerFastRunUpdated = false;
bool featurePlayerSuperJump = false;
bool featurePlayerInvisible = false;

bool featureWeaponNoReload = false;
bool featureWeaponFireAmmo = false;
bool featureWeaponExplosiveAmmo = false;
bool featureWeaponExplosiveMelee = false;
bool featureWeaponVehRockets = false;
bool featureWeaponOneHit = false;

DWORD featureWeaponVehShootLastTime = 0;

bool featureVehInvincible = false;
bool featureVehInvincibleUpdated = false;
bool featureVehSpeedBoost = false;
bool featureVehWrapInSpawned = true;
bool featureVehRainbow = false;
bool featureVehStickyCar = false;
bool featureVehSlide = false;

bool featureWorldMoonGravity = false;
bool featureWorldRandomCops = false;
bool featureWorldRandomTrains = false;
bool featureWorldRandomBoats = false;
bool featureWorldGarbageTrucks = false;

bool featureTimePaused = false;
bool featureTimePausedUpdated = false;
bool featureTimeSynced = false;

bool featureWeatherWind = false;

bool featureMiscLockRadio = false;
bool featureMiscHideHud = false;
bool featureMiscMobileRadio = false;

int rainbowCount = 0;

// Weapons
void give_weaponsSets_to_ped(Ped playerPed, std::vector <LPCSTR> &weaponSet, int ammoSize = 0) {
	output_writeToLog("give_weaponsSets_to_ped: Processing");

	int weaponSetSize = (int)weaponSet.size();
	for (int i = 0; i < weaponSetSize; i++) {
		WEAPON::GIVE_WEAPON_TO_PED(playerPed, GAMEPLAY::GET_HASH_KEY((char *)weaponSet[i]), ammoSize, FALSE, TRUE);
	}

	WEAPON::GIVE_WEAPON_TO_PED(playerPed, GAMEPLAY::GET_HASH_KEY("WEAPON_UNARMED"), 1, FALSE, TRUE);

	output_writeToLog("give_weaponsSets_to_ped: Done");
}

// Teleport
void teleport_to_nearest_vehicle(){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vector3 coord = ENTITY::GET_ENTITY_COORDS(playerPed, true);

	int VehicleHandle = VEHICLE::GET_CLOSEST_VEHICLE(coord.x, coord.y, coord.z, 100.0, 0, 71);
	PED::SET_PED_INTO_VEHICLE(playerPed, VehicleHandle, -1);
};
void teleportEntity(Entity entity, Vector3 coords) {
	ENTITY::SET_ENTITY_COORDS_NO_OFFSET(entity, coords.x, coords.y, coords.z, 0, 0, 1);
}
void teleportEntity(Ped playerPed) {
	float forwardDistance, floatDistance;

	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
		forwardDistance = 6.0f;
		floatDistance = 0.5f;
	}
	else {
		forwardDistance = 2.5f;
		floatDistance = 0.8f;
	}
	Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0.0, forwardDistance, 0.0);
	coords.z += floatDistance;
	teleportEntity(playerPed, coords);
}

// Vehicle spawning
void spawn_vehicle(DWORD model, bool bWrapInSpawned = featureVehWrapInSpawned) {
	//common variable
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model)) {
		STREAMING::REQUEST_MODEL(model);
		while (!STREAMING::HAS_MODEL_LOADED(model))
			if (loading_message_show()) break;
		loading_message_clear();

		Vector3 coords = ENTITY::GET_ENTITY_COORDS(playerPed, true);
		float speed = 0.0f;

		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
			Vehicle veh_pre = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			speed = ENTITY::GET_ENTITY_SPEED(veh_pre) * 1.05f;
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh_pre, true, false);
			VEHICLE::DELETE_VEHICLE(&veh_pre);
		}

		Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

		if (bWrapInSpawned) {
			ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(playerPed));
			VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true);
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, speed);
			PED::SET_PED_INTO_VEHICLE(playerPed, veh, -1);
		}

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
		ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);
	}
}
void spawn_vehicle(LPCSTR modelName, bool bWrapInSpawned = featureVehWrapInSpawned) {
	if (modelName[0] == '0') {
		spawn_vehicle(strtol(modelName, NULL, 0), bWrapInSpawned);
	}
	spawn_vehicle(GAMEPLAY::GET_HASH_KEY((char *)modelName), bWrapInSpawned);
}

void update_vehicle_guns()
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Ped playerGroup = PED::GET_PED_GROUP_INDEX(PLAYER::PLAYER_PED_ID());

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed) || !featureWeaponVehRockets) return;

	bool bSelect = get_key_pressed(key_veh_fire); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_VEHICLE_ROCKET");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, 0);
			while (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
				if (loading_message_show()) break;
			loading_message_clear();
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1f);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1f);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);

		featureWeaponVehShootLastTime = GetTickCount();
	}
}

// Player check
bool bMonitorPlayerRespawn = false;
std::string gender = "male";

bool is_ped_default_player(Hash model){

	output_writeToLog("is_ped_default_player: Processing");

	int startIndex, endIndex;

	if (NETWORK::NETWORK_IS_IN_SESSION()) { // GTA MP
		startIndex = 1;
		endIndex = 2;
	}
	else {
		startIndex = 3;
		endIndex = 5;
	}
	
	for (int i = startIndex; i <= endIndex; i++) {
		if (GAMEPLAY::GET_HASH_KEY((char *)pedModels[0][i]) == model) {
			output_writeToLog("is_ped_default_player: Done > true");
			return true;
		}
	}

	output_writeToLog("is_ped_default_player: Done > false");
	return false;
}
bool is_ped_default_player(Ped playerPed){
	if (NETWORK::NETWORK_IS_IN_SESSION()) // GTA MP
		return is_ped_default_player(ENTITY::GET_ENTITY_MODEL(playerPed));
	else if (PED::GET_PED_TYPE(playerPed) <= 3) { // GTA SP
		output_writeToLog("is_ped_default_player: Done > true");
		return true;
	}
	return false;
	
}
int is_ped_animal(Hash model) {
	
	for (int i = 1; i < pedModels[2].size(); i++) {
		if (GAMEPLAY::GET_HASH_KEY((char *)pedModels[2][i]) == model) {
			if (i < 21) return 1;		// Land animal
			else if (i > 25) return 3;  // Aquatics
			else return 2;				// Birds
		}
	}
	
	return 0;
}
int is_ped_animal(Ped playerPed) {
	if (PED::GET_PED_TYPE(playerPed) == 28)
		return is_ped_animal(ENTITY::GET_ENTITY_MODEL(playerPed));
	return 0;
}

int ped_componentArr_now[13][3];
int ped_componentArr_max[13][3];

void ped_components_update(int component, int drawable, int texture, int palette) {
	ped_componentArr_now[component][0] = drawable;
	ped_componentArr_now[component][1] = texture;
	ped_componentArr_now[component][2] = palette;
}
void ped_components_update(Ped playerPed) {
	for (int i = 0; i < 13; i++) {
		ped_componentArr_now[i][0] = PED::GET_PED_DRAWABLE_VARIATION(playerPed, i);
		ped_componentArr_now[i][1] = PED::GET_PED_TEXTURE_VARIATION(playerPed, i);
		ped_componentArr_now[i][2] = 0;

		ped_componentArr_max[i][0] = PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(playerPed, i) - 1;
		ped_componentArr_max[i][1] = PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(playerPed, i, ped_componentArr_now[i][0]) - 1;
		ped_componentArr_max[i][2] = 0;
	}
}
void ped_components_randomise(Ped playerPed)  {
	
	int drawable, texture, palette, drawableLim, textureLim, paletteLim;
	for (int i = 0; i < 13; i++) {
		
		drawableLim = PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(playerPed, i);
		if (drawableLim > 0)	drawable = rand() % drawableLim;
		else					drawable = 0;

		textureLim = PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(playerPed, i, drawable);
		if (textureLim > 0)		texture = rand() % textureLim;
		else					texture = 0;
		
		paletteLim = PED::GET_PED_PALETTE_VARIATION(playerPed, i);
		if (paletteLim > 0)		palette = rand() % paletteLim;
		else					palette = 0;

		PED::SET_PED_COMPONENT_VARIATION(playerPed, i, drawable, texture, palette);
		ped_components_update(i, drawable, texture, palette);
	}
	if (rand() % 4)		PED::SET_PED_RANDOM_PROPS(playerPed);
	else				PED::CLEAR_ALL_PED_PROPS(playerPed);
}
void ped_components_restore(Ped playerPed, int componentArray[13][3] = ped_componentArr_now) {
	for (int i = 0; i < 13; i++) {
		PED::SET_PED_COMPONENT_VARIATION(playerPed, i, componentArray[i][0], componentArray[i][1], componentArray[i][2]);
	}
}

void set_player_model(Ped playerPed, Hash model, bool bRestore = false, bool bPedCheck = false, bool bGiveWeapon = true) {

	output_writeToLog("set_player_model: " + std::to_string(model) + " Processing");

	if (ENTITY::GET_ENTITY_MODEL(playerPed) == model) {
		output_writeToLog("set_player_model: Same model is used, Randomised appearance only");
		ped_components_randomise(playerPed);
		output_writeToLog("set_player_model: Done");
		return;
	}

	// Common variables
	Ped playerPed_new;
	bool isInVehicle = false;
	Vehicle drivingVeh;

	// Vehicle check
	if (!bRestore) {
		bMonitorPlayerRespawn = !is_ped_default_player(model);

		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
			isInVehicle = true;
			drivingVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		}
	}

	// Check for validity
	if ((STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))) {
		
		output_writeToLog("set_player_model: model is valid");

		// Change model
		STREAMING::REQUEST_MODEL(model);
		while (!STREAMING::HAS_MODEL_LOADED(model)) {
			if (loading_message_show()) return;
		}
		loading_message_clear();

		output_writeToLog("set_player_model: model is changing");
		PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
		output_writeToLog("set_player_model: model is changed");
		
		playerPed_new = PLAYER::PLAYER_PED_ID();

		PED::SET_PED_DEFAULT_COMPONENT_VARIATION(playerPed_new);

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);

		if (!bRestore) // Randomise ped component
			ped_components_randomise(playerPed_new);
		else
			ped_components_restore(playerPed_new);

		if (isInVehicle)
			PED::SET_PED_INTO_VEHICLE(playerPed_new, drivingVeh, -1);

		if (bGiveWeapon) {
			give_weaponsSets_to_ped(playerPed_new, weaponOnlineNames, 6000);
			if (!NETWORK::NETWORK_IS_IN_SESSION()) {
				give_weaponsSets_to_ped(playerPed_new, weaponRestrictedNames, 6000);
			}
		}

		if (bPedCheck) {
			int pedType_n = PED::GET_PED_TYPE(playerPed_new);
			if (pedType_n == 4)
				gender = "male";
			else if (pedType_n == 5)
				gender = "female";
		}
	}
	else
		output_writeToLog("ERROR change_player_model: " + std::to_string(model) + " doesn't exist.");

	output_writeToLog("set_player_model: " + std::to_string(model) + " Done");
}
void set_player_model(Ped playerPed, char *modelName, bool bRestore = false, bool bPedCheck = false, bool bGiveWeapon = true) {
	output_writeToLog("set_player_model: Converting model name to hash key");
	set_player_model(playerPed, GAMEPLAY::GET_HASH_KEY(modelName), bRestore, bPedCheck, bGiveWeapon);
}
void set_player_model(Ped playerPed, int indexType, int indexItem)  {

	output_writeToLog("set_player_model: Checking model");

	bool bGiveWeapon = true;
	bool bPedCheck = false;
	char pedType = pedModels[indexType][indexItem][0];
	char pedGender;
	int pedType_n = PED::GET_PED_TYPE(playerPed);

	output_writeToLog("set_player_model: Ped type acquired: " + to_string((char)pedType));

	// Manually check player
	if (pedType == 'a' || pedType == 'g' || pedType == 's' || pedType == 'u') // a g s u
		pedGender = pedModels[indexType][indexItem][2];
	else if (pedType == 'i' || pedType == 'c')	// ig cs csb
		pedGender = 'x';
	else if (pedType == 'p')
		pedGender = 'm';
	else // mp player
		pedGender = pedModels[indexType][indexItem][3];

	output_writeToLog("set_player_model: Ped gender: " + to_string(pedGender));

	// Second checking
	if (pedGender == 'm')
		gender = "male";
	else if (pedGender == 'f')
		gender = "female";

	else if (pedGender == 'c') { // Animal
		output_writeToLog("set_player_model: Ped is an animal");

		if (indexItem > 25) {
			if (!ENTITY::IS_ENTITY_IN_WATER(PLAYER::PLAYER_PED_ID())) {
				display_message_caption("Not in water. Fish not spawned.");
				return;
			}
		}
		else if (indexItem > 2) // Not chimp or rhesus
			bGiveWeapon = false;
	}
	else
		bPedCheck = true;

	output_writeToLog("set_player_model: Model is checked");
	set_player_model(playerPed, (char*)pedModels[indexType][indexItem], false, bPedCheck, bGiveWeapon);
}

Ped get_nearby_ped(Ped playerPed = PLAYER::PLAYER_PED_ID()) {
	const int numElements = 1;
	const int arrSize = numElements * 2 + 2;  // Start at index 2, and the odd elements are padding
	int peds[arrSize];
	
	peds[0] = numElements;	// 0 index is the size of the array

	if (PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), peds, -1))
		return peds[2];
	else return 0;
}

// Ped Sense
void blendIntoPeds() {
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Ped otherPed = get_nearby_ped();

	if (otherPed)
		set_player_model(playerPed, ENTITY::GET_ENTITY_MODEL(otherPed), false, true);
	else
		display_message_notify("No ped found");
}

// Check and change player model to default when wasted or busted. // This is to avoid inf loading loop	
void player_respawn_check() {
	// common variables
	//Player player = PLAYER::PLAYER_ID();

	// common variable
	Ped pedChecking = PLAYER::PLAYER_PED_ID();
	if (!ENTITY::DOES_ENTITY_EXIST(pedChecking)) return;

	Ped pedDefault = pedChecking;
	if (ENTITY::IS_ENTITY_DEAD(pedChecking) || PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), false)) {
		output_writeToLog("player_respawn_check: player is dead or busted");
		bFeatureRecheck = true;
		Hash model_pre = ENTITY::GET_ENTITY_MODEL(pedChecking);

		if (!NETWORK::NETWORK_IS_IN_SESSION()) { // Singleplayer

			bMonitorPlayerRespawn = !is_ped_default_player(pedChecking);

			if (!bMonitorPlayerRespawn) { // ped is already a default player
				// wait until loading screen is over.
				while (ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) ||
					PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), false))
					WAIT(0);
				return;
			}
			else {
				// change ped back to default player.
				output_writeToLog("player_respawn_check: Not default player, restoration required.");

				WAIT(2400);
				ENTITY::SET_ENTITY_VISIBLE(pedChecking, FALSE);
				set_player_model(pedChecking, "player_zero", true);

			}
		}

		// entity is an animal, do not change back.
		if (is_ped_animal(model_pre)) {
			bMonitorPlayerRespawn = false;
			return;
		}

		// wait until player is resurrected
		output_writeToLog("player_respawn_check: Resurrecting.");
		while (!CAM::IS_SCREEN_FADING_OUT()) WAIT(0);
		while (CAM::IS_SCREEN_FADING_OUT()) WAIT(0);
		while (CAM::IS_SCREEN_FADED_OUT()) WAIT(0);			// Wasted/Busted screen is gone.

		// Change back
		set_player_model(PLAYER::PLAYER_PED_ID(), model_pre, true);
		pedDefault = PLAYER::PLAYER_PED_ID();
		ENTITY::SET_ENTITY_COLLISION(pedDefault, TRUE, 0);
		teleportEntity(pedDefault);

		while (!CAM::IS_GAMEPLAY_CAM_RENDERING()) WAIT(0);	// Resurrecting
		output_writeToLog("player_respawn_check: model_pre is changed back");
	}
}

// Updates all features that can be turned off by the game, being called each game frame
void update_features() {
	
	if (bMonitorPlayerRespawn)
		player_respawn_check();

	update_status_text();
	update_vehicle_guns();

	// read default feature values from the game
	featureWorldRandomCops = (PED::CAN_CREATE_RANDOM_COPS() == TRUE);

	// common variables
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(playerPed);

	// player invincible
	if (featurePlayerInvincibleUpdated || bFeatureRecheck) {
		if (bPlayerExists)
			PLAYER::SET_PLAYER_INVINCIBLE(player, featurePlayerInvincible);
		featurePlayerInvincibleUpdated = false;
	}

	// player never wanted
	if (featurePlayerNeverWantedUpdated || bFeatureRecheck) {
		PLAYER::CLEAR_PLAYER_WANTED_LEVEL(player);
		if (bPlayerExists) {
			if (!featurePlayerNeverWanted)
				PLAYER::SET_MAX_WANTED_LEVEL(5);
			else
				PLAYER::SET_MAX_WANTED_LEVEL(0);
		}
		featurePlayerNeverWantedUpdated = false;
	}


	// police ignore player
	if (featurePlayerIgnoredUpdated) {
		if (bPlayerExists)
			PLAYER::SET_POLICE_IGNORE_PLAYER(player, featurePlayerIgnored);
		featurePlayerIgnoredUpdated = false;
	}

	// player special ability
	if (featurePlayerUnlimitedAbility) {
		if (bPlayerExists)
			PLAYER::_RECHARGE_SPECIAL_ABILITY(player, 1);
		output_writeToLog("update_features: special ability");
	}

	// player no noise
	if (featurePlayerNoNoiseUpdated) {
		if (bPlayerExists && !featurePlayerNoNoise)
			PLAYER::SET_PLAYER_NOISE_MULTIPLIER(player, 1.0f);
		featurePlayerNoNoiseUpdated = false;
		output_writeToLog("update_features: no noise check");
	}
	if (featurePlayerNoNoise) {
		PLAYER::SET_PLAYER_NOISE_MULTIPLIER(player, 0.0f);
		output_writeToLog("update_features: no noise check 2");
	}

	// player fast swim
	if (featurePlayerFastSwimUpdated) {
		if (bPlayerExists && !featurePlayerFastSwim)
			PLAYER::_SET_SWIM_SPEED_MULTIPLIER(player, 1.0f);
		featurePlayerFastSwimUpdated = false;
		output_writeToLog("update_features: fast swim check");
	}
	if (featurePlayerFastSwim) {
		PLAYER::_SET_SWIM_SPEED_MULTIPLIER(player, 1.49f);
		output_writeToLog("update_features: fast swim check 2");
	}

	// player fast run
	if (featurePlayerFastRunUpdated) {
		if (bPlayerExists && !featurePlayerFastRun)
			PLAYER::_SET_MOVE_SPEED_MULTIPLIER(player, 1.0f);
		featurePlayerFastRunUpdated = false;
	}
	if (featurePlayerFastRun)
		PLAYER::_SET_MOVE_SPEED_MULTIPLIER(player, 1.49f);

	// player super jump
	if (featurePlayerSuperJump) {
		if (bPlayerExists)
			GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(player);
	}

	// weapon
	if (featureWeaponFireAmmo) {
		if (bPlayerExists)
			GAMEPLAY::SET_FIRE_AMMO_THIS_FRAME(player);
	}
	if (featureWeaponOneHit) {
		if (bPlayerExists) {
			PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(player, 999999);
		}
	}
	if (featureWeaponExplosiveAmmo) {
		if (bPlayerExists)
			GAMEPLAY::SET_EXPLOSIVE_AMMO_THIS_FRAME(player);
	}
	if (featureWeaponExplosiveMelee) {
		if (bPlayerExists)
			GAMEPLAY::SET_EXPLOSIVE_MELEE_THIS_FRAME(player);
	}
	if (featurePlayerInvisible && bPlayerExists) {
		ENTITY::SET_ENTITY_VISIBLE(playerPed, false);
	}
	else {
		ENTITY::SET_ENTITY_VISIBLE(playerPed, true);
	}

	
	// weapon no reload
	if (bPlayerExists && featureWeaponNoReload)	{
		Hash cur;
		if (WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &cur, 1))
		{
			if (WEAPON::IS_WEAPON_VALID(cur)) {
				int maxAmmo;
				if (WEAPON::GET_MAX_AMMO(playerPed, cur, &maxAmmo)) {
					WEAPON::SET_PED_AMMO(playerPed, cur, maxAmmo);

					maxAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, cur, 1);
					if (maxAmmo > 0)
						WEAPON::SET_AMMO_IN_CLIP(playerPed, cur, maxAmmo);
				}
			}
		}
	}
	

	// player's vehicle invincible
	if (featureVehInvincibleUpdated) {
		if (bPlayerExists && !featureVehInvincible && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			ENTITY::SET_ENTITY_INVINCIBLE(veh, FALSE);
			ENTITY::SET_ENTITY_PROOFS(veh, 0, 0, 0, 0, 0, 0, 0, 0);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, 1);
			VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, 1);
			VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, 1);
		}
		featureVehInvincibleUpdated = false;
	}
	if (featureVehInvincible) {
		if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			ENTITY::SET_ENTITY_INVINCIBLE(veh, TRUE);
			ENTITY::SET_ENTITY_PROOFS(veh, 1, 1, 1, 1, 1, 1, 1, 1);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, 0);
			VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, 0);
			VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, 0);
		}
	}

	// player's vehicle boost
	if (featureVehSpeedBoost && bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		DWORD model = ENTITY::GET_ENTITY_MODEL(veh);

		bool bUp = get_key_pressed(key_veh_boost);
		bool bDown = get_key_pressed(key_veh_stall);

		if (bUp || bDown) {
			float speed = ENTITY::GET_ENTITY_SPEED(veh);
			if (bUp) {
				speed += speed * 0.05f;
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, speed);
			}
			else
				if (ENTITY::IS_ENTITY_IN_AIR(veh) || speed > 5.0)
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 0.0);
		}
	}

	// time pause
	if (featureTimePausedUpdated) {
		TIME::PAUSE_CLOCK(featureTimePaused);
		featureTimePausedUpdated = false;
	}

	// time sync
	if (featureTimeSynced) {
		time_t now = time(0);
		tm t;
		localtime_s(&t, &now);
		TIME::SET_CLOCK_TIME(t.tm_hour, t.tm_min, t.tm_sec);
	}

	// hide hud
	if (featureMiscHideHud)
		UI::HIDE_HUD_AND_RADAR_THIS_FRAME();

	if (featureVehSlide) {
		VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
	}
	else {
		VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
	}

	if (featureVehRainbow) {
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		DWORD model = ENTITY::GET_ENTITY_MODEL(veh);

		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0) && rainbowCount <= 0) {
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, rand() % 255, rand() % 255, rand() % 255);
			rainbowCount = 15;
		}
		else
			rainbowCount--;
	}

	if (featureVehStickyCar) {
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
			int myVehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(myVehicle);
		}
	}

	bFeatureRecheck = false;
	WAIT(0);
}




// Animation

char AnimDict_LastPlayed[100], AnimID_LastPlayed[70];
// Stop an animation using previously called animation;
void Animation_Stop(Ped playerPed = PLAYER::PLAYER_PED_ID(), char* AnimDict = AnimDict_LastPlayed, char* AnimID = AnimID_LastPlayed) {

	if (ENTITY::IS_ENTITY_PLAYING_ANIM(playerPed, AnimDict, AnimID, 1))
		ENTITY::STOP_ENTITY_ANIM(playerPed, AnimID, AnimDict, 1);
	else {
		AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
		display_message_caption("Failed to properly stop animation.");
	}
};
// Execute an animation given its dictionary name and clip name
bool Animation_Start(char* AnimDict, char* AnimID, bool bHasNext = false, int playType = 0, int duration = -1) {
	
	int playerPed = PLAYER::PLAYER_PED_ID();
	playType = (16 * playType) + 1;
	/* playType:
	 0 Full body
	 1 Upper body
	 2 Full body navigate enabled
	 3 Upper body walk enabled
	*/
	if (bHasNext) playType--; // Freeze last frame

	// 0. Stop previous animation
	if (ENTITY::IS_ENTITY_PLAYING_ANIM(playerPed, AnimDict_LastPlayed, AnimID_LastPlayed, 3))
		Animation_Stop(playerPed);

	// 1. Load dictionary
	if (!STREAMING::HAS_ANIM_DICT_LOADED(AnimDict))
		STREAMING::REQUEST_ANIM_DICT(AnimDict);

	// 2. Wait until dictionary is loaded
	while (!STREAMING::HAS_ANIM_DICT_LOADED(AnimDict))
		if (loading_message_show()) return true;
	loading_message_clear();

	// 3. Remember current animation
	strcpy(AnimDict_LastPlayed, AnimDict);
	strcpy(AnimID_LastPlayed, AnimID);

	// 4. Play animation
	if (STREAMING::HAS_ANIM_DICT_LOADED(AnimDict)) {
		
		AI::TASK_PLAY_ANIM(playerPed, AnimDict, AnimID, 8.0f, 0.0f, duration, playType, 0, 0, 0, 0);

		if (bHasNext) {
			while (ENTITY::GET_ENTITY_ANIM_CURRENT_TIME(playerPed, AnimDict, AnimID) < 0.90f)
				if (loading_message_show(".")) {
					WAIT(100);
					return true;
				}
			loading_message_clear();
		}
	}
	else
		display_message_caption("Error loading animation. Try again");
	return false;
}
// Execute an animation given its dictionary name and clip name with string to char* conversion
bool Animation_Start(std::string AnimDict, std::string AnimID, bool bHasNext = false, int playType = 0, int duration = -1) {
	char char_AnimDict[100];
	strncpy(char_AnimDict, AnimDict.c_str(), sizeof(char_AnimDict));
	char_AnimDict[sizeof(char_AnimDict) - 1] = 0;

	char char_AnimID[70];
	strncpy(char_AnimID, AnimID.c_str(), sizeof(char_AnimID));
	char_AnimID[sizeof(char_AnimID) - 1] = 0;

	return Animation_Start(char_AnimDict, char_AnimID, bHasNext, playType, duration);
};




/**************************************/
// UI Display

void draw_rect(float posX, float posY, float width, float height, int colourRed, int colourGreen, int colourBlue, int colourAlpha) {
	GRAPHICS::DRAW_RECT((posX + (width * 0.5f)), (posY + (height * 0.5f)), width, height, colourRed, colourGreen, colourBlue, colourAlpha);
}
void draw_menu_line(std::string caption, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool title, bool rescaleText = true) {
	// default values
	int text_col[4] = { 255, 255, 255, 255 },
		rect_col[4] = { 0, 0, 0, 140 };
	float text_scale = 0.50;
	int font = 4;

	// correcting values for active line
	if (active) {
		text_col[0] = 243;
		text_col[1] = 23;
		text_col[2] = 84;

		rect_col[0] = 0;
		rect_col[1] = 0;
		rect_col[2] = 0;
		rect_col[3] = 140;

		if (rescaleText) text_scale = 0.50;
	}

	if (title) {
		rect_col[0] = 51;
		rect_col[1] = 153;
		rect_col[2] = 255;
		rect_col[3] = 140;

		if (rescaleText) text_scale = 0.50;
		font = 1;
	}

	int screen_w, screen_h;
	GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);

	textLeft += lineLeft;

	float lineWidthScaled = lineWidth / (float)screen_w; // line width
	float lineTopScaled = lineTop / (float)screen_h; // line top offset

	float lineHeightScaled = lineHeight / (float)screen_h; // line height
	float lineLeftScaled = lineLeft / (float)screen_w;

	float textLeftScaled = textLeft / (float)screen_w; // text left offset

	// this is how it's done in original scripts

	// text upper part
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(0.0, text_scale);
	UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)caption.c_str());
	UI::_DRAW_TEXT(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));

	// text lower part
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(0.0, text_scale);
	UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_GXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)caption.c_str());
	int num25 = UI::_0x9040DFB09BE75706(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));

	// rect
	draw_rect(lineLeftScaled, lineTopScaled + (0.00278f),
		lineWidthScaled, ((((float)(num25)* UI::_0xDB88A37483346780(text_scale, 0)) + (lineHeightScaled * 1.5f)) + 0.004f),
		rect_col[0], rect_col[1], rect_col[2], rect_col[3]);
}

void draw_menu_line(std::string caption, int index, float lineHeight, bool active = false) {
	float defaultSpace = 22;
	float lineTop;
	float titleTop = 60;

	if ((lineHeight / 2) == 0) // odd number
		lineHeight += 1;

	lineTop = titleTop + index * ((lineHeight * 1.5f) + defaultSpace);
	draw_menu_line(caption, 250, lineHeight, lineTop, 1000.0f, 7.0f, active, false);
}
std::string line_as_str(std::string text, bool *pState) {
	while (text.size() < 18) text += " ";
	return text + (pState ? (*pState ? ": ON" : ": OFF") : "");
}


// Menu navigation with up, down, select and back // Back with -1, Select with 1, else 0
int menu_list_navigate(DWORD *waitTime, int *active_line, const int line_count) {
	bool bSelect, bBack, bUp, bDown;
	get_button_state(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);

	int line_location = *active_line;

	if (bBack || trainer_switch_pressed()) {
		play_sound("BACK");
		return -1;
	}
	if (bUp) {
		play_sound("NAV_UP_DOWN");
		if (line_location == 0)
			line_location = line_count;
		line_location--;
		*waitTime = 80;
	}
	if (bDown) {
		play_sound("NAV_UP_DOWN");
		line_location++;
		if (line_location == line_count)
			line_location = 0;
		*waitTime = 80;
	}

	if (bSelect) {
		play_sound("SELECT");
		*waitTime = 200;
		return 1;
	}
	*active_line = line_location;
	return 0;
}
// Menu navigation with up, down, left, right, select and back // Back with -1, Select with 1, else 0
template <typename T>
int menu_list_navigate(DWORD *waitTime, int *active_line, int *active_tab, std::vector< std::vector <T> > &menu_lines, int *startIndex, int *endIndex, bool bHasNameVector) {
	bool bSelect, bBack, bUp, bDown, bLeft, bRight;
	get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

	int line_location = *active_line;
	int tab_location = *active_tab;
	int line_count = (int)menu_lines[tab_location].size();;
	int tab_count = (int)menu_lines.size();
	int tab_index_offset = 1;
	int tab_start_index = 0;

	if (bHasNameVector) {
		tab_index_offset = 2;
		tab_start_index = 1;
	}


	if (bBack || trainer_switch_pressed()) {
		play_sound("BACK");
		return -1;
	}
	if (bUp) {
		play_sound("NAV_UP_DOWN");
		if (line_location <= 1)
			line_location = line_count;
		line_location--;
		*waitTime = 80;
	}
	if (bDown) {
		play_sound("NAV_UP_DOWN");
		line_location++;
		if (line_location >= line_count)
			line_location = 1;
		*waitTime = 80;
	}

	if (bRight)	{
		play_sound("NAV_LEFT_RIGHT");
		tab_location += tab_index_offset;
		if (tab_location > tab_count - 1)
			tab_location = tab_start_index;
		*waitTime = 150;
		*startIndex = 1;
		*endIndex = 15;
	}
	if (bLeft) {
		play_sound("NAV_LEFT_RIGHT");
		tab_location -= tab_index_offset;
		if (tab_location < tab_start_index)
			tab_location = tab_count - 1;
		*waitTime = 150;
		*startIndex = 1;
		*endIndex = 15;
	}

	// Correction
	line_count = (int)menu_lines[tab_location].size();
	if (line_location >= line_count)
		line_location = line_count - 1;

	if (bSelect) {
		play_sound("SELECT");
		*waitTime = 200;
		return 1;
	}
	*active_line = line_location;
	*active_tab = tab_location;
	return 0;
}
// Menu navigation with back button only. // Back with -1, else 0
int menu_list_navigate(DWORD *waitTime) {
	bool bSelect, bBack, bUp, bDown;
	get_button_state(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);

	if (bBack || trainer_switch_pressed()) {
		play_sound("BACK");
		return -1;
	}
	return 0;
}




// To draw the trainer menu consisting boolean elements
void menu_list_draw(menuList_boolean menu_lines[], int lineCount, std::string caption, int active_line, DWORD *ptr_waitTime, float lineHeight = 9.0f, float lineWidth = 250.0f) {

	// timed menu draw, used for pause after active line switch
	DWORD waitTime = *ptr_waitTime;
	DWORD maxTickCount = GetTickCount() + waitTime;

	do {
		// Header
		draw_menu_line(caption, lineWidth, 13.0, 18.0, 1000.0, 3.0, false, true);

		// Menu List
		for (int i = 0; i < lineCount; i++) {
			if (i != active_line) {
				draw_menu_line(line_as_str(menu_lines[i].text, menu_lines[i].pState),
					i, lineHeight, false);
			}
		}

		// Active Line
		draw_menu_line(line_as_str(menu_lines[active_line].text, menu_lines[active_line].pState),
			active_line, lineHeight, true);

		update_features();
	} while (GetTickCount() < maxTickCount);

	// Reset waitTime
	*ptr_waitTime = 0;
}

// To draw the trainer menu with string output only
template <typename T>
void menu_list_draw(T menu_lines[], int lineCount, std::string caption, int active_line, DWORD *ptr_waitTime, bool bNavigation = true, float lineHeight = 9.0f, float lineWidth = 250.0f) {

	// timed menu draw, used for pause after active line switch
	DWORD waitTime = *ptr_waitTime;
	DWORD maxTickCount = GetTickCount() + waitTime;

	do {
		// Header
		draw_menu_line(caption, lineWidth, 13.0, 18.0, 1000.0, 3.0, false, true);

		// Menu List
		for (int i = 0; i < lineCount; i++) {
			if (i != active_line || !bNavigation) {
				draw_menu_line(menu_lines[i].text, i, lineHeight, false);
			}
		}

		// Active Line
		if (bNavigation)
			draw_menu_line(menu_lines[active_line].text, active_line, lineHeight, true);

		update_features();
	} while (GetTickCount() < maxTickCount);

	// Reset waitTime
	*ptr_waitTime = 0;
}

template <typename T>
void menu_list_draw(std::vector <T> &menu_lines, std::string caption, int active_line, int *ptr_startIndex, int *ptr_endIndex, DWORD *ptr_waitTime, float lineHeight = 9.0f, float lineWidth = 250.0f) {
	
	DWORD waitTime = *ptr_waitTime;
	DWORD maxTickCount = GetTickCount() + waitTime;

	int menu_offSet;
	int startIndex = *ptr_startIndex;
	int endIndex = *ptr_endIndex;

	do {
		if (endIndex >= menu_lines.size())
			endIndex = (int)menu_lines.size() - 1;

		if (active_line > endIndex) {
			menu_offSet = active_line - endIndex;
			startIndex += menu_offSet;
			endIndex += menu_offSet;
		}
		else if (active_line < startIndex) {
			menu_offSet = active_line - startIndex;
			startIndex += menu_offSet;
			endIndex += menu_offSet;
		}

		// Print Header
		draw_menu_line(caption, 250.0, 13.0, 18.0, 1000.0, 3.0, false, true);

		// Print List
		for (int i = startIndex; i <= endIndex; i++) {
			if (i != active_line)
				draw_menu_line(menu_lines[i], i - startIndex, lineHeight);
		}

		// Print cursor
		draw_menu_line(menu_lines[active_line], active_line - startIndex, lineHeight, true);

		update_features();

	} while (GetTickCount() < maxTickCount);

	*ptr_startIndex = startIndex;
	*ptr_endIndex = endIndex;
}

// To draw the trainer menu with vector and convey the navigation result. // Back with -1, Select with 1
int menu_line_process_reflow(std::vector< std::vector <LPCSTR> > &menu_lines, int *ptr_active_line, int *ptr_active_tab,
							int *ptr_startIndex, int *ptr_endIndex, DWORD *ptr_waitTime, bool bHasNameVector = false,
							float lineHeight = 9.0f, float lineWidth = 250.0f) {

	// Menu respond setup
	DWORD waitTime = *ptr_waitTime;
	DWORD maxTickCount = GetTickCount() + waitTime;

	// Menu initial value
	int active_line = *ptr_active_line;
	int active_tab = *ptr_active_tab;
	int currentTabSize = (int)menu_lines.size();
	int navigationResult;

	// Reflow settings
	int startIndex = *ptr_startIndex;
	int endIndex = *ptr_endIndex;
	int menu_offSet;

	do {
		if (endIndex >= menu_lines[active_tab].size())
			endIndex = (int)menu_lines[active_tab].size() - 1;

		if (active_line > endIndex) {
			menu_offSet = active_line - endIndex;
			startIndex += menu_offSet;
			endIndex += menu_offSet;
		}
		else if (active_line < startIndex) {
			menu_offSet = active_line - startIndex;
			startIndex += menu_offSet;
			endIndex += menu_offSet;
		}

		// Print Header
		draw_menu_line(menu_lines[active_tab][0], 250.0, 13.0, 18.0, 1000.0, 3.0, false, true);

		// Print List
		for (int i = startIndex; i <= endIndex; i++) {
			if (i != active_line)
				draw_menu_line(menu_lines[active_tab][i], i - startIndex, lineHeight);
		}

		// Print cursor
		draw_menu_line(menu_lines[active_tab][active_line], active_line - startIndex, lineHeight, true);

		update_features();

	} while (GetTickCount() < maxTickCount);

	// Reset waitTime
	waitTime = 0;

	navigationResult = menu_list_navigate(&waitTime, &active_line, &active_tab, menu_lines, &startIndex, &endIndex, bHasNameVector);

	// Return result
	*ptr_waitTime = waitTime;
	*ptr_active_line = active_line;
	*ptr_active_tab = active_tab;
	*ptr_startIndex = startIndex;
	*ptr_endIndex = endIndex;

	return navigationResult;
}

// To draw the trainer menu with vector and convey the navigation result. // Back with -1, Select with 1
template <typename T>
int menu_line_process_reflow(std::vector< std::vector <T> > &menu_lines, int *ptr_active_line, int *ptr_active_tab, 
							int *ptr_startIndex, int *ptr_endIndex, DWORD *ptr_waitTime, bool bHasNameVector = false,
							float lineHeight = 9.0f, float lineWidth = 250.0f) {

	// Menu respond setup
	DWORD waitTime = *ptr_waitTime;
	DWORD maxTickCount = GetTickCount() + waitTime;

	// Menu initial value
	int active_line = *ptr_active_line;
	int active_tab = *ptr_active_tab;
	int currentTabSize = (int)menu_lines.size();
	int navigationResult;

	// Reflow settings
	int startIndex = *ptr_startIndex;
	int endIndex = *ptr_endIndex;
	int menu_offSet;

	do {
		if (endIndex >= menu_lines[active_tab].size())
			endIndex = (int)menu_lines[active_tab].size() - 1;

		if (active_line > endIndex) {
			menu_offSet = active_line - endIndex;
			startIndex += menu_offSet;
			endIndex += menu_offSet;
		}
		else if (active_line < startIndex) {
			menu_offSet = active_line - startIndex;
			startIndex += menu_offSet;
			endIndex += menu_offSet;
		}

		// Print Header
		draw_menu_line(menu_lines[active_tab][0].text, 250.0, 13.0, 18.0, 1000.0, 3.0, false, true);

		// Print List
		for (int i = startIndex; i <= endIndex; i++) {
			if (i != active_line)
				draw_menu_line(menu_lines[active_tab][i].text, i - startIndex, lineHeight);
		}

		// Print cursor
		draw_menu_line(menu_lines[active_tab][active_line].text, active_line - startIndex, lineHeight, true);

		update_features();

	} while (GetTickCount() < maxTickCount);

	// Reset waitTime
	waitTime = 0;

	navigationResult = menu_list_navigate(&waitTime, &active_line, &active_tab, menu_lines, &startIndex, &endIndex, bHasNameVector);

	// Return result
	*ptr_waitTime = waitTime;
	*ptr_active_line = active_line;
	*ptr_active_tab = active_tab;
	*ptr_startIndex = startIndex;
	*ptr_endIndex = endIndex;

	return navigationResult;
}


// To update boolean of a menu line
void menu_list_feature_toggle(menuList_boolean lines[], int active_line) {
	if (lines[active_line].pState)
		*lines[active_line].pState = !(*lines[active_line].pState);
	if (lines[active_line].pUpdated)
		*lines[active_line].pUpdated = true;
}

int active_home_player_gameplay = 0;
void  menu_home_player_gameplay__action(menuList_boolean menu_lines[], int *ptr_active_line) {

	int active_line = *ptr_active_line;

	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	switch (active_line) {
	case 0: // wanted up
		if (bPlayerExists && PLAYER::GET_PLAYER_WANTED_LEVEL(player) < 5) {
			PLAYER::SET_PLAYER_WANTED_LEVEL(player, PLAYER::GET_PLAYER_WANTED_LEVEL(player) + 1, 0);
			PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, 0);
		}
		break;

	case 1: // wanted down
		if (bPlayerExists && PLAYER::GET_PLAYER_WANTED_LEVEL(player) > 0) {
			PLAYER::SET_PLAYER_WANTED_LEVEL(player, PLAYER::GET_PLAYER_WANTED_LEVEL(player) - 1, 0);
			PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, 0);
		}
		break;
		// switchable features
	default:
		menu_list_feature_toggle(menu_lines, active_line);
	}
}
void  menu_home_player_gameplay__display(std::string caption, DWORD waitTime = 150) {
	// Menu Labels
	const int LINE_COUNT = 11;
	menuList_boolean menu_home_player_gameplay[LINE_COUNT] = {
		/*  0 */{ "Wanted Up", NULL, NULL },
		/*  1 */{ "Wanted Down", NULL, NULL },
		/*  2 */{ "Never Wanted", &featurePlayerNeverWanted, &featurePlayerNeverWantedUpdated },
		/*  3 */{ "Godmode", &featurePlayerInvincible, &featurePlayerInvincibleUpdated },
		/*  4 */{ "Fast Run", &featurePlayerFastRun, &featurePlayerFastRunUpdated },
		/*  5 */{ "Super Jump", &featurePlayerSuperJump, NULL },
		/*  6 */{ "Silent", &featurePlayerNoNoise, &featurePlayerNoNoiseUpdated },
		/*  7 */{ "Police Ignore", &featurePlayerIgnored, &featurePlayerIgnoredUpdated },
		/*  8 */{ "Infinite Ability", &featurePlayerUnlimitedAbility, NULL },
		/*  9 */{ "Fast Swim", &featurePlayerFastSwim, &featurePlayerFastSwimUpdated },
		/* 10 */{ "Invisible", &featurePlayerInvisible, NULL }
	};

	menuList_boolean *current_menu = menu_home_player_gameplay;
	int *current_line = &active_home_player_gameplay;

	// Menu Setup and Navigation
	int navigationResult;
	while (true) {
		// draw menu and navigation path
		menu_list_draw(current_menu, LINE_COUNT, caption, *current_line, &waitTime);
		navigationResult = menu_list_navigate(&waitTime, current_line, LINE_COUNT);

		if (navigationResult == -1)
			break;
		else if (navigationResult == 1) {
			menu_home_player_gameplay__action(current_menu, current_line);
		}
	}
}

int active_home_misc_credits = 0;
void  menu_home_misc_credits__display(std::string caption)
{
	// Menu Labels
	const int LINE_COUNT = 8;
	menuList menu_home_misc_credits[LINE_COUNT] = {
		//PLEASE DO NOT REMOVE THESE YOU CAN ADD YOURSELF BUT DO NOT REMOVE THEM.
		//Please refer to the note at the top of this.
		{ "Created By " },
		{ "    Trevor (Pomfeh)" },
		{ "    DrWhat" },
		{ "    xDarkStarrx" },
		{ "    Kryptus" },
		{ "    BigBrainAFK" },
		{ "Additional refinement" },
		{ "    amoshydra" }
	};

	menuList *current_menu = menu_home_misc_credits;
	int *current_line = &active_home_misc_credits;

	// Menu Setup and Navigation
	int navigationResult;
	DWORD waitTime = 150;
	while (true) {
		// draw menu and navigation path
		menu_list_draw(current_menu, LINE_COUNT, caption, *current_line, &waitTime, false);
		navigationResult = menu_list_navigate(&waitTime);

		if (navigationResult == -1)
			break;
	}
}

// DEBUG START //

bool debug_collision_control_x = true;
int debug_door_type = 0;
DWORD debug_door_crack = 0;
DWORD currentI = 0;
char debug_stringA[100] = "anim@move_hostages@female";
char debug_stringB[100] = "female_idle";
char debug_stringC[20] = "1";
char debug_stringD[20] = "-1";

DWORD doorTypes[] = {
	9467943, 157484608, 245182344, 437009729, 450182863, 452874391, 543652229, 546378757, 575680671, 668467214,
	1230099731, 1309269072, 1335309163, 1425919976, 1713150633, 1713150633, 2243315674, 2265074802, 3060202522,
	3082015943, 3324172348, 3419809524, 3526235576, 3613901090, 3639771207, 3639771207, 3687927243, 3799246327, 3945237283
};

int active_home_misc_debug = 0;
void  menu_home_misc_debug__action(menuList_boolean menu_lines[], int *ptr_active_line){

	int active_line = *ptr_active_line;

	// common variable
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh_pre = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	Vector3 coordsPed = ENTITY::GET_ENTITY_COORDS(playerPed, 1);
	DWORD doorType;
	DWORD doorType2 = strtoul(debug_stringA, NULL, 10);
	DWORD limitDoor;
	BOOL bClose;
	float elevation, height;
	float doorHeading;

	std::string status;

	switch (active_line) {
		case 0:
			AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
			WAIT(100);
			strcpy(debug_stringC, get_user_input("HUD_TARG", debug_stringC));
			WAIT(50);
			strcpy(debug_stringD, get_user_input("FMMC_MPM_NA", debug_stringD));
			WAIT(50);
			Animation_Start(debug_stringA, debug_stringB, true, atoi(debug_stringD), atoi(debug_stringC));
			break;
		case 1:
			Animation_Start(debug_stringA, debug_stringB);
			break;
		case 2:
			STREAMING::REQUEST_IPL(debug_stringB);
			break;
		case 3:
			STREAMING::REMOVE_IPL(debug_stringB);
			break;
		case 4:
			OBJECT::GET_STATE_OF_CLOSEST_DOOR_OF_TYPE(doorType2, coordsPed.x, coordsPed.y, coordsPed.z, &bClose, &doorHeading);
			status = std::to_string(doorType2) + " is closed = " + std::to_string(bClose) + " at " + std::to_string(doorHeading);
			break;
		case 5:
			OBJECT::SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(doorType2, coordsPed.x, coordsPed.y, coordsPed.z, TRUE, 0, FALSE);
			break;
		case 6:
			OBJECT::SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(doorType2, coordsPed.x, coordsPed.y, coordsPed.z, FALSE, 0, FALSE);
			break;
		case 7:	
			limitDoor = debug_door_crack * 20000000;
			output_writeToLog("entering: " + to_string(currentI));
			for (currentI; currentI < (20000000 + limitDoor); currentI++) {
				OBJECT::GET_STATE_OF_CLOSEST_DOOR_OF_TYPE(currentI, coordsPed.x, coordsPed.y, coordsPed.z, &bClose, &doorHeading);

				if (bClose == TRUE) {
					status = "Found: " + to_string(currentI);
					output_writeToLog("Found: " + to_string(currentI));
					currentI++;
					break;
				}
			}
			debug_door_crack++;
			break;
		case 8:
			doorType = doorTypes[debug_door_type];
			status = "unlocking: " + std::to_string(doorType);
			OBJECT::SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(doorType, coordsPed.x, coordsPed.y, coordsPed.z, FALSE, 0, FALSE);
			debug_door_type++;
			if (debug_door_type > 28)
				debug_door_type = 0;
			break;
		case 9:
			for (int i = 0; i <= 28; i++)
				OBJECT::SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(doorTypes[i], coordsPed.x, coordsPed.y, coordsPed.z, TRUE, 0, FALSE);
			break;
		case 10:
			strcpy(debug_stringA, get_user_input("HUD_TARG", debug_stringA));
			WAIT(200);
			strcpy(debug_stringB, get_user_input("FMMC_MPM_NA", debug_stringB));
			break;
		
		case 11:
			GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coordsPed.x, coordsPed.y, coordsPed.z, &elevation);
			WATER::GET_WATER_HEIGHT(coordsPed.x, coordsPed.y, coordsPed.z, &height);
			status = "Ped : " + std::to_string(PED::GET_PED_TYPE(playerPed)) + "\n" +
				"Male? : " + std::to_string(PED::IS_PED_MALE(playerPed)) + "\n" +
				"Elevation : " + std::to_string(elevation) + "\n" +
				"Height : " + std::to_string(height);
			break;
		
		case 12:
			ped_components_update(playerPed);
			break;

		case 13:
			Ped playerPed = PLAYER::PLAYER_PED_ID();

			const int numElements = 1;
			const int arrSize = numElements * 2 + 2;  //Start at index 2, and the odd elements are padding
			int peds[arrSize];
			//0 index is the size of the array
			peds[0] = numElements;

			if (PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), peds, -1) != 0) {
				AUDIO::_PLAY_AMBIENT_SPEECH1(peds[2], "CHAT_STATE", "SPEECH_PARAMS_FORCE");
				while (AUDIO::IS_AMBIENT_SPEECH_PLAYING(peds[2])) WAIT(0);
				AUDIO::_PLAY_AMBIENT_SPEECH1(PLAYER::PLAYER_PED_ID(), "CHAT_RESP", "SPEECH_PARAMS_FORCE");
			}
			else
				display_message_notify("failed");
			break;
	}
	set_status_text(status, 7000UL);
}
void  menu_home_misc_debug__display(std::string caption) {
	// Menu Labels
	const int LINE_COUNT = 14;
	menuList_boolean menu_home_misc_debug[LINE_COUNT] = {
		/*  0 */ { "Animate once", NULL, NULL },
		/*  1 */ { "Animate", NULL, NULL },
		/*  2 */ { "Request IPL", NULL, NULL },
		/*  3 */ { "Remove IPL", NULL, NULL },
		/*  4 */ { "GET STATE DOOR ", NULL, NULL },
		/*  5 */ { "Manual Lock", NULL, NULL },
		/*  6 */ { "Manual Unlock", &debug_collision_control_x, NULL },
		/*  7 */ { "Crack door", NULL, NULL },
		/*  8 */ { "Unlock closest door", NULL, NULL },
		/*  9 */ { "Lock all array door", NULL, NULL },
		/* 10 */ { "Input 2 strings", NULL, NULL},
		/* 11 */ { "Check ped type", NULL, NULL},
		/* 12 */ { "Component changer", NULL, NULL},
		/* 13 */ { "Initiate chat", NULL, NULL}
	};

	menuList_boolean *current_menu = menu_home_misc_debug;
	int *current_line = &active_home_misc_debug;

	// Menu Setup and Navigation
	int navigationResult;
	DWORD waitTime = 150;
	while (true) {
		// draw menu and navigation path
		menu_list_draw(current_menu, LINE_COUNT, caption, *current_line, &waitTime);
		navigationResult = menu_list_navigate(&waitTime, current_line, LINE_COUNT);

		if (navigationResult == -1)
			break;
		else if (navigationResult == 1) {
			menu_home_misc_debug__action(current_menu, current_line);
		}
	}
}

// DEBUG END //

int active_home_misc_stats_unlocks = 0;
void  menu_home_misc_stats_unlocks__action(int *ptr_active_line) {

	int active_line = *ptr_active_line;

	switch (active_line) {
	case 0:
		if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()))	{
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, true);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, true);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, true);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, true);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, true);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, true);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, true);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 100, true);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 100, true);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 100, true);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 100, true);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 100, true);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 100, true);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 100, true);
		}
		break;
	case 1:
		if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()))	{
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_7"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_3"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_4"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_5"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_6"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_7"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_3"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_4"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_5"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_6"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_7"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_3"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_4"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_5"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_6"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_7"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_3"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_4"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_5"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_6"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_7"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_3"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_4"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_5"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_6"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_7"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_8"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_9"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_10"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_OUTFIT"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_3"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_4"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_5"), -1, 1);;
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_6"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_7"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_3"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_4"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_5"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_6"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_7"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_3"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_4"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_5"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_6"), -1, 1);;
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_7"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_3"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_4"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_5"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_6"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_7"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_3"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_4"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_5"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_6"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_7"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_3"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_4"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_5"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_6"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_7"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_8"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_9"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_10"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_OUTFIT"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TORSO"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_3"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_4"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_5"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_6"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_7"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL2_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_DECL"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH_2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TORSO"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_3"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_4"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_5"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_6"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_7"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL2_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_DECL"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH_2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_0"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_3"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_4"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_5"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_6"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_7"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_8"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_9"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_10"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_11"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_12"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_13"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_14"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_15"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_16"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_17"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_18"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_19"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_21"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_22"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_23"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_24"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_24"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_25"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_26"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_27"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_28"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_29"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_30"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_31"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_32"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_33"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_34"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_35"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_36"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_37"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_38"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_39"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_40"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHESGV_BS_3"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_4"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_5"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_6"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_7"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_8"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_9"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_13"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
		}
		break;
	case 2:
		if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()))	{
			STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMRACEWORLDRECHOLDER"), 1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_ENEMYDRIVEBYKILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_USJS_COMPLETED"), 50, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_USJS_FOUND"), 50, 0);
			STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMWINALLRACEMODES"), 1, 0);
			STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMWINEVERYGAMEMODE"), 1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DB_PLAYER_KILLS"), 1000, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_KILLS_PLAYERS"), 1000, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMHORDWAVESSURVIVE"), 21, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TDM_MVP"), 60, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_HOLD_UP_SHOPS"), 20, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_RACES_WON"), 101, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_NO_ARMWRESTLING_WINS"), 21, 0);
			STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMATTGANGHQ"), 1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMBBETWIN"), 50000, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 51, 0);
			STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMFULLYMODDEDCAR"), 1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_TOTALKILLS"), 500, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_DM_TOTAL_DEATHS"), 412, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_PLAYER_HEADSHOTS"), 623, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 63, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TDM_WINS"), 13, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_GTA_RACES_WON"), 12, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_GOLF_WON"), 2, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_TG_WON"), 2, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_RT_WON"), 2, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_CT_WON"), 2, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_GRAN_WON"), 2, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TENNIS_WON"), 2, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TENNIS_MATCHES_WON"), 2, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_WON"), 101, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_LOST"), 36, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_25_KILLS_STICKYBOMBS"), 50, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_50_KILLS_GRENADES"), 50, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS "), 50, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_20_KILLS_MELEE"), 50, 0);
		}
		break;
	case 3: //tattoooss
		if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()))	{
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_1"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_2"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_3"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_4"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_5"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_6"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_7"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_8"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_9"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_10"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_11"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_12"), -1, 1);
		}
		break;
	case 4:	//snacks/armor
		if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()))	{
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_YUM_SNACKS"), 99999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_HEALTH_SNACKS"), 99999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_EPIC_SNACKS"), 99999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CIGARETTES_BOUGHT"), 99999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NUMBER_OF_ORANGE_BOUGHT"), 99999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NUMBER_OF_BOURGE_BOUGHT"), 99999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_WHITE"), 999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_WHITE"), 999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_WHITE"), 999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_WHITE"), 999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_RED"), 999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_RED"), 999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_RED"), 999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_RED"), 999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_BLUE"), 999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_BLUE"), 999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_BLUE"), 999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_BLUE"), 999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ARMOUR_1_COUNT"), 9999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ARMOUR_2_COUNT"), 9999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ARMOUR_3_COUNT"), 9999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ARMOUR_4_COUNT"), 9999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP_CHAR_ARMOUR_5_COUNT"), 9999, 0);
		}
		break;
	case 5:
		if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()))	{
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHAS E"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHAS E2"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHAS E3"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHAS E4"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHAS E5"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHAS E6"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHAS E7"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHAS E8"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHAS E9"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHAS E10"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHAS E11"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHAS E12"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_1_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_2_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_3_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_4_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_5_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_6_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_7_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_8_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_9_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_10_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_11_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_12_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_races_won"), 100, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_number_turbo_starts_in_race"), 100, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_usjs_found"), 50, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_usjs_completed"), 50, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_awd_fmwinairrace"), 50, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_awd_fmwinsearace"), 50, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_awd_fmrallywonnav"), 50, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_awd_fmrallywondrive "), 500, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_awd_fm_races_fastest_lap"), 500, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_char_fm_carmod_0_unlck"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_char_fm_carmod_1_unlck"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_char_fm_carmod_2_unlck"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_char_fm_carmod_3_unlck"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_char_fm_carmod_4_unlck"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_char_fm_carmod_5_unlck"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_char_fm_carmod_6_unlck"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_char_fm_carmod_7_unlck"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_VEHICLE_1_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_VEHICLE_2_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_ABILITY_1_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_ABILITY_2_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_ABILITY_3_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_1_COLLECT"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_2_COLLECT"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_3_COLLECT"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_4_COLLECT"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_5_COLLECT"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_6_COLLECT"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_7_COLLECT"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_8_COLLECT"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_9_COLLECT"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_HEALTH_1_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_HEALTH_2_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_HOLDUPS_BITSET"), -1, 0);
		}
		break;
	case 6:
		if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()))	{
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MOLOTOV_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CMBTPISTOL_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_PISTOL50_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_APPISTOL_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MICROSMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ASLTSMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ASLTRIFLE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CRBNRIFLE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADVRIFLE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CMBTMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ASLTMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_PUMP_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SAWNOFF_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BULLPUP_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ASLTSHTGN_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SNIPERRFL_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_HVYSNIPER_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_GRNLAUNCH_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_RPG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MINIGUNS_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SMKGRENADE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_STKYBMB_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MOLOTOV_ENEMY_KILLS"), 600, 0);
		}
		break;
	case 7:
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_TOTAL_PLAYING_TIME"), 792000000, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_TOTAL_PLAYING_TIME"), 792000000, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_TOTAL_PLAYING_TIME"), 792000000, true);
		break;
	}
}
void  menu_home_misc_stats_unlocks__display(std::string caption) {

	// Menu Labels
	const int LINE_COUNT = 8;
	menuList menu_home_misc_stats_unlocks[LINE_COUNT] = {
		/* 0 */{ "100% Skills" },
		/* 1 */{ "All Clothes	" },
		/* 2 */{ "All LSC Unlocks" },
		/* 3 */{ "All Tattoos" },
		/* 4 */{ "All S/F/A" },
		/* 5 */{ "All Heist Cars" },
		/* 6 */{ "All Weapon Skins" },
		/* 7 */{ "Playtime Edits" }
	};

	menuList *current_menu = menu_home_misc_stats_unlocks;
	int *current_line = &active_home_misc_stats_unlocks;

	// Menu Setup and Navigation
	int navigationResult;
	DWORD waitTime = 150;
	while (true) {
		// draw menu and navigation path
		menu_list_draw(current_menu, LINE_COUNT, caption, *current_line, &waitTime);
		navigationResult = menu_list_navigate(&waitTime, current_line, LINE_COUNT);

		if (navigationResult == -1)
			break;
		else if (navigationResult == 1) {
			menu_home_misc_stats_unlocks__action(current_line);
		}
	}
}


int active_home_misc_cheats_players = 0;
void  menu_home_misc_cheats_players__process(std::string caption) {

	int LINE_COUNT = 32;

	// Functional setup
	std::vector <char*> playerList;
	playerList.reserve(LINE_COUNT);

	// Update player's name
	for (int i = 0; i < LINE_COUNT; i++) {
		playerList.push_back(PLAYER::GET_PLAYER_NAME(i));
	}

	Ped playerPed;

	// Menu Setup and Navigation
	int navigationResult;
	DWORD waitTime = 150;
	int startIndex = 0;
	int endIndex = 14;

	while (true) {
		// draw menu and navigation path
		menu_list_draw(playerList, caption, active_home_misc_cheats_players, &startIndex, &endIndex, &waitTime, 3.0f);
		navigationResult = menu_list_navigate(&waitTime, &active_home_misc_cheats_players, LINE_COUNT);

		if (navigationResult == -1)
			break;
		else if (navigationResult == 1) {
			playerPed = PLAYER::GET_PLAYER_PED(active_home_misc_cheats_players);
			set_status_text("pedID: " + std::to_string(playerPed));
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(playerPed, FALSE);
			UI::SET_NEW_WAYPOINT(coords.x, coords.y);
		}
	}
}

int active_home_misc_cheats = 0;
void  menu_home_misc_cheats__action(menuList menu_lines[], int *ptr_active_line){

	int active_line = *ptr_active_line;

	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	switch (active_line) {
	case 0:
		if (bPlayerExists) {
			Vector3 entityPos = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
			Hash prop_bag = GAMEPLAY::GET_HASH_KEY("prop_money_bag_01");
			STREAMING::REQUEST_MODEL(prop_bag); //Request the shitty Model so that 40k spawns are possible

			while (!STREAMING::HAS_MODEL_LOADED(prop_bag))
				if (loading_message_show()) break;
			loading_message_clear();

			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_MONEY_CASE"),
				entityPos.x, entityPos.y, entityPos.z + 1, 0, 40000, prop_bag, 0, 1);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(prop_bag);
		}
		break;
	case 1:
		menu_home_misc_cheats_players__process("Player list");
		break;
	case 2:
		if (ENTITY::IS_ENTITY_ATTACHED_TO_ANY_OBJECT(PLAYER::PLAYER_PED_ID()))
			ENTITY::DETACH_ENTITY(PLAYER::PLAYER_PED_ID(), 1, 1);
		break;
	}
}
void  menu_home_misc_cheats__display(std::string caption)
{
	// Menu Labels
	const int LINE_COUNT = 3;
	menuList menu_home_misc_cheats[LINE_COUNT] = {
		/* 0 */{ "Spawn 40k" },
		/* 1 */{ "Get player list" },
		/* 2 */{ "Detach object" }
	};

	menuList *current_menu = menu_home_misc_cheats;
	int *current_line = &active_home_misc_cheats;

	// Menu Setup and Navigation
	int navigationResult;
	DWORD waitTime = 150;
	while (true) {
		// draw menu and navigation path
		menu_list_draw(current_menu, LINE_COUNT, caption, *current_line, &waitTime);
		navigationResult = menu_list_navigate(&waitTime, current_line, LINE_COUNT);

		if (navigationResult == -1)
			break;
		else if (navigationResult == 1) {
			menu_home_misc_cheats__action(current_menu, current_line);
		}
	}
}

int active_home_misc_stats_level = 0;
void  menu_home_misc_stats_level__action(int *ptr_active_line) {

	int active_line = *ptr_active_line;

	// common variables
	Ped playerGroup = PED::GET_PED_GROUP_INDEX(PLAYER::PLAYER_PED_ID());
	int rpPoints;

	switch (active_line) {
	case 0:		rpPoints = 448800;		break;
	case 1:		rpPoints = 1584350;		break;
	case 2:		rpPoints = 3075600;		break;
	case 3:		rpPoints = 4691850;		break;
	case 4:		rpPoints = 6433100;		break;
	case 5:		rpPoints = 47488300;	break;
	}
	if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()))	{
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), rpPoints, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_XP_FM"), rpPoints, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_XP_FM"), rpPoints, true);
		display_message_caption("Rank is set");
	}
}
void  menu_home_misc_stats_level__display(std::string caption) {

	// Menu Labels
	const int LINE_COUNT = 6;
	menuList menu_home_misc_stats_level[LINE_COUNT] = {
		/* 0 */{ "Level 50" },
		/* 1 */{ "Level 100" },
		/* 2 */{ "Level 150" },
		/* 3 */{ "Level 200" },
		/* 4 */{ "Level 250" },
		/* 5 */{ "Level 1000" }
	};

	menuList *current_menu = menu_home_misc_stats_level;
	int *current_line = &active_home_misc_stats_level;

	// Menu Setup and Navigation
	int navigationResult;
	DWORD waitTime = 150;
	while (true) {
		// draw menu and navigation path
		menu_list_draw(current_menu, LINE_COUNT, caption, *current_line, &waitTime);
		navigationResult = menu_list_navigate(&waitTime, current_line, LINE_COUNT);

		if (navigationResult == -1)
			break;
		else if (navigationResult == 1) {
			menu_home_misc_stats_level__action(current_line);
		}
	}
}

int active_home_misc_stats = 0;
void  menu_home_misc_stats__action(int *ptr_active_line){

	int active_line = *ptr_active_line;

	switch (active_line) {
	case 0:
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("BADSPORT_NUMDAYS_1ST_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("BADSPORT_NUMDAYS_2ND_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("BADSPORT_NUMDAYS_3RD_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("BADSPORT_NUMDAYS_4TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("BADSPORT_NUMDAYS_5TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("BADSPORT_NUMDAYS_6TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("BADSPORT_NUMDAYS_7TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("BADSPORT_NUMDAYS_8TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("BADSPORT_NUMDAYS_9TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("BADSPORT_NUMDAYS_10TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BADSPORT_NUMDAYS_1ST_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BADSPORT_NUMDAYS_2ND_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BADSPORT_NUMDAYS_3RD_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BADSPORT_NUMDAYS_4TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BADSPORT_NUMDAYS_5TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BADSPORT_NUMDAYS_6TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BADSPORT_NUMDAYS_7TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BADSPORT_NUMDAYS_8TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BADSPORT_NUMDAYS_9TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BADSPORT_NUMDAYS_10TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_BADSPORT_NUMDAYS_1ST_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_BADSPORT_NUMDAYS_2ND_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_BADSPORT_NUMDAYS_3RD_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_BADSPORT_NUMDAYS_4TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_BADSPORT_NUMDAYS_5TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_BADSPORT_NUMDAYS_6TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_BADSPORT_NUMDAYS_7TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_BADSPORT_NUMDAYS_8TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_BADSPORT_NUMDAYS_9TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_BADSPORT_NUMDAYS_10TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_BADSPORT_NUMDAYS_1ST_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_BADSPORT_NUMDAYS_2ND_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_BADSPORT_NUMDAYS_3RD_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_BADSPORT_NUMDAYS_4TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_BADSPORT_NUMDAYS_5TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_BADSPORT_NUMDAYS_6TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_BADSPORT_NUMDAYS_7TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_BADSPORT_NUMDAYS_8TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_BADSPORT_NUMDAYS_9TH_OFFENCE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_BADSPORT_NUMDAYS_10TH_OFFENCE"), 0, true);
		STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY("BADSPORT_RESET_MINUTES"), 1.0, true);
		STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY("MP0_BADSPORT_RESET_MINUTES"), 1.0, true);
		STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY("MP1_BADSPORT_RESET_MINUTES"), 1.0, true);
		STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY("MP2_BADSPORT_RESET_MINUTES"), 1.0, true);
		STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_OVERALL_BADSPORT"), 0, true);
		STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_CHAR_IS_BADSPORT"), false, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_BECAME_BADSPORT_NUM"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BAD_SPORT_BITSET"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHEAT_BITSET"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_REPORT_STRENGTH"), 32, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_COMMEND_STRENGTH"), 100, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_FRIENDLY"), 100, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_HELPFUL"), 100, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_GRIEFING"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_OFFENSIVE_LANGUAGE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_OFFENSIVE_UGC"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_VC_HATE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_GAME_EXPLOITS"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_ISPUNISHED"), 0, true);
		STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_OVERALL_BADSPORT"), 0, true);
		STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_CHAR_IS_BADSPORT"), false, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_BECAME_BADSPORT_NUM"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_BAD_SPORT_BITSET"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHEAT_BITSET"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_REPORT_STRENGTH"), 32, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_COMMEND_STRENGTH"), 100, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_FRIENDLY"), 100, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_HELPFUL"), 100, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_GRIEFING"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_OFFENSIVE_LANGUAGE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_OFFENSIVE_UGC"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_VC_HATE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_GAME_EXPLOITS"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_ISPUNISHED"), 0, true);
		STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_OVERALL_BADSPORT"), 0, true);
		STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_CHAR_IS_BADSPORT"), false, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_BECAME_BADSPORT_NUM"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_BAD_SPORT_BITSET"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHEAT_BITSET"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_REPORT_STRENGTH"), 32, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_COMMEND_STRENGTH"), 100, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_FRIENDLY"), 100, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_HELPFUL"), 100, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_GRIEFING"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_OFFENSIVE_LANGUAGE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_OFFENSIVE_UGC"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_VC_HATE"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_GAME_EXPLOITS"), 0, true);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_ISPUNISHED"), 0, true);
		break;
	case 1:
		menu_home_misc_stats_unlocks__display("Unlocks");
		break;
	case 2:
		menu_home_misc_stats_level__display("Rank");
		break;
	}
}
void  menu_home_misc_stats__display(std::string caption) {

	// Menu Labels
	const int LINE_COUNT = 3;
	menuList menu_home_misc_stats[LINE_COUNT] = {
		/* 0 */{ "Clean online report" },
		/* 1 */{ "Unlocks options" },
		/* 2 */{ "Rank options" },
	};

	menuList *current_menu = menu_home_misc_stats;
	int *current_line = &active_home_misc_stats;

	// Menu Setup and Navigation
	int navigationResult;
	DWORD waitTime = 150;
	while (true) {
		// draw menu and navigation path
		menu_list_draw(current_menu, LINE_COUNT, caption, *current_line, &waitTime);
		navigationResult = menu_list_navigate(&waitTime, current_line, LINE_COUNT);

		if (navigationResult == -1)
			break;
		else if (navigationResult == 1) {
			menu_home_misc_stats__action(current_line);
		}
	}
}

int active_home_misc = 0;
void  menu_home_misc__action(menuList_boolean menu_lines[], int *ptr_active_line){

	int active_line = *ptr_active_line;

	switch (active_line)
	{
	case 0:
		featureMiscMobileRadio = !featureMiscMobileRadio;
		AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(featureMiscMobileRadio);
		break;
	case 1:
		if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()) &&
			(PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0) ||
			featureMiscMobileRadio))
			AUDIO::SKIP_RADIO_FORWARD();
		break;
	case 2:
		menu_home_misc_stats__display("Stats Edit");
		break;
	case 3:
		menu_home_misc_cheats__display("Cheats");
	case 4:
		menu_home_misc_debug__display("Debug Options");
		break;
	case 5:
		menu_home_misc_credits__display("Kinky Version 2.1 e-0.1");
		break;
	}
}
void  menu_home_misc__display(std::string caption)
{
	// Menu Labels
	const int LINE_COUNT = 6;
	menuList_boolean menu_home_misc[LINE_COUNT] = {
		/* 0 */{ "Mobile Radio", &featureMiscMobileRadio, NULL },
		/* 1 */{ "Next Radio Track", NULL, NULL },
		/* 2 */{ "Stats Edit", NULL, NULL },
		/* 3 */{ "Cheats", NULL, NULL },
		/* 4 */{ "Debug", NULL, NULL },
		/* 5 */{ "Credits", NULL, NULL }
	};

	menuList_boolean *current_menu = menu_home_misc;
	int *current_line = &active_home_misc;

	// Menu Setup and Navigation
	int navigationResult;
	DWORD waitTime = 150;
	while (true) {
		// draw menu and navigation path
		menu_list_draw(current_menu, LINE_COUNT, caption, *current_line, &waitTime);
		navigationResult = menu_list_navigate(&waitTime, current_line, LINE_COUNT);

		if (navigationResult == -1)
			break;
		else if (navigationResult == 1) {
			menu_home_misc__action(current_menu, current_line);
		}
	}
}

int active_home_weather = 0;
void  menu_home_weather__action(menuList_boolean menu_lines[], int *ptr_active_line){

	int active_line = *ptr_active_line;

	switch (active_line) {
		// wind
		case 0:
			featureWeatherWind = !featureWeatherWind;
			if (featureWeatherWind) {
				GAMEPLAY::SET_WIND(1.0);
				GAMEPLAY::SET_WIND_SPEED(11.99f);
				GAMEPLAY::SET_WIND_DIRECTION(ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
			}
			else {
				GAMEPLAY::SET_WIND(0.0);
				GAMEPLAY::SET_WIND_SPEED(0.0);
			}
			break;
		
			// set weather
		default:
			GAMEPLAY::SET_OVERRIDE_WEATHER((char *)menu_lines[active_line].text);
			//GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST((char *)menu_lines[active_line].text);
			//GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
			set_status_text(menu_lines[active_line].text);
	}
}
void  menu_home_weather__display(std::string caption) {
	// Menu Labels
	const int LINE_COUNT = 15;
	menuList_boolean menu_home_weather[LINE_COUNT] = {
		{ "Wind", &featureWeatherWind, NULL },
		{ "ExtraSunny", NULL, NULL },
		{ "Clear", NULL, NULL },
		{ "Clouds", NULL, NULL },
		{ "Smog", NULL, NULL },
		{ "Foggy", NULL, NULL },
		{ "Overcast", NULL, NULL },
		{ "Rain", NULL, NULL },
		{ "Thunder", NULL, NULL },
		{ "Clearing", NULL, NULL },
		{ "Neutral", NULL, NULL },
		{ "Snow", NULL, NULL },
		{ "Blizzard", NULL, NULL },
		{ "SNOWLIGHT", NULL, NULL },
		{ "XMAS", NULL, NULL }
	};

	menuList_boolean *current_menu = menu_home_weather;
	int *current_line = &active_home_weather;

	// Menu Setup and Navigation
	int navigationResult;
	DWORD waitTime = 150;
	while (true) {
		// draw menu and navigation path
		menu_list_draw(current_menu, LINE_COUNT, caption, *current_line, &waitTime);
		navigationResult = menu_list_navigate(&waitTime, current_line, LINE_COUNT);

		if (navigationResult == -1)
			break;
		else if (navigationResult == 1) {
			menu_home_weather__action(current_menu, current_line);
		}
	}
}

int active_home_time = 0;
void  menu_home_time__action(menuList_boolean menu_lines[], int *ptr_active_line){

	int active_line = *ptr_active_line;

	switch (active_line) {
		// hour forward/backward
	case 0:
	case 1:
	{
		int h = TIME::GET_CLOCK_HOURS();
		if (active_line == 0) h = (h == 23) ? 0 : h + 1; else h = (h == 0) ? 23 : h - 1;
		int m = TIME::GET_CLOCK_MINUTES();
		TIME::SET_CLOCK_TIME(h, m, 0);
		char text[32];
		sprintf_s(text, "time %d:%d", h, m);
		display_message_notify(text);
	}
	break;
	// switchable features
	default:
		if (menu_lines[active_line].pState)
			*menu_lines[active_line].pState = !(*menu_lines[active_line].pState);
		if (menu_lines[active_line].pUpdated)
			*menu_lines[active_line].pUpdated = true;
	}
}
void  menu_home_time__display(std::string caption)
{
	// Menu Labels
	const int LINE_COUNT = 4;
	menuList_boolean menu_home_time[LINE_COUNT] = {
		{ "Hour Forward", NULL, NULL },
		{ "Hour Backward", NULL, NULL },
		{ "Freeze Time", &featureTimePaused, &featureTimePausedUpdated },
		{ "Sync With System", &featureTimeSynced, NULL }
	};

	menuList_boolean *current_menu = menu_home_time;
	int *current_line = &active_home_time;

	// Menu Setup and Navigation
	int navigationResult;
	DWORD waitTime = 150;
	while (true) {
		// draw menu and navigation path
		menu_list_draw(current_menu, LINE_COUNT, caption, *current_line, &waitTime);
		navigationResult = menu_list_navigate(&waitTime, current_line, LINE_COUNT);

		if (navigationResult == -1)
			break;
		else if (navigationResult == 1) {
			menu_home_time__action(current_menu, current_line);
		}
	}
}

int active_home_vehicle_carspawnLine = 1;
int active_home_vehicle_carspawnTab = 1;
void  menu_home_vehicle_carspawn__process() {
	
	// 2D Vector menu
	int *current_line = &active_home_vehicle_carspawnLine;
	int *current_tab = &active_home_vehicle_carspawnTab;
	int navigationResult;

	// Menu Setup and Navigation
	DWORD waitTime = 150;
	int startIndex = 1;
	int endIndex = 15;
	
	// draw menu and navigation path
	while (true) {
		navigationResult = menu_line_process_reflow(vehicleModels, current_line, current_tab, &startIndex, &endIndex, &waitTime, true, 3.0);
		if (navigationResult == 1)
			spawn_vehicle(vehicleModels[*current_tab - 1][*current_line]);
		else if (navigationResult == -1)
			break;
	}
}

int active_home_vehicle = 0;
void menu_home_vehicle__action(menuList_boolean menu_lines[], int *ptr_active_line) {

	int active_line = *ptr_active_line;

	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	switch (active_line) {
		case 0: //Car Spawner
			menu_home_vehicle_carspawn__process();
			break;

		case 1: //Fix
			if (bPlayerExists) {
				if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
					VEHICLE::SET_VEHICLE_FIXED(PED::GET_VEHICLE_PED_IS_USING(playerPed));
				else
					display_message_caption("Player isn't in a vehicle");
			}
			break;

		case 2: //Flip
			if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(PED::GET_VEHICLE_PED_IS_USING(playerPed));
			}
			break;
		case 3: //Invincible
			menu_list_feature_toggle(menu_lines, active_line);
			break;

		case 4: //All Mods
			if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 120, 120);
				VEHICLE::TOGGLE_VEHICLE_MOD(veh, 18, 1);
				VEHICLE::TOGGLE_VEHICLE_MOD(veh, 22, 1);
				VEHICLE::SET_VEHICLE_MOD(veh, 16, 5, 0);
				VEHICLE::SET_VEHICLE_MOD(veh, 12, 2, 0);
				VEHICLE::SET_VEHICLE_MOD(veh, 11, 3, 0);
				VEHICLE::SET_VEHICLE_MOD(veh, 14, 14, 0);
				VEHICLE::SET_VEHICLE_MOD(veh, 15, 3, 0);
				VEHICLE::SET_VEHICLE_MOD(veh, 13, 2, 0);
				VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, 6);
				VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 5);
				VEHICLE::SET_VEHICLE_MOD(veh, 23, 19, 1);
				VEHICLE::SET_VEHICLE_MOD(veh, 0, 1, 0);
				VEHICLE::SET_VEHICLE_MOD(veh, 1, 1, 0);
				VEHICLE::SET_VEHICLE_MOD(veh, 2, 1, 0);
				VEHICLE::SET_VEHICLE_MOD(veh, 3, 1, 0);
				VEHICLE::SET_VEHICLE_MOD(veh, 4, 1, 0);
				VEHICLE::SET_VEHICLE_MOD(veh, 5, 1, 0);
				VEHICLE::SET_VEHICLE_MOD(veh, 6, 1, 0);
				VEHICLE::SET_VEHICLE_MOD(veh, 7, 1, 0);
				VEHICLE::SET_VEHICLE_MOD(veh, 8, 1, 0);
				VEHICLE::SET_VEHICLE_MOD(veh, 9, 1, 0);
				VEHICLE::SET_VEHICLE_MOD(veh, 10, 1, 0);
			}
			break;

		case 5: //Custom License Plate
			if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
				const int sizeOfPlate = 9;
				char plateText[sizeOfPlate];
				strcpy(plateText, get_user_input("FMMC_KEY_TIP12N", "630JK723", sizeOfPlate));

				if (strcmp(plateText, "")) { // String is not empty
					if (strlen(plateText) < 2) {
						set_status_text("Plate text should have at least 2 characters");
					}
					else {
						Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, plateText);
					}
				}
			}
			break;

		case 6: //Paint Random
			if (bPlayerExists) {
				if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
					Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, rand() % 255, rand() % 255, rand() % 255);
					if (VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(veh))
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, rand() % 255, rand() % 255, rand() % 255);
				}
				else {
					display_message_caption("Player isn't in a vehicle");
				}
			}
			break;

		// switchable features
		default:
			menu_list_feature_toggle(menu_lines, active_line);
	}
}
void menu_home_vehicle__display(std::string caption) {
	// Menu Labels
	const int LINE_COUNT = 13;
	menuList_boolean menu_home_vehicle[LINE_COUNT] = {
		/*  0 */ { "Car Spawner", NULL, NULL },
		/*  1 */ { "Fix", NULL, NULL },
		/*  2 */ { "Flip", NULL, NULL },
		/*  3 */ { "Invincible", &featureVehInvincible, &featureVehInvincibleUpdated },
		/*  4 */ { "All Mods", NULL, NULL },
		/*  5 */ { "Custom License Plate", NULL, NULL },
		/*  6 */ { "Paint Random", NULL, NULL },
		/*  7 */ { "Rainbow Car", &featureVehRainbow, NULL },
		/*  8 */ { "Speed boost", &featureVehSpeedBoost, NULL },
		/*  9 */ { "Sticky Cars", &featureVehStickyCar, NULL },
		/* 10 */ { "Slidey Cars", &featureVehSlide, NULL },
		/* 11 */ { "Vehicle Rockets", &featureWeaponVehRockets, NULL },
		/* 12 */ { "Wrap To Spawned Car", &featureVehWrapInSpawned, NULL }
	};

	menuList_boolean *current_menu = menu_home_vehicle;
	int *current_line = &active_home_vehicle;

	// Menu Setup and Navigation
	int navigationResult;
	DWORD waitTime = 150;
	while (true) {
		// draw menu and navigation path
		menu_list_draw(current_menu, LINE_COUNT, caption, *current_line, &waitTime);
		navigationResult = menu_list_navigate(&waitTime, current_line, LINE_COUNT);

		if (navigationResult == -1)
			break;
		else if (navigationResult == 1) {
			menu_home_vehicle__action(current_menu, current_line);
		}
	}
}

int active_home_weapon = 0;
void  menu_home_weapon__action(menuList_boolean menu_lines[], int *ptr_active_line) {

	int active_line = *ptr_active_line;

	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	switch (active_line) {
		case 0:
			give_weaponsSets_to_ped(playerPed, weaponOnlineNames);
			give_weaponsSets_to_ped(playerPed, weaponRestrictedNames);
			display_message_caption("Added all weapons");
			break;

		case 1:
			give_weaponsSets_to_ped(playerPed, weaponOnlineNames);
			display_message_caption("Added online weapons");
			break;

		case 2:
			give_weaponsSets_to_ped(playerPed, weaponRestrictedNames);
			display_message_caption("Added restricted weapons");;
			break;

		case 3:
			WEAPON::REMOVE_ALL_PED_WEAPONS(playerPed, 1);
			display_message_caption("Removed all weapons");
			break;

		// switchable features
		default:
			menu_list_feature_toggle(menu_lines, active_line);
	}
}
void  menu_home_weapon__display(std::string caption, DWORD waitTime = 150) {
	// Menu Labels
	const int LINE_COUNT = 9;
	menuList_boolean menu_home_weapon[LINE_COUNT] = {
		/*  0 */{ "All Weapons", NULL, NULL },
		/*  1 */{ "Weapons (Online)", NULL, NULL },
		/*  2 */{ "Weapons (Restricted)", NULL, NULL },
		/*  3 */{ "Remove All Weapons", NULL, NULL },
		/*  4 */{ "Infinite Ammo", &featureWeaponNoReload, NULL },
		/*  5 */{ "Fire Ammo", &featureWeaponFireAmmo, NULL },
		/*  6 */{ "Explosive Ammo", &featureWeaponExplosiveAmmo, NULL },
		/*  7 */{ "Explosive Melee", &featureWeaponExplosiveMelee, NULL },
		/*  8 */{ "One Hit Kill", &featureWeaponOneHit, NULL }
	};

	menuList_boolean *current_menu = menu_home_weapon;
	int *current_line = &active_home_weapon;

	// Menu Setup and Navigation
	int navigationResult;
	while (true) {
		// draw menu and navigation path
		menu_list_draw(current_menu, LINE_COUNT, caption, *current_line, &waitTime);
		navigationResult = menu_list_navigate(&waitTime, current_line, LINE_COUNT);

		if (navigationResult == -1)
			break;
		else if (navigationResult == 1) {
			menu_home_weapon__action(current_menu, current_line);
		}
	}
}

BOOL is_ipls_loaded(int index) {
	return STREAMING::IS_IPL_ACTIVE(ipl_database[index][0]);
}

void stream_ipls(int index) {
	int vectorSizeEnable = (int) ipl_database[index].size();
	int vectorSizeRestore = (int)ipl_database[index+1].size();
	for (int i = 0; i < vectorSizeEnable; i++) {
		STREAMING::REQUEST_IPL(ipl_database[index][i]);
	}
	for (int i = 0; i < vectorSizeRestore; i++) {
		STREAMING::REMOVE_IPL(ipl_database[index+1][i]);
	}
}
void restore_ipls(int index) {
	int vectorSizeEnable = (int)ipl_database[index].size();
	int vectorSizeRestore = (int)ipl_database[index + 1].size();
	for (int i = 0; i < vectorSizeEnable; i++) {
		STREAMING::REMOVE_IPL(ipl_database[index][i]);
	}
	for (int i = 0; i < vectorSizeRestore; i++) {
		STREAMING::REQUEST_IPL(ipl_database[index + 1][i]);
	}
}
void remove_ipls() {
	int vectorSize = (int)ipl_database.size();
	for (int i = 0; i < vectorSize; i+= 2) {
		output_writeToLog("remove_ipls: starting at index" + to_string(i) + "/" + to_string(vectorSize - 1));
		restore_ipls(i);
	}
}

void teleport_with_menu(int *ptr_active_tab, int *ptr_active_line) {

	int active_line = *ptr_active_line;
	int active_tab = *ptr_active_tab;

	// common variables
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vector3 coords;
	bool success = false;

	// get entity to teleport
	Entity entity = playerPed;
	if (PED::IS_PED_IN_ANY_VEHICLE(entity, 0))
		entity = PED::GET_VEHICLE_PED_IS_USING(entity);

	// Teleport to marker
	if (active_line == 1) {
		bool blipFound = false;

		// search for marker blip
		int blipIterator = UI::_GET_BLIP_INFO_ID_ITERATOR();
		for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator)) {
			if (UI::GET_BLIP_INFO_ID_TYPE(i) == 4) {
				coords = UI::GET_BLIP_INFO_ID_COORD(i);
				blipFound = true;
				break;
			}
		}
		if (blipFound) {
			// load needed map region and check height levels for ground existence
			bool groundFound = false;
			float startCheck, endCheck, intervalCheck;
			int bInvert;

			if (coords.y > 4000)	startCheck = 800.0f;
			if (coords.y > 1000)	startCheck = 500.0f;
			else					startCheck = 400.0f;

			endCheck = -30.0f;
			intervalCheck = -50.0f;
			bInvert = 1;

			for (float groundCheck = startCheck; groundCheck * bInvert > endCheck * bInvert; groundCheck += intervalCheck) {
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(entity, coords.x, coords.y, groundCheck, 0, 0, 1);
				WAIT(20);
				if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheck, &coords.z)) {
					groundFound = true;
					break;
				}
			}

			if (ENTITY::IS_ENTITY_IN_WATER(playerPed)) {
				// check water level and spawn to surface
				if (WATER::GET_WATER_HEIGHT(coords.x, coords.y, coords.z, &coords.z)) { // Get surface coord
					groundFound = true;
				}
			}
			
			// if ground not found
			if (!groundFound) // let game decide where to respawn.
				coords.z = -1000.0f;

			coords.z += 0.5f;
			success = true;
		}
		else {
			display_message_caption("Map marker isn't set");
		}

	}
	else if (active_line == 2) { // move forward
		teleportEntity(entity);
		return;
	}
	else { // predefined coords
		if (active_tab == 4) { // IPL Loader
			if (active_line == 3) { // remove all ipl
				remove_ipls();
				return;
			}
			if (!is_ipls_loaded((active_line - 4) * 2)) {
				stream_ipls((active_line - 4) * 2);
				display_message_notify("IPL loaded. Press again to teleport");
				return;
			}
		}

		coords.x = teleportLocations[active_tab][active_line].x;
		coords.y = teleportLocations[active_tab][active_line].y;
		coords.z = teleportLocations[active_tab][active_line].z;

		success = true;
	}

	// set player pos
	if (success) {
		teleportEntity(entity, coords);

	}
}

int active_home_teleportLine = 1;
int active_home_teleportTab = 0;
void  menu_home_teleport__process() {

	// 2D Vector menu
	int *current_line = &active_home_teleportLine;
	int *current_tab = &active_home_teleportTab;
	int navigationResult;

	// Menu Setup and Navigation
	DWORD waitTime = 150;
	int startIndex = 1;
	int endIndex = 15;

	// draw menu and navigation path
	while (true) {
		navigationResult = menu_line_process_reflow(teleportLocations, current_line, current_tab, &startIndex, &endIndex, &waitTime, false, 3.0);
		if (navigationResult == 1) {
			teleport_with_menu(current_tab, current_line);
		}
		else if (navigationResult == -1)
			break;
	}
}

int active_home_player_animation_poses = 0;
void menu_home_player_animation_poses__action(int *ptr_active_line) {

	int active_line = *ptr_active_line;

	switch (active_line) {
	case 0:	Animation_Stop(); break;
	case 1: Animation_Start("mini@strip_club@backroom@", "stripper_b_backroom_idle_b"); break;
	case 2: 
		switch (rand() % 3) {
			case 0:	Animation_Start("amb@world_human_muscle_flex@arms_at_side@idle_a", "idle_a"); break;
			case 1:	Animation_Start("amb@world_human_muscle_flex@arms_at_side@idle_a", "idle_b"); break;
			case 2:	Animation_Start("amb@world_human_muscle_flex@arms_at_side@idle_a", "idle_c"); break;
		} break;
	case 3: 
		switch (rand() % 3) {
			case 0:	Animation_Start("amb@world_human_muscle_flex@arms_at_front@idle_a", "idle_a"); break;
			case 1:	Animation_Start("amb@world_human_muscle_flex@arms_at_front@idle_a", "idle_b"); break;
			case 2:	Animation_Start("amb@world_human_muscle_flex@arms_at_front@idle_a", "idle_c"); break;
		} break;
	case 4: Animation_Start("switch@trevor@mocks_lapdance", "001443_01_trvs_28_idle_stripper"); break;
	case 5: Animation_Start("switch@trevor@mocks_lapdance", "001443_01_trvs_28_idle_trv"); break;
	case 6: Animation_Start("switch@trevor@mocks_lapdance", "001443_01_trvs_28_exit_trv"); break;
	}
}
void menu_home_player_animation_poses__display(std::string caption) {

	// Menu Labels
	std::vector <std::string> menu_home_player_animation_poses = {
		// 0
		{ "Stop" },
		// 1 2 3
		{ "Strip Club Changing Room" }, { "Flex muscle (side)" }, { "Flex muscle (front)" },
		// 4 5 6
		{ "Trevor mock" }, { "Trevor mock" }, { "Trevor mock" }
	};

	std::vector <std::string> *current_menu = &menu_home_player_animation_poses;
	int *current_line = &active_home_player_animation_poses;

	// Menu Setup and Navigation
	int navigationResult;
	DWORD waitTime = 150;
	int startIndex = 0;
	int endIndex = 15;


	while (true) {
		// draw menu and navigation path
		menu_list_draw(*current_menu, caption, *current_line, &startIndex, &endIndex, &waitTime);
		navigationResult = menu_list_navigate(&waitTime, current_line, (int)(*current_menu).size());

		if (navigationResult == -1)
			break;
		else if (navigationResult == 1) {
			menu_home_player_animation_poses__action(current_line);
		}
	}
}

int active_home_player_animation_mimes = 0;
void menu_home_player_animation_mimes__action(int *ptr_active_line) {

	int active_line = *ptr_active_line;

	switch (active_line) {
	case 0:	Animation_Stop(); break;
	case 1: Animation_Start("special_ped@mime@monologue_1@monologue_1a", "02_ig_1_r_0"); break;
	case 2: Animation_Start("special_ped@mime@monologue_2@monologue_2a", "02_ig_1_cli_0"); break;
	case 3: Animation_Start("special_ped@mime@monologue_3@monologue_3a", "03_ig_1_open_wind_0"); break;
	case 4: Animation_Start("special_ped@mime@monologue_4@monologue_4a", "09_ig_1_balo_0"); break;
	case 5: Animation_Start("special_ped@mime@monologue_5@monologue_5a", "10_ig_1_wa_0"); break;
	case 6: Animation_Start("special_ped@mime@monologue_6@monologue_6a", "12_ig_1_beaten__0"); break;
	case 7: Animation_Start("special_ped@mime@monologue_7@monologue_7a", "11_ig_1_run_aw_0"); break;
	case 8: Animation_Start("special_ped@mime@monologue_8@monologue_8a", "08_ig_1_wall_ba_0"); break;
	case 9: Animation_Start("timetable@mime@ig_1", "cowboy_riding_horse"); break;
	}
}
void menu_home_player_animation_mimes__display(std::string caption) {

	// Menu Labels
	std::vector <std::string> menu_home_player_animation_mimes = {
		/* 0 */{ "Stop" },
		/* 1 */{ "Running" },
		/* 2 */{ "Climbing ladders" },
		/* 3 */{ "Open Window" },
		/* 4 */{ "Air Balloon" },
		/* 5 */{ "Waves" },
		/* 6 */{ "Get Beaten Up" },
		/* 7 */{ "Flee Away" },
		/* 8 */{ "Wall Back" },
		/* 9 */{ "Cowboy riding horse" }
	};

	std::vector <std::string> *current_menu = &menu_home_player_animation_mimes;
	int *current_line = &active_home_player_animation_mimes;

	// Menu Setup and Navigation
	int navigationResult;
	DWORD waitTime = 150;
	int startIndex = 0;
	int endIndex = 15;


	while (true) {
		// draw menu and navigation path
		menu_list_draw(*current_menu, caption, *current_line, &startIndex, &endIndex, &waitTime);
		navigationResult = menu_list_navigate(&waitTime, current_line, (int)(*current_menu).size());

		if (navigationResult == -1)
			break;
		else if (navigationResult == 1) {
			menu_home_player_animation_mimes__action(current_line);
		}
	}
}

int active_home_player_animation_exercises = 0;
void menu_home_player_animation_exercises__action(int *ptr_active_line) {

	int active_line = *ptr_active_line;

	switch (active_line) {
	case 0:
		Animation_Stop();
		break;
	case 1:
		Animation_Start("amb@world_human_push_ups@male@enter", "enter", true );
		Animation_Start("amb@world_human_push_ups@male@base","base");
		break;
	case 2:
		Animation_Start("amb@world_human_sit_ups@male@enter","enter",true);
		Animation_Start("amb@world_human_sit_ups@male@base","base");
		break;
	case 3:
		while (true) {
			if (Animation_Start("timetable@denice@ig_1", "base", true)) break;
			if (Animation_Start("timetable@denice@ig_1", "idle_a", true)) break;
			if (Animation_Start("timetable@denice@ig_1", "idle_b", true)) break;
			if (Animation_Start("timetable@denice@ig_1", "idle_c", true)) break;
		} break;

	case 4:
		Animation_Start("amb@world_human_jog_standing@" + gender + "@base","base");
		break;
	case 5:
		Animation_Start("amb@world_human_jog@" + gender + "@base","base",false, 2); 
		break;
	case 6:
		Animation_Start("amb@world_human_power_walker@female@base","base", false, 2);
		break;
	case 7:
		Animation_Start("amb@world_human_yoga@" + gender + "@base", "base_a");
		break;
	case 8:
		Animation_Start("amb@world_human_yoga@" + gender + "@base","base_b");
		break;
	case 9:
		Animation_Start("amb@world_human_yoga@female@base","base_c");
		break;
	case 10:
		Animation_Start("amb@prop_human_muscle_chin_ups@male@enter","enter",true);
		Animation_Start("amb@prop_human_muscle_chin_ups@male@base","base");
		break;
	}
}
void menu_home_player_animation_exercises__display(std::string caption) {

	// Menu Labels
	std::vector <std::string> menu_home_player_animation_exercises = {
		// 0
		{ "Stop" }, 
		// 1 2 3 4 5
		{ "Push up" }, { "Sit up" }, { "Workout" }, { "Jog (Warming)" }, { "Jog" }, { "Power Walk" },
		// 6 7 8 9
		{ "Yoga 1" }, { "Yoga 2" }, { "Yoga 3" }, { "Chin up (Prop)" }
	};

	std::vector <std::string> *current_menu = &menu_home_player_animation_exercises;
	int *current_line = &active_home_player_animation_exercises;

	// Menu Setup and Navigation
	int navigationResult;
	DWORD waitTime = 150;
	int startIndex = 0;
	int endIndex = 15;

	while (true) {
		// draw menu and navigation path
		menu_list_draw(*current_menu, caption, *current_line, &startIndex, &endIndex, &waitTime);
		navigationResult = menu_list_navigate(&waitTime, current_line, (int)(*current_menu).size());

		if (navigationResult == -1)
			break;
		else if (navigationResult == 1) {
			menu_home_player_animation_exercises__action(current_line);
		}
	}
}

int active_home_player_animation_dances = 0;
void  menu_home_player_animation_dances__action(int *ptr_active_line) {

	int active_line = *ptr_active_line;
	
	switch (active_line) {
	case 0:
		Animation_Stop();
		break;
	case 1:
		Animation_Start(
			"mini@strip_club@private_dance@part1",
			"priv_dance_p1"
			); break;
	case 2:
		Animation_Start(
			"mini@strip_club@private_dance@part2",
			"priv_dance_p2"
			); break;
	case 3:
		Animation_Start(
			"mini@strip_club@private_dance@part2",
			"priv_dance_p2"
			); break;
	case 4:
		Animation_Start(
			"oddjobs@assassinate@multi@yachttarget@lapdance",
			"yacht_ld_f"
			); break;
	case 5:
		while(1) {
			if (Animation_Start("timetable@tracy@ig_5@base", "base", true)) break;
			if (Animation_Start("timetable@tracy@ig_5@idle_a", "idle_a", true)) break;
			if (Animation_Start("timetable@tracy@ig_5@idle_a", "idle_b", true)) break;
			if (Animation_Start("timetable@tracy@ig_5@idle_a", "idle_c", true)) break;
			if (Animation_Start("timetable@tracy@ig_5@idle_b", "idle_d", true)) break;
			if (Animation_Start("timetable@tracy@ig_5@idle_b", "idle_e", true)) break;
		} break;
	case 6:
		Animation_Start(
			"special_ped@mountain_dancer@base",
			"base"
			); break;
	case 7:
		Animation_Start(
			"special_ped@mountain_dancer@monologue_2@monologue_2a",
			"mnt_dnc_angel"
			); break;
	case 8:
		Animation_Start(
			"special_ped@mountain_dancer@monologue_3@monologue_3a",
			"mnt_dnc_buttwag"
			); break;
	case 9:
		Animation_Start(
			"special_ped@mountain_dancer@monologue_4@monologue_4a",
			"mnt_dnc_verse"
			); break;
	case 10:
		Animation_Start("rcmnigel1bnmt_1b", "dance_intro_tyler", true);
		Animation_Start("rcmnigel1bnmt_1b", "dance_loop_tyler", false);
		break;
	case 11:
		Animation_Start("misschinese2_crystalmazemcs1_ig", "dance_loop_tao");
		break;
	}
}
void  menu_home_player_animation_dances__display(std::string caption) {

	// Menu Labels
	std::vector <std::string> menu_home_player_animation_dances = {
		// 0
		{ "Stop" },
		// 1 2 3 4 5
		{ "Private dance 1" }, { "Private dance 2" },{ "Private dance 3" },{ "Lap dance" },{ "Game dance" },
		// 6 7 8 9 10
		{ "Mountain dance" },{ "Angel dance" },{ "Buttwag" },{ "Verse" },{ "Tyler's dance"},
		// 11
		{ "Loop dancing"}
	};

	std::vector <std::string> *current_menu = &menu_home_player_animation_dances;
	int *current_line = &active_home_player_animation_dances;

	// Menu Setup and Navigation
	int navigationResult;
	DWORD waitTime = 150;
	int startIndex = 0;
	int endIndex = 15;

	while (true) {
		// draw menu and navigation path
		menu_list_draw(*current_menu, caption, *current_line, &startIndex, &endIndex, &waitTime);
		navigationResult = menu_list_navigate(&waitTime, current_line, (int)(*current_menu).size());;

		if (navigationResult == -1)
			break;
		else if (navigationResult == 1) {
			menu_home_player_animation_dances__action(current_line);
		}
	}
}

int active_home_player_animation = 0;
void  menu_home_player_animation__action(int *ptr_active_line) {

	int active_line = *ptr_active_line;

	switch (active_line) {
	case 0:
		Animation_Stop();
		break;
	case 1:
		menu_home_player_animation_dances__display("Dances");
		break;
	case 2:
		Animation_Start("rcmcollect_paperleadinout@", "meditiate_idle");
		break;
	case 3:
		Animation_Start("switch@trevor@jerking_off", "trev_jerking_off_loop");
		break;
	case 4:
		Animation_Start("amb@world_human_sunbathe@" + gender + "@front@enter", "enter", true);
		while (!Animation_Start("amb@world_human_sunbathe@" + gender + "@front@base", "base", true));
		Animation_Start("amb@world_human_sunbathe@" + gender + "@front@exit", "exit", true);
		Animation_Stop();
		break;
	case 5:
		Animation_Start("amb@world_human_sunbathe@" + gender + "@back@enter", "enter", true);
		while (!Animation_Start("amb@world_human_sunbathe@" + gender + "@back@base", "base", true));
		Animation_Start("amb@world_human_sunbathe@" + gender + "@back@exit", "exit", true);
		Animation_Stop();
		break;
	case 6:
		switch (rand() % 4) {
			case 0: Animation_Start("amb@world_human_cheering@" + gender + "_a", "base"); break;
			case 1: Animation_Start("amb@world_human_cheering@" + gender + "_b", "base"); break;
			case 2: Animation_Start("amb@world_human_cheering@" + gender + "_d", "base"); break;
			case 3: 
				if (gender.compare("male"))
					Animation_Start("amb@world_human_cheering@female_c", "base");
				else
					Animation_Start("amb@world_human_cheering@male_e", "base");
				break;
		}
		break;
	case 7:
		menu_home_player_animation_mimes__display("Mime");
		break;
	case 8:
		menu_home_player_animation_exercises__display("Exercises");
		break;
	case 9:
		menu_home_player_animation_poses__display("Poses");
		break;
	default:
		if (!gender.compare("male")) { //If gender equals male
			gender = "female";
			display_message_caption("Play animation as female");
		}
		else {
			gender = "male";
			display_message_caption("Play animation as male");
		}
	}
}
void  menu_home_player_animation__display(std::string caption) {

	// Menu Labels
	std::vector <std::string> menu_home_player_animation = {
		// 0
		{ "Stop" },
		// 1 2 3 4 5
		{ "Dances:" },{ "Meditate" },{ "Fap" },{ "Sunbath Front" },{ "Sunbath Back" },
		// 6 7 8 9 10
		{ "Cheers" }, { "Mimes:" }, { "Exercises:" }, {"Poses:"}, { gender + ": change"}
	};

	std::vector <std::string> *current_menu = &menu_home_player_animation;
	int *current_line = &active_home_player_animation;

	// Menu Setup and Navigation
	int navigationResult;
	DWORD waitTime = 150;
	int startIndex = 0;
	int endIndex = 15;

	while (true) {
		// draw menu and navigation path
		menu_list_draw(*current_menu, caption, *current_line, &startIndex, &endIndex, &waitTime);
		navigationResult = menu_list_navigate(&waitTime, current_line, (int)(*current_menu).size());;

		if (navigationResult == -1)
			break;
		else if (navigationResult == 1) {
			menu_home_player_animation__action(current_line);
		}
	}
}


LPCSTR componentList[3][13] {
	{ "head", "facial", "hair", "torso", "bottoms", "gloves", "shoes", "x", "objects 1", "objects 2", "decals", "torso inner", "x" },
	{ "head", "mask", "hair", "skin & gloves", "bottoms", "parachute", "shoes", "accessories", "torso inner", "body armor", "decals", "torso outer", "x" }
};

int active_home_player_componentChangerRow = 0;
int active_home_player_componentChangerCol = 0;
bool menu_home_player_componentChanger__display(std::string caption, int playerType) {
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	float lineHeight = 8;
	float lineWidth = 250;
	float defaultSpace = 22;
	float lineTop;
	float titleTop = 60;
	float lineLeft = 1000.0f;

	if ((lineHeight / 2) == 0) // odd number
		lineHeight += 1;

	// timed menu draw, used for pause after active line switch
	DWORD waitTime = 100;
	DWORD maxTickCount = GetTickCount() + waitTime;

	do {
		// Header
		draw_menu_line(caption, lineWidth, 13.0, 18.0, 1000.0, 3.0, false, true);

		// Body
		for (int i = 0; i < 13; i++) {
			lineTop = titleTop + i * ((lineHeight * 1.5f) + defaultSpace);

			draw_menu_line(componentList[playerType][i],
				lineWidth / 3, lineHeight, lineTop, lineLeft + (lineWidth / 3) * 0, 7.0f, false, false);

			if (!(active_home_player_componentChangerCol == 0 && active_home_player_componentChangerRow == i))
				draw_menu_line((std::to_string(ped_componentArr_now[i][0]) + "/" + std::to_string(ped_componentArr_max[i][0])),
				lineWidth / 3, lineHeight, lineTop, lineLeft + (lineWidth / 3) * 1, 7.0f, false, false);

			if (!(active_home_player_componentChangerCol == 1 && active_home_player_componentChangerRow == i))
				draw_menu_line((std::to_string(ped_componentArr_now[i][1]) + "/" + std::to_string(ped_componentArr_max[i][1])),
				lineWidth / 3, lineHeight, lineTop, lineLeft + (lineWidth / 3) * 2, 7.0f, false, false);
		}

		// Active
		lineTop = titleTop + active_home_player_componentChangerRow * ((lineHeight * 1.5f) + defaultSpace);

		draw_menu_line((std::to_string(ped_componentArr_now[active_home_player_componentChangerRow][active_home_player_componentChangerCol]) + "/" + std::to_string(ped_componentArr_max[active_home_player_componentChangerRow][active_home_player_componentChangerCol])),
			lineWidth / 3, lineHeight, lineTop, lineLeft + (lineWidth / 3) * (active_home_player_componentChangerCol + 1), 7.0f, true, false);

		update_features();
	} while (GetTickCount() < maxTickCount);


	bool bSelect, bBack, bUp, bDown, bLeft, bRight, bDec, bInc;
	get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);
	get_button_state(&bDec, &bInc);

	if (bBack || trainer_switch_pressed()) {
		play_sound("BACK");
		return false;
	}
	if (bUp) {
		play_sound("NAV_UP_DOWN");
		if (active_home_player_componentChangerRow == 0)
			active_home_player_componentChangerRow = 13;
		active_home_player_componentChangerRow--;
		waitTime = 80;
	}
	if (bDown) {
		play_sound("NAV_UP_DOWN");
		active_home_player_componentChangerRow++;
		if (active_home_player_componentChangerRow == 13)
			active_home_player_componentChangerRow = 0;
		waitTime = 80;
	}

	if (bLeft) {
		play_sound("NAV_LEFT_RIGHT");
		if (active_home_player_componentChangerCol == 0)
			active_home_player_componentChangerCol = 2;
		active_home_player_componentChangerCol--;
		waitTime = 80;
	}

	if (bRight) {
		play_sound("NAV_LEFT_RIGHT");
		active_home_player_componentChangerCol++;
		if (active_home_player_componentChangerCol == 2)
			active_home_player_componentChangerCol = 0;
		waitTime = 80;
	}
	if (bDec || bInc) {
		int adjust;
		bool isTexture, isDrawable;

		(bDec) ? adjust = -1 : adjust = 1;
		(active_home_player_componentChangerCol) ? isTexture = true : isTexture = false;
		isDrawable = !isTexture;

		int drawableMax = PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(playerPed, active_home_player_componentChangerRow);
		int drawable = ped_componentArr_now[active_home_player_componentChangerRow][0] + adjust * isDrawable;
		if (drawable < 0)
			drawable = drawableMax - 1;
		else if (drawable >= drawableMax)
			drawable = 0;

		int textureMax = PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(playerPed, active_home_player_componentChangerRow, drawable);
		int texture = ped_componentArr_now[active_home_player_componentChangerRow][1] + adjust * isTexture;
		if (texture < 0)
			texture = textureMax - 1;
		else if (texture >= textureMax)
			texture = 0;

		PED::SET_PED_COMPONENT_VARIATION(playerPed, active_home_player_componentChangerRow, drawable, texture, 0);
		ped_components_update(playerPed);
	}

	return true;
}

void play_ped_speech(Ped playerPed, char* speech, Ped otherPed = 0) {

	if (otherPed) AI::TASK_LOOK_AT_ENTITY(playerPed, otherPed, -1, 2048, 3);
	WAIT(20);

	AUDIO::_PLAY_AMBIENT_SPEECH2(playerPed, speech, "Speech_Params_Allow_Repeat");
	if (otherPed) {
		while (AUDIO::IS_AMBIENT_SPEECH_PLAYING(playerPed))	loading_message_show("waiting");
		loading_message_clear();
		AI::TASK_LOOK_AT_ENTITY(playerPed, otherPed, 3000, 2048, 3);
	}
}

int active_home_player_speech = 0;
void menu_home_player_speech__action(int *ptr_active_line) {

	int active_line = *ptr_active_line;

	// Common variables
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	const int numElements = 1;
	const int arrSize = numElements * 2 + 2;  //Start at index 2, and the odd elements are padding
	int peds[arrSize];
	peds[0] = numElements; 	//0 index is the size of the array
	int bFoundPed = PED::GET_PED_NEARBY_PEDS(playerPed, peds, -1);
	Ped otherPed = peds[2];

	switch (active_line) {

	case 0: // Insult
		if (rand() % 2)
			play_ped_speech(playerPed, "GENERIC_INSULT_MED", otherPed);
		else
			play_ped_speech(playerPed, "GENERIC_INSULT_HIGH", otherPed);

		if (bFoundPed) {
			if (rand() % 3)
				play_ped_speech(otherPed, "GENERIC_Frightened_MED");
			else
				play_ped_speech(otherPed, "GENERIC_CURSE_MED");
		}
		break;
	case 1: // Make ped talk
		if (bFoundPed) {
			play_ped_speech(otherPed, "CHAT_STATE", playerPed);
			if (rand() % 2)
				play_ped_speech(playerPed, "CHAT_RESP");
			else
				play_ped_speech(playerPed, "CHAT_STATE");
		}
		else
			display_message_notify("No one is closed by.");
		break;

	case 2: // Make ped listen
		if (bFoundPed) {
			play_ped_speech(playerPed, "CHAT_STATE", otherPed);
			if (rand() % 2)
				play_ped_speech(otherPed, "CHAT_RESP");
			else
				play_ped_speech(otherPed, "CHAT_STATE");
		}
		else
			display_message_notify("No one is closed by.");
		break;
	case 3: // Hi
		if (rand() % 2)
			play_ped_speech(playerPed, "GENERIC_HI", otherPed);
		else
			play_ped_speech(playerPed, "GENERIC_HOWS_IT_GOING", otherPed);
		play_ped_speech(otherPed, "CHAT_STATE");
		break;
	case 4: // Curse
		if (rand() % 2)
			play_ped_speech(playerPed, "GENERIC_CURSE_MED");
		else
			play_ped_speech(playerPed, "GENERIC_CURSE_HIGH");
		break;
	case 5: // Shocked
		if (rand() % 2)
			play_ped_speech(playerPed, "GENERIC_SHOCKED_MED");
		else
			play_ped_speech(playerPed, "GENERIC_SHOCKED_HIGH");
		break;
	case 6: // Frightened
		if (rand() % 2)
			play_ped_speech(playerPed, "GENERIC_Frightened_MED");
		else
			play_ped_speech(playerPed, "GENERIC_Frightened_HIGH");
		break;
	case 7: // Thanks
		play_ped_speech(playerPed, "GENERIC_THANKS", otherPed);
		play_ped_speech(otherPed, "CHAT_RESP");
		break;
	case 8: // Apologize
		play_ped_speech(playerPed, "APOLOGY_NO_TROUBLE");
		break;
	}
}
void menu_home_player_speech__display(std::string caption) {

	// Menu Labels
	const int LINE_COUNT = 9;
	menuList menu_home_player_speech[LINE_COUNT] = {
		/* 0 */{ "Insult" },
		/* 1 */{ "Listen to Ped" },
		/* 2 */{ "Talk to Ped" },
		/* 3 */{ "Greet" },
		/* 4 */{ "Curse" },
		/* 5 */{ "Shocked" },
		/* 6 */{ "Frightened" },
		/* 7 */{ "Thanks" },
		/* 8 */{ "Apologize" }
	};

	menuList *current_menu = menu_home_player_speech;
	int *current_line = &active_home_player_speech;

	// Menu Setup and Navigation
	int navigationResult;
	DWORD waitTime = 150;
	while (true) {
		// draw menu and navigation path
		menu_list_draw(current_menu, LINE_COUNT, caption, *current_line, &waitTime);
		navigationResult = menu_list_navigate(&waitTime, current_line, LINE_COUNT);

		if (navigationResult == -1)
			break;
		else if (navigationResult == 1 || get_key_pressed(0x54)) {
			menu_home_player_speech__action(current_line);
		}
	}
}

int active_home_player_skinChangeLine = 1;
int active_home_player_skinChangeTab = 1;
void  menu_home_player_skinChange__process() {

	// 2D Vector menu
	int *current_line = &active_home_player_skinChangeLine;
	int *current_tab = &active_home_player_skinChangeTab;
	int navigationResult;

	// Menu Setup and Navigation
	DWORD waitTime = 150;
	int startIndex = 1;
	int endIndex = 15;

	// draw menu and navigation path
	while (true) {
		navigationResult = menu_line_process_reflow(pedModels, current_line, current_tab, &startIndex, &endIndex, &waitTime, true, 3.0);
		if (navigationResult == 1)
			set_player_model(PLAYER::PLAYER_PED_ID(), *current_tab - 1, *current_line);
		else if (navigationResult == -1)
			break;
	}
}

int active_home_player = 0;
void  menu_home_player__action(menuList menu_lines[], int *ptr_active_line) {

	int active_line = *ptr_active_line;

	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	switch (active_line) {
		// skin changer
		case 0:
			menu_home_player_skinChange__process();
			break;
	
		// fix player
		case 1:
			menu_home_player_speech__display("Speech Menu");
			break;

		// clean
		case 2:
			if (bPlayerExists) {
				PED::CLEAR_PED_BLOOD_DAMAGE(playerPed);
				PED::RESET_PED_VISIBLE_DAMAGE(playerPed);
			}

			ENTITY::SET_ENTITY_HEALTH(playerPed, ENTITY::GET_ENTITY_MAX_HEALTH(playerPed));
			PED::ADD_ARMOUR_TO_PED(playerPed, PLAYER::GET_PLAYER_MAX_ARMOUR(player) - PED::GET_PED_ARMOUR(playerPed));
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
				Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				if (ENTITY::DOES_ENTITY_EXIST(playerVeh) && !ENTITY::IS_ENTITY_DEAD(playerVeh))
					VEHICLE::SET_VEHICLE_FIXED(playerVeh);
			}
			display_message_caption("Player fixed");

			break;

		// reset model skin
		case 3: 
			PED::SET_PED_DEFAULT_COMPONENT_VARIATION(playerPed);
			PED::CLEAR_ALL_PED_PROPS(playerPed);
			display_message_caption("Using default model skin");
	
		break;

		// blend into ped
		case 4:
			blendIntoPeds();
			break;
		case 5: // Component Changer
			ped_components_update(playerPed);
			while (menu_home_player_componentChanger__display("Component changer", 0));
			ped_components_update(playerPed);
			break;
		case 6: // Animation 
			menu_home_player_animation__display("Animations");
			break;
	}
}
void  menu_home_player__display(std::string caption, DWORD waitTime = 150) {
	// Menu Labels
	const int LINE_COUNT = 7;
	menuList menu_home_player[LINE_COUNT] = {
		/*  0 */ { "Skin Change Menu" },
		/*  1 */ { "Speech Menu" },
		/*  2 */ { "Fix Player" },
		/*  3 */ { "Reset Skin" },
		/*  4 */ { "Disguise as nearby" },
		/*  5 */ { "Skin Component Menu"},
		/*  6 */ { "Animations Menu"}
	};

	menuList *current_menu = menu_home_player;
	int *current_line = &active_home_player;

	// Menu Setup and Navigation
	int navigationResult;
	while (true) {
		// draw menu and navigation path
		menu_list_draw(current_menu, LINE_COUNT, caption, *current_line, &waitTime);
		navigationResult = menu_list_navigate(&waitTime, current_line, LINE_COUNT);

		if (navigationResult == -1)
			break;
		else if (navigationResult == 1) {
			menu_home_player__action(current_menu, current_line);
		}
	}
}

int active_home = 0;
void  menu_home__action(int *ptr_active_line) {

	int active_line = *ptr_active_line;

	switch (active_line) {
		case 0:
			menu_home_player__display("Player Options");
			break;
		case 1:
			menu_home_teleport__process();
			break;
		case 2:
			menu_home_weapon__display("Weapon Options");
			break;
		case 3:
			menu_home_vehicle__display("Vehicle Options");
			break;
		case 4:
			menu_home_time__display("Time Options");
			break;
		case 5:
			menu_home_weather__display("Weather Options");
			break;
		case 6:
			menu_home_misc__display("Misc Options");
			break;
		case 7:
			menu_home_player_gameplay__display("Gameplay Options");
			break;
	}
}
void  menu_home__display(std::string caption) {
	// Menu Labels
	const int LINE_COUNT = 8;
	menuList menu_home[LINE_COUNT] = {
		/* 0 */{ "Player Options" },
		/* 1 */{ "Teleport Menu" },
		/* 2 */{ "Weapon Options" },
		/* 3 */{ "Vehicle Options" },
		/* 4 */{ "Time Options" },
		/* 5 */{ "Weather Options" },
		/* 6 */{ "Misc Options" },
		/* 7 */{ "Gameplay Option" }
	};

	menuList *current_menu = menu_home;
	int *current_line = &active_home;

	// Menu Setup and Navigation
	int navigationResult;
	DWORD waitTime = 150;
	while (true) {
		// draw menu and navigation path
		menu_list_draw(current_menu, LINE_COUNT, caption, *current_line, &waitTime);
		navigationResult = menu_list_navigate(&waitTime, current_line, LINE_COUNT);

		if (navigationResult == -1)
			break;
		else if (navigationResult == 1) {
			menu_home__action(current_line);
		}
	}
}


void reset_globals() {

	featurePlayerInvincible =
		featurePlayerInvincibleUpdated =
		featurePlayerNeverWanted =
		featurePlayerIgnored =
		featurePlayerIgnoredUpdated =
		featurePlayerUnlimitedAbility =
		featurePlayerNoNoise =
		featurePlayerNoNoiseUpdated =
		featurePlayerFastSwim =
		featurePlayerFastSwimUpdated =
		featurePlayerFastRun =
		featurePlayerFastRunUpdated =
		featurePlayerSuperJump =
		featureWeaponNoReload =
		featureWeaponFireAmmo =
		featureWeaponExplosiveAmmo =
		featureWeaponExplosiveMelee =
		featureWeaponVehRockets =
		featureWeaponOneHit =
		featureVehInvincible =
		featureVehInvincibleUpdated =
		featureVehSpeedBoost =
		featureWorldMoonGravity =
		featureTimePaused =
		featureTimePausedUpdated =
		featureTimeSynced =
		featureWeatherWind =
		featureMiscLockRadio =
		featureMiscHideHud =
		featureVehRainbow =
		featureVehStickyCar =
		featureVehSlide =
		featureWorldRandomCops =
		featureWorldRandomTrains =
		featureWorldRandomBoats =
		featurePlayerInvisible =
		featureWorldGarbageTrucks = false;

	featureMiscMobileRadio = 
		bMonitorPlayerRespawn = false;

	featureVehWrapInSpawned = true;
}

void main()
{
	output_writeToLog("ASI Running", false);
	bypass_online();
	reset_globals();

	bMonitorPlayerRespawn = !is_ped_default_player(PLAYER::PLAYER_PED_ID());
	display_message_notify("Kinky 2.1 ex-0.1 loaded");

	while (true) {
		if (trainer_switch_pressed()) {
			srand(time(NULL));
			reset_trainer_switch();
			play_sound("SELECT");
			menu_home__display("Kinky Menu");
			DWORD time = GetTickCount() + 1000;
			while (GetTickCount() < time) {
				update_features();
			}
			reset_trainer_switch();
		}
		update_features();
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}
