#include "tubeDatabase.h"

#include <QCoreApplication>
#include <QSqlError>
#include <QSqlRecord>
#include <QDateTime>
#include <QDir>
#include <QDebug>

tubeDatabase::tubeDatabase(QObject *parent) : QObject(parent)
{

    dbDirPath = QCoreApplication::applicationDirPath() + "/database";
    dbFilePath = QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss") + ".db";
    QDir dir;
    if (!dir.exists(dbDirPath)) {
        dir.mkpath(dbDirPath);
    }

    m_dbFilePath = dbDirPath + "/" + dbFilePath;
    init();
    // 定时提交数据
    connect(&m_timer, &QTimer::timeout, this, &tubeDatabase::committubeDatabase);
    m_timer.setInterval(5000);
    m_timer.start();
}

tubeDatabase::~tubeDatabase()
{
    // 确保退出时提交所有数据，关闭数据库
    closeDatabase();
}

// 导出数据为csv格式
void tubeDatabase::exportData(QString &dbPath, QString &path, QString &table)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if(db.isOpen())
    {
        qDebug() << "数据库已打开";
    }
    if (!db.open()) {
        qCritical() << "Could not open tubedatabase!";
        QMessageBox::information(NULL, QStringLiteral("错误"),
                                 QStringLiteral("文件不能打开，请检查文件路径！"));
        return;
    }
    QSqlQuery query(db);
    query.exec("SELECT * FROM " + table);
    for (int i=0; i<query.record().count(); i++) {
        qDebug() << query.record().value(i);
    }

    exportModel = new QSqlTableModel(this);
    exportModel->setTable(table);
    exportModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    exportModel->select(); //选取整个表的所有行

    QStringList strList,fieldList;//记录数据库中的一行数据
    QString strString,fieldString;
    const QString FILE_PATH(path);

    QFile csvFile(FILE_PATH);
    QString csv_str(table+"\n");
    QSqlRecord sqlRecord(query.record());
    if (csvFile.open(QIODevice::ReadWrite))
    {
        //写入表头
        csvFile.write(csv_str.toUtf8()+"\n");   
        for(int i = 0; i < sqlRecord.count(); i++){
            fieldList.insert(i,sqlRecord.fieldName(i).toUtf8());
        }
        fieldString=fieldList.join(", ")+"\n";
        csvFile.write(fieldString.toUtf8());

        while (query.next()) {
            for(int j=0;j<exportModel->columnCount();j++)
            {
                strList.insert(j,query.value(j).toString());
            }
            strString = strList.join(", ")+"\n";
            strList.clear();
            csvFile.write(strString.toUtf8());
        }
        csvFile.close();
    }
    QMessageBox::information(NULL, QStringLiteral("导出"), QStringLiteral("文件导出完成"));
    init();
}

void tubeDatabase::init()
{
    m_tubeDatabase = QSqlDatabase::addDatabase("QSQLITE");
    m_tubeDatabase.setDatabaseName(m_dbFilePath);
    if (!m_tubeDatabase.open()) {
        qCritical() << "Could not open database!";
    }

    // 设置同步模式，提高IO效率
    m_tubeDatabase.exec("PRAGMA synchronous = NORMAL");
    m_tubeDatabase.exec("PRAGMA journal_mode = MEMORY");

    // 创建表
    QSqlQuery query(m_tubeDatabase);
    query.exec("CREATE TABLE force_sensor_data "
               "(time, "
               "fA, "
               "fB, "
               "fC, "
               "fD, "
               "fE, "
               "fF)");
    query.exec("CREATE TABLE tube_motion_parameter "
               "(time, "
               "velocityA, "
               "velocityB, "
               "velocityC, "
               "velocityD, "
               "velocityE, "
               "velocityF, "
               "torA, "
               "torB, "
               "torC, "
               "torD, "
               "torE, "
               "torF, "
               "curA, "
               "curB, "
               "curC, "
               "curD, "
               "curE, "
               "curF)");
    // 开启事务，提高IO效率
    m_tubeDatabase.transaction();

    // 插入数据的SQL
    m_SensorDataQuerry = QSqlQuery(m_tubeDatabase);
    m_SensorDataQuerry.prepare("INSERT INTO force_sensor_data (time, fA, fB, fC, fD, fE, fF) "
                                                        "VALUES (:time, :fA, :fB, :fC, :fD, :fE, :fF)");

    m_motionParameterQuerry = QSqlQuery(m_tubeDatabase);
    m_motionParameterQuerry.prepare("INSERT INTO tube_motion_parameter "
                                    "(time, velocityA, velocityB, velocityC, velocityD, velocityE, velocityF, torA, torB, torC, torD, torE, torF, curA, curB, curC, curD, curE, curF)"
                                    "VALUES "
                                    "(:time, :velocityA, :velocityB, :velocityC, :velocityD, :velocityE, :velocityF, :torA, :torB, :torC, :torD, :torE, :torF, :curA, :curB, :curC, :curD, :curE, :curF)");

}

