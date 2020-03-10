#include "mainwindow.h"

MainWindow::MainWindow()
{
    selectedDate = QDate::currentDate();
//    fontSize = 10;

    guiObjects = new Interface();
    guiObjects->setDateLabel(new QLabel(tr("Date:")));
    guiObjects->setMonthCombo(new QComboBox);

    for (int month = 1; month <= 12; ++month)
    {
        guiObjects->getMonthCombo()->addItem(QLocale::system().monthName(month));
    }

    guiObjects->setYearEdit(new QDateTimeEdit);
    guiObjects->getYearEdit()->setDisplayFormat("yyyy");
    guiObjects->getYearEdit()->setDateRange(QDate(1753, 1, 1), QDate(8000, 1, 1));

    guiObjects->getMonthCombo()->setCurrentIndex(selectedDate.month() - 1);
    guiObjects->getYearEdit()->setDate(selectedDate);

    DataFetcher fetcher;
    std::string URI = "http://api.football-data.org/v2/competitions/PL/matches?status=SCHEDULED";
    this->setData(new QString(fetcher.getData(URI)->c_str()));

    guiObjects->setTable(createCalendar());

    connect(guiObjects->getMonthCombo(), QOverload<int>::of(&QComboBox::activated),
            this, &MainWindow::setMonth);
    connect(guiObjects->getYearEdit(), &QDateTimeEdit::dateChanged,
            this, &MainWindow::setYear);

    setLayout(*(guiObjects->getTable()));

//    guiObjects->getTable()->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
//    guiObjects->getTable()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    guiObjects->getTable()->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    guiObjects->getTable()->setFixedSize(guiObjects->getTable()->horizontalHeader()->length() +
                                         guiObjects->getTable()->verticalHeader()->width(),
                                         guiObjects->getTable()->verticalHeader()->length() +
                                         guiObjects->getTable()->horizontalHeader()->height());

}

MainWindow::~MainWindow()
{
    delete data;
    delete guiObjects;
//    delete popUp;
}

QTableWidget* MainWindow::createCalendar()
{
//    qDebug("\nTable: %d x %d", table->rowCount(), table->columnCount());

    QJsonObject JData = Utility::objectFromString(*(this->getData()));

    QJsonValue val = JData.value("matches");
    QJsonArray matches = val.toArray();

    QIcon ic("../images/epl.png");
    QDate date(selectedDate.year(), selectedDate.month(), 1);

    QTableWidget* table = new QTableWidget(1, 7, this);
//    qDebug("\nTable: %d x %d", table->rowCount(), table->columnCount());

    guiObjects->setInvalidLocs(new QHash< int, QSet<int> >());

    QSet<int> invalidCols;
    for (int weekDay = 1; weekDay <= 7; ++weekDay)
    {
        // THE NAME OF THE WEEKDAYS AS INVALID CELLS
        invalidCols.insert(weekDay - 1);
        QTableWidgetItem* item = new QTableWidgetItem(QLocale::system().dayName(weekDay));
        item->setTextAlignment(Qt::AlignCenter);
        item->setBackground(QBrush(Qt::gray));
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        table->setItem(0, weekDay - 1, item);
    }
    guiObjects->getInvalidLocs()->insert(0, invalidCols);

    table->insertRow(table->rowCount());

    // THE INVALID CELLS AT THE BEGINNING OF THE MONTH
    int firstDay = date.dayOfWeek();
    invalidCols.clear();
    for (int w = 0; w < firstDay - 1; ++w)
    {
        invalidCols.insert(w);
    }
    guiObjects->getInvalidLocs()->insert(table->rowCount() - 1, invalidCols);

    while (date.month() == selectedDate.month())
    {
        int weekDay = date.dayOfWeek();

        QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(date.day()));
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

        int l = Utility::getLeftBound(matches, -1, matches.size(), date);
        if (l >= 0)
        {
            item->setIcon(ic);
        }
        if (date == QDate::currentDate())
        {
            item->setBackground(QBrush(Qt::red));
        }
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        table->setItem(table->rowCount() - 1, weekDay - 1, item);
        date = date.addDays(1);
        if (weekDay == 7 && date.month() == selectedDate.month())
        {
            table->insertRow(table->rowCount());
        }
    }

    // THE INVALID CELLS AT THE END OF THE MONTH
    int lastDay = date.addDays(-1).dayOfWeek();
    invalidCols.clear();
    for (int w = lastDay; w < 7; ++w)
    {
        invalidCols.insert(w);
    }
    guiObjects->getInvalidLocs()->insert(table->rowCount() - 1, invalidCols);

    /*
    for (QHash< int, QSet<int> >::const_iterator it1 = guiObjects->getInvalidLocs()->constBegin(); it1 != guiObjects->getInvalidLocs()->constEnd(); ++it1)
    {
        QDebug debug = qDebug();
        debug << "Row: " << it1.key() << "---";
        for (auto x : it1.value())
        {
            debug << x;
        }
    }
    */

    this->setWindowTitle(tr("Calendar for %1 %2"
        ).arg(QLocale::system().monthName(selectedDate.month())
        ).arg(selectedDate.year()));

    table->horizontalHeader()->setVisible(false);
    table->verticalHeader()->setVisible(false);
    table->setMouseTracking(true);

    connect(table, SIGNAL(cellEntered(int, int)), this, SLOT(debugInfo(int, int)));
    connect(table, SIGNAL(cellEntered(int, int)), this, SLOT(createPopUp(int, int)));

    return table;
}

