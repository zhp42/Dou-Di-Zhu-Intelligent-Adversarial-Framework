#pragma once
#define _CRT_SECURE_NO_WARNINGS //（只会在该文件里起作用）
//可能因为一些老的.c文件使用了strcpy,scanf等不安全的函数，而报警告和错误，而导致无法编译通过。
#include <stdio.h>
#include <string.h>
#include <iostream>

#include"CallScore.h"
#include"DDZStruct.h"
#include"ScoreWay.h"
using namespace std;


//部分函数声明
void InitRound(struct Ddz* pDdz);				//M04 重置本局数据初始值
void AppendCardsToS(int iCards[], char sMsg[]);	//M05 将牌码数组转换为字符串追加(-1或)
void InitTurn(struct Ddz* pDdz);				//P01 重置本轮数据初始值
void InputMsg(struct Ddz* pDdz);				//P02 输入信息
void AnalyzeMsg(struct Ddz* pDdz);				//P03 分析处理信息
void GetDou(struct Ddz* pDdz);					//P0301 获取并处理版本信息DOU
void GetInf(struct Ddz* pDdz);					//P0302 获取并处理轮局信息INF
void GetDea(struct Ddz* pDdz);					//P0303 获取并处理牌套信息DEA
void GetBid(struct Ddz* pDdz);					//P0304 获取并处理叫牌信息BID
void GetLef(struct Ddz* pDdz);					//P0305 获取并处理底牌信息LEF
void GetPla(struct Ddz* pDdz);					//P0306 获取并处理出牌信息PLA
void UpdateMyPla(struct Ddz* pDdz);			//P030602 根据己方出牌更新数据
void UpdateHisPla(struct Ddz* pDdz);			//P030603 根据他人出牌更新数据
void GetGam(struct Ddz* pDdz);					//P0307 获取并处理胜负信息GAM
void OutputMsg(struct Ddz* pDdz);				//P04 输出信息
void CalOthers(struct Ddz* pDdz);				//P05 计算其它数据

bool JudgePutCard(struct Ddz* ddz);             //判断自己该不该出牌
int AlertCard(struct Ddz* ddz);					//报单/双函数


//测试 变量查看用函数
void Check(struct Ddz* ddz)//查看各种变量，测试时用
{
	cout << "本玩家方位编号" << ddz->cDir << "::地主玩家编号：" << ddz->cLandlord << "::胜利者编号：" << ddz->cWinner << endl;
	cout << "上次玩家编号 " << ddz->iOnPlayId[ddz->iOTmax - 2] << endl;
	cout << "叫牌过程" << " ";
	for (int i = 0; i < 3; i++)
		cout << ddz->iBid[i] << " ";
	cout << endl;
	cout << "当前叫牌：" << ddz->iBmax << endl;
	cout << "当前总出手牌数：" << ddz->iOTmax << endl;
	cout << "手中牌(DDZ中)："  ;
	for (int i = 0; ddz->iOnHand[i] >= 0; i++)
		cout << ddz->iOnHand[i] << " "  ;
	cout << endl;

	cout << "当前桌面连续pass数：" << ddz->iLastPassCount << "::当前桌面牌型张数：" << ddz->iLastTypeCount << "::当前桌面主牌点数：（"<< ddz->iLastMainPoint+3<<"）" << ddz->iLastMainPoint << endl;
	//手牌信息类
	cout << "手牌序列：";
	for (int i = 0; ddz->handCardInfor.onHandCard[i] >= 0; i++)
		cout << ddz->handCardInfor.onHandCard[i] << " ";
	cout << endl;
	cout << "手牌面值:";
	for (int i = 0; ddz->handCardInfor.onHandCard[i] >= 0; i++)
		cout << ddz->handCardInfor.onHandCard[i] / 4 + 3 << " ";
	cout << endl;
	cout << "各种牌点数：";
	for (int i = 0; i < 14; i++)
		cout << "(" << i + 3 << ")" << ddz->handCardInfor.CardPointNum[i] << " ";
	cout << endl;
	cout << "手牌总张数：" << ddz->handCardInfor.sumNum << endl;
	cout << "出牌牌型组合" << endl;
	cout << "牌型张数：" << ddz->handCardInfor.PutCardGroup.cardTypeId << "::价值:" << ddz->handCardInfor.PutCardGroup.value << "::主牌点数:" << ddz->handCardInfor.PutCardGroup.minCard;
	cout << "::带牌:" << ddz->handCardInfor.PutCardGroup.take1 << " " << ddz->handCardInfor.PutCardGroup.take2 << " " << ddz->handCardInfor.PutCardGroup.take3 << " " << ddz->handCardInfor.PutCardGroup.take4 << endl;
	cout << "出牌序列：";
	for (int i = 0; ddz->handCardInfor.PutCard[i] > -1; i++)
		cout << ddz->handCardInfor.PutCard[i] << " ";
	cout << endl;
	cout << "手牌信息类里：" << endl;
	cout << "是否可以出任意牌：" << ddz->handCardInfor.PutAnyCard << " 桌面牌型张数：" << ddz->handCardInfor.tableTypeCount << " 桌面主牌点数：" << ddz->handCardInfor.tableMainPoint << endl;
	//斗地主结构体
	cout << "斗地主结构体：" << endl;
	cout << "当前桌面主牌点数 " << ddz->iLastMainPoint << " 连续pass数 " << ddz->iLastPassCount << " 牌型张数 " << ddz->iLastTypeCount << endl;
	

}

//测试 用于查看怎么出牌算分函数
void CheckPut(struct Ddz* ddz)
{
	HandCardValue value1 = GetCardValue(ddz->handCardInfor);
	cout << "目前手牌价值 " << value1.value << " " << value1.needPly << endl;
	cout << "主动出牌后 " << endl;
	PutCardWayActive(ddz->handCardInfor);
	cout << "出牌 ";
	for (int i = 0; ddz->handCardInfor.PutCard[i] > -1; i++)
		cout << ddz->handCardInfor.PutCard[i] / 4 + 3 << " ";
	cout << endl;
	cout << "出牌价值 " << ddz->handCardInfor.PutCardGroup.value << endl;
}

/*//判断该不该出牌 true打，false 不打(主要谨防打队友)（待加入当前局势最大牌判定***************************）  
地主的牌，一定打，
队友的牌，如果是大牌，不接
只是判断
*/
bool JudgePutCard(struct Ddz* ddz)
{
	//if (ddz->iLastPassCount >= 2)//两家弃牌，自己随意出牌
	//	return true;
	//要考虑队友
	if (ddz->formation == 1)//上家是地主，打
		return true;

	if (ddz->cDir == ddz->cLandlord)//自己是地主，打
		return true ;
	//判断是不是一手牌
	CardGroup ownCardGroup = JudgeOneHand2(ddz->handCardInfor.CardPointNum);
	//同种牌型、能出   自己有王炸   自己是炸弹目前牌不是炸弹   自己炸弹比对方大
	if ((ddz->iLastTypeCount == ownCardGroup.cardTypeId && ownCardGroup.minCard > ddz->iLastMainPoint) || 
		ownCardGroup.cardTypeId/100==1 || (ownCardGroup.cardTypeId/100==2 && ddz->iLastTypeCount/100!=2) || 
		(ownCardGroup.cardTypeId/100==2 && ddz->iLastTypeCount/100==2 && ownCardGroup.minCard>ddz->iLastMainPoint))
	{
		int minCard = ownCardGroup.minCard;
		int t1 = ownCardGroup.take1;
		int t2 = ownCardGroup.take2;
		int t3 = ownCardGroup.take3;
		int t4 = ownCardGroup.take4;
		FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, ownCardGroup.cardTypeId, minCard, t1, t2, t3, t4);
		return 1;
	}

	int time = ddz->iOTmax;//当前桌面出来多少牌
	//接地主的牌
	if ((ddz->formation == 1 && ddz->iOnTable[time-1][0] != -1 && ddz->iOnTable[time - 1][0] != -2) ||  //上家地主出牌
		(ddz->formation == 3 && (ddz->iOnTable[time - 1][0] == -1 || ddz->iOnTable[time - 1][0] == -2))) //上家队友pass
	{
		return true;
	}
	else//接队友的牌
	{
		int cardPoint[14] = { 0 };
		for (int i = 0; ddz->iOnTable[time - 1][i] > -1; i++)
			cardPoint[ddz->iOnTable[time - 1][i] / 4]++;
		CardGroup parCard = JudgeOneHand2(cardPoint);
		switch (parCard.cardTypeId/100)
		{
		case 0: {//弃牌
			return true;
		}; break;
		case 1: {//火箭
			return false;
		}; break;
		case 2: {//炸弹
			return false;
		}; break;
		case 3: {//单牌
			if (parCard.minCard >= 12)//队友出大于等于 2 的牌，不出
				return false;
		}; break;
		case 4: {//对牌
			if (parCard.minCard >= 12)//
				return false;
		}; break;
		case 5: {//三条
			if (parCard.minCard >= 12)//
				return false;
		}; break;
		case 6: {//三带一
			if (parCard.minCard >= 12)//
				return false;
		}; break;
		case 7: {//单顺
			if (parCard.minCard+((parCard.cardTypeId%100)/1)-1 >= 12)//
				return false;
		}; break;
		case 8: {//双顺
			if (parCard.minCard + ((parCard.cardTypeId % 100) / 2) - 1 >= 12)//
				return false;
		}; break;
		case 9: {//三顺
			if (parCard.minCard + ((parCard.cardTypeId % 100) / 3) - 1 >= 12)//
				return false;
		}; break;
		case 10: {//三顺带牌
			if ((parCard.cardTypeId % 100) % 4 == 0)//三顺带单
			{
				if (parCard.minCard + ((parCard.cardTypeId % 100) / 4) - 1 >= 12)
					return false;;
			}
			if ((parCard.cardTypeId % 100) % 5 == 0)//三顺带对
			{
				if (parCard.minCard + ((parCard.cardTypeId % 100) / 5) - 1 >= 12)
					return false;;
			}
		}; break;
		case 11: {//四带二
			if ((parCard.cardTypeId % 100) % 6 == 0)//四带二单
			{
				if (parCard.minCard + ((parCard.cardTypeId % 100) / 6) - 1 >= 11)//
					return false;
			}
			if ((parCard.cardTypeId % 100) % 8 == 0)//四带二对
			{
				if (parCard.minCard + ((parCard.cardTypeId % 100) / 8) - 1 >= 11)//
					return false;
			}
		}; break;
		default:
			break;
		}
	}
	//该出 || 错误情况
	return true;
}

