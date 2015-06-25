#ifndef DATABASES_H
#define DATABASES_H

#include <vector>
#include <windows.h>

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

std::vector< std::vector<LPCSTR> > pedModels = {

	// 0 Default
	{ "_default", "mp_f_freemode_01", "mp_m_freemode_01", "player_zero", "player_one", "player_two" },
	{ "< Default >", "Female (Online)", "Male (Online)", "Michael", "Franklin", "Trevor" },

	// 2 Creatures
	{ "_creatures", "a_c_chimp", "a_c_rhesus", "a_c_rat", "a_c_cat_01", "a_c_chop", "a_c_husky", "a_c_poodle", 
	"a_c_pug", "a_c_retriever", "a_c_rottweiler", "a_c_shepherd", "a_c_westy", "a_c_rabbit_01", "a_c_hen", "a_c_pig", 
	"a_c_boar", "a_c_deer", "a_c_cow", "a_c_coyote", "a_c_mtlion", "a_c_cormorant", "a_c_crow", "a_c_chickenhawk", 
	"a_c_pigeon", "a_c_seagull", "a_c_dolphin", "a_c_fish", "a_c_sharkhammer", "a_c_sharktiger", "a_c_killerwhale", 
	"a_c_humpback", "a_c_stingray" },

	{ "< Creatures >", 
	// Lang [1 to 20]
	"Chimpanzee            - - - Land", 
	"Rhesus Monkey", "Rat", "Cat", "Chop (Dog)", "Husky (Dog)", "Poodle (Dog)", "Pug (Dog)", "Retriever (Dog)", "Rottweiler (Dog)", 
	"Shepherd (Dog)", "Westy (Dog)", "Rabbit", "Hen", "Pig", "Boar", "Deer", "Cow", "Coyote", "Mt. Lion", 
	// Air [21 to 25]
	"Cormorant                  - - - Air", 
	"Crow", "Hawk", "Pigeon", "Seagull", 
	// Water [26 to 32]
	"Dolphin                      - - - Sea", 
	"Fish", "Hammerhead Shark", "Tiger Shark", "Killer Whale", "Humpback Whale", "Stingray" },


	// 4 Ambient
	{ "_ambient", "a_m_m_afriamer_01", "a_f_y_femaleagent", "a_f_m_salton_01", "a_m_m_salton_01", "a_m_m_salton_02", "a_m_m_salton_03", "a_m_m_salton_04", "a_f_o_salton_01", "a_m_o_salton_01", "a_m_y_salton_01", "a_m_m_acult_01", "a_m_o_acult_01", "a_m_o_acult_02", "a_m_y_acult_01", "a_m_y_acult_02", "a_f_m_bodybuild_01", "a_f_m_beach_01", "a_m_m_beach_01", "a_m_m_beach_02", "a_m_y_musclbeac_01", "a_m_y_musclbeac_02", "a_m_o_beach_01", "a_f_m_trampbeac_01", "a_m_m_trampbeac_01", "a_m_y_beachvesp_01", "a_m_y_beachvesp_02", "a_f_y_beach_01", "a_m_y_beach_01", "a_m_y_beach_02", "a_m_y_beach_03", "a_m_y_breakdance_01", "a_m_y_busicas_01", "a_m_m_business_01", "a_f_m_business_02", "a_f_y_business_01", "a_m_y_business_01", "a_f_y_business_02", "a_m_y_business_02", "a_f_y_business_03", "a_m_y_business_03", "a_f_y_business_04", "a_m_y_cyclist_01", "a_f_m_downtown_01", "a_m_y_downtown_01", "a_m_y_dhill_01", "a_f_m_eastsa_01", "a_m_m_eastsa_01", "a_f_m_eastsa_02", "a_m_m_eastsa_02", "a_f_y_eastsa_01", "a_m_y_eastsa_01", "a_f_y_eastsa_02", "a_m_y_eastsa_02", "a_f_y_eastsa_03", "a_f_y_epsilon_01", "a_m_y_epsilon_01", "a_m_y_epsilon_02", "a_m_m_farmer_01", "a_f_m_fatbla_01", "a_f_m_fatcult_01", "a_m_m_fatlatin_01", "a_f_m_fatwhite_01", "a_f_y_fitness_01", "a_f_y_fitness_02", "a_m_y_gay_01", "a_m_y_gay_02", "a_m_m_genfat_01", "a_m_m_genfat_02", "a_f_y_genhot_01", "a_f_o_genstreet_01", "a_m_o_genstreet_01", "a_m_y_genstreet_01", "a_m_y_genstreet_02", "a_m_m_golfer_01", "a_f_y_golfer_01", "a_m_y_golfer_01", "a_m_m_hasjew_01", "a_m_y_hasjew_01", "a_f_y_hiker_01", "a_m_y_hiker_01", "a_m_m_hillbilly_01", "a_m_m_hillbilly_02", "a_f_y_hippie_01", "a_m_y_hippy_01", "a_f_y_hipster_01", "a_m_y_hipster_01", "a_f_y_hipster_02", "a_m_y_hipster_02", "a_f_y_hipster_03", "a_m_y_hipster_03", "a_f_y_hipster_04", "a_m_m_indian_01", "a_f_o_indian_01", "a_f_y_indian_01", "a_m_y_indian_01", "a_m_y_jetski_01", "a_f_y_juggalo_01", "a_m_y_juggalo_01", "a_f_m_ktown_01", "a_m_m_ktown_01", "a_f_m_ktown_02", "a_f_o_ktown_01", "a_m_o_ktown_01", "a_m_y_ktown_01", "a_m_y_ktown_02", "a_m_y_latino_01", "a_m_m_malibu_01", "a_m_y_methhead_01", "a_m_m_mexcntry_01", "a_m_m_mexlabor_01", "a_m_y_mexthug_01", "a_m_y_motox_01", "a_m_y_motox_02", "a_m_m_og_boss_01", "a_m_m_paparazzi_01", "a_m_m_polynesian_01", "a_m_y_polynesian_01", "a_f_m_prolhost_01", "a_m_m_prolhost_01", "a_m_y_roadcyc_01", "a_f_m_bevhills_01", "a_m_m_bevhills_01", "a_f_m_bevhills_02", "a_m_m_bevhills_02", "a_f_y_bevhills_01", "a_m_y_bevhills_01", "a_f_y_bevhills_02", "a_m_y_bevhills_02", "a_f_y_bevhills_03", "a_f_y_bevhills_04", "a_f_y_runner_01", "a_m_y_runner_01", "a_m_y_runner_02", "a_f_y_rurmeth_01", "a_m_m_rurmeth_01", "a_m_m_skater_01", "a_f_y_skater_01", "a_m_y_skater_01", "a_m_y_skater_02", "a_f_m_skidrow_01", "a_m_m_skidrow_01", "a_f_y_scdressy_01", "a_m_m_socenlat_01", "a_f_m_soucent_01", "a_m_m_soucent_01", "a_f_m_soucent_02", "a_m_m_soucent_02", "a_m_m_soucent_03", "a_m_m_soucent_04", "a_f_m_soucentmc_01", "a_f_o_soucent_01", "a_m_o_soucent_01", "a_f_o_soucent_02", "a_m_o_soucent_02", "a_m_o_soucent_03", "a_f_y_soucent_01", "a_m_y_soucent_01", "a_f_y_soucent_02", "a_m_y_soucent_02", "a_f_y_soucent_03", "a_m_y_soucent_03", "a_m_y_soucent_04", "a_m_y_stbla_01", "a_m_y_stbla_02", "a_m_y_stlat_01", "a_m_m_stlat_02", "a_m_y_stwhi_01", "a_m_y_stwhi_02", "a_m_y_sunbathe_01", "a_m_y_surfer_01", "a_f_y_tennis_01", "a_m_m_tennis_01", "a_f_y_topless_01", "a_f_m_tourist_01", "a_m_m_tourist_01", "a_f_y_tourist_01", "a_f_y_tourist_02", "a_f_m_tramp_01", "a_m_m_tramp_01", "a_m_o_tramp_01", "a_m_m_tranvest_01", "a_m_m_tranvest_02", "a_f_y_vinewood_01", "a_m_y_vinewood_01", "a_f_y_vinewood_02", "a_m_y_vinewood_02", "a_f_y_vinewood_03", "a_m_y_vinewood_03", "a_f_y_vinewood_04", "a_m_y_vinewood_04", "a_m_y_vindouche_01", "a_f_y_yoga_01", "a_m_y_yoga_01" },
	{ "< Ambient >", "African American (M)", "Agent (F)", "Alamo Sea Middle 1 (F)", "Alamo Sea Middle 1 (M)", "Alamo Sea Middle 2 (M)", "Alamo Sea Middle 3 (M)", "Alamo Sea Middle 4 (M)", "Alamo Sea Old 1 (F)", "Alamo Sea Old 1 (M)", "Alamo Sea Young 1 (M)", "Altruist Cult Middle (M)", "Altruist Cult Old 1 (M)", "Altruist Cult Old 2 (M)", "Altruist Cult Young 1 (M)", "Altruist Cult Young 2 (M)", "Beach Body Builder (F)", "Beach Middle 1 (F)", "Beach Middle 1 (M)", "Beach Middle 2 (M)", "Beach Muscle 1 (M)", "Beach Muscle 2 (M)", "Beach Old (M)", "Beach Tramp (F)", "Beach Tramp (M)", "Beach Vespucci 1 (M)", "Beach Vespucci 2 (M)", "Beach Young (F)", "Beach Young 1 (M)", "Beach Young 2 (M)", "Beach Young 3 (M)", "Break Dancer (M)", "Business Casual (M)", "Business Middle 1 (M)", "Business Middle 2 (F)", "Business Young 1 (F)", "Business Young 1 (M)", "Business Young 2 (F)", "Business Young 2 (M)", "Business Young 3 (F)", "Business Young 3 (M)", "Business Young 4 (F)", "Cyclist (M)", "Downtown (F)", "Downtown (M)", "Downtown Hill (M)", "East SA Middle 1 (F)", "East SA Middle 1 (M)", "East SA Middle 2 (F)", "East SA Middle 2 (M)", "East SA Young 1 (F)", "East SA Young 1 (M)", "East SA Young 2 (F)", "East SA Young 2 (M)", "East SA Young 3 (F)", "Epsilon 1 (F)", "Epsilon 1 (M)", "Epsilon 2 (M)", "Farmer (M)", "Fat Black (F)", "Fat Cult (F)", "Fat Latin (M)", "Fat White (F)", "Fitness 1 (F)", "Fitness 2 (F)", "Gay 1 (M)", "Gay 2 (M)", "Gen Fat 1 (M)", "Gen Fat 2 (M)", "Gen Hot 1 (F)", "Gen Street Old 1 (F)", "Gen Street Old 1 (M)", "Gen Street Young 1 (M)", "Gen Street Young 2 (M)", "Golfer Middle 1 (M)", "Golfer Young 1 (F)", "Golfer Young 1 (M)", "Hasidic Jew Middle 1 (M)", "Hasidic Jew Young 1 (M)", "Hiker 1 (F)", "Hiker 1 (M)", "Hillbilly 1 (M)", "Hillbilly 2 (M)", "Hippie (F)", "Hippy 1 (M)", "Hipster 1 (F)", "Hipster 1 (M)", "Hipster 2 (F)", "Hipster 2 (M)", "Hipster 3 (F)", "Hipster 3 (M)", "Hipster 4 (F)", "Indian Middle 1 (M)", "Indian Old 1 (F)", "Indian Young 1 (F)", "Indian Young 1 (M)", "Jetski (M)", "Juggalo 1 (F)", "Juggalo 1 (M)", "Korean Town Middle 1 (F)", "Korean Town Middle 1 (M)", "Korean Town Middle 2 (F)", "Korean Town Old 1 (F)", "Korean Town Old 1 (M)", "Korean Town Young 1 (M)", "Korean Town Young 2 (M)", "Latino (M)", "Malibu (M)", "Meth Head (M)", "Mexican Country (M)", "Mexican Labor (M)", "Mexican Thug (M)", "MotoX 1 (M)", "MotoX 2 (M)", "OG Boss (M)", "Paparazzi (M)", "Polynesian Middle (M)", "Polynesian Young (M)", "Prologue Hostage (F)", "Prologue Hostage (M)", "Road cyclist 1 (M)", "Rockford Hills Middle 1 (F)", "Rockford Hills Middle 1 (M)", "Rockford Hills Middle 2 (F)", "Rockford Hills Middle 2 (M)", "Rockford Hills Young 1 (F)", "Rockford Hills Young 1 (M)", "Rockford Hills Young 2 (F)", "Rockford Hills Young 2 (M)", "Rockford Hills Young 3 (F)", "Rockford Hills Young 4 (F)", "Runner (F)", "Runner 1 (M)", "Runner 2 (M)", "Rural Meth Addict (F)", "Rural Meth Addict (M)", "Skater Middle 1 (M)", "Skater Young 1 (F)", "Skater Young 1 (M)", "Skater Young 2 (M)", "Skid Row (F)", "Skid Row (M)", "South Center Dressy (F)", "South Center Latino (M)", "South Center Middle 1 (F)", "South Center Middle 1 (M)", "South Center Middle 2 (F)", "South Center Middle 2 (M)", "South Center Middle 3 (M)", "South Center Middle 4 (M)", "South Center Middle MC (F)", "South Center Old 1 (F)", "South Center Old 1 (M)", "South Center Old 2 (F)", "South Center Old 2 (M)", "South Center Old 3 (M)", "South Center Young 1 (F)", "South Center Young 1 (M)", "South Center Young 2 (F)", "South Center Young 2 (M)", "South Center Young 3 (F)", "South Center Young 3 (M)", "South Center Young 4 (M)", "Street Black 1 (M)", "Street Black 2 (M)", "Street Latino 1 (M)", "Street Latino 2 (M)", "St White 1 (M)", "Street White 2 (M)", "Sunbathe (M)", "Surfer (M)", "Tennis (F)", "Tennis (M)", "Topless (F)", "Tourist Middle 1 (F)", "Tourist Middle 1 (M)", "Tourist Young 1 (F)", "Tourist Young 2 (F)", "Tramp Middle (F)", "Tramp Middle (M)", "Tramp Young (M)", "Transvestites 1 (M)", "Transvestites 2 (M)", "Vinewood 1 (F)", "Vinewood 1 (M)", "Vinewood 2 (F)", "Vinewood 2 (M)", "Vinewood 3 (F)", "Vinewood 3 (M)", "Vinewood 4 (F)", "Vinewood 4 (M)", "Vinewood Douche (M)", "Yoga (F)", "Yoga (M)" },

	// 6 Gangs
	{ "_gangs", "g_m_m_armboss_01", "g_m_m_armgoon_01", "g_m_y_armgoon_02", "g_m_m_armlieut_01", "g_m_y_azteca_01", "g_m_y_ballaeast_01", "g_m_y_ballaorig_01", "g_m_y_ballasout_01", "g_f_y_ballas_01", "g_m_m_chemwork_01", "g_m_m_chiboss_01", "g_m_m_chicold_01", "g_m_m_chigoon_01", "g_m_m_chigoon_02", "g_m_y_famca_01", "g_m_y_famdnf_01", "g_m_y_famfor_01", "g_f_y_families_01", "g_m_y_korean_01", "g_m_y_korean_02", "g_m_m_korboss_01", "g_m_y_korlieut_01", "g_f_y_lost_01", "g_m_y_lost_01", "g_m_y_lost_02", "g_m_y_lost_03", "g_m_m_mexboss_01", "g_m_m_mexboss_02", "g_m_y_mexgang_01", "g_m_y_mexgoon_01", "g_m_y_mexgoon_02", "g_m_y_mexgoon_03", "g_f_y_vagos_01", "g_m_y_pologoon_01", "g_m_y_pologoon_02", "g_m_y_salvaboss_01", "g_m_y_salvagoon_01", "g_m_y_salvagoon_02", "g_m_y_salvagoon_03", "g_m_y_strpunk_01", "g_m_y_strpunk_02" },
	{ "< Gangs >", "Armenian Boss (M)", "Armenian Goon 1 (M)", "Armenian Goon 2 (M)", "Armenian Lieutenant (M)", "Azteca (M)", "Ballas East Side (M)", "Ballas Original Covernant (M)", "Ballas South Rancho (M)", "Ballas (F)", "Chem. Worker (M)", "Chinese Boss (M)", "Chinese Cold (M)", "Chinese Goon 1 (M)", "Chinese Goon 2 (M)", "Families CAF (M)", "Families DNF (M)", "Families Forum (M)", "Families (F)", "Korean 1 (M)", "Korean 2 (M)", "Korean Boss (M)", "Korean Lieutenant (M)", "Lost (F)", "Lost 1 (M)", "Lost 2 (M)", "Lost 3 (M)", "Mexican Boss 1 (M)", "Mexican Boss 2 (M)", "Mexican Gang (M)", "Mexican Goon 1 (M)", "Mexican Goon 2 (M)", "Mexican Goon 3 (M)", "Mexican Vagos (F)", "Polynesian Goon 1 (M)", "Polynesian Goon 2 (M)", "Salvadorian Boss (M)", "Salvadorian Goon 1 (M)", "Salvadorian Goon 2 (M)", "Salvadorian Goon 3 (M)", "Street Punk 1 (M)", "Street Punk 2 (M)" },

	// 8 In-game
	{ "_ingame", "ig_abigail", "ig_mp_agent14", "ig_agent", "ig_andreas", "csb_anita", "ig_ashley", "ig_money", "ig_barry", "ig_beverly", "ig_brad", "cs_bradcadaver", "ig_casey", "ig_chef2", "ig_chengsr", "ig_chrisformage", "ig_clay", "ig_claypain", "ig_cletus", "ig_dale", "ig_davenorton", "cs_debra", "ig_denise", "csb_denise_friend", "ig_devin", "ig_amandatownley", "ig_jimmydisanto", "ig_tracydisanto", "ig_dom", "ig_popov", "ig_drfriedlander", "ig_fabien", "ig_floyd", "csb_g", "ig_hao", "csb_hugh", "csb_imran", "ig_janet", "ig_jay_norris", "ig_jimmyboston", "ig_joeminuteman", "ig_johnnyklebitz", "ig_josef", "ig_josh", "ig_karen_daniels", "ig_kerrymcintosh", "ig_tenniscoach", "ig_lamardavis", "ig_lazlow", "ig_lestercrest", "ig_magenta", "ig_manuel", "ig_marnie", "cs_martinmadrazo", "ig_maryann", "ig_maude", "ig_michelle", "ig_milton", "ig_molly", "ig_mrk", "ig_mrsphillips", "ig_mrs_thornhill", "ig_natalia", "ig_nervousron", "ig_nigel", "ig_omega", "ig_orleans", "ig_ortega", "csb_oscar", "ig_paige", "ig_patricia", "ig_dreyfuss", "ig_rashcosvki", "ig_roccopelosi", "ig_siemonyetarian", "ig_solomon", "ig_stevehains", "ig_stretch", "ig_talina", "ig_tanisha", "ig_taocheng", "ig_taostranslator", "ig_terry", "cs_tom", "ig_tomepsilon", "ig_tonya", "ig_tylerdix", "ig_paper", "ig_wade", "ig_zimbor", "ig_ballasog", "ig_bankman", "ig_bestmen", "ig_bride", "ig_car3guy1", "ig_car3guy2", "cs_carbuyer", "csb_chin_goon", "csb_cop", "csb_customer", "ig_fbisuit_01", "csb_fos_rep", "ig_groom", "csb_grove_str_dlr", "cs_guadalope", "cs_gurk", "hc_driver", "hc_gunman", "hc_hacker", "ig_hunter", "csb_janitor", "ig_jewelass", "ig_lifeinvad_01", "ig_lifeinvad_02", "csb_mweather", "ig_old_man1a", "ig_old_man2", "csb_porndudes", "ig_priest", "csb_prolsec", "ig_prolsec_02", "ig_ramp_hipster", "csb_ramp_marine", "ig_ramp_mex", "ig_ramp_hic", "ig_ramp_gang", "csb_reporter", "ig_russiandrunk", "ig_screen_writer", "ig_trafficwarden" },
	{ "< In-Game >", "Abigail Mathers", "Agent 14", "Agent 14's associate", "Andreas Sanchez", "Anita Mendoza", "Ashley Butler", "Avi Schwartzman", "Barry", "Beverly Felton", "Brad Snider", "Brad (Cadaver)", "Casey", "Chef", "Cheng SR", "Chris Formage", "Clay Simons", "Clay Jackson, The Pain Giver", "Cletus Ewing", "Dale Jenkins", "Dave Norton", "Debra", "Denise", "Denise's Friend", "Devin Weston", "De Santa, Amanda", "De Santa, Jimmy", "De Santa, Tracy", "Dom Beasley", "Dmitri Popov", "Dr. Friedlander", "Fabien", "Floyd", "Gerald", "Hao", "Hugh Harrison", "Imran Shinowa", "Janet", "Jay Norris", "Jimmy Boston", "Joe Minute Man", "Johnn Klebitz", "Josef", "Josh Bernstein", "Karen Daniels", "Kerry McIntosh", "Kyle Chavis, Tennis Coach", "Lamar Davis", "Lazlow Jones", "Lester Crest", "Magenta", "Manuel", "Marnie", "Martin Madrazo", "Mary Ann", "Maude", "Michelle", "Milton", "Molly", "Mr. Kerimov, Ferdinand", "Mrs. Phillips", "Mrs. Thornhill", "Natalia", "Nervous Ron", "Nigel", "Omega", "Orleans (Big Foot)", "Ortega", "Oscar", "Paige Harris", "Patricia", "Peter Dreyfuss", "Prof. Rashkovsky, Maxim", "Rocco Pelosi", "Siemon Yetarian", "Solomon Richards", "Steve Haines", "Stretch", "Talina", "Tanisha", "Tao Cheng", "Tao's Translator", "Terry", "Tom", "Tom (Epsilon)", "Tonya", "Tyler Dix", "United Paper Man, IAA", "Wade Hebert", "Zimbor", "Ballas OG", "Bankman", "Bestmen", "Bride", "Car 3 Guy 1", "Car 3 Guy 2", "Car Buyer", "Chinense Goon", "Cop, Country", "Customer", "FIB Suit", "Fos Rep", "Groom", "Grove Street Dealer", "Guadalope", "Gurk", "Heist Crew, Driver", "Heist Crew, Gunman", "Heist Crew, Hacker", "Hunter", "Janitor", "Jeweller Assistance", "Life Invader 1", "Life Invader 2", "Merryweather Security", "Old Man 1", "Old Man 2", "Porn Dudes", "Priest", "Prologue Security 1", "Prologue Security 2", "Rampage - Hipster", "Rampage - Marine", "Rampage - Mexican", "Rampage - Redneck", "Rampage - Gang", "Reporter", "Russian Drunk", "Screen Writer", "Traffic Warden" },

	// 10 GTA Online
	{ "_gtaonline", "mp_m_claude_01", "mp_m_marston_01", "mp_f_misty_01", "mp_m_niko_01", "mp_s_m_armoured_01", "mp_f_deadhooker", "mp_m_exarmy_01", "mp_m_famdd_01", "mp_m_fibsec_01", "mp_g_m_pros_01", "mp_m_shopkeep_01", "mp_f_stripperlite" },
	{ "< GTA Online >", "Claude", "John Marston", "Misty", "Niko Bellic", "Armoured", "Dead Hooker", "Ex Army", "Families DD", "FIB Security", "Professional", "Shop Keeper", "Stripper Lite" },

	// 12 Specials
	{ "_special", "s_f_y_airhostess_01", "s_m_y_airworker", "s_m_y_ammucity_01", "s_m_m_ammucountry", "s_m_m_armoured_01", "s_m_m_armoured_02", "s_m_y_autopsy_01", "s_m_m_autoshop_01", "s_m_m_autoshop_02", "s_m_y_barman_01", "s_m_m_cntrybar_01", "s_f_y_bartender_01", "s_f_y_baywatch_01", "s_m_y_baywatch_01", "s_m_y_blackops_01", "s_m_y_blackops_02", "s_m_m_bouncer_01", "s_m_y_busboy_01", "s_m_o_busker_01", "s_m_y_chef_01", "s_m_y_clown_01", "s_m_y_construct_01", "s_m_y_construct_02", "s_f_y_cop_01", "s_m_y_cop_01", "s_m_y_hwaycop_01", "s_m_y_swat_01", "s_f_y_ranger_01", "s_m_y_ranger_01", "s_f_y_sheriff_01", "s_m_y_sheriff_01", "s_m_m_snowcop_01", "s_m_y_dealer_01", "s_m_m_dockwork_01", "s_m_y_dockwork_01", "s_m_m_doctor_01", "s_m_y_doorman_01", "s_m_y_dwservice_01", "s_m_y_dwservice_02", "s_f_y_factory_01", "s_m_y_factory_01", "s_m_m_fiboffice_01", "s_m_m_fiboffice_02", "s_m_y_fireman_01", "s_m_m_gaffer_01", "s_m_y_garbage", "s_m_m_gardener_01", "s_m_m_gentransport", "s_m_y_grip_01", "s_f_m_fembarber", "s_m_m_hairdress_01", "s_f_y_hooker_01", "s_f_y_hooker_02", "s_f_y_hooker_03", "s_m_m_janitor", "s_m_m_lathandy_01", "s_m_m_lifeinvad_01", "s_m_m_linecook", "s_m_m_lsmetro_01", "s_f_m_maid_01", "s_m_m_mariachi_01", "s_m_m_marine_01", "s_m_m_marine_02", "s_m_y_marine_01", "s_m_y_marine_02", "s_m_y_marine_03", "s_m_y_armymech_01", "s_f_y_migrant_01", "s_m_m_migrant_01", "s_m_y_mime", "s_m_m_movalien_01", "s_m_m_movspace_01", "s_f_y_movprem_01", "s_m_m_movprem_01", "s_m_m_paramedic_01", "s_m_y_pestcont_01", "s_m_m_pilot_01", "s_m_m_pilot_02", "s_m_y_pilot_01", "s_m_m_postal_01", "s_m_m_postal_02", "s_m_m_prisguard_01", "s_m_y_prismuscl_01", "s_m_y_prisoner_01", "s_m_y_robber_01", "s_m_m_scientist_01", "s_f_y_scrubs_01", "s_m_m_security_01", "s_m_m_chemsec_01", "s_m_y_devinsec_01", "s_m_m_highsec_01", "s_m_m_highsec_02", "s_m_m_ciasec_01", "s_f_m_shop_high", "s_f_y_shop_low", "s_m_y_shop_mask", "s_f_y_shop_mid", "s_f_y_stripper_01", "s_f_y_stripper_02", "s_f_y_stripperlite", "s_m_m_strperf_01", "s_m_m_strpreach_01", "s_m_m_strvend_01", "s_m_y_strvend_01", "s_f_m_sweatshop_01", "s_f_y_sweatshop_01", "s_m_m_trucker_01", "s_m_m_ups_01", "s_m_m_ups_02", "s_m_y_uscg_01", "s_m_y_valet_01", "s_m_y_waiter_01", "s_m_y_winclean_01", "s_m_y_xmech_01", "s_m_y_xmech_02" },
	{ "< Special >", "Air Hostess (F)", "Air Worker (M)", "AmmuNation City (M)", "AmmuNation Country (M)", "Armoured 1 (M)", "Armoured 2 (M)", "Autopsy (M)", "Autoshop 1 (M)", "Autoshop 2 (M)", "Barman (M)", "Barman, Country (M)", "Bartender (F)", "Baywatch (F)", "Baywatch (M)", "Blackops 1 (M)", "Blackops 2 (M)", "Bouncer (M)", "Busboy (M)", "Busker (M)", "Chef (M)", "Clown (M)", "Construct 1 (M)", "Construct 2 (M)", "Cop, LSPD (F)", "Cop, LSPD (M)", "Cop, Highway (M)", "Cop, NOOSE (M)", "Cop, Ranger (F)", "Cop, Ranger (M)", "Cop, Sheriff (F)", "Cop, Sheriff (M)", "Cop, Snow (M)", "Dealer (M)", "Dockwork M (M)", "Dockwork Y (M)", "Doctor (M)", "Doorman (M)", "Devin Weston Service 1 (M)", "Devin Weston Service 2 (M)", "Factory 1 (F)", "Factory 1 (M)", "FIB Office 1 (M)", "FIB Office 2 (M)", "Fireman (M)", "Gaffer (M)", "Garbage (M)", "Gardener (M)", "Gen Transport (M)", "Grip (M)", "Hairdresser (F)", "Hairdresser (M)", "Hooker 1 (F)", "Hooker 2 (F)", "Hooker 3 (F)", "Janitor (M)", "Latino Handyman (M)", "Life Invader (M)", "Linecook (M)", "LS Metro (M)", "Maid (F)", "Mariachi (Mexican man) (M)", "Marine M 1 (M)", "Marine M 2 (M)", "Marine Y 1 (M)", "Marine Y 2 (M)", "Marine Y 3 (M)", "Marine. Mechanics (M)", "Migrant (F)", "Migrant (M)", "Mime (M)", "Movie, Alien (M)", "Movie, Space Ranger (M)", "Movie Premier (F)", "Movie Premier (M)", "Paramedic (M)", "Pest Control  (M)", "Pilot M 1 (M)", "Pilot M 2 (M)", "Pilot Y 1 (M)", "Postal 1 (M)", "Postal 2 (M)", "Prison Guard (M)", "Prison Muscle (M)", "Prisoner (M)", "Robber (M)", "Scientist (M)", "Scrubs (F)", "Security 1 (M)", "Security Chem (M)", "Security Devin (M)", "Security High 1 (M)", "Security High 2 (M)", "Security ICA (M)", "Shop High-end (F)", "Shop Low-end (F)", "Shop Mask (M)", "Shop Mid-end (F)", "Stripper 1 (F)", "Stripper 2 (F)", "Stripper Lite (F)", "Street Performer (M)", "Street Preach (M)", "Street Vendor Middle (M)", "Street Vendor Young (M)", "Sweatshop M (F)", "Sweatshop Y (F)", "Trucker (M)", "Ups 1 (M)", "Ups 2 (M)", "US Coast Guard (M)", "Valet (M)", "Waiter (M)", "Windows Cleaner (M)", "X Mechanics 1 (M)", "X Mechanics 2 (M)" },

	// 14 Unique
	{ "_unique", "u_m_y_abner", "u_m_m_aldinapoli", "u_m_y_hippie_01", "u_m_y_antonb", "u_m_y_baygor", "u_m_o_finguru_01", "u_m_y_chip", "u_f_y_comjane", "u_m_y_zombie_01", "u_m_m_griff_01", "u_m_y_guido_01", "u_m_y_imporage", "u_m_m_jesus_01", "u_m_y_justin", "u_m_y_mani", "u_m_m_markfost", "u_f_m_miranda", "u_f_o_moviestar", "u_f_y_princess", "u_m_y_pogo_01", "u_f_y_poppymich", "u_m_y_rsranger_01", "u_m_m_partytarget", "u_m_m_willyfist", "u_m_y_babyd", "u_m_m_bankman", "u_m_m_bikehire_01", "u_f_y_bikerchic", "u_m_y_burgerdrug_01", "u_f_m_corpse_01", "u_f_y_corpse_01", "u_f_y_corpse_02", "u_m_y_cyclist_01", "u_m_m_fibarchitect", "u_m_y_fibmugger_01", "u_m_m_filmdirector", "u_m_o_filmnoir", "u_m_m_glenstank_01", "u_m_y_gunvend_01", "u_f_y_hotposh_01", "u_f_y_jewelass_01", "u_m_m_jewelsec_01", "u_m_m_jewelthief", "u_m_y_militarybum", "u_f_y_mistress", "u_m_y_paparazzi", "u_m_m_rivalpap", "u_m_y_party_01", "u_m_y_prisoner_01", "u_m_y_proldriver_01", "u_f_o_prolhost_01", "u_m_m_prolsec_01", "u_f_m_promourn_01", "u_m_m_promourn_01", "u_m_y_sbike", "u_m_m_spyactor", "u_f_y_spyactress", "u_m_y_staggrm_01", "u_m_o_taphillbilly", "u_m_y_tattoo_01", "u_m_o_tramp_01" },
	{ "< Unique >", "Abner Fitch, Theodore Bickford", "Al Di Napoli", "Andy Moon, Hippie", "Anton Beaudelaire", "Baygor (Epsilon)", "Bill Binder, Financial Guru", "Chip, John Cohn", "Com Jane", "Graham, Zombie", "Griff, Racist Uncle Sam", "Guido", "Impotent Rage", "Jesus, Jesse", "Justin", "Mani, Mariachi", "Mark Fostenburg", "Miranda Cowan", "Pamela Drake, Movie Star", "Princess Georgina", "Pogo The Monkey", "Poppy Mitchell", "Space Rangers (Republican)", "Tahir Javan", "Willy Love Fist", "Baby D", "Bankman", "Bike Hire", "Biker Chick", "Burger Drug", "Corpse Middle", "Corpse Young 1", "Corpse Young 2", "Cyclist", "FIB Architect", "FIB Mugger", "Film Director", "Film Noir", "Glenstank", "Gun Vendor", "Hot Posh", "Jeweller Assistance", "Jeweller Security", "Jeweller Thief", "Military Bum", "Mistress", "Paparazzi", "Paparazzi, Rival", "Party in Chumash", "Prisoner", "Prologue Driver", "Prologue Hostage", "Prologue L Security", "Prologue Mourner (F)", "Prologue Mourner (M)", "Sport Biker", "Spy Actor", "Spy Actress", "Stag Do Running Man", "Tap Hillbilly", "Tattoo", "Tramp" },

	// 16 Popular
	{ "_popular", "a_f_y_topless_01", "a_f_y_beach_01", "s_m_m_movalien_01", "u_m_y_rsranger_01", "u_m_m_jesus_01", "u_m_y_zombie_01" },
	{ "< Popular >", "Topless", "Beach (F)", "Alien", "Space Rangers (Republican)", "Jesus", "Zombie" }
};

