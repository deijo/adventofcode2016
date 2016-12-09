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
    qDebug() << "Advent of code #7";
    qDebug() << "=================" << endl;

    QStringList rawData = readFile("../AdventureNbr_7/puzzelinput.in");
    //QStringList rawData = readFile("../AdventureNbr_7/testinput.in");

    // Size of display
    int colDisp = 50;
    int rowDisp = 6;
    //int colDisp = 7;
    //int rowDisp = 3;

    QChar display[colDisp][rowDisp];

    // init

    for (int col = 0 ; col < colDisp ; col++)
    {
        for (int row = 0 ; row<rowDisp ; row++)
        {
            display[col][row] = '.';
        }
    }

    foreach( QString instruction, rawData)
    {
        QStringList parts = instruction.split(" ");

        if (parts.size() == 2 && parts[0] == "rect") // rect AxB
        {
            QStringList size = parts[1].split("x");
            int xSize = size[0].toInt();
            int ySize = size[1].toInt();

            for (int col = 0 ; col < xSize ; col++)
            {
                for (int row = 0 ; row<ySize ; row++)
                {
                    display[col][row] = '#';
                }

            }
//            qDebug() << instruction << endl;
//            for (int row = 0 ; row< rowDisp ; row++)
//            {
//                QString println;
//                for (int col = 0 ; col < colDisp ; col++)
//                {
//                    println.append(display[col][row]);
//                }
//                qDebug() << println;
//            }
//            qDebug() << endl;
        }
        else if (parts.size() == 5 && parts[0] == "rotate") // rotate row|column x=A by B
        {
            QStringList tmp = parts[2].split("=");
            int pos = tmp[1].toInt();
            int steps = parts[4].toInt();

            if (parts[1] == "row")
            {
                steps %= colDisp;

                QChar tmp[colDisp];
                for(int i = 0 ; i<colDisp ; i++)
                {
                    tmp[(i+steps)%colDisp] = display[i][pos];
                }

                // Update display
                for(int i = 0 ; i<colDisp ; i++)
                {
                    display[i][pos] = tmp[i];
                }

//                qDebug() << instruction << endl;
//                for (int row = 0 ; row< rowDisp ; row++)
//                {
//                    QString println;
//                    for (int col = 0 ; col < colDisp ; col++)
//                    {
//                        println.append(display[col][row]);
//                    }
//                    qDebug() << println;
//                }
//                qDebug() << endl;
            }
            else if (parts[1] == "column")
            {
                steps %= rowDisp;

                QChar tmp[rowDisp];
                for(int i = 0 ; i<rowDisp ; i++)
                {
                    tmp[(i+steps)%rowDisp] = display[pos][i];
                }

                // Update display
                for(int i = 0 ; i<rowDisp ; i++)
                {
                    display[pos][i] = tmp[i];
                }

//                qDebug() << instruction << endl;
//                for (int row = 0 ; row< rowDisp ; row++)
//                {
//                    QString println;
//                    for (int col = 0 ; col < colDisp ; col++)
//                    {
//                        println.append(display[col][row]);
//                    }
//                    qDebug() << println;
//                }
//                qDebug() << endl;
            }
            else
            {
                qDebug() << "BAD INPUT for rotate" << endl;
            }
        }
        else
        {
            qDebug() << "BAD COMMAND" << endl;
        }
    }
    int pixelslit = 0;

    qDebug() << endl;
    qDebug() << "=================================";
    qDebug() << "****   Day 7, part 1 answer  ****";
    qDebug() << "=================================" << endl;
    qDebug() << "Display: ";
    for (int row = 0 ; row< rowDisp ; row++)
    {
        QString println;
        for (int col = 0 ; col < colDisp ; col++)
        {
            println.append(display[col][row]);
            if (display[col][row] == '#')
            {
                pixelslit++;
            }

        }
        qDebug() << println;
    }
    qDebug() << endl;
    qDebug() << "Pixels lit: " << pixelslit << endl;
    qDebug() << endl;


    return 0;
}
