//                               软件授权协议
//1、	杭州三汇信息工程有限公司（以下简称本公司）拥有"本软件及所有附属产品、文件和相关文档"（以下简称本产品）的完全版权。任何单位和个人在使用前须获得本公司的授权。
//2、	本公司授权符合以下全部条件的单位和个人免费使用本产品：
//A、	本产品与通过合法销售渠道购买的本公司硬件产品配合使用时；
//B、	不私自向第三方传播本产品和本产品的任何一部分。
//3、	除符合第2条以外的其他单位和个人需要使用本产品时，必须获得本公司的书面授权。
//4、	获得授权的单位和个人不得转让其获得的授权。
//5、	使用本产品，即表明完全理解本协议的所有条款并全部接受。

/************************************
  REVISION LOG ENTRY
  Revision By: ...
  Revised on 02-7-1 16:55:52
  Comments: ...
 ************************************/

int		WINAPI	GetTotalPciBoard(int * pTotalBoards);
int		WINAPI	GetPciBoardModel(int nBId, LPSTR lpBoardModel);
int		WINAPI	GetPciBoardSerailNo(int nBId, DWORD *pSeraiNo);