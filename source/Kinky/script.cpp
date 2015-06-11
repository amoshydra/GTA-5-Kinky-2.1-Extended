/*
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
	*/

#include <string>
#include <ctime>
#include "script.h"
#include "onlinebypass.h"

#pragma warning(disable : 4244 4305) // double <-> float conversions
int valuef;

/******************
	UI Drawing
******************/

void draw_rect(float A_0, float A_1, float A_2, float A_3, int A_4, int A_5, int A_6, int A_7) {
	GRAPHICS::DRAW_RECT((A_0 + (A_2 * 0.5f)), (A_1 + (A_3 * 0.5f)), A_2, A_3, A_4, A_5, A_6, A_7);
}

void draw_menu_line(std::string caption, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool title, bool rescaleText = true)
{
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
		rect_col[0] = 243;
		rect_col[1] = 23;
		rect_col[2] = 84;
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

/**********************
	Button handling
**********************/

bool get_key_pressed(int nVirtKey) {
	//return (GetKeyState(nVirtKey) & 0x8000) != 0;
	return (GetAsyncKeyState(nVirtKey) & 0x8000) != 0;
}

DWORD trainerResetTime = 0;
bool trainer_switch_pressed() {
	return (GetTickCount() > trainerResetTime + 1000) && get_key_pressed(VK_F6);
}

void reset_trainer_switch() {
	trainerResetTime = GetTickCount();
}

void get_button_state(bool *select, bool *back, bool *up, bool *down, bool *left, bool *right) {
	if (select) *select = get_key_pressed(VK_NUMPAD5);
	if (back) *back = get_key_pressed(VK_NUMPAD0) || trainer_switch_pressed() /*|| get_key_pressed(VK_BACK)*/;
	if (up) *up = get_key_pressed(VK_NUMPAD8);
	if (down) *down = get_key_pressed(VK_NUMPAD2);
	if (left) *left = get_key_pressed(VK_NUMPAD4);
	if (right) *right = get_key_pressed(VK_NUMPAD6);
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


// Status Text //
std::string statusText;
DWORD statusTextDrawTicksMax;
bool statusTextGxtEntry;
void update_status_text()
{
	if (GetTickCount() < statusTextDrawTicksMax)
	{
		UI::SET_TEXT_FONT(4);
		UI::SET_TEXT_SCALE(0.55, 0.55);
		UI::SET_TEXT_COLOUR(243, 23, 84, 255);
		UI::SET_TEXT_WRAP(0.0, 1.0);
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
void set_status_text(std::string str, DWORD time = 2500, bool isGxtEntry = false)
{
	statusText = str;
	statusTextDrawTicksMax = GetTickCount() + time;
	statusTextGxtEntry = isGxtEntry;
}
void set_permstatus_text(std::string str, bool isGxtEntry = false)
{
	statusText = str;
	statusTextGxtEntry = isGxtEntry;
}

// Help Text //
void display_message_caption(char* text, int msToDisplay = 2500) {
	UI::_SET_TEXT_ENTRY_2("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_0x9D77056A530643F6(msToDisplay, 1);
}

// Notification //
void display_message_notify(char* text) {
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING3(text);
	UI::_DRAW_NOTIFICATION(1, 1);
}


// features
bool featurePlayerInvincible					=	false;
bool featurePlayerInvincibleUpdated				=	false;
bool featurePlayerNeverWanted					=	false;
bool featurePlayerIgnored						=	false;
bool featurePlayerIgnoredUpdated				=	false;
bool featurePlayerUnlimitedAbility				=	false;
bool featurePlayerNoNoise						=	false;
bool featurePlayerNoNoiseUpdated				=	false;
bool featurePlayerFastSwim						=	false;
bool featurePlayerFastSwimUpdated				=	false;
bool featurePlayerFastRun						=	false;
bool featurePlayerFastRunUpdated				=	false;
bool featurePlayerSuperJump						=	false;
bool featurePlayerInvisible						=	false;

bool featureWeaponNoReload						=	false;
bool featureWeaponFireAmmo						=	false;
bool featureWeaponExplosiveAmmo					=	false;
bool featureWeaponExplosiveMelee				=	false;
bool featureWeaponVehRockets					=	false;
bool featureWeaponOneHit						=	false;

DWORD featureWeaponVehShootLastTime				=	0;

bool featureVehInvincible						=	false;
bool featureVehInvincibleUpdated				=	false;
bool featureVehSpeedBoost						=	false;
bool featureVehWrapInSpawned					=	false;
bool featureVehRainbow							=	false;
bool featureVehStickyCar						=	false;
bool featureVehSlide							=	false;

bool featureWorldMoonGravity					=	false;
bool featureWorldRandomCops						=	false;
bool featureWorldRandomTrains					=	false;
bool featureWorldRandomBoats					=	false;
bool featureWorldGarbageTrucks					=	false;

bool featureTimePaused							=	false;
bool featureTimePausedUpdated					=	false;
bool featureTimeSynced							=	false;

bool featureWeatherWind							=	false;

bool featureMiscLockRadio						=	false;
bool featureMiscHideHud							=	false;
bool featureMiscMobileRadio						=	false;

int rainbowCount								=	0;


// player model control, switching on normal ped model when needed	

static LPCSTR animalModels[] = { "a_c_boar", "a_c_chimp", "a_c_cow", "a_c_coyote", "a_c_deer", "a_c_fish", "a_c_hen", "a_c_cat_01", "a_c_chickenhawk",
"a_c_cormorant", "a_c_crow", "a_c_dolphin", "a_c_humpback", "a_c_killerwhale", "a_c_pigeon", "a_c_seagull", "a_c_sharkhammer",
"a_c_pig", "a_c_rat", "a_c_rhesus", "a_c_chop", "a_c_husky", "a_c_mtlion", "a_c_retriever", "a_c_sharktiger", "a_c_shepherd" };

static LPCSTR defaultModels[] = { "player_zero", "player_one", "player_two" };

static LPCSTR pedModels[69][10] = {
	{ "player_zero", "player_one", "player_two", "a_c_boar", "a_c_chimp", "a_c_cow", "a_c_coyote", "a_c_deer", "a_c_fish", "a_c_hen" },
	{ "a_c_cat_01", "a_c_chickenhawk", "a_c_cormorant", "a_c_crow", "a_c_dolphin", "a_c_humpback", "a_c_killerwhale", "a_c_pigeon", "a_c_seagull", "a_c_sharkhammer" },
	{ "a_c_pig", "a_c_rat", "a_c_rhesus", "a_c_chop", "a_c_husky", "a_c_mtlion", "a_c_retriever", "a_c_sharktiger", "a_c_shepherd", "s_m_m_movalien_01" },
	{ "a_f_m_beach_01", "a_f_m_bevhills_01", "a_f_m_bevhills_02", "a_f_m_bodybuild_01", "a_f_m_business_02", "a_f_m_downtown_01", "a_f_m_eastsa_01", "a_f_m_eastsa_02", "a_f_m_fatbla_01", "a_f_m_fatcult_01" },
	{ "a_f_m_fatwhite_01", "a_f_m_ktown_01", "a_f_m_ktown_02", "a_f_m_prolhost_01", "a_f_m_salton_01", "a_f_m_skidrow_01", "a_f_m_soucentmc_01", "a_f_m_soucent_01", "a_f_m_soucent_02", "a_f_m_tourist_01" },
	{ "a_f_m_trampbeac_01", "a_f_m_tramp_01", "a_f_o_genstreet_01", "a_f_o_indian_01", "a_f_o_ktown_01", "a_f_o_salton_01", "a_f_o_soucent_01", "a_f_o_soucent_02", "a_f_y_beach_01", "a_f_y_bevhills_01" },
	{ "a_f_y_bevhills_02", "a_f_y_bevhills_03", "a_f_y_bevhills_04", "a_f_y_business_01", "a_f_y_business_02", "a_f_y_business_03", "a_f_y_business_04", "a_f_y_eastsa_01", "a_f_y_eastsa_02", "a_f_y_eastsa_03" },
	{ "a_f_y_epsilon_01", "a_f_y_fitness_01", "a_f_y_fitness_02", "a_f_y_genhot_01", "a_f_y_golfer_01", "a_f_y_hiker_01", "a_f_y_hippie_01", "a_f_y_hipster_01", "a_f_y_hipster_02", "a_f_y_hipster_03" },
	{ "a_f_y_hipster_04", "a_f_y_indian_01", "a_f_y_juggalo_01", "a_f_y_runner_01", "a_f_y_rurmeth_01", "a_f_y_scdressy_01", "a_f_y_skater_01", "a_f_y_soucent_01", "a_f_y_soucent_02", "a_f_y_soucent_03" },
	{ "a_f_y_tennis_01", "a_f_y_topless_01", "a_f_y_tourist_01", "a_f_y_tourist_02", "a_f_y_vinewood_01", "a_f_y_vinewood_02", "a_f_y_vinewood_03", "a_f_y_vinewood_04", "a_f_y_yoga_01", "a_m_m_acult_01" },
	{ "a_m_m_afriamer_01", "a_m_m_beach_01", "a_m_m_beach_02", "a_m_m_bevhills_01", "a_m_m_bevhills_02", "a_m_m_business_01", "a_m_m_eastsa_01", "a_m_m_eastsa_02", "a_m_m_farmer_01", "a_m_m_fatlatin_01" },
	{ "a_m_m_genfat_01", "a_m_m_genfat_02", "a_m_m_golfer_01", "a_m_m_hasjew_01", "a_m_m_hillbilly_01", "a_m_m_hillbilly_02", "a_m_m_indian_01", "a_m_m_ktown_01", "a_m_m_malibu_01", "a_m_m_mexcntry_01" },
	{ "a_m_m_mexlabor_01", "a_m_m_og_boss_01", "a_m_m_paparazzi_01", "a_m_m_polynesian_01", "a_m_m_prolhost_01", "a_m_m_rurmeth_01", "a_m_m_salton_01", "a_m_m_salton_02", "a_m_m_salton_03", "a_m_m_salton_04" },
	{ "a_m_m_skater_01", "a_m_m_skidrow_01", "a_m_m_socenlat_01", "a_m_m_soucent_01", "a_m_m_soucent_02", "a_m_m_soucent_03", "a_m_m_soucent_04", "a_m_m_stlat_02", "a_m_m_tennis_01", "a_m_m_tourist_01" },
	{ "a_m_m_trampbeac_01", "a_m_m_tramp_01", "a_m_m_tranvest_01", "a_m_m_tranvest_02", "a_m_o_acult_01", "a_m_o_acult_02", "a_m_o_beach_01", "a_m_o_genstreet_01", "a_m_o_ktown_01", "a_m_o_salton_01" },
	{ "a_m_o_soucent_01", "a_m_o_soucent_02", "a_m_o_soucent_03", "a_m_o_tramp_01", "a_m_y_acult_01", "a_m_y_acult_02", "a_m_y_beachvesp_01", "a_m_y_beachvesp_02", "a_m_y_beach_01", "a_m_y_beach_02" },
	{ "a_m_y_beach_03", "a_m_y_bevhills_01", "a_m_y_bevhills_02", "a_m_y_breakdance_01", "a_m_y_busicas_01", "a_m_y_business_01", "a_m_y_business_02", "a_m_y_business_03", "a_m_y_cyclist_01", "a_m_y_dhill_01" },
	{ "a_m_y_downtown_01", "a_m_y_eastsa_01", "a_m_y_eastsa_02", "a_m_y_epsilon_01", "a_m_y_epsilon_02", "a_m_y_gay_01", "a_m_y_gay_02", "a_m_y_genstreet_01", "a_m_y_genstreet_02", "a_m_y_golfer_01" },
	{ "a_m_y_hasjew_01", "a_m_y_hiker_01", "a_m_y_hippy_01", "a_m_y_hipster_01", "a_m_y_hipster_02", "a_m_y_hipster_03", "a_m_y_indian_01", "a_m_y_jetski_01", "a_m_y_juggalo_01", "a_m_y_ktown_01" },
	{ "a_m_y_ktown_02", "a_m_y_latino_01", "a_m_y_methhead_01", "a_m_y_mexthug_01", "a_m_y_motox_01", "a_m_y_motox_02", "a_m_y_musclbeac_01", "a_m_y_musclbeac_02", "a_m_y_polynesian_01", "a_m_y_roadcyc_01" },
	{ "a_m_y_runner_01", "a_m_y_runner_02", "a_m_y_salton_01", "a_m_y_skater_01", "a_m_y_skater_02", "a_m_y_soucent_01", "a_m_y_soucent_02", "a_m_y_soucent_03", "a_m_y_soucent_04", "a_m_y_stbla_01" },
	{ "a_m_y_stbla_02", "a_m_y_stlat_01", "a_m_y_stwhi_01", "a_m_y_stwhi_02", "a_m_y_sunbathe_01", "a_m_y_surfer_01", "a_m_y_vindouche_01", "a_m_y_vinewood_01", "a_m_y_vinewood_02", "a_m_y_vinewood_03" },
	{ "a_m_y_vinewood_04", "a_m_y_yoga_01", "u_m_y_proldriver_01", "u_m_y_rsranger_01", "u_m_y_sbike", "u_m_y_staggrm_01", "u_m_y_tattoo_01", "csb_abigail", "csb_anita", "csb_anton" },
	{ "csb_ballasog", "csb_bride", "csb_burgerdrug", "csb_car3guy1", "csb_car3guy2", "csb_chef", "csb_chin_goon", "csb_cletus", "csb_cop", "csb_customer" },
	{ "csb_denise_friend", "csb_fos_rep", "csb_g", "csb_groom", "csb_grove_str_dlr", "csb_hao", "csb_hugh", "csb_imran", "csb_janitor", "csb_maude" },
	{ "csb_mweather", "csb_ortega", "csb_oscar", "csb_porndudes", "csb_porndudes_p", "csb_prologuedriver", "csb_prolsec", "csb_ramp_gang", "csb_ramp_hic", "csb_ramp_hipster" },
	{ "csb_ramp_marine", "csb_ramp_mex", "csb_reporter", "csb_roccopelosi", "csb_screen_writer", "csb_stripper_01", "csb_stripper_02", "csb_tonya", "csb_trafficwarden", "cs_amandatownley" },
	{ "cs_andreas", "cs_ashley", "cs_bankman", "cs_barry", "cs_barry_p", "cs_beverly", "cs_beverly_p", "cs_brad", "cs_bradcadaver", "cs_carbuyer" },
	{ "cs_casey", "cs_chengsr", "cs_chrisformage", "cs_clay", "cs_dale", "cs_davenorton", "cs_debra", "cs_denise", "cs_devin", "cs_dom" },
	{ "cs_dreyfuss", "cs_drfriedlander", "cs_fabien", "cs_fbisuit_01", "cs_floyd", "cs_guadalope", "cs_gurk", "cs_hunter", "cs_janet", "cs_jewelass" },
	{ "cs_jimmyboston", "cs_jimmydisanto", "cs_joeminuteman", "cs_johnnyklebitz", "cs_josef", "cs_josh", "cs_lamardavis", "cs_lazlow", "cs_lestercrest", "cs_lifeinvad_01" },
	{ "cs_magenta", "cs_manuel", "cs_marnie", "cs_martinmadrazo", "cs_maryann", "cs_michelle", "cs_milton", "cs_molly", "cs_movpremf_01", "cs_movpremmale" },
	{ "cs_mrk", "cs_mrsphillips", "cs_mrs_thornhill", "cs_natalia", "cs_nervousron", "cs_nigel", "cs_old_man1a", "cs_old_man2", "cs_omega", "cs_orleans" },
	{ "cs_paper", "cs_paper_p", "cs_patricia", "cs_priest", "cs_prolsec_02", "cs_russiandrunk", "cs_siemonyetarian", "cs_solomon", "cs_stevehains", "cs_stretch" },
	{ "cs_tanisha", "cs_taocheng", "cs_taostranslator", "cs_tenniscoach", "cs_terry", "cs_tom", "cs_tomepsilon", "cs_tracydisanto", "cs_wade", "cs_zimbor" },
	{ "g_f_y_ballas_01", "g_f_y_families_01", "g_f_y_lost_01", "g_f_y_vagos_01", "g_m_m_armboss_01", "g_m_m_armgoon_01", "g_m_m_armlieut_01", "g_m_m_chemwork_01", "g_m_m_chemwork_01_p", "g_m_m_chiboss_01" },
	{ "g_m_m_chiboss_01_p", "g_m_m_chicold_01", "g_m_m_chicold_01_p", "g_m_m_chigoon_01", "g_m_m_chigoon_01_p", "g_m_m_chigoon_02", "g_m_m_korboss_01", "g_m_m_mexboss_01", "g_m_m_mexboss_02", "g_m_y_armgoon_02" },
	{ "g_m_y_azteca_01", "g_m_y_ballaeast_01", "g_m_y_ballaorig_01", "g_m_y_ballasout_01", "g_m_y_famca_01", "g_m_y_famdnf_01", "g_m_y_famfor_01", "g_m_y_korean_01", "g_m_y_korean_02", "g_m_y_korlieut_01" },
	{ "g_m_y_lost_01", "g_m_y_lost_02", "g_m_y_lost_03", "g_m_y_mexgang_01", "g_m_y_mexgoon_01", "g_m_y_mexgoon_02", "g_m_y_mexgoon_03", "g_m_y_mexgoon_03_p", "g_m_y_pologoon_01", "g_m_y_pologoon_01_p" },
	{ "g_m_y_pologoon_02", "g_m_y_pologoon_02_p", "g_m_y_salvaboss_01", "g_m_y_salvagoon_01", "g_m_y_salvagoon_02", "g_m_y_salvagoon_03", "g_m_y_salvagoon_03_p", "g_m_y_strpunk_01", "g_m_y_strpunk_02", "hc_driver" },
	{ "hc_gunman", "hc_hacker", "ig_abigail", "ig_amandatownley", "ig_andreas", "ig_ashley", "ig_ballasog", "ig_bankman", "ig_barry", "ig_barry_p" },
	{ "ig_bestmen", "ig_beverly", "ig_beverly_p", "ig_brad", "ig_bride", "ig_car3guy1", "ig_car3guy2", "ig_casey", "ig_chef", "ig_chengsr" },
	{ "ig_chrisformage", "ig_clay", "ig_claypain", "ig_cletus", "ig_dale", "ig_davenorton", "ig_denise", "ig_devin", "ig_dom", "ig_dreyfuss" },
	{ "ig_drfriedlander", "ig_fabien", "ig_fbisuit_01", "ig_floyd", "ig_groom", "ig_hao", "ig_hunter", "ig_janet", "ig_jay_norris", "ig_jewelass" },
	{ "ig_jimmyboston", "ig_jimmydisanto", "ig_joeminuteman", "ig_johnnyklebitz", "ig_josef", "ig_josh", "ig_kerrymcintosh", "ig_lamardavis", "ig_lazlow", "ig_lestercrest" },
	{ "ig_lifeinvad_01", "ig_lifeinvad_02", "ig_magenta", "ig_manuel", "ig_marnie", "ig_maryann", "ig_maude", "ig_michelle", "ig_milton", "ig_molly" },
	{ "ig_mrk", "ig_mrsphillips", "ig_mrs_thornhill", "ig_natalia", "ig_nervousron", "ig_nigel", "ig_old_man1a", "ig_old_man2", "ig_omega", "ig_oneil" },
	{ "ig_orleans", "ig_ortega", "ig_paper", "ig_patricia", "ig_priest", "ig_prolsec_02", "ig_ramp_gang", "ig_ramp_hic", "ig_ramp_hipster", "ig_ramp_mex" },
	{ "ig_roccopelosi", "ig_russiandrunk", "ig_screen_writer", "ig_siemonyetarian", "ig_solomon", "ig_stevehains", "ig_stretch", "ig_talina", "ig_tanisha", "ig_taocheng" },
	{ "ig_taostranslator", "ig_taostranslator_p", "ig_tenniscoach", "ig_terry", "ig_tomepsilon", "ig_tonya", "ig_tracydisanto", "ig_trafficwarden", "ig_tylerdix", "ig_wade" },
	{ "ig_zimbor", "mp_f_deadhooker", "mp_f_freemode_01", "mp_f_misty_01", "mp_f_stripperlite", "mp_g_m_pros_01", "mp_headtargets", "mp_m_claude_01", "mp_m_exarmy_01", "mp_m_famdd_01" },
	{ "mp_m_fibsec_01", "mp_m_freemode_01", "mp_m_marston_01", "mp_m_niko_01", "mp_m_shopkeep_01", "mp_s_m_armoured_01", "", "", "", "" },
	{ "", "s_f_m_fembarber", "s_f_m_maid_01", "s_f_m_shop_high", "s_f_m_sweatshop_01", "s_f_y_airhostess_01", "s_f_y_bartender_01", "s_f_y_baywatch_01", "s_f_y_cop_01", "s_f_y_factory_01" },
	{ "s_f_y_hooker_01", "s_f_y_hooker_02", "s_f_y_hooker_03", "s_f_y_migrant_01", "s_f_y_movprem_01", "s_f_y_ranger_01", "s_f_y_scrubs_01", "s_f_y_sheriff_01", "s_f_y_shop_low", "s_f_y_shop_mid" },
	{ "s_f_y_stripperlite", "s_f_y_stripper_01", "s_f_y_stripper_02", "s_f_y_sweatshop_01", "s_m_m_ammucountry", "s_m_m_armoured_01", "s_m_m_armoured_02", "s_m_m_autoshop_01", "s_m_m_autoshop_02", "s_m_m_bouncer_01" },
	{ "s_m_m_chemsec_01", "s_m_m_ciasec_01", "s_m_m_cntrybar_01", "s_m_m_dockwork_01", "s_m_m_doctor_01", "s_m_m_fiboffice_01", "s_m_m_fiboffice_02", "s_m_m_gaffer_01", "s_m_m_gardener_01", "s_m_m_gentransport" },
	{ "s_m_m_hairdress_01", "s_m_m_highsec_01", "s_m_m_highsec_02", "s_m_m_janitor", "s_m_m_lathandy_01", "s_m_m_lifeinvad_01", "s_m_m_linecook", "s_m_m_lsmetro_01", "s_m_m_mariachi_01", "s_m_m_marine_01" },
	{ "s_m_m_marine_02", "s_m_m_migrant_01", "u_m_y_zombie_01", "s_m_m_movprem_01", "s_m_m_movspace_01", "s_m_m_paramedic_01", "s_m_m_pilot_01", "s_m_m_pilot_02", "s_m_m_postal_01", "s_m_m_postal_02" },
	{ "s_m_m_prisguard_01", "s_m_m_scientist_01", "s_m_m_security_01", "s_m_m_snowcop_01", "s_m_m_strperf_01", "s_m_m_strpreach_01", "s_m_m_strvend_01", "s_m_m_trucker_01", "s_m_m_ups_01", "s_m_m_ups_02" },
	{ "s_m_o_busker_01", "s_m_y_airworker", "s_m_y_ammucity_01", "s_m_y_armymech_01", "s_m_y_autopsy_01", "s_m_y_barman_01", "s_m_y_baywatch_01", "s_m_y_blackops_01", "s_m_y_blackops_02", "s_m_y_busboy_01" },
	{ "s_m_y_chef_01", "s_m_y_clown_01", "s_m_y_construct_01", "s_m_y_construct_02", "s_m_y_cop_01", "s_m_y_dealer_01", "s_m_y_devinsec_01", "s_m_y_dockwork_01", "s_m_y_doorman_01", "s_m_y_dwservice_01" },
	{ "s_m_y_dwservice_02", "s_m_y_factory_01", "s_m_y_fireman_01", "s_m_y_garbage", "s_m_y_grip_01", "s_m_y_hwaycop_01", "s_m_y_marine_01", "s_m_y_marine_02", "s_m_y_marine_03", "s_m_y_mime" },
	{ "s_m_y_pestcont_01", "s_m_y_pilot_01", "s_m_y_prismuscl_01", "s_m_y_prisoner_01", "s_m_y_ranger_01", "s_m_y_robber_01", "s_m_y_sheriff_01", "s_m_y_shop_mask", "s_m_y_strvend_01", "s_m_y_swat_01" },
	{ "s_m_y_uscg_01", "s_m_y_valet_01", "s_m_y_waiter_01", "s_m_y_winclean_01", "s_m_y_xmech_01", "s_m_y_xmech_02", "u_f_m_corpse_01", "u_f_m_miranda", "u_f_m_promourn_01", "u_f_o_moviestar" },
	{ "u_f_o_prolhost_01", "u_f_y_bikerchic", "u_f_y_comjane", "u_f_y_corpse_01", "u_f_y_corpse_02", "u_f_y_hotposh_01", "u_f_y_jewelass_01", "u_f_y_mistress", "u_f_y_poppymich", "u_f_y_princess" },
	{ "u_f_y_spyactress", "u_m_m_aldinapoli", "u_m_m_bankman", "u_m_m_bikehire_01", "u_m_m_fibarchitect", "u_m_m_filmdirector", "u_m_m_glenstank_01", "u_m_m_griff_01", "u_m_m_jesus_01", "u_m_m_jewelsec_01" },
	{ "u_m_m_jewelthief", "u_m_m_markfost", "u_m_m_partytarget", "u_m_m_prolsec_01", "u_m_m_promourn_01", "u_m_m_rivalpap", "u_m_m_spyactor", "u_m_m_willyfist", "u_m_o_finguru_01", "u_m_o_taphillbilly" },
	{ "u_m_o_tramp_01", "u_m_y_abner", "u_m_y_antonb", "u_m_y_babyd", "u_m_y_baygor", "u_m_y_burgerdrug_01", "u_m_y_chip", "u_m_y_cyclist_01", "u_m_y_fibmugger_01", "u_m_y_guido_01" },
	{ "u_m_y_gunvend_01", "u_m_y_hippie_01", "u_m_y_imporage", "u_m_y_justin", "u_m_y_mani", "u_m_y_militarybum", "u_m_y_paparazzi", "u_m_y_party_01", "u_m_y_pogo_01", "u_m_y_prisoner_01" }
};

static LPCSTR pedModelNames[69][10] = {
	{ "MICHAEL", "FRANKLIN", "TREVOR", "BOAR", "CHIMP", "COW", "COYOTE", "DEER", "FISH", "HEN" },
	{ "CAT", "HAWK", "CORMORANT", "CROW", "DOLPHIN", "HUMPBACK", "WHALE", "PIGEON", "SEAGULL", "SHARKHAMMER" },
	{ "PIG", "RAT", "RHESUS", "CHOP", "HUSKY", "MTLION", "RETRIEVER", "SHARKTIGER", "SHEPHERD", "ALIEN" },
	{ "BEACH", "BEVHILLS", "BEVHILLS", "BODYBUILD", "BUSINESS", "DOWNTOWN", "EASTSA", "EASTSA", "FATBLA", "FATCULT" },
	{ "FATWHITE", "KTOWN", "KTOWN", "PROLHOST", "SALTON", "SKIDROW", "SOUCENTMC", "SOUCENT", "SOUCENT", "TOURIST" },
	{ "TRAMPBEAC", "TRAMP", "GENSTREET", "INDIAN", "KTOWN", "SALTON", "SOUCENT", "SOUCENT", "BEACH", "BEVHILLS" },
	{ "BEVHILLS", "BEVHILLS", "BEVHILLS", "BUSINESS", "BUSINESS", "BUSINESS", "BUSINESS", "EASTSA", "EASTSA", "EASTSA" },
	{ "EPSILON", "FITNESS", "FITNESS", "GENHOT", "GOLFER", "HIKER", "HIPPIE", "HIPSTER", "HIPSTER", "HIPSTER" },
	{ "HIPSTER", "INDIAN", "JUGGALO", "RUNNER", "RURMETH", "SCDRESSY", "SKATER", "SOUCENT", "SOUCENT", "SOUCENT" },
	{ "TENNIS", "TOPLESS", "TOURIST", "TOURIST", "VINEWOOD", "VINEWOOD", "VINEWOOD", "VINEWOOD", "YOGA", "ACULT" },
	{ "AFRIAMER", "BEACH", "BEACH", "BEVHILLS", "BEVHILLS", "BUSINESS", "EASTSA", "EASTSA", "FARMER", "FATLATIN" },
	{ "GENFAT", "GENFAT", "GOLFER", "HASJEW", "HILLBILLY", "HILLBILLY", "INDIAN", "KTOWN", "MALIBU", "MEXCNTRY" },
	{ "MEXLABOR", "OG_BOSS", "PAPARAZZI", "POLYNESIAN", "PROLHOST", "RURMETH", "SALTON", "SALTON", "SALTON", "SALTON" },
	{ "SKATER", "SKIDROW", "SOCENLAT", "SOUCENT", "SOUCENT", "SOUCENT", "SOUCENT", "STLAT", "TENNIS", "TOURIST" },
	{ "TRAMPBEAC", "TRAMP", "TRANVEST", "TRANVEST", "ACULT", "ACULT", "BEACH", "GENSTREET", "KTOWN", "SALTON" },
	{ "SOUCENT", "SOUCENT", "SOUCENT", "TRAMP", "ACULT", "ACULT", "BEACHVESP", "BEACHVESP", "BEACH", "BEACH" },
	{ "BEACH", "BEVHILLS", "BEVHILLS", "BREAKDANCE", "BUSICAS", "BUSINESS", "BUSINESS", "BUSINESS", "CYCLIST", "DHILL" },
	{ "DOWNTOWN", "EASTSA", "EASTSA", "EPSILON", "EPSILON", "GAY", "GAY", "GENSTREET", "GENSTREET", "GOLFER" },
	{ "HASJEW", "HIKER", "HIPPY", "HIPSTER", "HIPSTER", "HIPSTER", "INDIAN", "JETSKI", "JUGGALO", "KTOWN" },
	{ "KTOWN", "LATINO", "METHHEAD", "MEXTHUG", "MOTOX", "MOTOX", "MUSCLBEAC", "MUSCLBEAC", "POLYNESIAN", "ROADCYC" },
	{ "RUNNER", "RUNNER", "SALTON", "SKATER", "SKATER", "SOUCENT", "SOUCENT", "SOUCENT", "SOUCENT", "STBLA" },
	{ "STBLA", "STLAT", "STWHI", "STWHI", "SUNBATHE", "SURFER", "VINDOUCHE", "VINEWOOD", "VINEWOOD", "VINEWOOD" },
	{ "VINEWOOD", "YOGA", "PROLDRIVER", "RSRANGER", "SBIKE", "STAGGRM", "TATTOO", "ABIGAIL", "ANITA", "ANTON" },
	{ "BALLASOG", "BRIDE", "BURGERDRUG", "CAR3GUY1", "CAR3GUY2", "CHEF", "CHIN_GOON", "CLETUS", "COP", "CUSTOMER" },
	{ "DENISE_FRIEND", "FOS_REP", "G", "GROOM", "DLR", "HAO", "HUGH", "IMRAN", "JANITOR", "MAUDE" },
	{ "MWEATHER", "ORTEGA", "OSCAR", "PORNDUDES", "PORNDUDES_P", "PROLOGUEDRIVER", "PROLSEC", "GANG", "HIC", "HIPSTER" },
	{ "MARINE", "MEX", "REPORTER", "ROCCOPELOSI", "SCREEN_WRITER", "STRIPPER", "STRIPPER", "TONYA", "TRAFFICWARDEN", "AMANDATOWNLEY" },
	{ "ANDREAS", "ASHLEY", "BANKMAN", "BARRY", "BARRY_P", "BEVERLY", "BEVERLY_P", "BRAD", "BRADCADAVER", "CARBUYER" },
	{ "CASEY", "CHENGSR", "CHRISFORMAGE", "CLAY", "DALE", "DAVENORTON", "DEBRA", "DENISE", "DEVIN", "DOM" },
	{ "DREYFUSS", "DRFRIEDLANDER", "FABIEN", "FBISUIT", "FLOYD", "GUADALOPE", "GURK", "HUNTER", "JANET", "JEWELASS" },
	{ "JIMMYBOSTON", "JIMMYDISANTO", "JOEMINUTEMAN", "JOHNNYKLEBITZ", "JOSEF", "JOSH", "LAMARDAVIS", "LAZLOW", "LESTERCREST", "LIFEINVAD" },
	{ "MAGENTA", "MANUEL", "MARNIE", "MARTINMADRAZO", "MARYANN", "MICHELLE", "MILTON", "MOLLY", "MOVPREMF", "MOVPREMMALE" },
	{ "MRK", "MRSPHILLIPS", "MRS_THORNHILL", "NATALIA", "NERVOUSRON", "NIGEL", "OLD_MAN1A", "OLD_MAN2", "OMEGA", "ORLEANS" },
	{ "PAPER", "PAPER_P", "PATRICIA", "PRIEST", "PROLSEC", "RUSSIANDRUNK", "SIEMONYETARIAN", "SOLOMON", "STEVEHAINS", "STRETCH" },
	{ "TANISHA", "TAOCHENG", "TAOSTRANSLATOR", "TENNISCOACH", "TERRY", "TOM", "TOMEPSILON", "TRACYDISANTO", "WADE", "ZIMBOR" },
	{ "BALLAS", "FAMILIES", "LOST", "VAGOS", "ARMBOSS", "ARMGOON", "ARMLIEUT", "CHEMWORK", "CHEMWORK_P", "CHIBOSS" },
	{ "CHIBOSS_P", "CHICOLD", "CHICOLD_P", "CHIGOON", "CHIGOON_P", "CHIGOON", "KORBOSS", "MEXBOSS", "MEXBOSS", "ARMGOON" },
	{ "AZTECA", "BALLAEAST", "BALLAORIG", "BALLASOUT", "FAMCA", "FAMDNF", "FAMFOR", "KOREAN", "KOREAN", "KORLIEUT" },
	{ "LOST", "LOST", "LOST", "MEXGANG", "MEXGOON", "MEXGOON", "MEXGOON", "MEXGOON_P", "POLOGOON", "POLOGOON_P" },
	{ "POLOGOON", "POLOGOON_P", "SALVABOSS", "SALVAGOON", "SALVAGOON", "SALVAGOON", "SALVAGOON_P", "STRPUNK", "STRPUNK", "HC_DRIVER" },
	{ "HC_GUNMAN", "HC_HACKER", "ABIGAIL", "AMANDATOWNLEY", "ANDREAS", "ASHLEY", "BALLASOG", "BANKMAN", "BARRY", "BARRY_P" },
	{ "BESTMEN", "BEVERLY", "BEVERLY_P", "BRAD", "BRIDE", "CAR3GUY1", "CAR3GUY2", "CASEY", "CHEF", "CHENGSR" },
	{ "CHRISFORMAGE", "CLAY", "CLAYPAIN", "CLETUS", "DALE", "DAVENORTON", "DENISE", "DEVIN", "DOM", "DREYFUSS" },
	{ "DRFRIEDLANDER", "FABIEN", "FBISUIT", "FLOYD", "GROOM", "HAO", "HUNTER", "JANET", "JAY_NORRIS", "JEWELASS" },
	{ "JIMMYBOSTON", "JIMMYDISANTO", "JOEMINUTEMAN", "JOHNNYKLEBITZ", "JOSEF", "JOSH", "KERRYMCINTOSH", "LAMARDAVIS", "LAZLOW", "LESTERCREST" },
	{ "LIFEINVAD", "LIFEINVAD", "MAGENTA", "MANUEL", "MARNIE", "MARYANN", "MAUDE", "MICHELLE", "MILTON", "MOLLY" },
	{ "MRK", "MRSPHILLIPS", "MRS_THORNHILL", "NATALIA", "NERVOUSRON", "NIGEL", "OLD_MAN1A", "OLD_MAN2", "OMEGA", "ONEIL" },
	{ "ORLEANS", "ORTEGA", "PAPER", "PATRICIA", "PRIEST", "PROLSEC", "GANG", "HIC", "HIPSTER", "MEX" },
	{ "ROCCOPELOSI", "RUSSIANDRUNK", "SCREEN_WRITER", "SIEMONYETARIAN", "SOLOMON", "STEVEHAINS", "STRETCH", "TALINA", "TANISHA", "TAOCHENG" },
	{ "TAOSTRANSLATOR", "TAOSTRANSLATOR_P", "TENNISCOACH", "TERRY", "TOMEPSILON", "TONYA", "TRACYDISANTO", "TRAFFICWARDEN", "TYLERDIX", "WADE" },
	{ "ZIMBOR", "DEADHOOKER", "FREEMODE", "MISTY", "STRIPPERLITE", "PROS", "MP_HEADTARGETS", "CLAUDE", "EXARMY", "FAMDD" },
	{ "FIBSEC", "FREEMODE", "MARSTON", "NIKO", "SHOPKEEP", "ARMOURED", "NONE", "NONE", "NONE", "NONE" },
	{ "NONE", "FEMBARBER", "MAID", "SHOP_HIGH", "SWEATSHOP", "AIRHOSTESS", "BARTENDER", "BAYWATCH", "COP", "FACTORY" },
	{ "HOOKER", "HOOKER", "HOOKER", "MIGRANT", "MOVPREM", "RANGER", "SCRUBS", "SHERIFF", "SHOP_LOW", "SHOP_MID" },
	{ "STRIPPERLITE", "STRIPPER", "STRIPPER", "SWEATSHOP", "AMMUCOUNTRY", "ARMOURED", "ARMOURED", "AUTOSHOP", "AUTOSHOP", "BOUNCER" },
	{ "CHEMSEC", "CIASEC", "CNTRYBAR", "DOCKWORK", "DOCTOR", "FIBOFFICE", "FIBOFFICE", "GAFFER", "GARDENER", "GENTRANSPORT" },
	{ "HAIRDRESS", "HIGHSEC", "HIGHSEC", "JANITOR", "LATHANDY", "LIFEINVAD", "LINECOOK", "LSMETRO", "MARIACHI", "MARINE" },
	{ "MARINE", "MIGRANT", "ZOMBIE", "MOVPREM", "MOVSPACE", "PARAMEDIC", "PILOT", "PILOT", "POSTAL", "POSTAL" },
	{ "PRISGUARD", "SCIENTIST", "SECURITY", "SNOWCOP", "STRPERF", "STRPREACH", "STRVEND", "TRUCKER", "UPS", "UPS" },
	{ "BUSKER", "AIRWORKER", "AMMUCITY", "ARMYMECH", "AUTOPSY", "BARMAN", "BAYWATCH", "BLACKOPS", "BLACKOPS", "BUSBOY" },
	{ "CHEF", "CLOWN", "CONSTRUCT", "CONSTRUCT", "COP", "DEALER", "DEVINSEC", "DOCKWORK", "DOORMAN", "DWSERVICE" },
	{ "DWSERVICE", "FACTORY", "FIREMAN", "GARBAGE", "GRIP", "HWAYCOP", "MARINE", "MARINE", "MARINE", "MIME" },
	{ "PESTCONT", "PILOT", "PRISMUSCL", "PRISONER", "RANGER", "ROBBER", "SHERIFF", "SHOP_MASK", "STRVEND", "SWAT" },
	{ "USCG", "VALET", "WAITER", "WINCLEAN", "XMECH", "XMECH", "CORPSE", "MIRANDA", "PROMOURN", "MOVIESTAR" },
	{ "PROLHOST", "BIKERCHIC", "COMJANE", "CORPSE", "CORPSE", "HOTPOSH", "JEWELASS", "MISTRESS", "POPPYMICH", "PRINCESS" },
	{ "SPYACTRESS", "ALDINAPOLI", "BANKMAN", "BIKEHIRE", "FIBARCHITECT", "FILMDIRECTOR", "GLENSTANK", "GRIFF", "JESUS", "JEWELSEC" },
	{ "JEWELTHIEF", "MARKFOST", "PARTYTARGET", "PROLSEC", "PROMOURN", "RIVALPAP", "SPYACTOR", "WILLYFIST", "FINGURU", "TAPHILLBILLY" },
	{ "TRAMP", "ABNER", "ANTONB", "BABYD", "BAYGOR", "BURGERDRUG", "CHIP", "CYCLIST", "FIBMUGGER", "GUIDO" },
	{ "GUNVEND", "HIPPIE", "IMPORAGE", "JUSTIN", "MANI", "MILITARYBUM", "PAPARAZZI", "PARTY", "POGO", "PRISONER" }
};

static LPCSTR vehicleModels[35][10] = {
	{ "NINEF", "NINEF2", "BLISTA", "ASEA", "ASEA2", "BOATTRAILER", "BUS", "ARMYTANKER", "ARMYTRAILER", "ARMYTRAILER2" },
	{ "SUNTRAP", "COACH", "AIRBUS", "ASTEROPE", "AIRTUG", "AMBULANCE", "BARRACKS", "BARRACKS2", "BALLER", "BALLER2" },
	{ "BJXL", "BANSHEE", "BENSON", "BFINJECTION", "BIFF", "BLAZER", "BLAZER2", "BLAZER3", "BISON", "BISON2" },
	{ "BISON3", "BOXVILLE", "BOXVILLE2", "BOXVILLE3", "BOBCATXL", "BODHI2", "BUCCANEER", "BUFFALO", "BUFFALO2", "BULLDOZER" },
	{ "BULLET", "BLIMP", "BURRITO", "BURRITO2", "BURRITO3", "BURRITO4", "BURRITO5", "CAVALCADE", "CAVALCADE2", "POLICET" },
	{ "GBURRITO", "CABLECAR", "CADDY", "CADDY2", "CAMPER", "CARBONIZZARE", "CHEETAH", "COMET2", "COGCABRIO", "COQUETTE" },
	{ "CUTTER", "GRESLEY", "DILETTANTE", "DILETTANTE2", "DUNE", "DUNE2", "HOTKNIFE", "DLOADER", "DUBSTA", "DUBSTA2" },
	{ "DUMP", "RUBBLE", "DOCKTUG", "DOMINATOR", "EMPEROR", "EMPEROR2", "EMPEROR3", "ENTITYXF", "EXEMPLAR", "ELEGY2" },
	{ "F620", "FBI", "FBI2", "FELON", "FELON2", "FELTZER2", "FIRETRUK", "FLATBED", "FORKLIFT", "FQ2" },
	{ "FUSILADE", "FUGITIVE", "FUTO", "GRANGER", "GAUNTLET", "HABANERO", "HAULER", "HANDLER", "INFERNUS", "INGOT" },
	{ "INTRUDER", "ISSI2", "JACKAL", "JOURNEY", "JB700", "KHAMELION", "LANDSTALKER", "LGUARD", "MANANA", "MESA" },
	{ "MESA2", "MESA3", "CRUSADER", "MINIVAN", "MIXER", "MIXER2", "MONROE", "MOWER", "MULE", "MULE2" },
	{ "ORACLE", "ORACLE2", "PACKER", "PATRIOT", "PBUS", "PENUMBRA", "PEYOTE", "PHANTOM", "PHOENIX", "PICADOR" },
	{ "POUNDER", "POLICE", "POLICE4", "POLICE2", "POLICE3", "POLICEOLD1", "POLICEOLD2", "PONY", "PONY2", "PRAIRIE" },
	{ "PRANGER", "PREMIER", "PRIMO", "PROPTRAILER", "RANCHERXL", "RANCHERXL2", "RAPIDGT", "RAPIDGT2", "RADI", "RATLOADER" },
	{ "REBEL", "REGINA", "REBEL2", "RENTALBUS", "RUINER", "RUMPO", "RUMPO2", "RHINO", "RIOT", "RIPLEY" },
	{ "ROCOTO", "ROMERO", "SABREGT", "SADLER", "SADLER2", "SANDKING", "SANDKING2", "SCHAFTER2", "SCHWARZER", "SCRAP" },
	{ "SEMINOLE", "SENTINEL", "SENTINEL2", "ZION", "ZION2", "SERRANO", "SHERIFF", "SHERIFF2", "SPEEDO", "SPEEDO2" },
	{ "STANIER", "STINGER", "STINGERGT", "STOCKADE", "STOCKADE3", "STRATUM", "SULTAN", "SUPERD", "SURANO", "SURFER" },
	{ "SURFER2", "SURGE", "TACO", "TAILGATER", "TAXI", "TRASH", "TRACTOR", "TRACTOR2", "TRACTOR3", "GRAINTRAILER" },
	{ "BALETRAILER", "TIPTRUCK", "TIPTRUCK2", "TORNADO", "TORNADO2", "TORNADO3", "TORNADO4", "TOURBUS", "TOWTRUCK", "TOWTRUCK2" },
	{ "UTILLITRUCK", "UTILLITRUCK2", "UTILLITRUCK3", "VOODOO2", "WASHINGTON", "STRETCH", "YOUGA", "ZTYPE", "SANCHEZ", "SANCHEZ2" },
	{ "SCORCHER", "TRIBIKE", "TRIBIKE2", "TRIBIKE3", "FIXTER", "CRUISER", "BMX", "POLICEB", "AKUMA", "CARBONRS" },
	{ "BAGGER", "BATI", "BATI2", "RUFFIAN", "DAEMON", "DOUBLE", "PCJ", "VADER", "VIGERO", "FAGGIO2" },
	{ "HEXER", "ANNIHILATOR", "BUZZARD", "BUZZARD2", "CARGOBOB", "CARGOBOB2", "CARGOBOB3", "SKYLIFT", "POLMAV", "MAVERICK" },
	{ "NEMESIS", "FROGGER", "FROGGER2", "CUBAN800", "DUSTER", "STUNT", "MAMMATUS", "JET", "SHAMAL", "LUXOR" },
	{ "TITAN", "LAZER", "CARGOPLANE", "SQUALO", "MARQUIS", "DINGHY", "DINGHY2", "JETMAX", "PREDATOR", "TROPIC" },
	{ "SEASHARK", "SEASHARK2", "SUBMERSIBLE", "TRAILERS", "TRAILERS2", "TRAILERS3", "TVTRAILER", "RAKETRAILER", "TANKER", "TRAILERLOGS" },
	{ "TR2", "TR3", "TR4", "TRFLAT", "TRAILERSMALL", "VELUM", "ADDER", "VOLTIC", "VACCA", "BIFTA" },
	{ "SPEEDER", "PARADISE", "KALAHARI", "JESTER", "TURISMOR", "VESTRA", "ALPHA", "HUNTLEY", "THRUST", "MASSACRO" },
	{ "MASSACRO2", "ZENTORNO", "BLADE", "GLENDALE", "PANTO", "PIGALLE", "WARRENER", "RHAPSODY", "DUBSTA3", "MONSTER" },
	{ "SOVEREIGN", "INNOVATION", "HAKUCHOU", "FUROREGT", "MILJET", "COQUETTE2", "BTYPE", "BUFFALO3", "DOMINATOR2", "GAUNTLET2" },
	{ "MARSHALL", "DUKES", "DUKES2", "STALION", "STALION2", "BLISTA2", "BLISTA3", "DODO", "SUBMERSIBLE2", "HYDRA" },
	{ "INSURGENT", "INSURGENT2", "TECHNICAL", "SAVAGE", "VALKYRIE", "KURUMA", "KURUMA2", "JESTER2", "CASCO", "VELUM2" },
	{ "GUARDIAN", "ENDURO", "LECTRO", "SLAMVAN", "SLAMVAN2", "RATLOADER2", "", "", "", "" }
};

static LPCSTR weaponOnlineNames[] = {
	"WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_SNSPISTOL", "WEAPON_HEAVYPISTOL", "WEAPON_VINTAGEPISTOL", "WEAPON_FLAREGUN",
	"WEAPON_MICROSMG", "WEAPON_SMG", "WEAPON_ASSAULTSMG",
	"WEAPON_MG", "WEAPON_COMBATMG",
	"WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_SPECIALCARBINE", "WEAPON_BULLPUPRIFLE",
	"WEAPON_SNIPERRIFLE", "WEAPON_HEAVYSNIPER", "WEAPON_MARKSMANRIFLE",
	"WEAPON_KNIFE", "WEAPON_NIGHTSTICK", "WEAPON_HAMMER", "WEAPON_BAT", "WEAPON_GOLFCLUB", "WEAPON_CROWBAR", "WEAPON_DAGGER", "WEAPON_HATCHET",
	"WEAPON_PUMPSHOTGUN", "WEAPON_SAWNOFFSHOTGUN", "WEAPON_ASSAULTSHOTGUN", "WEAPON_BULLPUPSHOTGUN", "WEAPON_HEAVYSHOTGUN",
	"WEAPON_GRENADELAUNCHER", "WEAPON_RPG", "WEAPON_MINIGUN", "WEAPON_HOMINGLAUNCHER",
	"WEAPON_GRENADE", "WEAPON_STICKYBOMB", "WEAPON_SMOKEGRENADE", "WEAPON_MOLOTOV", "WEAPON_PETROLCAN", "WEAPON_PROXMINE"
};

static LPCSTR weaponRestrictedNames[] = {
	"WEAPON_STUNGUN",
	"WEAPON_BZGAS", "WEAPON_SNOWBALL", "WEAPON_FIREEXTINGUISHER",
	"WEAPON_MUSKET", "WEAPON_GUSENBERG",
	"WEAPON_RAILGUN", "WEAPON_FIREWORK",
	"WEAPON_HANDCUFFS"
};

void give_weapons_set_to_ped(Ped playerPed, LPCSTR weaponSet[], int arrayByteSize, int ammoSize = 1000) {

	int weaponSetSize = arrayByteSize / sizeof(LPCSTR);
	for (int i = 0; i < weaponSetSize; i++)
		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(playerPed, GAMEPLAY::GET_HASH_KEY((char *)weaponSet[i]), ammoSize, 0);
}
void teleport_to_nearest_vehicle(){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vector3 coord = ENTITY::GET_ENTITY_COORDS(playerPed, true);
	
	int VehicleHandle = VEHICLE::GET_CLOSEST_VEHICLE(coord.x, coord.y, coord.z, 100.0, 0, 71);
	PED::SET_PED_INTO_VEHICLE(playerPed, VehicleHandle, -1);
};

// Remove this after use
bool debug_ped_in_veh = false;

void change_player_model(Ped playerPed, Hash model, bool bRestore = false, bool bGiveWeapon = true){
	Ped playerPed_new;
	int isInVehicle = PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0);
	
	Vehicle drivingVeh;
	if (isInVehicle)
		drivingVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	
	// Check for validity
	if (bRestore ||	// Skip validation if restoration is used.
		(STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))) {

		// Change model
		STREAMING::REQUEST_MODEL(model);
		while (!STREAMING::HAS_MODEL_LOADED(model))
			WAIT(0);
		PLAYER::SET_PLAYER_MODEL(playerPed, model);

		playerPed_new = PLAYER::PLAYER_PED_ID();

		PED::SET_PED_DEFAULT_COMPONENT_VARIATION(playerPed_new);

		if (!bRestore) { // Randomise ped component
			WAIT(0);
			for (int i = 0; i < 12; i++) {
				for (int j = 0; j < 100; j++) {
					int drawable = rand() % 10;
					int texture = rand() % 10;
					if (PED::IS_PED_COMPONENT_VARIATION_VALID(playerPed_new, i, drawable, texture)) {
						PED::SET_PED_COMPONENT_VARIATION(playerPed_new, i, drawable, texture, 0);
						break;
					}
				}
			}
			WAIT(100);
		}
		else {
			if (isInVehicle) {
				WAIT(1500);
				PED::SET_PED_INTO_VEHICLE(playerPed_new, drivingVeh, -1);
				teleport_to_nearest_vehicle();
			}
		}
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
		
		if (bGiveWeapon)
			give_weapons_set_to_ped(playerPed_new, weaponOnlineNames, sizeof(weaponOnlineNames), 6000);
	}

}
void change_player_model(Ped playerPed, char *modelName, bool bRestore = false) {
	Hash model = GAMEPLAY::GET_HASH_KEY(modelName);
	change_player_model(playerPed, model, bRestore);
}

void player_dead_check() {
	// common variables
	//Player player = PLAYER::PLAYER_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID())) return;

	if (ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), true)) {

		Hash model_pre = ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID());
		display_message_notify("Previous model loaded");
		if (!NETWORK::NETWORK_IS_IN_SESSION()) { // Singleplayer
			
			bool bNeedToRestoreSkin = true;
			for (int i = 0; i < 3; i++) {
				if (GAMEPLAY::GET_HASH_KEY((char *)defaultModels[i]) == model_pre) {
					bNeedToRestoreSkin = false;
					break;
				}
			}
			if (bNeedToRestoreSkin)	{
				WAIT(500);
				change_player_model(PLAYER::PLAYER_PED_ID(), "player_zero", true);
				ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), false);

				// wait until player is ressurected
				while (CAM::IS_GAMEPLAY_CAM_RENDERING())
					WAIT(0); //Dying screen

				while (!CAM::IS_GAMEPLAY_CAM_RENDERING())
					WAIT(0); //Resurrecting
			}
		}
		else // Multiplayer
			WAIT(5000);

		// Change back
		change_player_model(PLAYER::PLAYER_PED_ID(), model_pre);
		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), !featurePlayerInvisible);
	}
}

