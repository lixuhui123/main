 

#include<AT89x51.H>

	//HL-1小车驱动接线定义
  #define Left_moto_go      {P1_2=1,P1_3=0;}    //左边电机向前走
	#define Left_moto_back    {P1_2=0,P1_3=1;}    //左边电机向后转
	#define Left_moto_Stop    {P1_2=0,P1_3=0;}    //左边电机停转                     
	#define Right_moto_go     {P1_6=0,P1_7=1;}	//右边电机向前走
	#define Right_moto_back   {P1_6=1,P1_7=0;}	//右边电机向后走
	#define Right_moto_Stop   {P1_6=0,P1_7=0;}	//右边电机停转   

	#define left     'C'
    #define right    'D'
	#define up       'A'
    #define down     'B'
	#define stop     'F'

	char code str[] =  "收到指令，向前!\n";
	char code str1[] = "收到指令，向后!\n";
	char code str2[] = "收到指令，向左!\n";
	char code str3[] = "收到指令，向右!\n";
	char code str4[] = "收到指令，停止!\n";

	bit  flag_REC=0; 
	bit  flag    =0;  
	

	unsigned char  i=0;
	unsigned char  dat=0;
    unsigned char  buff[5]=0; //接收缓冲字节


   
/************************************************************************/	
//延时函数	
   void delay(unsigned int k)
{    
     unsigned int x,y;
	 for(x=0;x<k;x++) 
	   for(y=0;y<2000;y++);
}

/************************************************************************/
//字符串发送函数
	  void send_str( )
                   // 传送字串
    {
	    unsigned char i = 0;
	    while(str[i] != '\0')
	   {
		SBUF = str[i];
		while(!TI);				// 等特数据传送
		TI = 0;					// 清除数据传送标志
		i++;					// 下一个字符
	   }	
    }
	
		  void send_str1( )
                   // 传送字串
    {
	    unsigned char i = 0;
	    while(str1[i] != '\0')
	   {
		SBUF = str1[i];
		while(!TI);				// 等特数据传送
		TI = 0;					// 清除数据传送标志
		i++;					// 下一个字符
	   }	
    }	

			  void send_str2( )
                   // 传送字串
    {
	    unsigned char i = 0;
	    while(str2[i] != '\0')
	   {
		SBUF = str2[i];
		while(!TI);				// 等特数据传送
		TI = 0;					// 清除数据传送标志
		i++;					// 下一个字符
	   }	
    }	
	    	
			  void send_str3()
                   // 传送字串
    {
	    unsigned char i = 0;
	    while(str3[i] != '\0')
	   {
		SBUF = str3[i];
		while(!TI);				// 等特数据传送
		TI = 0;					// 清除数据传送标志
		i++;					// 下一个字符
	   }	
    }	

	      void send_str4()
                   // 传送字串
    {
	    unsigned char i = 0;
	    while(str4[i] != '\0')
	   {
		SBUF = str4[i];
		while(!TI);				// 等特数据传送
		TI = 0;					// 清除数据传送标志
		i++;					// 下一个字符
	   }	
    }	
	    	
	    	
/************************************************************************/
//前速前进
     void  run(void)
{
    
	 Left_moto_go ;   //左电机往前走
	 Right_moto_go ;  //右电机往前走
}

//前速后退
     void  backrun(void)
{
    
	 Left_moto_back ;   //左电机往前走
	 Right_moto_back ;  //右电机往前走
}

//左转
     void  leftrun(void)
{
    
	 Left_moto_back ;   //左电机往前走
	 Right_moto_go ;  //右电机往前走
}

//右转
     void  rightrun(void)
{
    
	 Left_moto_go ;   //左电机往前走
	 Right_moto_back ;  //右电机往前走
}
//STOP
     void  stoprun(void)
{
    
	 Left_moto_Stop ;   //左电机往前走
	 Right_moto_Stop ;  //右电机往前走
}
/************************************************************************/
void sint() interrupt 4	  //中断接收3个字节
{ 
 
    if(RI)	                 //是否接收中断
    {
       RI=0;
       dat=SBUF;
       if(dat=='O'&&(i==0)) //接收数据第一帧
         {
            buff[i]=dat;
            flag=1;        //开始接收数据
         }
       else
      if(flag==1)
     {
      i++;
      buff[i]=dat;
      if(i>=2)
      {i=0;flag=0;flag_REC=1 ;}  // 停止接收
     }
	 }
}
/*********************************************************************/		 
/*--主函数--*/
	void main(void)
{
	TMOD=0x20;  
    TH1=0xFd;  		   //11.0592M晶振，9600波特率
    TL1=0xFd;
    SCON=0x50;  
    PCON=0x00; 
    TR1=1;
	ES=1;   
    EA=1;   
  	
	while(1)							/*无限循环*/
	{ 
	  if(flag_REC==1)				    //
	   {
		flag_REC=0;
		if(buff[0]=='O'&&buff[1]=='N')	//第一个字节为O，第二个字节为N，第三个字节为控制码
		switch(buff[2])
	     {
		      case up :						    // 前进
			  send_str( );
			  run();
			  break;
		      case down:						// 后退
			   send_str1( );
			  backrun();
			  break;
		      case left:						// 左转
			   send_str3( );
			  leftrun();
			  break;
		      case right:						// 右转
			  send_str2( );
			  rightrun();
			  break;
		      case stop:						// 停止
			   send_str4( );
			  stoprun();
			  break;

	     }
      
					 
	 }
	}
}	