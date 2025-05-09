#pragma once

#include <stdlib.h>//malloc，动态内存分配函数，防止栈内存不足导致溢出
#include<iostream>
using namespace std;

/*手牌价值结构体(价值、几手)*/
struct HandCardValue
{
	int value;//价值
	int needPly;//手数
};

/*
牌型组合结构(牌型张数、价值、主牌最小点数，带牌1，带牌2，带牌3，带牌4)
该结构为了方便计算出牌策略
（初始值 牌型张数-1；价值0；最小点数-1；）
*/
struct CardGroup
{
	int cardTypeId = -1;//牌型张数
	int value=0;//价值
	int minCard=-1;//主牌点数最小一位
	int take1 = -1;//带牌
	int take2 = -1;
	int take3 = -1;
	int take4 = -1;
};

/* 为了配合拆牌策略
各种组合牌对应的牌点数和数量
*/
class OwnCardGroup
{
public:
	int sum=0;//总牌型数
	int rocket=0, bomb=0, single=0, two=0, three=0, threeOne=0, threeTwo=0, linkSingle=0, linkTwo=0, linkThree=0;
	int linkThreeSingle=0, linkThreeTwo=0, fourSingle=0, fourTwo=0;
	CardGroup rocket1;				//最多1个火箭
	CardGroup bomb2[5];				//最多5个炸弹
	CardGroup single3[20];	//最多20单牌
	CardGroup double4[10];	//最多10对牌
	CardGroup three5[6];	//最多6三条
	CardGroup threeOne6[5];	//最多5三带一单
	CardGroup threeDouble6[4];//最多4三带一对
	CardGroup linkSingle7[4];//最多4单顺，最长12
	CardGroup linkDouble8[3];//最多3连对，最长20
	CardGroup linkThree9[3];//最多3三顺，最长20
	CardGroup linkThreeSingle10[2];//最多2三顺带单，
	CardGroup linkThreeDouble10[2];//最多2三顺带对
	CardGroup fourSingle11[3];//最多3四带二单
	CardGroup fourDouble11[2];//最多2四带二对 
public:
	//清除某个卡牌组合
	void clearOneCard(struct CardGroup *cardGroup)
	{
		cardGroup->cardTypeId = -1;
		cardGroup->minCard = -1;
		cardGroup->take1 = cardGroup->take2 = cardGroup->take3 = cardGroup->take4 = -1;
		cardGroup->value = -1;
	}
	//初始化，将全部组合牌置空
	void Init()
	{
		sum = 0;
		//各种牌组合为0；
		rocket = bomb = single = two = three = threeOne = threeTwo = linkSingle = 0;
		linkTwo = linkThree = linkThreeSingle = linkThreeTwo = fourSingle = fourTwo = 0;
		clearOneCard(&rocket1);//火箭
		for (int i = 0; i < 5; i++)//炸弹
			clearOneCard(&bomb2[i]);
		for (int i = 0; i < 20; i++)//单牌
			clearOneCard(&single3[i]);
		for (int i = 0; i < 10; i++)//对牌
			clearOneCard(&double4[i]);
		for (int i = 0; i < 6; i++)//三条
			clearOneCard(&three5[i]);
		for (int i = 0; i < 5; i++)//三带一单
			clearOneCard(&threeOne6[i]);
		for (int i = 0; i < 4; i++)//三带一对
			clearOneCard(&threeDouble6[i]);
		for (int i = 0; i < 4; i++)//单顺
			clearOneCard(&linkSingle7[i]);
		for (int i = 0; i < 3; i++)//双顺
			clearOneCard(&linkDouble8[i]);
		for (int i = 0; i < 3; i++)//三顺
			clearOneCard(&linkThree9[i]);
		for (int i = 0; i < 2; i++)//三顺带单
			clearOneCard(&linkThreeSingle10[i]);
		for (int i = 0; i < 2; i++)//三顺带双
			clearOneCard(&linkThreeDouble10[i]);
		for (int i = 0; i < 3; i++)//四带二单
			clearOneCard(&fourSingle11[i]);
		for (int i = 0; i < 2; i++)//四带二对
			clearOneCard(&fourDouble11[i]);
	}
	//整理组合牌，大的放前面
	void Tidy()
	{
		if (rocket1.cardTypeId != -1) rocket = 1;
		for(int i=0;i<5;i++)//炸弹
			for (int j = i + 1; j < 5; j++)
				if (bomb2[i].minCard < bomb2[j].minCard)
				{
					CardGroup tCard = bomb2[i];
					bomb2[i] = bomb2[j]; bomb2[j] = tCard;
				}
		for (int i = 0; i < 20; i++)//单牌
			for (int j = i + 1; j < 20; j++)
				if (single3[i].minCard < single3[j].minCard)
				{
					CardGroup tCard = single3[i];
					single3[i] = single3[j]; single3[j] = tCard;
				}
		for (int i = 0; i < 10; i++)//对牌
			for (int j = i + 1; j < 10; j++)
				if (double4[i].minCard < double4[j].minCard)
				{
					CardGroup tCard = double4[i];
					double4[i] = double4[j]; double4[j] = tCard;
				}
		for (int i = 0; i < 6; i++)//三条
			for (int j = i + 1; j < 6; j++)
				if (three5[i].minCard < three5[j].minCard)
				{
					CardGroup tCard = three5[i];
					three5[i] = three5[j]; three5[j] = tCard;
				}
		for (int i = 0; i < 5; i++)//三带一单
			for (int j = i + 1; j < 5; j++)
				if (threeOne6[i].minCard < threeOne6[j].minCard)
				{
					CardGroup tCard = threeOne6[i];
					threeOne6[i] = threeOne6[j]; threeOne6[j] = tCard;
				}
		for (int i = 0; i < 4; i++)//三带一对
			for (int j = i + 1; j < 4; j++)
				if (threeDouble6[i].minCard < threeDouble6[j].minCard)
				{
					CardGroup tCard = threeDouble6[i];
					threeDouble6[i] = threeDouble6[j]; threeDouble6[j] = tCard;
				}
		for (int i = 0; i < 4; i++)//单顺
			for (int j = i + 1; j < 4; j++)
				if (linkSingle7[i].minCard < linkSingle7[j].minCard)
				{
					CardGroup tCard = linkSingle7[i];
					linkSingle7[i] = linkSingle7[j]; linkSingle7[j] = tCard;
				}
		for (int i = 0; i < 3; i++)//双顺
			for (int j = i + 1; j < 3; j++)
				if (linkDouble8[i].minCard < linkDouble8[j].minCard)
				{
					CardGroup tCard = linkDouble8[i];
					linkDouble8[i] = linkDouble8[j]; linkDouble8[j] = tCard;
				}
		for (int i = 0; i < 3; i++)//三顺
			for (int j = i + 1; j < 3; j++)
				if (linkThree9[i].minCard < linkThree9[j].minCard)
				{
					CardGroup tCard = linkThree9[i];
					linkThree9[i] = linkThree9[j]; linkThree9[j] = tCard;
				}
		for (int i = 0; i < 2; i++)//三顺带单
			for (int j = i + 1; j < 2; j++)
				if (linkThreeSingle10[i].minCard < linkThreeSingle10[j].minCard)
				{
					CardGroup tCard = linkThreeSingle10[i];
					linkThreeSingle10[i] = linkThreeSingle10[j]; linkThreeSingle10[j] = tCard;
				}
		for (int i = 0; i < 2; i++)//三顺带双
			for (int j = i + 1; j < 2; j++)
				if (linkThreeDouble10[i].minCard < linkThreeDouble10[j].minCard)
				{
					CardGroup tCard = linkThreeDouble10[i];
					linkThreeDouble10[i] = linkThreeDouble10[j]; linkThreeDouble10[j] = tCard;
				}
		for (int i = 0; i < 3; i++)//四带二单
			for (int j = i + 1; j < 3; j++)
				if (fourSingle11[i].minCard < fourSingle11[j].minCard)
				{
					CardGroup tCard = fourSingle11[i];
					fourSingle11[i] = fourSingle11[j]; fourSingle11[j] = tCard;
				}
		for (int i = 0; i < 2; i++)//四带二对
			for (int j = i + 1; j < 2; j++)
				if (fourDouble11[i].minCard < fourDouble11[j].minCard)
				{
					CardGroup tCard = fourDouble11[i];
					fourDouble11[i] = fourDouble11[j]; fourDouble11[j] = tCard;
				}
		sum = 0;

		sum += bomb + rocket + single + two + three + threeOne + threeTwo + linkSingle + linkTwo + linkThree;
		sum += linkThreeSingle + linkThreeTwo + fourSingle + fourTwo;
	}
};

