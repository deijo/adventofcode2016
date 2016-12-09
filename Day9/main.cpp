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

quint64 decompressString(QString line)
{
    QString currentDecLine = "";
    quint64 currentDecLen  = 0;
    int index = 0;
    int end = 0;

    int start = line.indexOf('(', index);
    while (start > -1)
    {
        currentDecLine.append(line.mid(index, start-index));
        currentDecLen += start - index;

        end = line.indexOf(')', start);
        QString decompCmd = line.mid( start+1, end-start-1);
        QStringList dim = decompCmd.split('x');
        int nextc = dim[0].toInt();
        int repeat = dim[1].toInt();

        QString inputStr = "";

        currentDecLine.append(line.mid(end+1, nextc));
        inputStr.append(line.mid(end+1, nextc));

        currentDecLen += (repeat * decompressString(inputStr));

        //        qDebug() << line.mid(end+1, nextc);
        //        qDebug() << "Repeat: " << repeat << "Total Length: " << nextc*repeat;

        index = end + nextc + 1;
        start = line.indexOf('(', index);
    }
    currentDecLine.append(line.mid(index, line.size()-index));
    currentDecLen += line.size()-index;

//    qDebug() << "Line: " << line;
//    qDebug() << "Decompressed line: " << currentDecLine;
    qDebug() << "Decompressed length: " << currentDecLen;
    qDebug() << "-----------------------------------" << endl;

    return currentDecLen;

}

int main(int argc, char *argv[])
{
    qDebug() << "Advent of code #9";
    qDebug() << "=================" << endl;

    QStringList rawData = readFile("../Day9/puzzelinput.in");
    //QStringList rawData = readFile("../Day9/testinput");
    //QStringList rawData = readFile("../Day9/testinput2");

    quint64 decompressedLength = 0;

    foreach(QString line, rawData)
    {
        // Some cleanup
        line = line.simplified();
        line.replace( " ", "" );

        quint64 lineLength = 0;
        lineLength = decompressString(line);
        decompressedLength += lineLength;

        qDebug() << "Line length: " << lineLength;
        qDebug() << "Accu length: " << decompressedLength;
        qDebug() << "========================" << endl;

//        // Start by dividing the text into smaler pieces
//        QStringList pieces;
//        int index = 0;
//        int end = 0;

//        int start = line.indexOf('(', index);
//        while (start > -1)
//        {
//            // currentDecLine.append(line.mid(index, start-index));
//            decompressedLength += start - index;

//            end = line.indexOf(')', start);
//            QString decompCmd = line.mid( start+1, end-start-1);
//            QStringList dim = decompCmd.split('x');
//            int nextc = dim[0].toInt();

//            pieces.append(QString(line.mid(start, end - start + 1 + nextc)));
//            qDebug() << line.mid(start, end - start + 1 + nextc);

//            index = end + nextc + 1;
//            start = line.indexOf('(', index);
//        }
//        // currentDecLine.append(line.mid(index, line.size()-index));
//        decompressedLength += (line.size()-index);

//        uint32_t lineLength = 0;
//        foreach(QString newLine, pieces)
//        {
//            lineLength = decompressString(line);
//            decompressedLength += lineLength;

//            qDebug() << "Line length: " << lineLength;
//            qDebug() << "Accu length: " << decompressedLength;
//            qDebug() << "------------------------" << endl;
//        }
    }

    qDebug() << endl;
    qDebug() << "=================================";
    qDebug() << "****   Day 9, part 2 answer  ****";
    qDebug() << "=================================" << endl;
    qDebug() << "Decompressed length: " << decompressedLength;

    return 0;
}
