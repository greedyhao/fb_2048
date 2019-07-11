/****************************************
 * 文件名：2048game.h
 * 文件描述：该文件为2048游戏项目的头文件
 *   包含所用到的函数声明、宏定义，枚举等
 * 编辑人：王廷云
 * 编辑日期：2017-10-21
 * 修改日期：2018-2-10
*****************************************/

#ifndef _2048GAME_H_
#define _2048GAME_H_

#define   NR    4   // 游戏的维数

/* 按键输入枚举 */
enum KEY {
    UP,			// 上
    DOWN,		// 下
    LEFT,		// 左
    RIGHT,		// 右
    EXIT,		// 退出
    UNKNOW,		// 其它键
};

/*
 * 函数名：initGame
 * 功能：初始化2048游戏，该函数会对游戏界面数据进行初始化
 *       并产生两个随机数
 * 参数：需要初始化的游戏数据
 * 返回值：无
*/
void initGame(int data[NR][NR]);

/*
 * 函数名：showGame
 * 功能：显示游戏界面
 * 参数：需要显示的游戏数据
 * 返回值：无
*/
void showGame(int data[NR][NR]);

/*
 * 函数名：moveUp
 * 功能：把游戏数据上移
 * 参数：需要上移的游戏数据
 * 返回值：无
*/
void moveUp(int data[NR][NR]);

/*
 * 函数名：moveDown
 * 功能：把游戏数据下移
 * 参数：需要下移的游戏数据
 * 返回值：无
*/
void moveDown(int data[NR][NR]);

/*
 * 函数名：moveLeft
 * 功能：把游戏数据左移
 * 参数：需要左移的游戏数据
 * 返回值：无
*/
void moveLeft(int data[NR][NR]);

/*
 * 函数名：moveRight
 * 功能：把游戏数据右移
 * 参数：需要右移的游戏数据
 * 返回值：无
*/
void moveRight(int data[NR][NR]);

/*
 * 函数名：maxScore
 * 功能：获取游戏最高分
 * 参数：需要获取最高分的游戏数据
 * 返回值：返回游戏数据中的最大值
*/
int maxScore(int data[NR][NR]);

/*
 * 函数名：exitGame
 * 功能：游戏退出函数，直接退出当前游戏
 * 参数：无
 * 返回值：无
*/
void exitGame(void);

/*
 * 函数名：checkGameOver
 * 功能：检查游戏是否结束
 * 参数：需要检查的游戏数据
 * 返回值：游戏结束返回1，没有结束返回0
*/
int checkGameOver(int data[NR][NR]);

/*
 * 函数名：getInput
 * 功能：获取用户按键输入
 * 参数：无
 * 返回值：返回用户输入的对应按键
*/
int getInput(void);

/*
 * 函数名：getRand
 * 功能：在游戏数据中产生一个随机数，2的概率为80%，4的概率为20%
 * 参数：需要产生随机数的游戏数据
 * 返回值：无
*/
void getRand(int data[NR][NR]);

#endif  // _2048GAME_H_

