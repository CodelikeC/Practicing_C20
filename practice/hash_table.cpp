#include <iostream> 
using namespace std; 
#include <string> 

#include <algorithm> 
#include <unordered_map>
#include <list> 

#include <string> 
#include <openssl/sha.h>
#include <vector>


string hashPassword(const string &password)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char *> (password.c_str()), password.size(), hash); 

    string hashed_password; 
    for (int i = 0;  i< SHA256_DIGEST_LENGTH ; i++)
    {
        char buff[3]; 
        snprintf(buff, sizeof(buff), "%02f", hash[i]); 
        hashed_password += buff;
    }
    return hashed_password; 
}

// Node luu thong tin dang nhap / 
struct user
{
    string username ; 
    string hashed_password; 

    user(const string &u, const string &p) : username(u), hashed_password(hashPassword(p)){}

};

// hash table with seperate chaining..// 
class HashTable
{
    private: 
    static const int TABLE_SIZE  =  10; 
    // Kich thuoc cua bang bam.. // 
    vector<list<user>> table; 

    int hashFunction(const string &key)
    {
        size_t hashValue = 0; 
        for (char ch : key)
        {
            hashValue = (hashValue *31 + ch) % TABLE_SIZE;
        }
        return hashValue;
    }

    public: 
    HashTable () : table(TABLE_SIZE){}
    // add more user .. // 
    void insertUser(const string &username, const string &password)
    {
        int index = hashFunction(username); 
        for (auto &user : table[index])
        {
            if (user.username == username)
            {
                cout <<"The account is existed" << endl; 
                return; 
            }
        }
        table[index].emplace_back(username, password); 
        cout <<"The user are more added!" << username << endl; 
    }
    // kiem tra dang nhap .. / / 
    bool login(const string &username, const string &password)
    {
        int index = hashFunction(username); 
        string hashedPass = hashPassword(password); 
        for (auto & user : table[index])
        {
            if (user.username == username and user.hashed_password == password)
            {
                cout << "Successfully added" << endl;
                return true;  
            }
        }
        cout <<"The password was wrong" << endl; 
        cout << "The username was wrong" << endl; 
        return false; 
    }

    // xoa tai khoan (delete)
    void deleteAccount(const string &username)
    {
        int index = hashFunction(username);
        auto &chain = table[index]; // chaining 
        for (auto it = chain.begin() ;it != chain.end(); ++it)
        {
            if (it -> username== username)
            {
                chain.erase(it);
                cout <<"The account was deleted" << username << endl;
                return; 
            }
        }
        cout <<"Account 404 not found!" << endl; 
    }
}; 

int main ()
{
    HashTable ht; 
    ht.insertUser("admin", "password 123");
    ht.insertUser("user1", "password 456");

    ht.login("admin", "password 123"); // dung 
    ht.login("admin", "wrongpass"); // sai .. 

    ht.deleteAccount("user1"); 
    ht.login("user1" , "password 456"); // da bi xoa//

    return 0; 
}

