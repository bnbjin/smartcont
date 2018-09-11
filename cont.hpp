#pragma once

#include <string>
#include <vector>
#include <set>

#include <eosiolib/eosio.hpp>


class cont : eosio::contract
{
public:

    cont(account_name self);

    ~cont();

    void hi();

    void init();

    void getstat();

    void add(std::string str);

private:

    /// @!abi table stmp i64
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