/* TODO
1. Fix weapon
2. Figure out deadtime
3. Add collision toggle
4. Add more trigger

*/

void update_vehicle_guns()
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Ped playerGroup = PED::GET_PED_GROUP_INDEX(PLAYER::PLAYER_PED_ID());

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed) || !featureWeaponVehRockets) return;

	bool bSelect = get_key_pressed(0x6B); // num plus
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
				WAIT(0);
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
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

bool skinchanger_used = false;

// Updates all features that can be turned off by the game, being called each game frame
void update_features()
{
	update_status_text();

	update_vehicle_guns();

	// changing player model if died while being an animal, since it can cause inf loading loop
	if (skinchanger_used)
		player_dead_check();

	// read default feature values from the game
	featureWorldRandomCops = PED::CAN_CREATE_RANDOM_COPS() == TRUE;

	// common variables
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(playerPed);

	// player invincible
	if (featurePlayerInvincibleUpdated)
	{
		if (bPlayerExists && !featurePlayerInvincible)
			PLAYER::SET_PLAYER_INVINCIBLE(player, FALSE);
		featurePlayerInvincibleUpdated = false;
	}
	if (featurePlayerInvincible)
	{
		if (bPlayerExists)
			PLAYER::SET_PLAYER_INVINCIBLE(player, TRUE);
	}

	// player never wanted
	if (featurePlayerNeverWanted)
	{
		if (bPlayerExists)
			PLAYER::CLEAR_PLAYER_WANTED_LEVEL(player);
	}

	// police ignore player
	if (featurePlayerIgnoredUpdated)
	{
		if (bPlayerExists)
			PLAYER::SET_POLICE_IGNORE_PLAYER(player, featurePlayerIgnored);
		featurePlayerIgnoredUpdated = false;
	}

	// player special ability
	if (featurePlayerUnlimitedAbility)
	{
		if (bPlayerExists)
			PLAYER::_RECHARGE_SPECIAL_ABILITY(player, 1);
	}

	// player no noise
	if (featurePlayerNoNoiseUpdated)
	{
		if (bPlayerExists && !featurePlayerNoNoise)
			PLAYER::SET_PLAYER_NOISE_MULTIPLIER(player, 1.0);
		featurePlayerNoNoiseUpdated = false;
	}
	if (featurePlayerNoNoise)
		PLAYER::SET_PLAYER_NOISE_MULTIPLIER(player, 0.0);

	// player fast swim
	if (featurePlayerFastSwimUpdated)
	{
		if (bPlayerExists && !featurePlayerFastSwim)
			PLAYER::_SET_SWIM_SPEED_MULTIPLIER(player, 1.0);
		featurePlayerFastSwimUpdated = false;
	}
	if (featurePlayerFastSwim)
		PLAYER::_SET_SWIM_SPEED_MULTIPLIER(player, 1.49);

	// player fast run
	if (featurePlayerFastRunUpdated)
	{
		if (bPlayerExists && !featurePlayerFastRun)
			PLAYER::_SET_MOVE_SPEED_MULTIPLIER(player, 1.0);
		featurePlayerFastRunUpdated = false;
	}
	if (featurePlayerFastRun)
		PLAYER::_SET_MOVE_SPEED_MULTIPLIER(player, 1.49);

	// player super jump
	if (featurePlayerSuperJump)
	{
		if (bPlayerExists)
			GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(player);
	}

	// weapon
	if (featureWeaponFireAmmo)
	{
		if (bPlayerExists)
			GAMEPLAY::SET_FIRE_AMMO_THIS_FRAME(player);
	}
	if (featureWeaponOneHit)
	{
		if (bPlayerExists)
		{
			PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(player, 999999);
		}
	}
	if (featureWeaponExplosiveAmmo)
	{
		if (bPlayerExists)
			GAMEPLAY::SET_EXPLOSIVE_AMMO_THIS_FRAME(player);
	}
	if (featureWeaponExplosiveMelee)
	{
		if (bPlayerExists)
			GAMEPLAY::SET_EXPLOSIVE_MELEE_THIS_FRAME(player);
	}

	if (featurePlayerInvisible && bPlayerExists)
	{
		ENTITY::SET_ENTITY_VISIBLE(playerPed, false);
	}
	else
	{
		ENTITY::SET_ENTITY_VISIBLE(playerPed, true);
	}

	// weapon no reload
	if (bPlayerExists && featureWeaponNoReload)
	{
		Hash cur;
		if (WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &cur, 1))
		{
			if (WEAPON::IS_WEAPON_VALID(cur))
			{
				int maxAmmo;
				if (WEAPON::GET_MAX_AMMO(playerPed, cur, &maxAmmo))
				{
					WEAPON::SET_PED_AMMO(playerPed, cur, maxAmmo);

					maxAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, cur, 1);
					if (maxAmmo > 0)
						WEAPON::SET_AMMO_IN_CLIP(playerPed, cur, maxAmmo);
				}
			}
		}
	}

	// player's vehicle invincible
	if (featureVehInvincibleUpdated)
	{
		if (bPlayerExists && !featureVehInvincible && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			ENTITY::SET_ENTITY_INVINCIBLE(veh, FALSE);
			ENTITY::SET_ENTITY_PROOFS(veh, 0, 0, 0, 0, 0, 0, 0, 0);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, 1);
			VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, 1);
			VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, 1);
		}
		featureVehInvincibleUpdated = false;
	}
	if (featureVehInvincible)
	{
		if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			ENTITY::SET_ENTITY_INVINCIBLE(veh, TRUE);
			ENTITY::SET_ENTITY_PROOFS(veh, 1, 1, 1, 1, 1, 1, 1, 1);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, 0);
			VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, 0);
			VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, 0);
		}
	}

	// player's vehicle boost
	if (featureVehSpeedBoost && bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		DWORD model = ENTITY::GET_ENTITY_MODEL(veh);

		bool bUp = get_key_pressed(VK_NUMPAD9);
		bool bDown = get_key_pressed(VK_NUMPAD3);

		if (bUp || bDown)
		{
			float speed = ENTITY::GET_ENTITY_SPEED(veh);
			if (bUp)
			{
				speed += speed * 0.05f;
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, speed);
			}
			else
				if (ENTITY::IS_ENTITY_IN_AIR(veh) || speed > 5.0)
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 0.0);
		}
	}

	// time pause
	if (featureTimePausedUpdated)
	{
		TIME::PAUSE_CLOCK(featureTimePaused);
		featureTimePausedUpdated = false;
	}

	// time sync
	if (featureTimeSynced)
	{
		time_t now = time(0);
		tm t;
		localtime_s(&t, &now);
		TIME::SET_CLOCK_TIME(t.tm_hour, t.tm_min, t.tm_sec);
	}

	// hide hud
	if (featureMiscHideHud)
		UI::HIDE_HUD_AND_RADAR_THIS_FRAME();

	if (featureVehSlide)
	{
		VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
	}
	else
	{
		VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
	}

	if (featureVehRainbow)
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		DWORD model = ENTITY::GET_ENTITY_MODEL(veh);

		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0) && rainbowCount <= 0)
		{
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, rand() % 255, rand() % 255, rand() % 255);
			rainbowCount = 15;
		}
		else
			rainbowCount--;
	}

	if (featureVehStickyCar)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
		{
			int myVehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(myVehicle);
		}
	}


}

