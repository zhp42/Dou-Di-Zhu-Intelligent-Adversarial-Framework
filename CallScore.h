#pragma once
/*
  叫分策略函数（头文件）
  暂定的叫分策略
  1、根据每张牌的面值加分
	3、4、5、6、7、8、9、10、J、Q、K、A、2、小王、大王  分别加
	1、2、3、4、5、6、7、8、9、10、11、12、13、14、14  分
 2、牌型加分
	火箭加18分，炸弹加15分
 3、同点数牌（梅花4和方形4）加2分
*/
#include<iostream>

/*
叫分分值界限（暂定）

3分牌：
	大王、小王、3333（炸弹）、JJJ4、10 10 10 5、AAA    总分值 178
		三分界暂定 170
2分牌：
	3333（炸弹）、AA、22、9994、789 10 JK    总分值 141
		2分界限暂定： 140	
1分牌：AA、22、JJJ3、45678、4567  总分值120
		1分界限暂定： 120

*/

int callScore(int onHand[])//叫牌函数
{
	int sum = 0,Num=0;
	for (int i = 0; onHand[i] >= 0; i++)
	{
		Num++;
		//根据每张牌的面值加分
		sum += (onHand[i] / 4) + 1;
		//同点牌加2分
		if (i > 0 && onHand[i] / 4 == onHand[i - 1] / 4)
			sum += 2;
		//炸弹加15分
		if (i > 2 && onHand[i] / 4 == onHand[i - 1] / 4
			&& onHand[i] / 4 == onHand[i - 2] / 4 && onHand[i] / 4 == onHand[i - 3] / 4)
			sum += 15;
	}
	if (onHand[Num - 1] == 53 &&onHand[Num - 2] == 52)
		sum += 18;
	//叫分
	if (sum >= 170) return 3;
	else if (sum <= 140 && sum > 170) return 2;
	else if (sum >= 120) return 1;
	else return 0;
}

