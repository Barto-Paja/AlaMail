#ifndef QUERYBANK_H
#define QUERYBANK_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlRecord>

#include <QString>
#include <QMessageBox>

class QueryBank
{
public:

   QueryBank();
    ~QueryBank();

   bool isOpen();

//---- Profile GUI  1st part ----------------------

   bool Login(QString login, QString password);
   QString userInfo(int value);

   void setLogin(QString login);
   QString getLogin() const;

   bool isUserExist(QString nLogin);
   bool isUserExs(QString nLogin);
   void updateUser(QString pEmail, QString pLogin, QString pName, QString pSurname, int pidS);

   bool isAdmin();
   bool isModer();
   bool isUser();
   bool isBanned();

   void updateLvlUser(QString login, QString flag);

//--------------------------------------

   void closeDB(); // <-- Close DataBase Connection before create new Query Object

   void setQModel(QSqlQueryModel& qmodel);

//---- Classes GUI ---------------------

   void loadMyClass();
   QString selectedRecord(int i, int v, QString f);

   void loadStudents();
   void groupNames();
   bool getGroupName(QString &stream, int &c);
   bool getIdGruop(int& idG, QString groupName);
   QString getThisGroupName(int idG);

   bool addStudent(QString &surname, QString &name, QString &city, QString &street, QString &postcode, QString &snameM, QString &phoneM, QString &snameF, QString &phoneF, int &idG);
   bool delStudent(int idU);
   bool updStudent(QString surname, QString name, QString city, QString street, QString postcode, QString snameM, QString phoneM, QString snameF, QString phoneF, int idG, int idU);

//---- Query's statements ---------

   QString lastQuery();
   QString lastError();
   QString columnName(int idC);

//---- Groups GUI ------------------

   void loadGroups();

   bool delGroup(int idG);
   bool addGroup(QString date, QString groupName, int idW);
   bool updGroup(QString date, QString groupName, int idW, int idG);
   bool isNameExist(QString name);

   void workersNames();
   bool getworkersNames(QString &stream, int &idW);

//---- Profile GUI 2nd part --------

   void subjectsNames();
   bool getsubjectsNames(QString &stream, int &idS);

//---- Teachers GUI ----------------

   void loadTeachers();

   bool delTeacher(int idW);
   bool addTeacher(QString username, QString password, QString email, QString surname, QString name, int idS);
   bool updTeacher(QString username, QString password, QString email, QString surname, QString name, int idS, int idW);

//---- Flags management ----------------

   void loadFlags();
   bool getflagsNames(QString &stream, int &idF);
   bool isFlagExist(QString vf);

//---- Subjects GUI -----------------

   void loadSubjects();

   bool delSubject(int idS);
   bool addSubject(QString stream);
   bool updSubject(QString stream, int idS);

private:
    QSqlDatabase db;
    QSqlQuery *query;
//    QSqlQueryModel q_model;
//    QSqlTableModel *t_model;

    bool queryTest();

    static QString vLogin;
};

#endif // QUERYBANK_H
