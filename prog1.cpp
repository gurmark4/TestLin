
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <chrono>
#include <dirent.h>
#include <thread>         // std::thread
//#include <mutex>          // std::mutex

using namespace std;

template <class T>
void quickSortR(T& a, int N) {
	int k = -1, temp;
	for (auto i = 0; i < N; i++) {
		if (a[i] < a[i + 1]) {
			temp = a[i + 1];
			a[i + 1] = a[i];
			a[i] = temp;
			k = 1;
		}
	}
	// рекурсивные вызовы, если есть, что сортировать 

	if (k > 0) quickSortR(a, N);
}

void thr1(std::fstream &fl, std::string path, int* k)
{
	std::string s;
	int i = 0;
	char c;
     std::cout <<  "   thr1\n";
while (true) {
while (true) {if (*k > 0) std::this_thread::sleep_for(std::chrono::seconds(5)); else break;}
	int m = 0;
  std::cout << "   Input line\n";
  std::getline(std::cin, s);
  std::cout << s <<"\n";
	if (s == "exit") { std::cout << "Bye\n";  exit(1); }
	if (s.length() > 64) { std::cout << "Error: length " << s.length() << " >64\n";  exit(1); }
	else std::cout << "length  " << s.length() << "\n";
	for (i = 0; i < s.length(); i++)  if ((s[i] - '0') < 0 || (s[i] - '0') > 9) 
        { std::cout << "Error: not all elements is number  \n";  exit(1); }
	quickSortR(s, s.length());
	fl.open(path, ios::in |ios::out | ios::binary);
	if (!fl.is_open()) {		std::cout << "File not open\n"; exit(1);	
}
	for (i = 0; i < s.length(); i++) {
		if ((i + 1) % 2 != 0) fl.write((char*) &s[i], sizeof(c));
		else {
			c = 'K';
			m++;
			fl.write((char*) &c, sizeof(c));
			c = 'B';
			m++;
			fl.write((char*) &c, sizeof(c));
		     }
	}
	fl.close();
   *k = m;
  std::cout << "   End th1\n";
            }
}

void thr2(std::fstream &fl, std::string path, int* k)
{
while (true) {
	std::string s = "";
	int i = 0, n;
	char c;
while (true) {if (*k == 0) std::this_thread::sleep_for(std::chrono::seconds(5)); else 
{n = *k; break;}}
     std::cout << "   thr2\n";

	fl.open(path, ios::in |ios::out | ios::binary);  
	if (!fl.is_open()) {
          std::cout << path << "\n";
		std::cout << "File not open in\n"; exit(1);
	}
	int ks = 0;
	for (i = 0; i < n; i++) {
		fl.read((char*) &c, sizeof(c));
		s += c;
		//	std::cout << i << " " << (c - '0') << "  read\n";
		if (c != 'K' && c != 'B') ks += (c - '0');
	}
			c = '0';
			fl.write((char*) &c, sizeof(c));
	std::cout << "Res string:  " << s << "  \n";
	std::cout << "Sum:  " << ks << "  \n";
	fl.close();

     s = std::to_string(ks);
char message[s.length()];
for (i = 0; i < s.length(); i++) message[i] = s[i];
char buf[1024];

    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425); // или любой другой порт...
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

while (true) {
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
      //  exit(2);
	std::cout << "Please, run prog2 and press any key...  \n";
c = getchar();

    }
else break;
             }
    send(sock, message, sizeof(message),  0);
    recv(sock, buf, sizeof(buf), 0);

std::cout << "Anser from prog2:  " <<  buf <<  " \n";
    close(sock);
*k = 0;
  }
}

int main(void)
{
	int k = 0;
	std::string s = "";

	std::string path = "";
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));
	path = std::string(cwd);
	path += "/tmp.bin";
	std::cout << "path: " << path << "   Ok\n";

	fstream fl;
while (true) {
std::thread call1(thr1, ref(fl), path, &k);
std::thread call2(thr2, ref(fl), path, &k);
call1.join();
call2.join();
             }

	return 0;
}