std:: vector <std::vector <char*>> ipl_database {
	{ // New Yankton - to add
		"prologue_DistantLights", "prologue_grv_torch", "prologue_LODLights", "prologue_m2_door",
		"prologue_occl", "prologue01", "prologue01c", "prologue01d",
		"prologue01e", "prologue01f", "prologue01g", "prologue01h",
		"prologue01i", "prologue01j", "prologue01k", "prologue01z",
		"prologue02", "prologue03", "prologue03_grv_cov", "prologue03_grv_dug",
		"prologue03_grv_fun", "prologue03b", "prologue04", "prologue04_cover",
		"prologue04b", "prologue05", "prologue05b", "prologue06",
		"prologue06_int", "prologue06_pannel", "prologue06b", "prologuerd", "prologuerdb"
	},
	{ // New Yankton - to remove
		
	},
	{ // Heist carrier - to add
		"hei_carrier", "hei_Carrier_int1", "hei_Carrier_int2", "hei_Carrier_int3", "hei_Carrier_int4", "hei_Carrier_int5",
		"hei_Carrier_int6", "hei_carrier_DistantLights", "hei_carrier_LODLights"
	},
	{

	},
	{ // Heist Yacht
		"smboat", "hei_yacht_heist", "hei_yacht_heist_enginrm", "hei_yacht_heist_Lounge",
		"hei_yacht_heist_Bridge", "hei_yacht_heist_Bar", "hei_yacht_heist_Bedrm"
	},
	{

	},
	{ // Life Invader
		"facelobby"
	},
	{
		"facelobbyfake"
	},
	{ // Hospital
		"RC12B_Destroyed", "RC12B_HospitalInterior"
	},
	{
		"RC12B_Default", "RC12B_Fixed"
	},
	{ //Jewel Store
		"post_hiest_unload"
	},
	{
		"jewel2fake", "bh1_16_refurb"
	},
	{ // Morgue
		"Coroner_Int_on", "coronertrash"
	},
	{
		"Coroner_Int_off"
	},
	{ // Cluckin bell
		"CS1_02_cf_onmission1", "CS1_02_cf_onmission2", "CS1_02_cf_onmission3", "CS1_02_cf_onmission4"
	},
	{
		"CS1_02_cf_offmission"
	}
};

