#include<iostream>
#include<fstream>
using namespace std;
int main()
{
    fstream file; //Обєкт файлового потоку 
    

    file.open("/home/duck/Завантажене/1.txt",fstream::out/*даний прапорець використовується для вивід у файл або запиc*/);//спроба відкрити файл 

    if(!file.is_open())
    {
        cout<<"error"<<endl;
        return 0;
    }
    file<<"hash\n";

    file.close();
    return 0;
}