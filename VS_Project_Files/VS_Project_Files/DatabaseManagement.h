#pragma once
#include <string>
#include <fstream>
using namespace std;

// includes database handler + save data


// All the save file information is here
class SaveData
{
public:
    string username;               
    int currentLevel;               // last level played
    int totalScore;                 //  total score throughout the levels
    int totalGems;                  
    int livesRemaining;             
    int levelsCompleted[10];        // 0 left and 1 is complete
    int characterSelected;         

    
    SaveData();
    void Reset();

    string AddSeperator();
    void RemoveSeperator(const string& input);

    string intToString(int value);
    int stringToInt(const string& input);
};


// the file operations are managed here
class FileManage
{
private:
    string databasePath;        // path to database file. data basefile stores all username and passwords waghera
    string savePath;            // path to save data file, saves all data. continue ke liay istemaal hoga

public:
  
    FileManage(const string& dbPath);

    ~FileManage();

    // User management
    bool addUser(const string& username, const string& hashedPassword);
    bool userExists(const string& username);
    bool verifyPassword(const string& username, const string& hashedPassword);

    bool saveGameData(const string& username, SaveData* data);
    bool loadGameData(const string& username, SaveData* data);

    // Leaderboard
    bool addScore(const string& username, int score);
    void getTopScores(string names[10], int scores[10]);

private:
    // read the data on specific line
    bool readLine(const string& filename, int lineNumber, string& output);

    //change a line
    bool writeLine(const string& filename, int lineNumber, const string& data);
    int countLines(const string& filename);

    // finds a specific usernam. used duing login wala phase
    int findName(const string& username);
};