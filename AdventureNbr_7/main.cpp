#include <QDebug>
#include <QStringList>
#include <QFile>
#include <QRegExp>

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

bool FindABBA(QVector<QString> input)
{
    bool found = false;
    foreach(QString tmp, input)
    {
        if (tmp.size() > 3)
        {
            for (int i = 1 ; i < tmp.size()-2 ; i++)
            {
                if ((tmp.at(i) == tmp.at(i+1)) &&
                        (tmp.at(i-1) == tmp.at(i+2)) &&
                        (tmp.at(i) != tmp.at(i-1) ))
                {
                    found = true;
                    qDebug() << "Found ABBA: " << tmp;
                }
            }
        }
    }
    return found;
}

bool FindSSL(QVector<QString> supernet, QVector<QString> hypernet)
{
    bool found = false;
    QVector<QString> searchPatterns;

    // Find "aba" pattern
    foreach(QString tmp, supernet)
    {
        if (tmp.size() > 2)
        {
            for (int i = 0 ; i < tmp.size()-2 ; i++)
            {
                if ((tmp.at(i) == tmp.at(i+2)) &&
                        (tmp.at(i) != tmp.at(i+1) ))
                {
                    QString res = QString(tmp.at(i+1)) + QString(tmp.at(i)) + QString(tmp.at(i+1));
                    searchPatterns.append(res);
                }
            }
        }
    }

    foreach(QString findStr, hypernet)
    {
        foreach(QString pattern, searchPatterns)
        {
            if (findStr.contains(pattern))
            {
                found = true;
            }
        }
    }

    return found;
}

int main(int argc, char *argv[])
{
    qDebug() << "Advent of code #7";
    qDebug() << "=================" << endl;

    QStringList rawData = readFile("../AdventureNbr_7/puzzelinput.in");
//    QStringList rawData = readFile("../AdventureNbr_7/testdata.in");
//    QStringList rawData = readFile("../AdventureNbr_7/testdata7b.in");

    int nbrOfIPsTLSSupport = 0;
    int nbrOfIPsSSLSupport = 0;

    foreach(QString TLSstr, rawData)
    {
        QStringList splitList = TLSstr.split(QRegExp("[\\[\\]]"));
        // qDebug() << TLSstr;
        // qDebug() << splitList;

        QVector<QString> hypernet;
        QVector<QString> supernet;

        for( int index = 0 ; index < splitList.size() ; index++ )
        {
            if (index % 2)
            {
                hypernet.append(splitList.at(index));
            }
            else
            {
                supernet.append(splitList.at(index));
            }
        }

        // Does it support TLS?
        // If ABBA in hypernet do not continue
        if (!FindABBA(hypernet))
        {
            if (FindABBA(supernet))
            {
                nbrOfIPsTLSSupport++;
//                qDebug() << TLSstr;
//                qDebug() << splitList;
//                qDebug() << "-----------------------" << endl;
            }

        }

        // SSL support
        if (FindSSL(supernet, hypernet))
        {
            nbrOfIPsSSLSupport++;
        }
    }

    qDebug() << "=================================";
    qDebug() << "****          Day 7          ****";
    qDebug() << "=================================" << endl;
    qDebug() << "Number of IPs with TLS: " << nbrOfIPsTLSSupport;
    qDebug() << "Number of IPs with SSL: " << nbrOfIPsSSLSupport;
    qDebug() << endl;

    return 0;
}
