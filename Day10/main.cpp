#include <QDebug>
#include <QStringList>
#include <QFile>

struct Bot {
    int lowValueChip;
    int highValueChip;

    int giveLowValueChip;
    int giveHighValueChip;
};


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

void moveLowChip(Bot &src, Bot &dst)
{

    if (dst.lowValueChip == -1 && dst.highValueChip == -1)
    {
        dst.lowValueChip = src.lowValueChip;
    }
    else if ((src.lowValueChip > dst.lowValueChip) && (dst.highValueChip == -1))
    {
        dst.highValueChip = src.lowValueChip;
    }
    else if ((src.lowValueChip < dst.lowValueChip) && (dst.highValueChip == -1))
    {
        dst.highValueChip = dst.lowValueChip;
        dst.lowValueChip = src.lowValueChip;
    }
    else
    {
        qDebug() << "TRYING TO ADD VALUE TO FULL ITEM. MOVE LOW ITEM" << endl;
    }

    src.lowValueChip = -1;
}

void moveHighChip(Bot &src, Bot &dst)
{

    if (dst.lowValueChip == -1 && dst.highValueChip == -1)
    {
        dst.lowValueChip = src.highValueChip;
    }
    else if (src.highValueChip > dst.lowValueChip && dst.highValueChip == -1)
    {
        dst.highValueChip = src.highValueChip;
    }
    else if (src.highValueChip < dst.lowValueChip && dst.highValueChip == -1)
    {
        dst.highValueChip = dst.lowValueChip;
        dst.lowValueChip = src.highValueChip;
    }
    else
    {
        qDebug() << "TRYING TO ADD VALUE TO FULL ITEM. MOVE HIGH ITEM" << endl;
    }

    src.highValueChip = -1;
}

int findBot(int id, QMap<int, Bot> &bots, QMap<int, int> &output)
{
    int returnvalue = -1;
    int foundValueLow = 17;
    int foundValueHigh = 61;

    Bot bot = bots.value(id);
    if (bot.lowValueChip == foundValueLow && bot.highValueChip == foundValueHigh)
    {
        returnvalue = id;
    }
    Bot lowBot = bots.value(bot.giveLowValueChip);
    Bot highBot = bots.value(bot.giveHighValueChip);

    if (bot.giveLowValueChip < -1)
    {
        output.insert(-1*bot.giveLowValueChip-10, bot.lowValueChip);
        bot.lowValueChip = -1;
    }
    else
    {
        moveLowChip(bot, lowBot);
        bots.insert(bot.giveLowValueChip, lowBot);
    }

    if (bot.giveHighValueChip < -1)
    {
        output.insert(-1*bot.giveHighValueChip-10, bot.highValueChip);
        bot.highValueChip = -1;
    }
    else
    {
        moveHighChip(bot, highBot);
        bots.insert(bot.giveHighValueChip, highBot);
    }

    // Update bots
    bots.insert(id, bot);

    return returnvalue;
}


