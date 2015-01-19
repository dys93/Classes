#pragma once

#include <string>

using namespace std;
//一律小写
static int shade_opacity = 40;
	//body的属性
static	float	angulardamping = 0.8f;
static	float	lineardamping = 1.2f;
static	float	speed = 175;
static	float	density = 0.01f;

	//图片资源
static  string pic_game_back_ground = "gameback.png";

enum GameState { g_begin, g_sel,  g_move1, g_move2, g_attack, g_end };


static	string	pig_purple_horse = "horse.png";
static	string	pig_purple_cow = "cow.png";
static	string pig_purple_snack = "snack.png";
static	string pic_purple_dragon = "dragon.png";

static string	pig_blue_horse = "horse.png";
static	string	pig_blue_cow = "cow.png";
static	string pig_blue_snack = "snack.png";
static	string pic_blue_dragon = "dragon.png";
//调试使用透明度设置
static int opac = 255;
	//
static	string *sprite_belongto = new string[2]{ "red", "blue" };
static	string *sprite_kind = new string[5]{ "cow", "horse", "snack", "dragon", "array"};
static	string *sprite_pic = new string[10]{ "cow", "horse", "snack", "dragon", "array",
		"cow2", "horse2", "snack2", "dragon2", "array" };
static string *sprite_pic_sleep = new string[2]{"sleep", "sleep2"};
static	double *sprite_scale = new double[10]{	0.8, 0.8, 0.8, 1, 1,
0.8, 0.8, 0.8, 1, 1, };
static	double *sprite_max_move = new double[5]{ 1, 2, 2, 5, 1.0 };
static	double *sprite_max_speed = new double[5]{ 1.0, 1.2, 1.0, 0, 1.0 };
static	int *sprite_sizex = new int[5]{ 25, 25, 25, 65, 10 };
static	int *sprite_sizey = new int[5]{ 25, 25, 25, 65, 10 };
static	int *sprite_max_blood = new int[5]{ 2, 1, 1, 5, 0 };
static double *sprite_break_shade = new double[5]{0.95, 1.0, 1.1, 1.5, 0.2};
static int *sprite_rotation = new int[10]{0, 0, 0, 0, 0, 1, 1, 1, 1, 1};

static int *sprite_menu_num = new int[5]{3,3,3,3,0};
static int *sprite_menu_x = new int[3]{-80,0,80};
static int *sprite_menu_y = new int[3]{80, 95, 80};

static double *sprite_menu_position_x = new double[10]{ 0.6,0.6,0.6,1.5,0,
										-0.6, -0.6, -0.6, -1.5, 0};
static double *sprite_menu_position_y = new double[10]{ 0.6, 0.6, 0.6, 1.5, 0,
-0.6, -0.6, -0.6, -1.5, 0};

static int *moneycost = new int[3]{100,200,200};




enum PrioGame { background, Sprite, SpriteSleep, SpriteMenu, SpriteDiePar, shade, Menu1, Toast, PlayerInfor, Menu2back, Menu2 };