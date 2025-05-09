#pragma once
/*
��ֵ���������ļ�
Ŀǰ���������Ƽ�ֵ�����ͼ������Ų��Ժ���������ý��
*/
#include"DDZStruct.h"
#include<algorithm>

#define Rotation 6//��ֵ���ַ��У�ÿ�ִε�ֵ���ݶ�
/*
7  ���ڼ����������ȳ����ƣ����ܿ�����Ϊ��С������Ӯ
6 ���ǲ���ô���Ǻ���С�ƣ�2 k 10 8 ,�����Ƴ�2         *********** �ݶ�

4 ���װ�����Ʋ�ɢ��  �����ƴ�����22����Ѷ�2��ɵ�2��   ����

���ڽзֵĽ��飺
	1��#define Rotation 6 ���ˣ����Ƽ����������ȳ����ƣ�С�����ں���
	2��#define Rotation 6 С�ˣ����ڱ��أ����Ŵ��Ʋ���
	3�����ھ����ֵ�����Բο�����ļ�¼  ��  �Լ����ԣ�

	4�����糡������Լ���һЩ�����糡Ҫ���أ�
*/

using namespace std;

/* ========================��������============================*/
int CardTypeValue(int num, int minCard);//����������͵ļ�ֵ
void FindCardOnHandCard(int handCard[], int save[], int CardTypeCout, int minCard, int take1, int take2, int take3, int take4);
HandCardValue GetCardValue(HandCard& handCard);
void PutCardWay(HandCard& handCard);
void PutCardWayActive(HandCard& handCard);
void PutCardWayUnactive(HandCard& handCard);
int JudgeOneHand(int card[]);//�����Ƶ������ж��ǲ���һ����
CardGroup JudgeOneHand2(int CardPointNum[]);//�����Ƶ����ж��ǲ���һ����
/* ========================��������============================*/


/*
�������Ʊ����жϸ����ǲ���һ����
��	�������ͱ��
���� 0
��  -1
*/
int JudgeOneHand(int card[])//���Ƶ����顢��С�ƣ����ھ�����С��
{
	if (IsType0Pass(card)) return 0;//û����
	if (IsType1Rocket(card)) return 1;//���
	if (IsType2Bomb(card)) return 2;//ը��
	if (IsType3Single(card)) return 3;//����
	if (IsType4Double(card)) return 4;//����
	if (IsType5Three(card)) return 5;//����
	if (IsType6ThreeDouble(card)) return 6;//��������
	if (IsType6ThreeOne(card)) return 6;//��������
	if (IsType7LinkSingle(card)) return 7;//��˳
	if (IsType8LinkDouble(card)) return 8;//˫˳
	if (IsType9LinkThree(card)) return 9;//��˳
	if (IsType10LinkThreeSingle(card)) return 10; //��˳������
	if (IsType10LinkThreeDouble(card)) return 10; //��˳������
	if (IsType11FourSingle(card)) return 11;//�Ĵ�����
	if (IsType11FourDouble(card)) return 11;//�Ĵ�����

	return -1;
}

