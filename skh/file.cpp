#include<iostream>
#include <filesystem>
#include<string>
#include<sstream>

using namespace std;
using namespace std::filesysytem;
wstring DisplayPathInfo ()
{
    path pathToDisplay(L"/home/duck/Завантажене/Telegram Desktop/PR-15.pdf");

    wostringstream wos;
    int i = 0 ;
    wos << L"Displayingpath info for "<< pathToDisplay<<endl;
    for(path::iterator itr = pathToDisplay.begin(); itr != pathToDisplay.end():++itr)
    {
        wos<<L"path part "<<i++<<L" = "<<*itr<<endl;
    }
    wos << L"root_name() = " << pathToDisplay.root_name() << endl
    << L"root_path() = " << pathToDisplay.root_path() << endl
    << L"relative_path() = " << pathToDisplay.relative_path() << endl
    << L"parent_path() = " << pathToDisplay.parent_path() << endl
    << L"filename() = " << pathToDisplay.filename() << endl
    << L"stem() = " << pathToDisplay.stem() << endl
    << L"extension() = " << pathToDisplay.extension() << endl;
    return wos.str();
}
int main()
{
wcout << DisplayPathInfo() << endl;
// wcout << ComparePaths() << endl; // see following example
wcout << endl << L"Press Enter to exit" << endl;
wstring input;
getline(wcin, input);
}