#ifndef USER_H
#define USER_H

#include <QVector>

struct UserInfo{
    QString userId;
    QString pwd;
    QString name;
    QString roomId;
    UserInfo(const QString &userId, const QString &pwd, const QString &name, const QString &roomId):userId(userId),pwd(pwd),name(name),roomId(roomId){}
};

class User{
public:
    explicit User(){
        m_vUser.append(new UserInfo("10000", "pass", "User_A", "10000"));
        m_vUser.append(new UserInfo("10001", "pass", "User_B", "10001"));
        m_vUser.append(new UserInfo("10002", "pass", "User_C", "10002"));
        m_vUser.append(new UserInfo("10003", "pass", "User_D", "10003"));
        m_vUser.append(new UserInfo("10004", "pass", "User_E", "10004"));
    }

    inline bool isExsit(const QString &userId)const{
        for (int i = 0; i < m_vUser.size(); i++){
            if (userId == m_vUser.at(i)->userId){
                return true;
            }
        }
        return false;
    }

    inline QString name(const QString &userId)const{
        for (int i = 0; i < m_vUser.size(); i++){
            if (userId == m_vUser.at(i)->userId){
                return m_vUser.at(i)->name;
            }
        }
        return "";
    }

    inline QString roomId(const QString &userId)const{
        for (int i = 0; i < m_vUser.size(); i++){
            if (userId == m_vUser.at(i)->userId){
                return m_vUser.at(i)->roomId;
            }
        }
        return "";
    }

    inline bool log(const QString &userId, const QString &pass){
        for (int i = 0; i < m_vUser.size(); i++){
            if (userId == m_vUser.at(i)->userId && pass == m_vUser.at(i)->pwd){
                return true;
            }
        }
        return false;
    }

private:
    QVector<UserInfo *> m_vUser;

};

#endif // USER_H
