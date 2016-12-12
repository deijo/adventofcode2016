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

int compute(QStringList &rawData, QMap<QChar, int> &registers)
{
    int index = 0;
    while(index < rawData.size())
    {
//        qDebug() << "--------------------";
//        qDebug() << rawData.at(index) << endl;

        bool ok;
        QStringList instruction = rawData.at(index).split(" ");
        if (instruction[0] == "cpy")
        {
            int value = instruction[1].toInt(&ok);
            if (ok)
            {
                registers.insert(instruction[2].at(0), value);
            }
            else
            {
                registers.insert(instruction[2].at(0), registers.value(instruction[1].at(0)));
            }
        }
        else if (instruction[0] == "inc")
        {
            registers.insert(instruction[1].at(0), registers.value(instruction[1].at(0)) + 1);
        }
        else if (instruction[0] == "dec")
        {
            registers.insert(instruction[1].at(0), registers.value(instruction[1].at(0)) - 1);
        }
        else if (instruction[0] == "jnz")
        {
            int ifJump = instruction[1].toInt(&ok);

            if (!ok)
            {
                ifJump = registers.value(instruction[1].at(0));
            }

            if (ifJump != 0 )
            {
                int jumpSteps = instruction[2].toInt(&ok);

                if (!ok)
                {
                    jumpSteps = registers.value(instruction[2].at(0));
                }

                index += jumpSteps;

                if (index < 0)
                    index = 0;

                continue;
            }

        }
        else
        {
            qDebug() << "Not correct output.";
        }

//        QMapIterator<QChar, int> i(registers);
//        while (i.hasNext()) {
//            i.next();
//            qDebug() << "Register: " << i.key() << ", value: " << i.value();
//        }
//        qDebug() << "Index: " << index << endl;

        index++;
    }
    return registers.value('a');
}

int main(int argc, char *argv[])
{
    qDebug() << "Advent of code #10";
    qDebug() << "==================" << endl;

    QStringList rawData = readFile("../Day12/puzzelinput");
    //QStringList rawData = readFile("../Day12/testinput");

    QMap<QChar, int> registers;

    registers.insert('a', 0);
    registers.insert('b', 0);
    registers.insert('c', 0); // Part 1
    registers.insert('d', 0);

    int resultPart1 = compute(rawData, registers);

    registers.insert('a', 0);
    registers.insert('b', 0);
    registers.insert('c', 1); // Part 2 init
    registers.insert('d', 0);

    int resultPart2 = compute(rawData, registers);


    qDebug() << "=================================";
    qDebug() << "****  Day 10, part 1 answer  ****";
    qDebug() << "=================================" << endl;
    qDebug() << "Answer is: " << resultPart1 << endl;

    qDebug() << "=================================";
    qDebug() << "****  Day 10, part 2 answer  ****";
    qDebug() << "=================================" << endl;
    qDebug() << "Answer is: " << resultPart2 << endl;

    return 0;
}
