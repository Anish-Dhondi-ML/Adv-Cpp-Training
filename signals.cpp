#include<iostream>
#include<csignal>

using namespace std;

void signalHandler( int sigNum ) {
	cout<<" \n Interrupt Signal Received : "<< sigNum << endl;
	exit(sigNum);
}

int main(){
	
	signal(SIGINT,signalHandler);// 2
	signal(SIGTERM,signalHandler);// 15
	signal(SIGSEGV,signalHandler); // 11
	//char *str = "XYZ";
	//*(str + 1) = 'V';
	
	while(1) {
	
		cout<<"Going to Sleep......."<<endl;
		sleep(1);
	}
	
	return 0;
}


