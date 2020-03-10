#ifndef UTILITY_H
#define UTILITY_H

#include "interface.h"

#include <QRect>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QtMath>
#include <QDateTime>
#include <QHash>

class Utility
{
public:
    static QJsonObject objectFromString(const QString&);
    static QRect* decodePosition(const int);
    static int getLeftBound(const QJsonArray&, int, int, const QDate&);
    static int getRightBound(const QJsonArray&, int, int, const QDate&);
    static QDate* selectedDate(const Interface&, int, int);

private:
    Utility();
    static QHash<int, int>* teamMap;
};

#endif // UTILITY_H