/*
手牌类(自己使用)
为了方便计算手牌价值
*/
class HandCard
{
public:
	int onHandCard[21];//手牌序列，值为牌的编号,初始值-1，，数组大小为21
	int CardPointNum[14] = { 0 };//各种牌点数的数量，数组大小为14
	int sumNum;//手牌总张数,初始值0
	int value;//目前手牌价值,初始值0

	CardGroup PutCardGroup;//要出的牌的牌型组合
	int PutCard[21];//要出的牌型序列，值为牌编号,数组大小为21 

	int PutAnyCard = -1;//是否可以出任意牌  1出任意牌，0被动出牌，-1错误；用来判断调用主动策略还是被动策略
	int tableTypeCount = -1;//当前桌面牌型张数
	int tableMainPoint = -1;//当前桌面主牌（最小）点数

public:
	//清空手牌（全部赋值为-1）、牌点数数组、总张数、价值
	void ClearHandCard() {
		for (int i = 0; i < 21; i++)
			onHandCard[i] = -1;
		for (int i = 0; i < 14; i++)
			CardPointNum[i] = 0;
		sumNum = 0;
		value = 0;
	}
	//清空出牌序列、出牌牌型结构体
	void ClearPutCard() {
		for (int i = 0; i < 21; i++)
			PutCard[i] = -1;
		PutCardGroup.cardTypeId = -1;
		PutCardGroup.value = 0;
		PutCardGroup.minCard = -1;
		PutCardGroup.take1 = PutCardGroup.take2 = PutCardGroup.take3 = PutCardGroup.take4 = -1;//带牌初始化
	}
	//根据onHandCard[]计算手牌总张数
	void CalSumNum() {
		sumNum = 0;
		for (int i = 0; onHandCard[i] > -1; i++)
			sumNum++;
	}
	//根据onHandCard[]计算牌点数
	void CalPointNum() {
		for (int i = 0; i < 14; i++)//清空
			CardPointNum[i] = 0;
		for (int i = 0; onHandCard[i] > -1; i++)//计算
			CardPointNum[onHandCard[i] / 4]++;
	}
	//根据手牌计算各牌点数、手牌总数
	void ArrangeHandCard() {
		CalPointNum();//计算各种牌点数
		CalSumNum();//计算手牌数
	}
	//手牌类初始化函数
	void InIt()
	{
		ClearHandCard();//清空手牌
		ClearPutCard();//清空出牌序列
		PutAnyCard = -1;//初始化为 -1
		tableTypeCount = -1;
		tableMainPoint = -1;
	}
};