std::string line_as_str(std::string text, bool *pState)
{
	while (text.size() < 18) text += " ";
	return text + (pState ? (*pState ? ": ON" : ": OFF") : "");
}

/*****************************************************

	Code modification by amoshydra

******************************************************/

// Menu: Array of struct containing lines of string.
struct menuList{
	LPCSTR text;
};

// Menu: Array of struct containing lines of string with boolean value.
struct menuList_boolean{
	LPCSTR text;
	bool *pState;
	bool *pUpdated;
};

// Menu: Array of struct containing lines of string with xyz values.
struct menuList_coord{
	LPCSTR text;
	float x;
	float y;
	float z;
};

// Menu: Array of struct containing lines of string and 2 character array fields.
struct menuList_strings{
	LPCSTR text;
	char* string1;
	char* string2;
};

// To draw the trainer menu consisting boolean elements
void menu_list_draw(menuList_boolean menu_lines[], int lineCount, std::string caption, int active_line, DWORD *ptr_waitTime, bool bNavigation = true, float lineHeight = 9.0, float lineWidth = 250) {

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
					lineWidth, lineHeight, 60.0 + i * 36, 1000.0, 7.0, false, false);
			}
		}

		// Active Line
		draw_menu_line(line_as_str(menu_lines[active_line].text, menu_lines[active_line].pState),
			lineWidth, lineHeight, 60.0 + active_line * 36, 1000.0, 7.0, true, false);

		update_features();
		WAIT(0);
	} while (GetTickCount() < maxTickCount);

	// Reset waitTime
	*ptr_waitTime = 0;
}

