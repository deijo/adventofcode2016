#include <QDebug>
#include <QStringList>
#include <QFile>

QStringList readFile(QString filename)
{
    // Read file
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error: " << file.errorString() << endl;
    }

    QTextStream in(&file);
    QStringList indata;

    while(!in.atEnd()) {
        indata.append(in.readLine());
    }
    file.close();

    return indata;
}

int main(int argc, char *argv[])
{
    qDebug() << "Advent of code #6";
    qDebug() << "=================" << endl;

    QStringList rawData = readFile("../AdventureNbr_6/puzzelinput.in");
    // QStringList rawData = readFile("../AdventureNbr_6/testdata.in");

    QMap<QChar, int> messageLetters[rawData[0].size()];

    foreach(QString tmpStr, rawData)
    {
        for(int index = 0 ; index < tmpStr.size() ; index++)
        {
            if (messageLetters[index].contains(tmpStr.at(index)))
            {
                messageLetters[index].insert(tmpStr[index], messageLetters[index].value(tmpStr[index]) + 1);
            }
            else
            {
                messageLetters[index].insert(tmpStr[index], 1);
            }
        }
    }

    QString messageMax;
    QString messageMin;

    for(int index = 0 ; index < rawData[0].size() ; index++)
    {
        QChar cmax;
        QChar cmin;
        int max = 0;
        int min = 10000;

        QList<QChar> keys = messageLetters[index].uniqueKeys();
        foreach( QChar key, keys)
        {
            if (messageLetters[index].value(key) > max)
            {
                max = messageLetters[index].value(key);
                cmax = key;
            }
            if (messageLetters[index].value(key) < min)
            {
                min = messageLetters[index].value(key);
                cmin = key;
            }
        }

        messageMax.append(cmax);
        messageMin.append(cmin);
    }


    qDebug() << endl;
    qDebug() << "=================================";
    qDebug() << "****   Day 4, part 1 answer  ****";
    qDebug() << "=================================" << endl;
    qDebug() << "Message max: " << messageMax;
    qDebug() << endl;
    qDebug() << "=================================";
    qDebug() << "****   Day 4, part 2 answer  ****";
    qDebug() << "=================================" << endl;
    qDebug() << "Message min: " << messageMin;
    qDebug() << endl;


    return 0;
}
