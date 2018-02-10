#include<iostream>
#include<cmath>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>

using namespace std;
int zong=0;//记录总时间，用来比对求出最优解
int ask[1004];
int t;
int minn=99999999;
struct{
  	int time;//记录这名乘客发出请求的时刻 
  	int ceng;//记录这名乘客发出请求的层数 
  	int flag;//记录这名乘客去的方向  0表示向下，1表示向上 
  	int zhuang;//记录这名乘客的状态 0表示等待进入，1表示在电梯中，2表示已经下电梯 
  	int value;//记录这名乘客的到达时间：到达的时间-发出请求的time 
}r[1004];
struct{
	int time;
	int floor;
}ans[1004];//记录DFS中的数据 
struct {
	int time;
	int floor;
}anss[1004];//记录最后答案中的数据 
struct {
	int time;//记录当前的时间 
	int floor;//电梯当前所在的楼层 
	int flag;//记录现在取得方向，有0 10两种 
}dt;
int pd()//检验电梯运行的状态，有多少人，是否完成任务 
{
	for(int i=1;i<5;i++)
	if(r[i].zhuang!=2)
	return 0;
	return 1; 
}
void gx(int n)//用来更新电梯中人员的状态，n表示当前层数 
{
    if(n==10)
    for(int i=1;i<=5;i++)
    if(r[i].flag==1&&r[i].zhuang==1)
		{
		  r[i].zhuang=2;
	    }
		//如果当前是第10层，让电梯中需要出去的人出去 
		
	if(n==1)
    for(int i=1;i<=5;i++)
    if(r[i].flag==0&&r[i].zhuang==1)
	   {
		r[i].zhuang=2;
	   }//如果当前是第1层，让电梯中需要出去的人出去	
	for(int i=1;i<=5;i++)
	if(r[i].ceng==n&&r[i].zhuang==0)
	    r[i].zhuang=1;//如果当前停靠的层数有人要上，那就让他进入电梯  
}
void pd2(int w){
	if(w<minn)
	{
		minn=w; 
		for(int i=1;i<=20;i++){
		anss[i].time=ans[i].time;
		anss[i].floor=ans[i].floor;
		}
	}
}
void dfs(int k){//第K次决策 
	int ji=0;
//	cout<<111; 
    
	for(int i=1;i<=7;i++)//一个时刻有7种可能可以停靠,因为只会停靠在有人请求的楼层 
	{
	   if(i!=6&&i!=7&&r[i].zhuang==0)
	   	{
	   	//	cout<<r[i].ceng<<endl;
		    ji=dt.floor;
	   		dt.time+=abs(dt.floor-r[i].ceng);
	   		dt.floor=r[i].ceng;//模拟电梯移动 
	   		
	   		ans[k].time=dt.time;
	   		ans[k].floor=dt.floor;//数据更新 
	   		for(int j=1;j<=5;j++)
             	if(r[j].ceng==r[i].ceng&&r[j].zhuang==0)
	           { 
			   r[j].zhuang=1;
			   ask[j]=1;//如果当前停靠的层数有人要上，那就让他进入电梯    
				}
			if(pd()==1)
            pd2(t);
            else
	   	    dfs(k+1);
	   	    dt.time-=abs(dt.floor-r[i].ceng);
	   		dt.floor=ji; 
	   		for(int j=1;j<=5;j++)
	   		if(ask[j]==1)
	   		{
	   			r[j].zhuang=0;
			}
			for(int j=1;j<=5;j++)
			ask[j]=0;
		} 
		if(i==6)
		{
				//cout<<r[i].ceng<<endl;
			ji=dt.floor;
	   		dt.time+=abs(dt.floor-1);
	   		dt.floor=r[i].ceng;//模拟电梯移动 
	   		
	   		ans[k].time=dt.time;
	   		ans[k].floor=dt.floor;//数据更新
			for(int j=1;j<=5;j++)
            if(r[j].flag==0&&r[j].zhuang==1)
	        {
		     r[i].zhuang=2;
		     ask[j]=1;
		     t+=dt.time-r[i].time;
	        }//如果当前是第10层，让电梯中需要出去的人出去 
	        if(pd()==1)
            pd2(t);
            else
	   	    dfs(k+1);
	        dt.time-=abs(dt.floor-r[i].ceng);
	   		dt.floor=ji; 
	   		for(int j=1;j<=5;j++)
	   		if(ask[j]==1)
	   		{
	   			r[j].zhuang=1;
	   			t-=dt.time-r[i].time;
			}
			for(int j=1;j<=5;j++)
			ask[j]=0;
		}
		if(i==7)
		{
				//cout<<r[i].ceng<<endl;
			ji=dt.floor;
	   		dt.time+=abs(dt.floor-1);
	   		dt.floor=r[i].ceng;//模拟电梯移动 
	   		
	   		ans[k].time=dt.time;
	   		ans[k].floor=dt.floor;//数据更新
			for(int j=1;j<=5;j++)
            if(r[j].flag==1&&r[j].zhuang==1)
	        {
		     r[i].zhuang=2;
		     ask[j]=1;
		     t+=dt.time-r[i].time;
	        }//如果当前是第1层，让电梯中需要出去的人出去 
	        if(pd()==1)
            pd2(t);
            else
	   	    dfs(k+1);
	        dt.time-=abs(dt.floor-r[i].ceng);
	   		dt.floor=ji; 
	   		for(int j=1;j<=5;j++)
	   		if(ask[j]==1)
	   		{
	   			r[j].zhuang=1;
	   			t-=dt.time-r[i].time;
			}
			for(int j=1;j<=5;j++)
			ask[j]=0;
		}
	} 
}
int main(){
	
	for(int i=1;i<=5;i++)
	 scanf("%d%d%d",&r[i].time,&r[i].ceng,&r[i].flag);//读入 
	r[6].ceng=10;r[6].zhuang=0;//初始化 
	r[7].ceng=1;r[7].zhuang=0;//初始化 
	dfs(1); 
	for(int i=1;i<=20;i++)
	cout<<anss[i].time<<" "<<anss[i].floor<<endl; 
	return 0;
}
