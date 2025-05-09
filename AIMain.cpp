
#define kPlayerName "Aurora_DDZ"
#define kPlaMax 500  //500个出牌策略
#include"DDZMain2.h"




int	main()
{
	struct Ddz tDdz, * pDdz = &tDdz;
	//_resetstkoflw; //堆栈报错去除
	InitTurn(pDdz);			//初始化数据
	while (pDdz->iStatus != 0)
	{
		InputMsg(pDdz);			//输入信息
		AnalyzeMsg(pDdz);		//分析处理信息
		OutputMsg(pDdz);		//输出信息
		CalOthers(pDdz);		//计算其它数据
		
	}
	return 0;
}