/*
大致手牌情况类，用来记录被人的牌，进一步推测自己的策略
*/
class AboutCard
{
public:
	int sum;//手牌剩余总数,初始值 17
	int surCardPoint[14];//剩余手牌点数  可以知道地主底牌,初始值 0
	int putCardPoint[14];//已打出手牌点数,初始值 0

public:
	//初始化
	void Init()
	{
		sum = 17;
		for (int i = 0; i < 14; i++)
			putCardPoint[i] = 0;
		for (int i = 0; i < 14; i++)
			surCardPoint[i] = 0;
	}
	//根据手牌序列计算已出牌点数
	void CalPutCardPoint(int card[])
	{
		for (int i = 0; card[i] >= 0; i++)
		{
			putCardPoint[card[i] / 4]++;//记录
			if (surCardPoint[card[i] / 4] > 0)//剔除
				surCardPoint[card[i] / 4]--;
			sum--;//总数--
		}
	}
};
//斗地主结构体（游戏全局）
struct Ddz
{
	int  iStatus;			//引擎状态-1错误,0结束,1开始
	char sCommandIn[80];	//通信输入内容
	char sCommandOut[80];	//通信输出内容
	char sVer[80];			//协议版本号
	char sName[80];			//参赛选手称呼
	int iRoundNow;			//当前局次
	int iRoundTotal;		//每轮总局数
	int iTurnNow;			//当前轮次
	int iTurnTotal;			//总轮数
	int iLevelUp;			//晋级选手数
	int iScoreMax;			//封顶分数
	int iTime;              //应答时间限制

	char cDir;				//本玩家方位编号,默认为B,也可能是A C
	char cLandlord;			//地主玩家方位编号，可以根据地主方位判断队友等位置
	char cWinner;			//胜利者方位编号
	int iBid[3];			//叫牌过程  ABC玩家分别对应坐标0 1 2
	int iBmax;				//当前叫牌数，值域{0,1,2,3}
	int iOTmax;				//当前出牌手数（出了多少手牌），为了记录iOnTable[162][21]
	int iOnHand[21];		//手中牌（所有值初始化为-1）,值为牌的编号
	HandCard handCardInfor;    //手牌信息类
	int iOnTable[250][21];	//已经打出去的牌（所有值初始化为-2）每行是一手牌，以-1结尾，Pass记为-1 由250增至1000ver2020.1
	char iOnPlayId[162];       //记录每次出牌的玩家编号，方便找出是谁打的牌,初始值为 E，表示error
	int iToTable[21];		//己方或对方 打出或要出 的牌
	int allCardOnTable[14] = {0}; //统计所有已经打出的牌
	int formation;          //阵容确定 1.【地 AI 友】 2.【农 AI 农】 3.【友 AI 地】
	int fnohope;            //友方报单/双时无能为力为其赢的标记（1不管队友，自由出牌）
	AboutCard upCard, lowCard; //上家和下家手牌的大致情况,(自己不一定是B方)

	int iVoid;				//闲暇并行计算参数
	int iLef[3];			//本局底牌
	int iLastPassCount;		//当前桌面连续PASS数（值域[0,2],初值2，正常出牌取0，一家PASS取1，两家PASS取2）
	int iLastTypeCount;		//当前桌面牌型张数,牌型编号+（两位）牌数,（值域[0,1108],初值0，iLastPassCount=0时更新值，=1时保留原值，=2时值为0）
	int iLastMainPoint;		//当前桌面主牌点数（值域[0,15],初值-1，iLastPassCount=0时更新值，，=1时保留原值，=2时值为-1）
};

/*------------------------------------函数声明-------------------------*/
int CountCards(int iCards[]);//计算多少张牌
void SortById(int iCards[]);//按牌编码（大小）升序排列
int	AnalyzeMainPoint(int iCards[]);//计算主牌最小点数,弃牌返回-1，
void SortByMain(int iCards[]);//按管牌主要因素升序排列
int	AnalyzeTypeCount(int iCards[]);//按管牌主要因素升序排列
void SortByMuch(int iCards[]);//按主牌(同点数牌)编码升序排列,将牌多的放在前面，以便找出主牌最小点数
//自己加函数
int FindFourSame(int max, int card[], OwnCardGroup& cardGroup);//根据句牌点数找四张相同的,并记录
int FindSanShun(int max, int card[], OwnCardGroup& ownCardGroup);//根据牌点数找三顺并记录,
int FindShuangShun(int max, int card[], OwnCardGroup& ownCardGroup);//根据牌点数找双顺并记录
int FindDanShun(int max, int card[], OwnCardGroup& ownCard);//根据点数找单顺
int FindSanZhang(int max, int card[], OwnCardGroup& ownCard);//根据牌点数找三张
int FindDuiPai(int max, int card[], OwnCardGroup& ownCard);//根据牌点数找对牌
void ChaiCard(int card[], OwnCardGroup& cardGroup);//拆牌函数,根据牌点数拆牌,并保存
//测试函数
void CheckChaiCard(struct Ddz* ddz);//输出查看拆牌后各种牌型

