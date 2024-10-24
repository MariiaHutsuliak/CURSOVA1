#include "Admin.h"

Admin::Admin() : userName{"None"}, password{"None"}, role{AdminRole::VIEWER} {}

Admin::Admin(const std::string &userName, const std::string &password, AdminRole role)
        : userName{userName}, password{password}, role{role} {}

Admin::Admin(const Admin &other)
        : userName{other.userName}, password{other.password}, role{other.role} {}

Admin::Admin(Admin &&other) noexcept
        : userName{std::move(other.userName)}, password{std::move(other.password)}, role{other.role} {}

Admin &Admin::operator=(const Admin &other) {
    if (this == &other) {
        return *this;
    }
    userName = other.userName;
    password = other.password;
    role = other.role;
    return *this;
}

// Move assignment operator
Admin &Admin::operator=(Admin &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    userName = std::move(other.userName);
    password = std::move(other.password);
    role = other.role;
    return *this;
}

Admin::~Admin() {}

const std::string &Admin::getUserName() const {
    return userName;
}

void Admin::setUserName(const std::string &userName) {
    Admin::userName = userName;
}

const std::string &Admin::getPassword() const {
    return password;
}

void Admin::setPassword(const std::string &password) {
    Admin::password = password;
}

AdminRole Admin::getRole() const {
    return role;
}

void Admin::setRole(AdminRole role) {
    this->role = role;
}

void Admin::getDataFromObject(std::ostream &os) const {
    os << userName << std::endl;
    os << password << std::endl;
    os << static_cast<int>(role) << std::endl;
}

void Admin::setDataToObject(std::istream &is) {
    std::string currentLine;
    std::getline(is, currentLine);
    userName = currentLine;
    std::getline(is, currentLine);
    password = currentLine;
    int roleInt;
    is >> roleInt;
    role = static_cast<AdminRole>(roleInt);
}
