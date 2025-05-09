#pragma once
#define _CRT_SECURE_NO_WARNINGS //��ֻ���ڸ��ļ��������ã�
//������ΪһЩ�ϵ�.c�ļ�ʹ����strcpy,scanf�Ȳ���ȫ�ĺ�������������ʹ��󣬶������޷�����ͨ����
#include <stdio.h>
#include <string.h>
#include <iostream>

#include"CallScore.h"
#include"DDZStruct.h"
#include"ScoreWay.h"
using namespace std;


//���ֺ�������
void InitRound(struct Ddz* pDdz);				//M04 ���ñ������ݳ�ʼֵ
void AppendCardsToS(int iCards[], char sMsg[]);	//M05 ����������ת��Ϊ�ַ���׷��(-1��)
void InitTurn(struct Ddz* pDdz);				//P01 ���ñ������ݳ�ʼֵ
void InputMsg(struct Ddz* pDdz);				//P02 ������Ϣ
void AnalyzeMsg(struct Ddz* pDdz);				//P03 ����������Ϣ
void GetDou(struct Ddz* pDdz);					//P0301 ��ȡ������汾��ϢDOU
void GetInf(struct Ddz* pDdz);					//P0302 ��ȡ�������־���ϢINF
void GetDea(struct Ddz* pDdz);					//P0303 ��ȡ������������ϢDEA
void GetBid(struct Ddz* pDdz);					//P0304 ��ȡ�����������ϢBID
void GetLef(struct Ddz* pDdz);					//P0305 ��ȡ�����������ϢLEF
void GetPla(struct Ddz* pDdz);					//P0306 ��ȡ�����������ϢPLA
void UpdateMyPla(struct Ddz* pDdz);			//P030602 ���ݼ������Ƹ�������
void UpdateHisPla(struct Ddz* pDdz);			//P030603 �������˳��Ƹ�������
void GetGam(struct Ddz* pDdz);					//P0307 ��ȡ������ʤ����ϢGAM
void OutputMsg(struct Ddz* pDdz);				//P04 �����Ϣ
void CalOthers(struct Ddz* pDdz);				//P05 ������������

bool JudgePutCard(struct Ddz* ddz);             //�ж��Լ��ò��ó���
int AlertCard(struct Ddz* ddz);					//����/˫����


//���� �����鿴�ú���
void Check(struct Ddz* ddz)//�鿴���ֱ���������ʱ��
{
	cout << "����ҷ�λ���" << ddz->cDir << "::������ұ�ţ�" << ddz->cLandlord << "::ʤ���߱�ţ�" << ddz->cWinner << endl;
	cout << "�ϴ���ұ�� " << ddz->iOnPlayId[ddz->iOTmax - 2] << endl;
	cout << "���ƹ���" << " ";
	for (int i = 0; i < 3; i++)
		cout << ddz->iBid[i] << " ";
	cout << endl;
	cout << "��ǰ���ƣ�" << ddz->iBmax << endl;
	cout << "��ǰ�ܳ���������" << ddz->iOTmax << endl;
	cout << "������(DDZ��)��"  ;
	for (int i = 0; ddz->iOnHand[i] >= 0; i++)
		cout << ddz->iOnHand[i] << " "  ;
	cout << endl;

	cout << "��ǰ��������pass����" << ddz->iLastPassCount << "::��ǰ��������������" << ddz->iLastTypeCount << "::��ǰ�������Ƶ�������"<< ddz->iLastMainPoint+3<<"��" << ddz->iLastMainPoint << endl;
	//������Ϣ��
	cout << "�������У�";
	for (int i = 0; ddz->handCardInfor.onHandCard[i] >= 0; i++)
		cout << ddz->handCardInfor.onHandCard[i] << " ";
	cout << endl;
	cout << "������ֵ:";
	for (int i = 0; ddz->handCardInfor.onHandCard[i] >= 0; i++)
		cout << ddz->handCardInfor.onHandCard[i] / 4 + 3 << " ";
	cout << endl;
	cout << "�����Ƶ�����";
	for (int i = 0; i < 14; i++)
		cout << "(" << i + 3 << ")" << ddz->handCardInfor.CardPointNum[i] << " ";
	cout << endl;
	cout << "������������" << ddz->handCardInfor.sumNum << endl;
	cout << "�����������" << endl;
	cout << "����������" << ddz->handCardInfor.PutCardGroup.cardTypeId << "::��ֵ:" << ddz->handCardInfor.PutCardGroup.value << "::���Ƶ���:" << ddz->handCardInfor.PutCardGroup.minCard;
	cout << "::����:" << ddz->handCardInfor.PutCardGroup.take1 << " " << ddz->handCardInfor.PutCardGroup.take2 << " " << ddz->handCardInfor.PutCardGroup.take3 << " " << ddz->handCardInfor.PutCardGroup.take4 << endl;
	cout << "�������У�";
	for (int i = 0; ddz->handCardInfor.PutCard[i] > -1; i++)
		cout << ddz->handCardInfor.PutCard[i] << " ";
	cout << endl;
	cout << "������Ϣ���" << endl;
	cout << "�Ƿ���Գ������ƣ�" << ddz->handCardInfor.PutAnyCard << " ��������������" << ddz->handCardInfor.tableTypeCount << " �������Ƶ�����" << ddz->handCardInfor.tableMainPoint << endl;
	//�������ṹ��
	cout << "�������ṹ�壺" << endl;
	cout << "��ǰ�������Ƶ��� " << ddz->iLastMainPoint << " ����pass�� " << ddz->iLastPassCount << " �������� " << ddz->iLastTypeCount << endl;
	

}

//���� ���ڲ鿴��ô������ֺ���
void CheckPut(struct Ddz* ddz)
{
	HandCardValue value1 = GetCardValue(ddz->handCardInfor);
	cout << "Ŀǰ���Ƽ�ֵ " << value1.value << " " << value1.needPly << endl;
	cout << "�������ƺ� " << endl;
	PutCardWayActive(ddz->handCardInfor);
	cout << "���� ";
	for (int i = 0; ddz->handCardInfor.PutCard[i] > -1; i++)
		cout << ddz->handCardInfor.PutCard[i] / 4 + 3 << " ";
	cout << endl;
	cout << "���Ƽ�ֵ " << ddz->handCardInfor.PutCardGroup.value << endl;
}

/*//�жϸò��ó��� true��false ����(��Ҫ���������)�������뵱ǰ����������ж�***************************��  
�������ƣ�һ����
���ѵ��ƣ�����Ǵ��ƣ�����
ֻ���ж�
*/
bool JudgePutCard(struct Ddz* ddz)
{
	//if (ddz->iLastPassCount >= 2)//�������ƣ��Լ��������
	//	return true;
	//Ҫ���Ƕ���
	if (ddz->formation == 1)//�ϼ��ǵ�������
		return true;

	if (ddz->cDir == ddz->cLandlord)//�Լ��ǵ�������
		return true ;
	//�ж��ǲ���һ����
	CardGroup ownCardGroup = JudgeOneHand2(ddz->handCardInfor.CardPointNum);
	//ͬ�����͡��ܳ�   �Լ�����ը   �Լ���ը��Ŀǰ�Ʋ���ը��   �Լ�ը���ȶԷ���
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

	int time = ddz->iOTmax;//��ǰ�������������
	//�ӵ�������
	if ((ddz->formation == 1 && ddz->iOnTable[time-1][0] != -1 && ddz->iOnTable[time - 1][0] != -2) ||  //�ϼҵ�������
		(ddz->formation == 3 && (ddz->iOnTable[time - 1][0] == -1 || ddz->iOnTable[time - 1][0] == -2))) //�ϼҶ���pass
	{
		return true;
	}
	else//�Ӷ��ѵ���
	{
		int cardPoint[14] = { 0 };
		for (int i = 0; ddz->iOnTable[time - 1][i] > -1; i++)
			cardPoint[ddz->iOnTable[time - 1][i] / 4]++;
		CardGroup parCard = JudgeOneHand2(cardPoint);
		switch (parCard.cardTypeId/100)
		{
		case 0: {//����
			return true;
		}; break;
		case 1: {//���
			return false;
		}; break;
		case 2: {//ը��
			return false;
		}; break;
		case 3: {//����
			if (parCard.minCard >= 12)//���ѳ����ڵ��� 2 ���ƣ�����
				return false;
		}; break;
		case 4: {//����
			if (parCard.minCard >= 12)//
				return false;
		}; break;
		case 5: {//����
			if (parCard.minCard >= 12)//
				return false;
		}; break;
		case 6: {//����һ
			if (parCard.minCard >= 12)//
				return false;
		}; break;
		case 7: {//��˳
			if (parCard.minCard+((parCard.cardTypeId%100)/1)-1 >= 12)//
				return false;
		}; break;
		case 8: {//˫˳
			if (parCard.minCard + ((parCard.cardTypeId % 100) / 2) - 1 >= 12)//
				return false;
		}; break;
		case 9: {//��˳
			if (parCard.minCard + ((parCard.cardTypeId % 100) / 3) - 1 >= 12)//
				return false;
		}; break;
		case 10: {//��˳����
			if ((parCard.cardTypeId % 100) % 4 == 0)//��˳����
			{
				if (parCard.minCard + ((parCard.cardTypeId % 100) / 4) - 1 >= 12)
					return false;;
			}
			if ((parCard.cardTypeId % 100) % 5 == 0)//��˳����
			{
				if (parCard.minCard + ((parCard.cardTypeId % 100) / 5) - 1 >= 12)
					return false;;
			}
		}; break;
		case 11: {//�Ĵ���
			if ((parCard.cardTypeId % 100) % 6 == 0)//�Ĵ�����
			{
				if (parCard.minCard + ((parCard.cardTypeId % 100) / 6) - 1 >= 11)//
					return false;
			}
			if ((parCard.cardTypeId % 100) % 8 == 0)//�Ĵ�����
			{
				if (parCard.minCard + ((parCard.cardTypeId % 100) / 8) - 1 >= 11)//
					return false;
			}
		}; break;
		default:
			break;
		}
	}
	//�ó� || �������
	return true;
}