void MainWindow::setLayout(QTableWidget& tab)
{
    QWidget *centralWidget = new QWidget;

    QHBoxLayout *controlsLayout = new QHBoxLayout;
    controlsLayout->addWidget(guiObjects->getDateLabel());
    controlsLayout->addWidget(guiObjects->getMonthCombo());
    controlsLayout->addWidget(guiObjects->getYearEdit());
    controlsLayout->addSpacing(24);
    controlsLayout->addStretch(1);

    QVBoxLayout* centralLayout = new QVBoxLayout;
    centralLayout->addLayout(controlsLayout);
    centralLayout->addWidget(&tab, 1);
    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::setMonth(const int month)
{
    selectedDate = QDate(selectedDate.year(), month + 1, selectedDate.day());
    QTableWidget* tab = createCalendar();
    guiObjects->setTable(tab);
    setLayout(*tab);
}

void MainWindow::setYear(const QDate date)
{
    selectedDate = QDate(date.year(), selectedDate.month(), selectedDate.day());
    QTableWidget* tab = createCalendar();
    guiObjects->setTable(tab);
    setLayout(*tab);
}

void MainWindow::debugInfo(const int row, const int col)
{
    qDebug("\nCell = (%d, %d)", row, col);

//    Utility u;
    QDate* d = Utility::selectedDate(*(this->guiObjects), row, col);

    qDebug() << "Selected date: " << *d;
}

void MainWindow::createPopUp(const int row, const int col)
{
    qDebug() << "\n[INFO] createPopUp() called.";

    popUp = popUp->getInstance();
    QDate* mouseOverDate = Utility::selectedDate(*(this->guiObjects), row, col);

    QJsonObject JData = Utility::objectFromString(*(this->getData()));
    QJsonValue val = JData.value("matches");
    QJsonArray array = val.toArray();

    const QSize logoSize(30, 30);

    QVBoxLayout* windowLayout = new QVBoxLayout();
    QHBoxLayout* hLayout = new QHBoxLayout();

    QVBoxLayout* homeNameLayout = new QVBoxLayout();
    QVBoxLayout* homeLogoLayout = new QVBoxLayout();
    QVBoxLayout* timeLayout = new QVBoxLayout();
    QVBoxLayout* awayNameLayout = new QVBoxLayout();
    QVBoxLayout* awayLogoLayout = new QVBoxLayout();

    QHBoxLayout* dateLayout = new QHBoxLayout();
    QLabel* dateLabel = new QLabel();               // TODO: Display the date using proper formatting
    QFont font = dateLabel->font();
//    font.setPointSize(11);
    font.setBold(true);
    dateLabel->setFont(font);

    dateLabel->setText(mouseOverDate->toString());
    dateLabel->setStyleSheet("color: white");
    dateLayout->addWidget(dateLabel);
    dateLayout->setAlignment(dateLabel, Qt::AlignHCenter);
    windowLayout->addLayout(dateLayout);

    QPixmap spriteSheet("../images/sheet.png");

    QTableWidgetItem* mouseOverCell = guiObjects->getTable()->item(row, col);
    if ((!mouseOverDate->isValid()) || (mouseOverCell->icon().isNull()))
    {
        popUp->hide();
    }
    else
    {
        int left = Utility::getLeftBound(array, -1, array.size() - 1, *mouseOverDate);
        int right = Utility::getRightBound(array, 0, array.size(), *mouseOverDate);

        if ((right >= left) && (left >= 0) && (right >= 0))
        {
            for (int idx = left; idx <= right; ++idx)
            {
                QJsonObject match = array[idx].toObject();

                QString sDate = match["utcDate"].toString();
                QDateTime dDate = QDateTime::fromString(sDate, "yyyy'-'MM'-'dd'T'hh:mm:ss'Z'");
                dDate.setTimeSpec(Qt::UTC);

                QString homeName = match["homeTeam"].toObject()["name"].toString();
                QString awayName = match["awayTeam"].toObject()["name"].toString();

                int homeId = match["homeTeam"].toObject()["id"].toInt();
                int awayId = match["awayTeam"].toObject()["id"].toInt();

                QLabel* teamLabel1 = new QLabel();
                QLabel* teamLabel2 = new QLabel();
                QLabel* timeLabel = new QLabel();

        //        teamLabel1->setTextFormat(Qt::RichText);
                QFont font1 = teamLabel1->font();
                font1.setPointSize(10);
                font1.setBold(true);
                teamLabel1->setFont(font1);
                teamLabel1->setText(homeName);
                teamLabel1->setAlignment(Qt::AlignRight);
                teamLabel1->setStyleSheet("color: white");

                QFont font2 = teamLabel2->font();
                font2.setPointSize(10);
                font2.setBold(true);
                teamLabel2->setFont(font2);
                teamLabel2->setText(awayName);
                teamLabel2->setAlignment(Qt::AlignLeft);
                teamLabel2->setStyleSheet("color: white");

                timeLabel->setText(dDate.time().toString());
                timeLabel->setStyleSheet("color: white");

                QLabel* teamLogoLabel1 = new QLabel();
                QLabel* teamLogoLabel2 = new QLabel();

                QRect* homeRect = Utility::decodePosition(homeId);
                QRect* awayRect = Utility::decodePosition(awayId);

                QPixmap teamLogo1 = spriteSheet.copy(*homeRect);
                QPixmap teamLogo2 = spriteSheet.copy(*awayRect);
                teamLogoLabel1->setPixmap(teamLogo1.scaled(logoSize));
                teamLogoLabel2->setPixmap(teamLogo2.scaled(logoSize));

                homeNameLayout->addWidget(teamLabel1);
                homeLogoLayout->addWidget(teamLogoLabel1);
                timeLayout->addWidget(timeLabel);
                awayLogoLayout->addWidget(teamLogoLabel2);
                awayNameLayout->addWidget(teamLabel2);
            }

            hLayout->addLayout(homeNameLayout);
            hLayout->addLayout(homeLogoLayout);
            hLayout->addLayout(timeLayout);
            hLayout->addLayout(awayLogoLayout);
            hLayout->addLayout(awayNameLayout);

            windowLayout->addLayout(hLayout);

            QWidget* widget = new QWidget();
            widget->setLayout(windowLayout);
            widget->setStyleSheet("background-color: rgba(0, 0, 0, 0)");

        //    QScrollArea* scrollArea = new QScrollArea();
        //    scrollArea->setWidget(widget);
        //    widget->setAutoFillBackground(true);
            popUp->setCentralWidget(widget);
        //    this->setCentralWidget(scrollArea);
//            popUp->setStyleSheet("background-color: rgb(150, 0, 90);");

            popUp->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0, "
                                 "stop: 0 rgb(60, 0, 60), stop: 0.5 rgb(80, 5, 70), stop: 1 rgb(255, 40, 128));");
            popUp->setWindowFlags(Qt::FramelessWindowHint);
//            popUp->adjustSize();
            popUp->show();
        }
    }
}

QString* MainWindow::getData()
{
    return data;
}

void MainWindow::setData(QString* d)
{
    data = d;
}












