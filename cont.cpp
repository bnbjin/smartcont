#include "cont.hpp"


cont::cont(account_name self)
:   contract(self),
    _stmp(self, self)
{
    eosio::print("ctor\t");
}

cont::~cont()
{
    eosio::print("dtor\t");
}

void cont::hi()
{
    eosio::print("hi\t");
}

void cont::init()
{
    _stmp.emplace(_self, [&](auto &m){
        m.id = 0;
        m.vec.push_back(0);
        m.set.insert("init\t");
    });
}


void cont::getstat()
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


void cont::add(std::string str)
{
    auto itr = _stmp.find(0);
     
    _stmp.modify(itr, _self, [&](auto &m){
        m.vec.push_back(str.size());
        m.set.insert(str);
    });
    eosio::print("inserted ", str, "\t");
}


EOSIO_ABI(::cont, (hi)(init)(getstat)(add))
