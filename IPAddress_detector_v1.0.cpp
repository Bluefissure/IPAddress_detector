#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
using namespace std;
string getcmd(string IP,string Mask,string Gateway)
{
	string cmd="netsh interface ip set address name=\"本地连接\" static ";
	cmd+=IP+" "+Mask+" "+Gateway+" 1";
	return cmd;
}
char IP[100] ,Ma[100] ,Ga[100] ; //IP,子网掩码，网关 
void printinfo()
{
	system("title IPAddress_detector_v1.0");
	puts("IPAddress Detector v1.0");
	puts("\t CopyRight@Bluefissure");
	puts("\t Last Release:2015-9-7");
	puts("Press Enter to continue......");
	cin.get(); 
}
int main()
{
	printinfo();
	puts("正在进行DNS设置，请稍等......\n");
	puts("Removing DNS......");
	system("netsh interface ip set dns name = \"本地连接\" static addr = none ");
	puts("Adding DNS 211.87.226.11");
	system("netsh interface ip add dns name = \"本地连接\" addr = 211.87.226.11");
	puts("Successfully added DNS 211.87.226.11\n");
	puts("Adding DNS 202.194.15.12");
	system("netsh interface ip add dns name = \"本地连接\" addr = 202.194.15.12");
	puts("Successfully added DNS 202.194.15.12\n");
	system("@echo on");
    printf("请输入对应楼层的ip地址倒数第二位:");
    int c,d;
    scanf("%d",&c);
    strcpy(Ma,"255.255.255.0");
    bool ok=0;
    for(d=254;d>=10;d--){
    	sprintf(IP,"121.250.%d.%d",c,d);
    	sprintf(Ga,"121.250.%d.1",c);
    	printf("Testing on %s\n",IP);
    	system(getcmd(IP,Ma,Ga).c_str());
   		string filename=string(IP)+".txt";
   		string test="( ping 8.8.8.8 & ipconfig ) > "+filename;
   		system(test.c_str());
   		freopen(filename.c_str(),"r",stdin);
   		string info;
   		for(int k=1;k<=9;k++){
   			getline(cin,info);
   			if(info.find("TTL")!=-1){
   				ok=1;break;
   			}
   		}
   		if(ok) break;
	   	else{
	    	printf("IP:121.250.%d.%d is not available\n\n",c,d);
	    }
   		
    }
    if(ok)
    	printf("Found IP:121.250.%d.%d available\n",c,d);
	else
		puts("Sorry, haven't found any IP available");
	system("pause");
    return 0;
}
