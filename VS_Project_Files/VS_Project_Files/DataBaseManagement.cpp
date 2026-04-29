#include "DatabaseManagement.h"
#include <fstream>

using namespace std;

SaveData::SaveData()
{
    username = "";
    Reset();
}

void SaveData::Reset()
{
    currentLevel = 1;
    totalScore = 0;
    totalGems = 0;
    livesRemaining = 3;
    characterSelected = 0;

    for (int i = 0; i < 10; i++)
    {
        levelsCompleted[i] = 0;

    }
}

// use | to seperate data
// username |level| score |gems |lives |char |lvl
string SaveData::AddSeperator() 
{
    string output = username + "|";
    output += intToString(currentLevel) + "|";
    output += intToString(totalScore) + "|";
    output += intToString(totalGems) + "|";
    output += intToString(livesRemaining) + "|";
    output += intToString(characterSelected) + "|";

    for (int i = 0; i < 10; i++)
    {
        // adds levels
        output += intToString(levelsCompleted[i]);
        if (i < 9)
        {
            output += "|"; // no | at last data 
        }
    }

    return output;
}

// remove the | while inputting data from file
void SaveData::RemoveSeperator(const string& input)
{
    
    string data[16];    // data or featire like username
    int count = 0;
    string current = "";    // current data

    for (int i = 0; i <= input.size() && count < 16; i++)
    {
        if (i == input.size() || input[i] == '|')
        {
            if (count < 16)
            {
                data[count] = current;
                count++;
            }
            current = "";
        }
        else
        {
            current += input[i];
        }
    }

    // assign data to variables of class
    if (count > 0)
    {
        username = data[0];
    }
    if (count > 1)
    {
        //as data is integer i mafe the help function
        currentLevel = stringToInt(data[1]);
    }
    if (count > 2)
    {
        totalScore = stringToInt(data[2]);
    }
    if (count > 3)
    {
        totalGems = stringToInt(data[3]);
    }
    if (count > 4)
    {
        livesRemaining = stringToInt(data[4]);
    }
    if (count > 5)
    {
        characterSelected = stringToInt(data[5]);
    }

    for (int i = 0; count>=6 && count<=15; i++)
    {
        levelsCompleted[i] = stringToInt(data[count]);  //check logiv
        count++;
    }
}

string SaveData::intToString(int value)
{
    if (value == 0)
    {
        return "0";
    }

    string result = "";
    int temp = value;

    while (temp > 0)
    {
        // 0 is base ascii so addin int will form num 0-9.
        // typecasting to char adds string.
        result = (char)('0' + temp % 10) + result;
        // we do not need to reverse string as new num is added before the string
        
        temp /= 10;
    }

    return result;
}

int SaveData::stringToInt(const string& input)
{
    int result = 0;
    for (int i = 0; i < input.size(); i++)
    {
        result *= 10;   // shigts units tens hundreds
        result += input[i] - '0';       // adds the number by subtracting ASCII value
       
    }
    return result;
}



//
//   FileManage
// 

FileManage::FileManage(const string& datapath)
{
    databasePath = datapath;
    savePath = datapath + "_save";      // normally save files have same path as database but with _save added
}

FileManage::~FileManage()
{
}

// user's user name, password are stoed
bool FileManage::addUser(const string& name, const string& password)
{
    // ensuring ke user pehlay se na ho tabhi new username add karay
    if (!userExists(name)) 
    {
        string line = name + "," + password; // format to store username
        int lineCount = countLines(databasePath);


        return writeLine(databasePath, lineCount, line);
        // if name written then we say user added else not added
    }
    return false;

}

bool FileManage::userExists(const string& name)
{
    int line = findName(name);
    if (line >= 0)
    {
        return true;
    }
    return 0;
}

// username and passsword matches
bool FileManage::verifyPassword(const string& name, const string& password)
{
    // name will tell which line ot acually check the pasword of
    int lineNum = findName(name);
    if (lineNum < 0) // usename doesnt exist so how can password ???
    {
        return false;
    }

    string line;
    if (!readLine(databasePath, lineNum, line)) // no data to read maybe due to file corruption restriction
    {
        return false;
    }

    string currentpassword = "";
    bool foundComma = false;

    for (int j = 0; j < line.length(); j++)
    {
        // we first need to find the comma. bczbefre the comma was username but we need password.
        // after comma is found we append the current password and check whether it is equal to
        // password
        if (foundComma)
        {
            currentpassword += line[j];
        }
        else if (line[j] == ',')
        {
            foundComma = true; 
        }
    }

    if (currentpassword == password)
    {
        return 1;
    }
    return 0;
    
}

bool FileManage::saveGameData(const string& username, SaveData* data)
{
    int lineNum = findName(username);
    if (lineNum < 0)
    {
        return false;
    }
    // the data we recieve is seperated by '|'
    string seperatedData = data->AddSeperator();

    
    return writeLine(savePath, lineNum, seperatedData);
}

