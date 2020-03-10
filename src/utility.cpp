#include "utility.h"

QHash<int, int>* Utility::teamMap = new QHash<int, int>{
                                                        std::pair<int, int>(57, 0),
                                                        std::pair<int, int>(58, 1),
                                                        std::pair<int, int>(1044, 2),
                                                        std::pair<int, int>(397, 3),
                                                        std::pair<int, int>(328, 4),
                                                        std::pair<int, int>(61, 5),
                                                        std::pair<int, int>(354, 6),
                                                        std::pair<int, int>(62, 7),
                                                        std::pair<int, int>(338, 8),
                                                        std::pair<int, int>(64, 9),
                                                        std::pair<int, int>(65, 10),
                                                        std::pair<int, int>(66, 11),
                                                        std::pair<int, int>(67, 12),
                                                        std::pair<int, int>(68, 13),
                                                        std::pair<int, int>(356, 14),
                                                        std::pair<int, int>(340, 15),
                                                        std::pair<int, int>(73, 16),
                                                        std::pair<int, int>(346, 17),
                                                        std::pair<int, int>(563, 18),
                                                        std::pair<int, int>(76, 19)
                                                        };

Utility::Utility()
{

}

QJsonObject Utility::objectFromString(const QString& in)
{
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());

    if(!doc.isNull())
    {
        if(doc.isObject())
        {
            obj = doc.object();
        }
        else
        {
            qDebug() << "Document is not an object" << endl;
        }
    }
    else
    {
        qDebug() << "Invalid JSON...\n" << in << endl;
    }

    return obj;
}

QRect* Utility::decodePosition(const int JsonId)
{
    int id = (*teamMap)[JsonId];

    int startIdxX = 200 * qFloor(id / 4);
    int endIdxX = 200 * (id % 4);

    return new QRect(startIdxX, endIdxX, 200, 200);
}

int Utility::getLeftBound(const QJsonArray& a, int left, int right, const QDate& key)
{
    int mid;
    while (right - left > 1)
    {
        mid = left + (right - left) / 2;
        QJsonObject match = a[mid].toObject();

        QString sDate = match["utcDate"].toString();
        QDate dDate = QDateTime::fromString(sDate, "yyyy'-'MM'-'dd'T'hh:mm:ss'Z'").date();

        if (dDate >= key)
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    QDate d;
    if (right < a.size())
    {
        d = QDateTime::fromString(a[right].toObject()["utcDate"].toString(), "yyyy'-'MM'-'dd'T'hh:mm:ss'Z'").date();
    }

    return (((d == key) && (right < a.size())) ? right : -1);
}

int Utility::getRightBound(const QJsonArray& a, int left, int right, const QDate& key)
{
    int mid;
    while (right - left > 1)
    {
        mid = left + (right - left) / 2;
        QJsonObject match = a[mid].toObject();

        QString sDate = match["utcDate"].toString();
        QDate dDate = QDateTime::fromString(sDate, "yyyy'-'MM'-'dd'T'hh:mm:ss'Z'").date();

        if (dDate <= key)
            left = mid;
        else
            right = mid;
    }

    return left;
}

QDate* Utility::selectedDate(const Interface& intf, int row, int col)
{
    int day = 0, month = 0, year = 0;

    if (!(intf.getInvalidLocs()->contains(row)))
    {
        day = intf.getTable()->item(row, col)->text().toInt();
        month = (intf.getMonthCombo()->currentIndex()) + 1;
        year = intf.getYearEdit()->date().year();
    }
    else if (!(intf.getInvalidLocs()->value(row).contains(col)))
    {
        day = intf.getTable()->item(row, col)->text().toInt();
        month = (intf.getMonthCombo()->currentIndex()) + 1;
        year = intf.getYearEdit()->date().year();
    }

    return new QDate(year, month, day);
}

