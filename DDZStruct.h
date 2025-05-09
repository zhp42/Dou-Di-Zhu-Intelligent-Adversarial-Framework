#pragma once

#include <stdlib.h>//malloc����̬�ڴ���亯������ֹջ�ڴ治�㵼�����
#include<iostream>
using namespace std;

/*���Ƽ�ֵ�ṹ��(��ֵ������)*/
struct HandCardValue
{
	int value;//��ֵ
	int needPly;//����
};

/*
������Ͻṹ(������������ֵ��������С����������1������2������3������4)
�ýṹΪ�˷��������Ʋ���
����ʼֵ ��������-1����ֵ0����С����-1����
*/
struct CardGroup
{
	int cardTypeId = -1;//��������
	int value=0;//��ֵ
	int minCard=-1;//���Ƶ�����Сһλ
	int take1 = -1;//����
	int take2 = -1;
	int take3 = -1;
	int take4 = -1;
};

/* Ϊ����ϲ��Ʋ���
��������ƶ�Ӧ���Ƶ���������
*/
class OwnCardGroup
{
public:
	int sum=0;//��������
	int rocket=0, bomb=0, single=0, two=0, three=0, threeOne=0, threeTwo=0, linkSingle=0, linkTwo=0, linkThree=0;
	int linkThreeSingle=0, linkThreeTwo=0, fourSingle=0, fourTwo=0;
	CardGroup rocket1;				//���1�����
	CardGroup bomb2[5];				//���5��ը��
	CardGroup single3[20];	//���20����
	CardGroup double4[10];	//���10����
	CardGroup three5[6];	//���6����
	CardGroup threeOne6[5];	//���5����һ��
	CardGroup threeDouble6[4];//���4����һ��
	CardGroup linkSingle7[4];//���4��˳���12
	CardGroup linkDouble8[3];//���3���ԣ��20
	CardGroup linkThree9[3];//���3��˳���20
	CardGroup linkThreeSingle10[2];//���2��˳������
	CardGroup linkThreeDouble10[2];//���2��˳����
	CardGroup fourSingle11[3];//���3�Ĵ�����
	CardGroup fourDouble11[2];//���2�Ĵ����� 
public:
	//���ĳ���������
	void clearOneCard(struct CardGroup *cardGroup)
	{
		cardGroup->cardTypeId = -1;
		cardGroup->minCard = -1;
		cardGroup->take1 = cardGroup->take2 = cardGroup->take3 = cardGroup->take4 = -1;
		cardGroup->value = -1;
	}
	//��ʼ������ȫ��������ÿ�
	void Init()
	{
		sum = 0;
		//���������Ϊ0��
		rocket = bomb = single = two = three = threeOne = threeTwo = linkSingle = 0;
		linkTwo = linkThree = linkThreeSingle = linkThreeTwo = fourSingle = fourTwo = 0;
		clearOneCard(&rocket1);//���
		for (int i = 0; i < 5; i++)//ը��
			clearOneCard(&bomb2[i]);
		for (int i = 0; i < 20; i++)//����
			clearOneCard(&single3[i]);
		for (int i = 0; i < 10; i++)//����
			clearOneCard(&double4[i]);
		for (int i = 0; i < 6; i++)//����
			clearOneCard(&three5[i]);
		for (int i = 0; i < 5; i++)//����һ��
			clearOneCard(&threeOne6[i]);
		for (int i = 0; i < 4; i++)//����һ��
			clearOneCard(&threeDouble6[i]);
		for (int i = 0; i < 4; i++)//��˳
			clearOneCard(&linkSingle7[i]);
		for (int i = 0; i < 3; i++)//˫˳
			clearOneCard(&linkDouble8[i]);
		for (int i = 0; i < 3; i++)//��˳
			clearOneCard(&linkThree9[i]);
		for (int i = 0; i < 2; i++)//��˳����
			clearOneCard(&linkThreeSingle10[i]);
		for (int i = 0; i < 2; i++)//��˳��˫
			clearOneCard(&linkThreeDouble10[i]);
		for (int i = 0; i < 3; i++)//�Ĵ�����
			clearOneCard(&fourSingle11[i]);
		for (int i = 0; i < 2; i++)//�Ĵ�����
			clearOneCard(&fourDouble11[i]);
	}
	//��������ƣ���ķ�ǰ��
	void Tidy()
	{
		if (rocket1.cardTypeId != -1) rocket = 1;
		for(int i=0;i<5;i++)//ը��
			for (int j = i + 1; j < 5; j++)
				if (bomb2[i].minCard < bomb2[j].minCard)
				{
					CardGroup tCard = bomb2[i];
					bomb2[i] = bomb2[j]; bomb2[j] = tCard;
				}
		for (int i = 0; i < 20; i++)//����
			for (int j = i + 1; j < 20; j++)
				if (single3[i].minCard < single3[j].minCard)
				{
					CardGroup tCard = single3[i];
					single3[i] = single3[j]; single3[j] = tCard;
				}
		for (int i = 0; i < 10; i++)//����
			for (int j = i + 1; j < 10; j++)
				if (double4[i].minCard < double4[j].minCard)
				{
					CardGroup tCard = double4[i];
					double4[i] = double4[j]; double4[j] = tCard;
				}
		for (int i = 0; i < 6; i++)//����
			for (int j = i + 1; j < 6; j++)
				if (three5[i].minCard < three5[j].minCard)
				{
					CardGroup tCard = three5[i];
					three5[i] = three5[j]; three5[j] = tCard;
				}
		for (int i = 0; i < 5; i++)//����һ��
			for (int j = i + 1; j < 5; j++)
				if (threeOne6[i].minCard < threeOne6[j].minCard)
				{
					CardGroup tCard = threeOne6[i];
					threeOne6[i] = threeOne6[j]; threeOne6[j] = tCard;
				}
		for (int i = 0; i < 4; i++)//����һ��
			for (int j = i + 1; j < 4; j++)
				if (threeDouble6[i].minCard < threeDouble6[j].minCard)
				{
					CardGroup tCard = threeDouble6[i];
					threeDouble6[i] = threeDouble6[j]; threeDouble6[j] = tCard;
				}
		for (int i = 0; i < 4; i++)//��˳
			for (int j = i + 1; j < 4; j++)
				if (linkSingle7[i].minCard < linkSingle7[j].minCard)
				{
					CardGroup tCard = linkSingle7[i];
					linkSingle7[i] = linkSingle7[j]; linkSingle7[j] = tCard;
				}
		for (int i = 0; i < 3; i++)//˫˳
			for (int j = i + 1; j < 3; j++)
				if (linkDouble8[i].minCard < linkDouble8[j].minCard)
				{
					CardGroup tCard = linkDouble8[i];
					linkDouble8[i] = linkDouble8[j]; linkDouble8[j] = tCard;
				}
		for (int i = 0; i < 3; i++)//��˳
			for (int j = i + 1; j < 3; j++)
				if (linkThree9[i].minCard < linkThree9[j].minCard)
				{
					CardGroup tCard = linkThree9[i];
					linkThree9[i] = linkThree9[j]; linkThree9[j] = tCard;
				}
		for (int i = 0; i < 2; i++)//��˳����
			for (int j = i + 1; j < 2; j++)
				if (linkThreeSingle10[i].minCard < linkThreeSingle10[j].minCard)
				{
					CardGroup tCard = linkThreeSingle10[i];
					linkThreeSingle10[i] = linkThreeSingle10[j]; linkThreeSingle10[j] = tCard;
				}
		for (int i = 0; i < 2; i++)//��˳��˫
			for (int j = i + 1; j < 2; j++)
				if (linkThreeDouble10[i].minCard < linkThreeDouble10[j].minCard)
				{
					CardGroup tCard = linkThreeDouble10[i];
					linkThreeDouble10[i] = linkThreeDouble10[j]; linkThreeDouble10[j] = tCard;
				}
		for (int i = 0; i < 3; i++)//�Ĵ�����
			for (int j = i + 1; j < 3; j++)
				if (fourSingle11[i].minCard < fourSingle11[j].minCard)
				{
					CardGroup tCard = fourSingle11[i];
					fourSingle11[i] = fourSingle11[j]; fourSingle11[j] = tCard;
				}
		for (int i = 0; i < 2; i++)//�Ĵ�����
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
������(�Լ�ʹ��)
Ϊ�˷���������Ƽ�ֵ
*/
class HandCard
{
public:
	int onHandCard[21];//�������У�ֵΪ�Ƶı��,��ʼֵ-1���������СΪ21
	int CardPointNum[14] = { 0 };//�����Ƶ����������������СΪ14
	int sumNum;//����������,��ʼֵ0
	int value;//Ŀǰ���Ƽ�ֵ,��ʼֵ0

	CardGroup PutCardGroup;//Ҫ�����Ƶ��������
	int PutCard[21];//Ҫ�����������У�ֵΪ�Ʊ��,�����СΪ21 

	int PutAnyCard = -1;//�Ƿ���Գ�������  1�������ƣ�0�������ƣ�-1���������жϵ����������Ի��Ǳ�������
	int tableTypeCount = -1;//��ǰ������������
	int tableMainPoint = -1;//��ǰ�������ƣ���С������

public:
	//������ƣ�ȫ����ֵΪ-1�����Ƶ������顢����������ֵ
	void ClearHandCard() {
		for (int i = 0; i < 21; i++)
			onHandCard[i] = -1;
		for (int i = 0; i < 14; i++)
			CardPointNum[i] = 0;
		sumNum = 0;
		value = 0;
	}
	//��ճ������С��������ͽṹ��
	void ClearPutCard() {
		for (int i = 0; i < 21; i++)
			PutCard[i] = -1;
		PutCardGroup.cardTypeId = -1;
		PutCardGroup.value = 0;
		PutCardGroup.minCard = -1;
		PutCardGroup.take1 = PutCardGroup.take2 = PutCardGroup.take3 = PutCardGroup.take4 = -1;//���Ƴ�ʼ��
	}
	//����onHandCard[]��������������
	void CalSumNum() {
		sumNum = 0;
		for (int i = 0; onHandCard[i] > -1; i++)
			sumNum++;
	}
	//����onHandCard[]�����Ƶ���
	void CalPointNum() {
		for (int i = 0; i < 14; i++)//���
			CardPointNum[i] = 0;
		for (int i = 0; onHandCard[i] > -1; i++)//����
			CardPointNum[onHandCard[i] / 4]++;
	}
	//�������Ƽ�����Ƶ�������������
	void ArrangeHandCard() {
		CalPointNum();//��������Ƶ���
		CalSumNum();//����������
	}
	//�������ʼ������
	void InIt()
	{
		ClearHandCard();//�������
		ClearPutCard();//��ճ�������
		PutAnyCard = -1;//��ʼ��Ϊ -1
		tableTypeCount = -1;
		tableMainPoint = -1;
	}
};

/*
������������࣬������¼���˵��ƣ���һ���Ʋ��Լ��Ĳ���
*/
class AboutCard
{
public:
	int sum;//����ʣ������,��ʼֵ 17
	int surCardPoint[14];//ʣ�����Ƶ���  ����֪����������,��ʼֵ 0
	int putCardPoint[14];//�Ѵ�����Ƶ���,��ʼֵ 0

public:
	//��ʼ��
	void Init()
	{
		sum = 17;
		for (int i = 0; i < 14; i++)
			putCardPoint[i] = 0;
		for (int i = 0; i < 14; i++)
			surCardPoint[i] = 0;
	}
	//�����������м����ѳ��Ƶ���
	void CalPutCardPoint(int card[])
	{
		for (int i = 0; card[i] >= 0; i++)
		{
			putCardPoint[card[i] / 4]++;//��¼
			if (surCardPoint[card[i] / 4] > 0)//�޳�
				surCardPoint[card[i] / 4]--;
			sum--;//����--
		}
	}
};
//�������ṹ�壨��Ϸȫ�֣�
struct Ddz
{
	int  iStatus;			//����״̬-1����,0����,1��ʼ
	char sCommandIn[80];	//ͨ����������
	char sCommandOut[80];	//ͨ���������
	char sVer[80];			//Э��汾��
	char sName[80];			//����ѡ�ֳƺ�
	int iRoundNow;			//��ǰ�ִ�
	int iRoundTotal;		//ÿ���ܾ���
	int iTurnNow;			//��ǰ�ִ�
	int iTurnTotal;			//������
	int iLevelUp;			//����ѡ����
	int iScoreMax;			//�ⶥ����
	int iTime;              //Ӧ��ʱ������

	char cDir;				//����ҷ�λ���,Ĭ��ΪB,Ҳ������A C
	char cLandlord;			//������ҷ�λ��ţ����Ը��ݵ�����λ�ж϶��ѵ�λ��
	char cWinner;			//ʤ���߷�λ���
	int iBid[3];			//���ƹ���  ABC��ҷֱ��Ӧ����0 1 2
	int iBmax;				//��ǰ��������ֵ��{0,1,2,3}
	int iOTmax;				//��ǰ�������������˶������ƣ���Ϊ�˼�¼iOnTable[162][21]
	int iOnHand[21];		//�����ƣ�����ֵ��ʼ��Ϊ-1��,ֵΪ�Ƶı��
	HandCard handCardInfor;    //������Ϣ��
	int iOnTable[250][21];	//�Ѿ����ȥ���ƣ�����ֵ��ʼ��Ϊ-2��ÿ����һ���ƣ���-1��β��Pass��Ϊ-1 ��250����1000ver2020.1
	char iOnPlayId[162];       //��¼ÿ�γ��Ƶ���ұ�ţ������ҳ���˭�����,��ʼֵΪ E����ʾerror
	int iToTable[21];		//������Է� �����Ҫ�� ����
	int allCardOnTable[14] = {0}; //ͳ�������Ѿ��������
	int formation;          //����ȷ�� 1.���� AI �ѡ� 2.��ũ AI ũ�� 3.���� AI �ء�
	int fnohope;            //�ѷ�����/˫ʱ����Ϊ��Ϊ��Ӯ�ı�ǣ�1���ܶ��ѣ����ɳ��ƣ�
	AboutCard upCard, lowCard; //�ϼҺ��¼����ƵĴ������,(�Լ���һ����B��)

	int iVoid;				//��Ͼ���м������
	int iLef[3];			//���ֵ���
	int iLastPassCount;		//��ǰ��������PASS����ֵ��[0,2],��ֵ2����������ȡ0��һ��PASSȡ1������PASSȡ2��
	int iLastTypeCount;		//��ǰ������������,���ͱ��+����λ������,��ֵ��[0,1108],��ֵ0��iLastPassCount=0ʱ����ֵ��=1ʱ����ԭֵ��=2ʱֵΪ0��
	int iLastMainPoint;		//��ǰ�������Ƶ�����ֵ��[0,15],��ֵ-1��iLastPassCount=0ʱ����ֵ����=1ʱ����ԭֵ��=2ʱֵΪ-1��
};

/*------------------------------------��������-------------------------*/
int CountCards(int iCards[]);//�����������
void SortById(int iCards[]);//���Ʊ��루��С����������
int	AnalyzeMainPoint(int iCards[]);//����������С����,���Ʒ���-1��
void SortByMain(int iCards[]);//��������Ҫ������������
int	AnalyzeTypeCount(int iCards[]);//��������Ҫ������������
void SortByMuch(int iCards[]);//������(ͬ������)������������,���ƶ�ķ���ǰ�棬�Ա��ҳ�������С����
//�Լ��Ӻ���
int FindFourSame(int max, int card[], OwnCardGroup& cardGroup);//���ݾ��Ƶ�����������ͬ��,����¼
int FindSanShun(int max, int card[], OwnCardGroup& ownCardGroup);//�����Ƶ�������˳����¼,
int FindShuangShun(int max, int card[], OwnCardGroup& ownCardGroup);//�����Ƶ�����˫˳����¼
int FindDanShun(int max, int card[], OwnCardGroup& ownCard);//���ݵ����ҵ�˳
int FindSanZhang(int max, int card[], OwnCardGroup& ownCard);//�����Ƶ���������
int FindDuiPai(int max, int card[], OwnCardGroup& ownCard);//�����Ƶ����Ҷ���
void ChaiCard(int card[], OwnCardGroup& cardGroup);//���ƺ���,�����Ƶ�������,������
//���Ժ���
void CheckChaiCard(struct Ddz* ddz);//����鿴���ƺ��������

//�ж�����
int IsType0Pass(int iCs[]);//�жϳ��������Ƿ�Ϊ��Ȩ(û����)
int IsType1Rocket(int iCs[]);//�жϳ��������Ƿ�Ϊ���
int IsType2Bomb(int iCs[]);//�жϳ��������Ƿ�Ϊը��
int	IsType3Single(int iCs[]);//�жϳ��������Ƿ�Ϊ����
int	IsType4Double(int iCs[]);//�жϳ��������Ƿ�Ϊ����
int	IsType5Three(int iCs[]);//�жϳ��������Ƿ�Ϊ����
int IsType6ThreeOne(int iCs[]);//�жϳ��������Ƿ�Ϊ����һ��
int IsType6ThreeDouble(int iCs[]);//�жϳ��������Ƿ�Ϊ����һ��
int IsType7LinkSingle(int iCs[]);//�жϳ��������Ƿ�Ϊ��˳
int IsType8LinkDouble(int iCs[]);//�жϳ��������Ƿ�Ϊ����
int	IsType9LinkThree(int iCs[]);//�жϳ��������Ƿ�Ϊ��˳
int	IsType10LinkThreeSingle(int iCs[]);//�ж���˳����������1�ǣ�0����
int	IsType10LinkThreeDouble(int	iCs[]);//�ж���˳���ԣ�����1�ǣ�0����
int IsType11FourSingle(int iCs[]);//�жϳ��������Ƿ�Ϊ�Ĵ�����
int IsType11FourDouble(int iCs[]);//�жϳ��������Ƿ�Ϊ�Ĵ�����
/*------------------------------------��������-------------------------*/



//�����������
int CountCards(int iCards[])
{
	int iCount = 0;
	while (iCards[iCount] > -1)
		iCount++;
	return iCount;
}

//���Ʊ��루��С����������
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

//����������С����,���Ʒ���-1��
int	AnalyzeMainPoint(int iCards[])
{
	if (IsType0Pass(iCards))//����
		return -1;
	SortByMuch(iCards);
	return iCards[0] / 4;
}

//�жϳ��������Ƿ�Ϊ��Ȩ(û����)
int IsType0Pass(int iCs[])
{
	int iCount;
	iCount = CountCards(iCs);
	if (iCount == 0)//û���ƣ�����ʾ���ƣ�pass
		return 1;
	return 0;
}

//�жϳ��������Ƿ�Ϊ���
int IsType1Rocket(int iCs[])
{
	if ((iCs[2] == -1) && (iCs[0] + iCs[1] == 52 + 53))//ֻ�������Ʋ����Ǵ�С��
		return 1;
	return 0;
}

//�жϳ��������Ƿ�Ϊը��
int IsType2Bomb(int iCs[])
{
	if (4 != CountCards(iCs))//����������
		return 0;
	if ((iCs[4] == -1) &&
		(iCs[0] / 4 != -1 && //��ֹ���ǿյ�
			iCs[0] / 4 == iCs[1] / 4 && iCs[0] / 4 == iCs[2] / 4 && iCs[0] / 4 == iCs[3] / 4))
		return 1;
	return 0;
}

//�жϳ��������Ƿ�Ϊ����
int	IsType3Single(int iCs[])
{
	if (iCs[0] != -1 && iCs[1] == -1)//ֻ��һ����
		return 1;
	return 0;
}

//�жϳ��������Ƿ�Ϊ����
int	IsType4Double(int iCs[])
{
	if (IsType1Rocket(iCs))//����ǻ�����򷵻ش���
		return 0;
	if (iCs[0] / 4 == iCs[1] / 4 && iCs[0] != -1 && iCs[2] == -1)//ֻ�������ƣ�������һ��������
		return 1;
	return 0;
}

//�жϳ��������Ƿ�Ϊ����
int	IsType5Three(int iCs[])
{
	//ֻ�����ŷǿ��ƣ�������һ���ĵ���
	if (iCs[0] != -1 &&
		iCs[0] / 4 == iCs[1] / 4 && iCs[0] / 4 == iCs[2] / 4 
		&& iCs[3] == -1)
		return 1;
	return 0;
}

//�жϳ��������Ƿ�Ϊ����һ��
int IsType6ThreeOne(int iCs[])
{
	if (IsType2Bomb(iCs) || 4 != CountCards(iCs))//�����ը�����߲���������
		return 0;//�ų���������ͬ�����
	SortByMuch(iCs);
	if (iCs[0] / 4 == iCs[1] / 4 && iCs[0] / 4 == iCs[2] / 4 )
		return 1;
	return 0;
}

//�жϳ��������Ƿ�Ϊ����һ��
int IsType6ThreeDouble(int iCs[])
{
	if (5 != CountCards(iCs))//��������
		return 0;
	SortByMuch(iCs);
	if (iCs[0] / 4 == iCs[1] / 4 && iCs[0] / 4 == iCs[2] / 4)
		if (iCs[3] / 4 == iCs[4] / 4)//���ֻ������һ������
			return 1;
	return 0;
}

//�жϳ��������Ƿ�Ϊ��˳
int IsType7LinkSingle(int iCs[])
{
	int iCount = CountCards(iCs);
	if (iCount >= 5)
	{
		SortById(iCs);
		for (int i = 1; iCs[i] >= 0; i++)
			if (iCs[i - 1] / 4 + 1 != iCs[i] / 4 || iCs[i] >= 48)//��������������1��2����������˳��
				return 0;
		return 1;
	}
	return 0;
}

//�жϳ��������Ƿ�Ϊ����
int IsType8LinkDouble(int iCs[])
{
	int iCount = CountCards(iCs);
	if (iCount < 6 || iCount % 2 != 0)
		return 0;
	SortById(iCs);   //��iCs������
	for (int i = 1; i < iCount; i++)
	{
		if (iCs[i] >= 48) return 0;//˫˳������2����
		//�ж�i�ǵ�������˫��
		if (i % 2!=0)
		{
			//���i�ǵ��������i���Ƶı������������һ���Ʊ���
			if (iCs[i] / 4 != iCs[i - 1] / 4)
				return 0;
		}
		else
		{
			//���i��˫�������i���Ƶı������������һ���Ʊ���+1  
			if (iCs[i] / 4 != iCs[i - 1] / 4 + 1)
				return 0;
		}
	}
	return 1;
}

//�жϳ��������Ƿ�Ϊ��˳
int	IsType9LinkThree(int iCs[])
{ 
	int iCount = CountCards(iCs);
	if (iCount < 6 || iCount % 3 != 0)
		return 0;
	int i, iMinNum, iMaxNum;   //iMinNum Ϊ iCs ��С����,iMaxNum Ϊ iCs ������
	SortById(iCs);   //��iCs������
	iMinNum = iCs[0] / 4;
	iMaxNum = iMinNum + (iCount / 3) - 1;

	int iTempArr[14];//��ʼ������iTempArr������¼ 3 - A ÿ������������
	for (int h = 0; h < 14; h++)
		iTempArr[h] = 0;

	for (i = 0; i < iCount; i++)
	{
		//�ж�iCs[i]�Ƿ�����Ч������Χ��
		if (iCs[i] >= 48 || iCs[i] / 4 < iMinNum || iCs[i] / 4 > iMaxNum)//��˳������2����
		{
			return 0;
		}
		iTempArr[iCs[i] / 4]++;
	}
	for (i = iMinNum; i <= iMaxNum; i++)
	{
		//�ж��Ƿ�ÿ����Ч������Ϊ3����
		if (iTempArr[i]!=3)
		{
			return 0;
		}
	}
	return 1;
}

//�ж���˳����������1�ǣ�0����
int	IsType10LinkThreeSingle(int iCs[])
{
	int iCount = CountCards(iCs);
	if (iCount < 8 || iCount % 4 != 0)
		return 0;
	int iTempArr[14] ;//��¼�Ƶ���
	for (int i = 0; i < 14; i++)
		iTempArr[i] = 0;
	int iMinNum, iMaxNum;//iMinNum Ϊ iCs ��С����,iMaxNum Ϊ iCs ������
	SortByMuch(iCs);   //����
	iMinNum = iCs[0]/4;
	iMaxNum = iMinNum + iCount / 4 - 1;
	for (int i = 0; i < iCount; i++)//ͳ���Ƶĸ���
		iTempArr[iCs[i] / 4]++;
	int t = 0;//ͳ�Ƶ��Ƹ���
	for (int i = 0; i <= 13; i++)
	{
		if (i >= iMinNum && i <= iMaxNum)//��������ŵ���
		{
			if (iTempArr[i] != 3)
			{
				return 0;
			}
		}
		else//������
		{
			if (iTempArr[i] == 1) t++;//����ǵ���
			else if (iTempArr[i] == 0) continue;//û���ƣ������´�ѭ��
			else return 0;//������˳���ƣ�Ҳ���ǵ��ƣ����ش���
		}
	}
	if (t == iCount/4)//������������
		return 1;
	return 0;
}

//�ж���˳���ԣ�����1�ǣ�0����
int	IsType10LinkThreeDouble(int	iCs[])
{
	int iCount = CountCards(iCs);
	if (iCount < 10 || iCount % 5 != 0)
		return 0;
	int iTempArr[14];
	for (int i = 0; i < 14; i++)
		iTempArr[i] = 0; 
	int iMinNum, iMaxNum;//iMinNum Ϊ iCs ��С����,iMaxNum Ϊ iCs ������
	SortByMuch(iCs);   //����
	iMinNum = iCs[0] / 4;
	iMaxNum = iMinNum + iCount / 5 - 1;
	for (int i = 0; i < iCount; i++)//ͳ���Ƶĸ���
		iTempArr[iCs[i] / 4]++;
	int t = 0;//ͳ�ƶ��Ƶ�����
	for (int i = 0; i <= 13; i++)
	{
		if (i >= iMinNum && i <= iMaxNum)//��������ŵ���
		{
			if (iTempArr[i] != 3)
			{
				return 0;
			}
		}
		else//������
		{	//���Ƕ��ƾ��ǿ��ƣ����򷵻ش���
			if (iTempArr[i] == 2) t++;
			else if (iTempArr[i] == 0) continue;
			else return 0;
		}
	}
	if (t == iCount / 5)//������������
		return 1;
	return 0;
}

//�жϳ��������Ƿ�Ϊ�Ĵ�����
int IsType11FourSingle(int iCs[])
{
	int iCount = CountCards(iCs);
	if (iCount != 6)
		return 0;
	SortByMuch(iCs);  //ͬ�������Ƶ�����ǰ��
	if (iCs[0] / 4 == iCs[1] / 4 && iCs[0] / 4 == iCs[2] / 4 && iCs[0] / 4 == iCs[3] / 4  //����ͬ��
		&& iCs[4]/4!=iCs[5]/4 && iCs[4]/4!=iCs[0]/4 && iCs[5]/4!=iCs[0]/4)  //���Ų�ͬ����
		return 1;
	return 0;
}

//�жϳ��������Ƿ�Ϊ�Ĵ�����
int IsType11FourDouble(int iCs[])
{
	int iCount = CountCards(iCs);
	if (iCount != 8)
		return 0;
	SortByMuch(iCs);  //ͬ�������Ƶ�����ǰ��
	if (iCs[0] / 4 == iCs[1] / 4 && iCs[0] / 4 == iCs[2] / 4 && iCs[0] / 4 == iCs[3] / 4)  //����
		if (iCs[4] / 4 == iCs[5] / 4 && iCs[6] / 4 == iCs[7] / 4)  //��������
			if(iCs[4]/4!=iCs[6]/4 && iCs[4]/4!=iCs[0]/4 && iCs[6]/4!=iCs[0]/4)//��ͬ����
			return 1;
	return 0;
}

/*	�����������м��� �����������������飩	���� -1��*/
int	AnalyzeTypeCount(int iCards[])
{
	int iCount  = CountCards(iCards);//�����������

	if (IsType0Pass(iCards))//�ж����Ƿ�Ϊpass
		return 0 * 100 + iCount;
	if (IsType1Rocket(iCards))//�ж��Ƿ�Ϊ���
		return 1 * 100 + iCount;
	if (IsType2Bomb(iCards))//�ж��Ƿ�Ϊը��
		return 2 * 100 + iCount;
	if (IsType3Single(iCards))//�ж��Ƿ�Ϊ������
		return 3 * 100 + iCount;
	if (IsType4Double(iCards))//�ж��Ƿ�Ϊ����
		return 4 * 100 + iCount;
	if (IsType5Three(iCards))//�ж��Ƿ�Ϊ����
		return 5 * 100 + iCount;
	if (IsType6ThreeOne(iCards))//�ж��Ƿ�Ϊ����һ�ŵ���
		return 6 * 100 + iCount;
	if (IsType6ThreeDouble(iCards))//�ж��Ƿ�Ϊ������
		return 6 * 100 + iCount;
	if (IsType7LinkSingle(iCards))//�ж��Ƿ�Ϊ��˳
		return 7 * 100 + iCount;
	if (IsType8LinkDouble(iCards))//�ж��Ƿ�Ϊ˫˳
		return 8 * 100 + iCount;
	if (IsType9LinkThree(iCards))//�ж��Ƿ�Ϊ��˳
		return 9 * 100 + iCount;
	if (IsType10LinkThreeSingle(iCards))//�ж��Ƿ�Ϊ��˳����
		return 10 * 100 + iCount;
	if (IsType10LinkThreeDouble(iCards))//�ж��Ƿ�Ϊ��˳����
		return 10 * 100 + iCount;
	if (IsType11FourSingle(iCards))//�ж��Ƿ�Ϊ �Ĵ�����
		return 11 * 100 + iCount;
	if (IsType11FourDouble(iCards))//�ж��Ƿ�Ϊ �Ĵ���˫
		return 11 * 100 + iCount;

	return -1;
}

//��������Ҫ�����������У���ʱû�ã�
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

//������(ͬ������)������������,���ƶ�ķ���ǰ�棬�Ա��ж�����
void SortByMuch(int iCards[])
{
	int i, j, k, n;

	// iTempArr[i][0]����װ����Ϊ i �ж������ƣ�
	// iTempArr[i][1],iTempArr[i][2],iTempArr[i][3],iTempArr[i][4]����װ����Ϊ i ���Ƶı��룬
	int iTempArr[14][5];
	for (int h = 0; h < 14; h++)//������ȫ����ʼ��Ϊ -1
	{
		iTempArr[h][0] = 0;
		for (int hh = 1; hh < 5; hh++)
			iTempArr[h][hh] = -1;
	}
	for (i = 0; iCards[i] > -1; i++)//���ư��������࣬����¼������ÿ�ű���
	{
		if (iCards[i] <= 53)//���Ϸ�Χ
		{
			iTempArr[iCards[i] / 4][++(iTempArr[iCards[i] / 4][0])] = iCards[i];
		}
	}
	n = 0;   //nΪiCards���±꣬���½�iTempArr�е�������iCards��
	for (i = 0; iCards[i] > -1; i++)//�������
		iCards[i] = -1;
	//���ҳ�iTempArrһ���������ƣ�������д��ԭ����iCards�����У�Ȼ����Ѱ�����ŵģ���������	
	for (i = 4; i > 0; i--)
	{
		for (j = 0; j <= 13; j++)
		{
			if (iTempArr[j][0] == i)    //�жϸõ��������ǲ����� i ��
			{
				for (k = 1; k <= i; k++)    // �еĻ����Ͱ��ƶ��Ž�iCards[ n ]�У�Ȼ�� n++
				{
					iCards[n++] = iTempArr[j][k];
				}
			}
		}
	}
}

//���ݾ��Ƶ�����ը����,����¼(10.10���)
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

//�����Ƶ�������˳����¼,(10.10���)
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

//�����Ƶ�����˫˳����¼,(10.10���)
int FindShuangShun(int max, int card[], OwnCardGroup& ownCardGroup)
{
	if (max < 2) return 0;//���Ȳ���
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

//���ݵ����ҵ�˳(10.10���)
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

//�����Ƶ���������(10.10���)
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

//�����Ƶ����Ҷ��ƣ�10.10��飩
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

//���ƺ���,�����Ƶ�������,������(10.10���ԣ����)
void ChaiCard(int card[], OwnCardGroup& cardGroup)
{
	//�ȳ�ʼ��
	cardGroup.Init();

	int key = 1, max = -1;

	while (key)
	{
		//�ж������Ƿ����
		key = 0;
		for (int i = 0; i < 14; i++)
			if (card[i] > 0)
				key = 1;
		if (key == 0) break;
		//���ҵ�ǰ����Ƶ���
		for(int i=13;i>=0;i--)
			if (card[i] > 0)
			{
				max = i; break;
			}

		if (card[13] == 2)//���
		{
			card[13] -= 2;
			cardGroup.rocket1.cardTypeId = 102;
			cardGroup.rocket1.minCard = 13;
			cardGroup.rocket = 1;
			continue;
		}
		else if (FindFourSame(max,card,cardGroup))//ը��
		{
			continue;
		}
		if (FindSanShun(max, card, cardGroup))//��˳
		{
			continue;
		}
		if (FindShuangShun(max,card,cardGroup))//˫˳
		{
			continue;
		}
		if (FindDanShun(max, card, cardGroup))//��˳
		{
			continue;
		}
		if (FindSanZhang(max, card, cardGroup))//����
		{
			continue;
		}
		else if (FindDuiPai(max, card, cardGroup))//����
		{
			continue;
		}
		else {//����
			if (card[max] <= 0) continue;
			cardGroup.single3[cardGroup.single].cardTypeId = 301;
			cardGroup.single3[cardGroup.single].minCard = max;
			cardGroup.single++;
			card[max] -= 1;
		}
	}
	cardGroup.Tidy();//����
}

//����鿴��������(10.10���ԣ����)
void CheckChaiCard(struct Ddz* ddz)
{
	cout << "���ƣ�";
	for (int i = 0; ddz->handCardInfor.onHandCard[i] > -1; i++)
		cout << ddz->handCardInfor.onHandCard[i] / 4 << " ";
	cout << endl;
	cout << "������";
	for (int i = 0; i < 14; i++)
		cout << ddz->handCardInfor.CardPointNum[i] << " ";
	OwnCardGroup ownCard;
	ChaiCard(ddz->handCardInfor.CardPointNum, ownCard);
	cout << endl;
	if (ownCard.rocket > 0)
	{
		cout << "�������" << ownCard.rocket << endl;
	}
	if (ownCard.bomb > 0)
	{
		cout << "ը������" << ownCard.bomb << endl;
		for (int i = 0; i < ownCard.bomb; i++)
		{
			cout << ownCard.bomb2[i].minCard << " ";
		}
		cout << endl;
	}
	if (ownCard.fourSingle > 0)
	{
		cout << "�Ĵ�������" << ownCard.fourSingle << endl;
		for (int i = 0; i < ownCard.fourSingle; i++)
			cout << ownCard.fourSingle11[i].minCard << " "<<ownCard.fourSingle11[i].take1<<" "<< ownCard.fourSingle11[i].take2<<" |";
		cout << endl;
	}
	if (ownCard.fourTwo > 0)
	{
		cout << "�Ĵ����ԣ�" << ownCard.fourTwo << endl;
		for (int i = 0; i < ownCard.fourTwo; i++)
			cout << ownCard.fourDouble11[i].minCard << " " << ownCard.fourDouble11[i].take1 << " " << ownCard.fourDouble11[i].take2 << " |";
		cout << endl;
	}
	if (ownCard.linkThreeSingle > 0)
	{
		cout << "��˳������" << ownCard.linkThreeSingle << endl;
		for (int i = 0; i < ownCard.linkThreeSingle; i++)
			cout << ownCard.linkThreeSingle10[i].minCard << " "<<ownCard.linkThreeSingle10[i].take1<<" "<<ownCard.linkThreeSingle10[i].take2<<"|";
		cout << endl;
	}
	if (ownCard.linkThreeTwo > 0)
	{
		cout << "��˳���ԣ�" << ownCard.linkThreeTwo << endl;
		for (int i = 0; i < ownCard.linkThreeTwo; i++)
			cout << ownCard.linkThreeDouble10[i].minCard << " "<< ownCard.linkThreeDouble10[i].take1<<" "<< ownCard.linkThreeDouble10[i].take2<<"|";
		cout << endl;
	}
	if (ownCard.linkThree > 0)
	{
		cout << "��˳��" << ownCard.linkThree << endl;
		for (int i = 0; i < ownCard.linkThree; i++)
			cout << ownCard.linkThree9[i].cardTypeId<<" "<<ownCard.linkThree9[i].minCard << "| ";
		cout << endl;
	}
	if (ownCard.linkTwo > 0)
	{
		cout << "˫˳��" << ownCard.linkTwo << endl;
		for (int i = 0; i < ownCard.linkTwo; i++)
			cout << ownCard.linkDouble8[i].minCard << " ";
		cout << endl;
	}
	if (ownCard.linkSingle > 0)
	{
		cout << "��˳��" << ownCard.linkSingle << endl;
		for (int i = 0; i < ownCard.linkSingle; i++)
			cout << ownCard.linkSingle7[i].minCard << " ";
		cout << endl;
	}
	if (ownCard.threeOne > 0)
	{
		cout << "����һ����" << ownCard.threeOne << endl;
		for (int i = 0; i < ownCard.threeOne; i++)
			cout << ownCard.threeOne6[i].minCard << " ���� " <<ownCard.threeOne6[i].take1<<" ";
		cout << endl;
	}
	if (ownCard.threeTwo > 0)
	{
		cout << "����һ�ԣ�" << ownCard.threeTwo << endl;
		for (int i = 0; i < ownCard.threeTwo; i++)
			cout << ownCard.threeDouble6[i].minCard << " ���� " << ownCard.threeDouble6[i].take1 << " ";
		cout << endl;
	}
	if (ownCard.three > 0)
	{
		cout << "���ţ�" << ownCard.three << endl;
		for (int i = 0; i < ownCard.three; i++)
			cout << ownCard.three5[i].minCard  << " ";
		cout << endl;
	}
	if (ownCard.two > 0)
	{
		cout << "���ƣ�" << ownCard.two << endl;
		for (int i = 0; i < ownCard.two; i++)
			cout << ownCard.double4[i].minCard <<" ";
		cout << endl;
	}
	if (ownCard.single > 0)
	{
		cout << "���ƣ�" << ownCard.single << endl;
		for (int i = 0; i < ownCard.single; i++)
			cout << ownCard.single3[i].minCard << " ";
		cout << endl;
	}
}