/*
//���������������˱�������˫��ʱ��(�����ƾ�)
1 ��ʾ�Ѿ����� �������ǲ������溯������
0��ʾδ����
*/
int AlertCard(struct Ddz* ddz)
{
	//û�˱���ݣ��������ƣ�
	if (ddz->lowCard.sum > 2 && ddz->upCard.sum > 2) return 0;

	//����
	OwnCardGroup ownCard;//��ʱ��
	int tCardPoint[14] = { 0 };
	//����һ�ݣ��������ݶ�ʧ
	for (int i = 0; i < 14; i++)
		tCardPoint[i] = ddz->handCardInfor.CardPointNum[i];
	ChaiCard(tCardPoint, ownCard);
	
	int putCardType = 0;//���Լ�Ҫ��������,12����


	//�¼�����ֻʣ����
	if (ddz->lowCard.sum <= 2)
	{
		//ֻʣһ����
		if (ddz->lowCard.sum == 1)
		{
			//�¼��Ƕ���
			if (ddz->formation == 2 ||ddz->formation==3)
			{
				//��ը����Ϊ�Ĵ�����
				while (ownCard.bomb > 0 && ownCard.single > 1)
				{
					ownCard.fourSingle11[ownCard.fourSingle].cardTypeId = 1106;
					ownCard.fourSingle11[ownCard.fourSingle].minCard = ownCard.bomb2[ownCard.bomb - 1].minCard;//��Сը��
					ownCard.fourSingle11[ownCard.fourSingle].take1 = ownCard.single3[ownCard.single -1].minCard;//��С����
					ownCard.fourSingle11[ownCard.fourSingle].take2 = ownCard.single3[ownCard.single -2].minCard;
					ownCard.fourSingle++;
					//����
					ownCard.clearOneCard(&ownCard.bomb2[ownCard.bomb - 1]); ownCard.bomb--;
					ownCard.clearOneCard(&ownCard.single3[ownCard.single - 1]);
					ownCard.clearOneCard(&ownCard.single3[ownCard.single - 2]);
					ownCard.single -= 2;
					ownCard.sum -= 1;
					ownCard.Tidy();
				}
				//����˳��Ϊ��˳����  �� ����һ
				if (ownCard.linkThree > 0)
				{
					for (int i = ownCard.linkThree - 1; i >= 0; i--)//����С��˳��ʼ
					{
						if (ownCard.single >= ownCard.linkThree && ownCard.single > 0)//���㹻����
						{
							ownCard.linkThreeSingle10[ownCard.linkThreeSingle].cardTypeId = 1000 + ((ownCard.linkThree9[i].cardTypeId % 100) / 3) * 4;
							ownCard.linkThreeSingle10[ownCard.linkThreeSingle].minCard = ownCard.linkThree9[i].minCard;
							ownCard.linkThreeSingle10[ownCard.linkThreeSingle].take1 = ownCard.single3[ownCard.single - 1].minCard;
							ownCard.linkThreeSingle10[ownCard.linkThreeSingle].take1 = ownCard.single3[ownCard.single - 2].minCard;
							ownCard.clearOneCard(&ownCard.single3[ownCard.single - 1]);
							ownCard.clearOneCard(&ownCard.single3[ownCard.single - 2]);
							ownCard.single -= 2;
							if (((ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId % 100) / 3) >= 3)///����
							{
								ownCard.linkThreeSingle10[ownCard.linkThreeSingle].take3 = ownCard.single3[ownCard.single - 1].minCard;
								ownCard.clearOneCard(&ownCard.single3[ownCard.single - 1]);
								ownCard.single -= 1;
								if (((ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId % 100) / 3) >= 4)//�Ĵ�
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
						else if (ownCard.single < ownCard.linkThree && ownCard.single > 0)//û���㹻�ĵ��ƣ���Ϊ����һ
						{// �Ȳ�Ϊ���ţ������ٺϳ�����һ
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
				//�����ű�Ϊ����һ
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
				
				if (ddz->handCardInfor.PutAnyCard == 0) //��������
				{
					//ѹ��
					if (ddz->handCardInfor.CardPointNum[13] >= 2)//����ը
					{
						FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 102, 13, -1, -1, -1, -1);
						return 1;
					}
					//ը��ѹ��
					for(int i=0;i<13;i++)
						if (ddz->handCardInfor.CardPointNum[i] == 4)//�Լ���ը��
						{
							//�Է�����ը��������ը || �Է�ը�������Լ���
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
					//��������
					return 0;//�ø�ֵ�����Լ�����
				}
				else {
					//�Լ���������
					//������˳�����
				//��˳����10����˳��˫10����˳9��˫˳8����˳7������һ��6��������6������5���Ĵ�����11���Ĵ�����11������4��ը��2�����1��3����
					switch (10)
					{
					case 10: {//��˳����
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
					case 9: {//��˳
						if (ownCard.linkThree > 0)
						{
							int cardtype = ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId;
							int min = ownCard.linkThree9[ownCard.linkThree - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 8: {//˫˳8
						if (ownCard.linkTwo > 0)
						{
							int cardtype = ownCard.linkDouble8[ownCard.linkTwo - 1].cardTypeId;
							int min = ownCard.linkDouble8[ownCard.linkTwo - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 7: {//��˳7
						if (ownCard.linkSingle > 0)
						{
							int cardtype = ownCard.linkSingle7[ownCard.linkSingle - 1].cardTypeId;
							int min = ownCard.linkSingle7[ownCard.linkSingle - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 6: {//����һ
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
					case 5: {//����5
						if (ownCard.three > 0)
						{
							int cardtype = ownCard.three5[ownCard.three - 1].cardTypeId;
							int min = ownCard.three5[ownCard.three - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 11: {//�Ĵ�����11
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
					case 4: {//����4��
						if (ownCard.two > 0)
						{
							int cardtype = ownCard.double4[ownCard.two - 1].cardTypeId;
							int min = ownCard.double4[ownCard.two - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 2: {//ը��2
						if (ownCard.bomb > 0)
						{
							int cardtype = ownCard.bomb2[ownCard.bomb - 1].cardTypeId;
							int min = ownCard.bomb2[ownCard.bomb - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 1: {//���1
						if (ownCard.rocket > 0)
						{
							int cardtype = ownCard.rocket1.cardTypeId;
							int min = ownCard.rocket1.minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 3: {//3����
						if (ownCard.single > 0)
						{
							//�Ӵ�С��
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
			//�¼��Ƕ���
			else if (ddz->formation == 1)
			{
				//����ϼҶ��ֲ�����
				if (ddz->iOnTable[ddz->iOTmax - 1][0] < 0)
				{
					//���Ƹ�����
					ddz->handCardInfor.ClearPutCard();
					return 1;
					
				}
				else
				{
					int min;
					//���Լ���С��
					for (int i = 0; i < 14; i++)
						if (ddz->handCardInfor.CardPointNum[i] > 0)
							min = i;
					if (ddz->handCardInfor.PutAnyCard == 0)//��������
					{
						if (ddz->iLastTypeCount / 100 != 3)//Ŀǰ���ǳ�����
						{
							//Ϊ�˽Ӷ��ѣ�ѹ�Ƶ�����
							if (ddz->handCardInfor.CardPointNum[13] >= 2)//����ը
							{
								FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 102, 13, -1, -1, -1, -1);
								return 1;
							}
							//ը��ѹ��
							for (int i = 0; i < 13; i++)
								if (ddz->handCardInfor.CardPointNum[i] == 4)//�Լ���ը��
								{
									//�Է�����ը��������ը || �Է�ը�������Լ���
									if ((ddz->iLastTypeCount / 100 != 1 && ddz->iLastTypeCount / 100 != 2) || (ddz->iLastTypeCount / 100 == 2 && ddz->iLastMainPoint < i))
									{
										FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 204, i, -1, -1, -1, -1);
										return 1;
									}

								}
							//��������
							return 0;//�ø�ֵ�����Լ�����
						}
						else {
							//Ŀǰ�����ƣ��¼Ҷ���ֻʣһ��
							//���Լ���С����
							int minCard = -1;
							for (int i = 0; i < 14; i++)
								if (ddz->handCardInfor.CardPointNum[i] > 0)
								{
									minCard = i;
									break;
								}
							//����õ���С�ڵ�7 || �õ��Ʊ��Լ���С����С  -������
							if (ddz->iLastMainPoint <= 4 || (minCard != -1 && ddz->iLastMainPoint <= minCard))
							{
								//����
								ddz->handCardInfor.ClearPutCard();
								return 1;
							}
							//�Լ��бȶԷ���С�ĵ���
							if (ddz->iLastMainPoint - minCard >= 4 && minCard != -1)
							{
								//Ϊ�˽Ӷ��ѣ�ѹ�Ƶ�����
								if (ddz->handCardInfor.CardPointNum[13] >= 2)//����ը
								{
									FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 102, 13, -1, -1, -1, -1);
									return 1;
								}
								//ը��ѹ��
								for (int i = 0; i < 13; i++)
									if (ddz->handCardInfor.CardPointNum[i] == 4)//�Լ���ը��
									{
										//�Է�����ը��������ը || �Է�ը�������Լ���
										if ((ddz->iLastTypeCount / 100 != 1 && ddz->iLastTypeCount / 100 != 2) || (ddz->iLastTypeCount / 100 == 2 && ddz->iLastMainPoint < i))
										{
											FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 204, i, -1, -1, -1, -1);
											return 1;
										}

									}
								//��������
								return 0;//�ø�ֵ�����Լ�����
							}
						}
					}
					else {//��������

						//�ؿ���һ����û�г��Ƹ���
						if (ddz->iOnTable[ddz->iOTmax - 2 - 1][1] < 0 && ddz->iOnTable[ddz->iOTmax - 2 - 1][0] > -1)//�ϴ��Լ������Ƹ�����   
						{
							if (ddz->iOnTable[ddz->iOTmax - 2 - 1][0] / 4 <= min) {
								ddz->fnohope = 1;
								return 0;//��С�ƶ���Ҫ���𣬷�������,�ó��ƺ����Լ���
							}
						}
						//����С��Э������
						if (!(ddz->fnohope)) {
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 301, min, -1, -1, -1, -1);
							return 1;
						}
					}
				}
				
				
			}

		}
		//������
		else {
			//�¼��Ƕ���
			if (ddz->formation == 3|| ddz->formation == 2)
			{
				if (ddz->handCardInfor.PutAnyCard == 0)//��������
				{
					//if (ddz->iOnTable[ddz->iOTmax - 1][1] < 0)//�ϼҶ��ѳ����� 
					//	return 0;//�����ֺ����Լ���
					if (ddz->iLastTypeCount / 100 == 4)//Ŀǰ�Ƕ���
					{
						//ѹ��(֮ǰ�Ѿ��з�����Ѻ���)
						if (ddz->handCardInfor.CardPointNum[13] >= 2)//����ը
						{
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 102, 13, -1, -1, -1, -1);
							return 1;
						}
						//ը��ѹ��
						for (int i = 0; i < 13; i++)
							if (ddz->handCardInfor.CardPointNum[i] == 4)//�Լ���ը��
							{
								//�Է�����ը��������ը || �Է�ը�������Լ���
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
					//��������
					//��ը����Ϊ�Ĵ�����
					while (ownCard.bomb > 0 && ownCard.two > 1)
					{
						ownCard.fourDouble11[ownCard.fourTwo].cardTypeId = 1108;
						ownCard.fourDouble11[ownCard.fourTwo].minCard = ownCard.bomb2[ownCard.bomb - 1].minCard;//��Сը��
						ownCard.fourDouble11[ownCard.fourTwo].take1 = ownCard.double4[ownCard.two - 1].minCard;
						ownCard.fourDouble11[ownCard.fourTwo].take2 = ownCard.double4[ownCard.two - 2].minCard;
						ownCard.fourTwo++;
						//����
						ownCard.clearOneCard(&ownCard.bomb2[ownCard.bomb - 1]); ownCard.bomb--;
						ownCard.clearOneCard(&ownCard.double4[ownCard.two - 1]);
						ownCard.clearOneCard(&ownCard.double4[ownCard.two - 2]);
						ownCard.two -= 2;
						ownCard.sum -= 1;
						ownCard.Tidy();
					}
					//����˳��Ϊ��˳����  �� ����һ��
					if (ownCard.linkThree > 0)
					{
						for (int i = ownCard.linkThree - 1; i >= 0; i--)//����С��˳��ʼ
						{
							if (ownCard.two >= ownCard.linkThree && ownCard.two > 0)//���㹻����
							{
								ownCard.linkThreeDouble10[ownCard.linkThreeTwo].cardTypeId = 1000 + ((ownCard.linkThree9[i].cardTypeId % 100) / 3) * 5;
								ownCard.linkThreeDouble10[ownCard.linkThreeTwo].minCard = ownCard.linkThree9[i].minCard;
								ownCard.linkThreeDouble10[ownCard.linkThreeTwo].take1 = ownCard.double4[ownCard.two - 1].minCard;
								ownCard.linkThreeDouble10[ownCard.linkThreeTwo].take1 = ownCard.double4[ownCard.two - 2].minCard;
								ownCard.clearOneCard(&ownCard.double4[ownCard.two - 1]);
								ownCard.clearOneCard(&ownCard.double4[ownCard.two - 2]);
								ownCard.two -= 2;
								if (((ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId % 100) / 3) >= 3)///����
								{
									ownCard.linkThreeDouble10[ownCard.linkThreeTwo].take3 = ownCard.double4[ownCard.two - 1].minCard;
									ownCard.clearOneCard(&ownCard.double4[ownCard.two - 1]);
									ownCard.two -= 1;
									if (((ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId % 100) / 3) >= 4)//�Ĵ�
									{
										ownCard.linkThreeDouble10[ownCard.linkThreeTwo].take4 = ownCard.double4[ownCard.two - 1].minCard;
										ownCard.clearOneCard(&ownCard.double4[ownCard.two - 1]);
										ownCard.two -= 1;
									}
								}
								ownCard.linkThreeTwo++;
								ownCard.clearOneCard(&ownCard.linkThree9[i]); ownCard.linkThree--;//��˳����
								ownCard.Tidy();
							}
							else if (ownCard.single < ownCard.linkThree && ownCard.single > 0)//û���㹻�ĵ��ƣ���Ϊ����һ��
							{// �Ȳ�Ϊ���ţ������ٺϳ�����һ
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
					//�����ű�Ϊ����һ��
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
					//������˳�����
				//��˳����10����˳��˫10����˳9��˫˳8����˳7������һ��6��������6������5���Ĵ�����11���Ĵ�����11��ը��2�����1��3���ơ� ����4
					switch (10)
					{
					case 10: {//��˳����
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
					case 9: {//��˳
						if (ownCard.linkThree > 0)
						{
							int cardtype = ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId;
							int min = ownCard.linkThree9[ownCard.linkThree - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 8: {//˫˳8
						if (ownCard.linkTwo > 0)
						{
							int cardtype = ownCard.linkDouble8[ownCard.linkTwo - 1].cardTypeId;
							int min = ownCard.linkDouble8[ownCard.linkTwo - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 7: {//��˳7
						if (ownCard.linkSingle > 0)
						{
							int cardtype = ownCard.linkSingle7[ownCard.linkSingle - 1].cardTypeId;
							int min = ownCard.linkSingle7[ownCard.linkSingle - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 6: {//����һ
						if (ownCard.threeOne > 0)//����
						{
							int cardtype = ownCard.threeOne6[ownCard.threeOne - 1].cardTypeId;
							int min = ownCard.threeOne6[ownCard.threeOne - 1].minCard;
							int t1 = ownCard.threeOne6[ownCard.threeOne - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, -1, -1, -1);
							return 1;
						}
						if (ownCard.threeTwo > 0)//����
						{
							int cardtype = ownCard.threeDouble6[ownCard.threeTwo - 1].cardTypeId;
							int min = ownCard.threeDouble6[ownCard.threeTwo - 1].minCard;
							int t1 = ownCard.threeDouble6[ownCard.threeTwo - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, -1, -1, -1);
							return 1;
						}
					}
					case 5: {//����5
						if (ownCard.three > 0)
						{
							int cardtype = ownCard.three5[ownCard.three - 1].cardTypeId;
							int min = ownCard.three5[ownCard.three - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 11: {//�Ĵ���
						if (ownCard.fourSingle > 0)//����
						{
							int cardtype = ownCard.fourSingle11[ownCard.fourSingle - 1].cardTypeId;
							int min = ownCard.fourSingle11[ownCard.fourSingle - 1].minCard;
							int t1 = ownCard.fourSingle11[ownCard.fourSingle - 1].take1;
							int t2 = ownCard.fourSingle11[ownCard.fourSingle - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, t2, -1, -1);
							return 1;
						}
						if (ownCard.fourTwo > 0)//����
						{
							int cardtype = ownCard.fourDouble11[ownCard.fourTwo - 1].cardTypeId;
							int min = ownCard.fourDouble11[ownCard.fourTwo - 1].minCard;
							int t1 = ownCard.fourDouble11[ownCard.fourTwo - 1].take1;
							int t2 = ownCard.fourDouble11[ownCard.fourTwo - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, t2, -1, -1);
							return 1;
						}
					}
					case 2: {//ը��2
						if (ownCard.bomb > 0)
						{
							int cardtype = ownCard.bomb2[ownCard.bomb - 1].cardTypeId;
							int min = ownCard.bomb2[ownCard.bomb - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 1: {//���1
						if (ownCard.rocket > 0)
						{
							int cardtype = ownCard.rocket1.cardTypeId;
							int min = ownCard.rocket1.minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 3: {//3����
						if (ownCard.single > 0)
						{
							//����С��   //���ﲻ��Ӧ�ó������ѹ�Ƶ����� ���޸� 2020.8
							ownCard.Tidy();
							/*int cardtype = ownCard.single3[ownCard.single-1].cardTypeId;
							int min = ownCard.single3[ownCard.single-1].minCard;*/
							int cardtype = ownCard.single3[0].cardTypeId;
							int max = ownCard.single3[0].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, max, -1, -1, -1, -1);
							return 1;
						}
					}
					case 4: {//����4��
						if (ownCard.two > 0)
						{
							//ͬ�ϵ���
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
			//�¼��Ƕ���
			if (ddz->formation == 1)
			{
				if (ddz->handCardInfor.PutAnyCard == 0)//��������
				{
					//����ϼҶ��ֲ�����
					if (ddz->iOnTable[ddz->iOTmax - 1][0] < 0)
					{
						//���Ƹ�����
						ddz->handCardInfor.ClearPutCard();
						return 1;

					}
					//�ϼҶ��ֳ�����
					else 
					{
						//���Լ���С����
						int minCard = -1;
						for (int i = 0; i < 14; i++)
							if (ddz->handCardInfor.CardPointNum[i] >= 2)
							{
								minCard = i;
								break;
							}
						//�ϼҳ��˱��Լ���С�Ķ��ƣ�����
						if (ddz->iLastTypeCount / 100 == 4 && ddz->iLastMainPoint <= minCard)
						{
							ddz->handCardInfor.ClearPutCard();
							return 1;
						}
						//�Լ��и�С�Ķ���  || Ŀǰ���Ƕ���
						else if ((ddz->iLastTypeCount / 100 == 4 && ddz->iLastMainPoint - minCard >= 4) || ddz->iLastTypeCount / 100 != 4)
						{
							//ѹ��
							if (ddz->handCardInfor.CardPointNum[13] >= 2)//����ը
							{
								FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 102, 13, -1, -1, -1, -1);
								return 1;
							}
							//ը��ѹ��
							for (int i = 0; i < 13; i++)
								if (ddz->handCardInfor.CardPointNum[i] == 4)//�Լ���ը��
								{
									//�Է�����ը��������ը || �Է�ը�������Լ���
									if ((ddz->iLastTypeCount / 100 != 1 && ddz->iLastTypeCount / 100 != 2) || (ddz->iLastTypeCount / 100 == 2 && ddz->iLastMainPoint < i))
									{
										FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 204, i, -1, -1, -1, -1);
										return 1;
									}

								}
							//��������
							return 0;//�ø�ֵ�����Լ�����
						}
					}
					
				}
				else {
					//��������
					//���ȳ�����  �д��Ż����������һֱ��˫���һ�ֳ�һ����С����(���Ż�)
					if (AnalyzeTypeCount(ddz->iOnTable[ddz->iOTmax - 2 - 1]) / 100 == 4) 
					{
						if (ddz->iOnTable[ddz->iOTmax - 1 - 1][0] < 0) {
							ddz->fnohope = 1;
							return 0;
						}//���Ѳ�Ҫ����������
							
					}
					if (!(ddz->fnohope)&&ownCard.two > 0)//�Լ����ж���
					{
						//�ȳ�С��
						int minCard = ownCard.double4[ownCard.two - 1].minCard;
						FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 402, minCard, -1, -1, -1, -1);
						return 1;
					}
					return 0;//�����ֺ�����
				}
			}

		}
	}
	//�ϼ�ֻʣ������
	if (ddz->upCard.sum <= 2)
	{
		//ʣһ����
		if (ddz->upCard.sum == 1)
		{
			//�ϼ��Ƕ���
			if (ddz->formation == 1|| ddz->formation == 2)
			{
				//����ѹ�ƣ�Ȼ����ǵ��ƣ�����ֻ�е��ƣ�
				//��ը����Ϊ�Ĵ�����
								while (ownCard.bomb > 0 && ownCard.single > 1)
				{
					ownCard.fourSingle11[ownCard.fourSingle].cardTypeId = 1106;
					ownCard.fourSingle11[ownCard.fourSingle].minCard = ownCard.bomb2[ownCard.bomb - 1].minCard;//��Сը��
					ownCard.fourSingle11[ownCard.fourSingle].take1 = ownCard.single3[ownCard.single -1].minCard;//��С����
					ownCard.fourSingle11[ownCard.fourSingle].take2 = ownCard.single3[ownCard.single -2].minCard;
					ownCard.fourSingle++;
					//����
					ownCard.clearOneCard(&ownCard.bomb2[ownCard.bomb - 1]); ownCard.bomb--;
					ownCard.clearOneCard(&ownCard.single3[ownCard.single - 1]);
					ownCard.clearOneCard(&ownCard.single3[ownCard.single - 2]);
					ownCard.single -= 2;
					ownCard.sum -= 1;
					ownCard.Tidy();
				}
				//����˳��Ϊ��˳����  �� ����һ
				if (ownCard.linkThree > 0)
				{
					for (int i = ownCard.linkThree - 1; i >= 0; i--)//����С��˳��ʼ
					{
						if (ownCard.single >= ownCard.linkThree && ownCard.single > 0)//���㹻����
						{
							ownCard.linkThreeSingle10[ownCard.linkThreeSingle].cardTypeId = 1000 + ((ownCard.linkThree9[i].cardTypeId % 100) / 3) * 4;
							ownCard.linkThreeSingle10[ownCard.linkThreeSingle].minCard = ownCard.linkThree9[i].minCard;
							ownCard.linkThreeSingle10[ownCard.linkThreeSingle].take1 = ownCard.single3[ownCard.single - 1].minCard;
							ownCard.linkThreeSingle10[ownCard.linkThreeSingle].take1 = ownCard.single3[ownCard.single - 2].minCard;
							ownCard.clearOneCard(&ownCard.single3[ownCard.single - 1]);
							ownCard.clearOneCard(&ownCard.single3[ownCard.single - 2]);
							ownCard.single -= 2;
							if (((ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId % 100) / 3) >= 3)///����
							{
								ownCard.linkThreeSingle10[ownCard.linkThreeSingle].take3 = ownCard.single3[ownCard.single - 1].minCard;
								ownCard.clearOneCard(&ownCard.single3[ownCard.single - 1]);
								ownCard.single -= 1;
								if (((ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId % 100) / 3) >= 4)//�Ĵ�
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
						else if (ownCard.single < ownCard.linkThree && ownCard.single > 0)//û���㹻�ĵ��ƣ���Ϊ����һ
						{// �Ȳ�Ϊ���ţ������ٺϳ�����һ
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
				//�����ű�Ϊ����һ
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

				if (ddz->handCardInfor.PutAnyCard == 0) //��������
				{
					//ѹ��
					if (ddz->handCardInfor.CardPointNum[13] >= 2)//����ը
					{
						FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 102, 13, -1, -1, -1, -1);
						return 1;
					}
					//ը��ѹ��
					for(int i=0;i<13;i++)
						if (ddz->handCardInfor.CardPointNum[i] == 4)//�Լ���ը��
						{
							//�Է�����ը��������ը || �Է�ը�������Լ���
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
					//��������
					return 0;//�ø�ֵ�����Լ�����
				}
				else {
					//�Լ���������
					//������˳�����
				//��˳����10����˳��˫10����˳9��˫˳8����˳7������һ��6��������6������5���Ĵ�����11���Ĵ�����11������4��ը��2�����1��3����
					switch (10)
					{
					case 10: {//��˳����
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
					case 9: {//��˳
						if (ownCard.linkThree > 0)
						{
							int cardtype = ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId;
							int min = ownCard.linkThree9[ownCard.linkThree - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 8: {//˫˳8
						if (ownCard.linkTwo > 0)
						{
							int cardtype = ownCard.linkDouble8[ownCard.linkTwo - 1].cardTypeId;
							int min = ownCard.linkDouble8[ownCard.linkTwo - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 7: {//��˳7
						if (ownCard.linkSingle > 0)
						{
							int cardtype = ownCard.linkSingle7[ownCard.linkSingle - 1].cardTypeId;
							int min = ownCard.linkSingle7[ownCard.linkSingle - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 6: {//����һ
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
					case 5: {//����5
						if (ownCard.three > 0)
						{
							int cardtype = ownCard.three5[ownCard.three - 1].cardTypeId;
							int min = ownCard.three5[ownCard.three - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 11: {//�Ĵ�����11
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
					case 4: {//����4��
						if (ownCard.two > 0)
						{
							int cardtype = ownCard.double4[ownCard.two - 1].cardTypeId;
							int min = ownCard.double4[ownCard.two - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 2: {//ը��2
						if (ownCard.bomb > 0)
						{
							int cardtype = ownCard.bomb2[ownCard.bomb - 1].cardTypeId;
							int min = ownCard.bomb2[ownCard.bomb - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 1: {//���1
						if (ownCard.rocket > 0)
						{
							int cardtype = ownCard.rocket1.cardTypeId;
							int min = ownCard.rocket1.minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 3: {//3����
						if (ownCard.single > 0)
						{
							//�Ӵ�С��
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
			//�ϼ��Ƕ���
			if (ddz->formation == 3)
			{
				//��������
				if (ddz->handCardInfor.PutAnyCard == 0)
				{
					if (ddz->iOnTable[ddz->iOTmax - 1][0] < 0)//������Ѳ�Ҫ����ѹ�Ƶ������ƣ���ȡ�������Ʋ������ڶ��ѵĻ��� 
					{
						//ѹ��
						if (ddz->handCardInfor.CardPointNum[13] >= 2)//����ը
						{
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 102, 13, -1, -1, -1, -1);
							return 1;
						}
						//ը��ѹ��
						for (int i = 0; i < 13; i++)
							if (ddz->handCardInfor.CardPointNum[i] == 4)//�Լ���ը��
							{
								//�Է�����ը��������ը || �Է�ը�������Լ���
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
						//��������
						return 0;//�ø�ֵ�����Լ�����
					}
					else 
					{
						//����Ҫ�򲻳������ƣ�
						ddz->handCardInfor.ClearPutCard();
						return 1;
						
					}
				}
				//��������
				else
				{
					int min;
					//���Լ���С��
					for (int i = 0; i < 14; i++)
						if (ddz->handCardInfor.CardPointNum[i] > 0)
							min = i;
					//�ؿ���һ�ζ�����û�г����Ƹ���
					if (AnalyzeTypeCount(ddz->iOnTable[ddz->iOTmax - 2]) / 100 == 3)//�鿴�¼ң����֣������ѳ��ĵ��� 
					{
						
						if (ddz->iOnTable[ddz->iOTmax - 2][0] / 4 <= min)
						{
							ddz->fnohope = 1;
							return 0;//��С�Ʊȶ��ֵ��ƻ��󣬶��ѿ϶�Ҫ���𣬷�������,�ó��ƺ����Լ��� 
						}
					}
					//����С��Э������
					if (!ddz->fnohope) 
					{
						FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 301, min, -1, -1, -1, -1);
						return 1;
					}
					return 0;
				}
			}
		}
		//ʣ���� 
		else {
			//�ϼ��Ƕ���
			if (ddz->formation == 1|| ddz->formation == 2)
			{
				if (ddz->handCardInfor.PutAnyCard == 0)//��������
				{
					if (ddz->handCardInfor.CardPointNum[13] >= 2)//����ը
					{
						FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 102, 13, -1, -1, -1, -1);
						return 1;
					}
					//ը��ѹ��
					for (int i = 0; i < 13; i++)
						if (ddz->handCardInfor.CardPointNum[i] == 4)//�Լ���ը��
						{
							//�Է�����ը��������ը || �Է�ը�������Լ���
							if ((ddz->iLastTypeCount / 100 != 1 && ddz->iLastTypeCount / 100 != 2) || (ddz->iLastTypeCount / 100 == 2 && ddz->iLastMainPoint < i))
							{
								FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 204, i, -1, -1, -1, -1);
								return 1;
							}

						}
				}

				else
				{
					//��������
					//��ը����Ϊ�Ĵ�����
					while (ownCard.bomb > 0 && ownCard.two > 1)
					{
						ownCard.fourDouble11[ownCard.fourTwo].cardTypeId = 1108;
						ownCard.fourDouble11[ownCard.fourTwo].minCard = ownCard.bomb2[ownCard.bomb - 1].minCard;//��Сը��
						ownCard.fourDouble11[ownCard.fourTwo].take1 = ownCard.double4[ownCard.two - 1].minCard;
						ownCard.fourDouble11[ownCard.fourTwo].take2 = ownCard.double4[ownCard.two - 2].minCard;
						ownCard.fourTwo++;
						//����
						ownCard.clearOneCard(&ownCard.bomb2[ownCard.bomb - 1]); ownCard.bomb--;
						ownCard.clearOneCard(&ownCard.double4[ownCard.two - 1]);
						ownCard.clearOneCard(&ownCard.double4[ownCard.two - 2]);
						ownCard.two -= 2;
						ownCard.sum -= 1;
						ownCard.Tidy();
					}
					//����˳��Ϊ��˳����  �� ����һ��
					if (ownCard.linkThree > 0)
					{
						for (int i = ownCard.linkThree - 1; i >= 0; i--)//����С��˳��ʼ
						{
							if (ownCard.two >= ownCard.linkThree && ownCard.two > 0)//���㹻����
							{
								ownCard.linkThreeDouble10[ownCard.linkThreeTwo].cardTypeId = 1000 + ((ownCard.linkThree9[i].cardTypeId % 100) / 3) * 5;
								ownCard.linkThreeDouble10[ownCard.linkThreeTwo].minCard = ownCard.linkThree9[i].minCard;
								ownCard.linkThreeDouble10[ownCard.linkThreeTwo].take1 = ownCard.double4[ownCard.two - 1].minCard;
								ownCard.linkThreeDouble10[ownCard.linkThreeTwo].take1 = ownCard.double4[ownCard.two - 2].minCard;
								ownCard.clearOneCard(&ownCard.double4[ownCard.two - 1]);
								ownCard.clearOneCard(&ownCard.double4[ownCard.two - 2]);
								ownCard.two -= 2;
								if (((ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId % 100) / 3) >= 3)///����
								{
									ownCard.linkThreeDouble10[ownCard.linkThreeTwo].take3 = ownCard.double4[ownCard.two - 1].minCard;
									ownCard.clearOneCard(&ownCard.double4[ownCard.two - 1]);
									ownCard.two -= 1;
									if (((ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId % 100) / 3) >= 4)//�Ĵ�
									{
										ownCard.linkThreeDouble10[ownCard.linkThreeTwo].take4 = ownCard.double4[ownCard.two - 1].minCard;
										ownCard.clearOneCard(&ownCard.double4[ownCard.two - 1]);
										ownCard.two -= 1;
									}
								}
								ownCard.linkThreeTwo++;
								ownCard.clearOneCard(&ownCard.linkThree9[i]); ownCard.linkThree--;//��˳����
								ownCard.Tidy();
							}
							else if (ownCard.single < ownCard.linkThree && ownCard.single > 0)//û���㹻�ĵ��ƣ���Ϊ����һ��
							{// �Ȳ�Ϊ���ţ������ٺϳ�����һ
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
					//�����ű�Ϊ����һ��
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
					//������˳�����
				//��˳����10����˳��˫10����˳9��˫˳8����˳7������һ��6��������6������5���Ĵ�����11���Ĵ�����11��ը��2�����1��3���ơ� ����4
					switch (10)
					{
					case 10: {//��˳����
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
					case 9: {//��˳
						if (ownCard.linkThree > 0)
						{
							int cardtype = ownCard.linkThree9[ownCard.linkThree - 1].cardTypeId;
							int min = ownCard.linkThree9[ownCard.linkThree - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 8: {//˫˳8
						if (ownCard.linkTwo > 0)
						{
							int cardtype = ownCard.linkDouble8[ownCard.linkTwo - 1].cardTypeId;
							int min = ownCard.linkDouble8[ownCard.linkTwo - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 7: {//��˳7
						if (ownCard.linkSingle > 0)
						{
							int cardtype = ownCard.linkSingle7[ownCard.linkSingle - 1].cardTypeId;
							int min = ownCard.linkSingle7[ownCard.linkSingle - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 6: {//����һ
						if (ownCard.threeOne > 0)//����
						{
							int cardtype = ownCard.threeOne6[ownCard.threeOne - 1].cardTypeId;
							int min = ownCard.threeOne6[ownCard.threeOne - 1].minCard;
							int t1 = ownCard.threeOne6[ownCard.threeOne - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, -1, -1, -1);
							return 1;
						}
						if (ownCard.threeTwo > 0)//����
						{
							int cardtype = ownCard.threeDouble6[ownCard.threeTwo - 1].cardTypeId;
							int min = ownCard.threeDouble6[ownCard.threeTwo - 1].minCard;
							int t1 = ownCard.threeDouble6[ownCard.threeTwo - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, -1, -1, -1);
							return 1;
						}
					}
					case 5: {//����5
						if (ownCard.three > 0)
						{
							int cardtype = ownCard.three5[ownCard.three - 1].cardTypeId;
							int min = ownCard.three5[ownCard.three - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 11: {//�Ĵ���
						if (ownCard.fourSingle > 0)//����
						{
							int cardtype = ownCard.fourSingle11[ownCard.fourSingle - 1].cardTypeId;
							int min = ownCard.fourSingle11[ownCard.fourSingle - 1].minCard;
							int t1 = ownCard.fourSingle11[ownCard.fourSingle - 1].take1;
							int t2 = ownCard.fourSingle11[ownCard.fourSingle - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, t2, -1, -1);
							return 1;
						}
						if (ownCard.fourTwo > 0)//����
						{
							int cardtype = ownCard.fourDouble11[ownCard.fourTwo - 1].cardTypeId;
							int min = ownCard.fourDouble11[ownCard.fourTwo - 1].minCard;
							int t1 = ownCard.fourDouble11[ownCard.fourTwo - 1].take1;
							int t2 = ownCard.fourDouble11[ownCard.fourTwo - 1].take1;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, t1, t2, -1, -1);
							return 1;
						}
					}
					case 2: {//ը��2
						if (ownCard.bomb > 0)
						{
							int cardtype = ownCard.bomb2[ownCard.bomb - 1].cardTypeId;
							int min = ownCard.bomb2[ownCard.bomb - 1].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 1: {//���1
						if (ownCard.rocket > 0)
						{
							int cardtype = ownCard.rocket1.cardTypeId;
							int min = ownCard.rocket1.minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, min, -1, -1, -1, -1);
							return 1;
						}
					}
					case 3: {//3����
						if (ownCard.single > 0)
						{
							//����С��   //���ﲻ��Ӧ�ó������ѹ�Ƶ����� ���޸� 2020.8
							ownCard.Tidy();
							/*int cardtype = ownCard.single3[ownCard.single-1].cardTypeId;
							int min = ownCard.single3[ownCard.single-1].minCard;*/
							int cardtype = ownCard.single3[0].cardTypeId;
							int max = ownCard.single3[0].minCard;
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, cardtype, max, -1, -1, -1, -1);
							return 1;
						}
					}
					case 4: {//����4��
						if (ownCard.two > 0)
						{
							//ͬ�ϵ���
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
			//�ϼ��Ƕ���
			if (ddz->formation == 3)
			{
				if (ddz->handCardInfor.PutAnyCard == 0)//��������
				{
					if (ddz->iOnTable[ddz->iOTmax - 1][0] < 0) //���Ѳ�����
					{
						//ѹ�Ƶ�������ȡ�������ƵĻ���
						if (ddz->handCardInfor.CardPointNum[13] >= 2)//����ը
						{
							FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 102, 13, -1, -1, -1, -1);
							return 1;
						}
						//ը��ѹ��
						for (int i = 0; i < 13; i++)
							if (ddz->handCardInfor.CardPointNum[i] == 4)//�Լ���ը��
							{
								//�Է�����ը��������ը || �Է�ը�������Լ���
								if ((ddz->iLastTypeCount / 100 != 1 && ddz->iLastTypeCount / 100 != 2) || (ddz->iLastTypeCount / 100 == 2 && ddz->iLastMainPoint < i))
								{
									FindCardOnHandCard(ddz->handCardInfor.onHandCard, ddz->handCardInfor.PutCard, 204, i, -1, -1, -1, -1);
									return 1;
								}

							}
					}
					//������ѳ��˾�����
					else
					{
						ddz->handCardInfor.ClearPutCard();
						return 1;
					}
				}
				else //��������
				{
					
					int min;
					//���Լ���С����
					for (int i = 0; i < 14; i++)
						if (ddz->handCardInfor.CardPointNum[i] > 1)
							min = i;
					//�ؿ���һ�ζ�����û�г��Ƹ���
					if (AnalyzeTypeCount(ddz->iOnTable[ddz->iOTmax - 2]) / 100 == 4|| AnalyzeTypeCount(ddz->iOnTable[ddz->iOTmax - 2]) / 100 == 3)//�鿴�ϴ��¼ң����֣������ѳ��ĵ��� �����
					{
						
						//�д��Ż����������һֱ��˫���ܻ��һ�ֳ�һ����С����(���Ż�)
						if (ddz->iOnTable[ddz->iOTmax - 2][0] / 4 <= min)
						{
							ddz->fnohope = 1;
							return 0;//��С�������Ƶ����ȶ��ֵ��ƻ��󣬶��ѿ϶�Ҫ���𣬷�������,�ó��ƺ����Լ��� 
						}
					}
					//����С����Э������
					if (!(ddz->fnohope))  //�������԰����
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

//���ñ������ݳ�ʼֵ(��飺9.6)
void InitRound(struct Ddz* pDdz)
{
	int i, j;
	pDdz->iStatus = 1;					//��ʼ����������״̬
	strcpy(pDdz->sCommandIn, "");		//��ʼ������ͨ����������
	strcpy(pDdz->sCommandOut, "");		//��ʼ������ͨ���������
	strcpy(pDdz->sVer, "");				//��ʼ������Э��汾��
	strcpy(pDdz->sName, kPlayerName);		//��ʼ�����ֲ���ѡ�ֳƺ�
	pDdz->cDir = 'B';						//��ʼ��������ҷ�λ���
	pDdz->cLandlord = 'B';				//��ʼ�����ֵ�����λ���
	pDdz->cWinner = 'B';					//��ʼ������ʤ�߷�λ���
	pDdz->fnohope = 0;                   //��ʼ������Ϊ������
	for (i = 0; i < 3; i++)
		pDdz->iLef[i] = -1;             //��ʼ������
	for (i = 0; i < 21; i++)			//��ʼ����������
		pDdz->iOnHand[i] = -1;
	for (i = 0; i < 250; i++)				//��ʼ������������
		for (j = 0; j < 21; j++)
			pDdz->iOnTable[i][j] = -2;
	for (i = 0; i < 162; i++)
		pDdz->iOnPlayId[i] = 'E';        //��ʼֵ����ʾ����
	for (i = 0; i < 21; i++)			//��ʼ�����ֳ���
		pDdz->iToTable[i] = -1;
	for (i = 0; i < 3; i++)				//��ʼ�����ֽ���
		pDdz->iBid[i] = -1;
	for (i = 0; i < 14; i++)
		pDdz->allCardOnTable[i] = 0;
	pDdz->handCardInfor.InIt();//�Լ��������ʼ��
	pDdz->upCard.Init();//�ϼ����������ʼ��
	pDdz->lowCard.Init();
	
	pDdz->iLastPassCount = 0;		//��ǰ��������PASS����ֵ��[0,2],��ֵ0����������ȡ0��һ��PASSȡ1������PASSȡ2��
	pDdz->iLastTypeCount = 0;		//��ǰ��������������ֵ��[0,1108],��ֵ0��iLastPassCount=0ʱ����ֵ��=1ʱ����ԭֵ��=2ʱֵΪ0��
	pDdz->iLastMainPoint = -1;		//��ǰ�������Ƶ�����ֵ��[0,15],��ֵ-1��iLastPassCount=0ʱ����ֵ����=1ʱ����ԭֵ��=2ʱֵΪ-1��
	pDdz->iBmax = 0;					//��ʼ�����ֽ��Ʒ���
	pDdz->iOTmax = 0;					//��ʼ����������������
}

//����������ת��Ϊ�ַ���׷��(-1��)�����9.6��
void AppendCardsToS(int iCards[], char sMsg[])
{
	int i;
	char sCard[4] = "";
	char sCardString[90] = "";
	if (iCards[0] == -1)	// PASS
		strcat(sCardString, "-1");
	else					// ����PASS
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
		sCardString[strlen(sCardString) - 1] = '\0';	//ȥ�������β������

	}
	strcat(sMsg, sCardString);
}

//���ñ������ݳ�ʼֵ�����9.6��
void InitTurn(struct Ddz *pDdz)
{
	pDdz->iTurnTotal = 1;				//��ʼ��������
	pDdz->iTurnNow = 1;					//��ʼ����ǰ�ִ�
	pDdz->iRoundTotal = 1;				//��ʼ���ܾ���
	pDdz->iRoundNow = 1;				//��ʼ����ǰ�ִ�
	InitRound(pDdz);					//��ʼ����������
}

//����sCommandIn������Ϣ�����9.6��
void InputMsg(struct Ddz* pDdz)
{
	cin.getline(pDdz->sCommandIn, 80);
}

//����������Ϣ�����9.6��
void AnalyzeMsg(struct Ddz* pDdz)
{//��ȱ��ʱ��Ϣ����-------------�����ã�
	char sShort[4];
	int i;
	for (i = 0; i < 3; i++)
		sShort[i] = pDdz->sCommandIn[i];
	sShort[3] = '\0';
	if (strcmp(sShort, "DOU") == 0)					//�汾��Ϣ
	{
		GetDou(pDdz);
		return;
	}
	if (strcmp(sShort, "INF") == 0)					//�־���Ϣ info  ��Ϣ
	{
		GetInf(pDdz);
		return;
	}
	if (strcmp(sShort, "DEA") == 0)					//������Ϣ  deal ����
	{
		GetDea(pDdz);
		return;
	}
	if (strcmp(sShort, "BID") == 0)					//���ƹ���  bid Ͷ��
	{
		GetBid(pDdz);
		return;
	}
	if (strcmp(sShort, "LEF") == 0)					//������Ϣ
	{
		GetLef(pDdz);
		return;
	}
	if (strcmp(sShort, "PLA") == 0)					//���ƹ���
	{
		GetPla(pDdz);
		return;
	}
	if (strcmp(sShort, "GAM") == 0)					//ʤ����Ϣ  gameover ��Ϸ����
	{
		GetGam(pDdz);
		return;
	}
	if (strcmp(sShort, "EXI") == 0)					//ǿ���˳�
	{
		exit(0);
	}
	strcpy(pDdz->sCommandOut, "ERROR at module AnalyzeMsg,sCommandIn without match");//������ʾ
	return;
}

//��ȡ������汾��Ϣ������ͨ���������Ϊѡ������(���9.6)
void GetDou(struct Ddz* pDdz)
{
	int i;								//��ѭ������
	for (i = 0; pDdz->sCommandIn[i] != '\0'; i++)
		pDdz->sVer[i] = pDdz->sCommandIn[i];
	pDdz->sVer[i] = '\0';
	strcpy(pDdz->sCommandOut, "NAME ");
	strcat(pDdz->sCommandOut, pDdz->sName);//�ַ�������
}

//��ȡ�����־���ϢINF���������ͨ������OK INFO(���9.6)
void GetInf(struct Ddz* pDdz)		
{   //û��Ӧ��ʱ��������Ϣ���� 
	//�ִ���Ϣ������(����������Ϣ����Ӧд������Ա������):����INFO 1/4 1/9 9 2450     ���OK INFO
	//��ǰ����š�����������ǰ����š�ÿ���ܾ�����������ѡ�������ⶥ������Ӧ��ʱ��
	char c;					//�浱ǰ�ֽ���Ϣ		
	int iCount = 0;			//��¼���ݸ���
	int iTemp = 0;			//�м����
	int iMessage[7] = { 0 };		//��¼��������
	int i;
	for (i = 5; pDdz->sCommandIn[i] != '\0'; i++)
	{
		c = pDdz->sCommandIn[i];
		if (c >= '0' && c <= '9')											//��ǰ�ַ�Ϊ0-9
		{
			iTemp = iTemp * 10 + c - '0';
			iMessage[iCount] = iTemp;								//����ѡ����
		}
		if (c == ',')														//��ǰ�ַ�Ϊ����,
		{
			iCount++;
			iTemp = 0;
		}
	}
	pDdz->iTurnNow = iMessage[0];						//��ǰ�ִ�
	pDdz->iTurnTotal = iMessage[1];						//������
	pDdz->iRoundNow = iMessage[2];						//��ǰ�ִ�
	pDdz->iRoundTotal = iMessage[3];					//ÿ���ܾ���
	pDdz->iLevelUp = iMessage[4];						//����ѡ������
	pDdz->iScoreMax = iMessage[5];						//�ⶥ����
	pDdz->iTime = iMessage[6];                          //Ӧ��ʱ������
	strcpy(pDdz->sCommandOut, "OK INFO");
}

//��ȡ���淢����ϢDEA������ͨ�������ϢOK DEAL�����9.6��
void GetDea(struct Ddz* pDdz)
{  //DEAL dC1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,C17
	//d Ϊ��λ
	int i;			      //��ѭ������
	int iNow = 0;		  //��ǰ���������
	int iCardId = 0;	//��ǰ�����Ʊ���
	char c;			      //��ǰָ���ַ�
	pDdz->cDir = pDdz->sCommandIn[5];     //��ȡ����AI��λ��ţ�A || B || C��
	for (i = 0; i < 21; i++)				          //��������iOnhand[]
		pDdz->iOnHand[i] = -1;
	for (i = 6; pDdz->sCommandIn[i] != '\0'; i++)	//���ζ�ȡ����ָ��
	{
		c = pDdz->sCommandIn[i];			      //cΪ��ǰָ���ַ�
		if (c >= '0' && c <= '9')				        //��ǰ�ַ�Ϊ0-9
		{
			iCardId = iCardId * 10 + c - '0';
			pDdz->iOnHand[iNow] = iCardId;//��¼���ϵ���
		}
		if (c == ',')							            //��ǰ�ַ�Ϊ����,
		{
			iCardId = 0;
			iNow++;
		}
	}
	SortById(pDdz->iOnHand);  //iOnHand[]��С��������
	//���������п�����������
	for (i = 0; i < 21; i++)
		pDdz->handCardInfor.onHandCard[i] = pDdz->iOnHand[i];
	pDdz->handCardInfor.ArrangeHandCard();//��������
	strcpy(pDdz->sCommandOut, "OK DEAL");  //�ظ���Ϣ
	//���Բ��ƺ���
	//CheckChaiCard(pDdz);

}

//��ȡ���������ϢBID������ͨ���������OK BID��BID _0(���0.6)
void GetBid(struct Ddz* pDdz)
{                           //BID WHAT		BID A1
	if (pDdz->sCommandIn[4] == 'W')					//���������ϢΪBID WHAT������ѯ��ѡ�ֽ���
	{
		strcpy(pDdz->sCommandOut, "BID _0");
		pDdz->sCommandOut[4] = pDdz->cDir;//��ұ��
		int socre= callScore(pDdz->iOnHand);//���㲢������Ƶķ������£�
		//ֻ��Խ��Խ����߲���
		if (socre == 3)//���ƱȽϼ�����3����ò�
			socre = 2;
		if (socre > pDdz->iBmax)//��
		{
			pDdz->iBid[pDdz->cDir - 'A'] = socre;//���㲢������Ƶķ������£�
			pDdz->iBmax = pDdz->iBid[pDdz->cDir - 'A'];//����������
			pDdz->sCommandOut[5] = '0' + pDdz->iBid[pDdz->cDir - 'A'];		//
		}
		else {//������ֻ�ܲ���
			pDdz->iBid[pDdz->cDir - 'A'] = 0;//���㲢������Ƶķ������£�
			pDdz->sCommandOut[5] = '0' + pDdz->iBid[pDdz->cDir - 'A'];		//
		}

		//pDdz->iBid[pDdz->cDir - 'A'] = callScore(pDdz->iOnHand);//���㲢������Ƶķ������£�
		//if (pDdz->iBid[pDdz->cDir - 'A'] > pDdz->iBmax)//����ǲ��������Ʒ���
		//	pDdz->iBmax = pDdz->iBid[pDdz->cDir - 'A'];
		//pDdz->sCommandOut[5] = '0'+ pDdz->iBid[pDdz->cDir - 'A'];		//
		pDdz->sCommandOut[6] = '\0';
		return;
	}
	if (pDdz->sCommandIn[4] >= 'A' && pDdz->sCommandIn[4] <= 'C')  //������ϢΪBID **������ת������ѡ�ֽ�����Ϣ
	{
		pDdz->iBid[pDdz->sCommandIn[4] - 'A'] = pDdz->sCommandIn[5] - '0';//��������ѡ�ֽ��Ʒ���	
		if (pDdz->iBid[pDdz->sCommandIn[4] - 'A'] > pDdz->iBmax)//����ǲ��������Ʒ���
			pDdz->iBmax = pDdz->iBid[pDdz->sCommandIn[4] - 'A'];
		strcpy(pDdz->sCommandOut, "OK BID");
		return;
	}
}

//��ȡ���������ϢLEF������ͨ���������OK LEFTOVER(���9.6)
void GetLef(struct Ddz* pDdz)
{                //LEFTOVER B27,48,53
	int i, iCount = 0;
	char c;
	pDdz->cLandlord = pDdz->sCommandIn[9];    //���������λ
	pDdz->iLef[0] = 0;
	pDdz->iLef[1] = 0;
	pDdz->iLef[2] = 0;
	for (i = 10; pDdz->sCommandIn[i] != '\0'; i++)//�������
	{
		c = pDdz->sCommandIn[i];
		if (c >= '0' && c <= '9')
			pDdz->iLef[iCount] = pDdz->iLef[iCount] * 10 + c - '0';
		else
			iCount++;
	}
	//����ȷ��
	if (pDdz->cLandlord == pDdz->cDir)//�Լ��ǵ���
	{
		pDdz->formation = 2;//��ũ AI ũ��
	}
	else {//�Լ����ǵ���
		if (pDdz->cDir == 'A')//��A
		{
			if (pDdz->cLandlord == 'B')
				pDdz->formation = 3;
			else pDdz->formation = 1;
		}
		else if (pDdz->cDir == 'B')//��B
		{
			if (pDdz->cLandlord == 'A')
				pDdz->formation = 1;
			else pDdz->formation = 3;
		}
		else if (pDdz->cDir == 'C')//��C
		{
			if (pDdz->cLandlord == 'B')
				pDdz->formation = 1;
			else pDdz->formation = 3;
		}
	}

	if (pDdz->sCommandIn[9] == pDdz->cDir)//����Լ��ǵ���
	{     //(54-3)/3=17
		pDdz->iOnHand[17] = pDdz->iLef[0];
		pDdz->iOnHand[18] = pDdz->iLef[1];
		pDdz->iOnHand[19] = pDdz->iLef[2];
		pDdz->iOnHand[20] = -1;//

		SortById(pDdz->iOnHand);					//iOnHand[]��С��������
		for (int j = 0; pDdz->iOnHand[j]>-1; j++)//����������
		{
			pDdz->handCardInfor.onHandCard[j] = pDdz->iOnHand[j];
		}
		pDdz->handCardInfor.ArrangeHandCard();//����������
	}
	else if (pDdz->formation == 1 )//����ϼ��ǵ���
	{
		pDdz->upCard.sum += 3;
		for (int h = 0; h < 3; h++)//��¼����
			pDdz->upCard.surCardPoint[pDdz->iLef[h] / 4]++;
	}
	else if (pDdz->formation == 3 )//����¼��ǵ���
	{
		pDdz->lowCard.sum += 3;
		for (int h = 0; h < 3; h++)//��¼����
			pDdz->lowCard.surCardPoint[pDdz->iLef[h] / 4]++;
	}

	strcpy(pDdz->sCommandOut, "OK LEFTOVER");
}

//��ȡ�����������ϢPLA(���9.6)
void GetPla(struct Ddz* pDdz)
{                //PLAY WHAT  PLAY C-1
	//�����ô����
	CheckPut(pDdz);


	if (pDdz->sCommandIn[5] == 'W')			//�Լ�����
	{
		if (pDdz->handCardInfor.PutAnyCard !=0 )//��������
		{
			//���ж�˭�ȱ�������
			//if(!AlertCard(pDdz))

			//һ�����
				PutCardWayActive(pDdz->handCardInfor);
		}
		else {//��������
			//�ò��ý���
			//if (JudgePutCard(pDdz))
			//{
				//if(!AlertCard(pDdz))
					//��ͨ�ƾ�
					PutCardWayUnactive(pDdz->handCardInfor);
			//}
			//else pDdz->handCardInfor.ClearPutCard();//����
		}

		for (int i = 0; i < 21; i++)
			pDdz->iToTable[i] = pDdz->handCardInfor.PutCard[i];

		strcpy(pDdz->sCommandOut, "PLAY _");
		pDdz->sCommandOut[5] = pDdz->cDir;		//��ȡ�Լ��ķ�λ��ţ���������Ԥ����Ϣ׼����sCommandOut����
		AppendCardsToS(pDdz->iToTable, pDdz->sCommandOut);		//Ҫ��������iToTable[]�е�����ת��Ϊ�ַ������ӵ�sCommandOut��
		UpdateMyPla(pDdz);		//���ݼ������Ƹ�������
	}
	else										//�����յ���ϢΪ������ҳ���
	{
		UpdateHisPla(pDdz);		//�������˳��Ƹ�������       
		strcpy(pDdz->sCommandOut, "OK PLAY");//�ظ��յ�
	}

	//������ ����
	//Check(pDdz);

}

//�����Լ������Ƹ������ݣ����9.6��
void UpdateMyPla(struct Ddz* pDdz)
{
	int i, j, k;
	if (pDdz->iToTable[0] == -1)	//Pass
	{
		pDdz->iOnTable[pDdz->iOTmax][0] = -1;//ͳ�������ܳ������
		pDdz->iOnPlayId[pDdz->iOTmax] = pDdz->cDir;//��¼��λ
		pDdz->iOTmax++;

		pDdz->iLastPassCount = 0;
		pDdz->handCardInfor.PutAnyCard = 0;//�����Գ�������
	}
	else						//����PASS
	{
		//����������
		for (i = 0; pDdz->iToTable[i] >= 0; i++)
		{
			pDdz->iOnTable[pDdz->iOTmax][i] = pDdz->iToTable[i];

			pDdz->allCardOnTable[pDdz->iToTable[i] / 4]++;//��������
		}
		pDdz->iOnTable[pDdz->iOTmax][i] = -1;
		pDdz->iOnPlayId[pDdz->iOTmax] = pDdz->cDir;//��¼��λ
		pDdz->iOTmax++;

		//����������----------û����-1��β
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

		for (j = 0; j < 21; j++)//����һ������
			pDdz->handCardInfor.onHandCard[j] = pDdz->iOnHand[j];
		pDdz->handCardInfor.ArrangeHandCard();//������������
		//�������������
		pDdz->handCardInfor.PutAnyCard = pDdz->iLastPassCount = 0;
		pDdz->handCardInfor.tableTypeCount = pDdz->iLastTypeCount = AnalyzeTypeCount(pDdz->iToTable);
		pDdz->handCardInfor.tableMainPoint = pDdz->iLastMainPoint = AnalyzeMainPoint(pDdz->iToTable);
	}
}

//�������˳��Ƹ�������(���9.6,��Ӽ���������10.5)
void UpdateHisPla(struct Ddz* pDdz)
{//PLAY C-1
	int i;
	int iCardId;
	int iNow;
	char c;
	//����������
	if (pDdz->sCommandIn[6] == '-')// PLAY ?-1 ��PASS
	{
		pDdz->iOnTable[pDdz->iOTmax][0] = -1;
		pDdz->iOnPlayId[pDdz->iOTmax] = pDdz->sCommandIn[5];//��¼��λ
		pDdz->iOTmax++;
		pDdz->iLastPassCount++;

		if (pDdz->iLastPassCount >= 2)	//��������pass
		{
			pDdz->handCardInfor.PutAnyCard = 1;//���Գ�������
			pDdz->handCardInfor.tableMainPoint = -1;//û����С��
			pDdz->handCardInfor.tableTypeCount = 0;//����

			pDdz->iLastPassCount = 0;//
			pDdz->iLastTypeCount = 0;//��ǰ����������������
			pDdz->iLastMainPoint = -1;
		}
	}
	else						// PLAY ���ƣ��������ƣ�
	{
		for (i = 0; i < 21; i++)							//����iToTable[]
			pDdz->iToTable[i] = -1;
		iCardId = 0;//��ʱ����
		iNow = 0;//��ʱ����
		for (i = 6; pDdz->sCommandIn[i] != '\0'; i++)		//���ζ�ȡ����
		{
			c = pDdz->sCommandIn[i];					//cΪ��ǰָ���ַ�
			if (c >= '0' && c <= '9')				        //��ǰ�ַ�Ϊ0-9
			{
				iCardId = iCardId * 10 + c - '0';
				pDdz->iToTable[iNow] = iCardId;
			}
			if (c == ',')									//��ǰ�ַ�Ϊ����,
			{
				iCardId = 0;
				iNow++;
			}
		}
		//����������
		for (i = 0; pDdz->iToTable[i] >= 0; i++)
		{
			pDdz->iOnTable[pDdz->iOTmax][i] = pDdz->iToTable[i];
			pDdz->allCardOnTable[pDdz->iToTable[i] / 4]++;//��������
		}
		pDdz->iOnTable[pDdz->iOTmax][i] = -1;//��-1��β
		pDdz->iOnPlayId[pDdz->iOTmax] = pDdz->sCommandIn[5];//��¼��λ
		pDdz->handCardInfor.PutAnyCard = pDdz->iLastPassCount = 0;//0��pass�����ܳ�������
		pDdz->handCardInfor.tableTypeCount = pDdz->iLastTypeCount = AnalyzeTypeCount(pDdz->iToTable);//����������������
		pDdz->handCardInfor.tableMainPoint = pDdz->iLastMainPoint = AnalyzeMainPoint(pDdz->iToTable);//����������С������
		pDdz->iOTmax++;

		//������(��ʱ�����˳��)
		if ((pDdz->cDir == 'A' && pDdz->sCommandIn[5] == 'C') || (pDdz->cDir == 'B' && pDdz->sCommandIn[5] == 'A') ||
			(pDdz->cDir == 'C' && pDdz->sCommandIn[5] == 'B'))
		{//�ϼҳ���
			for (int h = 0; pDdz->iToTable[h] > -1; h++)
			{
				pDdz->upCard.putCardPoint[pDdz->iToTable[h] / 4]++;
				pDdz->upCard.sum--;
				for (int hh = 0; hh < 14; hh++)
					if (pDdz->upCard.surCardPoint[hh] > 0 && pDdz->upCard.surCardPoint[hh] == pDdz->iToTable[h] / 4)
						pDdz->upCard.surCardPoint[hh]--;
			}
		}
		else {//�¼ҳ���
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


//��ȡ������ʤ����ϢGAM�����9.6��
void GetGam(struct Ddz* pDdz)
{
	pDdz->cWinner = pDdz->sCommandIn[9];			//ʤ���߷�λ���
	if (pDdz->iRoundNow == pDdz->iRoundTotal)		//�����ǰ������ÿ�־����ʱ
	{
		pDdz->iStatus = 0;							//����״̬������Ϊ����
	}
	else											//����
	{
		pDdz->iRoundNow++;							//��ǰ�ִμ�1
		InitRound(pDdz);							//����״̬������Ϊ���¿�ʼ��һ��
	}
	strcpy(pDdz->sCommandOut, "OK GAMEOVER");
}

//�����Ϣ�����9.6��
void OutputMsg(struct Ddz* pDdz)
{
	cout << pDdz->sCommandOut << endl;
}

//�����������ݣ����9.6��
void CalOthers(struct Ddz* pDdz)
{
	pDdz->iVoid = 0;
}