//判断牌型
int IsType0Pass(int iCs[]);//判断出牌类型是否为弃权(没有牌)
int IsType1Rocket(int iCs[]);//判断出牌类型是否为火箭
int IsType2Bomb(int iCs[]);//判断出牌类型是否为炸弹
int	IsType3Single(int iCs[]);//判断出牌类型是否为单牌
int	IsType4Double(int iCs[]);//判断出牌类型是否为对牌
int	IsType5Three(int iCs[]);//判断出牌类型是否为三条
int IsType6ThreeOne(int iCs[]);//判断出牌类型是否为三带一单
int IsType6ThreeDouble(int iCs[]);//判断出牌类型是否为三带一对
int IsType7LinkSingle(int iCs[]);//判断出牌类型是否为单顺
int IsType8LinkDouble(int iCs[]);//判断出牌类型是否为连对
int	IsType9LinkThree(int iCs[]);//判断出牌类型是否为三顺
int	IsType10LinkThreeSingle(int iCs[]);//判断三顺带单，返回1是，0不是
int	IsType10LinkThreeDouble(int	iCs[]);//判断三顺带对，返回1是，0不是
int IsType11FourSingle(int iCs[]);//判断出牌类型是否为四带二单
int IsType11FourDouble(int iCs[]);//判断出牌类型是否为四带二对
/*------------------------------------函数声明-------------------------*/



//计算多少张牌
int CountCards(int iCards[])
{
	int iCount = 0;
	while (iCards[iCount] > -1)
		iCount++;
	return iCount;
}

//按牌编码（大小）升序排列
void SortById(int iCards[])
{
	for (int i = 0; iCards[i] >= 0; i++)
	{
		for (int j = i + 1; iCards[j] >= 0; j++)
			if (iCards[i] > iCards[j])
			{
				int iTemp = iCards[i];
				iCards[i] = iCards[j];
				iCards[j] = iTemp;
			}
	}
}

//计算主牌最小点数,弃牌返回-1，
int	AnalyzeMainPoint(int iCards[])
{
	if (IsType0Pass(iCards))//弃牌
		return -1;
	SortByMuch(iCards);
	return iCards[0] / 4;
}

//判断出牌类型是否为弃权(没有牌)
int IsType0Pass(int iCs[])
{
	int iCount;
	iCount = CountCards(iCs);
	if (iCount == 0)//没有牌，即表示弃牌，pass
		return 1;
	return 0;
}

//判断出牌类型是否为火箭
int IsType1Rocket(int iCs[])
{
	if ((iCs[2] == -1) && (iCs[0] + iCs[1] == 52 + 53))//只有两张牌并且是大小王
		return 1;
	return 0;
}

//判断出牌类型是否为炸弹
int IsType2Bomb(int iCs[])
{
	if (4 != CountCards(iCs))//不是四张牌
		return 0;
	if ((iCs[4] == -1) &&
		(iCs[0] / 4 != -1 && //防止牌是空的
			iCs[0] / 4 == iCs[1] / 4 && iCs[0] / 4 == iCs[2] / 4 && iCs[0] / 4 == iCs[3] / 4))
		return 1;
	return 0;
}

//判断出牌类型是否为单牌
int	IsType3Single(int iCs[])
{
	if (iCs[0] != -1 && iCs[1] == -1)//只有一张牌
		return 1;
	return 0;
}

//判断出牌类型是否为对牌
int	IsType4Double(int iCs[])
{
	if (IsType1Rocket(iCs))//如果是火箭，则返回错误
		return 0;
	if (iCs[0] / 4 == iCs[1] / 4 && iCs[0] != -1 && iCs[2] == -1)//只有两张牌，并且是一样点数的
		return 1;
	return 0;
}

//判断出牌类型是否为三条
int	IsType5Three(int iCs[])
{
	//只有三张非空牌，并且是一样的点数
	if (iCs[0] != -1 &&
		iCs[0] / 4 == iCs[1] / 4 && iCs[0] / 4 == iCs[2] / 4 
		&& iCs[3] == -1)
		return 1;
	return 0;
}

//判断出牌类型是否为三带一单
int IsType6ThreeOne(int iCs[])
{
	if (IsType2Bomb(iCs) || 4 != CountCards(iCs))//如果是炸弹或者不是四张牌
		return 0;//排除了四张相同的情况
	SortByMuch(iCs);
	if (iCs[0] / 4 == iCs[1] / 4 && iCs[0] / 4 == iCs[2] / 4 )
		return 1;
	return 0;
}

//判断出牌类型是否为三带一对
int IsType6ThreeDouble(int iCs[])
{
	if (5 != CountCards(iCs))//不是五张
		return 0;
	SortByMuch(iCs);
	if (iCs[0] / 4 == iCs[1] / 4 && iCs[0] / 4 == iCs[2] / 4)
		if (iCs[3] / 4 == iCs[4] / 4)//最多只有四张一样的牌
			return 1;
	return 0;
}