/*�������Ƶ����ж��ǲ���һ����
����������ϣ�������������ֵ��������С������
��������ʱ����������Ϊ -1��
*/
CardGroup JudgeOneHand2(int CardPointNum[])
{
	CardGroup tCardGroup;//����ʼֵ  ��������-1����С����-1����ֵ0����
	tCardGroup.cardTypeId = -1;//��ʼֵ
	int sum = 0;
	for (int i = 0; i < 14; i++)
		sum += CardPointNum[i];
	//����
	if (sum == 0)
	{
		tCardGroup.cardTypeId = 0;//��ʾ��������
		tCardGroup.value = 0;
	}
	//����
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
	//���ơ����
	else if (sum == 2)
	{
		for (int i = 0; i < 14; i++)
		{
			if (CardPointNum[i] == 2)
			{
				if (i < 13)//����
				{
					tCardGroup.cardTypeId = 402;
					tCardGroup.minCard = i;
					tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
					break;
				}
				else if (i == 13)//���
				{
					tCardGroup.cardTypeId = 102;
					tCardGroup.minCard = i;
					tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
					break;
				}
			}
		}
	}
	//����
	else if (sum == 3)
	{
		for (int i = 0; i < 13; i++)//�϶�������
			if (CardPointNum[i] == 3)
			{
				tCardGroup.cardTypeId = 503;
				tCardGroup.minCard = i;
				tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
				break;
			}
	}
	//ը��������һ����
	else if (4 == sum)
	{
		for (int i = 0; i < 13; i++)//��������
		{
			if (CardPointNum[i] == 4)//ը��
			{
				tCardGroup.cardTypeId = 204;
				tCardGroup.minCard = i;
				tCardGroup.value = CardTypeValue(tCardGroup.cardTypeId, tCardGroup.minCard);
				break;
			}
			if (CardPointNum[i] == 3)//����һ��
			{
				for (int j = 0; j < 14; j++)//��������
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
	//����һ�ԡ���˳
	else if (5 == sum)
	{
		for (int i = 0; i < 13; i++)//����һ�ԣ���������
		{
			if (CardPointNum[i] == 3)
			{
				for (int j = 0; j < 14; j++)//����
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
		for (int i = 0, pro = 0; i < 12; i++)//��˳(������2����)
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
	//��˳��˫˳����˳����˳��������˳���ԡ��Ĵ��������Ĵ�����
	else if (6 <= sum)
	{
		if (sum == 6)//�Ĵ�����
		{
			for (int i = 0; i < 13; i++)//��������
			{
				if (CardPointNum[i] == 4)
				{
					for (int j = 0; j < 13; j++)//һ��(����ѭ����14)
					{
						if (CardPointNum[j] == 1)
						{
							for (int k = j + 1; k < 14; k++)//����
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
		if (sum == 8)//�Ĵ�����
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
					break;//��ʱ����
				}
			}
		}
		if (sum % 5 == 0)//��˳������
		{
			int pro = 0;
			for (int i = 0; i < 13; i++)//��������
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
			if (pro == 2)//����
			{
				for (int i = 0; i <= 12; i++)//һ��������ѭ����13
				{
					if (CardPointNum[i] == 2)
					{
						for (int j = i + 1; j < 14; j++)//����
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
			else if (pro == 3)//����
			{
				for (int i = 0; i <= 11; i++)//һ����ѭ���Ż�
				{
					if (CardPointNum[i] == 2)
					{
						for (int j = i + 1; j <= 12; j++)//����
						{
							if (CardPointNum[j] == 2)
							{
								for (int k = j + 1; k <= 13; k++)//����
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
			else if (pro == 4)//����
			{
				for (int i = 0; i <= 10; i++)//һ��(ѭ���Ż�)
				{
					if (CardPointNum[i] == 2)
					{
						for (int j = i + 1; j <= 11; j++)//����
						{
							if (CardPointNum[j] == 2)
							{
								for (int k = j + 1; k <= 12; k++)
								{
									if (CardPointNum[k] == 2)//����
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
		if (sum % 4 == 0)//��˳������
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
				for (int i = 0; i <= 12; i++)//һ����ѭ���Ż���
				{
					if (CardPointNum[i] == 1)
					{
						for (int j = i + 1; j <= 13; j++)//����
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
				for (int i = 0; i <= 11; i++)//һ����ѭ���Ż���
				{
					if (CardPointNum[i] == 1)
					{
						for (int j = i + 1; j <= 12; j++)//����
						{
							if (CardPointNum[j] == 1)
							{
								for (int k = j + 1; k <= 13; k++)//����
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
				for (int i = 0; i <= 10; i++)//һ����ѭ���Ż���
				{
					if (CardPointNum[i] == 1)
					{
						for (int j = i + 1; j <= 11; j++)//����
						{
							if (CardPointNum[j] == 1)
							{
								for (int k = j + 1; k <= 12; k++)
								{
									if (CardPointNum[k] == 1)//����
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
		if (sum % 3 == 0)//��˳
		{
			for (int i = 0, pro = 0; i < 12; i++)//������2����
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
		if (sum % 2 == 0)//˫˳
		{
			for (int i = 0, pro = 0; i < 12; i++)//������2����
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
		for (int i = 0, pro = 0; i < 12; i++)//��˳  //������2����
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
�������ͣ����ض�Ӧ�ļ�ֵ,�������ͷ���-10000
������������������С������
1.����������ֵ��������Ϊ10�����е�λ�ã���<10���Ƽ�ֵΪ��������10�ĵ��Ƽ�ֵΪ��
2.���ֵļ�ֵ���壺������Ϊһ�ο���Ȩ���Ե���һ��������С���ͣ���С���ͣ�3���ļ�ֵΪ-7�������Ƕ���һ�ο���Ȩ�ļ�ֵΪ7
3.���Ƶļ�ֵ���壺���ƵĻ�����ֵ
4.���Ƶļ�ֵ���壺������Ϊ�����뵥�Ƽ�ֵ��ȣ������Ա����ƴ����������ֵΪ���ƵĻ�����ֵ
5.���Ƶļ�ֵ���壺
  ��������     ���ƵĻ�����ֵ
  ����һ��     ������Ϊͨ������ȥ���Ƽ�ֵһ��������ֵ�����ֵΪ���ƵĻ�����ֵ
  ��������     ������Ϊͨ������ȥ���Ƽ�ֵһ��������ֵ�����ֵΪ���ƵĻ�����ֵ
6.���Ƶļ�ֵ���壺
  ը����       ������Ϊը��������һ�ο���Ȩ����ը�����ܵĸ��ʼ�С�������޸���ֵ���Ǹ�������ֵ+7
  �Ĵ�������   ������Ϊ�Ĵ����������뱻�ܵĸ��ʼ�С�������޸���ֵ�����ֵΪ�Ǹ�������ֵ/2����ֵ���Ϊ6С��һ���ִ�7)
  �Ĵ����ԣ�   ������Ϊ�Ĵ����Թ����뱻�ܵĸ��ʼ�С�������޸���ֵ�����ֵΪ�Ǹ�������ֵ/2����ֵ���Ϊ6С��һ���ִ�7)
7.��ը�ļ�ֵ���壺��֪ը2��ֵΪ15-3+7=19�֣�����ը��ֵΪ20�֡�
8.˳�ӵļ�ֵ���壺
  ��˳��       ������Ϊ��˳�ļ�ֵ����������Ƶĵ����ֵ����2������˳�ӣ���˳�ӵ�Ȩֵ��������1
  ˫˳��       ������Ϊ˫˳�ļ�ֵ����������Ƶĵ����ֵ����2������˳�ӣ���˳�ӵ�Ȩֵ��������1
  �ɻ�������   ���ڷɻ����͹����뱻�ܵĸ��ʼ�С�������޸���ֵ�����ֵΪ�Ǹ�������ֵ/2����ֵ���Ϊ6С��һ���ִ�7)
  �ɻ���˫�᣺ ���ڷɻ����͹����뱻�ܵĸ��ʼ�С�������޸���ֵ�����ֵΪ�Ǹ�������ֵ/2����ֵ���Ϊ6С��һ���ִ�7)
  �ɻ������᣺ ���ڷɻ����͹����뱻�ܵĸ��ʼ�С�������޸���ֵ�����ֵΪ�Ǹ�������ֵ/2����ֵ���Ϊ6С��һ���ִ�7)

9.������ֵ�ֲ��������ݶ���   <10���з֣�10-14��һ�֣�15-19�����֣�20���Ͻ����֣�δ���ã�
*/
int CardTypeValue(int num,int minCard)//����������������Сֵ
{
	int card = minCard + 3;//���Ƶ���ת��Ϊ����ֵ,�Ա�Ʒ�
	if (0 == num)//0����
		return 0;
	else if (102 == num)//1���
		return 20;
	else if (204 == num)//2ը��
		return card - 3 + 7;
	else if (301 == num)//3����
		return card - 10;
	else if (402 == num)//4����
		return card - 10;
	else if (503 == num)//5����
		return card - 10;
	else if (604 == num)//6��������
		return card - 10;
	else if (605 == num)//6��������
		return card - 10;
	else if (num > 700 && num < 800)//7��˳
		return (card +num%100-1) - 10 + 1;
	else if (num > 800 && num < 900)//8˫˳
		return (card + (num % 100)/2 - 1) - 10 + 1;
	else if (num > 900 && num < 1000)//9��˳
		return ((card + (num % 100) / 3 - 1) - 3+1) / 2;
	else if (num > 1000 && num < 1100)//10��˳���������ɻ���
	{
		if ((num % 100) % 4 == 0)//��˳��������
			return ((card + (num % 100) / 4 - 1) - 3 + 1) / 2;//  �Ǹ�/2
		else if ((num % 100) % 5 == 0)//��˳������
			return ((card + (num % 100) / 5 - 1) - 3 + 1) / 2;

		else return  0;          //-1�Ƿ�����
	}
	else if (1106 == num)//11�Ĵ�����
		return (card - 3) / 2;
	else if (1108 == num)//11�Ĵ�����
		return (card - 3) / 2;
	else return  0;          //-1�Ƿ�����
}

/*
���������������������У�ֵΪ�Ʊ�ţ��ҳ���Ӧ����
���������顢���������顢���ͱ�š�������С����������1������2������3������4��
����ֵΪ�Ƶ���

��û���ҵ���Ӧ���ƶ��᷵�أ����Ż���
*/
void FindCardOnHandCard(int handCard[], int save[], int CardTypeCout, int minCard,int take1,int take2,int take3,int take4 )
{
	for (int i = 0; i < 21; i++)//save�����ʼ��
		save[i] = -1;

	if (0 == CardTypeCout)//0����
		return;
	else if (102 == CardTypeCout)//1���
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
	//2ը��
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
	//3����
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
	//4����
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
	//5����
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
	//6����һ��
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
	//6����һ��
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
	//7��˳
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
	//8˫˳
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
	//9��˳
	else if (CardTypeCout > 900 && CardTypeCout < 1000)
	{
		int n = 0;//��¼λ��
		for (int i = minCard; i <= ((CardTypeCout % 100) / 3 + minCard - 1); i++)
		{
			int m = 0;
			for (int j = 0; handCard[j] > -1; j++)
			{
				if (m >= 3) break;//ͬһ�����ƣ�������
				if (handCard[j] / 4 == i)
				{
					save[n++] = handCard[j];
					m++;
				}
			}
		}
		return;
	}
	//10��˳���������ɻ���
	else if (CardTypeCout > 1000 && CardTypeCout < 1100)
	{
		//��˳��������
		if ((CardTypeCout % 100) % 4 == 0)
		{
			int n = 0,lian= (CardTypeCout % 100) / 4;//��¼λ�á������ɻ�
			for (int i = minCard; i <= (lian + minCard - 1); i++)
			{
				int m = 0;
				for (int j = 0; handCard[j] > -1; j++)
				{
					if (m >= 3) break;//ͬһ�����ƣ�������
					if (handCard[j] / 4 == i)
					{
						save[n++] = handCard[j];
						m++;
					}
				}
			}
			for(int i=0;handCard[i]>-1;i++)//һ��
				if (handCard[i] / 4 == take1)
				{
					save[n++] = handCard[i];
					break;
				}
			for (int i = 0; handCard[i] > -1; i++)//����
				if (handCard[i] / 4 == take2)
				{
					save[n++] = handCard[i];
					break;
				}
			if (lian >= 3)//�����ɻ�
			{
				for (int i = 0; handCard[i] > -1; i++)
					if (handCard[i] / 4 == take3)
					{
						save[n++] = handCard[i];
						break;
					}
				if (lian >= 4)//�����ɻ�
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
		else if ((CardTypeCout % 100) % 5 == 0)//��˳������
		{
			int n = 0, lian = (CardTypeCout % 100) / 5;//��¼λ�á������ɻ�
			for (int i = minCard; i <= (lian + minCard - 1); i++)
			{
				int m = 0;
				for (int j = 0; handCard[j] > -1; j++)
				{
					if (m >= 3) break;//ͬһ�����ƣ�������
					if (handCard[j] / 4 == i)
					{
						save[n++] = handCard[j];
						m++;
					}
				}
			}
			for (int i = 0, m = 0; handCard[i] > -1; i++)//��һ�Ŷ���
			{
				if (m >= 2) break;
				if (handCard[i] / 4 == take1)
				{
					save[n++] = handCard[i];
					m++;
				}
			}
			for (int i = 0, m = 0; handCard[i] > -1; i++)//�ڶ��Ŷ���
			{
				if (m >= 2) break;
				if (handCard[i] / 4 == take2)
				{
					save[n++] = handCard[i];
					m++;
				}
			}
			if (lian >= 3)//�����ɻ�
			{
				for (int i = 0, m = 0; handCard[i] > -1; i++)//�����Ŷ���
				{
					if (m >= 2) break;
					if (handCard[i] / 4 == take3)
					{
						save[n++] = handCard[i];
						m++;
					}
				}
				if (lian >= 4)//�����ɻ�
				{
					for (int i = 0, m = 0; handCard[i] > -1; i++)//�����Ŷ���
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
	//11�Ĵ�����
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
		for(int i=0;handCard[i]>-1;i++)//һ��
			if (handCard[i] / 4 == take1)
			{
				save[n++] = handCard[i];
				break;
			}
		for (int i = 0; handCard[i] > - 1; i++)//����
			if (handCard[i] / 4 == take2)
			{
				save[n++] = handCard[i];
				break;
			}
		return;
	}
	//11�Ĵ�����
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
		for (int i = 0,m=0; handCard[i]> - 1; i++)//һ��
		{
			if (m >= 2) break;
			if (handCard[i] / 4 == take1)
			{
				save[n++] = handCard[i];
				m++;
			}
		}
		for (int i = 0, m = 0; handCard[i]> - 1; i++)//����
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

/*  ��ȡ�Ƶļ�ֵ
ͨ������dp�ķ�ʽ��ȡ���Ƽ�ֵ
�� PutCardWay() ��Ϊ����ݹ����
�������Ƽ�ֵ=����Ƶļ�ֵ + ʣ���Ƶļ�ֵ �� ����������Ҳ���ڼ��㷶Χ��
*/
HandCardValue GetCardValue(HandCard &handCard)
{
	handCard.ClearPutCard();//��ճ������У��ڳ�λ�ñ������ŷ���
	HandCardValue tHandCardvalue;//�ݴ����Ƽ�ֵ
	CardGroup tCardGroup;//�ݴ��������
	if (handCard.sumNum == 0)//��������
	{
		tHandCardvalue.value = 0;
		tHandCardvalue.needPly = 0;
		return tHandCardvalue;
	}
	//�ж��ǲ���ʣһ����
	tCardGroup = JudgeOneHand2(handCard.CardPointNum);
	if (tCardGroup.cardTypeId!=-1 && tCardGroup.cardTypeId/100!=11 )//���Ǵ������� && �����ǲ��Ĵ�������������ը����
	{
		tHandCardvalue.value = tCardGroup.value;
		tHandCardvalue.needPly = 1;
		return tHandCardvalue;
	}

	//��һ����
	/*
	����������/�������ƣ��������ų��Ʒ���
	��ѳ��Ʒ��������ڳ������кͳ�������������
	*/
	PutCardWay(handCard);

	tCardGroup = handCard.PutCardGroup;//�ݴ���ѳ������ͽṹ��������������ֵ��������С������
	int NowPutCard[21];//�ݴ�Ŀǰ��������
	for (int i = 0; i < 21; i++) {
		NowPutCard[i] = handCard.PutCard[i];
	}

	//ɾ��Ҫ������
	for (int i = 0; NowPutCard[i]>-1; i++)
	{
		handCard.CardPointNum[NowPutCard[i] / 4]--;
		handCard.sumNum--;
	}

	HandCardValue tSurCardValue = GetCardValue(handCard);	//ͨ�����ݻ�ȡʣ�����Ƽ�ֵ

	//�ӻ���
	for (int i = 0; NowPutCard[i] > -1; i++)
	{
		handCard.CardPointNum[NowPutCard[i] / 4]++;
		handCard.sumNum++;
	}

	tHandCardvalue.value = tCardGroup.value + tSurCardValue.value;//���Ƽ�ֵ=���Ƽ�ֵ+ʣ���Ƽ�ֵ
	tHandCardvalue.needPly = tSurCardValue.needPly + 1;//����+1��

	return tHandCardvalue;
	
}

//���Ʋ���  //ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���
void PutCardWay(HandCard &handCard)
{
	/*
	//�������Ʋ��ԣ�����������ƣ�
	if (handCard.PutAnyCard == 1 || handCard.PutAnyCard==-1)  //�Լ��ǵ���ʱ��һ��ʼ���Գ�������
	{
		PutCardWayActive(handCard);
	}
	//�������Ʋ���
	else if (handCard.PutAnyCard == 0)
	{
		PutCardWayUnactive(handCard);
	}
	*/
	PutCardWayActive(handCard);
}

/*
�������ƵĲ���   �������ȼ�������Է�Ϊ���ࣺ
��һ����ֱ��һ���Ƴ�ȥ�����ȳ���
�����������Ƴ�ȥ���о��Դ��ƣ��ȳ����Դ��ơ�
��������һ����ʹ�ý������Լ����Ƽ�ֵ��󻯡�
*/
void PutCardWayActive(HandCard &handCard)
{
	handCard.ClearPutCard();//��ճ�������
	HandCardValue tHandCardValue;//�ݴ����Ƽ�ֵ
	HandCardValue bestHandValue;	//�ݴ���ѵļ�ֵ
	CardGroup bestCardGroup;      //�ݴ�����������

	//�� һ ���ж��Ƿ�һ����
	bestCardGroup = JudgeOneHand2(handCard.CardPointNum);//�ݴ�������
	if (bestCardGroup.cardTypeId!=-1 && bestCardGroup.cardTypeId/100 != 11)//���Ǵ������� && ����ը��  ���������ƣ����ñȽϴ�С��
	{
		FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, bestCardGroup.cardTypeId, bestCardGroup.minCard, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
		handCard.PutCardGroup = bestCardGroup;
		handCard.value = bestCardGroup.value;//�������
		return;
	}

	//�� �� �������Ƴ�ȥ���о��Դ��ƣ��ȳ����Դ��ơ�
	/*��ը������ǰ����ֻ������ը��Ϊ�����ڶ��ֵ����ȳ���*/
	if (handCard.CardPointNum[13] > 1)//����ը
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
			handCard.value = tHandCardValue.value + 20;//���Ƽ�ֵ=���Ƽ�ֵ+ʣ���Ƽ�ֵ
			return;
		}
	}

	//�� �� ����һ����ʹ�ý������Լ����Ƽ�ֵ��󻯡�

	bestHandValue.needPly = 20;
	bestHandValue.value = -25;
	bestHandValue.needPly += 1;//������Ϊ�����ƵĻ����ö���һ���ִΣ�����һ�֣�Ȩֵ����7�����ں����ĶԱȲο�


	//���ȴ����������ɻ�����
	for (int i = 0; i < 13; i++)//(û����)
	{
		if (handCard.CardPointNum[i] != 4)//�����ǲ�ը��
		{
			//������һ��
			if (handCard.CardPointNum[i] >= 3)
			{
				handCard.CardPointNum[i] -= 3;
				handCard.sumNum-=3;
				for (int j = 0; j <= 13; j++)
				{
					if (handCard.CardPointNum[j] > 0 && j!=i)//����
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
			//������һ��
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
						//��ֵ�Ƚ�
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
			//���Ĵ��������ݲ����ǲ�ը����
			if (handCard.CardPointNum[i] == 4)
			{
				//�ݲ����ǲ�ը��
			}
			//���Ĵ����ԣ��ݲ����ǲ�ը����
			if (handCard.CardPointNum[i] == 4)
			{
				//�ݲ����ǲ�ը��
			}
			//����������
			if (handCard.CardPointNum[i] >= 3)
			{
				int pro = 0;
				for (int j = i; j<13; j++)//������������
				{
					if (handCard.CardPointNum[j] > 2) pro++;
					else break;
					//�����ɻ�
					if (pro == 2)
					{
						for (int k = i; k <= j; k++) handCard.CardPointNum[k] -= 3;
						handCard.sumNum -= pro*3;
						for (int t1 = 0; t1 <= 12; t1++)//��һ�ŵ��ƣ�ѭ���Ż���
						{
							if (handCard.CardPointNum[t1] > 0 && (t1<i || t1>j) )
							{
								handCard.CardPointNum[t1]--;
								handCard.sumNum--;
								for (int t2 = t1 + 1; t2 <= 13; t2++)//�ڶ��ŵ���
								{
									if (handCard.CardPointNum[t2] > 0 && (t2<i || t2>j) )
									{
										handCard.CardPointNum[t2]--;
										handCard.sumNum--;
										tHandCardValue = GetCardValue(handCard);
										handCard.CardPointNum[t2]++;
										handCard.sumNum++;
										//��ֵ�Ƚ�
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
					//�����ɻ�
					if (pro == 3)
					{
						for (int k = i; k <= j; k++) handCard.CardPointNum[k] -= 3;
						handCard.sumNum -= pro * 3;
						for (int t1 = 0; t1 <= 11; t1++)//��һ�ŵ���(ѭ���Ż�)
						{
							if (handCard.CardPointNum[t1] > 0 && (t1<i || t1>j))
							{
								handCard.CardPointNum[t1]--;
								handCard.sumNum--;
								for (int t2 = t1 + 1; t2 <= 12; t2++)//�ڶ��ŵ���
								{
									if (handCard.CardPointNum[t2] > 0 && (t2<i || t2>j))
									{
										handCard.CardPointNum[t2]--;
										handCard.sumNum--;
										for (int t3 = t2 + 1; t3 <= 13; t3++)//�����ŵ���
										{
											if (handCard.CardPointNum[t3] > 0 && (t3<i || t3>j))
											{
												handCard.CardPointNum[t3]--;
												handCard.sumNum--;
												tHandCardValue = GetCardValue(handCard);
												handCard.CardPointNum[t3]++;
												handCard.sumNum++;
												//��ֵ�Ƚ�
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
					//�����ɻ�
					if (pro == 4)
					{
						for (int k = i; k <= j; k++) handCard.CardPointNum[k] -= 3;
						handCard.sumNum -= pro * 3;
						for (int t1 = 0; t1 <= 10; t1++)//��һ�ŵ���  ��ѭ���Ż���
						{
							if (handCard.CardPointNum[t1] > 0 && (t1<i || t1>j))
							{
								handCard.CardPointNum[t1]--;
								handCard.sumNum--;
								for (int t2 = t1 + 1; t2 <= 11; t2++)//�ڶ��ŵ���
								{
									if (handCard.CardPointNum[t2] > 0 && (t2<i || t2>j))
									{
										handCard.CardPointNum[t2]--;
										handCard.sumNum--;
										for (int t3 = t2 + 1; t3 <= 12; t3++)//�����ŵ���
										{
											if (handCard.CardPointNum[t3] > 0 && (t3<i || t3>j))
											{
												handCard.CardPointNum[t3]--;
												handCard.sumNum--;
												for (int t4 = t3 + 1; t4 <= 13; t4++)//�����ŵ���
												{
													if (handCard.CardPointNum[t4] > 0 && (t4<i || t4>j))
													{
														handCard.CardPointNum[t4]--;
														handCard.sumNum--;
														tHandCardValue = GetCardValue(handCard);
														handCard.CardPointNum[t4]++;
														handCard.sumNum++;
														//��ֵ�Ƚ�
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
			//��������
			if (handCard.CardPointNum[i] >= 3)
			{
				int pro = 0;
				for (int j = i; j < 13; j++)//(��������)
				{
					if (handCard.CardPointNum[j] >= 3) pro++;
					else break;
					//�����ɻ�
					if (pro == 2)
					{
						for (int k = i; k <= j; k++) handCard.CardPointNum[k] -= 3;
						handCard.sumNum -= pro * 3;
						for (int t1 = 0; t1 <= 12; t1++)//��һ�Ŷ���
						{
							if (handCard.CardPointNum[t1] > 1 && (t1<i || t1>j))
							{
								handCard.CardPointNum[t1] -= 2;
								handCard.sumNum -= 2;
								for (int t2 = t1 + 1; t2 <= 13; t2++)//�ڶ��Ŷ���
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
					//�����ɻ�
					if (pro == 3)
					{
						for (int k = i; k <= j; k++) handCard.CardPointNum[k] -= 3;
						handCard.sumNum -= pro * 3;
						for (int t1 = 0; t1 <= 11; t1++)//һ��
						{
							if (handCard.CardPointNum[t1] > 1 && (t1<i || t1>j))
							{
								handCard.CardPointNum[t1] -= 2;
								handCard.sumNum -= 2;
								for (int t2 = t1 + 1; t2 <= 12; t2++)//����
								{
									if (handCard.CardPointNum[t2] > 1 && (t2<i || t2>j))
									{
										handCard.CardPointNum[t2] -= 2;
										handCard.sumNum -= 2;
										for (int t3 = t2 + 1; t3 <= 13; t3++)//�����Ŷ���
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
					//�����ɻ�
					if (pro == 4)
					{
						for (int k = i; k <= j; k++) handCard.CardPointNum[k] -= 3;
						handCard.sumNum -= pro * 3;
						for (int t1 = 0; t1 <= 10; t1++)//��һ�Ŷ���
						{
							if (handCard.CardPointNum[t1] > 1 && (t1<i || t1>j))
							{
								handCard.CardPointNum[t1] -= 2;
								handCard.sumNum -= 2;
								for (int t2 = t1 + 1; t2 <= 11; t2++)//�ڶ��Ŷ���
								{
									if (handCard.CardPointNum[t2] > 1 && (t2<i || t2>j))
									{
										handCard.CardPointNum[t2] -= 2;
										handCard.sumNum -= 2;
										for (int t3 = t2 + 1; t3 <= 12; t3++)//�����Ŷ���
										{
											if (handCard.CardPointNum[t3] > 1 && (t3<i || t3>j))
											{
												handCard.CardPointNum[t3] -= 2;
												handCard.sumNum -= 2;
												for (int t4 = t3 + 1; t4 <= 13; t4++)//�����Ŷ���
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
	//�ж��Ƿ��ж�Ӧ���ƿ��Գ�
	if ((bestCardGroup.cardTypeId / 100) == 6)//����һ
	{
		if (bestCardGroup.cardTypeId % 100 == 4)//������
		{
			//�������У��ҵ���Ӧ�����͵ı�ţ����������������
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, bestCardGroup.cardTypeId, bestCardGroup.minCard, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
			handCard.PutCardGroup = bestCardGroup;
			//�����ֵ
			handCard.value = bestHandValue.value + bestCardGroup.value;
			return;
		}
		else if (bestCardGroup.cardTypeId % 100 == 5)//������
		{
			//�������У��ҵ���Ӧ�����͵ı�ţ����������������
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, bestCardGroup.cardTypeId, bestCardGroup.minCard, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
			handCard.PutCardGroup = bestCardGroup;
			//�����ֵ
			handCard.value = bestHandValue.value + bestCardGroup.value;
			return;
		}
	}
	//�ɻ�
	else if ((bestCardGroup.cardTypeId / 100) == 10)
	{
		if ((bestCardGroup.cardTypeId % 100) % 4 == 0)//��������
		{
			//�������У��ҵ���Ӧ�����͵ı�ţ����������������
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, bestCardGroup.cardTypeId, bestCardGroup.minCard, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
			handCard.PutCardGroup = bestCardGroup;
			//�����ֵ
			handCard.value = bestHandValue.value + bestCardGroup.value;
			return;
		}
		else if((bestCardGroup.cardTypeId % 100) % 5 == 0)//��������
		{
			//�������У��ҵ���Ӧ�����͵ı�ţ����������������
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, bestCardGroup.cardTypeId, bestCardGroup.minCard, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
			handCard.PutCardGroup = bestCardGroup;
			//�����ֵ
			handCard.value = bestHandValue.value + bestCardGroup.value;
			return;
		}
	}

	//��֮����ǰ��ֵ��͵��ƣ����ơ����ơ����ơ���˳��˫˳����˳�������ڲ����ٿ��������ƿ��ܱ����ƴ��������
	for (int i = 0; i <= 13; i++)
	{
		if (handCard.CardPointNum[i] != 0 && handCard.CardPointNum[i] != 4)//���������ƣ��Ȳ�����
		{
			//����
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
			//������
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
			//������
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
			//����˳
			if (handCard.CardPointNum[i] > 0)
			{
				int pro = 0;
				for (int j = i; j < 12; j++)//������2����
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
			//��˫˳
			if (handCard.CardPointNum[i] >= 2)
			{
				int pro = 0;
				for (int j = i; j < 12; j++)//������2����
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
			//����˳
			if (handCard.CardPointNum[i] > 2)
			{
				int pro = 0;
				for (int j = i; j < 12; j++)//������2����
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

			//��Ϊ�������Ǳ�����������һ��i�Ƶģ����Գ��Ʋ�������ѭ���ڽ��У�Ҳ����˵��ֻҪ�㲻��ը3������������3���ڴ���3ʱһ����return  �;��Բ������ߵ�4��
			//����
			if (bestCardGroup.cardTypeId / 100 == 3)//����
			{
				//�������У��ҵ���Ӧ�����͵ı�ţ����������������
				FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, bestCardGroup.cardTypeId, bestCardGroup.minCard, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
				handCard.PutCardGroup = bestCardGroup;
				//�����ֵ
				handCard.value = bestHandValue.value + bestCardGroup.value;
				return;
			}
			else if (bestCardGroup.cardTypeId / 100 == 4)//����
			{
				//�������У��ҵ���Ӧ�����͵ı�ţ����������������
				FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, bestCardGroup.cardTypeId, bestCardGroup.minCard, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
				handCard.PutCardGroup = bestCardGroup;
				//�����ֵ
				handCard.value = bestHandValue.value + bestCardGroup.value;
				return;
			}
			else if (bestCardGroup.cardTypeId / 100 == 5)//����
			{
				//�������У��ҵ���Ӧ�����͵ı�ţ����������������
				FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, bestCardGroup.cardTypeId, bestCardGroup.minCard, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
				handCard.PutCardGroup = bestCardGroup;
				//�����ֵ
				handCard.value = bestHandValue.value + bestCardGroup.value;
				return;
			}
			else if (bestCardGroup.cardTypeId / 100 == 7)//��˳
			{
				//�������У��ҵ���Ӧ�����͵ı�ţ����������������
				FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, bestCardGroup.cardTypeId, bestCardGroup.minCard, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
				handCard.PutCardGroup = bestCardGroup;
				//�����ֵ
				handCard.value = bestHandValue.value + bestCardGroup.value;
				return;
			}
			else if (bestCardGroup.cardTypeId / 100 == 8)//˫˳
			{
				//�������У��ҵ���Ӧ�����͵ı�ţ����������������
				FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, bestCardGroup.cardTypeId, bestCardGroup.minCard, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
				handCard.PutCardGroup = bestCardGroup;
				//�����ֵ
				handCard.value = bestHandValue.value + bestCardGroup.value;
				return;
			}
		}

	}
	

	//���û��3-2�ķ�ը�ƣ��򿴿���û�е���
	if (handCard.CardPointNum[13] == 1)
	{
		handCard.CardPointNum[13]--;
		handCard.sumNum--;
		tHandCardValue = GetCardValue(handCard);
		handCard.CardPointNum[13]++;
		handCard.sumNum++;
		handCard.value = tHandCardValue.value + CardTypeValue(301, 13);

		//�����ֵ���ټ�¼�������飨���ⱻ�����ֵ�������  ���������¼ ��2020.1.3��
		//�������У��ҵ���Ӧ�����͵ı�ţ����������������
		FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, 301, 13, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
		bestCardGroup.cardTypeId = 301;
		bestCardGroup.minCard = 13;
		bestCardGroup.value = CardTypeValue(301, 13);
		handCard.PutCardGroup = bestCardGroup;
		return;
	}
	//����Ҳû�У���ը��
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

			//�����ֵ���ټ�¼�������飨���ⱻ�����ֵ�������  ���������¼ ��2020.1.3��
			//�������У��ҵ���Ӧ�����͵ı�ţ����������������
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, 204, i, bestCardGroup.take1, bestCardGroup.take2, bestCardGroup.take3, bestCardGroup.take4);
			bestCardGroup.cardTypeId = 204;
			bestCardGroup.value = CardTypeValue(204, i);
			bestCardGroup.minCard = i;
			handCard.PutCardGroup = bestCardGroup;

			return;
		}
	}
	//�쳣����
	handCard.PutCardGroup.cardTypeId = -1;
	handCard.PutCardGroup.minCard =  -1;
	handCard.PutCardGroup.value = -1;
	return;
}

/*
2.0�汾����  ���ݳ������ƾ�����ǰԤ��������ơ�����������
��ֱ�Ӵ�����ơ�����ͬ������ѹ�ơ�����ը����ըѹ�ơ�����������
*/
void PutCardWayUnactive(HandCard &handCard)//���ƺ���
{
	//��ճ�������
	handCard.ClearPutCard();
	HandCardValue tHandCardValue;//�ݴ����Ƽ�ֵ
	CardGroup tCardGroup;//�ݴ�������
	HandCardValue bestHandCardValue;//������Ƽ�ֵ

	//======================================�����⴦��========================================

	//���ƻ����Ǵ���  ������  (��ǰ��������Ϊ��������Ҳ���ڴ�������)
	if (handCard.tableTypeCount == 0 || handCard.tableTypeCount == -1)
	{
		handCard.PutCardGroup.cardTypeId = 0;
		handCard.PutCardGroup.minCard = -1;
		handCard.PutCardGroup.value = 0;

		return;
	}

	//��ը������ǰ����ֻ������ը��Ϊ�����ڶ��ֵ����ȳ����߼�
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

	//======================================��ֱ�Ӵ�����ơ�====================================
	tCardGroup = JudgeOneHand2(handCard.CardPointNum);
	if (tCardGroup.cardTypeId != -1)//�����һ����
	{
		if ((tCardGroup.cardTypeId == handCard.tableTypeCount && tCardGroup.minCard > handCard.tableMainPoint) || tCardGroup.cardTypeId / 100 == 1 )
		{ //ͬ�֣������������������� && �ȶԷ��� || ���
			//�ҳ���������
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, tCardGroup.cardTypeId, tCardGroup.minCard, tCardGroup.take1, tCardGroup.take2, tCardGroup.take3, tCardGroup.take4);
			//�����������
			handCard.PutCardGroup = tCardGroup;

			//handCard.value = tCardGroup.value;
			return;
		}
		else if (tCardGroup.cardTypeId / 100 == 2 && handCard.tableTypeCount/100!=1 && handCard.tableTypeCount / 100 != 2 )//�Է�����ը��������ը������ը����ֱ��ը
		{
			//�ҳ���������
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, tCardGroup.cardTypeId, tCardGroup.minCard, tCardGroup.take1, tCardGroup.take2, tCardGroup.take3, tCardGroup.take4);
			//�����������
			handCard.PutCardGroup = tCardGroup;

			//handCard.value = tCardGroup.value;
			return;
		}
	}
	//======================================��ͬ������ѹ�ơ�====================================

	bestHandCardValue = GetCardValue(handCard);
	bestHandCardValue.needPly += 1;//������Ϊ�����ƵĻ����ö���һ���ִΣ�����һ�֣�Ȩֵ����7�����ں����ĶԱȲο���

	int bestMinCard = -1;//�ݴ�����ƺ�
	bool put = false;//���Ʊ�־
	int take1 = -1, take2 = -1, take3 = -1, take4 = -1;//����

	//----------------------------���-----------------------
	if (handCard.tableTypeCount / 100 == 1)
	{
		//����
		handCard.PutCardGroup.cardTypeId = 0;
		handCard.PutCardGroup.minCard = -1;
		handCard.PutCardGroup.value = 0;

		//handCard.value = bestHandCardValue.value;//���Ƽ�ֵ����Ŀǰ���Ƶļ�ֵ
		return;
	}
	//----------------------------ը��---------------------
	else if (handCard.tableTypeCount / 100 == 2)
	{
		//�����ը����������ֱ��ը�������ǲ�ֺ������Ϊ����
		for (int i = handCard.tableMainPoint + 1; i < 13; i++)//��������
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
	//-----------------------------����--------------------
	else if (handCard.tableTypeCount / 100 == 3)
	{
		//��ͬ������ѹ�ơ�

		if (handCard.tableMainPoint == 13)
		{
			for(int hh=0;handCard.onHandCard[hh]>=0;hh++)/////******************������ѳ�С�����Լ�ק�Ŵ�������
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
	//---------------------------����------------------------
	else if (handCard.tableTypeCount / 100 == 4)
	{
		//��ͬ������ѹ�ơ�
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
	//--------------------------����------------------------
	else if (handCard.tableTypeCount / 100 == 5)
	{
		//��ͬ������ѹ�ơ�
		for (int i = handCard.tableMainPoint + 1; i < 13; i++)//�����ܰ�����
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
	//------------------------- ����һ ------------------------
	else if (handCard.tableTypeCount / 100 == 6)
	{
		if (handCard.tableTypeCount % 100 == 4)//-----------------------------����һ��
		{
			//��ͬ������ѹ�ơ�
			for (int i = handCard.tableMainPoint + 1; i < 13; i++)//��������
			{
				if (handCard.CardPointNum[i] == 4) continue;//��ֹ��ը��10.2�޸�

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
		else if (handCard.tableTypeCount % 100 == 5)//-----------------------��������
		{
			//��ͬ������ѹ�ơ�
			for (int i = handCard.tableMainPoint + 1; i < 13; i++)
			{
				if (handCard.CardPointNum[i] > 2)
				{
					handCard.CardPointNum[i] -= 3;
					handCard.sumNum -= 3;
					for (int j = 0; j <= 13; j++)//��һ�Ŷ���
					{
						if (handCard.CardPointNum[j] > 1 && j != i)//����ͬ��
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
	//-------------------------��˳--------------------------
	else if (handCard.tableTypeCount / 100 == 7)
	{
		//��ͬ������ѹ�ơ�
		int pro = 0, start = 0, end = 0, leng = handCard.tableTypeCount % 100;//һֱ��������
		for (int i = handCard.tableMainPoint + 1; i < 12; i++)//������2����
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
					bestMinCard = start;//����Ŀǰ���������ϵ���С����
					put = true;
				}
			}
		}
		if (put)
		{
			handCard.PutCardGroup.cardTypeId = 700 + leng;//���������ƣ����������̶� leng��
			handCard.PutCardGroup.minCard = bestMinCard;
			handCard.PutCardGroup.value = bestHandCardValue.value;
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, handCard.PutCardGroup.cardTypeId, handCard.PutCardGroup.minCard, 0, 0, 0, 0);
			
			return;
		}
	}
	//-------------------------˫˳-----------------------------
	else if (handCard.tableTypeCount / 100 == 8)
	{
		//��ͬ������ѹ�ơ�
		int pro = 0, start = 0, end = 0, leng = (handCard.tableTypeCount % 100) / 2;//һֱ��������
		for (int i = handCard.tableMainPoint + 1; i < 12; i++)//������2����
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
			handCard.PutCardGroup.cardTypeId = 800 + leng * 2;//���������ƣ����������̶� leng��
			handCard.PutCardGroup.minCard = bestMinCard;
			handCard.PutCardGroup.value = bestHandCardValue.value;
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, handCard.PutCardGroup.cardTypeId, handCard.PutCardGroup.minCard, 0, 0, 0, 0);
			return;
		}
	}
	//-------------------------��˳----------------------------
	else if (handCard.tableTypeCount / 100 == 9)
	{
		//��ͬ������ѹ�ơ�
		int pro = 0, start = 0, end = 0, leng = (handCard.tableTypeCount % 100) / 3;//һֱ��������
		for (int i = handCard.tableMainPoint + 1; i < 12; i++)//������2����
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
			handCard.PutCardGroup.cardTypeId = 900 + leng * 3;//���������ƣ����������̶� leng��
			handCard.PutCardGroup.minCard = bestMinCard;
			handCard.PutCardGroup.value = bestHandCardValue.value;
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, handCard.PutCardGroup.cardTypeId, handCard.PutCardGroup.minCard, 0, 0, 0, 0);
			return;
		}
	}
	//--------------------------��˳������---------------------
	else if (handCard.tableTypeCount / 100 == 10)
	{
		if ((handCard.tableTypeCount % 100) / 4 == 0)//��������
		{
			//��ͬ������ѹ�ơ�
			int pro = 0, start = 0, end = 0, leng = (handCard.tableTypeCount % 100) / 4;//һֱ��������
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
					if (leng == 2)//�����ɻ�
					{
						for (int j = 0; j <= 12; j++)//��һ�ŵ��ƣ�ѭ���Ż���
						{
							if (handCard.CardPointNum[j] > 0 && (j<start || j>end) )
							{
								handCard.CardPointNum[j] -= 1;
								handCard.sumNum -= 1;
								for (int k = j+1; k <= 13; k++)//�ڶ��ŵ���
								{
									if (handCard.CardPointNum[k] > 0 && (k<start || k>end))
									{
										handCard.CardPointNum[k] -= 1;
										handCard.sumNum -= 1;
										tHandCardValue = GetCardValue(handCard);
										handCard.CardPointNum[k] += 1;
										handCard.sumNum += 1;
										//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
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
					else if (leng == 3)//�����ɻ�
					{
						for (int j = 0; j <= 11; j++)//��һ�ŵ���
						{
							if (handCard.CardPointNum[j] > 0 && (j<start || j>end))
							{
								handCard.CardPointNum[j] -= 1;
								handCard.sumNum -= 1;
								for (int k = j+1; k <= 12; k++)//�ڶ��ŵ���
								{
									if (handCard.CardPointNum[k] > 0 && (k<start || k>end))
									{
										handCard.CardPointNum[k] -= 1;
										handCard.sumNum -= 1;
										for (int l = k+1; l <= 13; l++)//�����ŵ���
										{
											if (handCard.CardPointNum[l] > 0 && (l<start || l>end))
											{
												handCard.CardPointNum[l] -= 1;
												handCard.sumNum -= 1;
												tHandCardValue = GetCardValue(handCard);
												handCard.sumNum += 1;
												handCard.CardPointNum[l] += 1;
												//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
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
					else if (leng == 4)//�����ɻ�
					{
						for (int j = 0; j <= 10; j++)//��һ�ŵ���
						{
							if (handCard.CardPointNum[j] > 0 && (j<start || j>end))
							{
								handCard.CardPointNum[j] -= 1;
								handCard.sumNum -= 1;
								for (int k = j+1; k <= 11; k++)//�ڶ��ŵ���
								{
									if (handCard.CardPointNum[k] > 0 && (k<start || k>end))
									{
										handCard.CardPointNum[k] -= 1;
										handCard.sumNum -= 1;
										for (int l = k+1; l <= 12; l++)//�����ŵ���
										{
											if (handCard.CardPointNum[l] > 0 && (l<start || l>end))
											{
												handCard.CardPointNum[l]--;
												handCard.sumNum -= 1;
												for (int m = l+1; m <= 13; m++)//�����ŵ���
												{
													if (handCard.CardPointNum[m] > 0 && (m<start || m>end))
													{
														handCard.CardPointNum[m] -= 1;
														handCard.sumNum -= 1;
														tHandCardValue = GetCardValue(handCard);
														handCard.sumNum += 1;
														handCard.CardPointNum[m] += 1;
														//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
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
				handCard.PutCardGroup.cardTypeId = 1000 + leng * 4;//���������ƣ����������̶� leng��
				handCard.PutCardGroup.minCard = bestMinCard;
				handCard.PutCardGroup.value = bestHandCardValue.value;
				FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, handCard.PutCardGroup.cardTypeId, handCard.PutCardGroup.minCard, take1, take2, take3, take4);
				return;
			}
		}
		else if ((handCard.tableTypeCount % 100) / 5 == 0)//-------------------------------��������
		{
			//��ͬ������ѹ�ơ�
			int pro = 0, start = 0, end = 0, leng = (handCard.tableTypeCount % 100) / 5;//һֱ��������
			for (int i = handCard.tableMainPoint + 1; i < 12; i++)//�������2����
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
					if (leng == 2)//�����ɻ�
					{
						for (int j = 0; j <= 12; j++)//��һ�Ŷ���
						{
							if (handCard.CardPointNum[j] > 1 && (j<start || j>end) )
							{
								handCard.CardPointNum[j] -= 2;
								handCard.sumNum -= 2;
								for (int k = j+1; k <= 13; k++)//�ڶ��Ŷ���
								{
									if (handCard.CardPointNum[k] > 1 && (k<start || k>end))
									{
										handCard.CardPointNum[k] -= 2;
										handCard.sumNum -= 2;
										tHandCardValue = GetCardValue(handCard);
										handCard.CardPointNum[k] += 2;
										handCard.sumNum += 2;
										//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
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
					else if (leng == 3)//�����ɻ�
					{
						for (int j = 0; j <= 11; j++)//��һ�Ŷ���
						{
							if (handCard.CardPointNum[j] > 1 && (j<start || j>end))
							{
								handCard.CardPointNum[j] -= 2;
								handCard.sumNum -= 2;
								for (int k = j+1; k <= 12; k++)//�ڶ��Ŷ���
								{
									if (handCard.CardPointNum[k] > 1 && (k<start || k>end))
									{
										handCard.CardPointNum[k] -= 2;
										handCard.sumNum -= 2;
										for (int l = k+1; l <= 13; l++)//�����Ŷ���
										{
											if (handCard.CardPointNum[l] > 1 && (l<start || l>end))
											{
												handCard.CardPointNum[l] -= 2;
												handCard.sumNum -= 2;
												tHandCardValue = GetCardValue(handCard);
												handCard.sumNum += 2;
												handCard.CardPointNum[l] += 2;
												//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
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
					else if (leng == 4)//�����ɻ�
					{
						for (int j = 0; j <= 10; j++)//��һ�Ŷ���
						{
							if (handCard.CardPointNum[j] > 1 && (j<start || j>end))
							{
								handCard.CardPointNum[j] -= 2;
								handCard.sumNum -= 2;
								for (int k = j+1; k <= 11; k++)//�ڶ��Ŷ���
								{
									if (handCard.CardPointNum[k] > 1 && (k<start || k>end))
									{
										handCard.CardPointNum[k] -= 2;
										handCard.sumNum -= 2;
										for (int l = k+1; l <= 12; l++)//�����Ŷ���
										{
											if (handCard.CardPointNum[l] > 1 && (l<start || l>end))
											{
												handCard.CardPointNum[l] -= 2;
												handCard.sumNum -= 2;
												for (int m = l+1; m <= 13; m++)//�����Ŷ���
												{
													if (handCard.CardPointNum[m] > 1 && (m<start || m>end))
													{
														handCard.CardPointNum[m] -= 2;
														handCard.sumNum -= 2;
														tHandCardValue = GetCardValue(handCard);
														handCard.sumNum += 2;
														handCard.CardPointNum[m] += 2;
														//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
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
				handCard.PutCardGroup.cardTypeId = 1000 + leng * 5;//���������ƣ����������̶� leng��
				handCard.PutCardGroup.minCard = bestMinCard;
				handCard.PutCardGroup.value = bestHandCardValue.value;
				FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, handCard.PutCardGroup.cardTypeId, handCard.PutCardGroup.minCard, take1, take2, take3, take4);
				return;
			}
		}
	}
	//------------------------�Ĵ���---------------------
	else if (handCard.tableTypeCount / 100 == 11)
	{
		if (handCard.tableTypeCount % 100 == 6)//�Ĵ�����
		{
			//��ͬ������ѹ�ơ�
			for (int i = 0; i < 13; i++)//��������
			{
				if (handCard.CardPointNum[i] == 4)
				{
					handCard.CardPointNum[i] -= 4;
					handCard.sumNum -= 4;
					for (int j = 0; j <= 12; j++)//ѭ���Ż�
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
		else if (handCard.tableTypeCount % 100 == 8)//�Ĵ�����
		{
			//��ͬ������ѹ�ơ�
			/*�����Զ�������������ը��ը���Ĵ������ը����˵�����������ƣ���������14Ȩֵ�ļ�ֵ
		����ǰ���Ƽ�ֵ����14������Ϊ������ը��ը�����ؿ����Ĵ��������棬������ô���ԡ�*/
			if (bestHandCardValue.value > 14)
			{
				for (int i = 0; i < 13; i++)//��������
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
			//Ȩֵ�Ƚ�С�������Ҳը
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


	//======================================��ը����ըѹ�ơ�====================================

	//ը����ըѹ��
	for (int i = 0; i < 13; i++)//ը��
	{
		if (handCard.CardPointNum[i] == 4)
		{
			handCard.CardPointNum[i] -= 4;
			handCard.sumNum -= 4;
			tHandCardValue = GetCardValue(handCard);
			handCard.sumNum += 4;
			handCard.CardPointNum[i] += 4;
			//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ� ��ô������ը�������
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
	if (handCard.CardPointNum[13] > 1)	//��ը
	{
		//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ� ��ô������ը�������
		if (bestHandCardValue.value > 20)
		{
			FindCardOnHandCard(handCard.onHandCard, handCard.PutCard, 102, 13, 0, 0, 0, 0);
			handCard.PutCardGroup.cardTypeId = 102;
			handCard.PutCardGroup.minCard = 13;
			handCard.PutCardGroup.value = CardTypeValue(102, 13);
			return;
		}
	}

	//======================================��������============================================

	//�ܲ���
	handCard.PutCardGroup.cardTypeId = 0;
	handCard.PutCardGroup.minCard = -1;
	handCard.PutCardGroup.value = 0;
	return;
	
}