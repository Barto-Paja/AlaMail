#include "querybank.h"

QString QueryBank::vLogin = NULL;

QueryBank::QueryBank()
{

}

QueryBank::~QueryBank()
{
    if(db.isOpen())
    {
        db.close();
        db = QSqlDatabase();
    }
    db.removeDatabase("db");
}

bool QueryBank::isOpen()
{
    if(!db.isOpen())
    {
        db = QSqlDatabase::addDatabase("QOCI","db");
        db.setHostName("localhost");
        db.setDatabaseName("XE");
        db.setUserName("system");
        db.setPassword("SYSTEM");
    }

    query = new QSqlQuery(db);

    if(db.open())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool QueryBank::Login(QString login, QString password)
{

    if(db.isOpen()) {
        query->prepare("SELECT * FROM USERS_ALAMAIL WHERE USERNAME = :login AND PASSWORD = :password");
        query->bindValue(":login",login);
        query->bindValue(":password",password);
        query->exec();
        if(query->next())
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    else
      return false;
}

QString QueryBank::userInfo(int value)
{

    if(db.isOpen()){

        query->prepare("SELECT * FROM USERS_ALAMAIL WHERE USERNAME = :login");
        query->bindValue(":login",vLogin);
        query->exec();
    if(query->next())
    {
        QString result = query->value(value).toString();
        return result;
    }

    };

    return "";
}

void QueryBank::setLogin(QString login)
{
    vLogin = login;
}

QString QueryBank::getLogin() const
{
    return vLogin;
}

bool QueryBank::isUserExist(QString nLogin)
{
    query->prepare("SELECT USERNAME FROM USERS_ALAMAIL WHERE USERNAME = :login");
    query->bindValue(":login",nLogin);
    query->exec();

    if(vLogin==nLogin)
    {
        return false;
    }
    else if(query->next())
    {
        if(query->value(0).toString().isNull())
            return true;
    }
    else
        return false;

    return false;
}

bool QueryBank::isUserExs(QString nLogin)
{
    query->prepare("SELECT USERNAME FROM USERS_ALAMAIL WHERE USERNAME = :login");
    query->bindValue(":login",nLogin);
    query->exec();

    if(query->next())
    {
            if(query->value(0).toString().isNull())
                return true;
    }
}

void QueryBank::updateUser(QString pEmail, QString pLogin, QString pName, QString pSurname, int pidS)
{
    query->prepare("UPDATE USERS_ALAMAIL SET EMAIL = :email WHERE USERNAME = :login");
    query->bindValue(":email",pEmail);
    query->bindValue(":login",vLogin);
    query->exec();

    query->prepare("UPDATE USERS_ALAMAIL SET NAZWISKO = :name WHERE USERNAME = :login");
    query->bindValue(":name",pName);
    query->bindValue(":login",vLogin);
    query->exec();

    query->prepare("UPDATE USERS_ALAMAIL SET IMIE = :surname WHERE USERNAME = :login");
    query->bindValue(":surname",pSurname);
    query->bindValue(":login",vLogin);
    query->exec();

    query->prepare("UPDATE USERS_ALAMAIL SET USERNAME = :newlogin WHERE USERNAME = :login");
    query->bindValue(":newlogin",pLogin);
    query->bindValue(":login",vLogin);
    query->exec();

    query->prepare("UPDATE USERS_ALAMAIL SET ID_PRZEDMIOTU = :ids WHERE USERNAME = :login");
    query->bindValue(":ids",pidS);
    query->bindValue(":login",vLogin);
    query->exec();

    vLogin = pLogin;
}

bool QueryBank::isAdmin()
{
    query->prepare("SELECT * FROM USERS_ALAMAIL WHERE USERNAME = :name AND ID_FLAG = '1'");
    query->bindValue(":name",vLogin);
    query->exec();
    if(query->next())
    {
        return true;
    }
}

bool QueryBank::isModer()
{
    query->prepare("SELECT * FROM USERS_ALAMAIL WHERE USERNAME = :name AND ID_FLAG = '2'");
    query->bindValue(":name",vLogin);
    query->exec();
    if(query->next())
    {
        return true;
    }
}

bool QueryBank::isUser()
{
    query->prepare("SELECT * FROM USERS_ALAMAIL WHERE USERNAME = :name AND ID_FLAG = '3'");
    query->bindValue(":name",vLogin);
    query->exec();
    if(query->next())
    {
        return true;
    }
}

bool QueryBank::isBanned()
{
    query->prepare("SELECT * FROM USERS_ALAMAIL WHERE USERNAME = :name AND ID_FLAG = '4'");
    query->bindValue(":name",vLogin);
    query->exec();
    if(query->next())
    {
        return true;
    }
}

void QueryBank::updateLvlUser(QString login, QString flag)
{
    query->prepare("UPDATE USERS_ALAMAIL SET ID_FLAG = :flag WHERE USERNAME = :name");
    query->bindValue(":flag",flag);
    query->bindValue(":name",login);
    query->exec();
}

void QueryBank::closeDB()
{
    if(db.isOpen())
    {
        db.close();
        db = QSqlDatabase();
    }
    db.removeDatabase("db");
}

void QueryBank::setQModel(QSqlQueryModel &qmodel)
{
    qmodel.setQuery(*query);
}

void QueryBank::loadMyClass()
{
    int id = -1;
    query->prepare("SELECT ID FROM USERS_ALAMAIL WHERE USERNAME = :login");
    query->bindValue(":login",vLogin);
    query->exec();
    if(query->next())
        id=query->value(0).toInt();

    query->prepare("SELECT NAZWISKO, IMIE, ID_UCZNIA FROM UCZNIOWIE INNER JOIN GRUPY ON UCZNIOWIE.ID_GRUPY = GRUPY.ID_GRUPY WHERE GRUPY.ID_PRACOWNIKA = :id ORDER BY NAZWISKO ");
    query->bindValue(":id",id);
    query->exec();

}

QString QueryBank::selectedRecord(int i, int v, QString f)
{
    if(f=="s")
    {
        query->prepare("SELECT * FROM UCZNIOWIE WHERE ID_UCZNIA = :id");
        query->bindValue(":id",i);
        query->exec();
        if(query->next())
        {
        QString result = query->value(v).toString();
        return result;
        }
    }
    else if(f=="g")
    {
        query->prepare("SELECT * FROM GRUPY WHERE ID_GRUPY = :id");
        query->bindValue(":id",i);
        query->exec();
        if(query->next())
        {
        QString result = query->value(v).toString();
        return result;
        }
    }
    else if(f=="t")
    {
        query->prepare("SELECT * FROM USERS_ALAMAIL WHERE USERS_ALAMAIL.ID = :id");
        query->bindValue(":id",i);
        query->exec();
        if(query->next())
        {
        QString result = query->value(v).toString();
        return result;
        }
    }
    else if(f=="sb")
    {
        query->prepare("SELECT * FROM STANOWISKA WHERE ID_STANOWISKA = :id");
        query->bindValue(":id",i);
        query->exec();
        if(query->next())
        {
        QString result = query->value(v).toString();
        return result;
        }
    }

    return "";

}

void QueryBank::loadStudents()
{
    query->prepare("SELECT UCZNIOWIE.ID_UCZNIA, IMIE,NAZWISKO,MIASTO,ULICA,KOD_POCZTOWY,IMIE_MATKI,TELEFON_MATKI,IMIE_OJCA,TELEFON_OJCA, GRUPY.NAZWA_GRUPY, GRUPY.ID_GRUPY FROM UCZNIOWIE INNER JOIN GRUPY ON UCZNIOWIE.ID_GRUPY = GRUPY.ID_GRUPY");
    //query->prepare("SELECT UCZNIOWIE.ID_UCZNIA, IMIE,NAZWISKO,MIASTO,ULICA,KOD_POCZTOWY,IMIE_MATKI,TELEFON_MATKI,IMIE_OJCA,TELEFON_OJCA, GRUPY.NAZWA_GRUPY, GRUPY.ID_GRUPY FROM UCZNIOWIE, GRUPY");
    query->exec();
}

void QueryBank::groupNames()
{
    query->prepare("SELECT GRUPY.NAZWA_GRUPY, GRUPY.ID_GRUPY FROM GRUPY");
    query->exec();

}

bool QueryBank::getGroupName(QString &stream, int &c)
{
    if(query->next())
    {
       stream = query->value(0).toString();
       c = query->value(1).toInt();
       return true;
    }
    else
    {
        return false;
    }
}

bool QueryBank::getIdGruop(int &idG, QString groupName)
{
    query->prepare("SELECT GRUPY.ID_GRUPY FROM GRUPY WHERE GRUPY.NAZWA_GRUPY = :nazwa");
    query->bindValue(":nazwa", groupName);
    if(query->next())
    {
       idG = query->value(0).toInt();
       return true;
    }
    else
    {
        return false;
    }
}

QString QueryBank::getThisGroupName(int idG)
{
    query->prepare("SELECT GRUPY.NAZWA_GRUPY FROM GRUPY WHERE GRUPY.ID_GRUPY = :idg");
    query->bindValue(":idg",idG);
    query->exec();
    if(query->next())
    {
        QString result = query->value(0).toString();
        return result;
    };

    return "";
}

bool QueryBank::addStudent(QString &surname, QString &name, QString &city, QString &street, QString &postcode, QString &snameM, QString &phoneM, QString &snameF, QString &phoneF, int &idG)
{
    // Example:
    //INSERT INTO "SYSTEM"."UCZNIOWIE" (IMIE, NAZWISKO, MIASTO, ULICA, KOD_POCZTOWY, IMIE_MATKI, TELEFON_MATKI, IMIE_OJCA, TELEFON_OJCA, ID_GRUPY) VALUES ('Nowy', 'Uczun', 'Kowalewo', 'Mickiewicza 2', '10-721', 'Oliwia', '729123012', 'Karol', '236710107', '2')

    query->prepare("INSERT INTO UCZNIOWIE (IMIE, NAZWISKO, MIASTO, ULICA, KOD_POCZTOWY, IMIE_MATKI, TELEFON_MATKI, IMIE_OJCA, TELEFON_OJCA, ID_GRUPY) VALUES "
                   "(:IMIE, :NAZWISKO, :MIASTO, :ULICA, :KOD_POCZTOWY, :IMIE_MATKI, :TELEFON_MATKI, :IMIE_OJCA, :TELEFON_OJCA, :ID_GRUPY)");
    query->bindValue(":IMIE",surname);
    query->bindValue(":NAZWISKO",name);
    query->bindValue(":MIASTO",city);
    query->bindValue(":ULICA",street);
    query->bindValue(":KOD_POCZTOWY",postcode);
    query->bindValue(":IMIE_MATKI",snameM);
    query->bindValue(":TELEFON_MATKI",phoneM);
    query->bindValue(":IMIE_OJCA",snameF);
    query->bindValue(":TELEFON_OJCA",phoneF);
    query->bindValue(":ID_GRUPY",idG);

    query->exec();
    if(query->isActive())
    {
        return true;
    }
    else
        return false;
}

bool QueryBank::delStudent(int idU)
{
    query->prepare("DELETE FROM UCZNIOWIE WHERE UCZNIOWIE.ID_UCZNIA = :id");
    query->bindValue(":id",idU);
    query->exec();
    if(query->isActive())
    {
        return true;
    }
    else
        return false;
}

bool QueryBank::updStudent(QString surname, QString name, QString city, QString street, QString postcode, QString snameM, QString phoneM, QString snameF, QString phoneF, int idG, int idU)
{
    query->prepare("UPDATE UCZNIOWIE SET IMIE = :sname, NAZWISKO = :name, MIASTO = :city, ULICA = :street, KOD_POCZTOWY = :postcode, IMIE_MATKI = :snamem, TELEFON_MATKI = :phonem, IMIE_OJCA = :snamef, TELEFON_OJCA = :phonef, ID_GRUPY = :idg WHERE UCZNIOWIE.ID_UCZNIA = :idu");

    query->bindValue(":sname", surname);
    query->bindValue(":name", name);
    query->bindValue(":city", city);
    query->bindValue(":street", street);
    query->bindValue(":postcode", postcode);
    query->bindValue(":snamem",snameM);
    query->bindValue(":phonem",phoneM);
    query->bindValue(":snamef",snameF);
    query->bindValue(":phonef",phoneF);
    query->bindValue("idg",idG);
    query->bindValue("idu",idU);

    query->exec();
    if(query->isActive())
        return true;
    else
        return false;

}

QString QueryBank::lastQuery()
{
    QString lastQ =( query->lastQuery() + " ");
    return lastQ;
}

QString QueryBank::lastError()
{
    QString error =( query->lastError().text() + " " + QString::number(query->lastError().number()));
    return error;
}

bool QueryBank::queryTest()
{
    if(query->isActive())
        return true;
    else
        return false;
}

QString QueryBank::columnName(int idC)
{
    query->prepare("SELECT * FROM UCZNIOWIE WHERE ROWNUM < 1");
    query->exec();
    QSqlRecord record = query->record();
    return QString (record.fieldName(idC));
}

void QueryBank::loadGroups()
{
    query->prepare("SELECT GRUPY.ID_GRUPY, EXTRACT(YEAR FROM DATA_ZALOZENIA) ||'-'|| EXTRACT(MONTH FROM DATA_ZALOZENIA), GRUPY.NAZWA_GRUPY, USERS_ALAMAIL.IMIE, USERS_ALAMAIL.NAZWISKO, USERS_ALAMAIL.ID FROM GRUPY INNER JOIN USERS_ALAMAIL ON GRUPY.ID_PRACOWNIKA = USERS_ALAMAIL.ID");
    query->exec();
}

bool QueryBank::delGroup(int idG)
{
    query->prepare("DELETE FROM GRUPY WHERE ID_GRUPY = :id");
    query->bindValue(":id",idG);
    query->exec();

    if(queryTest())
        return true;

    return false;
}

bool QueryBank::addGroup(QString date, QString groupName, int idW)
{
    // Example:
    // INSERT INTO "SYSTEM"."GRUPY" (DATA_ZALOZENIA, NAZWA_GRUPY, ID_PRACOWNIKA) VALUES (TO_DATE('2016-09-01 00:00:00', 'YYYY-MM-DD HH24:MI:SS'), 'D', '1')

    query->prepare("INSERT INTO GRUPY (DATA_ZALOZENIA, NAZWA_GRUPY, ID_PRACOWNIKA) VALUES (TO_DATE( '"+date+"', 'YYYY-MM'),'"+groupName+"', '"+QString::number(idW)+"')");

    //query->prepare("INSERT INTO GRUPY (DATA_ZALOZENIA, NAZWA_GRUPY, ID_PRACOWNIKA) VALUES (TO_DATE(':date', 'YYYY-MM'), ':name', ':idw')");

    //    query->bindValue(":date",date);
    //    query->bindValue(":name",groupName);
    //    query->bindValue(":worker",idW);

    query->exec();

    if(queryTest())
        return true;

    return false;
}

bool QueryBank::updGroup(QString date, QString groupName, int idW, int idG)
{
    // Example:
    // UPDATE "SYSTEM"."GRUPY" SET DATA_ZALOZENIA = TO_DATE('2016-09-02 00:00:00', 'YYYY-MM-DD HH24:MI:SS'), NAZWA_GRUPY = 'L', ID_PRACOWNIKA = '2' WHERE ROWID = 'AAAE5jAABAAALDBAAD' AND ORA_ROWSCN = '2721708'

    //query->prepare("UPDATE GRUPY SET DATA_ZALOZENIA = TO_DATE( '"+date+"', 'YYYY-MM'), NAZWA_GRUPY = '"+groupName+"', ID_PRACOWNIKA = '"+idW+"' WHERE ID_GRUPY = '"+idG+"'");

      query->prepare("UPDATE GRUPY SET ID_PRACOWNIKA = '"+QString::number(idW)+"' WHERE ID_GRUPY = "+QString::number(idG));
      query->exec();

      query->prepare("UPDATE GRUPY SET DATA_ZALOZENIA = TO_DATE( '"+date+"', 'YYYY-MM') WHERE ID_GRUPY = "+QString::number(idG));
      query->exec();

      query->prepare("UPDATE GRUPY SET NAZWA_GRUPY = '"+groupName+"' WHERE ID_GRUPY = '"+QString::number(idG)+"'");
      query->exec();


//    query->bindValue(":name",groupName);
//    query->bindValue(":worker",idW);
//    query->bindValue(":idg",idG);



    if(queryTest())
        return true;

    return false;
}

bool QueryBank::isNameExist(QString name)
{
    query->prepare("SELECT NAZWA_GRUPY FROM GRUPY WHERE NAZWA_GRUPY = :name");
    query->bindValue(":name",name);
    query->exec();

    if(query->next())
    {
        return true;
    };

    return false;

}

void QueryBank::workersNames()
{
    query->prepare("SELECT IMIE || ' ' || NAZWISKO,  USERS_ALAMAIL.ID FROM USERS_ALAMAIL");
    query->exec();
}

bool QueryBank::getworkersNames(QString &stream, int &idW)
{
    if(query->next())
    {
       stream = query->value(0).toString();
       idW = query->value(1).toInt();
       return true;
    }
    else
    {
        return false;
    }

}

void QueryBank::subjectsNames()
{
    query->prepare("SELECT * FROM STANOWISKA");
    query->exec();
}

bool QueryBank::getsubjectsNames(QString &stream, int &idS)
{
    if(query->next())
    {
       stream = query->value(1).toString();
       idS = query->value(0).toInt();
       return true;
    }
    else
    {
        return false;
    }
}

void QueryBank::loadTeachers()
{
    query->prepare("SELECT USERS_ALAMAIL.* , STANOWISKA.NAZWA FROM USERS_ALAMAIL  INNER JOIN STANOWISKA ON USERS_ALAMAIL.ID_PRZEDMIOTU = STANOWISKA.ID_STANOWISKA");
    //query->prepare("SELECT * FROM USERS_ALAMAIL");
    query->exec();
}

bool QueryBank::delTeacher(int idW)
{
    query->prepare("DELETE FROM USERS_ALAMAIL WHERE USERS_ALAMAIL.ID = :idu");
    query->bindValue(":idu",idW);
    query->exec();
}

bool QueryBank::addTeacher(QString username, QString password, QString email, QString surname, QString name, int idS)
{
    // Example:
    // INSERT INTO "SYSTEM"."USERS_ALAMAIL" (USERNAME, PASSWORD, EMAIL, IMIE, NAZWISKO, ID_PRZEDMIOTU) VALUES ('MarMar', 'Haslo', 'ona@ano.pl', 'Maria', 'Marynarska', '1')
    query->prepare("INSERT INTO USERS_ALAMAIL (USERNAME, PASSWORD, EMAIL, IMIE, NAZWISKO, ID_PRZEDMIOTU, ID_FLAG) VALUES (:username, :password, :email, :surname, :name, :ids, '3')");
    query->bindValue(":username",username);
    query->bindValue(":password",password);
    query->bindValue(":email",email);
    query->bindValue(":surname",surname);
    query->bindValue(":name",name);
    query->bindValue(":ids",idS);
    query->exec();

}

bool QueryBank::updTeacher(QString username, QString password, QString email, QString surname, QString name, int idS, int idW)
{
    query->prepare("UPDATE USERS_ALAMAIL SET USERNAME = :username WHERE USERS_ALAMAIL.ID = :idw");
    query->bindValue(":username",username);
    query->bindValue(":idw",idW);
    query->exec();

    query->prepare("UPDATE USERS_ALAMAIL SET PASSWORD = :password WHERE USERS_ALAMAIL.ID = :idw");
    query->bindValue(":password",password);
    query->bindValue(":idw",idW);
    query->exec();

    query->prepare("UPDATE USERS_ALAMAIL SET EMAIL = :email WHERE USERS_ALAMAIL.ID = :idw");
    query->bindValue(":email",email);
    query->bindValue(":idw",idW);
    query->exec();

    query->prepare("UPDATE USERS_ALAMAIL SET IMIE = :surname WHERE USERS_ALAMAIL.ID = :idw");
    query->bindValue(":surname",surname);
    query->bindValue(":idw",idW);
    query->exec();

    query->prepare("UPDATE USERS_ALAMAIL SET NAZWISKO = :name WHERE USERS_ALAMAIL.ID = :idw");
    query->bindValue(":name",name);
    query->bindValue(":idw",idW);
    query->exec();

    query->prepare("UPDATE USERS_ALAMAIL SET ID_PRZEDMIOTU = :ids WHERE USERS_ALAMAIL.ID = :idw");
    query->bindValue(":ids",idS);
    query->bindValue(":idw",idW);
    query->exec();

    if(queryTest())
        return true;

    return false;

}

void QueryBank::loadFlags()
{
    query->prepare("SELECT * FROM ADMINS_FLAGS");
    query->exec();
}

bool QueryBank::getflagsNames(QString &stream, int &idF)
{
    if(query->next())
    {
       stream = query->value(1).toString();
       idF = query->value(0).toInt();
       return true;
    }
    else
    {
        return false;
    }
}

bool QueryBank::isFlagExist(QString vf)
{
    query->prepare("SELECT * FROM ADMINS_FLAGS WHERE ID_FLAG = :vf");
    query->bindValue(":vf",vf);
    query->exec();
    if(query->next())
    {
        return true;
    }
    else
        return false;
}

void QueryBank::loadSubjects()
{
    query->prepare("SELECT * FROM STANOWISKA");
    query->exec();
}

bool QueryBank::delSubject(int idS)
{
    query->prepare("DELETE FROM STANOWISKA WHERE ID_STANOWISKA = :ids");
    query->bindValue(":ids",idS);
    query->exec();
}

bool QueryBank::addSubject(QString stream)
{
    // Example:
    // INSERT INTO "SYSTEM"."STANOWISKA" (NAZWA) VALUES ('Surdopedagogika')

    query->prepare("INSERT INTO STANOWISKA (NAZWA) VALUES (:name)");
    query->bindValue(":name",stream);
    query->exec();
}

bool QueryBank::updSubject(QString stream, int idS)
{
    query->prepare("UPDATE STANOWISKA SET NAZWA = :name WHERE ID_STANOWISKA = :ids");
    query->bindValue(":name",stream);
    query->bindValue(":ids",idS);
    query->exec();
}



