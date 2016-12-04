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
    qDebug() << "Advent of code #4" << endl;
    qDebug() << "=================" << endl << endl;

    QStringList rawData = readFile("../AdventureNbr_4/puzzeldata.in");
    // QStringList rawData = readFile("../AdventureNbr_4/testdata.in");
    // QStringList rawData = readFile("../AdventureNbr_4/testdata4B.in");

    int sumOfIds = 0;

    foreach (QString str, rawData) {
        // Setup all the data from input
        QStringList firstSplit = str.split("[");

        QString chkSum = firstSplit[1].trimmed();
        chkSum.remove(5,1); // remove "]"

        int pos = firstSplit[0].lastIndexOf("-");
        QString roomName = firstSplit[0].left(pos);
        QString encryptedRoomName = firstSplit[0].left(pos);

        roomName.replace("-", "");

        firstSplit[0].remove(0, pos+1);
        int id = firstSplit[0].toInt();

        // And.... Action - 4A
        QMap<QChar, int> contains;
        while (roomName.size() > 0) {
            contains.insert(roomName[0], roomName.count(roomName[0]));
            roomName.replace(roomName[0], "");
        }
        QString theCode;
        while ((contains.size() > 0) && (theCode.size() < 5)) {
            int maxvalue = 0;
            QChar c;
            foreach (int value, contains) {
                if (value > maxvalue) {
                    maxvalue = value;
                    c = contains.key(value);
                }
            }
            theCode += c;
            contains.remove(c);
        }
        // qDebug() << "theCode: " << theCode << " Checksum: " << chkSum;
        if (theCode == chkSum) {
            sumOfIds += id;
            // qDebug() << "TRUE id: " << id << " SUM: " << sumOfIds << endl;
        }
        else {
            // qDebug() << "FALSE id: " << id << " SUM: " << sumOfIds << endl;
        }

        // STOP Action - 4A

        // START ACTION - 4B
        // North is five letters, only decode those that start with five letters
        int nbrOfRot = id % 26;
        QString decrypted;
        foreach (QChar c, encryptedRoomName) {
            if ( '-' == c ) {
                decrypted += ' ';
            }
            else {
                int base = QChar('a').unicode();
                int cvalue = c.unicode();

                int newnc = cvalue - base + nbrOfRot;
                newnc %= 26;
                newnc += base;

                QChar nc(newnc);
                decrypted += nc;
            }
        }
        // qDebug() << "Decrypted: " << decrypted << endl;
        if (decrypted.startsWith("north")) {
            qDebug() << "=================================" << endl;
            qDebug() << "****   Day 4, part 2 answer  ****" << endl;
            qDebug() << "=================================" << endl;
            qDebug() << "Decrypted: " << decrypted << endl;
            qDebug() << "Section ID: " << id << endl;
            qDebug() << endl;
            break;
        }

    }

    qDebug() << endl;
    qDebug() << "=================================" << endl;
    qDebug() << "****   Day 4, part 1 answer  ****" << endl;
    qDebug() << "=================================" << endl;
    qDebug() << "Sum Of Ids: " << sumOfIds << endl;
    qDebug() << endl;


    return 0;
}