std::vector <std::vector <menuList_coord>> teleportLocations{
	{
		{ "Places" },
		{ "Marker" },
		{ "Forward" },
		{ "Airport - Airstrip", -1336.000f, -3044.000f, 13.900f },
		{ "Altruist Camp Radio Tower", -1002.000f, 4842.000f, 280.000f },
		{ "Jetsam", 760.400f, -2943.200f, 5.800f },
		{ "Lighthouse", 3430.990f, 5174.220f, 43.500f },
		{ "In the Atmosphere", -74.942f, -818.635f, 10800.000f },
		{ "Mt. Chiliad - Jump", 430.204f, 5614.734f, 766.168f },
		{ "Mt. Gordo", 2876.984f, 5911.455f, 370.000f },
		{ "Mt. Josiah", -1212.987f, 3848.685f, 491.000f },
		{ "Paleto Bay Beach", 178.330f, 7041.822f, 1.867f },
		{ "Playboy Mansion", -1464.000f, 182.000f, 55.000f },
		{ "Raton Canyon", -589.532f, 4395.390f, 18.148f },
		{ "Vespucci Beach", -1600.090f, -1041.890f, 13.021f },
		{ "Windfarm", 2354.000f, 1830.300f, 101.100f }
	},
	{
		{ "Hideout/Fun" },
		{ "Marker" },
		{ "Forward" },
		{ "Avi Hideout", -2177.440f, 5182.596f, 16.475f },
		{ "Comedy Club", 377.088f, -991.869f, -97.604f },
		{ "Construction Site - Crane (1)", -167.982f, -1001.930f, 296.206f },
		{ "Construction Site on building", -147.593f, -964.695f, 254.133f },
		{ "Military Base Control Tower", -2356.094f, 3248.645f, 101.451f },
		{ "Mineshaft, Great Chaparral", -598.000f, 2096.000f, 131.000f },
		{ "Pacific Standard Bank Vault", 255.582f, 217.690f, 102.683f },
		{ "Paleto Bay - Bank", -104.207f, 6469.265f, 32.627f },
		{ "Paleto Bay - Lookout", -179.984f, 6150.478f, 42.637f },
		{ "Police Station", 441.209f, -983.114f, 31.690f },
		{ "Raton Canyon Train Tracks", -530.675f, 4534.996f, 89.046f },
		{ "Vanilla Unicorn DJ Booth", 123.000f, -1281.000f, 30.000f }
	},
	{
		{ "Glitch" },
		{ "Marker" },
		{ "Forward" },
		{ "Ammunation - Gun range", 22.873f, -1073.880f, 29.797f },
		{ "Ammunation - Office", 12.455f, -1110.260f, 29.797f },
		{ "LSPD Char Creator", 402.668f, -1003.000f, -98.004f },
		{ "Garage wall", 220.600f, -1006.760f, -99.000f }
	},
	{
		{ "Neighbour" },
		{ "Marker" },
		{ "Forward" },
		{ "Eclipse Towers, Apt 31", -790.000f, 336.000f, 207.000f },
		{ "Eclipse Towers, Apt 40", -764.000f, 321.000f, 220.000f },
		{ "Eclipse Towers, Apt 5", -790.000f, 336.000f, 159.000f },
		{ "Eclipse Towers, Apt 9", -764.000f, 321.000f, 175.000f },
		{ "Richards Majestic, Apt. 4", -906.000f, -375.000f, 85.000f },
		{ "Richards Majestic, Apt. 51", -922.000f, -375.000f, 109.000f }
	},

	{
		{ "IPL Required Map" },
		{ "Marker" },
		{ "Forward" },
		{ "Remove all IPL" },
		{ "North Yankton", 3217.697f, -4834.826f, 112.815f },
		{ "Heist Aircraft Carrier", 3084.730f, -4770.709f, 16.262f },
		{ "Heist Yacht", -2043.974f, -1031.582f, 11.981f },
		{ "LiveInvader", -1083.590f, -257.594f, 38.885f },
		{ "Hospital (Destroyed)", 356.8f, -590.1f, 43.3f },
		{ "Jewel Store", -630.4f, -236.7f, 40.0f },
		{ "Morgue", 244.9f, -1374.7f, 39.5f },
		{ "Cluckin bell Factory", -72.68752f, 6253.72656f, 31.08991f }
	},

	{
		{ "Singleplayer" },
		{ "Marker" },
		{ "Forward" },
		{ "Franklin - New", 7.415f, 535.549f, 176.028f },
		{ "Franklin - Old", -14.969f, -1436.443f, 32.119f },
		{ "Michael - Amanda", -815.000f, 179.000f, 77.000f },
		{ "Trevor - Floyd's", -1159.034f, -1521.180f, 10.633f },
		{ "Trevor - Trailer", 1976.000f, 3821.000f, 34.000f },
		{ "Trevor - V.U.", 97.271f, -1290.994f, 30.269f }
	},
	{
		{ "Safehouse online" },
		{ "Marker" },
		{ "Forward" },
		{ "Las Lagunas Boulevard, 4", 11.482f, 81.433f, 79.000f },
		{ "Apartment Medium-end", 347.000f, -999.000f, -99.000f },
		{ "Garage - 10 Cars", 234.000f, -1004.000f, -98.000f },
		{ "Garage - 6 Cars", 204.952f, -994.910f, -99.000f },
		{ "Weazel Plaza Entrance", -914.272f, -457.109f, 39.650f },
		{ "Weazel Plaza, Apt. 101", -891.000f, -450.000f, 125.000f },
		{ "Weazel Plaza, Apt. 26", -895.000f, -436.000f, 95.000f },
		{ "Weazel Plaza, Apt. 70", -907.000f, -440.000f, 121.000f }
	},
	{
		{ "Transport" },
		{ "Marker" },
		{ "Forward" },
		{ "Airport - Helipad", -1102.290f, -2894.520f, 13.947f },
		{ "Impound Lot", 391.475f, -1637.975f, 29.315f },
		{ "Los Santos Customs", -367.734f, -130.859f, 39.117f },
		{ "McKenzie Field Runway", 2121.700f, 4796.300f, 41.100f },
		{ "Military - Jet Spawn", -2148.350f, 3031.762f, 32.810f },
		{ "Mors Mutual Impound", -222.198f, -1185.850f, 23.029f },
		{ "Pegasus Aircraft, LSIA", -1098.490f, -2415.405f, 14.000f },
		{ "Sandy Shores Airfield", 1747.000f, 3273.700f, 41.100f }
	}
};




