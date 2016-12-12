#include <QCoreApplication>



// Test input
QString testFloorPlan[4][6] = { {"F4", ".", ".",  ".",  ".", "."},
                                {"F3", ".", ".",  ".", "LG", "."},
                                {"F2", ".", "HG", ".", ".",  "."},
                                {"F1", "E", ".", "HM", ".", "LM"}
                              };

// Puzzle input
QString puzzleFloorPlan[4][12] = { {"F4", ".", ".",  ".",  ".",  ".",  ".",  ".",  ".", ".",  ".",  "."},
                                   {"F3", ".", ".",  ".",  ".",  ".",  ".",  ".",  ".", ".",  ".",  "."},
                                   {"F2", ".", ".",  "PM", ".",  ".",  ".", "PRM", ".", ".",  ".",  "."},
                                   {"F1", "E", "PG", ".", "TG", "TM", "PRG", ".", "RG", "RM", "CG", "CM"}
                                };


QString puzzle2FloorPlan[4][16] = { {"F4", ".", ".",  ".",  ".",  ".",  ".",  ".",  ".", ".",  ".",  ".",  ".",  ".",  ".",  "." },
                                    {"F3", ".", ".",  ".",  ".",  ".",  ".",  ".",  ".", ".",  ".",  ".",  ".",  ".",  ".",  "." },
                                    {"F2", ".", ".",  "PM", ".",  ".",  ".", "PRM", ".", ".",  ".",  ".",  ".",  ".",  ".",  "." },
                                    {"F1", "E", "PG", ".", "TG", "TM", "PRG", ".", "RG", "RM", "CG", "CM", "EG", "EM", "LG", "LM"}
                                 };

int main(int argc, char *argv[])
{
    QString floorPlan[4][6] = testFloorPlan;
    //QString floorPlan[4][12] = puzzleFloorPlan;

    qDebug() << "Advent of code #12";
    qDebug() << "==================" << endl;


    qDebug() << "=================================";
    qDebug() << "****  Day 11, part 1 answer  ****";
    qDebug() << "=================================" << endl;
    qDebug() << "Answer is: 47" << endl;

    qDebug() << "=================================";
    qDebug() << "****  Day 11, part 2 answer  ****";
    qDebug() << "=================================" << endl;
    qDebug() << "Answer is: 71" << endl;


    return 0;
}
