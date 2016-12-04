#include <QDebug>
#include <QStringList>
#include <QFile>

int main(int argc, char *argv[])
{
    qDebug() << "Advent of code #3 A" << endl;
    qDebug() << "===================" << endl << endl;

    // Read file
    QFile file("../AdventureNbr_3/puzzeldata.in");
    // QFile file("../AdventureNbr_3/testdata.in");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error: " << file.errorString() << endl;
    }

    QTextStream in(&file);
    QList<QVector<int>> indata;

    while(!in.atEnd()) {
        QString line = in.readLine();
        QVector<int> vec;

        // Add to list but could do the solution direct
        line = line.simplified();
        line = line.trimmed();

        QStringList tmp = line.split(" ");

        vec.append(tmp[0].toInt());
        vec.append(tmp[1].toInt());
        vec.append(tmp[2].toInt());

        indata.append(vec);
    }
    file.close();


    int possibleTriangles = 0;
    int notPossibleTriangles = 0;

    for (int i = 0 ; i < indata.size() ; i++) {
        QVector<int> vec = indata.at(i);

        if ( ((vec[0] + vec[1]) > vec[2]) &&
                ((vec[0] + vec[2]) > vec[1]) &&
                ((vec[1] + vec[2]) > vec[0]) ) {
            possibleTriangles++;
        }
        else {
            notPossibleTriangles++;
        }
    }

    qDebug() << endl;
    qDebug() << "indata.size(): " << indata.size() << endl;
    qDebug() << "Result: " << possibleTriangles << " possible triangles." << endl;
    qDebug() << "Result: " << notPossibleTriangles << " NOT possible triangles." << endl;
    qDebug() << endl;
    qDebug() << "=================================" << endl;
    qDebug() << "****        END OF 3A        ****" << endl;
    qDebug() << "=================================" << endl;
    qDebug() << endl;

    qDebug() << "=================================" << endl;
    qDebug() << "****       START OF 3B       ****" << endl;
    qDebug() << "=================================" << endl;
    qDebug() << endl;


    possibleTriangles = 0;
    notPossibleTriangles = 0;

    for (int i = 0 ; i < indata.size() ; i += 3) {
        QVector<int> vec0 = indata.at(i);
        QVector<int> vec1 = indata.at(i+1);
        QVector<int> vec2 = indata.at(i+2);

        for (int col = 0 ; col < 3 ; col++) {
            if ( ((vec0[col] + vec1[col]) > vec2[col]) &&
                    ((vec0[col] + vec2[col]) > vec1[col]) &&
                    ((vec1[col] + vec2[col]) > vec0[col]) ) {
                possibleTriangles++;
            }
            else {
                notPossibleTriangles++;
            }
        }
    }


    qDebug() << endl;
    qDebug() << "indata.size(): " << indata.size() << endl;
    qDebug() << "Result: " << possibleTriangles << " possible triangles." << endl;
    qDebug() << "Result: " << notPossibleTriangles << " NOT possible triangles." << endl;
    qDebug() << endl;
    qDebug() << "=================================" << endl;
    qDebug() << "****        END OF 3B        ****" << endl;
    qDebug() << "=================================" << endl;
    qDebug() << endl;


    return 0;
}
