
#define kPlayerName "Aurora_DDZ"
#define kPlaMax 500  //500�����Ʋ���
#include"DDZMain2.h"




int	main()
{
	struct Ddz tDdz, * pDdz = &tDdz;
	//_resetstkoflw; //��ջ����ȥ��
	InitTurn(pDdz);			//��ʼ������
	while (pDdz->iStatus != 0)
	{
		InputMsg(pDdz);			//������Ϣ
		AnalyzeMsg(pDdz);		//����������Ϣ
		OutputMsg(pDdz);		//�����Ϣ
		CalOthers(pDdz);		//������������
		
	}
	return 0;
}