//判断出牌类型是否为单顺
int IsType7LinkSingle(int iCs[])
{
	int iCount = CountCards(iCs);
	if (iCount >= 5)
	{
		SortById(iCs);
		for (int i = 1; iCs[i] >= 0; i++)
			if (iCs[i - 1] / 4 + 1 != iCs[i] / 4 || iCs[i] >= 48)//相邻两张牌相差不是1，2和王不参与顺子
				return 0;
		return 1;
	}
	return 0;
}

//判断出牌类型是否为连对
int IsType8LinkDouble(int iCs[])
{
	int iCount = CountCards(iCs);
	if (iCount < 6 || iCount % 2 != 0)
		return 0;
	SortById(iCs);   //把iCs牌排序
	for (int i = 1; i < iCount; i++)
	{
		if (iCs[i] >= 48) return 0;//双顺不包含2和王
		//判断i是单数还是双数
		if (i % 2!=0)
		{
			//如果i是单数，则第i张牌的编码编码会等于上一张牌编码
			if (iCs[i] / 4 != iCs[i - 1] / 4)
				return 0;
		}
		else
		{
			//如果i是双数，则第i张牌的编码编码会等于上一张牌编码+1  
			if (iCs[i] / 4 != iCs[i - 1] / 4 + 1)
				return 0;
		}
	}
	return 1;
}

//判断出牌类型是否为三顺
int	IsType9LinkThree(int iCs[])
{ 
	int iCount = CountCards(iCs);
	if (iCount < 6 || iCount % 3 != 0)
		return 0;
	int i, iMinNum, iMaxNum;   //iMinNum 为 iCs 最小点数,iMaxNum 为 iCs 最大点数
	SortById(iCs);   //把iCs牌排序
	iMinNum = iCs[0] / 4;
	iMaxNum = iMinNum + (iCount / 3) - 1;

	int iTempArr[14];//初始化数组iTempArr用来记录 3 - A 每个点数的张数
	for (int h = 0; h < 14; h++)
		iTempArr[h] = 0;

	for (i = 0; i < iCount; i++)
	{
		//判断iCs[i]是否在有效点数范围内
		if (iCs[i] >= 48 || iCs[i] / 4 < iMinNum || iCs[i] / 4 > iMaxNum)//三顺不包含2和王
		{
			return 0;
		}
		iTempArr[iCs[i] / 4]++;
	}
	for (i = iMinNum; i <= iMaxNum; i++)
	{
		//判断是否每个有效点数都为3张牌
		if (iTempArr[i]!=3)
		{
			return 0;
		}
	}
	return 1;
}

//判断三顺带单，返回1是，0不是
int	IsType10LinkThreeSingle(int iCs[])
{
	int iCount = CountCards(iCs);
	if (iCount < 8 || iCount % 4 != 0)
		return 0;
	int iTempArr[14] ;//记录牌点数
	for (int i = 0; i < 14; i++)
		iTempArr[i] = 0;
	int iMinNum, iMaxNum;//iMinNum 为 iCs 最小点数,iMaxNum 为 iCs 最大点数
	SortByMuch(iCs);   //排序
	iMinNum = iCs[0]/4;
	iMaxNum = iMinNum + iCount / 4 - 1;
	for (int i = 0; i < iCount; i++)//统计牌的个数
		iTempArr[iCs[i] / 4]++;
	int t = 0;//统计单牌个数
	for (int i = 0; i <= 13; i++)
	{
		if (i >= iMinNum && i <= iMaxNum)//如果是三张的牌
		{
			if (iTempArr[i] != 3)
			{
				return 0;
			}
		}
		else//其他牌
		{
			if (iTempArr[i] == 1) t++;//如果是单牌
			else if (iTempArr[i] == 0) continue;//没有牌，继续下次循环
			else return 0;//不是三顺的牌，也不是单牌，返回错误
		}
	}
	if (t == iCount/4)//单牌数量符合
		return 1;
	return 0;
}

//判断三顺带对，返回1是，0不是
int	IsType10LinkThreeDouble(int	iCs[])
{
	int iCount = CountCards(iCs);
	if (iCount < 10 || iCount % 5 != 0)
		return 0;
	int iTempArr[14];
	for (int i = 0; i < 14; i++)
		iTempArr[i] = 0; 
	int iMinNum, iMaxNum;//iMinNum 为 iCs 最小点数,iMaxNum 为 iCs 最大点数
	SortByMuch(iCs);   //排序
	iMinNum = iCs[0] / 4;
	iMaxNum = iMinNum + iCount / 5 - 1;
	for (int i = 0; i < iCount; i++)//统计牌的个数
		iTempArr[iCs[i] / 4]++;
	int t = 0;//统计对牌的数量
	for (int i = 0; i <= 13; i++)
	{
		if (i >= iMinNum && i <= iMaxNum)//如果是三张的牌
		{
			if (iTempArr[i] != 3)
			{
				return 0;
			}
		}
		else//其他牌
		{	//不是对牌就是空牌，否则返回错误
			if (iTempArr[i] == 2) t++;
			else if (iTempArr[i] == 0) continue;
			else return 0;
		}
	}
	if (t == iCount / 5)//对牌数量符合
		return 1;
	return 0;
}