// To draw the trainer menu with string output only
template <typename T>
void menu_list_draw(T menu_lines[], int lineCount, std::string caption, int active_line, DWORD *ptr_waitTime, bool bNavigation = true, float lineHeight = 9.0, float lineWidth = 250) {

	// timed menu draw, used for pause after active line switch
	DWORD waitTime = *ptr_waitTime;
	DWORD maxTickCount = GetTickCount() + waitTime;

	do {
		// Header
		draw_menu_line(caption, lineWidth, 13.0, 18.0, 1000.0, 3.0, false, true);

		// Menu List
		for (int i = 0; i < lineCount; i++) {
			if (i != active_line || !bNavigation) {
				draw_menu_line(menu_lines[i].text, lineWidth, lineHeight, 60.0 + i * 36.0, 1000.0, 7.0, false, false);
			}
		}

		// Active Line
		if (bNavigation)
			draw_menu_line(menu_lines[active_line].text, lineWidth, lineHeight, 60.0 + active_line * 36, 1000.0, 7.0, true, false);

		update_features();
		WAIT(0);
	} while (GetTickCount() < maxTickCount);

	// Reset waitTime
	*ptr_waitTime = 0;
}

// Menu navigation with up, down, select and back
// Back with -1, Select with 1, else 0
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
		*waitTime = 150;
	}
	if (bDown) {
		play_sound("NAV_UP_DOWN");
		line_location++;
		if (line_location == line_count)
			line_location = 0;
		*waitTime = 150;
	}

	if (bSelect) {
		play_sound("SELECT");
		*waitTime = 200;
		return 1;
	}
	*active_line = line_location;
	return 0;
}