bool FileManage::loadGameData(const string& username, SaveData* data)
{
    int lineNum = findName(username);
    if (lineNum < 0)
    {
        return false;
    }

    string seperatedData;
    if (!readLine(savePath, lineNum, seperatedData))
    {
        // if we cant read then no save present.
        // Create new save by reset data and add usernmae.
        data->Reset();
        data->username = username;
        return true;
    }


    // if data is present then we read it and remove '|'
    data->RemoveSeperator(seperatedData);
    return true;
}

bool FileManage::addScore(const string& name, int score)
{
    SaveData data;
    if (!loadGameData(name, &data))
    {
        return false;
    }

    // check if new high score is greater then the previous one then update it if it is and save data
    if (score > data.totalScore)
    {
        data.totalScore = score;
        bool saved = saveGameData(name, &data);
        return saved; // if saved then true else false
    }

    return true;
}

// top 10 name adn scores are filled into array of name[10 and score[10]
void FileManage::getTopScores(string names[10], int scores[10])
{
    // all array position are empty
    for (int i = 0; i < 10; i++)
    {
        names[i] = "";
        scores[i] = 0;
    }

    int lineCount = countLines(databasePath);

    for (int i = 0; i < lineCount; i++)
    {
        string line;
        if (!readLine(databasePath, i, line))   // cant read then continue to next line
        {
            continue;
        }

       
        string uname = "";
        for (int j = 0; j < line.length(); j++)
        {
            if (line[j] == ',') // appends username until j reaches comma
            {
                break;
            }
            uname += line[j];          
        }
        
        
        SaveData data;
        if (!loadGameData(uname, &data))    // load current data of that user
        {
            continue;
        }

        // this is called insertion sort
        for (int k = 0; k < 10; k++)
        {
            // If the user's score is higher than a score in our Top 10 list
            // score checks each of top 10 scorees to find if it is bigger than any one
            if (data.totalScore > scores[k])
            {
                // move all things below this spot down by one
                // start from k and m+1 becomes m bcz original m was ffilled by k
                for (int m = k; m < 10; m++)
                {
                    scores[m+1] = scores[m];
                    names[m+1] = names[m];
                }
                
                // insert the new high score in the empty spot or k
                scores[k] = data.totalScore;
                names[k] = uname;

                // k is going from greater to lower. so the first spot k finds is the best one
                // therefore we break
                break;
            }
        }
    }
}



bool FileManage::readLine(const string& filename, int lineNumber, string& output)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    string line[500];
    // start to read and ignore the file until the line number is reached
    for (int i = 0; i <= lineNumber && i<500; i++)
    {
        if (!getline(file, line[i]))   // if the line number doesnt exist it will return
        {
            file.close();
            return false;
        }
    }

    // we can simply output line as it is iverrided by new input
    output = line[lineNumber];
    file.close();
    return true;
}

bool FileManage::writeLine(const string& filename, int lineNumber, const string& data)
{
    // get total lines present to build futher upon it
    int existingLines = countLines(filename);
    // we now store data in array so that it is not overwritten
    string lines[500];

    ifstream file(filename);
    if (file.is_open())
    {
        for (int i = 0; i < existingLines && i < 500; i++)
        {
            getline(file, lines[i]);
        }
        file.close();
    }

    // output the data onto the line and re write all file
    ofstream outFile(filename);
    if (!outFile.is_open())
    {
        return false;

    }

    // prints all previous files again
    for (int i = 0; i < lineNumber && i < existingLines; i++)
    {
        outFile << lines[i] << endl;
    }
    // we re write the modified line with data 
    outFile << data << endl;
    // now we right the next lines aafter
    for (int i = lineNumber + 1; i < existingLines; i++)
    {
        outFile << lines[i] <<endl;
    }

    outFile.close();
    return true;
}

int FileManage::countLines(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        return 0;
    }

    int count = 0;
    string line;
    // while loop is easier in file handliing
    // if input can be taken count++;
    while (getline(file, line))
    {
        count++;
    }

    file.close();
    return count;
}

//tells at which line the username detail are present and gives -1 agar name nhi milta
int FileManage::findName(const string& username)
{
    int lineCount = countLines(databasePath);

    for (int i = 0; i < lineCount; i++)
    {
        string line;
        if (!readLine(databasePath, i, line)) // checks if line can be read
        {
            continue;
        }

        string current="";          // empty string to store each username one by one

        for (int j = 0;j<line.length();j++)   // comma reached break and compare string with username
        {
            if (line[j] == ',')
            {
                break;
            }
            current += line[i];
        }

        if (current == username)
        {
            return i;
        }
    }

    return -1;
}