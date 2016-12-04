#include <QDebug>
#include <QStringList>
#include <QFile>

int main(int argc, char *argv[])
{
    qDebug() << "Advent of code #2 A&B" << endl;
    qDebug() << "=====================" << endl << endl;

    // Read file
    QFile file("../AdventureNbr_2A/puzzeldata.in");
    // QFile file("../AdventureNbr_2A/testdata.in");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error: " << file.errorString() << endl;
    }

    QTextStream in(&file);
    QList<QString> indata;

    while(!in.atEnd()) {
        QString line = in.readLine();

        // Add to list but could do the solution direct
        line.trimmed();
        indata.append(line);
    }
    file.close();

    // num Pad
    int numPad2A[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    int hIndex = 1; // Start at 5
    int vIndex = 1; // Start at 5

    for (int i = 0 ; i<indata.size() ; i++) {

        QString str = indata.at(i);
        for (int j = 0; j < str.size(); j++) {
            QChar c = str.at(j);

            if (c == 'U') {
                vIndex--;
                if (vIndex < 0)
                    vIndex = 0;
            }
            else if (c == 'D') {
                vIndex++;
                if (vIndex > 2)
                    vIndex = 2;
            }
            else if (c == 'L') {
                hIndex--;
                if (hIndex < 0)
                    hIndex = 0;
            }
            else if (c == 'R') {
                hIndex++;
                if (hIndex > 2)
                    hIndex = 2;
            }
        }
        qDebug() << "Found digit: " << numPad2A[vIndex][hIndex] << endl;
    }
    qDebug() << endl;
    qDebug() << "=================================" << endl;
    qDebug() << "****        END OF 2A        ****" << endl;
    qDebug() << "=================================" << endl;
    qDebug() << endl;

    qDebug() << endl;
    qDebug() << "=================================" << endl;
    qDebug() << "****        START 2B         ****" << endl;
    qDebug() << "=================================" << endl;
    qDebug() << endl;

    // num Pad
    int numPad[7][7] = { {-1, -1, -1, -1, -1, -1, -1},
                         {-1, -1, -1, 49, -1, -1, -1},
                         {-1, -1, 50, 51, 52, -1, -1},
                         {-1, 53, 54, 55, 56, 57, -1},
                         {-1, -1, 65, 66, 67, -1, -1},
                         {-1, -1, -1, 68, -1, -1, -1},
                         {-1, -1, -1, -1, -1, -1, -1}
                       };
    vIndex = 3; // Start at 5 (53)
    hIndex = 1; // Start at 5 (53)

    for (int i = 0 ; i<indata.size() ; i++) {

        QString str = indata.at(i);
        for (int j = 0; j < str.size(); j++) {
            QChar c = str.at(j);

            if (c == 'U') {
                if (numPad[vIndex-1][hIndex] != -1) {
                    vIndex--;
                }
            }
            else if (c == 'D') {
                if (numPad[vIndex+1][hIndex] != -1) {
                    vIndex++;
                }
            }
            else if (c == 'L') {
                if (numPad[vIndex][hIndex-1] != -1) {
                    hIndex--;
                }
            }
            else if (c == 'R') {
                if (numPad[vIndex][hIndex+1] != -1) {
                    hIndex++;
                }
            }
        }
        qDebug() << "Found digit: " << QChar(numPad[vIndex][hIndex]) << endl;
    }
    qDebug() << endl;
    qDebug() << "=================================" << endl;
    qDebug() << "****        END OF 2B        ****" << endl;
    qDebug() << "=================================" << endl;
    qDebug() << endl;


    return 0;
}
