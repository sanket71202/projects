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
SOCKET socket_side1,client_side1;
sockaddr_in socket_addr1,clientAddr;
atomic<bool> go(true);

void send_to_client(){
    while(go){
        string input;
        getline(cin,input);
        if(input == "exit"){
            send(client_side1,input.c_str(),input.size(),0);
            go = false;
            break;
        }else{
            send(client_side1,input.c_str(),input.size(),0);
        }
    }
}

void recv_from_client(){
    while(go){
        char messagebuf[1024] = {0};
        int bytesrecieved = recv(client_side1,messagebuf,sizeof(messagebuf)-1,0);
        if(bytesrecieved<=0){
            cout<<"This message could not be recieved"<<endl;
            continue;
        }else{
            messagebuf[bytesrecieved] = '\0';
            if(string(messagebuf) == "exit"){
                send(client_side1,messagebuf,sizeof(messagebuf),0);
                istringstream fakeinput("exit");
                cin.rdbuf(fakeinput.rdbuf());
                go = false;
                break;
            }else{

                cout<<"Sender: "<<string(messagebuf)<<endl;
            } 
        }
        
    }
    
}

int accept_connection(){
    if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0){
        cout<<"WSA init fail"<<endl;
        return -1;
    }

    socket_side1 = socket(AF_INET, SOCK_STREAM, 0);
    socket_addr1.sin_family = AF_INET;
    socket_addr1.sin_port = htons(PORT);
    socket_addr1.sin_addr.s_addr = INADDR_ANY;
    if(bind(socket_side1,(sockaddr*)&socket_addr1,sizeof(socket_addr1))==SOCKET_ERROR){
        cout<<"Bind error."<<endl;
        closesocket(socket_side1);
        WSACleanup();
        return -1;
    }

    if(listen(socket_side1,SOMAXCONN) == SOCKET_ERROR){
        cout<<"Listen Error."<<endl;
        closesocket(socket_side1);
        WSACleanup();
        return -1;
    }
    int s = sizeof(clientAddr);
    client_side1 = accept(socket_side1,(sockaddr*)&clientAddr,&s);
    if(client_side1 == INVALID_SOCKET){
        cout<<"Accept failed."<<endl;
        closesocket(socket_side1);
        WSACleanup();
        return -1;
    }
    return 0;
}

int main(){
    // socket create 
    // connect wth server side
    // send req


    
    if(accept_connection() == 0) cout<<"Client connected"<<endl;
    else return -1;

    thread recv_thread(recv_from_client);
    thread send_thread(send_to_client);

    
    recv_thread.join();
    send_thread.join();

    cout<<"Disconnected from Client."<<endl;

    closesocket(client_side1);
    closesocket(socket_side1);
    WSACleanup();

    return 0;    
}