//判断出牌类型是否为四带二单
int IsType11FourSingle(int iCs[])
{
	int iCount = CountCards(iCs);
	if (iCount != 6)
		return 0;
	SortByMuch(iCs);  //同点数多牌的排在前面
	if (iCs[0] / 4 == iCs[1] / 4 && iCs[0] / 4 == iCs[2] / 4 && iCs[0] / 4 == iCs[3] / 4  //四张同牌
		&& iCs[4]/4!=iCs[5]/4 && iCs[4]/4!=iCs[0]/4 && iCs[5]/4!=iCs[0]/4)  //两张不同单牌
		return 1;
	return 0;
}

//判断出牌类型是否为四带二对
int IsType11FourDouble(int iCs[])
{
	int iCount = CountCards(iCs);
	if (iCount != 8)
		return 0;
	SortByMuch(iCs);  //同点数多牌的排在前面
	if (iCs[0] / 4 == iCs[1] / 4 && iCs[0] / 4 == iCs[2] / 4 && iCs[0] / 4 == iCs[3] / 4)  //有四
		if (iCs[4] / 4 == iCs[5] / 4 && iCs[6] / 4 == iCs[7] / 4)  //两个对子
			if(iCs[4]/4!=iCs[6]/4 && iCs[4]/4!=iCs[0]/4 && iCs[6]/4!=iCs[0]/4)//不同对子
			return 1;
	return 0;
}

/*	根据手牌序列计算 牌型张数（手牌数组）	错误 -1；*/
int	AnalyzeTypeCount(int iCards[])
{
	int iCount  = CountCards(iCards);//计算多少张牌

	if (IsType0Pass(iCards))//判断是是否为pass
		return 0 * 100 + iCount;
	if (IsType1Rocket(iCards))//判断是否为火箭
		return 1 * 100 + iCount;
	if (IsType2Bomb(iCards))//判断是否为炸弹
		return 2 * 100 + iCount;
	if (IsType3Single(iCards))//判断是否为单张牌
		return 3 * 100 + iCount;
	if (IsType4Double(iCards))//判断是否为对牌
		return 4 * 100 + iCount;
	if (IsType5Three(iCards))//判断是否为三条
		return 5 * 100 + iCount;
	if (IsType6ThreeOne(iCards))//判断是否为三带一张单排
		return 6 * 100 + iCount;
	if (IsType6ThreeDouble(iCards))//判断是否为三带二
		return 6 * 100 + iCount;
	if (IsType7LinkSingle(iCards))//判断是否为单顺
		return 7 * 100 + iCount;
	if (IsType8LinkDouble(iCards))//判断是否为双顺
		return 8 * 100 + iCount;
	if (IsType9LinkThree(iCards))//判断是否为三顺
		return 9 * 100 + iCount;
	if (IsType10LinkThreeSingle(iCards))//判断是否为三顺带单
		return 10 * 100 + iCount;
	if (IsType10LinkThreeDouble(iCards))//判断是否为三顺带对
		return 10 * 100 + iCount;
	if (IsType11FourSingle(iCards))//判断是否为 四带二单
		return 11 * 100 + iCount;
	if (IsType11FourDouble(iCards))//判断是否为 四带二双
		return 11 * 100 + iCount;

	return -1;
}

//按管牌主要因素升序排列（暂时没用）
void SortByMain(int iCards[])
{
	if (IsType0Pass(iCards))
		return;
	if (IsType1Rocket(iCards))
		return;
	if (IsType2Bomb(iCards))
		return;
	if (IsType3Single(iCards))
		return;
	if (IsType4Double(iCards))
		return;
	if (IsType5Three(iCards))
		return;
	if (IsType6ThreeOne(iCards))
		return;
	if (IsType6ThreeDouble(iCards))
		return;
	if (IsType7LinkSingle(iCards))
		return;
	if (IsType8LinkDouble(iCards))
		return;
	if (IsType9LinkThree(iCards))
		return;
	if (IsType10LinkThreeSingle(iCards))
		return;
	if (IsType10LinkThreeDouble(iCards))
		return;
	if (IsType11FourSingle(iCards))
		return;
	if (IsType11FourDouble(iCards))
		return;
	return;
}

//按主牌(同点数牌)编码升序排列,将牌多的放在前面，以便判断牌型
void SortByMuch(int iCards[])
{
	int i, j, k, n;

	// iTempArr[i][0]用来装点数为 i 有多少张牌，
	// iTempArr[i][1],iTempArr[i][2],iTempArr[i][3],iTempArr[i][4]用来装点数为 i 的牌的编码，
	int iTempArr[14][5];
	for (int h = 0; h < 14; h++)//将数组全部初始化为 -1
	{
		iTempArr[h][0] = 0;
		for (int hh = 1; hh < 5; hh++)
			iTempArr[h][hh] = -1;
	}
	for (i = 0; iCards[i] > -1; i++)//将牌按点数分类，并记录张数、每张编码
	{
		if (iCards[i] <= 53)//符合范围
		{
			iTempArr[iCards[i] / 4][++(iTempArr[iCards[i] / 4][0])] = iCards[i];
		}
	}
	n = 0;   //n为iCards的下标，重新将iTempArr中的数放入iCards中
	for (i = 0; iCards[i] > -1; i++)//清空手牌
		iCards[i] = -1;
	//先找出iTempArr一样的四张牌，若有则写入原数组iCards【】中，然后再寻找三张的，依次类推	
	for (i = 4; i > 0; i--)
	{
		for (j = 0; j <= 13; j++)
		{
			if (iTempArr[j][0] == i)    //判断该点数的牌是不是有 i 张
			{
				for (k = 1; k <= i; k++)    // 有的话，就把牌都放进iCards[ n ]中，然后 n++
				{
					iCards[n++] = iTempArr[j][k];
				}
			}
		}
	}
}