std::vector< std::vector <LPCSTR> > vehicleModels = {
	// Super
	{ "_super",
	"Adder", "Bullet", "Cheetah", "Entityxf", "Infernus", "Osiris", "Turismor", "Vacca", "Voltic", "Zentorno" },

	{ "Supers",
	"Adder", "Bullet", "Cheetah", "Entity XF", "Infernus", "Osiris", "Turismor", "Vacca", "Voltic", "Zentorno" },

	// Sports
	{ "_sports",
	"Ninef", "Ninef2", "Alpha", "Banshee", "Buffalo", "Buffalo2", "Buffalo3", "Carbonizzare", "Comet2", "Coquette", "Elegy2", "Feltzer2",
	"Furoregt", "Fusilade", "Futo", "Jester", "Jester2", "Khamelion", "Kuruma", "Kuruma2", "Massacro",
	"Massacro2", "Penumbra", "Rapidgt", "Rapidgt2", "Sultan", "Surano" },
	
	{ "Sports",
	"9f", "9f Cabrio (Convertible)", "Alpha", "Banshee", "Buffalo", "Buffalo S", "Buffalo S (Liverly)", "Carbonizzare (Convertible)", "Comet", "Coquette", "Elegy RH8", "Feltzer",
	"Furore GT", "Fusilade", "Futo", "Jester", "Jester (Liverly)", "Khamelion", "Kuruma", "Kuruma (Armored)", "Massacro",
	"Massacro (Liverly)", "Penumbra", "Rapid GT", "Rapid GT (Convertible)", "Sultan", "Surano (Convertible)" },

	// Sports Classic
	{ "_sports_classic",
	"Casco", "Coquette2", "Jb700", "Manana", "Monroe", "Peyote", "Pigalle", "Btype", "Stinger", "Stingergt", "Feltzer3",
	"Tornado", "Tornado2", "Tornado3", "Tornado4", "Ztype" },

	{ "Sports Classic",
	"Casco", "Coquette Classic", "JB 700", "Manana", "Monroe", "Peyote", "Pigalle", "Roosevelt", "Stinger", "Stinger GT", "Stirling GT",
	"Tornado", "Tornado (Convertible)", "Tornado (Rusty)", "Tornado (Rusty Topless)", "Z-Type" },

	// Motobikes
	{ "_motobikes",
	"Akuma", "Bagger", "Bati", "Bati2", "Carbonrs", "Daemon", "Double", "Enduro", "Faggio2", "Hakuchou", "Hexer",
	"Innovation", "Lectro", "Nemesis", "Pcj", "Ruffian", "Sanchez2", "Sanchez", "Sovereign", "Thrust", "Vader" },

	{ "Motobikes", 
	"Akuma", "Bagger", "Bati 801", "Bati 801 (Liverly)", "Carbon RS", "Daemon", "Double-T", "Enduro", "Faggio", "Hakuchou", "Hexer", 
	"Innovation", "Lectro", "Nemesis", "PCJ 600", "Ruffian", "Sanchez", "Sanchez (Liverly)", "Sovereign", "Thrust", "Vader" },

	// Bicycles
	{ "_bicycles",
	"Bmx", "Cruiser", "Fixter", "Scorcher", "Tribike2", "Tribike3", "Tribike" },

	{ "Bicycles",
	"BMX", "Cruiser", "Fixter", "Scorcher", "Endurex Race Bike", "Tri-Cycles Race Bike", "Whippet Race Bike" },

	// Muscles
	{ "_muscles",
	"Blade", "Buccaneer", "Dominator", "Dominator2", "Dukes2", "Dukes", "Gauntlet", "Gauntlet2", "Hotknife", "Phoenix",
	"Picador", "Ratloader", "Ratloader2", "Ruiner", "Sabregt", "Slamvan", "Slamvan2", "Stalion", "Stalion2", "Vigero",
	"Virgo", "Voodoo2" },

	{ "Muscles",
	"Blade", "Buccaneer", "Dominator", "Dominator (Liverly)", "Duke O'Death", "Dukes", "Gauntlet", "Gauntlet (Liverly)", "Hotknife", "Phoenix",
	"Picador", "Rat-Loader (Rusty)", "Rat-Truck", "Ruiner", "Sabre Turbo", "Slamvan", "Slamvan (The Lost)", "Stalion", "Stalion (Liverly)", "Vigero",
	"Virgo", "Voodoo (Rusty)" },

	// Coupes
	{ "_coupes",
	"Cogcabrio", "Exemplar", "F620", "Felon", "Felon2", "Jackal", "Oracle2", "Oracle", "Sentinel2", "Sentinel",
	"Windsor", "Zion", "Zion2" },
	
	{ "Coupes",
	"Cognoscenti Cabrio (Convertible)", "Exemplar", "F620", "Felon", "Felon GT (Convertible)", "Jackal", "Oracle XS", "Oracle", "Sentinel (Convertible)", "Sentinel XS",
	"Windsor", "Zion", "Zion Cabrio (Convertible)" },

	// Sedans
	{ "_sedans",
	"Asea", "Asea2", "Asterope", "Emperor", "Emperor2", "Emperor3", "Fugitive", "Glendale", "Ingot", "Intruder",
	"Premier", "Primo", "Regina", "Romero", "Schafter2", "Schwarzer", "Stanier", "Stratum", "Stretch", "Superd",
	"Surge", "Tailgater", "Warrener", "Washington" },

	{ "Sedans",
	"Asea", "Asea (North Yankton)", "Asterope", "Emperor", "Emperor (Rusty)", "Emperor (North Yankton)", "Fugitive", "Glendale", "Ingot", "Intruder",
	"Premier", "Primo", "Regina", "Romero Hearse", "Schafter", "Schwarzer", "Stanier", "Stratum", "Stretch", "Super Diamond",
	"Surge", "Tailgater", "Warrener", "Washington" },

	// Compacts
	{ "_compacts",
	"Blista", "Blista2", "Blista3", "Dilettante", "Dilettante2", "Issi2", "Panto", "Prairie", "Rhapsody" },

	{ "Compacts",
	"Blista", "Blista Compatc", "Blista Compact (Liverly)", "Dilettante", "Dilettante (Merryweather Patrol)", "Issi (Convertible)", "Panto", "Prairie", "Rhapsody" },

	// SUVs
	{ "_suvs",
	"Baller", "Baller2", "Bjxl", "Cavalcade", "Cavalcade2", "Dubsta", "Dubsta2", "Fq2", "Granger", "Gresley",
	"Habanero", "Huntley", "Landstalker", "Mesa", "Mesa2", "Mesa3", "Patriot", "Radi", "Rocoto", "Seminole",
	"Serrano" },

	{ "SUVs",
	"Baller", "Baller 2nd-Gen", "BeeJay XL", "Cavalcade", "Cavalcade 2nd-Gen", "Dubsta", "Dubsta 2nd-Gen", "FQ 2", "Granger", "Gresley",
	"Habanero", "Huntley S", "Landstalker", "Mesa", "Mesa (North Yankton)", "Mesa (Off-road)", "Patriot", "Radius", "Rocoto", "Seminole",
	"Serrano" },

	// Vans
	{ "_vans",
	"Bison", "Bison2", "Bison3", "Bobcatxl", "Boxville", "Boxville2", "Boxville3", "Boxville4", "Burrito3", "Burrito", "Burrito2",
	"Burrito4", "Burrito5", "Gburrito", "Camper", "Journey", "Minivan", "Paradise", "Pony", "Pony2",
	"Rumpo", "Rumpo2", "Speedo", "Speedo2", "Surfer", "Surfer2", "Taco", "Youga" },

	{ "Vans",
	"Bison", "Bison (McGill-Olsen)", "Bison (The Mighty Bush)", "Bobcat XL", "Boxville (Water & Power)", "Boxville (GO Postal)", "Boxville (Humane)", "Boxville (Post OP)",
	"Burrito", "Burrito (Various)", "Burrito (Bugstars)", "Burrito (McGill-Olsen)", "Burrito (North Yankton)", "Burrito (The Lost)", "Camper", "Journey", "Minivan", "Paradise", 
	"Pony (Various)", "Pony (Smoke-Water)", "Rumpo", "Rumpo (Deludamol)", "Speedo", "Speedo (Clown)", "Surfer", "Surfer (Old)", "Taco Van", "Youga" },

	// Not Drivable
	{ "_not_drivable",
	"Cablecar", "Metrotrain", "Freight", "Freightcar", "Freightcont1", "Freightcont2", "Freightgrain", "Tankercar", "Freighttrailer", "Proptrailer" },

	{ "Not Drivable",
	"Cablecar", "Metro Train", "Freight", "Freight Car", "Freight Container 1", "Freight Container 2", "Freight Grain", "Freight Oil Tank", "Freight Trailer", "Prop Trailer" },

	// Components
	{ "_components",
	"Armytanker", "Armytrailer", "Armytrailer2", "Boattrailer", "Docktrailer", "Raketrailer", "Tanker", "Tanker2", "Tr2", "Tr3", "Tr4", "Trailerlogs", "Trailers",
	"Trailers2", "Trailers3", "Trailersmall", "Trflat", "Tvtrailer", "Baletrailer", "Graintrailer" },

	{ "Components",
	"Army Tanker", "Army Trailer", "Army Trailer 2", "Boat Trailer", "Dock Trailer", "Rake Trailer", "Tanker", "Tanker 2", "TR 2", "TR 3", "TR 4", "Trailer Logs", "Trailers",
	"Trailers 2", "Trailers 3", "Trailer Small", "TR flat", "TV Trailer", "Bale Trailer", "Grain Trailer" },

	// Commercials
	{ "_commercials",
	"Benson", "Biff", "Hauler", "Mule", "Mule2", "Packer", "Phantom", "Pounder", "Stockade", "Stockade3" },

	{ "Commercials",
	"Benson", "Biff", "Hauler", "Mule (Various)", "Mule (Various) 2", "Packer", "Phantom", "Pounder", "Stockade (gruppe6)", "Stockade (North Yankton)" },

	// Services
	{ "_services",
	"Airbus", "Bus", "Coach", "Pbus", "Rentalbus", "Taxi", "Tourbus", "Trash", "Trash2" },

	{ "Services",
	"Airport Bus", "Bus", "Coach (Dashound)", "Prison Bus", "Rental Shutter Bus", "Taxi", "Tourbus", "Trashmaster", "Trashmaster (Heist)" },

	// Utilities
	{ "_utilities",
	"Airtug", "Caddy2", "Caddy", "Docktug", "Forklift", "Mower", "Ripley", "Sadler", "Sadler2", "Scrap",
	"Towtruck", "Towtruck2", "Tractor", "Tractor2", "Tractor3", "Utillitruck", "Utillitruck2", "Utillitruck3" },

	{ "Utilities",
	"Airtug", "Caddy", "Caddy (Golf)", "Docktug", "Forklift", "Lawn Mower", "Ripley", "Sadler", "Sadler (North Yankton)", "Scrap Truck",
	"Towtruck", "Towtruck (Small)", "Tractor (Rusty)", "Tractor", "Tractor (North Yankton)", "Utillity Truck (Crane)", "Utillity Truck", "Utillity Truck (Small)" },

	// Industrials
	{ "_industrials",
	"Bulldozer", "Cutter", "Dump", "Flatbed", "Handler", "Mixer", "Mixer2", "Rubble", "Tiptruck", "Tiptruck2" },

	{ "Industrials",
	"Bulldozer", "Cutter", "Dump", "Flatbed", "Handler", "Mixer", "Mixer 2", "Rubble", "Tiptruck", "Tiptruck 2" },

	// Emergency
	{ "_emergency",
	"Ambulance", "Fbi", "Fbi2", "Firetruk", "Lguard", "Police2", "Police", "Police3", "Police4", "Policeb",
	"Policeold1", "Policeold2", "Policet", "Pranger", "Riot", "Sheriff", "Sheriff2" },

	{ "Emergency",
	"Ambulance", "FIB Buffalo", "FIB Granger", "Fire Truck", "Lifeguard Granger", "Police Cruiser Buffalo", "Police Cruiser Stainer", "Police Cruiser Interceptor", "Police Cruiser (Unmarked)", "Police Bike",
	"Police Rancher (North Yankton)", "Police Cruiser (North Yankton)", "Police Transporter Burrito", "Park Ranger Granger", "Police Riot", "Sheriff Cruiser Stainer", "Sheriff Granger" },

	// Off-Roads
	{ "_off-Roads",
	"Bfinjection", "Bifta", "Blazer", "Blazer2", "Blazer3", "Bodhi2", "Dloader", "Dubsta3", "Dune", "Dune2",
	"Guardian", "Insurgent", "Insurgent2", "Kalahari", "Marshall", "Monster", "Rancherxl", "Rancherxl2", "Rebel", "Rebel2",
	"Sandking", "Sandking2", "Technical" },

	{ "Off-Roads",
	"Injection", "Bifta", "Blazer", "Blazer (Lifeguard)", "Blazer (Hot Rod)", "Bodhi", "Duneloader", "Dubsta 6x6", "Dune Buggy", "Space Docker",
	"Guardian", "Insurgent Pick-up", "Insurgent", "Kalahari", "Marshall", "Monster", "Rancher XL", "Rancher XL (North Yankton)", "Rebel (Rusty)", "Rebel",
	"Sandking XL", "Sandking SWB", "Technical" },

	// Military
	{ "_military",
	"Barracks", "Barracks3", "Barracks2", "Crusader", "Rhino" },

	{ "Military",
	"Barracks", "Barracks 3", "Barracks Semi", "Crusader", "Rhino Tank" },

	// Watercrafts
	{ "_watercrafts",
	"Dinghy", "Dinghy2", "Dinghy3", "Jetmax", "Marquis", "Predator", "Seashark", "Seashark2", "Speeder", "Squalo",
	"Submersible", "Submersible2", "Suntrap", "Tropic" },

	{ "Watercrafts",
	"Dinghy", "Dinghy 2-Seater", "Dinghy (Stealth)", "Jetmax", "Marquis", "Police Predator", "Seashark", "Seashark (Lifeguard)", "Speeder", "Squalo",
	"Submersible", "Kraken", "Suntrap", "Tropic" },

	// Aircrafts
	{ "_aircrafts",
	"Besra", "Blimp", "Blimp2", "Cargoplane", "Cuban800", "Dodo", "Duster", "Hydra", "Jet",
	"Luxor", "Luxor2", "Mammatus", "Miljet", "Lazer", "Shamal", "Stunt", "Titan", "Velum", "Velum2", "Vestra" },

	{ "Aircrafts",
	"Besra", "Blimp (Atomic)", "Blimp (Xero)", "Cargo Plane", "Cuban 800", "Dodo", "Duster", "Hydra", "Jet",
	"Luxor", "Luxor Deluxe", "Mammatus", "Miljet", "P-996 LAZER", "Shamal", "Mallard", "Titan", "Velum", "Velum 5-Seater", "Vestra" },

	// Helicopter
	{ "_helicopters",
	"Annihilator", "Buzzard2", "Buzzard", "Cargobob", "Cargobob2", "Cargobob3", "Frogger", "Frogger2", "Maverick",
	"Polmav", "Savage", "Skylift", "Swift", "Swift2", "Valkyrie" },

	{ "Helicopters",
	"Annihilator", "Buzzard", "Buzzard Attack Chopper", "Cargobob", "Cargobob (Jetsam)", "Cargobob (TPI)", "Frogger", "Frogger (FIB/TPI)", "Maverick",
	"Mavrick (Emergency)", "Savage", "Skylift", "Swift", "Swift Deluxe", "Valkyrie" }
};

