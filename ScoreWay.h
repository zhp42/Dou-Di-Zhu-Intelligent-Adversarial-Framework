#pragma once
/*
赋值评估策略文件
目前，计算手牌价值函数和计算最优策略函数互相调用结合
*/
#include"DDZStruct.h"
#include<algorithm>

#define Rotation 6//赋值评分法中，每轮次的值，暂定
/*
7  过于激进，总是先出大牌，最后很可能因为牌小而不能赢
6 还是不怎么考虑后面小牌，2 k 10 8 ,主动牌出2         *********** 暂定

4 容易把组合牌拆散打  主动牌大王、22，会把对2拆成单2打   不好

关于叫分的建议：
	1、#define Rotation 6 高了，打牌激进，总是先出大牌，小牌留在后面
	2、#define Rotation 6 小了，过于保守，藏着大牌不出
	3、至于具体分值，可以参考上面的记录  或  自己测试；

	4、上午场可以相对激进一些，下午场要保守；
*/

using namespace std;

/* ========================函数声明============================*/
int CardTypeValue(int num, int minCard);//计算各种牌型的价值
void FindCardOnHandCard(int handCard[], int save[], int CardTypeCout, int minCard, int take1, int take2, int take3, int take4);
HandCardValue GetCardValue(HandCard& handCard);
void PutCardWay(HandCard& handCard);
void PutCardWayActive(HandCard& handCard);
void PutCardWayUnactive(HandCard& handCard);
int JudgeOneHand(int card[]);//根据牌的序列判断是不是一手牌
CardGroup JudgeOneHand2(int CardPointNum[]);//根据牌点数判断是不是一手牌
/* ========================函数声明============================*/


/*
根据手牌编码判断该牌是不是一手牌
是	返回牌型编号
空牌 0
否  -1
*/
int JudgeOneHand(int card[])//该牌的数组、大小牌（用于决定大小）
{
	if (IsType0Pass(card)) return 0;//没有牌
	if (IsType1Rocket(card)) return 1;//火箭
	if (IsType2Bomb(card)) return 2;//炸弹
	if (IsType3Single(card)) return 3;//单牌
	if (IsType4Double(card)) return 4;//对牌
	if (IsType5Three(card)) return 5;//三张
	if (IsType6ThreeDouble(card)) return 6;//三带对牌
	if (IsType6ThreeOne(card)) return 6;//三带单牌
	if (IsType7LinkSingle(card)) return 7;//单顺
	if (IsType8LinkDouble(card)) return 8;//双顺
	if (IsType9LinkThree(card)) return 9;//三顺
	if (IsType10LinkThreeSingle(card)) return 10; //三顺带单牌
	if (IsType10LinkThreeDouble(card)) return 10; //三顺带对牌
	if (IsType11FourSingle(card)) return 11;//四带二单
	if (IsType11FourDouble(card)) return 11;//四带二对

	return -1;
}

/*根据手牌点数判断是不是一手牌
返回牌型组合（牌型张数、价值，主牌最小点数）
错误类型时，牌型张数为 -1；
*/
CardGroup JudgeOneHand2(int CardPointNum[])
{
	CardGroup tCardGroup;//（初始值  牌型张数-1；最小点数-1；价值0；）
	tCardGroup.cardTypeId = -1;//初始值
	int sum = 0;
	for (int i = 0; i < 14; i++)
		sum += CardPointNum[i];
	//空牌
	if (sum == 0)
	{
		tCardGroup.cardTypeId = 0;//表示弃牌类型
		tCardGroup.value = 0;
	}
	//单牌
	else if (sum == 1)
	{
		tCardGroup.cardTypeId = 301;
		for (int i = 0; i < 14; i++)
			if (CardPointNum[i] == 1)
			{
				tCardGroup.minCard = i;
				tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
				break;
			}
	}
	//对牌、火箭
	else if (sum == 2)
	{
		for (int i = 0; i < 14; i++)
		{
			if (CardPointNum[i] == 2)
			{
				if (i < 13)//对牌
				{
					tCardGroup.cardTypeId = 402;
					tCardGroup.minCard = i;
					tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
					break;
				}
				else if (i == 13)//火箭
				{
					tCardGroup.cardTypeId = 102;
					tCardGroup.minCard = i;
					tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
					break;
				}
			}
		}
	}
	//三张
	else if (sum == 3)
	{
		for (int i = 0; i < 13; i++)//肯定不是王
			if (CardPointNum[i] == 3)
			{
				tCardGroup.cardTypeId = 503;
				tCardGroup.minCard = i;
				tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
				break;
			}
	}
	//炸弹、三带一单、
	else if (4 == sum)
	{
		for (int i = 0; i < 13; i++)//不包含王
		{
			if (CardPointNum[i] == 4)//炸弹
			{
				tCardGroup.cardTypeId = 204;
				tCardGroup.minCard = i;
				tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
				break;
			}
			if (CardPointNum[i] == 3)//三带一单
			{
				for (int j = 0; j < 14; j++)//可能有王
				{
					if (CardPointNum[j] == 1)
					{
						tCardGroup.cardTypeId = 604;
						tCardGroup.minCard = i;
						tCardGroup.take1 = j;
						tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
						break;
					}
				}
				break;
			}
		}
	}
	//三带一对、单顺
	else if (5 == sum)
	{
		for (int i = 0; i < 13; i++)//三带一对（不含王）
		{
			if (CardPointNum[i] == 3)
			{
				for (int j = 0; j < 14; j++)//含王
				{
					if (CardPointNum[j] == 2)
					{
						tCardGroup.cardTypeId = 605;
						tCardGroup.minCard = i;
						tCardGroup.take1 = j;
						tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
						break;
					}
				}
				break;
			}
		}
		for (int i = 0, pro = 0; i < 12; i++)//单顺(不包含2和王)
		{
			if (CardPointNum[i] == 1) pro++;
			else {
				if (pro >= 5 && sum == pro)
				{
					tCardGroup.cardTypeId = 700 + pro;
					tCardGroup.minCard = i - pro;
					tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
					break;
				}
				pro = 0;
			}
		}
	}
	//单顺、双顺、三顺、三顺带单、三顺带对、四带二单、四带二对
	else if (6 <= sum)
	{
		if (sum == 6)//四带二单
		{
			for (int i = 0; i < 13; i++)//不包含王
			{
				if (CardPointNum[i] == 4)
				{
					for (int j = 0; j < 13; j++)//一单(不用循环到14)
					{
						if (CardPointNum[j] == 1)
						{
							for (int k = j + 1; k < 14; k++)//二单
							{
								if (CardPointNum[k] == 1)
								{
									tCardGroup.cardTypeId = 1106;
									tCardGroup.minCard = i;
									tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
									tCardGroup.take1 = j;
									tCardGroup.take2 = k;
									break;
								}
							}
							break;
						}
					}
					break;
				}
			}
		}
		if (sum == 8)//四带二对
		{
			int t1 = -1, t2 = -1, four = -1;
			for (int i = 0; i < 14; i++)
			{
				if (CardPointNum[i] == 4) four = i;
				if (CardPointNum[i] == 2)
				{
					if (t1 == -1) t1 = i;
					else t2 = i;
				}
				if (four != -1 && t1 != -1 && t2 != -1)
				{
					tCardGroup.cardTypeId = 1108;
					tCardGroup.minCard = four;
					tCardGroup.take1 = t1;
					tCardGroup.take2 = t2;
					tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
					break;//及时跳出
				}
			}
		}
		if (sum % 5 == 0)//三顺带对牌
		{
			int pro = 0;
			for (int i = 0; i < 13; i++)//不包含王
			{
				if (CardPointNum[i] == 3) pro++;
				else {
					if (pro == sum / 5)
					{
						tCardGroup.minCard = i - pro;
						break;
					}
					pro = 0;
				}
			}
			if (pro == 2)//二连
			{
				for (int i = 0; i <= 12; i++)//一带，不用循环到13
				{
					if (CardPointNum[i] == 2)
					{
						for (int j = i + 1; j < 14; j++)//二带
						{
							if (CardPointNum[j] == 2)
							{
								tCardGroup.cardTypeId = 1010;
								tCardGroup.take1 = i;
								tCardGroup.take2 = j;
								tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
								break;
							}
						}
						break;
					}
				}
			}
			else if (pro == 3)//三连
			{
				for (int i = 0; i <= 11; i++)//一带，循环优化
				{
					if (CardPointNum[i] == 2)
					{
						for (int j = i + 1; j <= 12; j++)//二带
						{
							if (CardPointNum[j] == 2)
							{
								for (int k = j + 1; k <= 13; k++)//三带
								{
									if (CardPointNum[k] == 2)
									{
										tCardGroup.cardTypeId = 1015;
										tCardGroup.take1 = i;
										tCardGroup.take2 = j;
										tCardGroup.take3 = k;
										tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
										break;
									}
								}
								break;
							}
						}
						break;
					}
				}
			}
			else if (pro == 4)//四连
			{
				for (int i = 0; i <= 10; i++)//一带(循环优化)
				{
					if (CardPointNum[i] == 2)
					{
						for (int j = i + 1; j <= 11; j++)//二带
						{
							if (CardPointNum[j] == 2)
							{
								for (int k = j + 1; k <= 12; k++)
								{
									if (CardPointNum[k] == 2)//三带
									{
										for (int l = k + 1; l <= 13; l++)
										{
											if (CardPointNum[l] == 2)
											{
												tCardGroup.cardTypeId = 1020;
												tCardGroup.take1 = i;
												tCardGroup.take2 = j;
												tCardGroup.take3 = k;
												tCardGroup.take4 = l;
												tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
												break;
											}
										}
										break;
									}
								}
								break;
							}
						}
						break;
					}
				}
			}
		}
		if (sum % 4 == 0)//三顺带单牌
		{
			int pro = 0;
			for (int i = 0; i < 14; i++)
			{
				if (CardPointNum[i] == 3) pro++;
				else {
					if (pro == sum / 4)
					{
						tCardGroup.minCard = i - pro;
						break;
					}
					pro = 0;
				}
			}
			if (pro == 2)
			{
				for (int i = 0; i <= 12; i++)//一带（循环优化）
				{
					if (CardPointNum[i] == 1)
					{
						for (int j = i + 1; j <= 13; j++)//二带
						{
							if (CardPointNum[j] == 1)
							{
								tCardGroup.cardTypeId = 108;
								tCardGroup.take1 = i;
								tCardGroup.take2 = j;
								tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
								break;
							}
						}
						break;
					}
				}
			}
			else if (pro == 3)
			{
				for (int i = 0; i <= 11; i++)//一带（循环优化）
				{
					if (CardPointNum[i] == 1)
					{
						for (int j = i + 1; j <= 12; j++)//二带
						{
							if (CardPointNum[j] == 1)
							{
								for (int k = j + 1; k <= 13; k++)//三带
								{
									if (CardPointNum[k] == 1)
									{
										tCardGroup.cardTypeId = 1012;
										tCardGroup.take1 = i;
										tCardGroup.take2 = j;
										tCardGroup.take3 = k;
										tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
										break;
									}
								}
								break;
							}
						}
						break;
					}
				}
			}
			else if (pro == 4)
			{
				for (int i = 0; i <= 10; i++)//一带（循环优化）
				{
					if (CardPointNum[i] == 1)
					{
						for (int j = i + 1; j <= 11; j++)//二带
						{
							if (CardPointNum[j] == 1)
							{
								for (int k = j + 1; k <= 12; k++)
								{
									if (CardPointNum[k] == 1)//三带
									{
										for (int l = k + 1; l <= 13; l++)
										{
											if (CardPointNum[l] == 1)
											{
												tCardGroup.cardTypeId = 1016;
												tCardGroup.take1 = i;
												tCardGroup.take2 = j;
												tCardGroup.take3 = k;
												tCardGroup.take4 = l;
												tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
												break;
											}
										}
										break;
									}
								}
								break;
							}
						}
						break;
					}
				}
			}
		}
		if (sum % 3 == 0)//三顺
		{
			for (int i = 0, pro = 0; i < 12; i++)//不包含2和王
			{
				if (CardPointNum[i] == 3) pro++;
				else {
					if (pro == sum / 3)
					{
						tCardGroup.cardTypeId = 900 + 3 * pro;
						tCardGroup.minCard = i - pro;
						tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
						break;
					}
					pro = 0;
				}
			}
		}
		if (sum % 2 == 0)//双顺
		{
			for (int i = 0, pro = 0; i < 12; i++)//不包含2和王
			{
				if (CardPointNum[i] == 2) pro++;
				else {
					if (pro == sum / 2)
					{
						tCardGroup.cardTypeId = 800 + 2 * pro;
						tCardGroup.minCard = i - pro;
						tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
						break;
					}
					pro = 0;
				}
			}
		}
		for (int i = 0, pro = 0; i < 12; i++)//单顺  //不包含2和王
		{
			if (CardPointNum[i] == 1) pro++;
			else {
				if (pro == sum)
				{
					tCardGroup.cardTypeId = 700 + pro;
					tCardGroup.minCard = i - pro;
					tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
					break;
				}
				pro = 0;
			}
		}
	}

	return tCardGroup;
}

