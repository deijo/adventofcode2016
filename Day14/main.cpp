#include <QCoreApplication>
#include <QDebug>
#include <QCryptographicHash>


int findKeys(QString salt, int partToMD5Iter)
{
    QVector<QString> keys;
    QVector<QString> generatedHashes;

    int index = 0;

    while (keys.size() < 64)
    {
        QString hashed;
        if (index > generatedHashes.size()-1)
        {
            QString indata = salt + QString::number(index);
            QByteArray ba(indata.toLocal8Bit());

            QByteArray tmp(QCryptographicHash::hash(ba, QCryptographicHash::Md5).toHex());
            for (int hashcount = 0 ; hashcount < partToMD5Iter ; hashcount++)
            {
                tmp = QCryptographicHash::hash(tmp, QCryptographicHash::Md5).toHex();
            }

            hashed = tmp;
            generatedHashes.append(hashed);
        }
        else
        {
            hashed = generatedHashes.at(index);
        }

        int cindex = hashed.indexOf(QRegExp("([a-f0-9])\\1\\1"));
        if (cindex > -1)
        {
            QString rxStr(hashed.at(cindex));
            rxStr.append("{5}");
            QRegExp rx(rxStr);

            for (int i = 1; i < 1000 ; i++)
            {
                QString nextFive;
                if ((index + i) > (generatedHashes.size()-1))
                {
                    QString newdata = salt + QString::number(index + i);
                    QByteArray ba(newdata.toLocal8Bit());

                    QByteArray tmp2(QCryptographicHash::hash(ba, QCryptographicHash::Md5).toHex());
                    for (int hashcount = 0 ; hashcount < partToMD5Iter ; hashcount++)
                    {
                        tmp2 = QCryptographicHash::hash(tmp2, QCryptographicHash::Md5).toHex();
                    }
                    nextFive =tmp2;

                    generatedHashes.append(nextFive);
                }
                else
                {
                    nextFive = generatedHashes.at(index + i);
                }

                if (nextFive.contains(rx))
                {
//                    qDebug() << "Tripple Index:" << index << ", " << hashed;
//                    qDebug() << "   Five index:" << index + i << ", " << nextFive << endl;
                    keys.append(hashed);
                    break;
                }
            }
        }

        index++;
    }
return --index;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int lastIndex = 0;
    QString testsalt = "abc";
    QString puzzlesalt = "yjdafjpo";

    qDebug() << "Advent of code #14";
    qDebug() << "==================" << endl;

    qDebug() << "Test with salt abc, part 1";
    qDebug() << "==========================";

    lastIndex = findKeys(testsalt, 0);

    qDebug() << "Index: " << lastIndex << endl;


    qDebug() << "=================================";
    qDebug() << "****  Day 14, part 1 answer  ****";
    qDebug() << "=================================";

    lastIndex = findKeys(puzzlesalt, 0);
    qDebug() << "Index: " << lastIndex << endl;

    qDebug() << "Test with salt abc, part 2";
    qDebug() << "==========================";

    lastIndex = findKeys(testsalt, 2016);

    qDebug() << "Index: " << lastIndex << endl;


    qDebug() << "=================================";
    qDebug() << "****  Day 14, part 2 answer  ****";
    qDebug() << "=================================";

    lastIndex = findKeys(puzzlesalt, 2016);
    qDebug() << "Index: " << lastIndex << endl;


    exit(1);
    return a.exec();
}