// Menu navigation with back button only.
// Back with -1, else 0
int menu_list_navigate(DWORD *waitTime) {
	bool bSelect, bBack, bUp, bDown;
	get_button_state(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);

	if (bBack || trainer_switch_pressed()) {
		play_sound("BACK");
		return -1;
	}
	return 0;
}

// To update boolean of a menu line
void menu_list_feature_toggle(menuList_boolean lines[], int active_line) {
	if (lines[active_line].pState)
		*lines[active_line].pState = !(*lines[active_line].pState);
	if (lines[active_line].pUpdated)
		*lines[active_line].pUpdated = true;
}

// Animation Codes
char AnimDict_LastPlayed[100], AnimID_LastPlayed[70];

// Execute an animation given its dictionary name and clip name
void Animation_Start(char* AnimDict, char* AnimID, bool bHasNext = false, int duration = -1, int lastframe = 9) {
	//duration set to -1 for infinite loop
	int playerPed = PLAYER::PLAYER_PED_ID();
	
	// 1. Load dictionary
	if (!STREAMING::HAS_ANIM_DICT_LOADED(AnimDict))
		STREAMING::REQUEST_ANIM_DICT(AnimDict);

	// 2. Wait until dictionary is loaded
	int counter = 800;
	while (!STREAMING::HAS_ANIM_DICT_LOADED(AnimDict) && (counter > 0)) {
		counter--;
		WAIT(1);
	}

	// 3. Remember current animation
	strcpy(AnimDict_LastPlayed, AnimDict);
	strcpy(AnimID_LastPlayed, AnimID);

	// 4. Play animation
	if (STREAMING::HAS_ANIM_DICT_LOADED(AnimDict)) {
		AI::TASK_PLAY_ANIM(playerPed, AnimDict, AnimID, 8.0f, 0.0f, duration, lastframe, 0, 0, 0, 0);
		
		if (bHasNext) {
			while (ENTITY::GET_ENTITY_ANIM_CURRENT_TIME(playerPed, AnimDict, AnimID) < 0.90)
				WAIT(0);
		}
	}
	else
		display_message_caption("Error loading animation. Try again");
}
// Execute an animation given its dictionary name and clip name with string to char* conversion
void Animation_Start(std::string AnimDict, std::string AnimID, bool bHasNext = false, int duration = -1, int lastframe = 9) {
	char char_AnimDict[100];
	strncpy(char_AnimDict, AnimDict.c_str(), sizeof(char_AnimDict));
	char_AnimDict[sizeof(char_AnimDict) - 1] = 0;

	char char_AnimID[70];
	strncpy(char_AnimID, AnimID.c_str(), sizeof(char_AnimID));
	char_AnimID[sizeof(char_AnimID) - 1] = 0;

	Animation_Start(char_AnimDict, char_AnimID, bHasNext, duration, lastframe);
};
// Stop an animation using previously called animation;
void Animation_Stop(Ped playerPed = PLAYER::PLAYER_PED_ID(), char* AnimDict = AnimDict_LastPlayed, char* AnimID = AnimID_LastPlayed) {
	display_message_notify(AnimDict);
	display_message_notify(AnimID);
	
	if (ENTITY::IS_ENTITY_PLAYING_ANIM(playerPed, AnimDict, AnimID, 1))
		ENTITY::STOP_ENTITY_ANIM(playerPed, AnimID, AnimDict, 1);
	else {
		AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
		display_message_caption("Failed to properly stop animation.");
	}
};

