#include <iostream>
#include <functional>
#include <vector>
#include <string>

using namespace std;
using namespace std::placeholders;


class Client1
{
public:
    void callback(int value) {
        cout << "Client1::callback(): value=" << value << endl;
    }
};

class Event
{
public:
    void event(int val) {
        cout << "Event with val=" << val << " triggered" << endl;
        for(auto fn : _callbacks)
            fn(val);
    }

    void registerCallback(function<void(int)> fn) {
        _callbacks.push_back(fn);
    }

private:
    vector<function<void(int)>> _callbacks;
    
};


int main()
{
    Event e;
    Client1 c1;
    e.registerCallback(bind(&Client1::callback,&c1,_1));
    e.event(10);

    return 0;
}


// reference: https://stackoverflow.com/questions/400257/how-can-i-pass-a-class-member-function-as-a-callback
/*
class RedundencyManager // incl. Typo ;-)
{
public:
    // std::function<return_type(list of argument_type(s))>
    std::string Init(std::function<std::string(void)> f) 
    {
        return f();
    }
};

class CLoggersInfra
{
private:
    std::string member = "Hello from non static member callback!";

public:
    static std::string RedundencyManagerCallBack()
    {
        return "Hello from static member callback!";
    }

    std::string NonStaticRedundencyManagerCallBack()
    {
        return member;
    }
};

std::string NonMemberCallBack()
{
    return "Hello from non member function!";
}

int main()
{
    auto instance = RedundencyManager();

    auto callback1 = std::bind(&NonMemberCallBack);
    std::cout << instance.Init(callback1) << "\n";

    // Similar to non member function.
    auto callback2 = std::bind(&CLoggersInfra::RedundencyManagerCallBack);
    std::cout << instance.Init(callback2) << "\n";

    // Class instance is passed to std::bind as second argument.
    // (heed that I call the constructor of CLoggersInfra)
    auto callback3 = std::bind(&CLoggersInfra::NonStaticRedundencyManagerCallBack,
                               CLoggersInfra()); 
    std::cout << instance.Init(callback3) << "\n";
}
*/
