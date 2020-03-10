#ifndef INTERFACE_H
#define INTERFACE_H

#include <QtWidgets>
#include <QHash>
#include <QSet>

class Interface
{
public:
    Interface();
    ~Interface();

    QLabel* getDateLabel();
    QComboBox* getMonthCombo() const;
    QDateTimeEdit* getYearEdit() const;
    QTableWidget* getTable() const;
    QHash< int, QSet<int> >* getInvalidLocs() const;

    void setDateLabel(QLabel*);
    void setMonthCombo(QComboBox*);
    void setYearEdit(QDateTimeEdit*);
    void setTable(QTableWidget*);
    void setInvalidLocs(QHash< int, QSet<int> >*);

private:
    QLabel* dateLabel;
    QComboBox* monthCombo;
    QDateTimeEdit* yearEdit;
    QTableWidget* table;
    QHash< int, QSet<int> >* invalidLocs;
};

#endif // INTERFACE_H