/*
根据牌型，返回对应的价值,错误类型返回-10000
（牌型张数，主牌最小点数）
1.牌力基础价值：我们认为10属于中等位置，即<10单牌价值为负，大于10的单牌价值为正
2.控手的价值定义：我们认为一次控手权可以抵消一次手中最小牌型，最小牌型（3）的价值为-7，即我们定义一次控手权的价值为7
3.单牌的价值定义：该牌的基础价值
4.对牌的价值定义：我们认为对牌与单牌价值相等（均可以被三牌带出）故其价值为该牌的基础价值
5.三牌的价值定义：
  三不带：     该牌的基础价值
  三带一：     我们认为通常带出去的牌价值一定无正价值故其价值为该牌的基础价值
  三带二：     我们认为通常带出去的牌价值一定无正价值故其价值为该牌的基础价值
6.四牌的价值定义：
  炸弹：       我们认为炸弹会享有一次控手权利且炸弹被管的概率极小，故其无负价值，非负基础价值+7
  四带二单：   我们认为四带二单管人与被管的概率极小，故其无负价值，其价值为非负基础价值/2（该值最大为6小于一个轮次7)
  四带二对：   我们认为四带二对管人与被管的概率极小，故其无负价值，其价值为非负基础价值/2（该值最大为6小于一个轮次7)
7.王炸的价值定义：已知炸2价值为15-3+7=19分，故王炸价值为20分。
8.顺子的价值定义：
  单顺：       我们认为单顺的价值等于其最大牌的单体价值，且2不参与顺子，故顺子的权值依次提升1
  双顺：       我们认为双顺的价值等于其最大牌的单体价值，且2不参与顺子，故顺子的权值依次提升1
  飞机不带：   由于飞机牌型管人与被管的概率极小，故其无负价值，其价值为非负基础价值/2（该值最大为6小于一个轮次7)
  飞机带双翅： 由于飞机牌型管人与被管的概率极小，故其无负价值，其价值为非负基础价值/2（该值最大为6小于一个轮次7)
  飞机带单翅： 由于飞机牌型管人与被管的概率极小，故其无负价值，其价值为非负基础价值/2（该值最大为6小于一个轮次7)

9.根据数值分布，我们暂定：   <10不叫分，10-14叫一分，15-19叫两分，20以上叫三分（未启用）
*/
int CardTypeValue(int num,int minCard)//牌型张数、主牌最小值
{
	int card = minCard + 3;//将牌点数转换为牌面值,以便计分
	if (0 == num)//0弃牌
		return 0;
	else if (102 == num)//1火箭
		return 20;
	else if (204 == num)//2炸弹
		return card - 3 + 7;
	else if (301 == num)//3单牌
		return card - 10;
	else if (402 == num)//4对牌
		return card - 10;
	else if (503 == num)//5三条
		return card - 10;
	else if (604 == num)//6三带单牌
		return card - 10;
	else if (605 == num)//6三带对牌
		return card - 10;
	else if (num > 700 && num < 800)//7单顺
		return (card +num%100-1) - 10 + 1;
	else if (num > 800 && num < 900)//8双顺
		return (card + (num % 100)/2 - 1) - 10 + 1;
	else if (num > 900 && num < 1000)//9三顺
		return ((card + (num % 100) / 3 - 1) - 3+1) / 2;
	else if (num > 1000 && num < 1100)//10三顺带牌连（飞机）
	{
		if ((num % 100) % 4 == 0)//三顺带单牌连
			return ((card + (num % 100) / 4 - 1) - 3 + 1) / 2;//  非负/2
		else if ((num % 100) % 5 == 0)//三顺带对牌
			return ((card + (num % 100) / 5 - 1) - 3 + 1) / 2;

		else return  0;          //-1非法牌型
	}
	else if (1106 == num)//11四带单牌
		return (card - 3) / 2;
	else if (1108 == num)//11四带对牌
		return (card - 3) / 2;
	else return  0;          //-1非法牌型
}

/*
根据牌型张数，在手牌中（值为牌编号）找出对应的牌
（手牌数组、保存结果数组、牌型编号、主牌最小点数、带牌1、带牌2、带牌3、带牌4）
带牌值为牌点数

有没有找到对应的牌都会返回（待优化）
*/
void FindCardOnHandCard(int handCard[], int save[], int CardTypeCout, int minCard,int take1,int take2,int take3,int take4 )
{
	for (int i = 0; i < 21; i++)//save数组初始化
		save[i] = -1;

	if (0 == CardTypeCout)//0弃牌
		return;
	else if (102 == CardTypeCout)//1火箭
	{
		for (int i = 0; handCard[i] > -1; i++)
		{
			if (handCard[i] / 4 == 13)
			{
				for (int j = i + 1; handCard[j] > -1; j++)
				{
					if (handCard[j] / 4 == 13)
					{
						save[0] = handCard[i];
						save[1] = handCard[j];
						break;
					}
				}
				break;
			}
		}
		return;
	}
	//2炸弹
	else if (204==CardTypeCout)
	{
		int n = 0;
		for (int i = 0; handCard[i] > -1; i++)
		{
			if (n >= 4) break;
			if (handCard[i] / 4 == minCard)
			{
				save[n++] = handCard[i];
			}
		}
		return;
	}
	//3单牌
	else if (301 == CardTypeCout)
	{
		for (int i = 0; handCard[i] > -1; i++)
		{
			if (handCard[i] / 4 == minCard)
			{
				save[0] = handCard[i];
				break;
			}
		}
		return;
	}
	//4对牌
	else if (402 == CardTypeCout)
	{
		int n = 0;
		for (int i = 0; handCard[i] > -1; i++)
		{
			if (n >= 2) break;
			if (handCard[i] / 4 == minCard)
			{
				save[n++] = handCard[i];
			}
		}
		return;
	}
	//5三条
	else if (503 == CardTypeCout)
	{
		int n = 0;
		for (int i = 0; handCard[i] > -1; i++)
		{
			if (n >= 3) break;
			if (handCard[i] / 4 == minCard)
			{
				save[n++] = handCard[i];
			}
		}
		return;
	}
	//6三带一单
	else if (604 == CardTypeCout)
	{
		int n = 0;
		for (int i = 0; handCard[i] > -1; i++)
		{
			if (n >= 3) break;
			if (handCard[i] / 4 == minCard)
			{
				save[n++] = handCard[i];
			}
		}
		for (int i = 0; handCard[i] > -1; i++)
			if (handCard[i] / 4 == take1)
			{
				save[n++] = handCard[i];
				break;
			}
		return;
	}
	//6三带一对
	else if (605 == CardTypeCout)
	{
		int n = 0;
		for (int i = 0; handCard[i] > -1; i++)
		{
			if (n >= 3) break;
			if (handCard[i] / 4 == minCard)
			{
				save[n++] = handCard[i];
			}
		}
		for (int i = 0; handCard[i] > -1; i++)
		{
			if (n >= 5) break;
			if (handCard[i] / 4 == take1)
			{
				save[n++] = handCard[i];
			}
		}
		return;
	}
	//7单顺
	else if (CardTypeCout > 700 && CardTypeCout < 800)
	{
		int n = 0;
		for (int i = minCard; i <= (CardTypeCout % 100 + minCard - 1);i++)
		{
			for (int j = 0; handCard[j] > -1; j++)
			{
				if (handCard[j] / 4 == i)
				{
					save[n++] = handCard[j];
					break;
				}
			}
		}
		return;
	}
	//8双顺
	else if (CardTypeCout > 800 && CardTypeCout < 900)
	{
		int n = 0;
		for (int i = minCard; i <= ((CardTypeCout % 100) / 2 + minCard - 1); i++)
		{
			int m = 0;
			for (int j = 0; handCard[j] > -1; j++)
			{
				if (m >= 2) break;
				if (handCard[j] / 4 == i)
				{
					save[n++] = handCard[j];
					m++;
				}
			}
		}
		return;
	}
	//9三顺
	else if (CardTypeCout > 900 && CardTypeCout < 1000)
	{
		int n = 0;//记录位置
		for (int i = minCard; i <= ((CardTypeCout % 100) / 3 + minCard - 1); i++)
		{
			int m = 0;
			for (int j = 0; handCard[j] > -1; j++)
			{
				if (m >= 3) break;//同一点数牌，找三张
				if (handCard[j] / 4 == i)
				{
					save[n++] = handCard[j];
					m++;
				}
			}
		}
		return;
	}
	//10三顺带牌连（飞机）
	else if (CardTypeCout > 1000 && CardTypeCout < 1100)
	{
		//三顺带单牌连
		if ((CardTypeCout % 100) % 4 == 0)
		{
			int n = 0,lian= (CardTypeCout % 100) / 4;//记录位置、几连飞机
			for (int i = minCard; i <= (lian + minCard - 1); i++)
			{
				int m = 0;
				for (int j = 0; handCard[j] > -1; j++)
				{
					if (m >= 3) break;//同一点数牌，找三张
					if (handCard[j] / 4 == i)
					{
						save[n++] = handCard[j];
						m++;
					}
				}
			}
			for(int i=0;handCard[i]>-1;i++)//一单
				if (handCard[i] / 4 == take1)
				{
					save[n++] = handCard[i];
					break;
				}
			for (int i = 0; handCard[i] > -1; i++)//二单
				if (handCard[i] / 4 == take2)
				{
					save[n++] = handCard[i];
					break;
				}
			if (lian >= 3)//三连飞机
			{
				for (int i = 0; handCard[i] > -1; i++)
					if (handCard[i] / 4 == take3)
					{
						save[n++] = handCard[i];
						break;
					}
				if (lian >= 4)//四连飞机
				{
					for (int i = 0; handCard[i] > -1; i++)
						if (handCard[i] / 4 == take4)
						{
							save[n++] = handCard[i];
							break;
						}
				}
			}
			
		}
		else if ((CardTypeCout % 100) % 5 == 0)//三顺带对牌
		{
			int n = 0, lian = (CardTypeCout % 100) / 5;//记录位置、几连飞机
			for (int i = minCard; i <= (lian + minCard - 1); i++)
			{
				int m = 0;
				for (int j = 0; handCard[j] > -1; j++)
				{
					if (m >= 3) break;//同一点数牌，找三张
					if (handCard[j] / 4 == i)
					{
						save[n++] = handCard[j];
						m++;
					}
				}
			}
			for (int i = 0, m = 0; handCard[i] > -1; i++)//第一张对牌
			{
				if (m >= 2) break;
				if (handCard[i] / 4 == take1)
				{
					save[n++] = handCard[i];
					m++;
				}
			}
			for (int i = 0, m = 0; handCard[i] > -1; i++)//第二张对牌
			{
				if (m >= 2) break;
				if (handCard[i] / 4 == take2)
				{
					save[n++] = handCard[i];
					m++;
				}
			}
			if (lian >= 3)//三连飞机
			{
				for (int i = 0, m = 0; handCard[i] > -1; i++)//第三张对牌
				{
					if (m >= 2) break;
					if (handCard[i] / 4 == take3)
					{
						save[n++] = handCard[i];
						m++;
					}
				}
				if (lian >= 4)//四连飞机
				{
					for (int i = 0, m = 0; handCard[i] > -1; i++)//第四张对牌
					{
						if (m >= 2) break;
						if (handCard[i] / 4 == take4)
						{
							save[n++] = handCard[i];
							m++;
						}
					}
				}
			}
		}
		return;
	}
	//11四带两单
	else if (1106 == CardTypeCout)
	{
		int n = 0;
		for (int i = 0; handCard[i] > -1; i++)
		{
			if (n >= 4) break;
			if (handCard[i] / 4 == minCard)
			{
				save[n++] = handCard[i];
			}
		}
		for(int i=0;handCard[i]>-1;i++)//一单
			if (handCard[i] / 4 == take1)
			{
				save[n++] = handCard[i];
				break;
			}
		for (int i = 0; handCard[i] > - 1; i++)//二单
			if (handCard[i] / 4 == take2)
			{
				save[n++] = handCard[i];
				break;
			}
		return;
	}
	//11四带对牌
	else if (1108 == CardTypeCout)
	{
		int n = 0;
		for (int i = 0; handCard[i] > -1; i++)
		{
			if (n >= 4) break;
			if (handCard[i] / 4 == minCard)
			{
				save[n++] = handCard[i];
			}
		}
		for (int i = 0,m=0; handCard[i]> - 1; i++)//一对
		{
			if (m >= 2) break;
			if (handCard[i] / 4 == take1)
			{
				save[n++] = handCard[i];
				m++;
			}
		}
		for (int i = 0, m = 0; handCard[i]> - 1; i++)//二对
		{
			if (m >= 2) break;
			if (handCard[i] / 4 == take2)
			{
				save[n++] = handCard[i];
				m++;
			}
		}
		return;
	}
}