//根据句牌点数找炸弹的,并记录(10.10检查)
int FindFourSame(int max,int card[],OwnCardGroup& cardGroup)
{
	if (card[max] == 4)
	{
		cardGroup.bomb2[cardGroup.bomb].cardTypeId = 204;
		cardGroup.bomb2[cardGroup.bomb].minCard = max;
		cardGroup.bomb++;
		card[max] -= 4;
		return 1;
	}
	return 0;
}

//根据牌点数找三顺并记录,(10.10检查)
int FindSanShun(int max, int card[], OwnCardGroup& ownCardGroup)
{
	if (max <= 0) return 0;
	if (card[max] >= 3 && card[max - 1] >= 3)//
	{
		int min = max;
		for (; min >= 0; min--)
			if (card[min] < 3)
				break;
		//cout << "min:" << min << endl;
		ownCardGroup.linkThree9[ownCardGroup.linkThree].cardTypeId = 900 + 3 * (max - min);
		ownCardGroup.linkThree9[ownCardGroup.linkThree].minCard = min + 1;
		ownCardGroup.linkThree++;
		for (int i = min + 1; i <= max; i++)
			card[i] -= 3;
		return 1;
	}
	else return 0;
}

//根据牌点数找双顺并记录,(10.10检查)
int FindShuangShun(int max, int card[], OwnCardGroup& ownCardGroup)
{
	if (max < 2) return 0;//长度不够
	if (card[max] >= 2 && card[max - 1] >= 2 && card[max-2]>=2 )//
	{
		int min = max;
		for (; min >= 0; min--)
			if (card[min] < 2)
				break;
		ownCardGroup.linkDouble8[ownCardGroup.linkTwo].cardTypeId = 800 + 2 * (max - min);
		ownCardGroup.linkDouble8[ownCardGroup.linkTwo].minCard = min + 1;
		ownCardGroup.linkTwo++;
		for (int i = min + 1; i <= max; i++)
			card[i] -= 2;
		return 1;
	}
	else return 0;
}

//根据点数找单顺(10.10检查)
int FindDanShun(int max, int card[], OwnCardGroup& ownCard)
{
	if (max < 4) return 0;
	int min;
	for (min = max; min >= 0; min--)
		if (card[min] <= 0)
			break;
	if (max - min >= 5)
	{
		ownCard.linkSingle7[ownCard.linkSingle].cardTypeId = 700 + (max - min);
		ownCard.linkSingle7[ownCard.linkSingle].minCard = min + 1;
		ownCard.linkSingle++;
		for (int i = min + 1; i <= max; i++)
			card[i] -= 1;
		return 1;
	}
	else return 0;
}

//根据牌点数找三张(10.10检查)
int FindSanZhang(int max, int card[], OwnCardGroup& ownCard)
{
	if (card[max] >= 3)
	{
		ownCard.three5[ownCard.three].cardTypeId = 503;
		ownCard.three5[ownCard.three].minCard = max;
		ownCard.three++;
		card[max] -= 3;
		return 1;
	}
	else return 0;
}

//根据牌点数找对牌（10.10检查）
int FindDuiPai(int max, int card[], OwnCardGroup& ownCard)
{
	if (card[max] >= 2)
	{
		ownCard.double4[ownCard.two].cardTypeId = 402;
		ownCard.double4[ownCard.two].minCard = max;
		ownCard.two++;
		card[max] -= 2;
		return 1;
	}
	else return 0;
}

//拆牌函数,根据牌点数拆牌,并保存(10.10测试，完好)
void ChaiCard(int card[], OwnCardGroup& cardGroup)
{
	//先初始化
	cardGroup.Init();

	int key = 1, max = -1;

	while (key)
	{
		//判断手牌是否分完
		key = 0;
		for (int i = 0; i < 14; i++)
			if (card[i] > 0)
				key = 1;
		if (key == 0) break;
		//查找当前最大牌点数
		for(int i=13;i>=0;i--)
			if (card[i] > 0)
			{
				max = i; break;
			}

		if (card[13] == 2)//火箭
		{
			card[13] -= 2;
			cardGroup.rocket1.cardTypeId = 102;
			cardGroup.rocket1.minCard = 13;
			cardGroup.rocket = 1;
			continue;
		}
		else if (FindFourSame(max,card,cardGroup))//炸弹
		{
			continue;
		}
		if (FindSanShun(max, card, cardGroup))//三顺
		{
			continue;
		}
		if (FindShuangShun(max,card,cardGroup))//双顺
		{
			continue;
		}
		if (FindDanShun(max, card, cardGroup))//单顺
		{
			continue;
		}
		if (FindSanZhang(max, card, cardGroup))//三张
		{
			continue;
		}
		else if (FindDuiPai(max, card, cardGroup))//对牌
		{
			continue;
		}
		else {//单牌
			if (card[max] <= 0) continue;
			cardGroup.single3[cardGroup.single].cardTypeId = 301;
			cardGroup.single3[cardGroup.single].minCard = max;
			cardGroup.single++;
			card[max] -= 1;
		}
	}
	cardGroup.Tidy();//整理
}

