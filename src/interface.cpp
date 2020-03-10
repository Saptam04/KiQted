#include "interface.h"

Interface::Interface()
{

}

Interface::~Interface()
{
    delete dateLabel;
    delete monthCombo;
    delete yearEdit;
    delete table;
    delete invalidLocs;
}

QLabel* Interface::getDateLabel()
{
    return dateLabel;
}

QComboBox* Interface::getMonthCombo() const
{
    return monthCombo;
}

QDateTimeEdit* Interface::getYearEdit() const
{
    return yearEdit;
}

QTableWidget* Interface::getTable() const
{
    return table;
}

QHash< int, QSet<int> >* Interface::getInvalidLocs() const
{
    return invalidLocs;
}

void Interface::setDateLabel(QLabel* dLabel)
{
    dateLabel = dLabel;
}

void Interface::setMonthCombo(QComboBox* combo)
{
    monthCombo = combo;
}

void Interface::setYearEdit(QDateTimeEdit* edit)
{
    yearEdit = edit;
}

void Interface::setTable(QTableWidget* tab)
{
    table = tab;
}

void Interface::setInvalidLocs(QHash<int, QSet<int> >* map)
{
    invalidLocs = map;
}