std::vector <LPCSTR> weaponOnlineNames = {
	"WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_SNSPISTOL", "WEAPON_HEAVYPISTOL", "WEAPON_VINTAGEPISTOL", "WEAPON_FLAREGUN",
	"WEAPON_MICROSMG", "WEAPON_SMG", "WEAPON_ASSAULTSMG", "WEAPON_COMBATPDW",
	"WEAPON_MG", "WEAPON_COMBATMG",
	"WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_SPECIALCARBINE", "WEAPON_BULLPUPRIFLE",
	"WEAPON_SNIPERRIFLE", "WEAPON_HEAVYSNIPER", "WEAPON_MARKSMANRIFLE",
	"WEAPON_KNIFE", "WEAPON_NIGHTSTICK", "WEAPON_HAMMER", "WEAPON_BAT", "WEAPON_GOLFCLUB", "WEAPON_CROWBAR", "WEAPON_DAGGER", "WEAPON_HATCHET",
	"WEAPON_PUMPSHOTGUN", "WEAPON_SAWNOFFSHOTGUN", "WEAPON_ASSAULTSHOTGUN", "WEAPON_BULLPUPSHOTGUN", "WEAPON_HEAVYSHOTGUN",
	"WEAPON_GRENADELAUNCHER", "WEAPON_RPG", "WEAPON_MINIGUN", "WEAPON_HOMINGLAUNCHER",
	"WEAPON_GRENADE", "WEAPON_STICKYBOMB", "WEAPON_SMOKEGRENADE", "WEAPON_MOLOTOV", "WEAPON_PETROLCAN", "WEAPON_PROXMINE"
};

std::vector <LPCSTR> weaponRestrictedNames = {
	"WEAPON_STUNGUN",
	"WEAPON_BZGAS", "WEAPON_SNOWBALL", "WEAPON_FIREEXTINGUISHER", "WEAPON_BALL", "WEAPON_FLARE",
	"WEAPON_MUSKET", "WEAPON_GUSENBERG",
	"WEAPON_RAILGUN", "WEAPON_FIREWORK"
};


#endif