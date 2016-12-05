#include <QDebug>
#include <QCryptographicHash>
#include <QByteArray>

int main(int argc, char *argv[])
{
    qDebug() << "Advent of code #4" << endl;
    qDebug() << "=================" << endl << endl;

    // Data set
    // QString phrase("abc");
    QString phrase("ojvtpuvg");

    QString passwd;
    quint64 counter = 0;

    while (passwd.size() <=7 ) {
        QString indata = phrase + QString::number(counter);
        QByteArray ba(indata.toLocal8Bit());

        QByteArray tmp(QCryptographicHash::hash(ba, QCryptographicHash::Md5).toHex());
        QString hashed(tmp);

        if (hashed.startsWith("00000")) {
            passwd.append(hashed[5]);
            // qDebug() << "#" << passwd.size() << " Hash:" << hashed << endl;
        }
        counter++;
    }

    qDebug() << endl;
    qDebug() << "=================================" << endl;
    qDebug() << "****   Day 4, part 1 answer  ****" << endl;
    qDebug() << "=================================" << endl;
    qDebug() << "password: " << passwd << endl;
    qDebug() << endl;

    // Brut force
    passwd = "________";
    counter = 0;

    while (passwd.contains('_')) {
        QString indata = phrase + QString::number(counter);
        QByteArray ba(indata.toLocal8Bit());

        QByteArray tmp(QCryptographicHash::hash(ba, QCryptographicHash::Md5).toHex());
        QString hashed(tmp);

        if (hashed.startsWith("00000")) {
            // qDebug() << "Hash: " << hashed << endl;

            QChar c = hashed[5];
            int pos = 0;

            if (c.isDigit()) {
                pos = c.digitValue();
            }
            else {
                counter++;
                continue;
            }

            if (pos < passwd.size() && (passwd[pos] == '_')) {
                passwd[pos] = hashed[6];
                // qDebug() << "Index:" << pos << " c:" << hashed[6] << " Hash:" << hashed << endl;
                // qDebug() << "password:" << passwd << endl;
            }
        }
        counter++;
    }
    qDebug() << endl;
    qDebug() << "=================================" << endl;
    qDebug() << "****   Day 4, part 2 answer  ****" << endl;
    qDebug() << "=================================" << endl;
    qDebug() << "password: " << passwd << endl;
    qDebug() << endl;

    return 0;
}
