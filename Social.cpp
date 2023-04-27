#include "Social.h"
#include <iostream>

std::shared_ptr<Social::User> Social::getCheckUser(const std::string& name)
{
    for (auto& user : usersData)
    {
        if (name == user.name_)
        {
            return std::make_shared<User>(user);
        }
    }
    return nullptr;
}

bool Social::isConnection(const std::string& nameUser, const std::string& nameFriend)
{
    user_ = getCheckUser(nameUser);
    for (auto& userFriend : user_->connectionsData)
    {
        if (getCheckUser(nameFriend)->name_ == userFriend.connection_->name_)
        {
            return true;
        }
    }
    return false;
}

void Social::addUser(const std::string& name)
{
    if (nullptr == getCheckUser(name))
    {
        usersData.emplace_back(name);
    }
    else
    {
        std::cout << "User " << name << " exists\n" << std::endl;
    }
}

void Social::addConnection(const std::string& nameUser, const std::string& nameFriend)
{
    if (nullptr == getCheckUser(nameUser) || nullptr == getCheckUser(nameFriend))
    {
        std::cout << "Error in entered data: " << nameUser << " or " << nameFriend << "\n" << std::endl;
        return;
    }
    if (false == isConnection(nameUser, nameFriend))
    { 
        for (auto& user : usersData)
        {
            if (nameUser == user.name_)
            {
                user_ = getCheckUser(nameFriend);
                user.connectionsData.emplace_back(user_);
            }
            if (nameFriend == user.name_)
            {
                user_ = getCheckUser(nameUser);
                user.connectionsData.emplace_back(user_);
            }
        }
    }
    else
    {
        std::cout << "There is a connection between " << nameUser << " and " << nameFriend << "\n" << std::endl;
    }
    user_ = nullptr;
}

void Social::searchSocialConnections(int handshake)
{
    int handshakeMax = handshake;
    int countHandshake = 0;
    std::vector<Connection> visited;
    visited.push_back(std::make_shared<User>(usersData.front()));

    for (auto& user : usersData)
    {
        bool vis = false;

        for (auto& visit : visited)
        {
            if (user.name_ == visit.connection_->name_)
            {
                vis = true;
            }
        }
        if (true == vis)
        {
            user_ = std::make_shared<User>(user);
            findSocialConnections(std::make_shared<User>(usersData.front()), user_, visited, countHandshake, handshakeMax);
        }
    }
    user_ = nullptr;
}

void Social::findSocialConnections(const std::shared_ptr<User> nameUser, const std::shared_ptr<User> nameFriend,
                                   std::vector<Connection>& visited, int countHandshake, int& handshakeMax)
{
    ++countHandshake;
    if (handshakeMax < countHandshake)
    {
        return;
    }

    for (auto& userFriend : nameFriend->connectionsData)
    {
        bool vis = false;
        for (auto& visit : visited)
        {
            if (userFriend.connection_->name_ == visit.connection_->name_)
            {
                vis = true;
            }
        }
        if (false == vis)
        {
            user_ = getCheckUser(userFriend.connection_->name_);
            visited.push_back(user_);
            std::cout << "(" << countHandshake << " handshake): " << nameUser->name_ << " - "
                      << userFriend.connection_->name_ << std::endl;
        }
    }
}

void Social::show()
{
    for (auto& user : usersData)
    {
        std::cout << user.name_ << ": ";
        
        for (auto& userFriend : user.connectionsData)
        {
            std::cout << " " << userFriend.connection_->name_ << ",";
        }
        std::cout << std::endl;
    }
}