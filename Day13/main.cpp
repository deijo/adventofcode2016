#include <QDebug>
#include <QCoreApplication>

struct Coord {
    int x;
    int y;
    int iter;
};

bool operator==(const Coord& lhs, const Coord& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int favoriteNumber = 1358;

    int xSize = 50;
    int ySize = 50;
    QChar area[ySize][xSize];

    qDebug() << "Advent of code #13";
    qDebug() << "==================" << endl;


    for (int y = 0 ; y<ySize; y++)
    {
        for (int x = 0; x<xSize; x++)
        {
            int sum = x*x + 3*x + 2*x*y + y + y*y;
            sum += favoriteNumber;

            QString myStringOfBits( QString::number( sum, 2 ) );
            int ones = myStringOfBits.count('1');

            if (ones % 2) // Odd - wall
            {
                area[y][x] = '#';
            }
            else
            {
                area[y][x] = '.';
            }
        }
    }

    for (int y = 0 ; y<ySize; y++)
    {
        QString row; // (QChar(y+48));
        for (int x = 0; x<xSize; x++)
        {
            if ( x == 31 && y == 39)
            {
                row.append('T');
            }
            else
            {
                row.append(area[y][x]);
            }
        }
        qDebug() << row;
    }


    QVector<Coord> coords;
//    Coord target = { 7 ,4, 0};
    Coord target = { 31 ,39, 0};
//    Coord start = { 1 ,1, 0};
    Coord start = { 0 ,0, 0};

    coords.append(start);

    int iter = 0;
    bool found = false;
    while (!found)
    {
        QVector<Coord> local;
        foreach(Coord c, coords)
        {
            if (c.iter < iter)
            {
                continue;
            }

            if ( (c.x-1 >= 0) && (area[c.y][c.x-1] == '.') )
            {
                local.append({c.x-1, c.y, iter+1});
            }
            if ( (c.x+1 < xSize) && (area[c.y][c.x+1] == '.') )
            {
                local.append({c.x+1, c.y, iter+1});
            }
            if ( (c.y-1 >= 0) && (area[c.y-1][c.x] == '.') )
            {
                local.append({c.x, c.y-1, iter+1});
            }
            if ( (c.y+1 < ySize) && (area[c.y+1][c.x] == '.') )
            {
                local.append({c.x, c.y+1, iter+1});
            }
        }
        foreach(Coord l, local)
        {
            for(int i = 0 ; i<coords.size(); i++)
            {
                if (l.x == coords.at(i).x && l.y == coords.at(i).y && l.iter<coords.at(i).iter)
                {
                    coords.remove(i);
                }
            }

            area[l.y][l.x] = 'X';

            if (l.x == target.x && l.y == target.y)
            {
                found = true;
                break;
            }
        }

        coords.append(local);

//        for (int y = 0 ; y<ySize; y++)
//        {
//            QString row; // (QChar(y+48));
//            for (int x = 0; x<xSize; x++)
//            {
//                if ( x == 31 && y == 39)
//                {
//                    row.append('O');
//                }
//                else
//                {
//                    row.append(area[y][x]);
//                }
//            }
//            qDebug() << row;
//        }


        qDebug() << "local: " << local.size();
        qDebug() << endl << "Done iter: " << iter << " In coords: " << coords.size()<< endl;

        iter++;

    }

    qDebug() << "=================================";
    qDebug() << "****  Day 13, part 1 answer  ****";
    qDebug() << "=================================" << endl;
    qDebug() << "Start: " << start.x << ", " << start.y;
    qDebug() << "End: " << target.x << ", " << target.y;
    qDebug() << "Shortest route: " << iter << "steps" << endl;
//    // qDebug() << "   0 1 2 3 4 5 6 7 8 9";
//    for (int y = 0 ; y<ySize; y++)
//    {
//        QString row; // (QChar(y+48));
//        row += " ";
//        for (int x = 0; x<xSize; x++)
//        {
//            if ( x == 31 && y == 39)
//            {
//                row.append('O');
//            }
//            else
//            {
//                row.append(area[y][x]);
//            row.append(' ');
//            }
//        }
//        qDebug() << row;
//    }

    qDebug() << "=================================";
    qDebug() << "****  Day 13, part 2 answer  ****";
    qDebug() << "=================================" << endl;

    // How many points in 50 steps
    int res = 0;
    foreach(Coord c, coords)
    {
        if (c.iter < 50 )
        {
            qDebug() << "x,y,iter: " << c.x <<", " << c.y << ", " << c.iter;
            res++;
        }
    }

    for (int y = 0 ; y<25; y++)
    {
        QString row; // (QChar(y+48));
        for (int x = 0; x<25 ;x++)
        {
            if ( x == 1 && y == 1)
            {
                row.append('O');
            }
            else
            {
                row.append(area[y][x]);
            }
        }
        qDebug() << row;
    }

    qDebug() << "Locations: " << res;
    qDebug() << "Coords: " << coords.size();

    qDebug() << "Answer is 141.";

    exit(1);
    return a.exec();
}
