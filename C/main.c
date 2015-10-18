#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/*


 Author: Kim Hyun Woo (npr05324@gmail.com) 


 Not Completed 


*/


void menu(int *choice);  // print Menu
int result(int choice);  // print result
void func(int choice);  
void getIP(); 
void getPrefix();
void getNetAddr(int *ip,int *sm,int *save); 
void getBcastAddr(int *ip,int *sm,int *save);
void getSubnetmask(int prefix,int * sm);
int prefixtodec(int prefix);


	int prefix;
	int hosts; 
	int ip[4]={0};
	int sm[4]={0};
	int na[4]={0}; //��Ʈ��ũ �ּ� 
	int ba[4]={0}; // ��ε�ĳ��Ʈ �ּ� 
	


int main(){
	int choice; 

	
	
	menu(&choice);
	
	
	 
	
	


	
	
	
}


void menu(int *choice){
	printf("-----------------------------------------------------\n");
	printf("  1,IP�� ����� ����ũ                               \n");
	printf("  2,IP�� ����� �����Ƚ�                             \n");
	printf("  3,IP�� ȣ��Ʈ����                                  \n");
	printf("-----------------------------------------------------\n");
	printf("����(1~3):");
	scanf("%d",&choice); 
	
	
	func(choice);
	
}

void func(int choice){
	
	
	switch(choice){
		case 1:
			getIP();
			printf("����� ����ũ �Է�(255.255.255.255 --> 255 255 255 255)\n: ");
			scanf("%d %d %d %d",&sm[0],&sm[1],&sm[2],&sm[3]);
			break;
		case 2:
			getIP();
			getPrefix();
			break;
		case 3:
			getIP();
			getHost();
			break;
			
		default:
			printf("�ùٸ� ���� ���� �Է����ּ���\n");
			break;
			
		
		
	}
	
	result(choice);
	
}


int result(int choice){
	switch(choice){
		case 1:
			getNetAddr(ip,sm,na);
			getBcastAddr(ip,sm,ba);
			break;
		case 2:
			getSubnetmask(prefix,sm);
			getNetAddr(ip,sm,na);
			getBcastAddr(ip,sm,ba);
			break;
		case 3:
			getSubnetmask(host_to_Prefix(hosts),sm);
			getNetAddr(ip,sm,na);
			getBcastAddr(ip,sm,ba);
			break;
		
	}
	
	
	

	
	printf("\n\n\n\n");
	
	
	printf("IP: %d.%d.%d.%d\n",ip[0],ip[1],ip[2],ip[3]);
	printf("Subnet Mask: %d.%d.%d.%d\n",sm[0],sm[1],sm[2],sm[3]);
	
	printf("Network: %d.%d.%d.%d\n",na[0],na[1],na[2],na[3]);
	printf("Broadcast: %d.%d.%d.%d\n",ba[0],ba[1],ba[2],ba[3]);
	
	
	return 0;
}




void getIP(){
	printf("IP�Է� (8.8.8.8 --> 8 8 8 8 ):");
	scanf("%d %d %d %d",&ip,&ip[1],&ip[2],&ip[3]); 
	
}

void getPrefix(){
	printf("����� �����Ƚ� �Է�:");
	scanf("%d",&prefix);
}

void getHost(){
	printf("ȣ��Ʈ �����Է�:");
	scanf("%d",&hosts); 
}






void getNetAddr(int *ip,int *sm,int *save){
	*(save)=*(ip)&*(sm); // First 8bit 
	*(save+1)=*(ip+1)&*(sm+1); // Second 8bit
	*(save+2)=*(ip+2)&*(sm+2); // Third 8bit
	*(save+3)=*(ip+3)&*(sm+3); // Fourth 8bit	


}

void getBcastAddr(int *ip,int *sm,int *save){
	int *temp;
	temp=(int*)malloc(4*sizeof(int));
	
	*(save)=255-*(sm);
	*(save+1)=255-*(sm+1);
	*(save+2)=255-*(sm+2);
	*(save+3)=255-*(sm+3);
	
	getNetAddr(ip,sm,temp);
	
	*(save)+=*(temp);
	*(save+1)+=*(temp+1);
	*(save+2)+=*(temp+2);
	*(save+3)+=*(temp+3);
	
	
	
	free(temp);
}



void getSubnetmask(int prefix,int * sm){
	int quota=prefix/8; // 1���� ���ΰ� 1�ϰ�� 255
	
	int remainder=prefix%8;
	
	int i;
	for(i=0;i<quota;i++){ // ���ݿ� �� ä���, (�̰�� 255�� ä��) 
		*(sm+i)=255;	
	} 	 
	
	
	if(remainder!=0){
		
		if(quota==0){
		*(sm)=prefixtodec(remainder);
		*(sm+1)=0;
		*(sm+2)=0;
		*(sm+3)=0;
		}else
		if(quota==1){
			*(sm+1)=prefixtodec(remainder);
			*(sm+2)=0;
			*(sm+3)=0;
	
		}else 
		if(quota==2){
			*(sm+2)=prefixtodec(remainder);
			*(sm+3)=0;
		}else
		if(quota==3){
			*(sm+3)=prefixtodec(remainder);
		}
	
	}
	
	
	// ����  4 �϶��� 255.255.255.255�� ���� 
	 
	
	
	
	
	
	
}

int prefixtodec(int prefix){
	int sm=0;
	int i=7;
	int cnt=0;
	while(1){
		
		
		sm+=(int)pow(2,i);
		i--;
		cnt++;
		
		if(prefix==cnt) break;
	}
		
	
	
		
	
		
		
		
	return sm; 
}


int host_to_Prefix(int hosts){
	int i=0;
	int temp=0;
	
	hosts+=2; // NetAdd+ BcastAddr
	for(i=0;temp<hosts;i++)
		temp=(int)pow(2,i);


	return 32-(i-1);

}









