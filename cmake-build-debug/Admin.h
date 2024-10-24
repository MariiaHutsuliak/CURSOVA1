#ifndef CURSOVA_ADMIN_H
#define CURSOVA_ADMIN_H
#include "Serializable.h"
#include <string>

enum class AdminRole {
    ADMIN,
    VIEWER
};

class Admin: public Serializable {
private:
    std::string userName;
    std::string password;
    AdminRole role;

public:
    Admin();
    Admin(const std::string &userName, const std::string &password, AdminRole role = AdminRole::VIEWER); // Default role is VIEWER
    Admin(const Admin &other);
    Admin(Admin &&other) noexcept;
    Admin &operator=(const Admin &other);
    Admin &operator=(Admin &&other) noexcept;
    ~Admin();

    const std::string &getUserName() const;
    void setUserName(const std::string &userName);

    const std::string &getPassword() const;
    void setPassword(const std::string &password);

    AdminRole getRole() const;
    void setRole(AdminRole role);

    void getDataFromObject(std::ostream &os) const override;
    void setDataToObject(std::istream &is) override;

};


#endif //CURSOVA_ADMIN_H