/********************************
	Beginning of 
	menu list in reverse order
*********************************/

std::string gender = "male";

int active_home_animation_exercises = 0;
void menu_home_animation_exercises__action(int *ptr_active_line) {

	int active_line = *ptr_active_line;

	switch (active_line) {
	case 0:
		Animation_Stop();
		break;
	case 1:
		Animation_Start(
			"amb@world_human_push_ups@male@enter",
			"enter",
			true
			);
		Animation_Start(
			"amb@world_human_push_ups@male@base",
			"base"
			); break;
	case 2:
		Animation_Start(
			"amb@world_human_sit_ups@male@enter",
			"enter",
			true
			);
		Animation_Start(
			"amb@world_human_sit_ups@male@base",
			"base"
			); break;
	case 3:
		Animation_Start(
			"amb@world_human_jog_standing@" + gender + "@base",
			"base"
			); break;
	case 4:
		Animation_Start(
			"amb@world_human_jog@" + gender + "@base",
			"base"
			); break;
	case 5:
		Animation_Start(
			"amb@world_human_yoga@" + gender + "@base",
			"base_a"
			); break;
	case 6:
		Animation_Start(
			"amb@world_human_yoga@" + gender + "@base",
			"base_b"
			); break;
	case 7:
		Animation_Start(
			"amb@world_human_yoga@female@base",
			"base_c"
			); break;
	case 8:
		Animation_Start(
			"amb@prop_human_muscle_chin_ups@male@enter",
			"enter",
			true
			);		
		Animation_Start(
			"amb@prop_human_muscle_chin_ups@male@base",
			"base"
			); break;
	}
}
void menu_home_animation_exercises__display(std::string caption) {

	// Menu Labels
	const int LINE_COUNT = 9;
	menuList menu_home_animation_exercises[LINE_COUNT] = {
		/* 0 */{ "Stop" },
		/* 1 */{ "Push up" },
		/* 2 */{ "Sit up" },
		/* 3 */{ "Jog (Warming)" },
		/* 4 */{ "Jog" },
		/* 5 */{ "Yoga 1" },
		/* 6 */{ "Yoga 2" },
		/* 7 */{ "Yoga 3" },
		/* 8 */{ "Chin up (Prop)" }
	};

	menuList *current_menu = menu_home_animation_exercises;
	int *current_line = &active_home_animation_exercises;

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
			menu_home_animation_exercises__action(current_line);
		}
	}
}

int active_home_animation_dances = 0;
void menu_home_animation_dances__action(int *ptr_active_line) {

	int active_line = *ptr_active_line;

	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

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
		Animation_Start(
			"misschinese1crazydance",
			"crazy_dance_3"
			); break;
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

	}
}
void menu_home_animation_dances__display(std::string caption) {

	// Menu Labels
	const int LINE_COUNT = 10;
	menuList menu_home_animation_dances[LINE_COUNT] = {
		/*  0 */{ "Stop" },
		/*  1 */{ "Private dance 1" },
		/*  2 */{ "Private dance 2" },
		/*  3 */{ "Private dance 3" },
		/*  4 */{ "Lap dance" },
		/*  5 */{ "Crazy dance" },
		/*  6 */{ "Mountain dance" },
		/*  7 */{ "Angel dance" },
		/*  8 */{ "Buttwag" },
		/*  9 */{ "Verse" }
	};

	menuList *current_menu = menu_home_animation_dances;
	int *current_line = &active_home_animation_dances;

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
			menu_home_animation_dances__action(current_line);
		}
	}
}

int active_home_animation = 0;
void menu_home_animation__action(int *ptr_active_line) {

	int active_line = *ptr_active_line;

	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	switch (active_line) {
		case 0:
			Animation_Stop();
			break;
		case 1:
			menu_home_animation_dances__display("Dances");
			break;
		case 2:
			Animation_Start(
				"rcmcollect_paperleadinout@",
				"meditiate_idle"
				);
			break;
		case 3:
			Animation_Start(
				"switch@trevor@jerking_off",
				"trev_jerking_off_loop"
				);
			break;
		case 4:
			Animation_Start(
				"amb@world_human_sunbathe@" + gender + "@front@enter",
				"enter",
				true
				);
			Animation_Start(
				"amb@world_human_sunbathe@" + gender + "@front@base",
				"base"
				);
			break;
		case 5:
			Animation_Start(
				"amb@world_human_sunbathe@" + gender + "@back@enter",
				"enter",
				true
				);
			Animation_Start(
				"amb@world_human_sunbathe@" + gender + "@back@base",
				"base"
				);
			break;
		case 6:
			Animation_Start(
				"timetable@mime@ig_1",
				"cowboy_riding_horse"
				);
			break;
		case 7:
			menu_home_animation_exercises__display("Exercises");
			break;
		default:
			if (!gender.compare("male")) //If gender equals male
				gender = "female";
			else
				gender = "male";
	}
}
void menu_home_animation__display(std::string caption) {

	// Menu Labels
	const int LINE_COUNT = 9;
	menuList menu_home_animation[LINE_COUNT] = {
		/* 0 */{ "Stop" },
		/* 1 */{ "Dances:" },
		/* 2 */{ "Meditate" },
		/* 3 */{ "Fap" },
		/* 4 */{ "Sunbath Front" },
		/* 5 */{ "Sunbath Back" },
		/* 6 */{ "Mimes:" },
		/* 7 */{ "Exercises:" },
		/* 8 */{ "Switch gender" }
	};

	menuList *current_menu = menu_home_animation;
	int *current_line = &active_home_animation;

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
			menu_home_animation__action(current_line);
		}
	}
}

int active_home_misc_credits = 0;
void menu_home_misc_credits__display(std::string caption)
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

int active_home_misc_debug = 0;

bool debug_collision_control_x = true;

char debug_anim_dictionary[] = "amb@world_human_yoga@female@base";
char debug_anim_clip[] = "base_b";

