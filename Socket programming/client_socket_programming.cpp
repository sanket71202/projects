// The file is named client but this file and its complementary files both are used as client and server.
// Command to compile: g++ server_socket_programming.cpp -o server_socket_programming.exe -lws2_32
#include <ws2tcpip.h>
#include <iostream>
#include <winsock2.h>
#include <thread>
#include <atomic>
#include <sstream>
using namespace std;    
#pragma comment(lib, "ws2_32.lib")
#define PORT 8080

WSADATA wsaData;
SOCKET socket_side2;
sockaddr_in serverAddr;
atomic<bool> go(true);

void send_to_server(){
    while(go){
        string input;
        getline(cin,input);
        if(input=="exit"){
            send(socket_side2,input.c_str(),input.size(),0);
            go=false;
            break;
        }else{
            send(socket_side2,input.c_str(),input.size(),0);
        }
        
    }
}

void recv_from_server(){
    while(go){
        char message[1024] = {0}; 
        int bytesrecieved = recv(socket_side2,message,sizeof(message)-1,0);
        if(bytesrecieved<=0){
            cout<<"Error in recieving message from server."<<endl;
            continue;
        }else{
            message[bytesrecieved] = '\0';
            if(string(message)=="exit"){
                send(socket_side2,message,sizeof(message),0);
                istringstream fakeinput("exit");
                cin.rdbuf(fakeinput.rdbuf());
                go = false;
                break;
            }else{
                cout<<"Sender: "<<string(message)<<endl;
            }
        }
        
    }
}

int connect_to_server(){
    if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0){
        cout<<"Wsa init failed."<<endl;
        return -1;
    }

    socket_side2 = socket(AF_INET,SOCK_STREAM,0);
    if(socket_side2==INVALID_SOCKET){
        cout<<"Socket creation failed."<<endl;
        WSACleanup();
        return -1;
    }
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET,"127.0.0.1",&serverAddr.sin_addr);

    if(connect(socket_side2,(sockaddr*)&serverAddr,sizeof(serverAddr))==SOCKET_ERROR){
        cout<<"Could not connect to server."<<endl;
        closesocket(socket_side2);
        WSACleanup();
        return -1;
    }
    return 0;
}


int main(){
    // socket create 
    // connect wth server side
    // send req

    if(connect_to_server() == 0) cout<<"Connected to server."<<endl;
    else return -1;
    
    thread send_thread(send_to_server);
    thread recv_thread(recv_from_server);

    send_thread.join();
    recv_thread.join();
    cout<<"Disconnected from server"<<endl;

    closesocket(socket_side2);
    WSACleanup();

    return 0;
}