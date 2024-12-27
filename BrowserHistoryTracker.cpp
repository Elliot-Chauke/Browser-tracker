//Elliot Chauke
//Browser simulation

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <regex>
#include <cstdlib>
#ifdef _win32
#else
#endif
using namespace std;



class browserStack
{
private:
stack<string>navigateBack;//stack to store urls navigating back
stack<string>navigateForward;//stack to store urls navigating forward

public:
void navigateTo(string& url)
{   //navigate to current url
    navigateBack.push(url);
    cout << "navigate to: " << url << endl;
    
    //clear forward stack
    while(!navigateForward.empty())
    {
    navigateForward.pop();
    }
}


void backStack()
{
    if(!navigateBack.empty())
            {

                string currentUrl=navigateBack.top();//store the url at the top of the stack to currentUrl
                cout<<"navigated to: "<<currentUrl<<endl;//output the url at the top of the stack
                navigateBack.pop();//remove the url at the top of the navigateback stack
                navigateForward.push(currentUrl);//store the removed url the stack that navigate forward
            }
            else
                {
                cout<<"No more back history"<<endl;//if the is no url in the stack display the message
                }
}


void forwardStack()
{
//if statement to check if the stack if empty
           if(!navigateForward.empty())
            {

                string nextUrl = navigateForward.top();//store the url at the top of navigateforward stack to currentUrl2
                cout<<"navigated to: "<<nextUrl<<endl;//output the url at the top of the navigateforward stack
                navigateBack.push(nextUrl);//store the removed url back to the stack that navigate back
                navigateForward.pop();
            }
            else
                {
                cout<<"No more forward history"<<endl;//if the is no url in the stack display the message
                }
}


void initialiseStack(string& fname)
{
    ifstream inputFile(fname);
if(!inputFile.is_open())
{
   cout<<"cannot open file"<<endl;
   cin.ignore();
   cin.get();
}

string url;
while(getline(inputFile,url))
      {
          navigateBack.push(url);//push each url into navigateBack stack

      }
inputFile.close();

}

};


//Function to display menu
void displayMenu()
{   system("cls");//To clear the screen
    cout<<""<<endl;
    cout<< "  Menu"<<endl;
    cout<<"1. New URL"<<endl;
    cout<<"2. Navigate back"<<endl;
    cout<<"3. Navigate forward"<<endl;
    cout<<"4. Exit"<<endl;
    cout<<""<<endl;
}

//Function to verify if the input string matches the url
bool validateURL(string url) {
        // Simple regex pattern: starts with "www." and contains at least one period (.)
        regex pattern("www\\..+\\..+");
        return regex_match(url, pattern);
    }


void writeToFile(const string& fName,const string& contents)
{

ofstream file(fName);
if(file.is_open())
{
file << contents;
file.close();
cout << "Data written to " << fName <<endl;
}    
else
{
    cout << "Cannot open file " << endl;
}

}

void updateFileText(const string& fname,const string& newUrl)
{
//open file 
ifstream file(fname);
if(!file.is_open())
{
    cout << " Cannot open file " << endl; 
}
stack<string> allUrl; //to store all urls
string line;
//store all urls from file to allUrl stack
while(getline(file,line))
{
    allUrl.push(line);
}
file.close();
//Add new url to stack
allUrl.push(newUrl);

 string content;
 
 while(!allUrl.empty())
 {
    content += allUrl.top() + "\n";
    allUrl.pop();
 }

//write to file
writeToFile(fname,content);

}


int main()
{

browserStack browser;
string filename = "Brows.txt";//input file name
int option=0;//initializing the switch option
browser.initialiseStack(filename);
displayMenu(); //calling the menu function

//a loop that allows the selection of options until option 4 is selected then the loop terminate
do
{
cin>>option;//taking input option from the user
cout<<""<<endl;//new line

//switch statement to choose options from
switch(option)
{
    case 1:
    {
    string newUrl = "";
    cout <<  "Enter new Url " <<endl;
    cin >> newUrl;

    while(!validateURL(newUrl))
    {
        cout << " Not a valid Url, please enter valid url" << endl;
        cin >> newUrl;
    }
    updateFileText(filename,newUrl);
    browser.navigateTo(newUrl);
    break;

    }
    case 2:
        {   
           browser.backStack();
            break;
        }
    case 3:
        {
          browser.forwardStack();
            break;
        }
    case 4:
        {   //exit the program
            break;
        }
    default:
        cout<<"Invalid option, Please Enter option from the Menu"<<endl;//message to display when wrong option is selected
}

cout<<"  Press enter to continue ..." <<endl;
cin.ignore();//clears the input
cin.get();//to retrieve inputs

displayMenu(); //calling the menu function

}while(option != 4);

    return 0;

}