void tubeDatabase::saveSensorData(Force ft)
{

    m_SensorDataQuerry.bindValue(":time", ft.time);
    m_SensorDataQuerry.bindValue(":fA", ft.FA);
    m_SensorDataQuerry.bindValue(":fB", ft.FB);
    m_SensorDataQuerry.bindValue(":fC", ft.FC);
    m_SensorDataQuerry.bindValue(":fD", ft.FD);
    m_SensorDataQuerry.bindValue(":fE", ft.FE);
    m_SensorDataQuerry.bindValue(":fF", ft.FF);
    if (!m_SensorDataQuerry.exec()) {
        qCritical() << "Insert data Error: " << m_tubeDatabase.lastError().text();
    }
    //m_tubeDatabase.close();
}

void tubeDatabase::savetubeMotionParameter(const tubeMotionParameter &mp)
{

    m_motionParameterQuerry.bindValue(":time", mp.time);
    m_motionParameterQuerry.bindValue(":velocityA", mp.velocityA);
    m_motionParameterQuerry.bindValue(":velocityB", mp.velocityB);
    m_motionParameterQuerry.bindValue(":velocityC", mp.velocityC);
    m_motionParameterQuerry.bindValue(":velocityD", mp.velocityD);
    m_motionParameterQuerry.bindValue(":velocityE", mp.velocityE);
    m_motionParameterQuerry.bindValue(":velocityF", mp.velocityF);
    m_motionParameterQuerry.bindValue(":torA", mp.torqueA);
    m_motionParameterQuerry.bindValue(":torB", mp.torqueB);
    m_motionParameterQuerry.bindValue(":torC", mp.torqueC);
    m_motionParameterQuerry.bindValue(":torD", mp.torqueD);
    m_motionParameterQuerry.bindValue(":torE", mp.torqueE);
    m_motionParameterQuerry.bindValue(":torF", mp.torqueF);
    m_motionParameterQuerry.bindValue(":curA", mp.currentA);
    m_motionParameterQuerry.bindValue(":curB", mp.currentB);
    m_motionParameterQuerry.bindValue(":curC", mp.currentC);
    m_motionParameterQuerry.bindValue(":curD", mp.currentD);
    m_motionParameterQuerry.bindValue(":curE", mp.currentE);
    m_motionParameterQuerry.bindValue(":curF", mp.currentF);
    bool ok = m_motionParameterQuerry.exec();
    if (!ok) {
        qCritical() << "Insert data Error: " << m_tubeDatabase.lastError().text();
    }
        //m_tubeDatabase.close();


}

void tubeDatabase::committubeDatabase()
{
    if(m_tubeDatabase.commit())
        qDebug() << "Success Commit!";
    else
        qCritical() << m_tubeDatabase.lastError();
    m_tubeDatabase.transaction();
}

void tubeDatabase::closeDatabase()
{

    m_tubeDatabase.commit();
    m_tubeDatabase.close();
}

void tubeDatabase::bootDatabase()
{
    if (!m_tubeDatabase.open()) {
        qCritical() << "Could not open database!";
    }

    // 设置同步模式，提高IO效率
    m_tubeDatabase.exec("PRAGMA synchronous = NORMAL");
    m_tubeDatabase.exec("PRAGMA journal_mode = MEMORY");
    m_tubeDatabase.transaction();
}

