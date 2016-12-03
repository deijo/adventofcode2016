#include <stdlib.h>

#include <QDebug>
#include <QStringList>
#include <QPair>

struct Block {
    int northSouth;
    int eastWest;
};

const QString input[4] = { "R2, L3",
                           "R2, R2, R2",
                           "R5, L5, R5, R3",
                           "R3, R1, R4, L4, R3, R1, R1, L3, L5, L5, L3, R1, R4, L2, L1, R3, L3, R2, R1, R1, L5, L2, L1, R2, L4, R1, L2, L4, R2, R2, L2, L4, L3, R1, R4, R3, L1, R1, L5, R4, L2, R185, L2, R4, R49, L3, L4, R5, R1, R1, L1, L1, R2, L1, L4, R4, R5, R4, L3, L5, R1, R71, L1, R1, R186, L5, L2, R5, R4, R1, L5, L2, R3, R2, R5, R5, R4, R1, R4, R2, L1, R4, L1, L4, L5, L4, R4, R5, R1, L2, L4, L1, L5, L3, L5, R2, L5, R4, L4, R3, R3, R1, R4, L1, L2, R2, L1, R4, R2, R2, R5, R2, R5, L1, R1, L4, R5, R4, R2, R4, L5, R3, R2, R5, R3, L3, L5, L4, L3, L2, L2, R3, R2, L1, L1, L5, R1, L3, R3, R4, R5, L3, L5, R1, L3, L5, L5, L2, R1, L3, L1, L3, R4, L1, R3, L2, L2, R3, R3, R4, R4, R1, L4, R1, L5"
                         };

const QPair<int, int> directionMultiplier[4] = { qMakePair(1, 0),  // north
                                                 qMakePair(0, 1),  // east
                                                 qMakePair(-1, 0), // south
                                                 qMakePair(0, -1)  // west
                                               };


int main(int argc, char *argv[])
{
    qDebug() << "Advent of code #1 A" << endl;
    qDebug() << "===================" << endl << endl;

    for(int i = 0; i < 4 ; i++)
    {
        QPair<int, int> block = qMakePair(0, 0);

        // Direction
        // NORTH = 0
        // EAST = 1
        // SOUTH = 2
        // WEST = 3

        int dir = 0;

        QStringList list = input[i].split(",");
        int away = 0;

        for(int index=0; index<list.size() ; index++)
        {
            QString tmpStr = list.at(index);
            int steps = 0;
            tmpStr.replace(" ","");

            // qDebug() << tmpStr << endl;

            if (tmpStr[0] == 'R')
            {
                dir++;
                dir %= 4;
            }
            else if (tmpStr[0] == 'L')
            {
                    dir--;
                    if (dir < 0)
                        dir = 3;
            }

            tmpStr.remove(0, 1);
            // qDebug() << tmpStr << endl;

            block.first += tmpStr.toInt()* directionMultiplier[dir].first;
            block.second += tmpStr.toInt()* directionMultiplier[dir].second;
        }
        away = abs(block.first) + abs(block.second);

        qDebug() << endl;
        qDebug() << block.first << ", " << block.second << endl;
        qDebug() << "Nbr of blocks away: " << away << endl;
        qDebug() << endl;
        qDebug() << "=================================" << endl;
        qDebug() << endl;

    }


    return 0;
}