/*  获取牌的价值
通过回溯dp的方式获取手牌价值
与 PutCardWay() 作为交替递归调用
计算手牌价值=打出牌的价值 + 剩余牌的价值 ； （出牌手数也属于计算范围）
*/
HandCardValue GetCardValue(HandCard &handCard)
{
	handCard.ClearPutCard();//清空出牌序列，腾出位置保存最优方案
	HandCardValue tHandCardvalue;//暂存手牌价值
	CardGroup tCardGroup;//暂存手牌组合
	if (handCard.sumNum == 0)//出完牌了
	{
		tHandCardvalue.value = 0;
		tHandCardvalue.needPly = 0;
		return tHandCardvalue;
	}
	//判断是不是剩一手牌
	tCardGroup = JudgeOneHand2(handCard.CardPointNum);
	if (tCardGroup.cardTypeId!=-1 && tCardGroup.cardTypeId/100!=11 )//不是错误类型 && 不考虑拆四带二（尽量保持炸弹）
	{
		tHandCardvalue.value = tCardGroup.value;
		tHandCardvalue.needPly = 1;
		return tHandCardvalue;
	}

	//非一手牌
	/*
	（根据主动/被动出牌）计算最优出牌方案
	最佳出牌方案保存在出牌序列和出牌牌型数组中
	*/
	PutCardWay(handCard);

	tCardGroup = handCard.PutCardGroup;//暂存最佳出牌牌型结构（牌型张数、价值、主牌最小点数）
	int NowPutCard[21];//暂存目前出牌序列
	for (int i = 0; i < 21; i++) {
		NowPutCard[i] = handCard.PutCard[i];
	}

	//删除要出的牌
	for (int i = 0; NowPutCard[i]>-1; i++)
	{
		handCard.CardPointNum[NowPutCard[i] / 4]--;
		handCard.sumNum--;
	}

	HandCardValue tSurCardValue = GetCardValue(handCard);	//通过回溯获取剩余手牌价值

	//加回来
	for (int i = 0; NowPutCard[i] > -1; i++)
	{
		handCard.CardPointNum[NowPutCard[i] / 4]++;
		handCard.sumNum++;
	}

	tHandCardvalue.value = tCardGroup.value + tSurCardValue.value;//手牌价值=出牌价值+剩余牌价值
	tHandCardvalue.needPly = tSurCardValue.needPly + 1;//手数+1；

	return tHandCardvalue;
	
}

//出牌策略  //选取总权值-轮次*7值最高的策略
void PutCardWay(HandCard &handCard)
{
	/*
	//主动出牌策略（可以任意出牌）
	if (handCard.PutAnyCard == 1 || handCard.PutAnyCard==-1)  //自己是地主时，一开始可以出任意牌
	{
		PutCardWayActive(handCard);
	}
	//被动出牌策略
	else if (handCard.PutAnyCard == 0)
	{
		PutCardWayUnactive(handCard);
	}
	*/
	PutCardWayActive(handCard);
}

