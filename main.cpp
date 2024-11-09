#include <map>
#include "generateUsers.hpp"
using namespace std;


map<string, User> buildMapByUserName(vector<User> users) {  //DONE
    map<string, User> usersMap;
    
    for(const auto& user : users)
    {
        usersMap[user.userName] = user;
    }

    return usersMap;
}


map<string, User> buildMapByEmail(vector<User> users) { 
    map<string, User> usersMap;
    
    for (const auto& user : users)
    {
        usersMap[user.email] = user;
    }

    return usersMap;
}


void printMap(map<string, User> aMap) { //DONE
    if (aMap.empty())
    {
        cout << " empty map has been entered" << endl;
    }

    for (const auto& pair : aMap)
    {
        cout << "- user:" << pair.first << ", info: ";
        printAUser(pair.second);
    }
}


bool isMapSorted(map<string, User> aMap) {
    if ( aMap.empty() )
        return true;
    
    auto iter = aMap.cbegin();    //cbegin() returns a const_iterator that points to the first element
    auto prev_iter = iter++;     //Initialize prevIt with the first element then increment it to the second element for comparison reagions

    for (;iter != aMap.cend();++iter, ++prev_iter)
    {
        if (iter->first < prev_iter->first) //checks if not sorted
        {
            return false;   //not sorted 
        }
    }

    return true;    //sorted
}


bool testSearchByKey(map<string, User> aMap, string keyToSearch) {
    
    if (aMap.find(keyToSearch) != aMap.end())
    {
        return true;
    }
    else
    {
        return false;
    }

}


bool testDeleteByKey(map<string, User> aMap, string keyToDelete) {
    
    if (aMap.find(keyToDelete) != aMap.end())
    {
        aMap.erase(keyToDelete);

        if (aMap.find(keyToDelete) == aMap.end())
        {
            return true;
        }
    }
    else
    {
        cout << keyToDelete <<", is not in the map" << endl;
        return false;
    }

}


void printActiveUsers(map<string, User> aMap) {
    int activeThreshold = 800;
    for (auto it = aMap.cbegin(); it != aMap.cend(); it++)
    {
        if(it->second.numPosts > activeThreshold)
        {
            cout << it->second.userName << "is an active user" << endl;
        }
    }
}


void printMostPopularCategory(map<string, User> aMap) {   
    map<string, int> categoryMap;
    for (const auto& pair : aMap) {
        string category = pair.second.mostViewedCategory;

        auto it = categoryMap.find(category);
        if (it != categoryMap.end())
        {
            it->second++;
        }
        else
        {
            categoryMap[category] = 1;
        }
        
    }
    string mostPopular;
    int highestCount = 0;
    for (const auto& pair : categoryMap) {
        if (pair.second > highestCount) {
            highestCount = pair.second;
            mostPopular = pair.first;
        }
    }

    cout << "most popular is: " << mostPopular << endl;

}


int main()
{
    int numUsers = 5;
    vector<User> users = generateUsers(numUsers);


    cout << "Build map with username as key" << endl;
    map<string, User> mapByUserName = buildMapByUserName(users);
    if ( mapByUserName.size() == numUsers )
        cout << "  Built successfully." << endl << endl;
    else
        cout << "  Built unsuccessfully." << endl << endl;


    cout << "Print \"mapByUserName\" map:" << endl;
    printMap(mapByUserName);
    cout << endl;


    string keyToSearch = "smith55";
    cout << "Search by key: mapByUserName[\"" << keyToSearch << "\"]" << endl;
    if ( testSearchByKey(mapByUserName, keyToSearch) )
        cout << "  Search successfully." << endl << endl;
    else
        cout << "  Search unsuccessfully." << endl << endl;


    string keyToDelete = "smith55";
    cout << "Delete by key: \"" << keyToDelete << "\"" << endl;
    if ( testDeleteByKey(mapByUserName, keyToDelete) )
        cout << "  Delete successfully." << endl << endl;
    else
        cout << "  Delete unsuccessfully." << endl << endl;


    cout << "Test if map's key is sorted" << endl;
    if ( isMapSorted(mapByUserName) )
        cout << "  Order test passed!" << endl << endl;
    else
        cout << "  Order test failed!" << endl << endl;


    cout << "Print usernames with more than 800 tweets:" << endl;
    printActiveUsers(mapByUserName);
    cout << endl;

    cout << "Print the most popular category" << endl;
    printMostPopularCategory(mapByUserName);
    cout << endl;


    cout << " ============================================================================== " << endl << endl;


    cout << "Build map with username as key" << endl;
    map<string, User> mapByEmail = buildMapByEmail(users);
    if ( mapByEmail.size() == numUsers )
        cout << "  Built successfully." << endl << endl;
    else
        cout << "  Built unsuccessfully." << endl << endl;
    

    keyToSearch = "kat@gmail.com";
    cout << "Search by key: mapByEmail[\"" << keyToSearch << "\"]" << endl;
    if ( testSearchByKey(mapByEmail, keyToSearch) )
        cout << "  Search successfully." << endl << endl;
    else
        cout << "  Search unsuccessfully." << endl << endl;


    keyToDelete = "kat@gmail.com";
    cout << "Delete by key: \"" << keyToDelete << "\"" << endl;
    if ( testDeleteByKey(mapByEmail, keyToDelete) )
        cout << "  Delete successfully." << endl << endl;
    else
        cout << "  Delete unsuccessfully." << endl << endl;


    return 0;
}