int main(int argc, char *argv[])
{
    qDebug() << "Advent of code #10";
    qDebug() << "==================" << endl;

    QStringList rawData = readFile("../Day10/puzzelinput");
    //QStringList rawData = readFile("../Day10/testinput");

    QMap<int, Bot> bots; // id, low value, high value
    QMap<int, int> output;

    // Init
    foreach(QString instruction, rawData)
    {
        QStringList instrList = instruction.split(" ");

        if (instrList[0] == "value")
        {
            int id = instrList[5].toInt();
            int value = instrList[1].toInt();

            if (bots.contains(id))
            {
                Bot currentValues = bots.value(id);

                if ((currentValues.lowValueChip == -1) && (currentValues.highValueChip == -1))
                {
                    currentValues.lowValueChip = value;
                    bots.insert(id, currentValues);
                }
                else if ((value > currentValues.lowValueChip) && (currentValues.highValueChip == -1))
                {
                    currentValues.highValueChip = value;
                    bots.insert(id, currentValues);
                }
                else if ((value < currentValues.lowValueChip) && (currentValues.highValueChip == -1))
                {
                    currentValues.highValueChip = currentValues.lowValueChip;
                    currentValues.lowValueChip = value;
                    bots.insert(id, currentValues);
                }
            }
            else
            {
                Bot tmp;
                tmp.lowValueChip = value;
                tmp.highValueChip = -1;
                tmp.giveLowValueChip = -1;
                tmp.giveHighValueChip = -1;

                bots.insert(id, tmp);
            }

        }
        else if (instrList[0] == "bot")
        {
            int id = instrList[1].toInt();
            int lowID = instrList[6].toInt();
            if (instrList[5] == "output")
            {
                lowID = -1*(lowID + 10);
            }

            int highID = instrList[11].toInt();
            if (instrList[10] == "output")
            {
                highID = -1*(highID + 10);
            }

            Bot bot;
            if (!bots.contains(id))
            {
                bot.lowValueChip = -1;
                bot.highValueChip = -1;
            }
            else
            {
                bot = bots.value(id);
            }

            bot.giveLowValueChip = lowID;
            bot.giveHighValueChip = highID;

            bots.insert(id, bot);
        }
        else
        {
            qDebug() << "COMMAND NOT FOUND" << endl;
        }
    }
    qDebug() << "Rules done";
    qDebug() << "----------" << endl;
    QMapIterator<int, Bot> i(bots);
    while (i.hasNext()) {
        i.next();
        qDebug() << "bot id: " << i.key() << ", low: " << i.value().lowValueChip << ", high: " << i.value().highValueChip <<
                    ", givelow: " << i.value().giveLowValueChip << ", giveHigh: " << i.value().giveHighValueChip;
    }
    qDebug() << endl;
    qDebug() << "Finding what to move";
    qDebug() << "--------------------" << endl;

    // Just find the numbers, part 1 17 and 61
    int foundIt = -1;

    while (true)
    {
        QVector<int> keys;
        QMapIterator<int, Bot> i(bots);
        while (i.hasNext())
        {
            i.next();

            if (i.value().lowValueChip != -1 && i.value().highValueChip != -1)
            {
                keys.append(i.key());
                qDebug() << "bot id: " << i.key() << ", low: " << i.value().lowValueChip << ", high: " << i.value().highValueChip <<
                            ", givelow: " << i.value().giveLowValueChip << ", giveHigh: " << i.value().giveHighValueChip;
            }
        }


        foreach(int id, keys)
        {
            if (foundIt == -1)
            {
                foundIt = findBot(id, bots, output);
            }
            else
            {
                findBot(id, bots, output);
            }
        }

        qDebug() << "--------------------" << endl;
        if (output.contains(0) && output.contains(1) && output.contains(2))
        {
            break;
        }
    }

    qDebug() << "=================================";
    qDebug() << "****  Day 10, part 1 answer  ****";
    qDebug() << "=================================" << endl;
    QMapIterator<int, Bot> b(bots);
    while (b.hasNext()) {
        b.next();
        qDebug() << "bot id: " << b.key() << ", low: " << b.value().lowValueChip << ", high: " << b.value().highValueChip <<
                    ", givelow: " << b.value().giveLowValueChip << ", giveHigh: " << b.value().giveHighValueChip;
    }

    QMapIterator<int, int> o(output);
    while (o.hasNext()) {
        o.next();
        qDebug() << "output id: " << o.key() << ", value " << o.value();
    }

    qDebug() << endl << "Bot that compare 17 and 61: " << foundIt << endl;
    qDebug() << "=================================";
    qDebug() << "****  Day 10, part 2 answer  ****";
    qDebug() << "=================================" << endl;
    qDebug() << "Multiplication is: " << output.value(0) * output.value(1) * output.value(2) << endl;

    return 0;
}