/*
//警报函数（当有人报单或者双的时候）(特殊牌局)
1 表示已经出牌 ，或者是不让下面函数出牌
0表示未出牌
*/
int AlertCard(struct Ddz* ddz)
{
	//没人报身份，正常出牌；
	if (ddz->lowCard.sum > 2 && ddz->upCard.sum > 2) return 0;

	//拆牌
	OwnCardGroup ownCard;//临时用
	int tCardPoint[14] = { 0 };
	//拷贝一份，避免数据丢失
	for (int i = 0; i < 14; i++)
		tCardPoint[i] = ddz->handCardInfor.CardPointNum[i];
	ChaiCard(tCardPoint, ownCard);
	
	int putCardType = 0;//找自己要出的牌型,12放弃


	//下家手牌只剩两张
	if (ddz->lowCard.sum <= 2)
	{
		//只剩一张牌
		if (ddz->lowCard.sum == 1)
		{
			//下家是对手
			if (ddz->formation == 2 ||ddz->formation==3)
			{
				//把炸弹变为四带二单
				while (ownCard.bomb > 0 && ownCard.single > 1)
				{
					ownCard.fourSingle11[ownCard.fourSingle].cardTypeId = 1106;
					ownCard.fourSingle11[ownCard.fourSingle].minCard = ownCard.bomb2[ownCard.bomb - 1].minCard;//最小炸弹
					ownCard.fourSingle11[ownCard.fourSingle].take1 = ownCard.single3[ownCard.single -1].minCard;//最小单牌
					ownCard.fourSingle11[ownCard.fourSingle].take2 = ownCard.single3[ownCard.single -2].minCard;
					ownCard.fourSingle++;
					//清理
					ownCard.clearOneCard(&ownCard.bomb2[ownCard.bomb - 1]); ownCard.bomb--;
					ownCard.clearOneCard(&ownCard.single3[ownCard.single - 1]);
					ownCard.clearOneCard(&ownCard.single3[ownCard.single - 2]);
					ownCard.single -= 2;
					ownCard.sum -= 1;
					ownCard.Tidy();
				}
				//把三顺变为三顺带单  或 三带一
				if (ownCard.linkThree > 0)
				{
					for (int i = ownCard.linkThree - 1; i >= 0; i--)//从最小三顺开始
					{
						if (ownCard.single >= ownCard.linkThree && ownCard.single > 0)//有足够单牌
						{
							ownCard.linkThreeSingle10[ownCard.linkThreeSingle].cardTypeId = 1000 + ((ownCard.linkThree9[i].cardTypeId % 100) / 3) * 4;
							ownCard.linkThreeSingle10[ownCard.linkThreeSingle].minCard = ownCard.linkThree9[i].minCard;
							ownCard.linkThreeSingle10[ownCard.linkThreeSingle].take1 = ownCard.single3[ownCard.single - 1].minCard;
							ownCard.linkThreeSingle10[ownCard.linkThreeSingle].take1 = ownCard.single3[ownCard.single - 2].minCard;
							ownCard.clearOneCard(&ownCard.single3[ownCard.single - 1]);
							ownCard.clearOneCard(&ownCard.single3[ownCard.single - 2]);
							ownCard.single -= 2;
							if (((ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId % 100) / 3) >= 3)///三带
							{
								ownCard.linkThreeSingle10[ownCard.linkThreeSingle].take3 = ownCard.single3[ownCard.single - 1].minCard;
								ownCard.clearOneCard(&ownCard.single3[ownCard.single - 1]);
								ownCard.single -= 1;
								if (((ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId % 100) / 3) >= 4)//四带
								{
									ownCard.linkThreeSingle10[ownCard.linkThreeSingle].take4 = ownCard.single3[ownCard.single - 1].minCard;
									ownCard.clearOneCard(&ownCard.single3[ownCard.single - 1]);
									ownCard.single -= 1;
								}
							}
							ownCard.linkThreeSingle++;
							ownCard.clearOneCard(&ownCard.linkThree9[i]); ownCard.linkThree--;
							ownCard.Tidy();
						}
						else if (ownCard.single < ownCard.linkThree && ownCard.single > 0)//没有足够的单牌，拆为三带一
						{// 先拆为三张，后面再合成三带一
							int lian = (ownCard.linkThree9[i].cardTypeId % 100) / 3;
							int min = ownCard.linkThree9[i].minCard;
							for (int j = 0; j < lian; j++)
							{
								ownCard.three5[ownCard.three].cardTypeId = 503;
								ownCard.three5[ownCard.three].minCard = min + lian - j-1;
								ownCard.three++;
							}
							ownCard.clearOneCard(&ownCard.linkThree9[i]);
							ownCard.linkThree--;
							ownCard.Tidy();
						}
					}
				}
				//吧三张变为三带一
				if (ownCard.three > 0 && ownCard.single > 0)
				{
					while (ownCard.three > 0 && ownCard.single > 0)
					{
						ownCard.threeOne6[ownCard.threeOne].cardTypeId = 604;
						ownCard.threeOne6[ownCard.threeOne].minCard = ownCard.three5[ownCard.three - 1].minCard;
						ownCard.threeOne6[ownCard.threeOne].take1 = ownCard.single3[ownCard.single - 1].minCard;
						ownCard.threeOne++;
						ownCard.clearOneCard(&ownCard.three5[ownCard.three - 1]); ownCard.three--;
						ownCard.clearOneCard(&ownCard.single3[ownCard.single - 1]); ownCard.single--;
					}
				}
				
				if (ddz->handCardInfor.PutAnyCard == 0) //被动出牌
				{
					//压制
					if (ddz->handCardInfor.CardPointNum[13] >= 2)//有王炸
					{
						FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 102, 13, -1, -1, -1, -1);
						return 1;
					}
					//炸弹压制
					for(int i=0;i<13;i++)
						if (ddz->handCardInfor.CardPointNum[i] == 4)//自己有炸弹
						{
							//对方不是炸弹或者王炸 || 对方炸弹不够自己大
							if (ddz->iLastTypeCount / 100 != 1 && ddz->iLastTypeCount / 100 != 2)
							{
								FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 204, i, -1, -1, -1, -1);
								return 1;
							}
							if ( ddz->iLastTypeCount / 100 == 2 && ddz->iLastMainPoint < i)
							{
								FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 204, i, -1, -1, -1, -1);
								return 1;
							}
						}
					//正常出牌
					return 0;//让赋值评分自己出牌
				}
				else {
					//自己主动出牌
					//按以下顺序出牌
				//三顺带单10》三顺带双10》三顺9》双顺8》单顺7》三带一单6》三带对6》三条5》四带二单11》四带二对11》对牌4》炸弹2》火箭1》3单牌
					switch (10)
					{
					case 10: {//三顺带牌
						if (ownCard.linkThreeSingle > 0)
						{
							int t1 = ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].take1;
							int t2 = ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].take2;
							int t3 = ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].take3;
							int t4 = ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].take4;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].cardTypeId, ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].minCard, t1, t2, t3, t4);
							return 1;
						}
						if (ownCard.linkThreeTwo > 0)
						{
							int t1 = ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].take1;
							int t2 = ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].take2;
							int t3 = ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].take3;
							int t4 = ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].take4;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].cardTypeId, ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].minCard, t1, t2, t3, t4);
							return 1;
						}
					}
					case 9: {//三顺
						if (ownCard.linkThree > 0)
						{
							int cardtype = ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId;
							int min = ownCard.linkThree9[ownCard.linkThree - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 8: {//双顺8
						if (ownCard.linkTwo > 0)
						{
							int cardtype = ownCard.linkDouble8[ownCard.linkTwo - 1].cardTypeId;
							int min = ownCard.linkDouble8[ownCard.linkTwo - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 7: {//单顺7
						if (ownCard.linkSingle > 0)
						{
							int cardtype = ownCard.linkSingle7[ownCard.linkSingle - 1].cardTypeId;
							int min = ownCard.linkSingle7[ownCard.linkSingle - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 6: {//三带一
						if (ownCard.threeOne > 0 )
						{
							int cardtype = ownCard.threeOne6[ownCard.threeOne - 1].cardTypeId;
							int min = ownCard.threeOne6[ownCard.threeOne - 1].minCard;
							int t1 = ownCard.threeOne6[ownCard.threeOne - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, -1, -1, -1);
							return 1;
						}
						if (ownCard.threeTwo > 0)
						{
							int cardtype = ownCard.threeDouble6[ownCard.threeTwo - 1].cardTypeId;
							int min = ownCard.threeDouble6[ownCard.threeTwo - 1].minCard;
							int t1 = ownCard.threeDouble6[ownCard.threeTwo - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, -1, -1, -1);
							return 1;
						}
					}
					case 5: {//三条5
						if (ownCard.three > 0)
						{
							int cardtype = ownCard.three5[ownCard.three - 1].cardTypeId;
							int min = ownCard.three5[ownCard.three - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 11: {//四带二单11
						if (ownCard.fourSingle > 0)
						{
							int cardtype = ownCard.fourSingle11[ownCard.fourSingle - 1].cardTypeId;
							int min = ownCard.fourSingle11[ownCard.fourSingle - 1].minCard;
							int t1 = ownCard.fourSingle11[ownCard.fourSingle - 1].take1;
							int t2 = ownCard.fourSingle11[ownCard.fourSingle - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, t2, -1, -1);
							return 1;
						}
						if (ownCard.fourTwo > 0)
						{
							int cardtype = ownCard.fourDouble11[ownCard.fourTwo - 1].cardTypeId;
							int min = ownCard.fourDouble11[ownCard.fourTwo - 1].minCard;
							int t1 = ownCard.fourDouble11[ownCard.fourTwo - 1].take1;
							int t2 = ownCard.fourDouble11[ownCard.fourTwo - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, t2, -1, -1);
							return 1;
						}
					}
					case 4: {//对牌4》
						if (ownCard.two > 0)
						{
							int cardtype = ownCard.double4[ownCard.two - 1].cardTypeId;
							int min = ownCard.double4[ownCard.two - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 2: {//炸弹2
						if (ownCard.bomb > 0)
						{
							int cardtype = ownCard.bomb2[ownCard.bomb - 1].cardTypeId;
							int min = ownCard.bomb2[ownCard.bomb - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 1: {//火箭1
						if (ownCard.rocket > 0)
						{
							int cardtype = ownCard.rocket1.cardTypeId;
							int min = ownCard.rocket1.minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 3: {//3单牌
						if (ownCard.single > 0)
						{
							//从大到小出
							ownCard.Tidy();
							int cardtype = ownCard.single3[0].cardTypeId;
							int min = ownCard.single3[0].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					default: return 0;
						break;
					}
				}
			}
			//下家是队友
			else if (ddz->formation == 1)
			{
				//如果上家对手不出牌
				if (ddz->iOnTable[ddz->iOTmax - 1][0] < 0)
				{
					//让牌给队友
					ddz->handCardInfor.ClearPutCard();
					return 1;
					
				}
				else
				{
					int min;
					//找自己最小牌
					for (int i = 0; i < 14; i++)
						if (ddz->handCardInfor.CardPointNum[i] > 0)
							min = i;
					if (ddz->handCardInfor.PutAnyCard == 0)//被动出牌
					{
						if (ddz->iLastTypeCount / 100 != 3)//目前不是出单牌
						{
							//为了接队友，压制地主牌
							if (ddz->handCardInfor.CardPointNum[13] >= 2)//有王炸
							{
								FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 102, 13, -1, -1, -1, -1);
								return 1;
							}
							//炸弹压制
							for (int i = 0; i < 13; i++)
								if (ddz->handCardInfor.CardPointNum[i] == 4)//自己有炸弹
								{
									//对方不是炸弹或者王炸 || 对方炸弹不够自己大
									if ((ddz->iLastTypeCount / 100 != 1 && ddz->iLastTypeCount / 100 != 2) || (ddz->iLastTypeCount / 100 == 2 && ddz->iLastMainPoint < i))
									{
										FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 204, i, -1, -1, -1, -1);
										return 1;
									}

								}
							//正常出牌
							return 0;//让赋值评分自己出牌
						}
						else {
							//目前出单牌，下家队友只剩一张
							//找自己最小单牌
							int minCard = -1;
							for (int i = 0; i < 14; i++)
								if (ddz->handCardInfor.CardPointNum[i] > 0)
								{
									minCard = i;
									break;
								}
							//如果该单牌小于等7 || 该单牌比自己最小单牌小  -》不出
							if (ddz->iLastMainPoint <= 4 || (minCard != -1 && ddz->iLastMainPoint <= minCard))
							{
								//弃牌
								ddz->handCardInfor.ClearPutCard();
								return 1;
							}
							//自己有比对方更小的单牌
							if (ddz->iLastMainPoint - minCard >= 4 && minCard != -1)
							{
								//为了接队友，压制地主牌
								if (ddz->handCardInfor.CardPointNum[13] >= 2)//有王炸
								{
									FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 102, 13, -1, -1, -1, -1);
									return 1;
								}
								//炸弹压制
								for (int i = 0; i < 13; i++)
									if (ddz->handCardInfor.CardPointNum[i] == 4)//自己有炸弹
									{
										//对方不是炸弹或者王炸 || 对方炸弹不够自己大
										if ((ddz->iLastTypeCount / 100 != 1 && ddz->iLastTypeCount / 100 != 2) || (ddz->iLastTypeCount / 100 == 2 && ddz->iLastMainPoint < i))
										{
											FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 204, i, -1, -1, -1, -1);
											return 1;
										}

									}
								//正常出牌
								return 0;//让赋值评分自己出牌
							}
						}
					}
					else {//主动出牌

						//回看上一次有没有出牌给他
						if (ddz->iOnTable[ddz->iOTmax - 2 - 1][1] < 0 && ddz->iOnTable[ddz->iOTmax - 2 - 1][0] > -1)//上次自己出单牌给队友   
						{
							if (ddz->iOnTable[ddz->iOTmax - 2 - 1][0] / 4 <= min) {
								ddz->fnohope = 1;
								return 0;//最小牌队友要不起，放弃队友,让出牌函数自己打
							}
						}
						//拆最小牌协助队友
						if (!(ddz->fnohope)) {
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 301, min, -1, -1, -1, -1);
							return 1;
						}
					}
				}
				
				
			}

		}
		//两张牌
		else {
			//下家是对手
			if (ddz->formation == 3|| ddz->formation == 2)
			{
				if (ddz->handCardInfor.PutAnyCard == 0)//被动出牌
				{
					//if (ddz->iOnTable[ddz->iOTmax - 1][1] < 0)//上家队友出单牌 
					//	return 0;//让评分函数自己出
					if (ddz->iLastTypeCount / 100 == 4)//目前是对牌
					{
						//压制(之前已经有防打队友函数)
						if (ddz->handCardInfor.CardPointNum[13] >= 2)//有王炸
						{
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 102, 13, -1, -1, -1, -1);
							return 1;
						}
						//炸弹压制
						for (int i = 0; i < 13; i++)
							if (ddz->handCardInfor.CardPointNum[i] == 4)//自己有炸弹
							{
								//对方不是炸弹或者王炸 || 对方炸弹不够自己大
								if ((ddz->iLastTypeCount / 100 != 1 && ddz->iLastTypeCount / 100 != 2) || (ddz->iLastTypeCount / 100 == 2 && ddz->iLastMainPoint < i))
								{
									FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 204, i, -1, -1, -1, -1);
									return 1;
								}

							}
						return 0;
					}
				}
				else {
					//主动出牌
					//把炸弹变为四带二对
					while (ownCard.bomb > 0 && ownCard.two > 1)
					{
						ownCard.fourDouble11[ownCard.fourTwo].cardTypeId = 1108;
						ownCard.fourDouble11[ownCard.fourTwo].minCard = ownCard.bomb2[ownCard.bomb - 1].minCard;//最小炸弹
						ownCard.fourDouble11[ownCard.fourTwo].take1 = ownCard.double4[ownCard.two - 1].minCard;
						ownCard.fourDouble11[ownCard.fourTwo].take2 = ownCard.double4[ownCard.two - 2].minCard;
						ownCard.fourTwo++;
						//清理
						ownCard.clearOneCard(&ownCard.bomb2[ownCard.bomb - 1]); ownCard.bomb--;
						ownCard.clearOneCard(&ownCard.double4[ownCard.two - 1]);
						ownCard.clearOneCard(&ownCard.double4[ownCard.two - 2]);
						ownCard.two -= 2;
						ownCard.sum -= 1;
						ownCard.Tidy();
					}
					//把三顺变为三顺带对  或 三带一对
					if (ownCard.linkThree > 0)
					{
						for (int i = ownCard.linkThree - 1; i >= 0; i--)//从最小三顺开始
						{
							if (ownCard.two >= ownCard.linkThree && ownCard.two > 0)//有足够单牌
							{
								ownCard.linkThreeDouble10[ownCard.linkThreeTwo].cardTypeId = 1000 + ((ownCard.linkThree9[i].cardTypeId % 100) / 3) * 5;
								ownCard.linkThreeDouble10[ownCard.linkThreeTwo].minCard = ownCard.linkThree9[i].minCard;
								ownCard.linkThreeDouble10[ownCard.linkThreeTwo].take1 = ownCard.double4[ownCard.two - 1].minCard;
								ownCard.linkThreeDouble10[ownCard.linkThreeTwo].take1 = ownCard.double4[ownCard.two - 2].minCard;
								ownCard.clearOneCard(&ownCard.double4[ownCard.two - 1]);
								ownCard.clearOneCard(&ownCard.double4[ownCard.two - 2]);
								ownCard.two -= 2;
								if (((ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId % 100) / 3) >= 3)///三带
								{
									ownCard.linkThreeDouble10[ownCard.linkThreeTwo].take3 = ownCard.double4[ownCard.two - 1].minCard;
									ownCard.clearOneCard(&ownCard.double4[ownCard.two - 1]);
									ownCard.two -= 1;
									if (((ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId % 100) / 3) >= 4)//四带
									{
										ownCard.linkThreeDouble10[ownCard.linkThreeTwo].take4 = ownCard.double4[ownCard.two - 1].minCard;
										ownCard.clearOneCard(&ownCard.double4[ownCard.two - 1]);
										ownCard.two -= 1;
									}
								}
								ownCard.linkThreeTwo++;
								ownCard.clearOneCard(&ownCard.linkThree9[i]); ownCard.linkThree--;//三顺减少
								ownCard.Tidy();
							}
							else if (ownCard.single < ownCard.linkThree && ownCard.single > 0)//没有足够的单牌，拆为三带一对
							{// 先拆为三张，后面再合成三带一
								int lian = (ownCard.linkThree9[i].cardTypeId % 100) / 3;
								int min = ownCard.linkThree9[i].minCard;
								for (int j = 0; j < lian; j++)
								{
									ownCard.three5[ownCard.three].cardTypeId = 503;
									ownCard.three5[ownCard.three].minCard = min + lian - j - 1;
									ownCard.three++;
								}
								ownCard.clearOneCard(&ownCard.linkThree9[i]);
								ownCard.linkThree--;
								ownCard.Tidy();
							}
						}
					}
					//吧三张变为三带一对
					if (ownCard.three > 0 && ownCard.two > 0)
					{
						while (ownCard.three > 0 && ownCard.two > 0)
						{
							ownCard.threeDouble6[ownCard.threeTwo].cardTypeId = 605;
							ownCard.threeDouble6[ownCard.threeTwo].minCard = ownCard.three5[ownCard.three - 1].minCard;
							ownCard.threeDouble6[ownCard.threeTwo].take1 = ownCard.double4[ownCard.two - 1].minCard;
							ownCard.threeTwo++;
							ownCard.clearOneCard(&ownCard.three5[ownCard.three - 1]); ownCard.three--;
							ownCard.clearOneCard(&ownCard.double4[ownCard.two - 1]); ownCard.two--;
						}
					}
					//按以下顺序出牌
				//三顺带单10》三顺带双10》三顺9》双顺8》单顺7》三带一单6》三带对6》三条5》四带二单11》四带二对11》炸弹2》火箭1》3单牌》 对牌4
					switch (10)
					{
					case 10: {//三顺带单
						if (ownCard.linkThreeSingle > 0)
						{
							int t1 = ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].take1;
							int t2 = ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].take2;
							int t3 = ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].take3;
							int t4 = ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].take4;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].cardTypeId, ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].minCard, t1, t2, t3, t4);
							return 1;
						}
						if (ownCard.linkThreeTwo > 0)
						{
							int t1 = ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].take1;
							int t2 = ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].take2;
							int t3 = ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].take3;
							int t4 = ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].take4;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].cardTypeId, ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].minCard, t1, t2, t3, t4);
							return 1;
						}
					}
					case 9: {//三顺
						if (ownCard.linkThree > 0)
						{
							int cardtype = ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId;
							int min = ownCard.linkThree9[ownCard.linkThree - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 8: {//双顺8
						if (ownCard.linkTwo > 0)
						{
							int cardtype = ownCard.linkDouble8[ownCard.linkTwo - 1].cardTypeId;
							int min = ownCard.linkDouble8[ownCard.linkTwo - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 7: {//单顺7
						if (ownCard.linkSingle > 0)
						{
							int cardtype = ownCard.linkSingle7[ownCard.linkSingle - 1].cardTypeId;
							int min = ownCard.linkSingle7[ownCard.linkSingle - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 6: {//三带一
						if (ownCard.threeOne > 0)//带单
						{
							int cardtype = ownCard.threeOne6[ownCard.threeOne - 1].cardTypeId;
							int min = ownCard.threeOne6[ownCard.threeOne - 1].minCard;
							int t1 = ownCard.threeOne6[ownCard.threeOne - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, -1, -1, -1);
							return 1;
						}
						if (ownCard.threeTwo > 0)//带对
						{
							int cardtype = ownCard.threeDouble6[ownCard.threeTwo - 1].cardTypeId;
							int min = ownCard.threeDouble6[ownCard.threeTwo - 1].minCard;
							int t1 = ownCard.threeDouble6[ownCard.threeTwo - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, -1, -1, -1);
							return 1;
						}
					}
					case 5: {//三条5
						if (ownCard.three > 0)
						{
							int cardtype = ownCard.three5[ownCard.three - 1].cardTypeId;
							int min = ownCard.three5[ownCard.three - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 11: {//四带二
						if (ownCard.fourSingle > 0)//带单
						{
							int cardtype = ownCard.fourSingle11[ownCard.fourSingle - 1].cardTypeId;
							int min = ownCard.fourSingle11[ownCard.fourSingle - 1].minCard;
							int t1 = ownCard.fourSingle11[ownCard.fourSingle - 1].take1;
							int t2 = ownCard.fourSingle11[ownCard.fourSingle - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, t2, -1, -1);
							return 1;
						}
						if (ownCard.fourTwo > 0)//带对
						{
							int cardtype = ownCard.fourDouble11[ownCard.fourTwo - 1].cardTypeId;
							int min = ownCard.fourDouble11[ownCard.fourTwo - 1].minCard;
							int t1 = ownCard.fourDouble11[ownCard.fourTwo - 1].take1;
							int t2 = ownCard.fourDouble11[ownCard.fourTwo - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, t2, -1, -1);
							return 1;
						}
					}
					case 2: {//炸弹2
						if (ownCard.bomb > 0)
						{
							int cardtype = ownCard.bomb2[ownCard.bomb - 1].cardTypeId;
							int min = ownCard.bomb2[ownCard.bomb - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 1: {//火箭1
						if (ownCard.rocket > 0)
						{
							int cardtype = ownCard.rocket1.cardTypeId;
							int min = ownCard.rocket1.minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 3: {//3单牌
						if (ownCard.single > 0)
						{
							//出最小牌   //这里不是应该出最大牌压制地主吗 已修改 2020.8
							ownCard.Tidy();
							/*int cardtype = ownCard.single3[ownCard.single-1].cardTypeId;
							int min = ownCard.single3[ownCard.single-1].minCard;*/
							int cardtype = ownCard.single3[0].cardTypeId;
							int max = ownCard.single3[0].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, max, -1, -1, -1, -1);
							return 1;
						}
					}
					case 4: {//对牌4》
						if (ownCard.two > 0)
						{
							//同上单牌
							/*int cardtype = ownCard.double4[ownCard.two - 1].cardTypeId;
							int min = ownCard.double4[ownCard.two - 1].minCard;*/
							int cardtype = ownCard.single3[0].cardTypeId;
							int max = ownCard.single3[0].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, max, -1, -1, -1, -1);
							return 1;
						}
					}
					default: return 0;
						break;
					}

				}
			}
			//下家是队友
			if (ddz->formation == 1)
			{
				if (ddz->handCardInfor.PutAnyCard == 0)//被动出牌
				{
					//如果上家对手不出牌
					if (ddz->iOnTable[ddz->iOTmax - 1][0] < 0)
					{
						//让牌给队友
						ddz->handCardInfor.ClearPutCard();
						return 1;

					}
					//上家对手出牌了
					else 
					{
						//找自己最小对牌
						int minCard = -1;
						for (int i = 0; i < 14; i++)
							if (ddz->handCardInfor.CardPointNum[i] >= 2)
							{
								minCard = i;
								break;
							}
						//上家出了比自己更小的对牌，不出
						if (ddz->iLastTypeCount / 100 == 4 && ddz->iLastMainPoint <= minCard)
						{
							ddz->handCardInfor.ClearPutCard();
							return 1;
						}
						//自己有更小的对牌  || 目前不是对牌
						else if ((ddz->iLastTypeCount / 100 == 4 && ddz->iLastMainPoint - minCard >= 4) || ddz->iLastTypeCount / 100 != 4)
						{
							//压制
							if (ddz->handCardInfor.CardPointNum[13] >= 2)//有王炸
							{
								FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 102, 13, -1, -1, -1, -1);
								return 1;
							}
							//炸弹压制
							for (int i = 0; i < 13; i++)
								if (ddz->handCardInfor.CardPointNum[i] == 4)//自己有炸弹
								{
									//对方不是炸弹或者王炸 || 对方炸弹不够自己大
									if ((ddz->iLastTypeCount / 100 != 1 && ddz->iLastTypeCount / 100 != 2) || (ddz->iLastTypeCount / 100 == 2 && ddz->iLastMainPoint < i))
									{
										FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 204, i, -1, -1, -1, -1);
										return 1;
									}

								}
							//正常出牌
							return 0;//让赋值评分自己出牌
						}
					}
					
				}
				else {
					//主动出牌
					//优先出对牌  有待优化：如果队友一直报双会隔一轮出一次最小对子(已优化)
					if (AnalyzeTypeCount(ddz->iOnTable[ddz->iOTmax - 2 - 1]) / 100 == 4) 
					{
						if (ddz->iOnTable[ddz->iOTmax - 1 - 1][0] < 0) {
							ddz->fnohope = 1;
							return 0;
						}//队友不要，放弃队友
							
					}
					if (!(ddz->fnohope)&&ownCard.two > 0)//自己还有对牌
					{
						//先出小牌
						int minCard = ownCard.double4[ownCard.two - 1].minCard;
						FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 402, minCard, -1, -1, -1, -1);
						return 1;
					}
					return 0;//让评分函数出
				}
			}

		}
	}
	//上家只剩两手牌
	if (ddz->upCard.sum <= 2)
	{
		//剩一张牌
		if (ddz->upCard.sum == 1)
		{
			//上家是对手
			if (ddz->formation == 1|| ddz->formation == 2)
			{
				//顶牌压制，然后出非单牌（除非只有单牌）
				//把炸弹变为四带二单
								while (ownCard.bomb > 0 && ownCard.single > 1)
				{
					ownCard.fourSingle11[ownCard.fourSingle].cardTypeId = 1106;
					ownCard.fourSingle11[ownCard.fourSingle].minCard = ownCard.bomb2[ownCard.bomb - 1].minCard;//最小炸弹
					ownCard.fourSingle11[ownCard.fourSingle].take1 = ownCard.single3[ownCard.single -1].minCard;//最小单牌
					ownCard.fourSingle11[ownCard.fourSingle].take2 = ownCard.single3[ownCard.single -2].minCard;
					ownCard.fourSingle++;
					//清理
					ownCard.clearOneCard(&ownCard.bomb2[ownCard.bomb - 1]); ownCard.bomb--;
					ownCard.clearOneCard(&ownCard.single3[ownCard.single - 1]);
					ownCard.clearOneCard(&ownCard.single3[ownCard.single - 2]);
					ownCard.single -= 2;
					ownCard.sum -= 1;
					ownCard.Tidy();
				}
				//把三顺变为三顺带单  或 三带一
				if (ownCard.linkThree > 0)
				{
					for (int i = ownCard.linkThree - 1; i >= 0; i--)//从最小三顺开始
					{
						if (ownCard.single >= ownCard.linkThree && ownCard.single > 0)//有足够单牌
						{
							ownCard.linkThreeSingle10[ownCard.linkThreeSingle].cardTypeId = 1000 + ((ownCard.linkThree9[i].cardTypeId % 100) / 3) * 4;
							ownCard.linkThreeSingle10[ownCard.linkThreeSingle].minCard = ownCard.linkThree9[i].minCard;
							ownCard.linkThreeSingle10[ownCard.linkThreeSingle].take1 = ownCard.single3[ownCard.single - 1].minCard;
							ownCard.linkThreeSingle10[ownCard.linkThreeSingle].take1 = ownCard.single3[ownCard.single - 2].minCard;
							ownCard.clearOneCard(&ownCard.single3[ownCard.single - 1]);
							ownCard.clearOneCard(&ownCard.single3[ownCard.single - 2]);
							ownCard.single -= 2;
							if (((ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId % 100) / 3) >= 3)///三带
							{
								ownCard.linkThreeSingle10[ownCard.linkThreeSingle].take3 = ownCard.single3[ownCard.single - 1].minCard;
								ownCard.clearOneCard(&ownCard.single3[ownCard.single - 1]);
								ownCard.single -= 1;
								if (((ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId % 100) / 3) >= 4)//四带
								{
									ownCard.linkThreeSingle10[ownCard.linkThreeSingle].take4 = ownCard.single3[ownCard.single - 1].minCard;
									ownCard.clearOneCard(&ownCard.single3[ownCard.single - 1]);
									ownCard.single -= 1;
								}
							}
							ownCard.linkThreeSingle++;
							ownCard.clearOneCard(&ownCard.linkThree9[i]); ownCard.linkThree--;
							ownCard.Tidy();
						}
						else if (ownCard.single < ownCard.linkThree && ownCard.single > 0)//没有足够的单牌，拆为三带一
						{// 先拆为三张，后面再合成三带一
							int lian = (ownCard.linkThree9[i].cardTypeId % 100) / 3;
							int min = ownCard.linkThree9[i].minCard;
							for (int j = 0; j < lian; j++)
							{
								ownCard.three5[ownCard.three].cardTypeId = 503;
								ownCard.three5[ownCard.three].minCard = min + lian - j-1;
								ownCard.three++;
							}
							ownCard.clearOneCard(&ownCard.linkThree9[i]);
							ownCard.linkThree--;
							ownCard.Tidy();
						}
					}
				}
				//吧三张变为三带一
				if (ownCard.three > 0 && ownCard.single > 0)
				{
					while (ownCard.three > 0 && ownCard.single > 0)
					{
						ownCard.threeOne6[ownCard.threeOne].cardTypeId = 604;
						ownCard.threeOne6[ownCard.threeOne].minCard = ownCard.three5[ownCard.three - 1].minCard;
						ownCard.threeOne6[ownCard.threeOne].take1 = ownCard.single3[ownCard.single - 1].minCard;
						ownCard.threeOne++;
						ownCard.clearOneCard(&ownCard.three5[ownCard.three - 1]); ownCard.three--;
						ownCard.clearOneCard(&ownCard.single3[ownCard.single - 1]); ownCard.single--;
					}
				}

				if (ddz->handCardInfor.PutAnyCard == 0) //被动出牌
				{
					//压制
					if (ddz->handCardInfor.CardPointNum[13] >= 2)//有王炸
					{
						FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 102, 13, -1, -1, -1, -1);
						return 1;
					}
					//炸弹压制
					for(int i=0;i<13;i++)
						if (ddz->handCardInfor.CardPointNum[i] == 4)//自己有炸弹
						{
							//对方不是炸弹或者王炸 || 对方炸弹不够自己大
							if (ddz->iLastTypeCount / 100 != 1 && ddz->iLastTypeCount / 100 != 2)
							{
								FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 204, i, -1, -1, -1, -1);
								return 1;
							}
							if ( ddz->iLastTypeCount / 100 == 2 && ddz->iLastMainPoint < i)
							{
								FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 204, i, -1, -1, -1, -1);
								return 1;
							}
						}
					//正常出牌
					return 0;//让赋值评分自己出牌
				}
				else {
					//自己主动出牌
					//按以下顺序出牌
				//三顺带单10》三顺带双10》三顺9》双顺8》单顺7》三带一单6》三带对6》三条5》四带二单11》四带二对11》对牌4》炸弹2》火箭1》3单牌
					switch (10)
					{
					case 10: {//三顺带牌
						if (ownCard.linkThreeSingle > 0)
						{
							int t1 = ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].take1;
							int t2 = ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].take2;
							int t3 = ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].take3;
							int t4 = ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].take4;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].cardTypeId, ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].minCard, t1, t2, t3, t4);
							return 1;
						}
						if (ownCard.linkThreeTwo > 0)
						{
							int t1 = ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].take1;
							int t2 = ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].take2;
							int t3 = ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].take3;
							int t4 = ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].take4;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].cardTypeId, ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].minCard, t1, t2, t3, t4);
							return 1;
						}
					}
					case 9: {//三顺
						if (ownCard.linkThree > 0)
						{
							int cardtype = ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId;
							int min = ownCard.linkThree9[ownCard.linkThree - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 8: {//双顺8
						if (ownCard.linkTwo > 0)
						{
							int cardtype = ownCard.linkDouble8[ownCard.linkTwo - 1].cardTypeId;
							int min = ownCard.linkDouble8[ownCard.linkTwo - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 7: {//单顺7
						if (ownCard.linkSingle > 0)
						{
							int cardtype = ownCard.linkSingle7[ownCard.linkSingle - 1].cardTypeId;
							int min = ownCard.linkSingle7[ownCard.linkSingle - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 6: {//三带一
						if (ownCard.threeOne > 0 )
						{
							int cardtype = ownCard.threeOne6[ownCard.threeOne - 1].cardTypeId;
							int min = ownCard.threeOne6[ownCard.threeOne - 1].minCard;
							int t1 = ownCard.threeOne6[ownCard.threeOne - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, -1, -1, -1);
							return 1;
						}
						if (ownCard.threeTwo > 0)
						{
							int cardtype = ownCard.threeDouble6[ownCard.threeTwo - 1].cardTypeId;
							int min = ownCard.threeDouble6[ownCard.threeTwo - 1].minCard;
							int t1 = ownCard.threeDouble6[ownCard.threeTwo - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, -1, -1, -1);
							return 1;
						}
					}
					case 5: {//三条5
						if (ownCard.three > 0)
						{
							int cardtype = ownCard.three5[ownCard.three - 1].cardTypeId;
							int min = ownCard.three5[ownCard.three - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 11: {//四带二单11
						if (ownCard.fourSingle > 0)
						{
							int cardtype = ownCard.fourSingle11[ownCard.fourSingle - 1].cardTypeId;
							int min = ownCard.fourSingle11[ownCard.fourSingle - 1].minCard;
							int t1 = ownCard.fourSingle11[ownCard.fourSingle - 1].take1;
							int t2 = ownCard.fourSingle11[ownCard.fourSingle - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, t2, -1, -1);
							return 1;
						}
						if (ownCard.fourTwo > 0)
						{
							int cardtype = ownCard.fourDouble11[ownCard.fourTwo - 1].cardTypeId;
							int min = ownCard.fourDouble11[ownCard.fourTwo - 1].minCard;
							int t1 = ownCard.fourDouble11[ownCard.fourTwo - 1].take1;
							int t2 = ownCard.fourDouble11[ownCard.fourTwo - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, t2, -1, -1);
							return 1;
						}
					}
					case 4: {//对牌4》
						if (ownCard.two > 0)
						{
							int cardtype = ownCard.double4[ownCard.two - 1].cardTypeId;
							int min = ownCard.double4[ownCard.two - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 2: {//炸弹2
						if (ownCard.bomb > 0)
						{
							int cardtype = ownCard.bomb2[ownCard.bomb - 1].cardTypeId;
							int min = ownCard.bomb2[ownCard.bomb - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 1: {//火箭1
						if (ownCard.rocket > 0)
						{
							int cardtype = ownCard.rocket1.cardTypeId;
							int min = ownCard.rocket1.minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 3: {//3单牌
						if (ownCard.single > 0)
						{
							//从大到小出
							ownCard.Tidy();
							int cardtype = ownCard.single3[0].cardTypeId;
							int min = ownCard.single3[0].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					default: return 0;
						break;
					}
				}


			}
			//上家是队友
			if (ddz->formation == 3)
			{
				//被动出牌
				if (ddz->handCardInfor.PutAnyCard == 0)
				{
					if (ddz->iOnTable[ddz->iOTmax - 1][0] < 0)//如果队友不要，则压制地主出牌，争取主动出牌并让牌于队友的机会 
					{
						//压制
						if (ddz->handCardInfor.CardPointNum[13] >= 2)//有王炸
						{
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 102, 13, -1, -1, -1, -1);
							return 1;
						}
						//炸弹压制
						for (int i = 0; i < 13; i++)
							if (ddz->handCardInfor.CardPointNum[i] == 4)//自己有炸弹
							{
								//对方不是炸弹或者王炸 || 对方炸弹不够自己大
								if (ddz->iLastTypeCount / 100 != 1 && ddz->iLastTypeCount / 100 != 2)
								{
									FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 204, i, -1, -1, -1, -1);
									return 1;
								}
								if (ddz->iLastTypeCount / 100 == 2 && ddz->iLastMainPoint < i)
								{
									FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 204, i, -1, -1, -1, -1);
									return 1;
								}
							}
						//正常出牌
						return 0;//让赋值评分自己出牌
					}
					else 
					{
						//队友要则不出（让牌）
						ddz->handCardInfor.ClearPutCard();
						return 1;
						
					}
				}
				//主动出牌
				else
				{
					int min;
					//找自己最小牌
					for (int i = 0; i < 14; i++)
						if (ddz->handCardInfor.CardPointNum[i] > 0)
							min = i;
					//回看上一次对手有没有出单牌给他
					if (AnalyzeTypeCount(ddz->iOnTable[ddz->iOTmax - 2]) / 100 == 3)//查看下家（对手）给队友出的单牌 
					{
						
						if (ddz->iOnTable[ddz->iOTmax - 2][0] / 4 <= min)
						{
							ddz->fnohope = 1;
							return 0;//最小牌比对手单牌还大，队友肯定要不起，放弃队友,让出牌函数自己打 
						}
					}
					//拆最小牌协助队友
					if (!ddz->fnohope) 
					{
						FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 301, min, -1, -1, -1, -1);
						return 1;
					}
					return 0;
				}
			}
		}
		//剩两张 
		else {
			//上家是对手
			if (ddz->formation == 1|| ddz->formation == 2)
			{
				if (ddz->handCardInfor.PutAnyCard == 0)//被动出牌
				{
					if (ddz->handCardInfor.CardPointNum[13] >= 2)//有王炸
					{
						FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 102, 13, -1, -1, -1, -1);
						return 1;
					}
					//炸弹压制
					for (int i = 0; i < 13; i++)
						if (ddz->handCardInfor.CardPointNum[i] == 4)//自己有炸弹
						{
							//对方不是炸弹或者王炸 || 对方炸弹不够自己大
							if ((ddz->iLastTypeCount / 100 != 1 && ddz->iLastTypeCount / 100 != 2) || (ddz->iLastTypeCount / 100 == 2 && ddz->iLastMainPoint < i))
							{
								FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 204, i, -1, -1, -1, -1);
								return 1;
							}

						}
				}

				else
				{
					//主动出牌
					//把炸弹变为四带二对
					while (ownCard.bomb > 0 && ownCard.two > 1)
					{
						ownCard.fourDouble11[ownCard.fourTwo].cardTypeId = 1108;
						ownCard.fourDouble11[ownCard.fourTwo].minCard = ownCard.bomb2[ownCard.bomb - 1].minCard;//最小炸弹
						ownCard.fourDouble11[ownCard.fourTwo].take1 = ownCard.double4[ownCard.two - 1].minCard;
						ownCard.fourDouble11[ownCard.fourTwo].take2 = ownCard.double4[ownCard.two - 2].minCard;
						ownCard.fourTwo++;
						//清理
						ownCard.clearOneCard(&ownCard.bomb2[ownCard.bomb - 1]); ownCard.bomb--;
						ownCard.clearOneCard(&ownCard.double4[ownCard.two - 1]);
						ownCard.clearOneCard(&ownCard.double4[ownCard.two - 2]);
						ownCard.two -= 2;
						ownCard.sum -= 1;
						ownCard.Tidy();
					}
					//把三顺变为三顺带对  或 三带一对
					if (ownCard.linkThree > 0)
					{
						for (int i = ownCard.linkThree - 1; i >= 0; i--)//从最小三顺开始
						{
							if (ownCard.two >= ownCard.linkThree && ownCard.two > 0)//有足够单牌
							{
								ownCard.linkThreeDouble10[ownCard.linkThreeTwo].cardTypeId = 1000 + ((ownCard.linkThree9[i].cardTypeId % 100) / 3) * 5;
								ownCard.linkThreeDouble10[ownCard.linkThreeTwo].minCard = ownCard.linkThree9[i].minCard;
								ownCard.linkThreeDouble10[ownCard.linkThreeTwo].take1 = ownCard.double4[ownCard.two - 1].minCard;
								ownCard.linkThreeDouble10[ownCard.linkThreeTwo].take1 = ownCard.double4[ownCard.two - 2].minCard;
								ownCard.clearOneCard(&ownCard.double4[ownCard.two - 1]);
								ownCard.clearOneCard(&ownCard.double4[ownCard.two - 2]);
								ownCard.two -= 2;
								if (((ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId % 100) / 3) >= 3)///三带
								{
									ownCard.linkThreeDouble10[ownCard.linkThreeTwo].take3 = ownCard.double4[ownCard.two - 1].minCard;
									ownCard.clearOneCard(&ownCard.double4[ownCard.two - 1]);
									ownCard.two -= 1;
									if (((ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId % 100) / 3) >= 4)//四带
									{
										ownCard.linkThreeDouble10[ownCard.linkThreeTwo].take4 = ownCard.double4[ownCard.two - 1].minCard;
										ownCard.clearOneCard(&ownCard.double4[ownCard.two - 1]);
										ownCard.two -= 1;
									}
								}
								ownCard.linkThreeTwo++;
								ownCard.clearOneCard(&ownCard.linkThree9[i]); ownCard.linkThree--;//三顺减少
								ownCard.Tidy();
							}
							else if (ownCard.single < ownCard.linkThree && ownCard.single > 0)//没有足够的单牌，拆为三带一对
							{// 先拆为三张，后面再合成三带一
								int lian = (ownCard.linkThree9[i].cardTypeId % 100) / 3;
								int min = ownCard.linkThree9[i].minCard;
								for (int j = 0; j < lian; j++)
								{
									ownCard.three5[ownCard.three].cardTypeId = 503;
									ownCard.three5[ownCard.three].minCard = min + lian - j - 1;
									ownCard.three++;
								}
								ownCard.clearOneCard(&ownCard.linkThree9[i]);
								ownCard.linkThree--;
								ownCard.Tidy();
							}
						}
					}
					//吧三张变为三带一对
					if (ownCard.three > 0 && ownCard.two > 0)
					{
						while (ownCard.three > 0 && ownCard.two > 0)
						{
							ownCard.threeDouble6[ownCard.threeTwo].cardTypeId = 605;
							ownCard.threeDouble6[ownCard.threeTwo].minCard = ownCard.three5[ownCard.three - 1].minCard;
							ownCard.threeDouble6[ownCard.threeTwo].take1 = ownCard.double4[ownCard.two - 1].minCard;
							ownCard.threeTwo++;
							ownCard.clearOneCard(&ownCard.three5[ownCard.three - 1]); ownCard.three--;
							ownCard.clearOneCard(&ownCard.double4[ownCard.two - 1]); ownCard.two--;
						}
					}
					//按以下顺序出牌
				//三顺带单10》三顺带双10》三顺9》双顺8》单顺7》三带一单6》三带对6》三条5》四带二单11》四带二对11》炸弹2》火箭1》3单牌》 对牌4
					switch (10)
					{
					case 10: {//三顺带单
						if (ownCard.linkThreeSingle > 0)
						{
							int t1 = ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].take1;
							int t2 = ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].take2;
							int t3 = ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].take3;
							int t4 = ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].take4;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].cardTypeId, ownCard.linkThreeSingle10[ownCard.linkThreeSingle - 1].minCard, t1, t2, t3, t4);
							return 1;
						}
						if (ownCard.linkThreeTwo > 0)
						{
							int t1 = ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].take1;
							int t2 = ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].take2;
							int t3 = ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].take3;
							int t4 = ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].take4;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].cardTypeId, ownCard.linkThreeDouble10[ownCard.linkThreeTwo - 1].minCard, t1, t2, t3, t4);
							return 1;
						}
					}
					case 9: {//三顺
						if (ownCard.linkThree > 0)
						{
							int cardtype = ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId;
							int min = ownCard.linkThree9[ownCard.linkThree - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 8: {//双顺8
						if (ownCard.linkTwo > 0)
						{
							int cardtype = ownCard.linkDouble8[ownCard.linkTwo - 1].cardTypeId;
							int min = ownCard.linkDouble8[ownCard.linkTwo - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 7: {//单顺7
						if (ownCard.linkSingle > 0)
						{
							int cardtype = ownCard.linkSingle7[ownCard.linkSingle - 1].cardTypeId;
							int min = ownCard.linkSingle7[ownCard.linkSingle - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 6: {//三带一
						if (ownCard.threeOne > 0)//带单
						{
							int cardtype = ownCard.threeOne6[ownCard.threeOne - 1].cardTypeId;
							int min = ownCard.threeOne6[ownCard.threeOne - 1].minCard;
							int t1 = ownCard.threeOne6[ownCard.threeOne - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, -1, -1, -1);
							return 1;
						}
						if (ownCard.threeTwo > 0)//带对
						{
							int cardtype = ownCard.threeDouble6[ownCard.threeTwo - 1].cardTypeId;
							int min = ownCard.threeDouble6[ownCard.threeTwo - 1].minCard;
							int t1 = ownCard.threeDouble6[ownCard.threeTwo - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, -1, -1, -1);
							return 1;
						}
					}
					case 5: {//三条5
						if (ownCard.three > 0)
						{
							int cardtype = ownCard.three5[ownCard.three - 1].cardTypeId;
							int min = ownCard.three5[ownCard.three - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 11: {//四带二
						if (ownCard.fourSingle > 0)//带单
						{
							int cardtype = ownCard.fourSingle11[ownCard.fourSingle - 1].cardTypeId;
							int min = ownCard.fourSingle11[ownCard.fourSingle - 1].minCard;
							int t1 = ownCard.fourSingle11[ownCard.fourSingle - 1].take1;
							int t2 = ownCard.fourSingle11[ownCard.fourSingle - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, t2, -1, -1);
							return 1;
						}
						if (ownCard.fourTwo > 0)//带对
						{
							int cardtype = ownCard.fourDouble11[ownCard.fourTwo - 1].cardTypeId;
							int min = ownCard.fourDouble11[ownCard.fourTwo - 1].minCard;
							int t1 = ownCard.fourDouble11[ownCard.fourTwo - 1].take1;
							int t2 = ownCard.fourDouble11[ownCard.fourTwo - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, t2, -1, -1);
							return 1;
						}
					}
					case 2: {//炸弹2
						if (ownCard.bomb > 0)
						{
							int cardtype = ownCard.bomb2[ownCard.bomb - 1].cardTypeId;
							int min = ownCard.bomb2[ownCard.bomb - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 1: {//火箭1
						if (ownCard.rocket > 0)
						{
							int cardtype = ownCard.rocket1.cardTypeId;
							int min = ownCard.rocket1.minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 3: {//3单牌
						if (ownCard.single > 0)
						{
							//出最小牌   //这里不是应该出最大牌压制地主吗 已修改 2020.8
							ownCard.Tidy();
							/*int cardtype = ownCard.single3[ownCard.single-1].cardTypeId;
							int min = ownCard.single3[ownCard.single-1].minCard;*/
							int cardtype = ownCard.single3[0].cardTypeId;
							int max = ownCard.single3[0].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, max, -1, -1, -1, -1);
							return 1;
						}
					}
					case 4: {//对牌4》
						if (ownCard.two > 0)
						{
							//同上单牌
							/*int cardtype = ownCard.double4[ownCard.two - 1].cardTypeId;
							int min = ownCard.double4[ownCard.two - 1].minCard;*/
							int cardtype = ownCard.single3[0].cardTypeId;
							int max = ownCard.single3[0].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, max, -1, -1, -1, -1);
							return 1;
						}
					}
					default: return 0;
						break;
					}

				}
			}
			//上家是队友
			if (ddz->formation == 3)
			{
				if (ddz->handCardInfor.PutAnyCard == 0)//被动出牌
				{
					if (ddz->iOnTable[ddz->iOTmax - 1][0] < 0) //队友不出牌
					{
						//压制地主，争取主动出牌的机会
						if (ddz->handCardInfor.CardPointNum[13] >= 2)//有王炸
						{
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 102, 13, -1, -1, -1, -1);
							return 1;
						}
						//炸弹压制
						for (int i = 0; i < 13; i++)
							if (ddz->handCardInfor.CardPointNum[i] == 4)//自己有炸弹
							{
								//对方不是炸弹或者王炸 || 对方炸弹不够自己大
								if ((ddz->iLastTypeCount / 100 != 1 && ddz->iLastTypeCount / 100 != 2) || (ddz->iLastTypeCount / 100 == 2 && ddz->iLastMainPoint < i))
								{
									FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 204, i, -1, -1, -1, -1);
									return 1;
								}

							}
					}
					//如果队友出了就让牌
					else
					{
						ddz->handCardInfor.ClearPutCard();
						return 1;
					}
				}
				else //主动出牌
				{
					
					int min;
					//找自己最小对牌
					for (int i = 0; i < 14; i++)
						if (ddz->handCardInfor.CardPointNum[i] > 1)
							min = i;
					//回看上一次对手有没有出牌给他
					if (AnalyzeTypeCount(ddz->iOnTable[ddz->iOTmax - 2]) / 100 == 4|| AnalyzeTypeCount(ddz->iOnTable[ddz->iOTmax - 2]) / 100 == 3)//查看上次下家（对手）给队友出的单牌 或对牌
					{
						
						//有待优化：如果队友一直报双可能会隔一轮出一次最小对子(已优化)
						if (ddz->iOnTable[ddz->iOTmax - 2][0] / 4 <= min)
						{
							ddz->fnohope = 1;
							return 0;//最小对牌主牌点数比对手单牌还大，队友肯定要不起，放弃队友,让出牌函数自己打 
						}
					}
					//拆最小对牌协助队友
					if (!(ddz->fnohope))  //还能试试帮队友
					{
						FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 402, min, -1, -1, -1, -1);
						return 1;
					}
					return 0;
				}
			}
		}
	}
	
	return 0;
}

//重置本局数据初始值(检查：9.6)
void InitRound(struct Ddz* pDdz)
{
	int i, j;
	pDdz->iStatus = 1;					//初始化本局引擎状态
	strcpy(pDdz->sCommandIn, "");		//初始化本局通信输入内容
	strcpy(pDdz->sCommandOut, "");		//初始化本局通信输出内容
	strcpy(pDdz->sVer, "");				//初始化本局协议版本号
	strcpy(pDdz->sName, kPlayerName);		//初始化本局参赛选手称呼
	pDdz->cDir = 'B';						//初始化本局玩家方位编号
	pDdz->cLandlord = 'B';				//初始化本局地主方位编号
	pDdz->cWinner = 'B';					//初始化本局胜者方位编号
	pDdz->fnohope = 0;                   //初始化无能为力变量
	for (i = 0; i < 3; i++)
		pDdz->iLef[i] = -1;             //初始化底牌
	for (i = 0; i < 21; i++)			//初始化本局手牌
		pDdz->iOnHand[i] = -1;
	for (i = 0; i < 250; i++)				//初始化本局桌面牌
		for (j = 0; j < 21; j++)
			pDdz->iOnTable[i][j] = -2;
	for (i = 0; i < 162; i++)
		pDdz->iOnPlayId[i] = 'E';        //初始值，表示错误
	for (i = 0; i < 21; i++)			//初始化本局出牌
		pDdz->iToTable[i] = -1;
	for (i = 0; i < 3; i++)				//初始化本局叫牌
		pDdz->iBid[i] = -1;
	for (i = 0; i < 14; i++)
		pDdz->allCardOnTable[i] = 0;
	pDdz->handCardInfor.InIt();//自己手牌类初始化
	pDdz->upCard.Init();//上家手牌情况初始化
	pDdz->lowCard.Init();
	
	pDdz->iLastPassCount = 0;		//当前桌面连续PASS数（值域[0,2],初值0，正常出牌取0，一家PASS取1，两家PASS取2）
	pDdz->iLastTypeCount = 0;		//当前桌面牌型张数（值域[0,1108],初值0，iLastPassCount=0时更新值，=1时保留原值，=2时值为0）
	pDdz->iLastMainPoint = -1;		//当前桌面主牌点数（值域[0,15],初值-1，iLastPassCount=0时更新值，，=1时保留原值，=2时值为-1）
	pDdz->iBmax = 0;					//初始化本局叫牌分数
	pDdz->iOTmax = 0;					//初始化本局桌面牌手数
}

//将牌码数组转换为字符串追加(-1或)（检查9.6）
void AppendCardsToS(int iCards[], char sMsg[])
{
	int i;
	char sCard[4] = "";
	char sCardString[90] = "";
	if (iCards[0] == -1)	// PASS
		strcat(sCardString, "-1");
	else					// 不是PASS
	{
		for (i = 0; iCards[i] >= 0; i++)
		{
			if (iCards[i] >= 10)
			{
				sCard[0] = iCards[i] / 10 + '0';
				sCard[1] = iCards[i] % 10 + '0';
				sCard[2] = ',';
				sCard[3] = '\0';
			}
			else
			{
				sCard[0] = iCards[i] % 10 + '0';
				sCard[1] = ',';
				sCard[2] = '\0';
			}
			strcat(sCardString, sCard);
		}
		sCardString[strlen(sCardString) - 1] = '\0';	//去掉多余的尾部逗号

	}
	strcat(sMsg, sCardString);
}

//重置本轮数据初始值（检查9.6）
void InitTurn(struct Ddz *pDdz)
{
	pDdz->iTurnTotal = 1;				//初始化总轮数
	pDdz->iTurnNow = 1;					//初始化当前轮次
	pDdz->iRoundTotal = 1;				//初始化总局数
	pDdz->iRoundNow = 1;				//初始化当前局次
	InitRound(pDdz);					//初始化本局数据
}

//接受sCommandIn输入信息（检查9.6）
void InputMsg(struct Ddz* pDdz)
{
	cin.getline(pDdz->sCommandIn, 80);
}

//分析处理信息（检查9.6）
void AnalyzeMsg(struct Ddz* pDdz)
{//还缺超时信息处理-------------（不用）
	char sShort[4];
	int i;
	for (i = 0; i < 3; i++)
		sShort[i] = pDdz->sCommandIn[i];
	sShort[3] = '\0';
	if (strcmp(sShort, "DOU") == 0)					//版本信息
	{
		GetDou(pDdz);
		return;
	}
	if (strcmp(sShort, "INF") == 0)					//轮局信息 info  信息
	{
		GetInf(pDdz);
		return;
	}
	if (strcmp(sShort, "DEA") == 0)					//发牌信息  deal 处理
	{
		GetDea(pDdz);
		return;
	}
	if (strcmp(sShort, "BID") == 0)					//叫牌过程  bid 投标
	{
		GetBid(pDdz);
		return;
	}
	if (strcmp(sShort, "LEF") == 0)					//底牌信息
	{
		GetLef(pDdz);
		return;
	}
	if (strcmp(sShort, "PLA") == 0)					//出牌过程
	{
		GetPla(pDdz);
		return;
	}
	if (strcmp(sShort, "GAM") == 0)					//胜负信息  gameover 游戏结束
	{
		GetGam(pDdz);
		return;
	}
	if (strcmp(sShort, "EXI") == 0)					//强制退出
	{
		exit(0);
	}
	strcpy(pDdz->sCommandOut, "ERROR at module AnalyzeMsg,sCommandIn without match");//错误提示
	return;
}

//获取、保存版本信息，更新通信输出内容为选手名称(检查9.6)
void GetDou(struct Ddz* pDdz)
{
	int i;								//简单循环变量
	for (i = 0; pDdz->sCommandIn[i] != '\0'; i++)
		pDdz->sVer[i] = pDdz->sCommandIn[i];
	pDdz->sVer[i] = '\0';
	strcpy(pDdz->sCommandOut, "NAME ");
	strcat(pDdz->sCommandOut, pDdz->sName);//字符串连接
}

//获取保存轮局信息INF，更新输出通信内容OK INFO(检查9.6)
void GetInf(struct Ddz* pDdz)		
{   //没有应答时间限制信息处理 
	//轮次信息处理函数(处理数字信息，对应写入对象成员变量中):输入INFO 1/4 1/9 9 2450     输出OK INFO
	//当前轮序号、总轮数、当前局序号、每轮总局数、晋级的选手数、封顶分数、应答时间
	char c;					//存当前字节信息		
	int iCount = 0;			//记录数据个数
	int iTemp = 0;			//中间变量
	int iMessage[7] = { 0 };		//记录数据数组
	int i;
	for (i = 5; pDdz->sCommandIn[i] != '\0'; i++)
	{
		c = pDdz->sCommandIn[i];
		if (c >= '0' && c <= '9')											//当前字符为0-9
		{
			iTemp = iTemp * 10 + c - '0';
			iMessage[iCount] = iTemp;								//晋级选手数
		}
		if (c == ',')														//当前字符为逗号,
		{
			iCount++;
			iTemp = 0;
		}
	}
	pDdz->iTurnNow = iMessage[0];						//当前轮次
	pDdz->iTurnTotal = iMessage[1];						//总轮数
	pDdz->iRoundNow = iMessage[2];						//当前局次
	pDdz->iRoundTotal = iMessage[3];					//每轮总局数
	pDdz->iLevelUp = iMessage[4];						//晋级选手数量
	pDdz->iScoreMax = iMessage[5];						//封顶分数
	pDdz->iTime = iMessage[6];                          //应答时间限制
	strcpy(pDdz->sCommandOut, "OK INFO");
}

//获取保存发牌信息DEA，更新通信输出信息OK DEAL（检查9.6）
void GetDea(struct Ddz* pDdz)
{  //DEAL dC1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,C17
	//d 为方位
	int i;			      //简单循环变量
	int iNow = 0;		  //当前处理牌序号
	int iCardId = 0;	//当前处理牌编码
	char c;			      //当前指令字符
	pDdz->cDir = pDdz->sCommandIn[5];     //获取本家AI方位编号（A || B || C）
	for (i = 0; i < 21; i++)				          //重新清理iOnhand[]
		pDdz->iOnHand[i] = -1;
	for (i = 6; pDdz->sCommandIn[i] != '\0'; i++)	//依次读取牌码指令
	{
		c = pDdz->sCommandIn[i];			      //c为当前指令字符
		if (c >= '0' && c <= '9')				        //当前字符为0-9
		{
			iCardId = iCardId * 10 + c - '0';
			pDdz->iOnHand[iNow] = iCardId;//记录手上的牌
		}
		if (c == ',')							            //当前字符为逗号,
		{
			iCardId = 0;
			iNow++;
		}
	}
	SortById(pDdz->iOnHand);  //iOnHand[]从小到大排序
	//将手牌序列拷贝到手牌类
	for (i = 0; i < 21; i++)
		pDdz->handCardInfor.onHandCard[i] = pDdz->iOnHand[i];
	pDdz->handCardInfor.ArrangeHandCard();//整理手牌
	strcpy(pDdz->sCommandOut, "OK DEAL");  //回复信息
	//测试拆牌函数
	//CheckChaiCard(pDdz);

}

//获取保存叫牌信息BID，更新通信输出内容OK BID或BID _0(检查0.6)
void GetBid(struct Ddz* pDdz)
{                           //BID WHAT		BID A1
	if (pDdz->sCommandIn[4] == 'W')					//如果输入信息为BID WHAT，裁判询问选手叫牌
	{
		strcpy(pDdz->sCommandOut, "BID _0");
		pDdz->sCommandOut[4] = pDdz->cDir;//玩家编号
		int socre= callScore(pDdz->iOnHand);//计算并保存叫牌的分数（新）
		//只能越叫越大或者不叫
		if (socre == 3)//大牌比较激进，3分输得惨
			socre = 2;
		if (socre > pDdz->iBmax)//大
		{
			pDdz->iBid[pDdz->cDir - 'A'] = socre;//计算并保存叫牌的分数（新）
			pDdz->iBmax = pDdz->iBid[pDdz->cDir - 'A'];//保存最大叫牌
			pDdz->sCommandOut[5] = '0' + pDdz->iBid[pDdz->cDir - 'A'];		//
		}
		else {//不够大只能不叫
			pDdz->iBid[pDdz->cDir - 'A'] = 0;//计算并保存叫牌的分数（新）
			pDdz->sCommandOut[5] = '0' + pDdz->iBid[pDdz->cDir - 'A'];		//
		}

		//pDdz->iBid[pDdz->cDir - 'A'] = callScore(pDdz->iOnHand);//计算并保存叫牌的分数（新）
		//if (pDdz->iBid[pDdz->cDir - 'A'] > pDdz->iBmax)//检查是不是最大叫牌分数
		//	pDdz->iBmax = pDdz->iBid[pDdz->cDir - 'A'];
		//pDdz->sCommandOut[5] = '0'+ pDdz->iBid[pDdz->cDir - 'A'];		//
		pDdz->sCommandOut[6] = '\0';
		return;
	}
	if (pDdz->sCommandIn[4] >= 'A' && pDdz->sCommandIn[4] <= 'C')  //输入信息为BID **，裁判转发其它选手叫牌信息
	{
		pDdz->iBid[pDdz->sCommandIn[4] - 'A'] = pDdz->sCommandIn[5] - '0';//保存其他选手叫牌分数	
		if (pDdz->iBid[pDdz->sCommandIn[4] - 'A'] > pDdz->iBmax)//检查是不是最大叫牌分数
			pDdz->iBmax = pDdz->iBid[pDdz->sCommandIn[4] - 'A'];
		strcpy(pDdz->sCommandOut, "OK BID");
		return;
	}
}

//获取保存底牌信息LEF，更新通信输出内容OK LEFTOVER(检查9.6)
void GetLef(struct Ddz* pDdz)
{                //LEFTOVER B27,48,53
	int i, iCount = 0;
	char c;
	pDdz->cLandlord = pDdz->sCommandIn[9];    //保存地主方位
	pDdz->iLef[0] = 0;
	pDdz->iLef[1] = 0;
	pDdz->iLef[2] = 0;
	for (i = 10; pDdz->sCommandIn[i] != '\0'; i++)//保存底牌
	{
		c = pDdz->sCommandIn[i];
		if (c >= '0' && c <= '9')
			pDdz->iLef[iCount] = pDdz->iLef[iCount] * 10 + c - '0';
		else
			iCount++;
	}
	//阵容确定
	if (pDdz->cLandlord == pDdz->cDir)//自己是地主
	{
		pDdz->formation = 2;//【农 AI 农】
	}
	else {//自己不是地主
		if (pDdz->cDir == 'A')//坐A
		{
			if (pDdz->cLandlord == 'B')
				pDdz->formation = 3;
			else pDdz->formation = 1;
		}
		else if (pDdz->cDir == 'B')//坐B
		{
			if (pDdz->cLandlord == 'A')
				pDdz->formation = 1;
			else pDdz->formation = 3;
		}
		else if (pDdz->cDir == 'C')//坐C
		{
			if (pDdz->cLandlord == 'B')
				pDdz->formation = 1;
			else pDdz->formation = 3;
		}
	}

	if (pDdz->sCommandIn[9] == pDdz->cDir)//如果自己是地主
	{     //(54-3)/3=17
		pDdz->iOnHand[17] = pDdz->iLef[0];
		pDdz->iOnHand[18] = pDdz->iLef[1];
		pDdz->iOnHand[19] = pDdz->iLef[2];
		pDdz->iOnHand[20] = -1;//

		SortById(pDdz->iOnHand);					//iOnHand[]从小到大排序
		for (int j = 0; pDdz->iOnHand[j]>-1; j++)//拷贝到手牌
		{
			pDdz->handCardInfor.onHandCard[j] = pDdz->iOnHand[j];
		}
		pDdz->handCardInfor.ArrangeHandCard();//整理手牌类
	}
	else if (pDdz->formation == 1 )//如果上家是地主
	{
		pDdz->upCard.sum += 3;
		for (int h = 0; h < 3; h++)//记录底牌
			pDdz->upCard.surCardPoint[pDdz->iLef[h] / 4]++;
	}
	else if (pDdz->formation == 3 )//如果下家是地主
	{
		pDdz->lowCard.sum += 3;
		for (int h = 0; h < 3; h++)//记录底牌
			pDdz->lowCard.surCardPoint[pDdz->iLef[h] / 4]++;
	}

	strcpy(pDdz->sCommandOut, "OK LEFTOVER");
}

//获取并处理出牌信息PLA(检查9.6)
void GetPla(struct Ddz* pDdz)
{                //PLAY WHAT  PLAY C-1
	//检查怎么出牌
	CheckPut(pDdz);


	if (pDdz->sCommandIn[5] == 'W')			//自己出牌
	{
		if (pDdz->handCardInfor.PutAnyCard !=0 )//主动出牌
		{
			//先判断谁先报警问题
			//if(!AlertCard(pDdz))

			//一般情况
				PutCardWayActive(pDdz->handCardInfor);
		}
		else {//被动出牌
			//该不该接牌
			//if (JudgePutCard(pDdz))
			//{
				//if(!AlertCard(pDdz))
					//普通牌局
					PutCardWayUnactive(pDdz->handCardInfor);
			//}
			//else pDdz->handCardInfor.ClearPutCard();//不出
		}

		for (int i = 0; i < 21; i++)
			pDdz->iToTable[i] = pDdz->handCardInfor.PutCard[i];

		strcpy(pDdz->sCommandOut, "PLAY _");
		pDdz->sCommandOut[5] = pDdz->cDir;		//获取自己的方位编号，输出命令的预备信息准备到sCommandOut数组
		AppendCardsToS(pDdz->iToTable, pDdz->sCommandOut);		//要出牌数组iToTable[]中的数字转化为字符并连接到sCommandOut中
		UpdateMyPla(pDdz);		//根据己方出牌更新数据
	}
	else										//否则收到信息为其它玩家出牌
	{
		UpdateHisPla(pDdz);		//根据他人出牌更新数据       
		strcpy(pDdz->sCommandOut, "OK PLAY");//回复收到
	}

	//测试用 函数
	//Check(pDdz);

}

//根据自己方出牌更新数据（检查9.6）
void UpdateMyPla(struct Ddz* pDdz)
{
	int i, j, k;
	if (pDdz->iToTable[0] == -1)	//Pass
	{
		pDdz->iOnTable[pDdz->iOTmax][0] = -1;//统计桌面总出牌情况
		pDdz->iOnPlayId[pDdz->iOTmax] = pDdz->cDir;//记录方位
		pDdz->iOTmax++;

		pDdz->iLastPassCount = 0;
		pDdz->handCardInfor.PutAnyCard = 0;//不可以出任意牌
	}
	else						//不是PASS
	{
		//增加桌面牌
		for (i = 0; pDdz->iToTable[i] >= 0; i++)
		{
			pDdz->iOnTable[pDdz->iOTmax][i] = pDdz->iToTable[i];

			pDdz->allCardOnTable[pDdz->iToTable[i] / 4]++;//点数增加
		}
		pDdz->iOnTable[pDdz->iOTmax][i] = -1;
		pDdz->iOnPlayId[pDdz->iOTmax] = pDdz->cDir;//记录方位
		pDdz->iOTmax++;

		//减少手中牌----------没有以-1结尾
		for (j = 0; pDdz->iToTable[j] >= 0; j++)
		{
			for (i = 0; pDdz->iOnHand[i] >= 0; i++)
				if (pDdz->iOnHand[i] == pDdz->iToTable[j])
				{
					for (k = i; pDdz->iOnHand[k] >= 0; k++)
						pDdz->iOnHand[k] = pDdz->iOnHand[k+1];
					break;
				}
		}

		for (j = 0; j < 21; j++)//拷贝一份手牌
			pDdz->handCardInfor.onHandCard[j] = pDdz->iOnHand[j];
		pDdz->handCardInfor.ArrangeHandCard();//重新整理手牌
		//更新桌面牌情况
		pDdz->handCardInfor.PutAnyCard = pDdz->iLastPassCount = 0;
		pDdz->handCardInfor.tableTypeCount = pDdz->iLastTypeCount = AnalyzeTypeCount(pDdz->iToTable);
		pDdz->handCardInfor.tableMainPoint = pDdz->iLastMainPoint = AnalyzeMainPoint(pDdz->iToTable);
	}
}

//根据他人出牌更新数据(检查9.6,添加记牌器功能10.5)
void UpdateHisPla(struct Ddz* pDdz)
{//PLAY C-1
	int i;
	int iCardId;
	int iNow;
	char c;
	//减少手中牌
	if (pDdz->sCommandIn[6] == '-')// PLAY ?-1 即PASS
	{
		pDdz->iOnTable[pDdz->iOTmax][0] = -1;
		pDdz->iOnPlayId[pDdz->iOTmax] = pDdz->sCommandIn[5];//记录方位
		pDdz->iOTmax++;
		pDdz->iLastPassCount++;

		if (pDdz->iLastPassCount >= 2)	//连续两家pass
		{
			pDdz->handCardInfor.PutAnyCard = 1;//可以出任意牌
			pDdz->handCardInfor.tableMainPoint = -1;//没有最小牌
			pDdz->handCardInfor.tableTypeCount = 0;//弃牌

			pDdz->iLastPassCount = 0;//
			pDdz->iLastTypeCount = 0;//当前桌面牌型张数清零
			pDdz->iLastMainPoint = -1;
		}
	}
	else						// PLAY 出牌（正常出牌）
	{
		for (i = 0; i < 21; i++)							//清理iToTable[]
			pDdz->iToTable[i] = -1;
		iCardId = 0;//临时变量
		iNow = 0;//临时变量
		for (i = 6; pDdz->sCommandIn[i] != '\0'; i++)		//依次读取牌码
		{
			c = pDdz->sCommandIn[i];					//c为当前指令字符
			if (c >= '0' && c <= '9')				        //当前字符为0-9
			{
				iCardId = iCardId * 10 + c - '0';
				pDdz->iToTable[iNow] = iCardId;
			}
			if (c == ',')									//当前字符为逗号,
			{
				iCardId = 0;
				iNow++;
			}
		}
		//增加桌面牌
		for (i = 0; pDdz->iToTable[i] >= 0; i++)
		{
			pDdz->iOnTable[pDdz->iOTmax][i] = pDdz->iToTable[i];
			pDdz->allCardOnTable[pDdz->iToTable[i] / 4]++;//点数增加
		}
		pDdz->iOnTable[pDdz->iOTmax][i] = -1;//以-1结尾
		pDdz->iOnPlayId[pDdz->iOTmax] = pDdz->sCommandIn[5];//记录方位
		pDdz->handCardInfor.PutAnyCard = pDdz->iLastPassCount = 0;//0家pass，不能出任意牌
		pDdz->handCardInfor.tableTypeCount = pDdz->iLastTypeCount = AnalyzeTypeCount(pDdz->iToTable);//更新桌面牌型张数
		pDdz->handCardInfor.tableMainPoint = pDdz->iLastMainPoint = AnalyzeMainPoint(pDdz->iToTable);//更新桌面最小主点数
		pDdz->iOTmax++;

		//记牌器(逆时针出牌顺序)
		if ((pDdz->cDir == 'A' && pDdz->sCommandIn[5] == 'C') || (pDdz->cDir == 'B' && pDdz->sCommandIn[5] == 'A') ||
			(pDdz->cDir == 'C' && pDdz->sCommandIn[5] == 'B'))
		{//上家出牌
			for (int h = 0; pDdz->iToTable[h] > -1; h++)
			{
				pDdz->upCard.putCardPoint[pDdz->iToTable[h] / 4]++;
				pDdz->upCard.sum--;
				for (int hh = 0; hh < 14; hh++)
					if (pDdz->upCard.surCardPoint[hh] > 0 && pDdz->upCard.surCardPoint[hh] == pDdz->iToTable[h] / 4)
						pDdz->upCard.surCardPoint[hh]--;
			}
		}
		else {//下家出牌
			for (int h = 0; pDdz->iToTable[h] > -1; h++)
			{
				pDdz->lowCard.putCardPoint[pDdz->iToTable[h] / 4]++;
				pDdz->lowCard.sum--;
				for (int hh = 0; hh < 14; hh++)
					if (pDdz->lowCard.surCardPoint[hh] > 0 && pDdz->lowCard.surCardPoint[hh] == pDdz->iToTable[h] / 4)
						pDdz->lowCard.surCardPoint[hh]--;
			}
		}
	}
}


//获取并处理胜负信息GAM（检查9.6）
void GetGam(struct Ddz* pDdz)
{
	pDdz->cWinner = pDdz->sCommandIn[9];			//胜利者方位编号
	if (pDdz->iRoundNow == pDdz->iRoundTotal)		//如果当前局数与每轮局相等时
	{
		pDdz->iStatus = 0;							//引擎状态变量设为结束
	}
	else											//否则
	{
		pDdz->iRoundNow++;							//当前局次加1
		InitRound(pDdz);							//引擎状态变量设为重新开始下一局
	}
	strcpy(pDdz->sCommandOut, "OK GAMEOVER");
}

//输出信息（检查9.6）
void OutputMsg(struct Ddz* pDdz)
{
	cout << pDdz->sCommandOut << endl;
}

//计算其它数据（检查9.6）
void CalOthers(struct Ddz* pDdz)
{
	pDdz->iVoid = 0;
}