void menu_home_misc_debug__action(menuList_boolean menu_lines[], int *ptr_active_line){

	int active_line = *ptr_active_line;

	// common variable
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::string status;

	switch (active_line) {
		case 0:
			status = "Entity exist: " + std::to_string(ENTITY::DOES_ENTITY_EXIST(playerPed)) + "\n" +
				"Waiting: " + std::to_string(ENTITY::IS_ENTITY_WAITING_FOR_WORLD_COLLISION(playerPed)) + "\n" +
				"Health: " + std::to_string(ENTITY::GET_ENTITY_HEALTH(playerPed)) + "\n" +
				"Player ID: " + std::to_string(PLAYER::PLAYER_PED_ID());
			break;
		case 1:
			status = "Free to ambient: " + std::to_string(PLAYER::IS_PLAYER_FREE_FOR_AMBIENT_TASK(playerPed));
			break;
		case 2:
			status = "Is in session: " + std::to_string(NETWORK::NETWORK_IS_IN_SESSION()) + "\n" +
				"Is activity session: " + std::to_string(NETWORK::NETWORK_IS_ACTIVITY_SESSION());
			break;
		case 3:
			status = "Vehicle ped in: " + std::to_string(PED::GET_VEHICLE_PED_IS_IN(playerPed, 0)) + "\n" +
				"Vehicle ped using: " + std::to_string(PED::GET_VEHICLE_PED_IS_USING(playerPed)) + "\n" +
				"Is in any vehicle: " + std::to_string(PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) + "\n" +
				"Is in vehicle: " + std::to_string(PED::IS_PED_IN_VEHICLE(playerPed, PED::GET_VEHICLE_PED_IS_IN(playerPed, 0), 0)) + "\n" +
				"PED in seat -1: " + std::to_string(PED::IS_PED_SITTING_IN_ANY_VEHICLE(playerPed)) + "\n" +
				"PED in seat 0: " + std::to_string(VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_IN(playerPed, 0), 0)) + "\n" +
				"PED in seat 1: " + std::to_string(VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_IN(playerPed, 0), 1)) + "\n" +
				"PED in seat 2: " + std::to_string(VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_IN(playerPed, 0), 2)) + "\n" +
				"PED in seat 3: " + std::to_string(VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_IN(playerPed, 0), 3));		
			break;
		case 4:
			teleport_to_nearest_vehicle();
			break;
		case 5:
			debug_ped_in_veh = !debug_ped_in_veh;
			break;
		case 6:
			debug_collision_control_x = !debug_collision_control_x;
			ENTITY::SET_ENTITY_COLLISION(playerPed, debug_collision_control_x, debug_ped_in_veh);
			break;
		case 7:			
			status = "Anim current time: " + std::to_string(ENTITY::GET_ENTITY_ANIM_CURRENT_TIME(playerPed, debug_anim_dictionary, debug_anim_clip)) + "\n" +
				"Anim total time: " + std::to_string(ENTITY::GET_ENTITY_ANIM_TOTAL_TIME(playerPed, debug_anim_dictionary, debug_anim_clip)) + "\n" +
				"Anim is playing: " + std::to_string(ENTITY::IS_ENTITY_PLAYING_ANIM(playerPed, debug_anim_dictionary, debug_anim_clip, 1));
			break;
		case 8:
			Animation_Start(debug_anim_dictionary, debug_anim_clip);
			break;
		case 9:
			ENTITY::STOP_ENTITY_ANIM(playerPed, debug_anim_clip, debug_anim_dictionary, 1);
			break;

		case 10:
			strcpy(debug_anim_dictionary, get_user_input("HUD_TARG", debug_anim_dictionary));
			WAIT(500);
			strcpy(debug_anim_clip, get_user_input("FMMC_MPM_NA", debug_anim_clip));
			break;
	}
	set_status_text(status, 7000UL);
}
void menu_home_misc_debug__display(std::string caption) {
	// Menu Labels
	const int LINE_COUNT = 11;
	menuList_boolean menu_home_misc_debug[LINE_COUNT] = {
		/*  0 */ { "All check", NULL, NULL },
		/*  1 */ { "Free for ambient", NULL, NULL },
		/*  2 */ { "Online Check", NULL, NULL },
		/*  3 */ { "Vehicle check", NULL, NULL },
		/*  4 */ { "Teleport to vehicle", NULL, NULL },
		/*  5 */ { "Toggle model veh", &debug_ped_in_veh, NULL },
		/*  6 */ { "Toggle collision", &debug_collision_control_x, NULL },
		/*  7 */ { "Debug animation", NULL, NULL },
		/*  8 */ { "Play animation", NULL, NULL },
		/*  9 */ { "Stop animation", NULL, NULL },
		/* 10 */ { "Input animation", NULL, NULL}
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


int active_home_misc_stats_unlocks = 0;
void menu_home_misc_stats_unlocks__action(int *ptr_active_line) {

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
void menu_home_misc_stats_unlocks__display(std::string caption) {

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

int active_home_misc_stats_level = 0;
void menu_home_misc_stats_level__action(int *ptr_active_line) {

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
		set_status_text("Rank is set");
	}
}
void menu_home_misc_stats_level__display(std::string caption) {

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
void menu_home_misc_stats__action(int *ptr_active_line){

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
void menu_home_misc_stats__display(std::string caption) {

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
void menu_home_misc__action(menuList_boolean menu_lines[], int *ptr_active_line){

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
		menu_home_misc_debug__display("Debug Options");
		break;
	case 4:
		menu_home_misc_credits__display("Kinky Version 2.1");
		break;
	}
}
void menu_home_misc__display(std::string caption)
{
	// Menu Labels
	const int LINE_COUNT = 5;
	menuList_boolean menu_home_misc[LINE_COUNT] = {
		/* 0 */{ "Mobile Radio", &featureMiscMobileRadio, NULL },
		/* 1 */{ "Next Radio Track", NULL, NULL },
		/* 2 */{ "Stats Edit", NULL, NULL },
		/* 3 */{ "Debug", NULL, NULL },
		/* 4 */{ "Credits", NULL, NULL }
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
void menu_home_weather__action(menuList_boolean menu_lines[], int *ptr_active_line){

	int active_line = *ptr_active_line;

	switch (active_line) {
		// wind
		case 0:
			featureWeatherWind = !featureWeatherWind;
			if (featureWeatherWind) {
				GAMEPLAY::SET_WIND(1.0);
				GAMEPLAY::SET_WIND_SPEED(11.99);
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
void menu_home_weather__display(std::string caption)
{
	// Menu Labels
	const int LINE_COUNT = 15;
	menuList_boolean menu_home_weather[LINE_COUNT] = {
		{ "WIND", &featureWeatherWind, NULL },
		{ "EXTRASUNNY", NULL, NULL },
		{ "CLEAR", NULL, NULL },
		{ "CLOUDS", NULL, NULL },
		{ "SMOG", NULL, NULL },
		{ "FOGGY", NULL, NULL },
		{ "OVERCAST", NULL, NULL },
		{ "RAIN", NULL, NULL },
		{ "THUNDER", NULL, NULL },
		{ "CLEARING", NULL, NULL },
		{ "NEUTRAL", NULL, NULL },
		{ "SNOW", NULL, NULL },
		{ "BLIZZARD", NULL, NULL },
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
void menu_home_time__action(menuList_boolean menu_lines[], int *ptr_active_line){

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
		set_status_text(text);
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
void menu_home_time__display(std::string caption)
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

int active_home_veh_carspawnLine = 0;
int active_home_veh_carspawnItem = 0;
void menu_home_veh_carspawn__display() {
	DWORD waitTime = 150;
	const int lineCount = 35;
	const int itemCount = 10;
	const int itemCountLastLine = 6;
	while (true)
	{
		// timed menu draw, used for pause after active line switch
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			char caption[32];
			sprintf_s(caption, "CAR SPAWNER   %d / %d", active_home_veh_carspawnLine + 1, lineCount);
			draw_menu_line(caption, 350.0, 15.0, 18.0, 0.0, 5.0, false, true);
			for (int i = 0; i < itemCount; i++)
				if (strlen(vehicleModels[active_home_veh_carspawnLine][i]))
					draw_menu_line(vehicleModels[active_home_veh_carspawnLine][i], 100.0, 5.0, 200.0, 100.0 + i * 110.0, 5.0, i == active_home_veh_carspawnItem, false, false);

			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			play_sound("SELECT");
			LPCSTR modelName = vehicleModels[active_home_veh_carspawnLine][active_home_veh_carspawnItem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char *)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVehWrapInSpawned)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);
			}
		}
		else
			if (bBack)
			{
				play_sound("BACK");
				break;
			}
			else
				if (bRight)
				{
					play_sound("NAV_LEFT_RIGHT");
					active_home_veh_carspawnItem++;
					int itemsMax = (active_home_veh_carspawnLine == (lineCount - 1)) ? itemCountLastLine : itemCount;
					if (active_home_veh_carspawnItem == itemsMax)
						active_home_veh_carspawnItem = 0;
					waitTime = 100;
				}
				else
					if (bLeft)
					{
						play_sound("NAV_LEFT_RIGHT");
						if (active_home_veh_carspawnItem == 0)
							active_home_veh_carspawnItem = (active_home_veh_carspawnLine == (lineCount - 1)) ? itemCountLastLine : itemCount;
						active_home_veh_carspawnItem--;
						waitTime = 100;
					}
					else
						if (bUp)
						{
							play_sound("NAV_UP_DOWN");
							if (active_home_veh_carspawnLine == 0)
								active_home_veh_carspawnLine = lineCount;
							active_home_veh_carspawnLine--;
							waitTime = 200;
						}
						else
							if (bDown)
							{
								play_sound("NAV_UP_DOWN");
								active_home_veh_carspawnLine++;
								if (active_home_veh_carspawnLine == lineCount)
									active_home_veh_carspawnLine = 0;
								waitTime = 200;
							}
		if (active_home_veh_carspawnLine == (lineCount - 1))
			if (active_home_veh_carspawnItem >= itemCountLastLine)
				active_home_veh_carspawnItem = 0;
	}
}

int active_home_veh = 0;
void menu_home_veh__action(menuList_boolean menu_lines[], int *ptr_active_line) {

	int active_line = *ptr_active_line;

	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	switch (active_line) {
		case 0: //Car Spawner
			menu_home_veh_carspawn__display();
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
		case 3:
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

		case 6:
			menu_list_feature_toggle(menu_lines, active_line);
			break;

		case 7: //Paint Random
			if (bPlayerExists) {
				if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
					Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, rand() % 255, rand() % 255, rand() % 255);
					if (VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(veh))
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, rand() % 255, rand() % 255, rand() % 255);
				}
				else {
					set_status_text("Player isn't in a vehicle");
				}
			}
			break;

		// switchable features
		default:
			menu_list_feature_toggle(menu_lines, active_line);
	}
}
void menu_home_veh__display(std::string caption) {
	// Menu Labels
	const int LINE_COUNT = 12;
	menuList_boolean menu_home_veh[LINE_COUNT] = {
		/*  0 */ { "Car Spawner", NULL, NULL },
		/*  1 */ { "Fix", NULL, NULL },
		/*  2 */ { "Flip", NULL, NULL },
		/*  3 */ { "Invincible", &featureVehInvincible, &featureVehInvincibleUpdated },
		/*  4 */ { "All Mods", NULL, NULL },
		/*  5 */ { "Custom License Plate", NULL, NULL },
		/*  6 */ { "Wrap To Spawned Car", &featureVehWrapInSpawned, NULL },
		/*  7 */ { "Paint Random", NULL, NULL },
		/*  8 */ { "Speed boost", &featureVehSpeedBoost, NULL },
		/*  9 */ { "Rainbow Car", &featureVehRainbow, NULL },
		/* 10 */ { "Sticky Cars", &featureVehStickyCar, NULL },
		/* 11 */ { "Slidey Cars", &featureVehSlide, NULL }
	};

	menuList_boolean *current_menu = menu_home_veh;
	int *current_line = &active_home_veh;

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
			menu_home_veh__action(current_menu, current_line);
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
			give_weapons_set_to_ped(playerPed, weaponOnlineNames, sizeof(weaponOnlineNames));
			give_weapons_set_to_ped(playerPed, weaponRestrictedNames, sizeof(weaponRestrictedNames));
			display_message_caption("Added all weapons");
			break;

		case 1:
			give_weapons_set_to_ped(playerPed, weaponOnlineNames, sizeof(weaponOnlineNames));
			display_message_caption("Added online weapons");
			break;

		case 2:
			give_weapons_set_to_ped(playerPed, weaponRestrictedNames, sizeof(weaponRestrictedNames));
			display_message_caption("Added restricted weapons");;
			break;

		case 3:
			WEAPON::REMOVE_ALL_PED_WEAPONS(playerPed, 1);
			set_status_text("Removed all weapons");
			break;

		// switchable features
		default:
			menu_list_feature_toggle(menu_lines, active_line);
	}
}
void  menu_home_weapon__display(std::string caption, DWORD waitTime = 150) {
	// Menu Labels
	const int LINE_COUNT = 10;
	menuList_boolean menu_home_weapon[LINE_COUNT] = {
		/*  0 */{ "All Weapons", NULL, NULL },
		/*  1 */{ "Weapons (Online)", NULL, NULL },
		/*  2 */{ "Weapons (Restricted)", NULL, NULL },
		/*  3 */{ "Remove All Weapons", NULL, NULL },
		/*  4 */{ "Infinite Ammo", &featureWeaponNoReload, NULL },
		/*  5 */{ "Fire Ammo", &featureWeaponFireAmmo, NULL },
		/*  6 */{ "Explosive Ammo", &featureWeaponExplosiveAmmo, NULL },
		/*  7 */{ "Explosive Melee", &featureWeaponExplosiveMelee, NULL },
		/*  8 */{ "Vehicle Rockets", &featureWeaponVehRockets, NULL },
		/*  9 */{ "One Hit Kill", &featureWeaponOneHit, NULL }
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

int active_home_teleport = 0;
void  menu_home_teleport__action(menuList_coord menu_lines[], int *ptr_active_line) {
	int active_line = *ptr_active_line;
	
	// common variables
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vector3 coords;
	Vector3 direction;
	bool success = false;

	// get entity to teleport
	Entity e = playerPed;
	if (PED::IS_PED_IN_ANY_VEHICLE(e, 0))
		e = PED::GET_VEHICLE_PED_IS_USING(e);

	// Teleport to marker
	if (active_line == 0) {
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
			static float groundCheckHeight[] = {
				0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 300.0, 350.0, 400.0,
				450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0
			};
			for (int i = 0; i < sizeof(groundCheckHeight) / sizeof(float); i++) {
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);
				WAIT(100);
				if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[i], &coords.z)) {
					groundFound = true;
					coords.z += 3.0;
					break;
				}
			}
			// if ground not found then set Z in air and give player a parachute
			if (!groundFound) {
				coords.z = 1000.0;
				if (!WEAPON::HAS_PED_GOT_WEAPON(playerPed, 0xFBAB5776, 0))
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(playerPed, 0xFBAB5776, 1, 0);
			}
			success = true;
		}
		else {
			display_message_caption("Map marker isn't set");
		}

	}
	else if (active_line == 1) { // move forward
		coords = ENTITY::GET_ENTITY_COORDS(playerPed, 1);
		direction = ENTITY::GET_ENTITY_FORWARD_VECTOR(playerPed);
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
			coords.x = coords.x + direction.x * 5;
			coords.y = coords.y + direction.y * 5;
			coords.z += 0.5;
		}
		else {
			coords.x = coords.x + direction.x * 2.5;
			coords.y = coords.y + direction.y * 2.5;
			coords.z += 0.8;
		}
		success = true;
	}
	else { // predefined coords
		coords.x = menu_lines[active_line].x;
		coords.y = menu_lines[active_line].y;
		coords.z = menu_lines[active_line].z;
		success = true;
	}

	// set player pos
	if (success) {
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, coords.z, 0, 0, 1);
		WAIT(0);
		display_message_caption("Teleported");
	}
}
void  menu_home_teleport__display(std::string caption) {
	// Menu Labels
	const int LINE_COUNT = 18;
	menuList_coord menu_home_teleport[LINE_COUNT] = {
		/*  0 */ { "MARKER" },
		/*  1 */ { "Forward" },
		/*  2 */ { "MICHAEL'S HOUSE", -852.4f, 160.0f, 65.6f },
		/*  3 */ { "FRANKLIN'S HOUSE", 7.9f, 548.1f, 175.5f },
		/*  4 */ { "TREVOR'S TRAILER", 1985.7f, 3812.2f, 32.2f },
		/*  5 */ { "AIRPORT ENTRANCE", -1034.6f, -2733.6f, 13.8f },
		/*  6 */ { "AIRPORT FIELD", -1336.0f, -3044.0f, 13.9f },
		/*  7 */ { "ELYSIAN ISLAND", 338.2f, -2715.9f, 38.5f },
		/*  8 */ { "JETSAM", 760.4f, -2943.2f, 5.8f },
		/*  9 */ { "STRIPCLUB", 127.4f, -1307.7f, 29.2f },
		/* 10 */ { "ELBURRO HEIGHTS", 1384.0f, -2057.1f, 52.0f },
		/* 11 */ { "FERRIS WHEEL", -1670.7f, -1125.0f, 13.0f },
		/* 12 */ { "CHUMASH", -3192.6f, 1100.0f, 20.2f },
		/* 13 */ { "WINDFARM", 2354.0f, 1830.3f, 101.1f },
		/* 14 */ { "MILITARY BASE", -2047.4f, 3132.1f, 32.8f },
		/* 15 */ { "MCKENZIE AIRFIELD", 2121.7f, 4796.3f, 41.1f },
		/* 16 */ { "DESERT AIRFIELD", 1747.0f, 3273.7f, 41.1f },
		/* 17 */ { "CHILLIAD", 425.4f, 5614.3f, 766.5f }
	};

	menuList_coord *current_menu = menu_home_teleport;
	int *current_line = &active_home_teleport;

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
			menu_home_teleport__action(current_menu, current_line);
		}
	}
}

