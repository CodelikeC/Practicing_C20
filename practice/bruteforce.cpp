#include <iostream> 
#include <chrono> 
#include <thread> 
#include <vector> 
#include <unordered_map>
using namespace std; 

// tao mot lop luu thong tin dang nhap va co the phat hien bruteforce..// 
class ComputerSystem
{
    private: 
    unordered_map<string, pair<int, chrono :: steady_clock :: time_point>> loginAttempts; 
    const int max_attempts = 3 ; 
    const chrono :: seconds lock_duration = chrono :: seconds(10) ; 

    public: 
    bool login(const string &username, const string &password)
    {
        // kiem tra xem co dang nhap hay khong..// 
        auto now = chrono :: steady_clock :: now();
        string key = username + password; 

        // kiem tra xem tai khoan bi khoa ..// 
        if (loginAttempts.find(key) != loginAttempts.end())
        {
            auto &[attempts, lastTime] = loginAttempts[key]; 
            auto timelapsed = chrono :: duration_cast<chrono :: seconds> (now - lastTime);
            if(attempts >= max_attempts and timelapsed < lock_duration)
            {
                cout <<"Account is locked. Try again" << endl; 
                cout << (lock_duration - timelapsed).count() << " seconds remaining" << endl; 
                return false; 
            }
            // neu het thoi gian khoa, reset so lan thu.. // 
            if (timelapsed >= lock_duration)
            {
                attempts = 0; 
            }
        }

        // gia lap kiem tra mat khau .. //
        string correctPassword = "password"; 
        if (password != correctPassword)
        {
            cout <<"Incorrect password. Try again" << endl; 
            loginAttempts[key].first++;
        }
        if (password == correctPassword)
        {
            cout <<"Login successful" << endl; 
            loginAttempts.erase(key);
            return true; 
        }

        // Tang so lan thu neu sai.. // 
        // if (loginAttempts[key].first >= max_attempts)
        // {
        //     cout << "Account is locked.Try again" << endl;
        //     loginAttempts[key].second = now; 
        // }

        if (loginAttempts.find(key) == loginAttempts.end())
        {
            loginAttempts[key] = {1, now} ;
        }
        else 
        {
            loginAttempts[key].first++; // tang so lan thu
            loginAttempts[key].second = now; // Cap nhat thoi gian thuc..// 

        }

        int attemptleft = max_attempts - loginAttempts[key].first;
        cout << "Wrong password" << "You have" << attemptleft << "attempts left :" << endl; 
        return false;  
    }
};


// ham main de chay chuong trinh .. 
int main ()
{
    ComputerSystem system; 
    string username = "fsociety"; 
    string password [] = {"wrong1", "wrong2", "wrong3", "password"}; 
    for (const auto &pwd :password)
    {
        cout <<"Thu dang nhap:" << pwd << endl; 
        system.login(username,pwd); 
        this_thread :: sleep_for(chrono :: seconds(1)); 
        cout << endl;
    }

    // thu lai sau khi bi khoa.. // 
    cout << "Thu lai sau 60 giay" << endl; 
    this_thread :: sleep_for(chrono :: seconds(60)); 
    system.login(username, "securepass123");
     
    return 0; 
    
}