/*
主动出牌的策略   按照优先级大体可以分为三类：
【一】能直接一手牌出去，优先出。
【二】两手牌出去且有绝对大牌，先出绝对大牌。
【三】出一手牌使得接下来自己手牌价值最大化。
*/
void PutCardWayActive(HandCard &handCard)
{
	handCard.ClearPutCard();//清空出牌序列
	HandCardValue tHandCardValue;//暂存手牌价值
	HandCardValue bestHandValue;	//暂存最佳的价值
	CardGroup bestCardGroup;      //暂存最佳牌型组合

	//【 一 】判断是否一手牌
	bestCardGroup = JudgeOneHand2(handCard.CardPointNum);//暂存出牌组合
	if (bestCardGroup.cardTypeId!=-1 && bestCardGroup.cardTypeId/100 != 11)//不是错误类型 && 不拆炸弹  （主动出牌，不用比较大小）
	{
		FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, bestCardGroup.cardTypeId, bestCardGroup.minCard, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
		handCard.PutCardGroup = bestCardGroup;
		handCard.value = bestCardGroup.value;//方便调试
		return;
	}

	//【 二 】两手牌出去且有绝对大牌，先出绝对大牌。
	/*王炸——当前策略只处理王炸作为倒数第二手的优先出牌*/
	if (handCard.CardPointNum[13] > 1)//有王炸
	{
		handCard.CardPointNum[13] -= 2;
		handCard.sumNum -= 2;
		tHandCardValue = GetCardValue(handCard);
		handCard.CardPointNum[13] += 2;
		handCard.sumNum += 2;
		if (tHandCardValue.needPly == 1)
		{
			handCard.PutCard[0] = 52;
			handCard.PutCard[1] = 53;
			handCard.PutCardGroup.cardTypeId = 102;
			handCard.PutCardGroup.minCard = 13;
			handCard.PutCardGroup.value = CardTypeValue(102, 13);
			handCard.value = tHandCardValue.value + 20;//手牌价值=出牌价值+剩余牌价值
			return;
		}
	}

	//【 三 】出一手牌使得接下来自己手牌价值最大化。

	bestHandValue.needPly = 20;
	bestHandValue.value = -25;
	bestHandValue.needPly += 1;//我们认为不出牌的话会让对手一个轮次，即加一轮（权值减少7）便于后续的对比参考


	//优先处理三带、飞机等牌
	for (int i = 0; i < 13; i++)//(没有王)
	{
		if (handCard.CardPointNum[i] != 4)//不考虑拆炸弹
		{
			//出三带一单
			if (handCard.CardPointNum[i] >= 3)
			{
				handCard.CardPointNum[i] -= 3;
				handCard.sumNum-=3;
				for (int j = 0; j <= 13; j++)
				{
					if (handCard.CardPointNum[j] > 0 && j!=i)//单牌
					{
						handCard.CardPointNum[j]--;
						handCard.sumNum --;
						tHandCardValue = GetCardValue(handCard);
						handCard.CardPointNum[j]++;
						handCard.sumNum++;
						if (bestHandValue.value - (bestHandValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
						{
							bestHandValue = tHandCardValue;
							bestCardGroup.cardTypeId = 604;
							bestCardGroup.minCard = i;
							bestCardGroup.value = CardTypeValue(604, i);
							bestCardGroup.take1 = j;
						}
					}
				}
				handCard.CardPointNum[i] += 3;
				handCard.sumNum += 3;
			}
			//出三带一对
			if (handCard.CardPointNum[i] >= 3)
			{
				handCard.CardPointNum[i] -= 3;
				handCard.sumNum -= 3;
				for (int j = 0; j <= 13; j++)
				{
					if (handCard.CardPointNum[j] > 1 && j != i)
					{
						handCard.CardPointNum[j] -= 2;
						handCard.sumNum -= 2;
						tHandCardValue = GetCardValue(handCard);
						handCard.CardPointNum[j] += 2;
						handCard.sumNum += 2;
						//价值比较
						if (bestHandValue.value - (bestHandValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
						{
							bestHandValue = tHandCardValue;
							bestCardGroup.cardTypeId = 605;
							bestCardGroup.minCard = i;
							bestCardGroup.value = CardTypeValue(605, i);
							bestCardGroup.take1 = j;
						}
					}
				}
				handCard.CardPointNum[i] += 3;
				handCard.sumNum += 3;
			}
			//出四带二单（暂不考虑拆炸弹）
			if (handCard.CardPointNum[i] == 4)
			{
				//暂不考虑拆炸弹
			}
			//出四带二对（暂不考虑拆炸弹）
			if (handCard.CardPointNum[i] == 4)
			{
				//暂不考虑拆炸弹
			}
			//出三带单连
			if (handCard.CardPointNum[i] >= 3)
			{
				int pro = 0;
				for (int j = i; j<13; j++)//（不包含王）
				{
					if (handCard.CardPointNum[j] > 2) pro++;
					else break;
					//二连飞机
					if (pro == 2)
					{
						for (int k = i; k <= j; k++) handCard.CardPointNum[k] -= 3;
						handCard.sumNum -= pro*3;
						for (int t1 = 0; t1 <= 12; t1++)//第一张单牌（循环优化）
						{
							if (handCard.CardPointNum[t1] > 0 && (t1<i || t1>j) )
							{
								handCard.CardPointNum[t1]--;
								handCard.sumNum--;
								for (int t2 = t1 + 1; t2 <= 13; t2++)//第二张单牌
								{
									if (handCard.CardPointNum[t2] > 0 && (t2<i || t2>j) )
									{
										handCard.CardPointNum[t2]--;
										handCard.sumNum--;
										tHandCardValue = GetCardValue(handCard);
										handCard.CardPointNum[t2]++;
										handCard.sumNum++;
										//价值比较
										if (bestHandValue.value - (bestHandValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
										{
											bestHandValue = tHandCardValue;
											bestCardGroup.cardTypeId = 1008;
											bestCardGroup.minCard = i;
											bestCardGroup.value = CardTypeValue(1008, i);
											bestCardGroup.take1 = t1;
											bestCardGroup.take2 = t2;
										}
									}
								}
								handCard.sumNum++;
								handCard.CardPointNum[t1]++;
							}
						}
						handCard.sumNum += pro*3;
						for (int k = i; k <= j; k++) handCard.CardPointNum[k] += 3;
					}
					//三连飞机
					if (pro == 3)
					{
						for (int k = i; k <= j; k++) handCard.CardPointNum[k] -= 3;
						handCard.sumNum -= pro * 3;
						for (int t1 = 0; t1 <= 11; t1++)//第一张单牌(循环优化)
						{
							if (handCard.CardPointNum[t1] > 0 && (t1<i || t1>j))
							{
								handCard.CardPointNum[t1]--;
								handCard.sumNum--;
								for (int t2 = t1 + 1; t2 <= 12; t2++)//第二张单牌
								{
									if (handCard.CardPointNum[t2] > 0 && (t2<i || t2>j))
									{
										handCard.CardPointNum[t2]--;
										handCard.sumNum--;
										for (int t3 = t2 + 1; t3 <= 13; t3++)//第三张单牌
										{
											if (handCard.CardPointNum[t3] > 0 && (t3<i || t3>j))
											{
												handCard.CardPointNum[t3]--;
												handCard.sumNum--;
												tHandCardValue = GetCardValue(handCard);
												handCard.CardPointNum[t3]++;
												handCard.sumNum++;
												//价值比较
												if (bestHandValue.value - (bestHandValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
												{
													bestHandValue = tHandCardValue;
													bestCardGroup.cardTypeId = 1012;
													bestCardGroup.minCard = i;
													bestCardGroup.value = CardTypeValue(1012, i);
													bestCardGroup.take1 = t1;
													bestCardGroup.take2 = t2;
													bestCardGroup.take3 = t3;
												}
											}
										}
										handCard.CardPointNum[t2]++;
										handCard.sumNum++;
									}
								}
								handCard.sumNum++;
								handCard.CardPointNum[t1]++;
							}
						}
						handCard.sumNum += pro * 3;
						for (int k = i; k <= j; k++) handCard.CardPointNum[k] += 3;
					}
					//四连飞机
					if (pro == 4)
					{
						for (int k = i; k <= j; k++) handCard.CardPointNum[k] -= 3;
						handCard.sumNum -= pro * 3;
						for (int t1 = 0; t1 <= 10; t1++)//第一张单牌  （循环优化）
						{
							if (handCard.CardPointNum[t1] > 0 && (t1<i || t1>j))
							{
								handCard.CardPointNum[t1]--;
								handCard.sumNum--;
								for (int t2 = t1 + 1; t2 <= 11; t2++)//第二张单牌
								{
									if (handCard.CardPointNum[t2] > 0 && (t2<i || t2>j))
									{
										handCard.CardPointNum[t2]--;
										handCard.sumNum--;
										for (int t3 = t2 + 1; t3 <= 12; t3++)//第三张单牌
										{
											if (handCard.CardPointNum[t3] > 0 && (t3<i || t3>j))
											{
												handCard.CardPointNum[t3]--;
												handCard.sumNum--;
												for (int t4 = t3 + 1; t4 <= 13; t4++)//第四张单牌
												{
													if (handCard.CardPointNum[t4] > 0 && (t4<i || t4>j))
													{
														handCard.CardPointNum[t4]--;
														handCard.sumNum--;
														tHandCardValue = GetCardValue(handCard);
														handCard.CardPointNum[t4]++;
														handCard.sumNum++;
														//价值比较
														if (bestHandValue.value - (bestHandValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
														{
															bestHandValue = tHandCardValue;
															bestCardGroup.cardTypeId = 1016;
															bestCardGroup.minCard = i;
															bestCardGroup.value = CardTypeValue(1016, i);
															bestCardGroup.take1 = t1;
															bestCardGroup.take2 = t2;
															bestCardGroup.take3 = t3;
															bestCardGroup.take4 = t4;
														}
													}
												}
												handCard.CardPointNum[t3]++;
												handCard.sumNum++;
											}
										}
										handCard.CardPointNum[t2]++;
										handCard.sumNum++;
									}
								}
								handCard.sumNum++;
								handCard.CardPointNum[t1]++;
							}
						}
						handCard.sumNum += pro * 3;
						for (int k = i; k <= j; k++) handCard.CardPointNum[k] += 3;
					}
				}
			}
			//三带对连
			if (handCard.CardPointNum[i] >= 3)
			{
				int pro = 0;
				for (int j = i; j < 13; j++)//(不包含王)
				{
					if (handCard.CardPointNum[j] >= 3) pro++;
					else break;
					//二连飞机
					if (pro == 2)
					{
						for (int k = i; k <= j; k++) handCard.CardPointNum[k] -= 3;
						handCard.sumNum -= pro * 3;
						for (int t1 = 0; t1 <= 12; t1++)//第一张对牌
						{
							if (handCard.CardPointNum[t1] > 1 && (t1<i || t1>j))
							{
								handCard.CardPointNum[t1] -= 2;
								handCard.sumNum -= 2;
								for (int t2 = t1 + 1; t2 <= 13; t2++)//第二张对牌
								{
									if (handCard.CardPointNum[t2] > 1 && (t2<i || t2>j))
									{
										handCard.CardPointNum[t2] -= 2;
										handCard.sumNum -= 2;
										tHandCardValue = GetCardValue(handCard);
										handCard.sumNum += 2;
										handCard.CardPointNum[t2] += 2;
										if (bestHandValue.value - (bestHandValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
										{
											bestHandValue = tHandCardValue;
											bestCardGroup.cardTypeId = 1010;
											bestCardGroup.minCard = i;
											bestCardGroup.value = CardTypeValue(1010, i);
											bestCardGroup.take1 = t1;
											bestCardGroup.take2 = t2;
										}
									}
								}
								handCard.sumNum += 2;
								handCard.CardPointNum[t1] += 2;
							}
						}
						handCard.sumNum += pro * 3;
						for (int k = i; k <= j; k++) handCard.CardPointNum[k] += 3;
					}
					//三连飞机
					if (pro == 3)
					{
						for (int k = i; k <= j; k++) handCard.CardPointNum[k] -= 3;
						handCard.sumNum -= pro * 3;
						for (int t1 = 0; t1 <= 11; t1++)//一对
						{
							if (handCard.CardPointNum[t1] > 1 && (t1<i || t1>j))
							{
								handCard.CardPointNum[t1] -= 2;
								handCard.sumNum -= 2;
								for (int t2 = t1 + 1; t2 <= 12; t2++)//二对
								{
									if (handCard.CardPointNum[t2] > 1 && (t2<i || t2>j))
									{
										handCard.CardPointNum[t2] -= 2;
										handCard.sumNum -= 2;
										for (int t3 = t2 + 1; t3 <= 13; t3++)//第三张对牌
										{
											if (handCard.CardPointNum[t3] > 1 && (t3<i || t3>j))
											{
												handCard.CardPointNum[t3] -= 2;
												handCard.sumNum -= 2;
												tHandCardValue = GetCardValue(handCard);
												handCard.sumNum += 2;
												handCard.CardPointNum[t3] += 2;
												if (bestHandValue.value - (bestHandValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
												{
													bestHandValue = tHandCardValue;
													bestCardGroup.cardTypeId = 1015;
													bestCardGroup.minCard = i;
													bestCardGroup.value = CardTypeValue(1015, i);
													bestCardGroup.take1 = t1;
													bestCardGroup.take2 = t2;
													bestCardGroup.take3 = t3;
												}
											}
										}
										handCard.sumNum += 2;
										handCard.CardPointNum[t2] += 2;
									}
								}
								handCard.sumNum += 2;
								handCard.CardPointNum[t1] += 2;
							}
						}
						handCard.sumNum += pro * 3;
						for (int k = i; k <= j; k++) handCard.CardPointNum[k] += 3;
					}
					//四连飞机
					if (pro == 4)
					{
						for (int k = i; k <= j; k++) handCard.CardPointNum[k] -= 3;
						handCard.sumNum -= pro * 3;
						for (int t1 = 0; t1 <= 10; t1++)//第一张对牌
						{
							if (handCard.CardPointNum[t1] > 1 && (t1<i || t1>j))
							{
								handCard.CardPointNum[t1] -= 2;
								handCard.sumNum -= 2;
								for (int t2 = t1 + 1; t2 <= 11; t2++)//第二张对牌
								{
									if (handCard.CardPointNum[t2] > 1 && (t2<i || t2>j))
									{
										handCard.CardPointNum[t2] -= 2;
										handCard.sumNum -= 2;
										for (int t3 = t2 + 1; t3 <= 12; t3++)//第三张对牌
										{
											if (handCard.CardPointNum[t3] > 1 && (t3<i || t3>j))
											{
												handCard.CardPointNum[t3] -= 2;
												handCard.sumNum -= 2;
												for (int t4 = t3 + 1; t4 <= 13; t4++)//第四张对牌
												{
													if (handCard.CardPointNum[t4] > 1 && (t4<i || t4>j))
													{
														handCard.CardPointNum[t4] -= 2;
														handCard.sumNum -= 2;
														tHandCardValue = GetCardValue(handCard);
														handCard.sumNum += 2;
														handCard.CardPointNum[t4] += 2;
														if (bestHandValue.value - (bestHandValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
														{
															bestHandValue = tHandCardValue;
															bestCardGroup.cardTypeId = 1020;
															bestCardGroup.minCard = i;
															bestCardGroup.value = CardTypeValue(1020, i);
															bestCardGroup.take1 = t1;
															bestCardGroup.take2 = t2;
															bestCardGroup.take3 = t3;
															bestCardGroup.take4 = t4;
														}
													}
												}
												handCard.sumNum += 2;
												handCard.CardPointNum[t3] += 2;
											}
										}
										handCard.sumNum += 2;
										handCard.CardPointNum[t2] += 2;
									}
								}
								handCard.sumNum += 2;
								handCard.CardPointNum[t1] += 2;
							}
						}
						handCard.sumNum += pro * 3;
						for (int k = i; k <= j; k++) handCard.CardPointNum[k] += 3;
					}
				}
			}
		}
	}
	//判断是否有对应的牌可以出
	if ((bestCardGroup.cardTypeId / 100) == 6)//三带一
	{
		if (bestCardGroup.cardTypeId % 100 == 4)//三带单
		{
			//在手牌中，找到对应的牌型的编号，并放入出牌序列中
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, bestCardGroup.cardTypeId, bestCardGroup.minCard, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
			handCard.PutCardGroup = bestCardGroup;
			//保存价值
			handCard.value = bestHandValue.value + bestCardGroup.value;
			return;
		}
		else if (bestCardGroup.cardTypeId % 100 == 5)//三带对
		{
			//在手牌中，找到对应的牌型的编号，并放入出牌序列中
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, bestCardGroup.cardTypeId, bestCardGroup.minCard, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
			handCard.PutCardGroup = bestCardGroup;
			//保存价值
			handCard.value = bestHandValue.value + bestCardGroup.value;
			return;
		}
	}
	//飞机
	else if ((bestCardGroup.cardTypeId / 100) == 10)
	{
		if ((bestCardGroup.cardTypeId % 100) % 4 == 0)//三带单连
		{
			//在手牌中，找到对应的牌型的编号，并放入出牌序列中
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, bestCardGroup.cardTypeId, bestCardGroup.minCard, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
			handCard.PutCardGroup = bestCardGroup;
			//保存价值
			handCard.value = bestHandValue.value + bestCardGroup.value;
			return;
		}
		else if((bestCardGroup.cardTypeId % 100) % 5 == 0)//三带对连
		{
			//在手牌中，找到对应的牌型的编号，并放入出牌序列中
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, bestCardGroup.cardTypeId, bestCardGroup.minCard, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
			handCard.PutCardGroup = bestCardGroup;
			//保存价值
			handCard.value = bestHandValue.value + bestCardGroup.value;
			return;
		}
	}

	//次之处理当前价值最低的牌（单牌、对牌、三牌、单顺、双顺、三顺），现在不必再考虑这张牌可能被三牌带出等情况
	for (int i = 0; i <= 13; i++)
	{
		if (handCard.CardPointNum[i] != 0 && handCard.CardPointNum[i] != 4)//若有四张牌，先不处理
		{
			//单牌
			if (handCard.CardPointNum[i] > 0)
			{
				handCard.CardPointNum[i]--;
				handCard.sumNum--;
				tHandCardValue = GetCardValue(handCard);
				handCard.sumNum++;
				handCard.CardPointNum[i]++;
				if (bestHandValue.value - (bestHandValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
				{
					bestHandValue = tHandCardValue;
					bestCardGroup.cardTypeId = 301;
					bestCardGroup.minCard = i;
					bestCardGroup.value = CardTypeValue(301, i);
				}
			}
			//出对牌
			if (handCard.CardPointNum[i] > 1)
			{
				handCard.CardPointNum[i] -= 2;
				handCard.sumNum -= 2;
				tHandCardValue = GetCardValue(handCard);
				handCard.sumNum += 2;
				handCard.CardPointNum[i] += 2;
				if (bestHandValue.value - (bestHandValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
				{
					bestHandValue = tHandCardValue;
					bestCardGroup.cardTypeId = 402;
					bestCardGroup.minCard = i;
					bestCardGroup.value = CardTypeValue(402, i);
				}
			}
			//出三牌
			if (handCard.CardPointNum[i] >= 3)
			{
				handCard.CardPointNum[i] -= 3;
				handCard.sumNum -= 3;
				tHandCardValue = GetCardValue(handCard);
				handCard.sumNum += 3;
				handCard.CardPointNum[i] += 3;
				if (bestHandValue.value - (bestHandValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
				{
					bestHandValue = tHandCardValue;
					bestCardGroup.cardTypeId = 503;
					bestCardGroup.minCard = i;
					bestCardGroup.value = CardTypeValue(503, i);
				}
			}
			//出单顺
			if (handCard.CardPointNum[i] > 0)
			{
				int pro = 0;
				for (int j = i; j < 12; j++)//不包含2和王
				{
					if (handCard.CardPointNum[j] > 0) pro++;
					else break;

					if (pro >= 5)
					{
						for (int k = i; k <= j; k++)
							handCard.CardPointNum[k]--;
						handCard.sumNum -= pro;
						tHandCardValue = GetCardValue(handCard);
						handCard.sumNum += pro;
						for (int k = i; k <= j; k++)
							handCard.CardPointNum[k]++;
						if (bestHandValue.value - (bestHandValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
						{
							bestHandValue = tHandCardValue;
							bestCardGroup.cardTypeId = 700 + pro;
							bestCardGroup.minCard = i;
							bestCardGroup.value = CardTypeValue(700 + pro, i);
						}
					}
				}
			}
			//出双顺
			if (handCard.CardPointNum[i] >= 2)
			{
				int pro = 0;
				for (int j = i; j < 12; j++)//不包含2和王
				{
					if (handCard.CardPointNum[j] > 1) pro++;
					else break;

					if (pro >= 3)
					{
						for (int k = i; k <= j; k++)
							handCard.CardPointNum[k] -= 2;
						handCard.sumNum -= pro * 2;
						tHandCardValue = GetCardValue(handCard);
						handCard.sumNum += pro * 2;
						for (int k = i; k <= j; k++)
							handCard.CardPointNum[k] += 2;
						if (bestHandValue.value - (bestHandValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
						{
							bestHandValue = tHandCardValue;
							bestCardGroup.cardTypeId = 800 + pro * 2;
							bestCardGroup.minCard = i;
							bestCardGroup.value = CardTypeValue(800 + pro * 2, i);
						}
					}
				}
			}
			//出三顺
			if (handCard.CardPointNum[i] > 2)
			{
				int pro = 0;
				for (int j = i; j < 12; j++)//不包含2和王
				{
					if (handCard.CardPointNum[j] > 2) pro++;
					else break;

					if (pro >= 2)
					{
						for (int k = i; k <= j; k++)
							handCard.CardPointNum[k] -= 3;
						handCard.sumNum -= pro * 3;
						tHandCardValue = GetCardValue(handCard);
						handCard.sumNum += pro * 3;
						for (int k = i; k <= j; k++)
							handCard.CardPointNum[k] += 3;
						if (bestHandValue.value - (bestHandValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
						{
							bestHandValue = tHandCardValue;
							bestCardGroup.cardTypeId = 900 + pro * 3;
							bestCardGroup.minCard = i;
							bestCardGroup.value = CardTypeValue(900 + pro * 3, i);
						}
					}
				}
			}

			//因为本策略是必须解决掉至少一个i牌的，所以出牌操作放在循环内进行，也就是说，只要你不是炸3，若你手牌有3，在处理3时一定会return  就绝对不会再走到4。
			//出牌
			if (bestCardGroup.cardTypeId / 100 == 3)//单牌
			{
				//在手牌中，找到对应的牌型的编号，并放入出牌序列中
				FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, bestCardGroup.cardTypeId, bestCardGroup.minCard, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
				handCard.PutCardGroup = bestCardGroup;
				//保存价值
				handCard.value = bestHandValue.value + bestCardGroup.value;
				return;
			}
			else if (bestCardGroup.cardTypeId / 100 == 4)//对牌
			{
				//在手牌中，找到对应的牌型的编号，并放入出牌序列中
				FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, bestCardGroup.cardTypeId, bestCardGroup.minCard, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
				handCard.PutCardGroup = bestCardGroup;
				//保存价值
				handCard.value = bestHandValue.value + bestCardGroup.value;
				return;
			}
			else if (bestCardGroup.cardTypeId / 100 == 5)//三条
			{
				//在手牌中，找到对应的牌型的编号，并放入出牌序列中
				FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, bestCardGroup.cardTypeId, bestCardGroup.minCard, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
				handCard.PutCardGroup = bestCardGroup;
				//保存价值
				handCard.value = bestHandValue.value + bestCardGroup.value;
				return;
			}
			else if (bestCardGroup.cardTypeId / 100 == 7)//单顺
			{
				//在手牌中，找到对应的牌型的编号，并放入出牌序列中
				FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, bestCardGroup.cardTypeId, bestCardGroup.minCard, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
				handCard.PutCardGroup = bestCardGroup;
				//保存价值
				handCard.value = bestHandValue.value + bestCardGroup.value;
				return;
			}
			else if (bestCardGroup.cardTypeId / 100 == 8)//双顺
			{
				//在手牌中，找到对应的牌型的编号，并放入出牌序列中
				FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, bestCardGroup.cardTypeId, bestCardGroup.minCard, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
				handCard.PutCardGroup = bestCardGroup;
				//保存价值
				handCard.value = bestHandValue.value + bestCardGroup.value;
				return;
			}
		}

	}
	

	//如果没有3-2的非炸牌，则看看有没有单王
	if (handCard.CardPointNum[13] == 1)
	{
		handCard.CardPointNum[13]--;
		handCard.sumNum--;
		tHandCardValue = GetCardValue(handCard);
		handCard.CardPointNum[13]++;
		handCard.sumNum++;
		handCard.value = tHandCardValue.value + CardTypeValue(301, 13);

		//计算价值后再记录出牌数组（以免被计算价值函数清楚  出牌数组记录 ）2020.1.3改
		//在手牌中，找到对应的牌型的编号，并放入出牌序列中
		FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, 301, 13, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
		bestCardGroup.cardTypeId = 301;
		bestCardGroup.minCard = 13;
		bestCardGroup.value = CardTypeValue(301, 13);
		handCard.PutCardGroup = bestCardGroup;
		return;
	}
	//单王也没有，出炸弹
	for (int i = 0; i <= 13; i++)
	{
		if (handCard.CardPointNum[i] == 4)
		{
			handCard.CardPointNum[i]-=4;
			handCard.sumNum-=4;
			tHandCardValue = GetCardValue(handCard);
			handCard.CardPointNum[i]+=4;
			handCard.sumNum+=4;
			handCard.value = tHandCardValue.value + CardTypeValue(204, i);

			//计算价值后再记录出牌数组（以免被计算价值函数清楚  出牌数组记录 ）2020.1.3改
			//在手牌中，找到对应的牌型的编号，并放入出牌序列中
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, 204, i, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
			bestCardGroup.cardTypeId = 204;
			bestCardGroup.value = CardTypeValue(204, i);
			bestCardGroup.minCard = i;
			handCard.PutCardGroup = bestCardGroup;

			return;
		}
	}
	//异常错误
	handCard.PutCardGroup.cardTypeId = -1;
	handCard.PutCardGroup.minCard =  -1;
	handCard.PutCardGroup.value = -1;
	return;
}

/*
2.0版本策略  根据场上形势决定当前预打出的手牌——被动出牌
【直接打光手牌】→【同类型牌压制】→【炸弹王炸压制】→【不出】
*/
void PutCardWayUnactive(HandCard &handCard)//接牌函数
{
	//清空出牌序列
	handCard.ClearPutCard();
	HandCardValue tHandCardValue;//暂存手牌价值
	CardGroup tCardGroup;//暂存出牌组合
	HandCardValue bestHandCardValue;//最佳手牌价值

	//======================================【特殊处理】========================================

	//弃牌或者是错误  不出牌  (当前桌面牌型为弃牌类型也属于错误类型)
	if (handCard.tableTypeCount == 0 || handCard.tableTypeCount == -1)
	{
		handCard.PutCardGroup.cardTypeId = 0;
		handCard.PutCardGroup.minCard = -1;
		handCard.PutCardGroup.value = 0;

		return;
	}

	//王炸——当前策略只处理王炸作为倒数第二手的优先出牌逻辑
	if (handCard.CardPointNum[13] > 1)
	{
		handCard.CardPointNum[13] -= 2;
		handCard.sumNum -= 2;
		tHandCardValue = GetCardValue(handCard);
		handCard.sumNum += 2;
		handCard.CardPointNum[13] += 2;
		if (tHandCardValue.needPly == 1)
		{
			handCard.PutCard[0] = 52;
			handCard.PutCard[1] = 53;
			handCard.PutCardGroup.value = 20;
			handCard.PutCardGroup.cardTypeId = 102;
			handCard.PutCardGroup.minCard = 13;

			//handCard.value = tHandCardValue.value + 20;
			return;
		}
	}

	//======================================【直接打光手牌】====================================
	tCardGroup = JudgeOneHand2(handCard.CardPointNum);
	if (tCardGroup.cardTypeId != -1)//如果是一手牌
	{
		if ((tCardGroup.cardTypeId == handCard.tableTypeCount && tCardGroup.minCard > handCard.tableMainPoint) || tCardGroup.cardTypeId / 100 == 1 )
		{ //同种（包括出牌数量）牌型 && 比对方大 || 火箭
			//找出出牌序列
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, tCardGroup.cardTypeId, tCardGroup.minCard, tCardGroup.take1, tCardGroup.take2, tCardGroup.take3, tCardGroup.take4);
			//保存牌型组合
			handCard.PutCardGroup = tCardGroup;

			//handCard.value = tCardGroup.value;
			return;
		}
		else if (tCardGroup.cardTypeId / 100 == 2 && handCard.tableTypeCount/100!=1 && handCard.tableTypeCount / 100 != 2 )//对方不是炸弹或者王炸，我是炸弹，直接炸
		{
			//找出出牌序列
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, tCardGroup.cardTypeId, tCardGroup.minCard, tCardGroup.take1, tCardGroup.take2, tCardGroup.take3, tCardGroup.take4);
			//保存牌型组合
			handCard.PutCardGroup = tCardGroup;

			//handCard.value = tCardGroup.value;
			return;
		}
	}
	//======================================【同类型牌压制】====================================

	bestHandCardValue = GetCardValue(handCard);
	bestHandCardValue.needPly += 1;//我们认为不出牌的话会让对手一个轮次，即加一轮（权值减少7）便于后续的对比参考。

	int bestMinCard = -1;//暂存最佳牌号
	bool put = false;//出牌标志
	int take1 = -1, take2 = -1, take3 = -1, take4 = -1;//带牌

	//----------------------------火箭-----------------------
	if (handCard.tableTypeCount / 100 == 1)
	{
		//不出
		handCard.PutCardGroup.cardTypeId = 0;
		handCard.PutCardGroup.minCard = -1;
		handCard.PutCardGroup.value = 0;

		//handCard.value = bestHandCardValue.value;//手牌价值等于目前手牌的价值
		return;
	}
	//----------------------------炸弹---------------------
	else if (handCard.tableTypeCount / 100 == 2)
	{
		//更大的炸弹——这里直接炸，不考虑拆分后果。因为信仰
		for (int i = handCard.tableMainPoint + 1; i < 13; i++)//不包含王
		{
			if (handCard.CardPointNum[i] == 4)
			{
				handCard.PutCardGroup.cardTypeId = 204;
				handCard.PutCardGroup.minCard = i;
				handCard.PutCardGroup.value = CardTypeValue(204, i);
				FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, handCard.PutCardGroup.cardTypeId, handCard.PutCardGroup.minCard, 0, 0, 0, 0);
				
				return;
			}
		}
		if (handCard.CardPointNum[13] > 1)
		{
			handCard.PutCard[0] = 52;
			handCard.PutCard[1] = 53;
			handCard.PutCardGroup.cardTypeId = 102;
			handCard.PutCardGroup.minCard = 13;
			handCard.PutCardGroup.value = 20;

			return;
		}
	}
	//-----------------------------单牌--------------------
	else if (handCard.tableTypeCount / 100 == 3)
	{
		//【同类型牌压制】

		if (handCard.tableMainPoint == 13)
		{
			for(int hh=0;handCard.onHandCard[hh]>=0;hh++)/////******************避免队友出小王，自己拽着大王不出
				if (handCard.onHandCard[hh] == 53)
				{
					handCard.CardPointNum[handCard.onHandCard[hh]/4]--;
					handCard.sumNum--;
					tHandCardValue = GetCardValue(handCard);
					handCard.sumNum++;
					handCard.CardPointNum[handCard.onHandCard[hh] / 4]--;
					if (bestHandCardValue.value - (bestHandCardValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
					{
						bestHandCardValue = tHandCardValue;
						bestMinCard = handCard.onHandCard[hh] / 4;
						put = true;
					}

				}
		}
		
		for (int i = handCard.tableMainPoint + 1; i <= 13; i++)
		{
			if (handCard.CardPointNum[i] > 0)
			{
				handCard.CardPointNum[i]--;
				handCard.sumNum--;
				tHandCardValue = GetCardValue(handCard);
				handCard.sumNum++;
				handCard.CardPointNum[i]++;
				if (bestHandCardValue.value - (bestHandCardValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
				{
					bestHandCardValue = tHandCardValue;
					bestMinCard = i;
					put = true;
				}
			}
		}
		if (put)
		{
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, 301, bestMinCard, 0, 0, 0, 0);
			handCard.PutCardGroup.cardTypeId = 301;
			handCard.PutCardGroup.minCard = bestMinCard;
			handCard.PutCardGroup.value = bestHandCardValue.value;

			//handCard.value = bestHandCardValue.value + handCard.PutCardGroup.value;
			return;
		}
	}
	//---------------------------对牌------------------------
	else if (handCard.tableTypeCount / 100 == 4)
	{
		//【同类型牌压制】
		for (int i = handCard.tableMainPoint + 1; i <= 13; i++)
		{
			if (handCard.CardPointNum[i] > 1)
			{
				handCard.CardPointNum[i] -= 2;
				handCard.sumNum -= 2;
				tHandCardValue = GetCardValue(handCard);
				handCard.sumNum += 2;
				handCard.CardPointNum[i] += 2;
				if (bestHandCardValue.value - (bestHandCardValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
				{
					bestHandCardValue = tHandCardValue;
					bestMinCard = i;
					put = true;
				}
			}
		}
		if (put)
		{
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, 402, bestMinCard, 0, 0, 0, 0);
			handCard.PutCardGroup.cardTypeId = 402;
			handCard.PutCardGroup.minCard = bestMinCard;
			handCard.PutCardGroup.value = bestHandCardValue.value;

			//handCard.value = bestHandCardValue.value + handCard.PutCardGroup.value;
			return;
		}
	}
	//--------------------------三牌------------------------
	else if (handCard.tableTypeCount / 100 == 5)
	{
		//【同类型牌压制】
		for (int i = handCard.tableMainPoint + 1; i < 13; i++)//不可能包含王
		{
			if (handCard.CardPointNum[i] > 2)
			{
				handCard.CardPointNum[i] -= 3;
				handCard.sumNum -= 3;
				tHandCardValue = GetCardValue(handCard);
				handCard.sumNum += 3;
				handCard.CardPointNum[i] += 3;
				if (bestHandCardValue.value - (bestHandCardValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
				{
					bestHandCardValue = tHandCardValue;
					bestMinCard = i;
					put = true;
				}
			}
		}
		if (put)
		{
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, 503, bestMinCard, 0, 0, 0, 0);
			handCard.PutCardGroup.cardTypeId = 503;
			handCard.PutCardGroup.minCard = bestMinCard;
			handCard.PutCardGroup.value = bestHandCardValue.value;
			return;
		}
	}
	//------------------------- 三带一 ------------------------
	else if (handCard.tableTypeCount / 100 == 6)
	{
		if (handCard.tableTypeCount % 100 == 4)//-----------------------------三带一单
		{
			//【同类型牌压制】
			for (int i = handCard.tableMainPoint + 1; i < 13; i++)//不包含王
			{
				if (handCard.CardPointNum[i] == 4) continue;//防止拆炸弹10.2修改

				if (handCard.CardPointNum[i] > 2)
				{
					handCard.CardPointNum[i] -= 3;
					handCard.sumNum -= 3;
					for (int j = 0; j <= 13; j++)
					{
						if (handCard.CardPointNum[j] > 0 && j != i)
						{
							handCard.CardPointNum[j]--;
							handCard.sumNum--;
							tHandCardValue = GetCardValue(handCard);
							handCard.CardPointNum[j]++;
							handCard.sumNum++;
							if (bestHandCardValue.value - (bestHandCardValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
							{
								bestHandCardValue = tHandCardValue;
								bestMinCard = i;
								take1 = j;
								put = true;
							}
						}
					}
					handCard.sumNum += 3;
					handCard.CardPointNum[i] += 3;
				}
			}
			if (put)
			{
				handCard.PutCardGroup.cardTypeId = 604;
				handCard.PutCardGroup.minCard = bestMinCard;
				handCard.PutCardGroup.value = bestHandCardValue.value;
				FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, handCard.PutCardGroup.cardTypeId, bestMinCard, take1, 0, 0, 0);
				return;
			}

		}
		else if (handCard.tableTypeCount % 100 == 5)//-----------------------三带对牌
		{
			//【同类型牌压制】
			for (int i = handCard.tableMainPoint + 1; i < 13; i++)
			{
				if (handCard.CardPointNum[i] > 2)
				{
					handCard.CardPointNum[i] -= 3;
					handCard.sumNum -= 3;
					for (int j = 0; j <= 13; j++)//第一张对牌
					{
						if (handCard.CardPointNum[j] > 1 && j != i)//避免同牌
						{
							handCard.CardPointNum[j] -= 2;
							handCard.sumNum -= 2;
							tHandCardValue = GetCardValue(handCard);
							handCard.CardPointNum[j] += 2;
							handCard.sumNum += 2;
							if (bestHandCardValue.value - (bestHandCardValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
							{
								bestHandCardValue = tHandCardValue;
								bestMinCard = i;
								take1 = j;
								put = true;
							}
						}
					}
					handCard.sumNum += 3;
					handCard.CardPointNum[i] += 3;
				}
			}
			if (put)
			{
				handCard.PutCardGroup.cardTypeId = 605;
				handCard.PutCardGroup.minCard = bestMinCard;
				handCard.PutCardGroup.value = bestHandCardValue.value;
				FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, handCard.PutCardGroup.cardTypeId, bestMinCard, take1, 0, 0, 0);
				return;
			}
		}
	}
	//-------------------------单顺--------------------------
	else if (handCard.tableTypeCount / 100 == 7)
	{
		//【同类型牌压制】
		int pro = 0, start = 0, end = 0, leng = handCard.tableTypeCount % 100;//一直单连长度
		for (int i = handCard.tableMainPoint + 1; i < 12; i++)//不包含2和王
		{
			if (handCard.CardPointNum[i] > 0) pro++;
			else pro = 0;

			if (pro >= leng)
			{
				start = i-leng+1;
				end = i;
				for (int j = start; j <= end; j++)
					handCard.CardPointNum[j]--;
				handCard.sumNum -= pro;
				tHandCardValue = GetCardValue(handCard);
				handCard.sumNum += pro;
				for (int j = start; j <= end; j++)
					handCard.CardPointNum[j]++;
				if (bestHandCardValue.value - (bestHandCardValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
				{
					bestHandCardValue = tHandCardValue;
					bestMinCard = start;//保存目前计算出牌组合的最小点数
					put = true;
				}
			}
		}
		if (put)
		{
			handCard.PutCardGroup.cardTypeId = 700 + leng;//（被动出牌，接牌数量固定 leng）
			handCard.PutCardGroup.minCard = bestMinCard;
			handCard.PutCardGroup.value = bestHandCardValue.value;
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, handCard.PutCardGroup.cardTypeId, handCard.PutCardGroup.minCard, 0, 0, 0, 0);
			
			return;
		}
	}
	//-------------------------双顺-----------------------------
	else if (handCard.tableTypeCount / 100 == 8)
	{
		//【同类型牌压制】
		int pro = 0, start = 0, end = 0, leng = (handCard.tableTypeCount % 100) / 2;//一直单连长度
		for (int i = handCard.tableMainPoint + 1; i < 12; i++)//不包含2和王
		{
			if (handCard.CardPointNum[i] > 1) pro++;
			else pro = 0;

			if (pro >= leng)
			{
				start = i-leng+1;
				end = i;
				for (int j = start; j <= end; j++)
					handCard.CardPointNum[j] -= 2;
				handCard.sumNum -= pro * 2;
				tHandCardValue = GetCardValue(handCard);
				handCard.sumNum += pro * 2;
				for (int j = start; j <= end; j++)
					handCard.CardPointNum[j] += 2;
				if (bestHandCardValue.value - (bestHandCardValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
				{
					bestHandCardValue = tHandCardValue;
					bestMinCard = start;
					put = true;
				}
			}
		}
		if (put)
		{
			handCard.PutCardGroup.cardTypeId = 800 + leng * 2;//（被动出牌，接牌数量固定 leng）
			handCard.PutCardGroup.minCard = bestMinCard;
			handCard.PutCardGroup.value = bestHandCardValue.value;
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, handCard.PutCardGroup.cardTypeId, handCard.PutCardGroup.minCard, 0, 0, 0, 0);
			return;
		}
	}
	//-------------------------三顺----------------------------
	else if (handCard.tableTypeCount / 100 == 9)
	{
		//【同类型牌压制】
		int pro = 0, start = 0, end = 0, leng = (handCard.tableTypeCount % 100) / 3;//一直单连长度
		for (int i = handCard.tableMainPoint + 1; i < 12; i++)//不包含2和王
		{
			if (handCard.CardPointNum[i] > 2) pro++;
			else pro = 0;

			if (pro >= leng)
			{
				end = i;
				start = i - leng + 1;
				for (int j = start; j <= end; j++)
					handCard.CardPointNum[j] -= 3;
				handCard.sumNum -= pro * 3;
				tHandCardValue = GetCardValue(handCard);
				handCard.sumNum += pro * 3;
				for (int j = start; j <= end; j++)
					handCard.CardPointNum[j] += 3;
				if (bestHandCardValue.value - (bestHandCardValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
				{
					bestHandCardValue = tHandCardValue;
					bestMinCard = start;
					put = true;
				}
			}
		}
		if (put)
		{
			handCard.PutCardGroup.cardTypeId = 900 + leng * 3;//（被动出牌，接牌数量固定 leng）
			handCard.PutCardGroup.minCard = bestMinCard;
			handCard.PutCardGroup.value = bestHandCardValue.value;
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, handCard.PutCardGroup.cardTypeId, handCard.PutCardGroup.minCard, 0, 0, 0, 0);
			return;
		}
	}
	//--------------------------三顺带牌连---------------------
	else if (handCard.tableTypeCount / 100 == 10)
	{
		if ((handCard.tableTypeCount % 100) / 4 == 0)//三带单连
		{
			//【同类型牌压制】
			int pro = 0, start = 0, end = 0, leng = (handCard.tableTypeCount % 100) / 4;//一直单连长度
			for (int i = handCard.tableMainPoint + 1; i < 13; i++)
			{
				if (handCard.CardPointNum[i] > 2) pro++;
				else pro = 0;

				if (pro >= leng)
				{
					end = i;
					start = i - leng + 1;
					for (int j = start; j <= end; j++)
						handCard.CardPointNum[j] -= 3;
					handCard.sumNum -= pro * 3;
					if (leng == 2)//二连飞机
					{
						for (int j = 0; j <= 12; j++)//第一张单牌（循环优化）
						{
							if (handCard.CardPointNum[j] > 0 && (j<start || j>end) )
							{
								handCard.CardPointNum[j] -= 1;
								handCard.sumNum -= 1;
								for (int k = j+1; k <= 13; k++)//第二张单牌
								{
									if (handCard.CardPointNum[k] > 0 && (k<start || k>end))
									{
										handCard.CardPointNum[k] -= 1;
										handCard.sumNum -= 1;
										tHandCardValue = GetCardValue(handCard);
										handCard.CardPointNum[k] += 1;
										handCard.sumNum += 1;
										//选取总权值-轮次*7值最高的策略  因为我们认为剩余的手牌需要n次控手的机会才能出完，若轮次牌型很大（如炸弹） 则其-7的价值也会为正
										if ((bestHandCardValue.value - (bestHandCardValue.needPly * Rotation)) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
										{
											bestHandCardValue = tHandCardValue;
											bestMinCard = start;
											take1 = j;
											take2 = k;
											put = true;
										}
									}
								}
								handCard.CardPointNum[j] += 1;
								handCard.sumNum += 1;
							}
						}
					}
					else if (leng == 3)//三连飞机
					{
						for (int j = 0; j <= 11; j++)//第一张单牌
						{
							if (handCard.CardPointNum[j] > 0 && (j<start || j>end))
							{
								handCard.CardPointNum[j] -= 1;
								handCard.sumNum -= 1;
								for (int k = j+1; k <= 12; k++)//第二张单牌
								{
									if (handCard.CardPointNum[k] > 0 && (k<start || k>end))
									{
										handCard.CardPointNum[k] -= 1;
										handCard.sumNum -= 1;
										for (int l = k+1; l <= 13; l++)//第三张单牌
										{
											if (handCard.CardPointNum[l] > 0 && (l<start || l>end))
											{
												handCard.CardPointNum[l] -= 1;
												handCard.sumNum -= 1;
												tHandCardValue = GetCardValue(handCard);
												handCard.sumNum += 1;
												handCard.CardPointNum[l] += 1;
												//选取总权值-轮次*7值最高的策略  因为我们认为剩余的手牌需要n次控手的机会才能出完，若轮次牌型很大（如炸弹） 则其-7的价值也会为正
												if ((bestHandCardValue.value - (bestHandCardValue.needPly * Rotation)) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
												{
													bestHandCardValue = tHandCardValue;;
													bestMinCard = start;
													take1 = j;
													take2 = k;
													take3 = l;
													put = true;
												}
											}
										}
										handCard.CardPointNum[k] += 1;
										handCard.sumNum += 1;
									}
								}
								handCard.CardPointNum[j] += 1;
								handCard.sumNum += 1;
							}
						}
					}
					else if (leng == 4)//四连飞机
					{
						for (int j = 0; j <= 10; j++)//第一张单牌
						{
							if (handCard.CardPointNum[j] > 0 && (j<start || j>end))
							{
								handCard.CardPointNum[j] -= 1;
								handCard.sumNum -= 1;
								for (int k = j+1; k <= 11; k++)//第二张单牌
								{
									if (handCard.CardPointNum[k] > 0 && (k<start || k>end))
									{
										handCard.CardPointNum[k] -= 1;
										handCard.sumNum -= 1;
										for (int l = k+1; l <= 12; l++)//第三张单牌
										{
											if (handCard.CardPointNum[l] > 0 && (l<start || l>end))
											{
												handCard.CardPointNum[l]--;
												handCard.sumNum -= 1;
												for (int m = l+1; m <= 13; m++)//第四张单牌
												{
													if (handCard.CardPointNum[m] > 0 && (m<start || m>end))
													{
														handCard.CardPointNum[m] -= 1;
														handCard.sumNum -= 1;
														tHandCardValue = GetCardValue(handCard);
														handCard.sumNum += 1;
														handCard.CardPointNum[m] += 1;
														//选取总权值-轮次*7值最高的策略  因为我们认为剩余的手牌需要n次控手的机会才能出完，若轮次牌型很大（如炸弹） 则其-7的价值也会为正
														if ((bestHandCardValue.value - (bestHandCardValue.needPly * Rotation)) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
														{
															bestHandCardValue = tHandCardValue;;
															bestMinCard = start;
															take1 = j;
															take2 = k;
															take3 = l;
															take4 = m;
															put = true;
														}
													}
												}
												handCard.CardPointNum[l]++;
												handCard.sumNum += 1;
											}
										}
										handCard.CardPointNum[k] += 1;
										handCard.sumNum += 1;
									}
								}
								handCard.CardPointNum[j] += 1;
								handCard.sumNum += 1;
							}
						}
					}
					for (int j = start; j <= end; j++)
						handCard.CardPointNum[j] += 3;
					handCard.sumNum += pro * 3;
				}
			}
			if (put)
			{
				handCard.PutCardGroup.cardTypeId = 1000 + leng * 4;//（被动出牌，接牌数量固定 leng）
				handCard.PutCardGroup.minCard = bestMinCard;
				handCard.PutCardGroup.value = bestHandCardValue.value;
				FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, handCard.PutCardGroup.cardTypeId, handCard.PutCardGroup.minCard, take1, take2, take3, take4);
				return;
			}
		}
		else if ((handCard.tableTypeCount % 100) / 5 == 0)//-------------------------------三带对连
		{
			//【同类型牌压制】
			int pro = 0, start = 0, end = 0, leng = (handCard.tableTypeCount % 100) / 5;//一直单连长度
			for (int i = handCard.tableMainPoint + 1; i < 12; i++)//不会包含2和王
			{
				if (handCard.CardPointNum[i] > 2) pro++;
				else pro = 0;

				if (pro >= leng)
				{
					end = i;
					start = i + leng - 1;
					for (int j = start; j <= end; j++)
						handCard.CardPointNum[j] -= 3;
					handCard.sumNum -= pro * 3;
					if (leng == 2)//二连飞机
					{
						for (int j = 0; j <= 12; j++)//第一张对牌
						{
							if (handCard.CardPointNum[j] > 1 && (j<start || j>end) )
							{
								handCard.CardPointNum[j] -= 2;
								handCard.sumNum -= 2;
								for (int k = j+1; k <= 13; k++)//第二张对牌
								{
									if (handCard.CardPointNum[k] > 1 && (k<start || k>end))
									{
										handCard.CardPointNum[k] -= 2;
										handCard.sumNum -= 2;
										tHandCardValue = GetCardValue(handCard);
										handCard.CardPointNum[k] += 2;
										handCard.sumNum += 2;
										//选取总权值-轮次*7值最高的策略  因为我们认为剩余的手牌需要n次控手的机会才能出完，若轮次牌型很大（如炸弹） 则其-7的价值也会为正
										if ((bestHandCardValue.value - (bestHandCardValue.needPly * Rotation)) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
										{
											bestHandCardValue = tHandCardValue;;
											bestMinCard = i;
											take1 = j;
											take2 = k;
											put = true;
										}
									}
								}
								handCard.CardPointNum[j] += 2;
								handCard.sumNum += 2;
							}
						}
					}
					else if (leng == 3)//三连飞机
					{
						for (int j = 0; j <= 11; j++)//第一张对牌
						{
							if (handCard.CardPointNum[j] > 1 && (j<start || j>end))
							{
								handCard.CardPointNum[j] -= 2;
								handCard.sumNum -= 2;
								for (int k = j+1; k <= 12; k++)//第二张对牌
								{
									if (handCard.CardPointNum[k] > 1 && (k<start || k>end))
									{
										handCard.CardPointNum[k] -= 2;
										handCard.sumNum -= 2;
										for (int l = k+1; l <= 13; l++)//第三张对牌
										{
											if (handCard.CardPointNum[l] > 1 && (l<start || l>end))
											{
												handCard.CardPointNum[l] -= 2;
												handCard.sumNum -= 2;
												tHandCardValue = GetCardValue(handCard);
												handCard.sumNum += 2;
												handCard.CardPointNum[l] += 2;
												//选取总权值-轮次*7值最高的策略  因为我们认为剩余的手牌需要n次控手的机会才能出完，若轮次牌型很大（如炸弹） 则其-7的价值也会为正
												if ((bestHandCardValue.value - (bestHandCardValue.needPly * Rotation)) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
												{
													bestHandCardValue = tHandCardValue;;
													bestMinCard = i;
													take1 = j;
													take2 = k;
													take3 = l;
													put = true;
												}
											}
										}
										handCard.CardPointNum[k] += 2;
										handCard.sumNum += 2;
									}
								}
								handCard.CardPointNum[j] += 2;
								handCard.sumNum += 2;
							}
						}
					}
					else if (leng == 4)//四连飞机
					{
						for (int j = 0; j <= 10; j++)//第一张对牌
						{
							if (handCard.CardPointNum[j] > 1 && (j<start || j>end))
							{
								handCard.CardPointNum[j] -= 2;
								handCard.sumNum -= 2;
								for (int k = j+1; k <= 11; k++)//第二张对牌
								{
									if (handCard.CardPointNum[k] > 1 && (k<start || k>end))
									{
										handCard.CardPointNum[k] -= 2;
										handCard.sumNum -= 2;
										for (int l = k+1; l <= 12; l++)//第三张对牌
										{
											if (handCard.CardPointNum[l] > 1 && (l<start || l>end))
											{
												handCard.CardPointNum[l] -= 2;
												handCard.sumNum -= 2;
												for (int m = l+1; m <= 13; m++)//第四张对牌
												{
													if (handCard.CardPointNum[m] > 1 && (m<start || m>end))
													{
														handCard.CardPointNum[m] -= 2;
														handCard.sumNum -= 2;
														tHandCardValue = GetCardValue(handCard);
														handCard.sumNum += 2;
														handCard.CardPointNum[m] += 2;
														//选取总权值-轮次*7值最高的策略  因为我们认为剩余的手牌需要n次控手的机会才能出完，若轮次牌型很大（如炸弹） 则其-7的价值也会为正
														if ((bestHandCardValue.value - (bestHandCardValue.needPly * Rotation)) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
														{
															bestHandCardValue = tHandCardValue;;
															bestMinCard = i;
															take1 = j;
															take2 = k;
															take3 = l;
															take4 = m;
															put = true;
														}
													}
												}
												handCard.CardPointNum[l] += 2;
												handCard.sumNum += 2;
											}
										}
										handCard.CardPointNum[k] += 2;
										handCard.sumNum += 2;
									}
								}
								handCard.CardPointNum[j] += 2;
								handCard.sumNum += 2;
							}
						}
					}
					for (int j = start; j <= end; j++)
						handCard.CardPointNum[j] += 3;
					handCard.sumNum += pro * 3;
				}
			}
			if (put)
			{
				handCard.PutCardGroup.cardTypeId = 1000 + leng * 5;//（被动出牌，接牌数量固定 leng）
				handCard.PutCardGroup.minCard = bestMinCard;
				handCard.PutCardGroup.value = bestHandCardValue.value;
				FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, handCard.PutCardGroup.cardTypeId, handCard.PutCardGroup.minCard, take1, take2, take3, take4);
				return;
			}
		}
	}
	//------------------------四带二---------------------
	else if (handCard.tableTypeCount / 100 == 11)
	{
		if (handCard.tableTypeCount % 100 == 6)//四带二单
		{
			//【同类型牌压制】
			for (int i = 0; i < 13; i++)//不包含王
			{
				if (handCard.CardPointNum[i] == 4)
				{
					handCard.CardPointNum[i] -= 4;
					handCard.sumNum -= 4;
					for (int j = 0; j <= 12; j++)//循环优化
					{
						if (handCard.CardPointNum[j] > 0 && j != i)
						{
							handCard.CardPointNum[j]--;
							handCard.sumNum -= 1;
							for (int k = j+1; k <= 13; k++)
							{
								if (handCard.CardPointNum[k] > 0 && k != i )
								{
									handCard.CardPointNum[k]--;
									handCard.sumNum -= 1;
									tHandCardValue = GetCardValue(handCard);
									handCard.CardPointNum[k]++;
									handCard.sumNum += 1;
									if ((bestHandCardValue.value - (bestHandCardValue.needPly * Rotation)) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)))
									{
										bestHandCardValue = tHandCardValue;;
										bestMinCard = i;
										take1 = j;
										take2 = k;
										put = true;
									}

								}
							}
							handCard.CardPointNum[j]++;
							handCard.sumNum += 1;
						}
					}
					handCard.CardPointNum[i] += 4;
					handCard.sumNum += 4;
				}
			}
			if (put)
			{
				handCard.PutCardGroup.cardTypeId = 1100 + 6;
				handCard.PutCardGroup.minCard = bestMinCard;
				handCard.PutCardGroup.value = bestHandCardValue.value;
				FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, handCard.PutCardGroup.cardTypeId, handCard.PutCardGroup.minCard, take1, take2, 0, 0);
				return;
			}
		}
		else if (handCard.tableTypeCount % 100 == 8)//四带两对
		{
			//【同类型牌压制】
			/*本策略对于这种牌型有炸必炸，四带二相比炸弹来说会多带出两手牌，即最多提高14权值的价值
		若当前手牌价值大于14，即认为我们能炸即炸，不必考虑四带二的收益，就是这么任性。*/
			if (bestHandCardValue.value > 14)
			{
				for (int i = 0; i < 13; i++)//不包含王
				{
					if (handCard.CardPointNum[i] == 4)
					{
						handCard.PutCardGroup.cardTypeId = 204;
						handCard.PutCardGroup.minCard = i;
						handCard.PutCardGroup.value = CardTypeValue(handCard.PutCardGroup.cardTypeId, handCard.PutCardGroup.minCard);
						FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, handCard.PutCardGroup.cardTypeId, handCard.PutCardGroup.minCard, take1, take2, 0, 0);
						return;
					}
				}
				if (handCard.CardPointNum[13] > 1)
				{
					handCard.PutCardGroup.cardTypeId = 102;
					handCard.PutCardGroup.minCard = 13;
					handCard.PutCardGroup.value = 20;
					FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, handCard.PutCardGroup.cardTypeId, handCard.PutCardGroup.minCard, take1, take2, 0, 0);
					return;
				}
			}
			//权值比较小的情况，也炸
			for (int i = 0; i < 13; i++)
			{
				if (handCard.CardPointNum[i] == 4)
				{
					handCard.PutCardGroup.cardTypeId = 204;
					handCard.PutCardGroup.minCard = i;
					handCard.PutCardGroup.value = CardTypeValue(handCard.PutCardGroup.cardTypeId, handCard.PutCardGroup.minCard);
					FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, handCard.PutCardGroup.cardTypeId, handCard.PutCardGroup.minCard, take1, take2, 0, 0);
					return;
				}
			}
			if (handCard.CardPointNum[13] > 1)
			{
				handCard.PutCardGroup.cardTypeId = 102;
				handCard.PutCardGroup.minCard = 13;
				handCard.PutCardGroup.value = 20;
				FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, handCard.PutCardGroup.cardTypeId, handCard.PutCardGroup.minCard, take1, take2, 0, 0);
				return;
			}
			
		}
	}


	//======================================【炸弹王炸压制】====================================

	//炸弹王炸压制
	for (int i = 0; i < 13; i++)//炸弹
	{
		if (handCard.CardPointNum[i] == 4)
		{
			handCard.CardPointNum[i] -= 4;
			handCard.sumNum -= 4;
			tHandCardValue = GetCardValue(handCard);
			handCard.sumNum += 4;
			handCard.CardPointNum[i] += 4;
			//如果剩余手牌价值为正，证明出去的几率很大， 那么可以用炸获得先手
			if (bestHandCardValue.value - (bestHandCardValue.needPly * Rotation) <= (tHandCardValue.value - (tHandCardValue.needPly * Rotation)) || tHandCardValue.value > 0)
			{
				bestHandCardValue = tHandCardValue;
				bestMinCard = i;
				put = true;
			}
		}
	}
	if (put)
	{
		FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, 204, bestMinCard, 0, 0, 0, 0);
		handCard.PutCardGroup.cardTypeId = 204;
		handCard.PutCardGroup.minCard = bestMinCard;
		handCard.PutCardGroup.value = bestHandCardValue.value;
		return;
	}
	if (handCard.CardPointNum[13] > 1)	//王炸
	{
		//如果剩余手牌价值为正，证明出去的几率很大， 那么可以用炸获得先手
		if (bestHandCardValue.value > 20)
		{
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, 102, 13, 0, 0, 0, 0);
			handCard.PutCardGroup.cardTypeId = 102;
			handCard.PutCardGroup.minCard = 13;
			handCard.PutCardGroup.value = CardTypeValue(102, 13);
			return;
		}
	}

	//======================================【不出】============================================

	//管不上
	handCard.PutCardGroup.cardTypeId = 0;
	handCard.PutCardGroup.minCard = -1;
	handCard.PutCardGroup.value = 0;
	return;
	
}