int active_home_player_skinchangerLine = 0;
int active_home_player_skinchangerItem = 0;
void  menu_home_player_skinchanger__display() {
	DWORD waitTime = 150;
	const int lineCount = 69;
	const int itemCount = 10;
	const int itemCountLastLine = itemCount;
	while (true) {
		// timed menu draw, used for pause after active line switch
		DWORD maxTickCount = GetTickCount() + waitTime;
		do {
			// draw menu
			char caption[32];
			sprintf_s(caption, "Skin Changer   %d / %d", active_home_player_skinchangerLine + 1, lineCount);
			draw_menu_line(caption, 350.0, 15.0, 18.0, 0.0, 5.0, false, true);
			for (int i = 0; i < itemCount; i++)
				if (strlen(pedModels[active_home_player_skinchangerLine][i]))
					draw_menu_line(pedModelNames[active_home_player_skinchangerLine][i], 100.0f, 5.0f, 200.0f, 100.0f + i * 110.0f, 5.0f, i == active_home_player_skinchangerItem, false, false);

			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect) {
			play_sound("SELECT");
			change_player_model(PLAYER::PLAYER_ID(), 
				GAMEPLAY::GET_HASH_KEY((char *)pedModels[active_home_player_skinchangerLine][active_home_player_skinchangerItem]));
			skinchanger_used = true;
			waitTime = 200;
		}
		else {
			if (bBack) {
				play_sound("BACK");
				break;
			}
			if (bRight) {
				play_sound("NAV_LEFT_RIGHT");
				active_home_player_skinchangerItem++;
				int itemsMax = (active_home_player_skinchangerLine == (lineCount - 1)) ? itemCountLastLine : itemCount;
				if (active_home_player_skinchangerItem == itemsMax)
					active_home_player_skinchangerItem = 0;
				waitTime = 100;
			}
			if (bLeft) {
				play_sound("NAV_LEFT_RIGHT");
				if (active_home_player_skinchangerItem == 0)
					active_home_player_skinchangerItem = (active_home_player_skinchangerLine == (lineCount - 1)) ? itemCountLastLine : itemCount;
				active_home_player_skinchangerItem--;
				waitTime = 100;
			}
			if (bUp) {
				play_sound("NAV_UP_DOWN");
				if (active_home_player_skinchangerLine == 0)
					active_home_player_skinchangerLine = lineCount;
				active_home_player_skinchangerLine--;
				waitTime = 200;
			}
			if (bDown) {
				play_sound("NAV_UP_DOWN");
				active_home_player_skinchangerLine++;
				if (active_home_player_skinchangerLine == lineCount)
					active_home_player_skinchangerLine = 0;
				waitTime = 200;
			}
		}
		if (active_home_player_skinchangerLine == (lineCount - 1))
			if (active_home_player_skinchangerItem >= itemCountLastLine)
				active_home_player_skinchangerItem = 0;
	}
}

int active_home_player_player2 = 0;
void  menu_home_player_player2__action(int *ptr_active_line) {
	int active_line = *ptr_active_line;

	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	switch (active_line) {
		case 0:
			if (bPlayerExists) {
				PED::CLEAR_PED_BLOOD_DAMAGE(playerPed);
				PED::RESET_PED_VISIBLE_DAMAGE(playerPed);
			}
			break;
	}
}
void  menu_home_player_player2__display(std::string caption) {
	// Menu Labels
	const int LINE_COUNT = 1;
	menuList menu_home_player_player2[LINE_COUNT] = {
		/* 0 */ { "Clean Player" }
	};

	menuList *current_menu = menu_home_player_player2;
	int *current_line = &active_home_player_player2;

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
			menu_home_player_player2__action (current_line);
		}
	}
}

int active_home_player = 0;
void  menu_home_player__action(menuList_boolean menu_lines[], int *ptr_active_line) {

	int active_line = *ptr_active_line;

	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	switch (active_line) {
		//call next page
		case 0:
			menu_home_player_player2__display("Player 2/2");
			break;
	
		// skin changer
		case 1:
			menu_home_player_skinchanger__display();
			break;

		// fix player
		case 2:
			ENTITY::SET_ENTITY_HEALTH(playerPed, ENTITY::GET_ENTITY_MAX_HEALTH(playerPed));
			PED::ADD_ARMOUR_TO_PED(playerPed, PLAYER::GET_PLAYER_MAX_ARMOUR(player) - PED::GET_PED_ARMOUR(playerPed));
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
			{
				Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				if (ENTITY::DOES_ENTITY_EXIST(playerVeh) && !ENTITY::IS_ENTITY_DEAD(playerVeh))
					VEHICLE::SET_VEHICLE_FIXED(playerVeh);
			}
			display_message_caption("Player fixed");
			break;

		// reset model skin
		case 3: 
			PED::SET_PED_DEFAULT_COMPONENT_VARIATION(playerPed);
			display_message_caption("Using default model skin");
	
		break;

		// add cash
		case 4:
			if (bPlayerExists) {
				Vector3 ENTPOS = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
				static Any prop_bag = GAMEPLAY::GET_HASH_KEY("prop_money_bag_01");
				STREAMING::REQUEST_MODEL(prop_bag); //Request the shitty Model so that 40k spawns are possible
				while (!STREAMING::HAS_MODEL_LOADED(prop_bag)) WAIT(0);
				//if (STREAMING::HAS_MODEL_LOADED(prop_bag))
				//{
				OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_MONEY_CASE"), 
					ENTPOS.x, ENTPOS.y, ENTPOS.z + 1, 0, 40000, prop_bag, 0, 1);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(prop_bag);
				//}
			}
			break;
		// wanted up
		case 5:
			if (bPlayerExists && PLAYER::GET_PLAYER_WANTED_LEVEL(player) < 5)
			{
				PLAYER::SET_PLAYER_WANTED_LEVEL(player, PLAYER::GET_PLAYER_WANTED_LEVEL(player) + 1, 0);
				PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, 0);
				set_status_text("Wanted Up");
			}
			break;
		// wanted down
		case 6:
			if (bPlayerExists && PLAYER::GET_PLAYER_WANTED_LEVEL(player) > 0)
			{
				PLAYER::SET_PLAYER_WANTED_LEVEL(player, PLAYER::GET_PLAYER_WANTED_LEVEL(player) - 1, 0);
				PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, 0);
				set_status_text("Wanted Down");
			}
			break;
		// switchable features
		default:
			menu_list_feature_toggle(menu_lines, active_line);
	}
}
void  menu_home_player__display(std::string caption, DWORD waitTime = 150) {
	// Menu Labels
	const int LINE_COUNT = 16;
	menuList_boolean menu_home_player[LINE_COUNT] = {
		/*  0 */ { "Next Page...", NULL, NULL },
		/*  1 */ { "Skin Changer", NULL, NULL },
		/*  2 */ { "Fix Player", NULL, NULL },
		/*  3 */ { "Reset Skin", NULL, NULL },
		/*  4 */ { "Money Money", NULL, NULL },
		/*  5 */ { "Wanted Up", NULL, NULL },
		/*  6 */ { "Wanted Down", NULL, NULL },
		/*  7 */ { "Never Wanted", &featurePlayerNeverWanted, NULL },
		/*  8 */ { "Godmode", &featurePlayerInvincible, &featurePlayerInvincibleUpdated },
		/*  9 */ { "Police Ignore", &featurePlayerIgnored, &featurePlayerIgnoredUpdated },
		/* 10 */ { "Infinite Ability", &featurePlayerUnlimitedAbility, NULL },
		/* 11 */ { "Silent", &featurePlayerNoNoise, &featurePlayerNoNoiseUpdated },
		/* 12 */ { "Fast Swim", &featurePlayerFastSwim, &featurePlayerFastSwimUpdated },
		/* 13 */ { "Fast Run", &featurePlayerFastRun, &featurePlayerFastRunUpdated },
		/* 14 */ { "Super Jump", &featurePlayerSuperJump, NULL },
		/* 15 */ { "Invisible", &featurePlayerInvisible, NULL }
	};

	menuList_boolean *current_menu = menu_home_player;
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
void menu_home__action(int *ptr_active_line) {

	int active_line = *ptr_active_line;

	switch (active_line) {
		case 0:
			menu_home_player__display("Player 1/2");
			break;
		case 1:
			menu_home_teleport__display("Teleport");
			break;
		case 2:
			menu_home_weapon__display("Weapons");
			break;
		case 3:
			menu_home_veh__display("Vehicle Options");
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
			menu_home_animation__display("Animation");
			break;
	}
}
void menu_home__display(std::string caption) {
	// Menu Labels
	const int LINE_COUNT = 8;
	menuList menu_home[LINE_COUNT] = {
		/* 0 */{ "Player Options" },
		/* 1 */{ "Teleport" },
		/* 2 */{ "Weapon Options" },
		/* 3 */{ "Vehicle Options" },
		/* 4 */{ "Time Options" },
		/* 5 */{ "Weather Options" },
		/* 6 */{ "Misc Options" },
		/* 7 */{ "Animations" }
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

/********************************
	End of
	menu list in reverse order
*********************************/

void reset_globals()
{
	active_home =
		active_home_player =
		active_home_player_player2 =
		active_home_player_skinchangerLine =
		active_home_player_skinchangerItem =
		active_home_teleport =
		active_home_weapon =
		active_home_veh =
		active_home_veh_carspawnLine =
		active_home_time =
		active_home_weather = 
		active_home_misc =
		active_home_misc_stats =
		active_home_misc_stats_unlocks =
		active_home_misc_stats_level =
		active_home_misc_credits =
		active_home_animation = 0;

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
		featureVehWrapInSpawned =
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

		featureMiscMobileRadio = false;

		skinchanger_used = false;
}

void main()
{
	bypass_online();
	reset_globals();

	while (true)
	{
		if (trainer_switch_pressed())
		{
			reset_trainer_switch();
			play_sound("SELECT");
			menu_home__display("Kinky Menu");
			DWORD time = GetTickCount() + 1000;
			while (GetTickCount() < time)
			{
				update_features();
				WAIT(0);
			}
			reset_trainer_switch();
		}
		update_features();

		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}
