#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>

#define MAX_X_GRAPHVIEW 600
#define MAX_Y_GRAPHVIEW 600
#define MAX_XY_LIKE_INFTY 9999

QT_BEGIN_NAMESPACE

class Ui_Window
{


public:

    // Area SX - Tools
    QWidget *window;
    QWidget *zoomWidget;
    QHBoxLayout *zoomLayoutBox;
    QSlider *zoomSlider;
    QPushButton *button1;
    QPushButton *button2;
    QGroupBox *groupBox;
    QCheckBox *check1;
    QCheckBox *check2;
    QCheckBox *check3;
    QVBoxLayout *vbox;
    QVBoxLayout *rightToolsLayout;
    QWidget *rightTools;
    QLabel *userInfo;

    // Graph Area
    QGraphicsView *graphicsView;
    QProgressBar *progressBarGraph;
    QVBoxLayout *graphLayout;
    QWidget *graphWidget;
    QHBoxLayout *horizontalLayout;


    void setupUi(QWidget *widget)
    {
        if (widget->objectName().isEmpty())
            widget->setObjectName(QStringLiteral("Widget"));
        widget->resize(1024, 768);


        // Area SX - Tools
        zoomSlider = new QSlider(Qt::Horizontal);
        zoomSlider->setRange(5,50);
        zoomSlider->setValue( 25 );
        zoomLayoutBox = new QHBoxLayout;
        zoomLayoutBox->addWidget(zoomSlider);
        zoomWidget = new QWidget;
        zoomWidget->setLayout(zoomLayoutBox);

        button1 = new QPushButton("Button1");
        button2 = new QPushButton("Button2");

        button1->setDefault( false );
        button1->setAutoDefault( false ) ;
        button2->setDefault( false );
        button2->setAutoDefault( false ) ;


        groupBox = new QGroupBox(QGroupBox::tr("Settings"));
        check1 = new QCheckBox(QCheckBox::tr("&Grid"));
        check2 = new QCheckBox(QCheckBox::tr("C&ollisions_"));
        check3 = new QCheckBox(QCheckBox::tr("Lap&s_"));
        check1->setChecked(true);

        vbox = new QVBoxLayout;
        vbox->addWidget(check1);
        vbox->addWidget(check2);
        vbox->addWidget(check3);
        vbox->addStretch(1);
        groupBox->setLayout(vbox);

        userInfo = new QLabel;
        userInfo->setText("Info");
        rightToolsLayout = new QVBoxLayout;
        rightToolsLayout->addWidget(zoomWidget);
        rightToolsLayout->addWidget(button1);
        rightToolsLayout->addWidget(button2);
        rightToolsLayout->addWidget(groupBox);
        rightToolsLayout->addWidget(userInfo);
        rightTools = new QWidget;
        rightTools->setLayout(rightToolsLayout);


        // Graph Area
        graphicsView = new QGraphicsView;
        graphicsView->setRenderHints(QPainter::Antialiasing |
                                     QPainter::TextAntialiasing |
                                     QPainter::HighQualityAntialiasing |
                                     QPainter::SmoothPixmapTransform);

        progressBarGraph = new QProgressBar;
        graphLayout = new QVBoxLayout;
        graphLayout->addWidget(graphicsView);
        graphLayout->addWidget(progressBarGraph);
        graphWidget = new QWidget;
        graphWidget->setLayout( graphLayout );


        horizontalLayout = new QHBoxLayout;
        horizontalLayout->addWidget(rightTools);
        horizontalLayout->addWidget(graphWidget);

        widget->setLayout(horizontalLayout);


    } // setupUi


};

namespace Ui {
    class MainWindow: public Ui_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
