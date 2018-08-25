#include <eosiolib/eosio.hpp>
#include <string>
#include <vector>
#include <set>

class cont : eosio::contract
{
public:

    cont(account_name self)
    :   contract(self),
        _stmp(self, self)
    {
        eosio::print("ctor\t");
    }

    ~cont()
    {
        eosio::print("dtor\t");
    }

    void hi()
    {
        eosio::print("hi\t");
    }

    void init()
    {
        _stmp.emplace(_self, [&](auto &m){
            m.id = 0;
            m.vec.push_back(0);
            m.set.insert("init\t");
        });
    }
    

    void getstat()
    {
        auto itr = _stmp.find(0);

        eosio::print("vec size: ", itr->vec.size(), "\t");
        for (auto veccitr = itr->vec.cbegin(); veccitr != itr->vec.end(); ++veccitr)
        {
            eosio::print(*veccitr, " ");
        }
        eosio::print("\t");

        eosio::print("set size: ", itr->set.size(), "\t");
        for (auto setcitr = itr->set.cbegin(); setcitr != itr->set.end(); ++setcitr)
        {
            eosio::print(*setcitr, " ");
        }
        eosio::print("\t");
    }


    void add(std::string str)
    {
        auto itr = _stmp.find(0);
         
        _stmp.modify(itr, _self, [&](auto &m){
            m.vec.push_back(str.size());
            m.set.insert(str);
        });
        eosio::print("inserted ", str, "\t");
    }

private:

    struct stmp
    {
        uint64_t id;
        std::vector<int> vec;
        std::set<std::string> set;
        
        uint64_t primary_key() const { return id; }
    };
    typedef eosio::multi_index<N(stmp), stmp> stmp_t;

    stmp_t _stmp;
};


EOSIO_ABI(::cont, (hi)(init)(getstat)(add))
