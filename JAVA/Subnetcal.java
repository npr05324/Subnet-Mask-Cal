import java.lang.*;


/*
 * getNetaddr(String ip, String sm) : ip와 서브넷 마스크의 각  Bit를 And 연산하여 네트워크 주소를 String 형으로 반환합니다.
 * getBcastAddr(String ip, String sm) : ip와 서브넷 마스크를 이용하여 네트워크 주소 + 서브넷마스크의 역 을 이용하여 브로드 캐스트 주소를 String 형으로 반환합니다.
 * getSubnetmask(int prefix) : 서브넷 프리픽스를 입력받아 프리픽스에 해당하는 서브넷 마스크를 String 형으로 반환합니다.
 * prefixtodec(int prefix) : 서브넷 마스크의 1옥텟을 2^x 의 비트형에서 정수형으로 변환합니다.
 * host_to_Prefix(int hosts) : 호스트 갯수를 이용하여 호스트 갯수에 해당하는 서브넷 프리픽스를 Int 형으로 반환합니다.
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * */





public class Subnetcal {

	
	
	
	
	
	
	static public String getNetAddr(String ip,String sm){
		int ip_int[] =new int[4]; // 문자열로부터 IP 로 변환
		int sm_int[] =new int[4]; // 문자열로부터 SM 로 변환
		
		String netaddr="";
		
		String[] ipstr = ip.split("[.]");
		String[] smstr = sm.split("[.]");
		for(int i=0;i<4;i++){
			ip_int[i] = Integer.parseInt(ipstr[i]);
			sm_int[i] = Integer.parseInt(smstr[i]);
		}
		
		
		
		netaddr+=String.valueOf(ip_int[0]&sm_int[0])+"."; // First 8bit 
		netaddr+=String.valueOf(ip_int[1]&sm_int[1])+"."; // Second 8bit
		netaddr+=String.valueOf(ip_int[2]&sm_int[2])+".";// Third 8bit
		netaddr+=String.valueOf(ip_int[3]&sm_int[3]); // Fourth 8bit	

		return netaddr;

	}

	
	static public String getBcastAddr(String ip, String sm){
		int ip_int[] =new int[4]; // 문자열로부터 IP 로 변환
		int sm_int[] =new int[4]; // 문자열로부터 SM 로 변환
		int reverse_sm[] = new int[4]; // 서브넷 마스크의 역
		int net_int[] =new int[4]; // 네트워크 주소 저장
		
		String bcastaddr="";
		String netaddr= getNetAddr(ip,sm);
		
		String[] ipstr = ip.split("[.]");
		String[] smstr = sm.split("[.]");
		String[] netstr = netaddr.split("[.]");
		
		

		
		for(int i=0;i<4;i++){
			ip_int[i] = Integer.parseInt(ipstr[i]);
			sm_int[i] = Integer.parseInt(smstr[i]);
			net_int[i] = Integer.parseInt(netstr[i]);
		}
		
		for(int i=0;i<4;i++){
			reverse_sm[i] = 255-sm_int[i];
		}
		
		for(int i=0;i<4;i++){
			bcastaddr+= String.valueOf(net_int[i]+reverse_sm[i]);
			if(i!=3)
				bcastaddr+=".";
		}
		
		
		
	
		
		
		return bcastaddr;
	}
	


	static String getSubnetmask(int prefix){
		
		
		int quota=prefix/8; // 1옥텟 전부가 1일경우 255
		
		int remainder=prefix%8;
		int sm_int[] =new int[4];
		
		
		String sm="";
		
		
		for(int i=0;i<quota;i++){ // 옥텟에 값 채우기, (이경우 255로 채움) 
			sm_int[i]=255;	
		} 	 
		
		
		if(remainder!=0){
			
			if(quota==0){
			sm_int[0]=prefixtodec(remainder);
			sm_int[1]=0;
			sm_int[2]=0;
			sm_int[3]=0;
			}else
			if(quota==1){
				sm_int[1]=prefixtodec(remainder);
				sm_int[2]=0;
				sm_int[3]=0;
		
			}else 
			if(quota==2){
				sm_int[2]=prefixtodec(remainder);
				sm_int[3]=0;
			}else
			if(quota==3){
				sm_int[3]=prefixtodec(remainder);
			}
		
		}
		
		
		// 몫이  4 일때는 255.255.255.255로 고정 
		 
		
		for(int i=0;i<4;i++){
			sm+= String.valueOf(sm_int[i]);
			if(i!=3)
				sm+=".";
		}
		
		
		
		return sm;
		
	}

	static public int prefixtodec(int prefix){
		int sm=0;
		int i=7;
		int cnt=0;
		while(true){
			
			
			sm+=(int)Math.pow(2,i);
			i--;
			cnt++;
			
			if(prefix==cnt) break;
		}
	
		return sm; 
	}


	static public int host_to_Prefix(int hosts){
		int i=0;
		int temp=0;
		
		hosts+=2; // NetAdd+ BcastAddr
		for(i=0;temp<hosts;i++)
			temp=(int)Math.pow(2,i);


		return 32-(i-1);

	}

	
	
	
}
