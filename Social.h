#pragma once
#include <string>
#include <vector>
#include <memory>

class Social
{
public:
    Social() = default;

    void addUser(const std::string& name);

    void addConnection(const std::string& nameUser, const std::string& nameFriend);

    void searchSocialConnections(int handshake);

    void show();

    ~Social() = default;

private:
    class Connection;

    class User
    {
    public:
        User() = default;

        User(const std::string& name) : name_(name), connectionsData() {}

        ~User() = default;

        std::string name_;

        std::vector <Connection> connectionsData;
    };

    class Connection
    {
    public:
        Connection() = default;

        Connection(const std::shared_ptr<User> connection) : connection_(connection) {}

        ~Connection() = default;

        std::shared_ptr<User> connection_ = nullptr;
    };

    std::vector <User> usersData;

    std::shared_ptr<User> user_ = nullptr;

    std::shared_ptr<User> getCheckUser(const std::string& name);

    bool isConnection(const std::string& nameUser, const std::string& nameFriend);

    void findSocialConnections(const std::shared_ptr<User> nameUser, const std::shared_ptr<User> nameFriend,
                               std::vector<Connection>& visited, int countHandshake, int& handshakeMax);
};