//输出查看各种牌型(10.10测试，完好)
void CheckChaiCard(struct Ddz* ddz)
{
	cout << "手牌：";
	for (int i = 0; ddz->handCardInfor.onHandCard[i] > -1; i++)
		cout << ddz->handCardInfor.onHandCard[i] / 4 << " ";
	cout << endl;
	cout << "点数：";
	for (int i = 0; i < 14; i++)
		cout << ddz->handCardInfor.CardPointNum[i] << " ";
	OwnCardGroup ownCard;
	ChaiCard(ddz->handCardInfor.CardPointNum, ownCard);
	cout << endl;
	if (ownCard.rocket > 0)
	{
		cout << "火箭数：" << ownCard.rocket << endl;
	}
	if (ownCard.bomb > 0)
	{
		cout << "炸弹数：" << ownCard.bomb << endl;
		for (int i = 0; i < ownCard.bomb; i++)
		{
			cout << ownCard.bomb2[i].minCard << " ";
		}
		cout << endl;
	}
	if (ownCard.fourSingle > 0)
	{
		cout << "四带二单：" << ownCard.fourSingle << endl;
		for (int i = 0; i < ownCard.fourSingle; i++)
			cout << ownCard.fourSingle11[i].minCard << " "<<ownCard.fourSingle11[i].take1<<" "<< ownCard.fourSingle11[i].take2<<" |";
		cout << endl;
	}
	if (ownCard.fourTwo > 0)
	{
		cout << "四带二对：" << ownCard.fourTwo << endl;
		for (int i = 0; i < ownCard.fourTwo; i++)
			cout << ownCard.fourDouble11[i].minCard << " " << ownCard.fourDouble11[i].take1 << " " << ownCard.fourDouble11[i].take2 << " |";
		cout << endl;
	}
	if (ownCard.linkThreeSingle > 0)
	{
		cout << "三顺带单：" << ownCard.linkThreeSingle << endl;
		for (int i = 0; i < ownCard.linkThreeSingle; i++)
			cout << ownCard.linkThreeSingle10[i].minCard << " "<<ownCard.linkThreeSingle10[i].take1<<" "<<ownCard.linkThreeSingle10[i].take2<<"|";
		cout << endl;
	}
	if (ownCard.linkThreeTwo > 0)
	{
		cout << "三顺带对：" << ownCard.linkThreeTwo << endl;
		for (int i = 0; i < ownCard.linkThreeTwo; i++)
			cout << ownCard.linkThreeDouble10[i].minCard << " "<< ownCard.linkThreeDouble10[i].take1<<" "<< ownCard.linkThreeDouble10[i].take2<<"|";
		cout << endl;
	}
	if (ownCard.linkThree > 0)
	{
		cout << "三顺：" << ownCard.linkThree << endl;
		for (int i = 0; i < ownCard.linkThree; i++)
			cout << ownCard.linkThree9[i].cardTypeId<<" "<<ownCard.linkThree9[i].minCard << "| ";
		cout << endl;
	}
	if (ownCard.linkTwo > 0)
	{
		cout << "双顺：" << ownCard.linkTwo << endl;
		for (int i = 0; i < ownCard.linkTwo; i++)
			cout << ownCard.linkDouble8[i].minCard << " ";
		cout << endl;
	}
	if (ownCard.linkSingle > 0)
	{
		cout << "单顺：" << ownCard.linkSingle << endl;
		for (int i = 0; i < ownCard.linkSingle; i++)
			cout << ownCard.linkSingle7[i].minCard << " ";
		cout << endl;
	}
	if (ownCard.threeOne > 0)
	{
		cout << "三带一单：" << ownCard.threeOne << endl;
		for (int i = 0; i < ownCard.threeOne; i++)
			cout << ownCard.threeOne6[i].minCard << " 带牌 " <<ownCard.threeOne6[i].take1<<" ";
		cout << endl;
	}
	if (ownCard.threeTwo > 0)
	{
		cout << "三带一对：" << ownCard.threeTwo << endl;
		for (int i = 0; i < ownCard.threeTwo; i++)
			cout << ownCard.threeDouble6[i].minCard << " 带牌 " << ownCard.threeDouble6[i].take1 << " ";
		cout << endl;
	}
	if (ownCard.three > 0)
	{
		cout << "三张：" << ownCard.three << endl;
		for (int i = 0; i < ownCard.three; i++)
			cout << ownCard.three5[i].minCard  << " ";
		cout << endl;
	}
	if (ownCard.two > 0)
	{
		cout << "对牌：" << ownCard.two << endl;
		for (int i = 0; i < ownCard.two; i++)
			cout << ownCard.double4[i].minCard <<" ";
		cout << endl;
	}
	if (ownCard.single > 0)
	{
		cout << "单牌：" << ownCard.single << endl;
		for (int i = 0; i < ownCard.single; i++)
			cout << ownCard.single3[i].minCard << " ";
		cout << endl;
	}
}

