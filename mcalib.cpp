#include "mcalib.h"
#include "ui_mcalib.h"
#include "QDir"
#include <cstdlib>
#include <QPen>
#include<QColor>
#include<QLineEdit>
#include<QPalette>
#include"qpalette.h"
#include <QLabel>
#include <QVBoxLayout>
#include<QMessageBox>
#include<QUndoStack>
#include <QPrinter>
#include <QPrintDialog>
#include<QPainter>
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QTextEdit>
#include <QPixmap>
#include <QStandardItemModel>
#include<QStackedWidget>
#include"qstackedwidget.h"

MCALIB::MCALIB(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MCALIB)
{

    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
                              "invoke a context menu</i>"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->addWidget(topFiller);
    layout->addWidget(infoLabel);
    layout->addWidget(bottomFiller);
    widget->setLayout(layout);

    createActions();
    createMenus();

    QString message = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);

    setWindowTitle(tr("Menus"));
    setMinimumSize(160, 160);
    resize(480, 320);

    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    m_undo_stack = new QUndoStack(this);



}
#ifndef QT_NO_CONTEXTMENU
void MCALIB::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(cutAct);
    menu.addAction(copyAct);
    menu.addAction(pasteAct);
   // menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU
void MCALIB::newFile()
{

     ui->stackedWidget->setCurrentIndex(0);
    //QDesktopServices::openUrl(QUrl::fromUserInput(ui->lineEdit->text()));
  /* newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &metric::newFile);*/

        /*QAction *action;

        QMenu *file = new QMenu(this);
        action= new QAction(tr("&Open"), this);
        action->setShortcut(tr("CTRL+O"));
        connect(action, &QAction::triggered, this, &QMenus::fileOpen);
        file->addAction(action);*/
    //infoLabel->setText(tr("Invoked <b>File|New</b>"));
}
/*void MCALIB::fileOpen()
{
    m_editor->append(tr("File Open selected."));
}*/
void MCALIB::open()
{

         filename =  QFileDialog::getOpenFileName(
              this,
              "Open Document",
              QDir::currentPath(),
              "All files (*.*) ;; Document files (*.doc *.rtf);; PNG files (*.png)");

        if( !filename.isNull() )
        {
          qDebug() << "selected file path : " <<filename.toUtf8();
        }
    //infoLabel->setText(tr("Invoked <b>File|Open</b>"));
}
void MCALIB::save()
{
    infoLabel->setText(tr("Invoked <b>File|Save</b>"));
}
void MCALIB::print()
{

    QList <QWidget *> widgets;
    widgets.append({ui->stackedWidget->currentWidget()});

    QPrinter printer(QPrinter::HighResolution);

 const QString name = ui->lineEdit_362->text() +".pdf";
    printer.setOutputFormat(QPrinter::PdfFormat);
   printer.setOutputFileName(name);
   // printer.setOrientation(QPrinter::Landscape);
    // printer.setPaperSize(QPrinter::A4);
    QPainter painter;

    if (! painter.begin(&printer)) { // failed to open file
        qWarning("failed to open file, is it writable?");
    }

    for(auto widget: widgets){
        if(widget){
                  ui->pushButton_13->setVisible(false);
                  ui->pushButton_5->setVisible(false);
            if(widget->width() > 0 && widget->height() >0 ){

                qreal xscale = printer.pageRect().width()/qreal(widget->width());
                qreal yscale = printer.pageRect().height()/qreal(widget->height());

                qreal scale = qMin(xscale, yscale);

                painter.translate(printer.paperRect().x() + printer.pageRect().width()/1.5,
                                  printer.paperRect().y() + printer.pageRect().height()/2.5);

                painter.scale(scale, scale);
                painter.translate(-widget->width()/1.5, -widget->height()/2.5);
                widget->render(&painter);
                painter.resetTransform();
                if(widget != widgets.last())
                    printer.newPage();
            }

        }
     ui->pushButton_13->setVisible(true);
     ui->pushButton_5->setVisible(true);
    }
    painter.end();
}
void MCALIB::undo()
{

    m_undo_stack->undo();
    //infoLabel->setText(tr("Invoked <b>Edit|Undo</b>"));
}
void MCALIB::redo()
{
    m_undo_stack->redoText();

    infoLabel->setText(tr("Invoked <b>Edit|Redo</b>"));
}
void MCALIB::cut()
{
    infoLabel->setText(tr("Invoked <b>Edit|Cut</b>"));
}
void MCALIB::copy()
{
    infoLabel->setText(tr("Invoked <b>Edit|Copy</b>"));
}
void MCALIB::paste()
{
    infoLabel->setText(tr("Invoked <b>Edit|Paste</b>"));
}
void MCALIB::bold()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Bold</b>"));
}
void MCALIB::italic()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Italic</b>"));
}
void MCALIB::leftAlign()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Left Align</b>"));
}
void MCALIB::rightAlign()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Right Align</b>"));
}
void MCALIB::justify()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Justify</b>"));
}
void MCALIB::center()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Center</b>"));
}
void MCALIB::setLineSpacing()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Set Line Spacing</b>"));
}
void MCALIB::setParagraphSpacing()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Set Paragraph Spacing</b>"));
}
void MCALIB::about()
{

    QMessageBox::about(this, tr("About MCALIB "),
            tr(" <b>MCALIB</b> is a calibration software from metrics"));
}
void MCALIB::aboutQt()
{
    infoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
}
void MCALIB::createActions()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MCALIB::newFile);

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MCALIB::open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MCALIB::save);

    printAct = new QAction(tr("&Print..."), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip(tr("Print the document"));
    connect(printAct, &QAction::triggered, this, &MCALIB::print);

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last operation"));
    connect(undoAct, &QAction::triggered, this, &MCALIB::undo);

    redoAct = new QAction(tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo the last operation"));
    connect(redoAct, &QAction::triggered, this, &MCALIB::redo);

    cutAct = new QAction(tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, &QAction::triggered, this, &MCALIB::cut);

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, &QAction::triggered, this, &MCALIB::copy);

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, &QAction::triggered, this, &MCALIB::paste);

    boldAct = new QAction(tr("&Bold"), this);
    boldAct->setCheckable(true);
    boldAct->setShortcut(QKeySequence::Bold);
    boldAct->setStatusTip(tr("Make the text bold"));
    connect(boldAct, &QAction::triggered, this, &MCALIB::bold);

    QFont boldFont = boldAct->font();
    boldFont.setBold(true);
    boldAct->setFont(boldFont);

    italicAct = new QAction(tr("&Italic"), this);
    italicAct->setCheckable(true);
    italicAct->setShortcut(QKeySequence::Italic);
    italicAct->setStatusTip(tr("Make the text italic"));
    connect(italicAct, &QAction::triggered, this, &MCALIB::italic);

    QFont italicFont = italicAct->font();
    italicFont.setItalic(true);
    italicAct->setFont(italicFont);

    setLineSpacingAct = new QAction(tr("Set &Line Spacing..."), this);
    setLineSpacingAct->setStatusTip(tr("Change the gap between the lines of a "
                                       "paragraph"));
    connect(setLineSpacingAct, &QAction::triggered, this, &MCALIB::setLineSpacing);

    setParagraphSpacingAct = new QAction(tr("Set &Paragraph Spacing..."), this);
    setParagraphSpacingAct->setStatusTip(tr("Change the gap between paragraphs"));
    connect(setParagraphSpacingAct, &QAction::triggered,
            this, &MCALIB::setParagraphSpacing);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MCALIB::about);

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(aboutQtAct, &QAction::triggered, this, &MCALIB::aboutQt);

    leftAlignAct = new QAction(tr("&Left Align"), this);
    leftAlignAct->setCheckable(true);
    leftAlignAct->setShortcut(tr("Ctrl+L"));
    leftAlignAct->setStatusTip(tr("Left align the selected text"));
    connect(leftAlignAct, &QAction::triggered, this, &MCALIB::leftAlign);

    rightAlignAct = new QAction(tr("&Right Align"), this);
    rightAlignAct->setCheckable(true);
    rightAlignAct->setShortcut(tr("Ctrl+R"));
    rightAlignAct->setStatusTip(tr("Right align the selected text"));
    connect(rightAlignAct, &QAction::triggered, this, &MCALIB::rightAlign);

    justifyAct = new QAction(tr("&Justify"), this);
    justifyAct->setCheckable(true);
    justifyAct->setShortcut(tr("Ctrl+J"));
    justifyAct->setStatusTip(tr("Justify the selected text"));
    connect(justifyAct, &QAction::triggered, this, &MCALIB::justify);

    centerAct = new QAction(tr("&Center"), this);
    centerAct->setCheckable(true);
    centerAct->setShortcut(tr("Ctrl+E"));
    centerAct->setStatusTip(tr("Center the selected text"));
    connect(centerAct, &QAction::triggered, this, &MCALIB::center);

    alignmentGroup = new QActionGroup(this);
    alignmentGroup->addAction(leftAlignAct);
    alignmentGroup->addAction(rightAlignAct);
    alignmentGroup->addAction(justifyAct);
    alignmentGroup->addAction(centerAct);
    leftAlignAct->setChecked(true);
}
void MCALIB::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    formatMenu = editMenu->addMenu(tr("&Format"));
    formatMenu->addAction(boldAct);
    formatMenu->addAction(italicAct);
    formatMenu->addSeparator()->setText(tr("Alignment"));
    formatMenu->addAction(leftAlignAct);
    formatMenu->addAction(rightAlignAct);
    formatMenu->addAction(justifyAct);
    formatMenu->addAction(centerAct);
    formatMenu->addSeparator();
    formatMenu->addAction(setLineSpacingAct);
    formatMenu->addAction(setParagraphSpacingAct);
}
MCALIB::~MCALIB()
{
    delete ui;
}
void MCALIB::makePlot()
{


//    QVector<double> x(101), y(101); // initialize with entries 0..100
////    for (int i=0; i<101; ++i)
////    {
////      x[i] = i/50.0 - 1; // x goes from -1 to 1
////      y[i] = x[i]*x[i]; // let's plot a quadratic function
////    }
//    // create graph and assign data to it:
//    ui->customPlot->addGraph();

//    ui->customPlot->graph(0)->setData(x, y);
//    // give the axes some labels:
//    ui->customPlot->xAxis->setLabel("x");
//    ui->customPlot->yAxis->setLabel("y");


//    // set axes ranges, so we see all data:
//  //int row_n=ui->tableWidget->rowCount();
//  QStringList categories;
//      categories << "Jan" << "Feb" << "Mar" << "Apr" << "May"<<"aka";
//    ui->customPlot->xAxis->setRange(0,8);

//  ui->customPlot->yAxis->setRange(0,90);

//    ui->customPlot->replot();

}
void MCALIB::on_import_2_clicked()
{


    filename =  QFileDialog::getOpenFileName(
                  this,
                  "Open Document",
                  QDir::currentPath(),
                  "All files (*.*) ;; Document files (*.xlsx *xls *.xml *.rtf);; PNG files (*.png)");
            if( !filename.isNull() )
            {
              qDebug() << "selected file path : " <<filename.toUtf8();
            }
          QFileInfo info(filename);
          QString filename1 = info.path() + "/" + info.completeBaseName() + ".csv";
            QFile file(filename1.toUtf8());
              QTextStream in(&file);
              int line_count=0;
                if(!file.open(QIODevice::ReadOnly)) {
                    QMessageBox::information(0, "error", file.errorString());
                }




                while(!in.atEnd())
                             {
                                QString line=in.readLine();
                                QStringList line_data=line.split(",",QString::SkipEmptyParts);
                              for(int j=0;j<line_data.size();j++)
                              {
                                  QString m_prop=line_data.at(j);
                                  //QStandardItem *item=new QStandardItem(m_prop);  this is for tableview
                                  QTableWidgetItem *it=new QTableWidgetItem(m_prop,1002);
                                  //model->setItem(line_count,j,item);

                                  ui->tableWidget_3->setItem(line_count,j,it);
                                  // ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
                             // ui->tableWidget->setItem();
                              }
                              line_count++;
                             }
                file.close();

//    QFile file("filename");

//    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/", ("File(*.csv)"));


//    QString data;
//    QStringList rowOfData;
//    QStringList rowData;
//    data.clear();
//    rowOfData.clear();
//    rowData.clear();

//    if (file.open(QFile::ReadOnly))
//    {
//        data = file.readAll();
//        rowOfData = data.split("\n");
//        file.close();
//    }

//   qDebug()<<rowOfData;

//   for (int x = 0; x < rowOfData.size(); x++)
//       {
//           rowData = rowOfData.at(x).split(";");
//           qDebug()<<rowData;
//           for (int y = 0; y < rowData.size(); y++)
//           {
//           //ui->tableWidget_3->item(x,y)->setText(rowData[y]);
//           ui->tableWidget_3->setItem(x,y,new QTableWidgetItem (QString("rowData[y]")));
//           }
//    }

}
void MCALIB::tablecolum()
{

    for(int i=0; i<10 ;i++)
    {
    ui->tableWidget_9->insertColumn(i);
    ui->tableWidget_3->insertColumn(i);
    }
    int s =50;
    for(int j=0; j<10 ;j++)
    {
    ui->tableWidget_9->setColumnWidth(j,s);
    ui->tableWidget_3->setColumnWidth(j,s);
    }
    QStringList h1;
    h1 <<"0" << "10"<<"20"<<"30"<<"40"<<"50"<<"60"<<"70"<<"80"<<"90";
    ui->tableWidget_9->setHorizontalHeaderLabels(h1);
    ui->tableWidget_3->setHorizontalHeaderLabels(h1);


}
void MCALIB::tablecolum1()
{
    for(int i=0; i<10 ;i++)
    {
    ui->tableWidget_9->insertColumn(i);
       ui->tableWidget_3->insertColumn(i);
    }
    int s =50;
    for(int j=0; j<10 ;j++)
    {
    ui->tableWidget_9->setColumnWidth(j,s);
    ui->tableWidget_3->setColumnWidth(j,s);
    }
    QStringList h1;
    h1 <<"0" << "20"<<"40"<<"60"<<"80"<<"100"<<"80"<<"60"<<"40"<<"20";
    ui->tableWidget_9->setHorizontalHeaderLabels(h1);
    ui->tableWidget_3->setHorizontalHeaderLabels(h1);

}
void MCALIB::on_pushButton_clicked()
{

    QString str = ui->lineEdit_362->text();
    QString str1 = ui->lineEdit_2->text();
    QString str2 = ui->lineEdit_3->text();
    QString str3 = ui->lineEdit_4->text();
    QString str4 = ui->lineEdit_5->text();
    QString str5 = ui->textEdit->toPlainText();
    ui->lineEdit_29->setText(str1);
    ui->lineEdit_30->setText(str2);
    ui->lineEdit_36->setText(str3);
    ui->lineEdit_35->setText(str4);
    ui->textEdit_2->setText(str5);
    ui->textEdit_3->setText(str5);
    ui->textEdit_4->setText(str5);
    ui->textEdit_5->setText(str5);
    ui->label_42->setText(str);
    ui->label_8->setText(str);
    ui->label_233->setText(str);
    ui->lineEdit_106->setText(str1);
    ui->lineEdit_107->setText(str2);
    ui->lineEdit_108->setText(str3);
    ui->lineEdit_98->setText(str4);
    ui->lineEdit_97->setText(str5);
    ui->textEdit_6->setText(str5);
    ui->scrollArea_5->verticalScrollBar()->setSliderPosition(0);
    ui->scrollArea_2->verticalScrollBar()->setSliderPosition(0);
    ui->scrollArea_3->verticalScrollBar()->setSliderPosition(0);
    ui->scrollArea_4->verticalScrollBar()->setSliderPosition(0);
    ui->scrollArea->verticalScrollBar()->setSliderPosition(0);
    ui->scrollArea_7->verticalScrollBar()->setSliderPosition(0);
    ui->scrollArea_9->verticalScrollBar()->setSliderPosition(0);
     ui->scrollArea_6->verticalScrollBar()->setSliderPosition(0);

    ui->tableWidget_15->horizontalHeader()->setVisible(false);
    ui->tableWidget_15->verticalHeader()->setVisible(false);
    ui->tableWidget_15->setColumnWidth(0,300);

    if(ui->comboBox->currentIndex()==3)
    {

            ui->label_3->setText(str);
            ui->stackedWidget->setCurrentIndex(4);
            tablecolum();
            ui->tableWidget_3->setRowCount(12);
            ui->tableWidget_3->resize(677,400);

            int r=25;
            for(int j=0; j<11 ;j++)
            {
                ui->tableWidget_3->setRowHeight(j,r);
            }
            QStringList v1;
            v1 <<"Forward Start"<< "Reverse Start" << "1 Revolution (Forward)"<<"1 Revolution (Reverse)"<<"2 Revolution (Forward)"<<"2 Revolution (Reverse)"<<"3 Revolution (Forward)"<<"3 Revolution (Reverse)"<<"4 Revolution (Forward)"<<"4 Revolution (Reverse)"<<"5 Revolution (Forward)"<<"5 Revolution (Reverse)";
            ui->tableWidget_3->setVerticalHeaderLabels(v1);

    }

    if(ui->comboBox->currentIndex()==2)
    {

        ui->label_3->setText(str);
        ui->stackedWidget->setCurrentIndex(4);
        tablecolum();
        ui->tableWidget_3->setRowCount(8);
        ui->tableWidget_3->resize(677,275);
        int r=25;
        for(int j=0; j<8;j++)
        {
            ui->tableWidget_3->setRowHeight(j,r);
        }

        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "1 Revolution (Forward)"<<"1 Revolution (Reverse)"<<"2 Revolution (Forward)"<<"2 Revolution (Reverse)"<<"3 Revolution (Forward)"<<"3 Revolution (Reverse)";
        ui->tableWidget_3->setVerticalHeaderLabels(v1);
    }

    if(ui->comboBox->currentIndex()== 4)
     {

        ui->label_3->setText(str);
        ui->stackedWidget->setCurrentIndex(4);
        tablecolum();
        ui->tableWidget_3->setRowCount(14);
        ui->tableWidget_3->resize(677,465);
        int r=18;
        for(int j=0; j<13 ;j++)
        {
            ui->tableWidget_3->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "1 Revolution (Forward)"<<"1 Revolution (Reverse)"<<"2 Revolution (Forward)"<<"2 Revolution (Reverse)"<<"3 Revolution (Forward)"<<"3 Revolution (Reverse)"<<"4 Revolution (Forward)"<<"4 Revolution (Reverse)"<<"5 Revolution (Forward)"<<"5 Revolution (Reverse)"<<"6 Revolution (Forward)"<<"6 Revolution (Reverse)";
        ui->tableWidget_3->setVerticalHeaderLabels(v1);
}

    if(ui->comboBox->currentIndex()== 5)
        {

        ui->label_3->setText(str);
        ui->stackedWidget->setCurrentIndex(4);
        tablecolum();
        ui->tableWidget_3->setRowCount(16);
        ui->tableWidget_3->resize(688,523);
        int r=15;
        for(int j=0; j<16 ;j++)
        {
            ui->tableWidget_3->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "1 Revolution (Forward)"<<"1 Revolution (Reverse)"<<"2 Revolution (Forward)"<<"2 Revolution (Reverse)"<<"3 Revolution (Forward)"<<"3 Revolution (Reverse)"<<"4 Revolution (Forward)"<<"4 Revolution (Reverse)"<<"5 Revolution (Forward)"<<"5 Revolution (Reverse)"<<"6 Revolution (Forward)"<<"6 Revolution (Reverse)"<<"7 Revolution (Forward)"<<"7 Revolution (Reverse)";
        ui->tableWidget_3->setVerticalHeaderLabels(v1);
        }

    if(ui->comboBox->currentIndex()== 6)
        {

        ui->label_3->setText(str);
        ui->stackedWidget->setCurrentIndex(1);
        tablecolum();
        ui->tableWidget_9->setRowCount(22);
        ui->tableWidget_9->resize(688,700);

        int r=15;
        for(int j=0; j<23 ;j++)
        {
            ui->tableWidget_9->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "1 Revolution (Forward)"<<"1 Revolution (Reverse)"<<"2 Revolution (Forward)"<<"2 Revolution (Reverse)"<<"3 Revolution (Forward)"<<"3 Revolution (Reverse)"<<"4 Revolution (Forward)"<<"4 Revolution (Reverse)"<<"5 Revolution (Forward)"<<"5 Revolution (Reverse)"<<"6 Revolution (Forward)"<<"6 Revolution (Reverse)"<<"7 Revolution (Forward)"<<"7 Revolution (Reverse)"<<"8 Revolution (Forward)"<<"8 Revolution (Reverse)"<<"9 Revolution (Forward)"<<"9 Revolution (Reverse)"<<"10 Revolution (Forward)"<<"10 Revolution (Reverse)";
        ui->tableWidget_9->setVerticalHeaderLabels(v1);
        }

    if(ui->comboBox->currentIndex()== 7)
        {

        ui->label_3->setText(str);
        ui->stackedWidget->setCurrentIndex(4);
        tablecolum1();
        ui->tableWidget_3->setRowCount(4);


         ui->tableWidget_3->setGeometry(40,130,688,170);
         ui->groupBox_17->setGeometry(40,380,461,211);
         ui->label_109->setGeometry(370,640,381,17);
         ui->label_157->setGeometry(320,710,61,61);
         ui->tableWidget_6->setGeometry(410,710,270,221);
         ui->label_154->setGeometry(720,720,171,101);
         ui->pushButton_35->setGeometry(50,950,101,31);
         ui->pushButton_82->setGeometry(1070,910,99,28);
         ui->scrollAreaWidgetContents_7->setGeometry(0,0,1309,1100);


        int r=25;
        for(int j=0; j<4;j++)
        {
            ui->tableWidget_3->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "1 Revolution (Forward)"<<"1 Revolution (Reverse)";
        ui->tableWidget_3->setVerticalHeaderLabels(v1);
        }

    if(ui->comboBox->currentIndex()== 8)
        {

        ui->label_3->setText(str);
        ui->stackedWidget->setCurrentIndex(4);
        tablecolum1();
        ui->tableWidget_3->setRowCount(12);
        ui->tableWidget_3->resize(677,400);

        int r=25;
        for(int j=0; j<11 ;j++)
        {
            ui->tableWidget_3->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "1 Revolution (Forward)"<<"1 Revolution (Reverse)"<<"2 Revolution (Forward)"<<"2 Revolution (Reverse)"<<"3 Revolution (Forward)"<<"3 Revolution (Reverse)"<<"4 Revolution (Forward)"<<"4 Revolution (Reverse)"<<"5 Revolution (Forward)"<<"5 Revolution (Reverse)";
        ui->tableWidget_3->setVerticalHeaderLabels(v1);
    }

    if(ui->comboBox->currentIndex()== 9)
    {
        ui->label_3->setText(str);
        ui->stackedWidget->setCurrentIndex(1);
        tablecolum();
        ui->tableWidget_9->setRowCount(22);
        ui->tableWidget_9->resize(688,700);

        int r=15;
        for(int j=0; j<23 ;j++)
        {
            ui->tableWidget_9->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "1 Revolution (Forward)"<<"1 Revolution (Reverse)"<<"2 Revolution (Forward)"<<"2 Revolution (Reverse)"<<"3 Revolution (Forward)"<<"3 Revolution (Reverse)"<<"4 Revolution (Forward)"<<"4 Revolution (Reverse)"<<"5 Revolution (Forward)"<<"5 Revolution (Reverse)"<<"6 Revolution (Forward)"<<"6 Revolution (Reverse)"<<"7 Revolution (Forward)"<<"7 Revolution (Reverse)"<<"8 Revolution (Forward)"<<"8 Revolution (Reverse)"<<"9 Revolution (Forward)"<<"9 Revolution (Reverse)"<<"10 Revolution (Forward)"<<"10 Revolution (Reverse)";
        ui->tableWidget_9->setVerticalHeaderLabels(v1);
    }

    if(ui->comboBox->currentIndex()== 10)
    {
        ui->label_3->setText(str);
        ui->stackedWidget->setCurrentIndex(1);
        tablecolum1();
        ui->tableWidget_9->setRowCount(22);
        ui->tableWidget_9->resize(688,700);

        int r=15;
        for(int j=0; j<23 ;j++)
        {
            ui->tableWidget_9->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "1 Revolution (Forward)"<<"1 Revolution (Reverse)"<<"2 Revolution (Forward)"<<"2 Revolution (Reverse)"<<"3 Revolution (Forward)"<<"3 Revolution (Reverse)"<<"4 Revolution (Forward)"<<"4 Revolution (Reverse)"<<"5 Revolution (Forward)"<<"5 Revolution (Reverse)"<<"6 Revolution (Forward)"<<"6 Revolution (Reverse)"<<"7 Revolution (Forward)"<<"7 Revolution (Reverse)"<<"8 Revolution (Forward)"<<"8 Revolution (Reverse)"<<"9 Revolution (Forward)"<<"9 Revolution (Reverse)"<<"10 Revolution (Forward)"<<"10 Revolution (Reverse)";
        ui->tableWidget_9->setVerticalHeaderLabels(v1);

    }

    if(ui->comboBox->currentIndex()==11)
    {
        ui->label_3->setText(str);
        ui->stackedWidget->setCurrentIndex(1);
        tablecolum1();
        ui->tableWidget_9->setRowCount(22);
        ui->tableWidget_9->resize(688,700);

        int r=15;
        for(int j=0; j<23 ;j++)
        {
            ui->tableWidget_9->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "1 Revolution (Forward)"<<"1 Revolution (Reverse)"<<"2 Revolution (Forward)"<<"2 Revolution (Reverse)"<<"3 Revolution (Forward)"<<"3 Revolution (Reverse)"<<"4 Revolution (Forward)"<<"4 Revolution (Reverse)"<<"5 Revolution (Forward)"<<"5 Revolution (Reverse)"<<"6 Revolution (Forward)"<<"6 Revolution (Reverse)"<<"7 Revolution (Forward)"<<"7 Revolution (Reverse)"<<"8 Revolution (Forward)"<<"8 Revolution (Reverse)"<<"9 Revolution (Forward)"<<"9 Revolution (Reverse)"<<"10 Revolution (Forward)"<<"10 Revolution (Reverse)";
        ui->tableWidget_9->setVerticalHeaderLabels(v1);
    }

    if(ui->comboBox->currentIndex()==12)
    {
        ui->label_3->setText(str);
        ui->stackedWidget->setCurrentIndex(1);
        for(int a=0; a<10 ;a++)
        {
        ui->tableWidget_9->insertColumn(a);
        }
        int s =50;
        for(int b=0; b<10 ;b++)
        {
        ui->tableWidget_9->setColumnWidth(b,s);
        }
        QStringList h1;
        h1 <<"0" << "5"<<"10"<<"15"<<"20"<<"25"<<"20"<<"15"<<"10"<<"5";
        ui->tableWidget_9->setHorizontalHeaderLabels(h1);

        for(int i=0; i<16 ;i++)
        {
          ui->tableWidget_9->insertRow(i);
        }
        ui->tableWidget_9->setFixedHeight(425);
         ui->tableWidget_9->setFixedWidth(642);
        int r=25;
        for(int j=0; j<16 ;j++)
        {
            ui->tableWidget_9->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "1 Revolution (Forward)"<<"1 Revolution (Reverse)"<<"2 Revolution (Forward)"<<"2 Revolution (Reverse)"<<"3 Revolution (Forward)"<<"3 Revolution (Reverse)"<<"4 Revolution (Forward)"<<"4 Revolution (Reverse)"<<"5 Revolution (Forward)"<<"5 Revolution (Reverse)"<<"6 Revolution (Forward)"<<"6 Revolution (Reverse)"<<"7 Revolution (Forward)"<<"7 Revolution (Reverse)";
        ui->tableWidget_9->setVerticalHeaderLabels(v1);
    }

    if(ui->comboBox->currentIndex()==13)
    {
       ui->label_120->setText(str);
       ui->stackedWidget->setCurrentIndex(3);
       ui->tableWidget_2->setSpan(0,1,1,2);
       ui->tableWidget_2->setSpan(0,0,2,1);
       ui->tableWidget_2->setRowCount(8);
       ui->tableWidget_2->setFixedWidth(378);
       ui->tableWidget_2->setFixedHeight(298);
       ui->tableWidget_2->setItem(0,0,new QTableWidgetItem (QString("Reference value (mm)")));
       ui->tableWidget_2->setItem(0,1,new QTableWidgetItem (QString("Observed Error (µm) ")));
       ui->tableWidget_2->setItem(1,1,new QTableWidgetItem (QString("L.H.S")));
       ui->tableWidget_2->setItem(1,2,new QTableWidgetItem (QString("R.H.S")));
       ui->tableWidget_2->setItem(2,0,new QTableWidgetItem (QString("0")));
       ui->tableWidget_2->setItem(3,0,new QTableWidgetItem (QString("0.01")));
       ui->tableWidget_2->setItem(4,0,new QTableWidgetItem (QString("0.02")));
       ui->tableWidget_2->setItem(5,0,new QTableWidgetItem (QString("0.03")));
       ui->tableWidget_2->setItem(6,0,new QTableWidgetItem (QString("0.04")));
       ui->tableWidget_2->setItem(7,0,new QTableWidgetItem (QString("0.05")));
       ui->tableWidget_2->setItem(2,1,new QTableWidgetItem (QString("SET")));
       ui->tableWidget_2->setItem(2,2,new QTableWidgetItem (QString("SET")));
       ui->tableWidget_2->horizontalHeader()->setVisible(false);
       ui->tableWidget_2->verticalHeader()->setVisible(false);
    }

    if(ui->comboBox->currentIndex()==14)
    {
        ui->label_120->setText(str);
        ui->stackedWidget->setCurrentIndex(3);
        ui->scrollAreaWidgetContents_3->setGeometry(11,11,1437,1750);
        ui->tableWidget_2->setSpan(0,1,1,2);
        ui->tableWidget_2->setSpan(0,0,2,1);
        ui->tableWidget_2->setRowCount(12);
        ui->tableWidget_2->setFixedWidth(378);
        ui->tableWidget_2->setFixedHeight(450);
        ui->tableWidget_2->setItem(0,0,new QTableWidgetItem (QString("Reference value (mm)")));
        ui->tableWidget_2->setItem(0,1,new QTableWidgetItem (QString("Observed Error (µm) ")));
        ui->tableWidget_2->setItem(1,1,new QTableWidgetItem (QString("L.H.S")));
        ui->tableWidget_2->setItem(1,2,new QTableWidgetItem (QString("R.H.S")));
        ui->tableWidget_2->setItem(2,0,new QTableWidgetItem (QString("0")));
        ui->tableWidget_2->setItem(3,0,new QTableWidgetItem (QString("0.01")));
        ui->tableWidget_2->setItem(4,0,new QTableWidgetItem (QString("0.02")));
        ui->tableWidget_2->setItem(5,0,new QTableWidgetItem (QString("0.03")));
        ui->tableWidget_2->setItem(6,0,new QTableWidgetItem (QString("0.04")));
        ui->tableWidget_2->setItem(7,0,new QTableWidgetItem (QString("0.05")));
        ui->tableWidget_2->setItem(8,0,new QTableWidgetItem (QString("0.05")));
        ui->tableWidget_2->setItem(9,0,new QTableWidgetItem (QString("0.05")));
        ui->tableWidget_2->setItem(10,0,new QTableWidgetItem (QString("0.05")));
        ui->tableWidget_2->setItem(11,0,new QTableWidgetItem (QString("0.05")));
        ui->tableWidget_2->setItem(2,1,new QTableWidgetItem (QString("SET")));
        ui->tableWidget_2->setItem(2,2,new QTableWidgetItem (QString("SET")));
        ui->tableWidget_2->horizontalHeader()->setVisible(false);
        ui->tableWidget_2->verticalHeader()->setVisible(false);

    }

    if(ui->comboBox->currentIndex()==15)
    {
        ui->label_120->setText(str);
        ui->stackedWidget->setCurrentIndex(3);
        ui->scrollAreaWidgetContents_3->setGeometry(11,11,1437,1750);
        ui->tableWidget_2->setSpan(0,1,1,2);
        ui->tableWidget_2->setSpan(0,0,2,1);
        ui->tableWidget_2->setRowCount(8);
        ui->tableWidget_2->setFixedWidth(378);
        ui->tableWidget_2->setFixedHeight(298);
        ui->tableWidget_2->setItem(0,0,new QTableWidgetItem (QString("Reference value (mm)")));
        ui->tableWidget_2->setItem(0,1,new QTableWidgetItem (QString("Observed Error (µm) ")));
        ui->tableWidget_2->setItem(1,1,new QTableWidgetItem (QString(" (-Ve Side)")));
        ui->tableWidget_2->setItem(1,2,new QTableWidgetItem (QString(" (+Ve Side)")));
        ui->tableWidget_2->setItem(2,0,new QTableWidgetItem (QString("0")));
        ui->tableWidget_2->setItem(3,0,new QTableWidgetItem (QString("0.01")));
        ui->tableWidget_2->setItem(4,0,new QTableWidgetItem (QString("0.02")));
        ui->tableWidget_2->setItem(5,0,new QTableWidgetItem (QString("0.03")));
        ui->tableWidget_2->setItem(6,0,new QTableWidgetItem (QString("0.04")));
        ui->tableWidget_2->setItem(7,0,new QTableWidgetItem (QString("0.05")));
        ui->tableWidget_2->setItem(2,1,new QTableWidgetItem (QString("SET")));
        ui->tableWidget_2->setItem(2,2,new QTableWidgetItem (QString("SET")));
        ui->tableWidget_2->horizontalHeader()->setVisible(false);
        ui->tableWidget_2->verticalHeader()->setVisible(false);

    }

    if(ui->comboBox->currentIndex()==16)
    {
        ui->label_3->setText(str);
        ui->stackedWidget->setCurrentIndex(1);
        tablecolum();
        for(int i=0; i<42 ;i++)
        {
          ui->tableWidget_9->insertRow(i);
        }
        ui->tableWidget_9->setFixedHeight(1300);
         ui->tableWidget_9->setFixedWidth(695);
        int r=18;
        for(int j=0; j<42 ;j++)
        {
            ui->tableWidget_9->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "1 Revolution (Forward)"<<"1 Revolution (Reverse)"<<"2 Revolution (Forward)"<<"2 Revolution (Reverse)"<<"3 Revolution (Forward)"<<"3 Revolution (Reverse)"<<"4 Revolution (Forward)"<<"4 Revolution (Reverse)"<<"5 Revolution (Forward)"<<"5 Revolution (Reverse)"<<"6 Revolution (Forward)"<<"6 Revolution (Reverse)"<<"7 Revolution (Forward)"<<"7 Revolution (Reverse)"<<"8 Revolution (Forward)"<<"8 Revolution (Reverse)"<<"9 Revolution (Forward)"<<"9 Revolution (Reverse)"<<"10 Revolution (Forward)"<<"10 Revolution (Reverse)" << "11 Revolution (Forward)"<<"11 Revolution (Reverse)"<<"12 Revolution (Forward)"<<"12 Revolution (Reverse)"<<"13 Revolution (Forward)"<<"13 Revolution (Reverse)"<<"14 Revolution (Forward)"<<"14 Revolution (Reverse)"<<"15 Revolution (Forward)"<<"15 Revolution (Reverse)"<<"16 Revolution (Forward)"<<"16 Revolution (Reverse)"<<"17 Revolution (Forward)"<<"17 Revolution (Reverse)"<<"18 Revolution (Forward)"<<"18 Revolution (Reverse)"<<"19 Revolution (Forward)"<<"19 Revolution (Reverse)"<<"20 Revolution (Forward)"<<"20 Revolution (Reverse)";
        ui->tableWidget_9->setVerticalHeaderLabels(v1);

        ui->scrollAreaWidgetContents_4->setGeometry(0,0,1309,1500);
    }

    if(ui->comboBox->currentIndex()==17)
    {
        ui->label_3->setText(str);
        ui->stackedWidget->setCurrentIndex(1);
        tablecolum();
        for(int i=0; i<47 ;i++)
        {
          ui->tableWidget_9->insertRow(i);
        }
        ui->tableWidget_9->setFixedHeight(1450);
         ui->tableWidget_9->setFixedWidth(695);
        int r=18;
        for(int j=0; j<47 ;j++)
        {
            ui->tableWidget_9->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "1 Revolution (Forward)"<<"1 Revolution (Reverse)"<<"2 Revolution (Forward)"<<"2 Revolution (Reverse)"<<"3 Revolution (Forward)"<<"3 Revolution (Reverse)"<<"4 Revolution (Forward)"<<"4 Revolution (Reverse)"<<"5 Revolution (Forward)"<<"5 Revolution (Reverse)"<<"6 Revolution (Forward)"<<"6 Revolution (Reverse)"<<"7 Revolution (Forward)"<<"7 Revolution (Reverse)"<<"8 Revolution (Forward)"<<"8 Revolution (Reverse)"<<"9 Revolution (Forward)"<<"9 Revolution (Reverse)"<<"10 Revolution (Forward)"<<"10 Revolution (Reverse)" << "11 Revolution (Forward)"<<"11 Revolution (Reverse)"<<"12 Revolution (Forward)"<<"12 Revolution (Reverse)"<<"13 Revolution (Forward)"<<"13 Revolution (Reverse)"<<"14 Revolution (Forward)"<<"14 Revolution (Reverse)"<<"15 Revolution (Forward)"<<"15 Revolution (Reverse)"<<"16 Revolution (Forward)"<<"16 Revolution (Reverse)"<<"17 Revolution (Forward)"<<"17 Revolution (Reverse)"<<"18 Revolution (Forward)"<<"18 Revolution (Reverse)"<<"19 Revolution (Forward)"<<"19 Revolution (Reverse)"<<"20 Revolution (Forward)"<<"20 Revolution (Reverse)"<< "21 Revolution (Forward)"<<"21 Revolution (Reverse)"<<"22 Revolution (Forward)"<<"22 Revolution (Reverse)"<<"23 Revolution (Forward)"<<"23 Revolution (Reverse)"<<"24 Revolution (Forward)"<<"24 Revolution (Reverse)"<<"25 Revolution (Forward)"<<"25 Revolution (Reverse)";
        ui->tableWidget_9->setVerticalHeaderLabels(v1);

        ui->scrollAreaWidgetContents_4->setGeometry(0,0,1309,1600);
    }

    if(ui->comboBox->currentIndex()==18)
    {
        ui->label_3->setText(str);
        ui->stackedWidget->setCurrentIndex(1);
        tablecolum();
        for(int i=0; i<42 ;i++)
        {
          ui->tableWidget_9->insertRow(i);
        }
        ui->tableWidget_9->setFixedHeight(1300);
         ui->tableWidget_9->setFixedWidth(695);
        int r=18;
        for(int j=0; j<42 ;j++)
        {
            ui->tableWidget_9->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "1 Revolution (Forward)"<<"1 Revolution (Reverse)"<<"2 Revolution (Forward)"<<"2 Revolution (Reverse)"<<"3 Revolution (Forward)"<<"3 Revolution (Reverse)"<<"4 Revolution (Forward)"<<"4 Revolution (Reverse)"<<"5 Revolution (Forward)"<<"5 Revolution (Reverse)"<<"6 Revolution (Forward)"<<"6 Revolution (Reverse)"<<"7 Revolution (Forward)"<<"7 Revolution (Reverse)"<<"8 Revolution (Forward)"<<"8 Revolution (Reverse)"<<"9 Revolution (Forward)"<<"9 Revolution (Reverse)"<<"10 Revolution (Forward)"<<"10 Revolution (Reverse)" << "12 Revolution (Forward)"<<"12 Revolution (Reverse)"<<"14 Revolution (Forward)"<<"14 Revolution (Reverse)"<<"16 Revolution (Forward)"<<"16 Revolution (Reverse)"<<"18 Revolution (Forward)"<<"18 Revolution (Reverse)"<<"20 Revolution (Forward)"<<"20 Revolution (Reverse)"<<"22 Revolution (Forward)"<<"22 Revolution (Reverse)"<<"24 Revolution (Forward)"<<"24 Revolution (Reverse)"<<"26 Revolution (Forward)"<<"26 Revolution (Reverse)"<<"28 Revolution (Forward)"<<"28 Revolution (Reverse)"<<"30 Revolution (Forward)"<<"30 Revolution (Reverse)";
        ui->tableWidget_9->setVerticalHeaderLabels(v1);

        ui->scrollAreaWidgetContents_4->setGeometry(0,0,1309,1500);

    }

    if(ui->comboBox->currentIndex()==19)
    {
        ui->label_3->setText(str);
        ui->stackedWidget->setCurrentIndex(1);
        tablecolum();
        for(int i=0; i<62 ;i++)
        {
          ui->tableWidget_9->insertRow(i);
        }
        ui->tableWidget_9->setFixedHeight(1900);
         ui->tableWidget_9->setFixedWidth(695);
        int r=18;
        for(int j=0; j<62 ;j++)
        {
            ui->tableWidget_9->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "1 Revolution (Forward)"<<"1 Revolution (Reverse)"<<"2 Revolution (Forward)"<<"2 Revolution (Reverse)"<<"3 Revolution (Forward)"<<"3 Revolution (Reverse)"<<"4 Revolution (Forward)"<<"4 Revolution (Reverse)"<<"5 Revolution (Forward)"<<"5 Revolution (Reverse)"<<"6 Revolution (Forward)"<<"6 Revolution (Reverse)"<<"7 Revolution (Forward)"<<"7 Revolution (Reverse)"<<"8 Revolution (Forward)"<<"8 Revolution (Reverse)"<<"9 Revolution (Forward)"<<"9 Revolution (Reverse)"<<"10 Revolution (Forward)"<<"10 Revolution (Reverse)" << "12 Revolution (Forward)"<<"12 Revolution (Reverse)"<<"14 Revolution (Forward)"<<"14 Revolution (Reverse)"<<"16 Revolution (Forward)"<<"16 Revolution (Reverse)"<<"18 Revolution (Forward)"<<"18 Revolution (Reverse)"<<"20 Revolution (Forward)"<<"20 Revolution (Reverse)"<<"22 Revolution (Forward)"<<"22 Revolution (Reverse)"<<"24 Revolution (Forward)"<<"24 Revolution (Reverse)"<<"26 Revolution (Forward)"<<"26 Revolution (Reverse)"<<"28 Revolution (Forward)"<<"28 Revolution (Reverse)"<<"30 Revolution (Forward)"<<"30 Revolution (Reverse)"<<"32 Revolution (Forward)"<<"32 Revolution (Reverse)"<<"34 Revolution (Forward)"<<"34 Revolution (Reverse)"<<"36 Revolution (Forward)"<<"36 Revolution (Reverse)"<<"38 Revolution (Forward)"<<"38 Revolution (Reverse)"<<"40 Revolution (Forward)"<<"40 Revolution (Reverse)"<<"42 Revolution (Forward)"<<"42 Revolution (Reverse)"<<"44 Revolution (Forward)"<<"44 Revolution (Reverse)"<<"46 Revolution (Forward)"<<"46 Revolution (Reverse)"<<"48 Revolution (Forward)"<<"48 Revolution (Reverse)"<<"50 Revolution (Forward)"<<"50 Revolution (Reverse)";
        ui->tableWidget_9->setVerticalHeaderLabels(v1);

        ui->scrollAreaWidgetContents_4->setGeometry(0,0,1309,2200);
    }

    if(ui->comboBox->currentIndex()==20)
    {
        ui->label_3->setText(str);
        ui->stackedWidget->setCurrentIndex(1);
        tablecolum1();
        for(int i=0; i<4 ;i++)
        {
          ui->tableWidget_9->insertRow(i);
        }


         ui->tableWidget_9->setGeometry(40,130,642,125);
         ui->groupBox_8->setGeometry(50,310,461,211);
         ui->label_59->setGeometry(210,610,351,17);
         ui->label_58->setGeometry(150,680,61,61);
         ui->tableWidget->setGeometry(250,680,270,181);
         ui->label_60->setGeometry(540,680,171,101);
         ui->pushButton_2->setGeometry(10,830,101,31);
         ui->pushButton_78->setGeometry(1030,850,99,28);
         ui->scrollAreaWidgetContents_4->setGeometry(0,0,1209,900);


        int r=25;
        for(int j=0; j<4;j++)
        {
            ui->tableWidget_9->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "1 Revolution (Forward)"<<"1 Revolution (Reverse)";
        ui->tableWidget_9->setVerticalHeaderLabels(v1);

    }

    if(ui->comboBox->currentIndex()==21)
    {
        ui->label_3->setText(str);
        ui->stackedWidget->setCurrentIndex(1);
        for(int i=0; i<5 ;i++)
        {
          ui->tableWidget_9->insertRow(i);
        }
        ui->tableWidget_9->setFixedHeight(200);
         ui->tableWidget_9->setFixedWidth(642);

        int r=25;
        for(int j=0; j<5;j++)
        {
            ui->tableWidget_9->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "1 Revolution (Forward)"<<"1 Revolution (Reverse)"<<"2 Revolution (Forward)"<<"2 Revolution (Reverse)";
        ui->tableWidget_9->setVerticalHeaderLabels(v1);

        for(int i=0; i<10 ;i++)
        {
        ui->tableWidget_9->insertColumn(i);
        }
        int s =50;
        for(int j=0; j<10 ;j++)
        {
        ui->tableWidget_9->setColumnWidth(j,s);
        }
        QStringList h1;
        h1 <<"0" << "1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9";
        ui->tableWidget_9->setHorizontalHeaderLabels(h1);
    }

    if(ui->comboBox->currentIndex()==22)
    {
        ui->label_3->setText(str);
        ui->stackedWidget->setCurrentIndex(1);
        for(int i=0; i<5 ;i++)
        {
          ui->tableWidget_9->insertRow(i);
        }
        ui->tableWidget_9->setFixedHeight(200);
         ui->tableWidget_9->setFixedWidth(642);

        int r=25;
        for(int j=0; j<5;j++)
        {
            ui->tableWidget_9->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "1 Revolution (Forward)"<<"1 Revolution (Reverse)"<<"2 Revolution (Forward)"<<"2 Revolution (Reverse)";
        ui->tableWidget_9->setVerticalHeaderLabels(v1);

        for(int i=0; i<10 ;i++)
        {
        ui->tableWidget_9->insertColumn(i);
        }
        int s =50;
        for(int j=0; j<10 ;j++)
        {
        ui->tableWidget_9->setColumnWidth(j,s);
        }
        QStringList h1;
        h1 <<"0" << "10"<<"20"<<"30"<<"40"<<"50"<<"60"<<"70"<<"80"<<"90";
        ui->tableWidget_9->setHorizontalHeaderLabels(h1);
    }

    if(ui->comboBox->currentIndex()==23)
    {
        ui->label_3->setText(str);
        ui->stackedWidget->setCurrentIndex(1);
        tablecolum();
        for(int i=0; i<11 ;i++)
        {
          ui->tableWidget_9->insertRow(i);
        }
        ui->tableWidget_9->setFixedHeight(300);
         ui->tableWidget_9->setFixedWidth(642);
        int r=25;
        for(int j=0; j<11 ;j++)
        {
            ui->tableWidget_9->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "1 Revolution (Forward)"<<"1 Revolution (Reverse)"<<"2 Revolution (Forward)"<<"2 Revolution (Reverse)"<<"3 Revolution (Forward)"<<"3 Revolution (Reverse)"<<"4 Revolution (Forward)"<<"4 Revolution (Reverse)"<<"5 Revolution (Forward)"<<"5 Revolution (Reverse)";
        ui->tableWidget_9->setVerticalHeaderLabels(v1);
    }

    if(ui->comboBox->currentIndex()==25)
    {
                    ui->label_144->setText(str);
                    ui->lineEdit_74->setText(str1);
                    ui->lineEdit_75->setText(str2);
                    ui->lineEdit_68->setText(str3);
                    ui->lineEdit_67->setText(str4);

                    ui->scrollArea_5->verticalScrollBar()->setSliderPosition(0);

        ui->stackedWidget->setCurrentIndex(5);

        ui->tableWidget_4->setRowCount(4);
        ui->tableWidget_13->setRowCount(4);
        int r=15;
        for(int j=0; j<4 ;j++)
        {
            ui->tableWidget_4->setRowHeight(j,r);
            ui->tableWidget_13->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "Forward End"<<"Reverse End";
         ui->tableWidget_4->setVerticalHeaderLabels(v1);
          ui->tableWidget_13->setVerticalHeaderLabels(v1);


        ui->tableWidget_4->setColumnCount(10);
        ui->tableWidget_13->setColumnCount(10);


        int s =80;
        for(int j=0; j<10 ;j++)
        {
        ui->tableWidget_4->setColumnWidth(j,s);
        ui->tableWidget_13->setColumnWidth(j,s);
        }
        QStringList h1;
        h1 <<"0" <<"5" << "10"<<"15"<<"20"<<"25"<<"20"<<"15"<<"10"<<"5";
        ui->tableWidget_4->setHorizontalHeaderLabels(h1);
        ui->tableWidget_13->setHorizontalHeaderLabels(h1);

         ui->tableWidget_4->setFixedHeight(155);
         ui->tableWidget_4->setFixedWidth(911);
         ui->tableWidget_13->setFixedHeight(155);
         ui->tableWidget_13->setFixedWidth(911);

}

    if(ui->comboBox->currentIndex()==26)
    {
                    ui->label_144->setText(str);
                    ui->lineEdit_74->setText(str1);
                    ui->lineEdit_75->setText(str2);
                    ui->lineEdit_68->setText(str3);
                    ui->lineEdit_67->setText(str4);
                    //ui->lineEdit_10->setText(str5);
                    ui->scrollArea_5->verticalScrollBar()->setSliderPosition(0);

        ui->stackedWidget->setCurrentIndex(5);

        ui->tableWidget_4->setRowCount(4);
        ui->tableWidget_13->setRowCount(4);
        int r=15;
        for(int j=0; j<4 ;j++)
        {
            ui->tableWidget_4->setRowHeight(j,r);
            ui->tableWidget_13->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "Forward End"<<"Reverse End";
         ui->tableWidget_4->setVerticalHeaderLabels(v1);
          ui->tableWidget_13->setVerticalHeaderLabels(v1);


        ui->tableWidget_4->setColumnCount(5);
        ui->tableWidget_13->setColumnCount(5);


        int s =70;
        for(int j=0; j<5 ;j++)
        {
        ui->tableWidget_4->setColumnWidth(j,s);
        ui->tableWidget_13->setColumnWidth(j,s);
        }
        QStringList h1;
        h1 <<"0" <<"0.1" << "0.2"<<"0.2"<<"0.1";
        ui->tableWidget_4->setHorizontalHeaderLabels(h1);
        ui->tableWidget_13->setHorizontalHeaderLabels(h1);

         ui->tableWidget_4->setFixedHeight(155);
         ui->tableWidget_4->setFixedWidth(460);
         ui->tableWidget_13->setFixedHeight(155);
         ui->tableWidget_13->setFixedWidth(460);

}

    if(ui->comboBox->currentIndex()==27)
    {
        ui->label_144->setText(str);
        ui->lineEdit_74->setText(str1);
        ui->lineEdit_75->setText(str2);
        ui->lineEdit_68->setText(str3);
        ui->lineEdit_67->setText(str4);
        //ui->lineEdit_10->setText(str5);
        ui->scrollArea_5->verticalScrollBar()->setSliderPosition(0);

        ui->stackedWidget->setCurrentIndex(5);

        ui->tableWidget_4->setRowCount(4);
        ui->tableWidget_13->setRowCount(4);
        int r=15;
        for(int j=0; j<4 ;j++)
        {
        ui->tableWidget_4->setRowHeight(j,r);
        ui->tableWidget_13->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "Forward End"<<"Reverse End";
        ui->tableWidget_4->setVerticalHeaderLabels(v1);
        ui->tableWidget_13->setVerticalHeaderLabels(v1);


        ui->tableWidget_4->setColumnCount(8);
        ui->tableWidget_13->setColumnCount(8);


        int s =80;
        for(int j=0; j<8 ;j++)
        {
        ui->tableWidget_4->setColumnWidth(j,s);
        ui->tableWidget_13->setColumnWidth(j,s);
        }
        QStringList h1;
        h1 <<"0" <<"10" << "20"<<"30"<<"40"<<"30"<<"20"<<"10";
        ui->tableWidget_4->setHorizontalHeaderLabels(h1);
        ui->tableWidget_13->setHorizontalHeaderLabels(h1);

        ui->tableWidget_4->setFixedHeight(155);
        ui->tableWidget_4->setFixedWidth(750);
        ui->tableWidget_13->setFixedHeight(155);
        ui->tableWidget_13->setFixedWidth(750);


    }

    if(ui->comboBox->currentIndex()==28)
    {
        ui->label_144->setText(str);
        ui->lineEdit_74->setText(str1);
        ui->lineEdit_75->setText(str2);
        ui->lineEdit_68->setText(str3);
        ui->lineEdit_67->setText(str4);
        //ui->lineEdit_10->setText(str5);
        ui->scrollArea_5->verticalScrollBar()->setSliderPosition(0);

        ui->stackedWidget->setCurrentIndex(5);

        ui->tableWidget_4->setRowCount(4);
        ui->tableWidget_13->setRowCount(4);
        int r=15;
        for(int j=0; j<4 ;j++)
        {
        ui->tableWidget_4->setRowHeight(j,r);
        ui->tableWidget_13->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "Forward End"<<"Reverse End";
        ui->tableWidget_4->setVerticalHeaderLabels(v1);
        ui->tableWidget_13->setVerticalHeaderLabels(v1);


        ui->tableWidget_4->setColumnCount(10);
        ui->tableWidget_13->setColumnCount(10);


        int s =80;
        for(int j=0; j<10 ;j++)
        {
        ui->tableWidget_4->setColumnWidth(j,s);
        ui->tableWidget_13->setColumnWidth(j,s);
        }
        QStringList h1;
        h1 <<"0" <<"10"<<"20"<<"30"<<"40"<<"50"<<"40"<<"30"<<"20"<<"10";
        ui->tableWidget_4->setHorizontalHeaderLabels(h1);
        ui->tableWidget_13->setHorizontalHeaderLabels(h1);

        ui->tableWidget_4->setFixedHeight(155);
        ui->tableWidget_4->setFixedWidth(911);
        ui->tableWidget_13->setFixedHeight(155);
        ui->tableWidget_13->setFixedWidth(911);


    }

    if(ui->comboBox->currentIndex()==29)
    {
        ui->label_144->setText(str);
        ui->lineEdit_74->setText(str1);
        ui->lineEdit_75->setText(str2);
        ui->lineEdit_68->setText(str3);
        ui->lineEdit_67->setText(str4);
        //ui->lineEdit_10->setText(str5);
        ui->scrollArea_5->verticalScrollBar()->setSliderPosition(0);

        ui->stackedWidget->setCurrentIndex(5);

        ui->tableWidget_4->setRowCount(6);
        ui->tableWidget_13->setRowCount(6);
        int r=11;
        for(int j=0; j<6 ;j++)
        {
        ui->tableWidget_4->setRowHeight(j,r);
        ui->tableWidget_13->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" <<  "1 Revolution (Forward)"<<"1 Revolution (Reverse)"<<"2 Revolution (Forward)"<<"2 Revolution (Reverse)";
        ui->tableWidget_4->setVerticalHeaderLabels(v1);
        ui->tableWidget_13->setVerticalHeaderLabels(v1);


        ui->tableWidget_4->setColumnCount(8);
        ui->tableWidget_13->setColumnCount(8);


        int s =80;
        for(int j=0; j<8 ;j++)
        {
        ui->tableWidget_4->setColumnWidth(j,s);
        ui->tableWidget_13->setColumnWidth(j,s);
        }
        QStringList h1;
        h1 <<"0" <<"10" << "20"<<"30"<<"40"<<"30"<<"20"<<"10";
        ui->tableWidget_4->setHorizontalHeaderLabels(h1);
        ui->tableWidget_13->setHorizontalHeaderLabels(h1);

        ui->tableWidget_4->setFixedHeight(220);
        ui->tableWidget_4->setFixedWidth(820);
        ui->tableWidget_13->setFixedHeight(220);
        ui->tableWidget_13->setFixedWidth(820);


    }

    if(ui->comboBox->currentIndex()==30)
    {
        ui->label_144->setText(str);
        ui->lineEdit_74->setText(str1);
        ui->lineEdit_75->setText(str2);
        ui->lineEdit_68->setText(str3);
        ui->lineEdit_67->setText(str4);
        //ui->lineEdit_10->setText(str5);
        ui->scrollArea_5->verticalScrollBar()->setSliderPosition(0);

        ui->stackedWidget->setCurrentIndex(5);

        ui->tableWidget_4->setRowCount(4);
        ui->tableWidget_13->setRowCount(4);
        int r=15;
        for(int j=0; j<4 ;j++)
        {
        ui->tableWidget_4->setRowHeight(j,r);
        ui->tableWidget_13->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "Forward End"<<"Reverse End";
        ui->tableWidget_4->setVerticalHeaderLabels(v1);
        ui->tableWidget_13->setVerticalHeaderLabels(v1);


        ui->tableWidget_4->setColumnCount(14);
        ui->tableWidget_13->setColumnCount(14);


        int s =60;
        for(int j=0; j<14 ;j++)
        {
        ui->tableWidget_4->setColumnWidth(j,s);
        ui->tableWidget_13->setColumnWidth(j,s);
        }
        QStringList h1;
        h1 <<"0" <<"10"<<"20"<<"30"<<"40"<<"50"<<"60"<<"70"<<"60"<<"50"<<"40"<<"30"<<"20"<<"10";
        ui->tableWidget_4->setHorizontalHeaderLabels(h1);
        ui->tableWidget_13->setHorizontalHeaderLabels(h1);

        ui->tableWidget_4->setFixedHeight(160);
        ui->tableWidget_4->setFixedWidth(950);
        ui->tableWidget_13->setFixedHeight(160);
        ui->tableWidget_13->setFixedWidth(950);


    }

    if(ui->comboBox->currentIndex()==31)
    {
        ui->label_144->setText(str);
        ui->lineEdit_74->setText(str1);
        ui->lineEdit_75->setText(str2);
        ui->lineEdit_68->setText(str3);
        ui->lineEdit_67->setText(str4);
        ///ui->lineEdit_10->setText(str5);
        ui->scrollArea_5->verticalScrollBar()->setSliderPosition(0);

        ui->stackedWidget->setCurrentIndex(5);

        ui->tableWidget_4->setRowCount(4);
        ui->tableWidget_13->setRowCount(4);
        int r=15;
        for(int j=0; j<4 ;j++)
        {
        ui->tableWidget_4->setRowHeight(j,r);
        ui->tableWidget_13->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "Forward End"<<"Reverse End";
        ui->tableWidget_4->setVerticalHeaderLabels(v1);
        ui->tableWidget_13->setVerticalHeaderLabels(v1);


        ui->tableWidget_4->setColumnCount(10);
        ui->tableWidget_13->setColumnCount(10);


        int s =80;
        for(int j=0; j<10 ;j++)
        {
        ui->tableWidget_4->setColumnWidth(j,s);
        ui->tableWidget_13->setColumnWidth(j,s);
        }
        QStringList h1;
        h1 <<"0" <<"20"<<"40"<<"60"<<"80"<<"100"<<"80"<<"60"<<"40"<<"20";
        ui->tableWidget_4->setHorizontalHeaderLabels(h1);
        ui->tableWidget_13->setHorizontalHeaderLabels(h1);

        ui->tableWidget_4->setFixedHeight(155);
        ui->tableWidget_4->setFixedWidth(911);
        ui->tableWidget_13->setFixedHeight(155);
        ui->tableWidget_13->setFixedWidth(911);
    }

    if(ui->comboBox->currentIndex()==32)
    {
        ui->label_144->setText(str);
        ui->lineEdit_74->setText(str1);
        ui->lineEdit_75->setText(str2);
        ui->lineEdit_68->setText(str3);
        ui->lineEdit_67->setText(str4);
        //ui->lineEdit_10->setText(str5);
        ui->scrollArea_5->verticalScrollBar()->setSliderPosition(0);

        ui->stackedWidget->setCurrentIndex(5);

        ui->tableWidget_4->setRowCount(6);
        ui->tableWidget_13->setRowCount(6);
        int r=11;
        for(int j=0; j<6 ;j++)
        {
        ui->tableWidget_4->setRowHeight(j,r);
        ui->tableWidget_13->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" <<  "1 Revolution (Forward)"<<"1 Revolution (Reverse)"<<"2 Revolution (Forward)"<<"2 Revolution (Reverse)";
        ui->tableWidget_4->setVerticalHeaderLabels(v1);
        ui->tableWidget_13->setVerticalHeaderLabels(v1);

        ui->tableWidget_4->setColumnCount(10);
        ui->tableWidget_13->setColumnCount(10);

        int s =80;
        for(int j=0; j<10 ;j++)
        {
        ui->tableWidget_4->setColumnWidth(j,s);
        ui->tableWidget_13->setColumnWidth(j,s);
        }
        QStringList h1;
        h1 <<"0" <<"20"<<"40"<<"60"<<"80"<<"100"<<"80"<<"60"<<"40"<<"20";
        ui->tableWidget_4->setHorizontalHeaderLabels(h1);
        ui->tableWidget_13->setHorizontalHeaderLabels(h1);

        ui->tableWidget_4->setFixedHeight(220);
        ui->tableWidget_4->setFixedWidth(911);
        ui->tableWidget_13->setFixedHeight(220);
        ui->tableWidget_13->setFixedWidth(911);

    }

    if(ui->comboBox->currentIndex()==33)
    {
        ui->label_144->setText(str);
        ui->lineEdit_74->setText(str1);
        ui->lineEdit_75->setText(str2);
        ui->lineEdit_68->setText(str3);
        ui->lineEdit_67->setText(str4);
        //ui->lineEdit_10->setText(str5);
        ui->scrollArea_5->verticalScrollBar()->setSliderPosition(0);

        ui->stackedWidget->setCurrentIndex(5);

        ui->tableWidget_4->setRowCount(4);
        ui->tableWidget_13->setRowCount(4);
        int r=15;
        for(int j=0; j<4 ;j++)
        {
        ui->tableWidget_4->setRowHeight(j,r);
        ui->tableWidget_13->setRowHeight(j,r);
        }
        QStringList v1;
        v1 <<"Forward Start"<< "Reverse Start" << "Forward End"<<"Reverse End";
        ui->tableWidget_4->setVerticalHeaderLabels(v1);
        ui->tableWidget_13->setVerticalHeaderLabels(v1);


        ui->tableWidget_4->setColumnCount(8);
        ui->tableWidget_13->setColumnCount(8);


        int s =80;
        for(int j=0; j<8 ;j++)
        {
        ui->tableWidget_4->setColumnWidth(j,s);
        ui->tableWidget_13->setColumnWidth(j,s);
        }
        QStringList h1;
        h1 <<"0" <<"1" << "2"<<"3"<<"4"<<"3"<<"2"<<"1";
        ui->tableWidget_4->setHorizontalHeaderLabels(h1);
        ui->tableWidget_13->setHorizontalHeaderLabels(h1);

        ui->tableWidget_4->setFixedHeight(155);
        ui->tableWidget_4->setFixedWidth(750);
        ui->tableWidget_13->setFixedHeight(155);
        ui->tableWidget_13->setFixedWidth(750);


    }

    if(ui->comboBox->currentIndex()==35)
    {
          ui->label_168->setText(str);
          ui->lineEdit_83->setText(str1);
          ui->lineEdit_84->setText(str2);
          ui->lineEdit_89->setText(str3);
          ui->lineEdit_88->setText(str4);
          //ui->lineEdit_11->setText(str5);
          ui->stackedWidget->setCurrentIndex(6);
          ui->tableWidget_19->setRowCount(6);
          ui->tableWidget_19->setColumnCount(3);
          ui->tableWidget_19->verticalHeader()->setVisible(false);
          ui->tableWidget_17->horizontalHeader()->setVisible(false);
          ui->tableWidget_19->setItem(0,0,new QTableWidgetItem (QString("0")));
          ui->tableWidget_19->setItem(1,0,new QTableWidgetItem (QString("0.1")));
          ui->tableWidget_19->setItem(2,0,new QTableWidgetItem (QString("0.2")));
          ui->tableWidget_19->setItem(3,0,new QTableWidgetItem (QString("0.3")));
          ui->tableWidget_19->setItem(4,0,new QTableWidgetItem (QString("0.4")));
          ui->tableWidget_19->setItem(5,0,new QTableWidgetItem (QString("0.5")));
          int s =250;
          for(int j=0; j<2 ;j++)
          {
          ui->tableWidget_19->setColumnWidth(j,s);

          }
          ui->tableWidget_19->setColumnWidth(2,100);
          QStringList h1;
          h1 <<"Reference value on Bore Gauge" <<"Observed value on Master (DCT)" << "Error";
          ui->tableWidget_19->setHorizontalHeaderLabels(h1);

          ui->tableWidget_19->item(0,0)->setTextAlignment(Qt::AlignCenter);
          ui->tableWidget_19->item(1,0)->setTextAlignment(Qt::AlignCenter);
          ui->tableWidget_19->item(2,0)->setTextAlignment(Qt::AlignCenter);
          ui->tableWidget_19->item(3,0)->setTextAlignment(Qt::AlignCenter);
          ui->tableWidget_19->item(4,0)->setTextAlignment(Qt::AlignCenter);
          ui->tableWidget_19->item(5,0)->setTextAlignment(Qt::AlignCenter);

          ui->tableWidget_19->setFixedWidth(610);
          ui->tableWidget_19->setFixedHeight(260);


    }

    if(ui->comboBox->currentIndex()==36)
    {
          ui->label_168->setText(str);
          ui->lineEdit_83->setText(str1);
          ui->lineEdit_84->setText(str2);
          ui->lineEdit_89->setText(str3);
          ui->lineEdit_88->setText(str4);
          //ui->lineEdit_11->setText(str5);
          ui->stackedWidget->setCurrentIndex(6);
          ui->tableWidget_19->setRowCount(7);
          ui->tableWidget_19->setColumnCount(3);
          ui->tableWidget_19->verticalHeader()->setVisible(false);
          ui->tableWidget_17->horizontalHeader()->setVisible(false);

          ui->tableWidget_19->setItem(0,0,new QTableWidgetItem (QString("0")));
          ui->tableWidget_19->setItem(1,0,new QTableWidgetItem (QString("0.1")));
          ui->tableWidget_19->setItem(2,0,new QTableWidgetItem (QString("0.2")));
          ui->tableWidget_19->setItem(3,0,new QTableWidgetItem (QString("0.3")));
          ui->tableWidget_19->setItem(4,0,new QTableWidgetItem (QString("0.4")));
          ui->tableWidget_19->setItem(5,0,new QTableWidgetItem (QString("0.5")));
          ui->tableWidget_19->setItem(6,0,new QTableWidgetItem (QString("0.6")));


          int s =250;
          for(int j=0; j<2 ;j++)
          {
          ui->tableWidget_19->setColumnWidth(j,s);

          }
          ui->tableWidget_19->setColumnWidth(2,100);
          QStringList h1;
          h1 <<"Reference value on Bore Gauge" <<"Observed value on Master (DCT)" << "Error";
          ui->tableWidget_19->setHorizontalHeaderLabels(h1);

              ui->tableWidget_19->item(0,0)->setTextAlignment(Qt::AlignCenter);
              ui->tableWidget_19->item(1,0)->setTextAlignment(Qt::AlignCenter);
              ui->tableWidget_19->item(2,0)->setTextAlignment(Qt::AlignCenter);
              ui->tableWidget_19->item(3,0)->setTextAlignment(Qt::AlignCenter);
              ui->tableWidget_19->item(4,0)->setTextAlignment(Qt::AlignCenter);
              ui->tableWidget_19->item(5,0)->setTextAlignment(Qt::AlignCenter);
              ui->tableWidget_19->item(6,0)->setTextAlignment(Qt::AlignCenter);

              ui->tableWidget_19->setFixedWidth(610);
              ui->tableWidget_19->setFixedHeight(300);

    }

    if(ui->comboBox->currentIndex()==37)
    {
          ui->label_168->setText(str);
          ui->lineEdit_83->setText(str1);
          ui->lineEdit_84->setText(str2);
          ui->lineEdit_89->setText(str3);
          ui->lineEdit_88->setText(str4);
          //ui->lineEdit_11->setText(str5);
          ui->stackedWidget->setCurrentIndex(6);
          ui->tableWidget_19->setRowCount(6);
          ui->tableWidget_19->setColumnCount(3);
          ui->tableWidget_19->verticalHeader()->setVisible(false);
          ui->tableWidget_17->horizontalHeader()->setVisible(false);
          ui->tableWidget_19->setItem(0,0,new QTableWidgetItem (QString("0")));
          ui->tableWidget_19->setItem(1,0,new QTableWidgetItem (QString("0.1")));
          ui->tableWidget_19->setItem(2,0,new QTableWidgetItem (QString("0.2")));
          ui->tableWidget_19->setItem(3,0,new QTableWidgetItem (QString("0.3")));
          ui->tableWidget_19->setItem(4,0,new QTableWidgetItem (QString("0.4")));
          ui->tableWidget_19->setItem(5,0,new QTableWidgetItem (QString("0.5")));
          int s =250;
          for(int j=0; j<2 ;j++)
          {
          ui->tableWidget_19->setColumnWidth(j,s);

          }
          ui->tableWidget_19->setColumnWidth(2,100);
          QStringList h1;
          h1 <<"Reference value on Bore Gauge" <<"Observed value on Master (DCT)" << "Error";
          ui->tableWidget_19->setHorizontalHeaderLabels(h1);

          ui->tableWidget_19->item(0,0)->setTextAlignment(Qt::AlignCenter);
          ui->tableWidget_19->item(1,0)->setTextAlignment(Qt::AlignCenter);
          ui->tableWidget_19->item(2,0)->setTextAlignment(Qt::AlignCenter);
          ui->tableWidget_19->item(3,0)->setTextAlignment(Qt::AlignCenter);
          ui->tableWidget_19->item(4,0)->setTextAlignment(Qt::AlignCenter);
          ui->tableWidget_19->item(5,0)->setTextAlignment(Qt::AlignCenter);

          ui->tableWidget_19->setFixedWidth(610);
          ui->tableWidget_19->setFixedHeight(260);


    }

}
void MCALIB::on_pushButton_78_clicked()                //Plunger Dial Gauge 0.01-5mm mcalib page  next button
{
      ui->stackedWidget->setCurrentIndex(2);
      ui->stackedWidget->scroll(9,9);
}
void MCALIB::on_pushButton_2_clicked()                  //Plunger Dial Gauge 0.01-5mm mcalib page  back button
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableWidget_9->setRowCount(0);
    ui->tableWidget_9->setColumnCount(0);
    ui->stackedWidget->scroll(9,9);

}
void MCALIB::on_pushButton_3_clicked()                     //Plunger Dial Gauge calibration certificate page  back button
{ 
    ui->stackedWidget->setCurrentIndex(1);
    //ui->scrollArea_3->setHorizontalScrollBar();
    ui->stackedWidget->unsetCursor();
}
void MCALIB::on_pushButton_35_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableWidget_3->setRowCount(0);
    ui->tableWidget_3->setColumnCount(0);
    ui->stackedWidget->scroll(9,9);

}
void MCALIB::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableWidget_3->setRowCount(0);
    ui->tableWidget_3->setColumnCount(0);
    ui->stackedWidget->scroll(9,9);

    ui->pushButton_9->setVisible(true);
}
void MCALIB::on_pushButton_82_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
    //ui->scrollArea_3->setHorizontalScrollBar();
    ui->stackedWidget->unsetCursor();
}
void MCALIB::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableWidget_3->setRowCount(0);
    ui->tableWidget_3->setColumnCount(0);
    ui->stackedWidget->scroll(9,9);
}
void MCALIB::on_pushButton_6_clicked()
{

    QList <QWidget *> widgets;
    widgets.append({ui->scrollAreaWidgetContents_7, ui->scrollAreaWidgetContents_6});

    QPrinter printer(QPrinter::HighResolution);

 const QString name = ui->lineEdit_362->text() +".pdf";
    printer.setOutputFormat(QPrinter::PdfFormat);
   printer.setOutputFileName(name);
   // printer.setOrientation(QPrinter::Landscape);
    // printer.setPaperSize(QPrinter::A4);
    QPainter painter;

    if (! painter.begin(&printer)) { // failed to open file
        qWarning("failed to open file, is it writable?");
    }

    for(auto widget: widgets){
        ui->pushButton_17->setVisible(false);
         ui->pushButton_15->setVisible(false);
          ui->import_2->setVisible(false);
           ui->pushButton_35->setVisible(false);
             ui->pushButton_6->setVisible(false);
               ui->pushButton_82->setVisible(false);
               ui->pushButton_16->setVisible(false);
        if(widget){
            if(widget->width() > 0 && widget->height() >0 ){

                qreal xscale = printer.pageRect().width()/qreal(widget->width());
                qreal yscale = printer.pageRect().height()/qreal(widget->height());

                qreal scale = qMin(xscale, yscale);

                painter.translate(printer.paperRect().x() + printer.pageRect().width()/1.5,
                                  printer.paperRect().y() + printer.pageRect().height()/2.5);

                painter.scale(scale, scale);
                painter.translate(-widget->width()/1.5, -widget->height()/2.5);
                widget->render(&painter);
                painter.resetTransform();
                if(widget != widgets.last())
                    printer.newPage();
            }
        }
        ui->pushButton_17->setVisible(true);
         ui->pushButton_15->setVisible(true);
          ui->import_2->setVisible(true);
           ui->pushButton_35->setVisible(true);
             ui->pushButton_6->setVisible(true);
               ui->pushButton_82->setVisible(true);
               ui->pushButton_16->setVisible(true);

    }
    painter.end();



}
void MCALIB::on_import_3_clicked()
{

    filename =  QFileDialog::getOpenFileName(
                  this,
                  "Open Document",
                  QDir::currentPath(),
                  "All files (*.*) ;; Document files (*.csv *.rtf);; PNG files (*.png)");
            if( !filename.isNull() )
            {
              qDebug() << "selected file path : " <<filename.toUtf8();
            }
            QFileInfo info(filename);
            QString filename1 = info.path() + "/" + info.completeBaseName() + ".csv";
              QFile file(filename1.toUtf8());
              QTextStream in(&file);
              int line_count=0;
                if(!file.open(QIODevice::ReadOnly)) {
                    QMessageBox::information(0, "error", file.errorString());
                }




                while(!in.atEnd())
                             {
                                QString line=in.readLine();
                                QStringList line_data=line.split(",",QString::SkipEmptyParts);
                              for(int j=0;j<line_data.size();j++)
                              {
                                  QString m_prop=line_data.at(j);
                                  //QStandardItem *item=new QStandardItem(m_prop);  this is for tableview
                                  QTableWidgetItem *it=new QTableWidgetItem(m_prop,1002);
                                  //model->setItem(line_count,j,item);

                                  ui->tableWidget_9->setItem(line_count,j,it);
                                  // ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
                             // ui->tableWidget->setItem();
                              }
                              line_count++;
                             }
                file.close();

}
void MCALIB::on_pushButton_10_clicked()
{
    QList <QWidget *> widgets;
    widgets.append({ui->scrollAreaWidgetContents_4, ui->scrollAreaWidgetContents_2});

    QPrinter printer(QPrinter::HighResolution);

 const QString name = ui->lineEdit_362->text() +".pdf";
    printer.setOutputFormat(QPrinter::PdfFormat);
   printer.setOutputFileName(name);
   // printer.setOrientation(QPrinter::Landscape);
    // printer.setPaperSize(QPrinter::A4);
    QPainter painter;

    if (! painter.begin(&printer)) { // failed to open file
        qWarning("failed to open file, is it writable?");
    }

    for(auto widget: widgets){
         ui->pushButton_11->setVisible(false);
          ui->pushButton_7->setVisible(false);
           ui->import_3->setVisible(false);
            ui->pushButton_10->setVisible(false);
        if(widget){
            if(widget->width() > 0 && widget->height() >0 ){

                qreal xscale = printer.pageRect().width()/qreal(widget->width());
                qreal yscale = printer.pageRect().height()/qreal(widget->height());

                qreal scale = qMin(xscale, yscale);

                painter.translate(printer.paperRect().x() + printer.pageRect().width()/1.5,
                                  printer.paperRect().y() + printer.pageRect().height()/2.5);

                painter.scale(scale, scale);
                painter.translate(-widget->width()/1.5, -widget->height()/2.5);
                widget->render(&painter);
                painter.resetTransform();
                if(widget != widgets.last())
                    printer.newPage();
            }
        }

    }

    painter.end();
    ui->pushButton_11->setVisible(true);
     ui->pushButton_7->setVisible(true);
      ui->import_3->setVisible(true);
       ui->pushButton_10->setVisible(true);
}
void MCALIB::on_pushButton_12_clicked()
{
    QList <QWidget *> widgets;
    widgets.append({ui->scrollAreaWidgetContents_3});

    QPrinter printer(QPrinter::HighResolution);

 const QString name = ui->lineEdit_362->text() +".pdf";
    printer.setOutputFormat(QPrinter::PdfFormat);
   printer.setOutputFileName(name);
   // printer.setOrientation(QPrinter::Landscape);
    // printer.setPaperSize(QPrinter::A4);
    QPainter painter;

    if (! painter.begin(&printer)) { // failed to open file
        qWarning("failed to open file, is it writable?");
    }

    for(auto widget: widgets){
        ui->pushButton_15->setVisible(false);
         ui->pushButton_16->setVisible(false);
          ui->import_2->setVisible(false);
           ui->pushButton_12->setVisible(false);
        if(widget){
            if(widget->width() > 0 && widget->height() >0 ){

                qreal xscale = printer.pageRect().width()/qreal(widget->width());
                qreal yscale = printer.pageRect().height()/qreal(widget->height());

                qreal scale = qMin(xscale, yscale);

                painter.translate(printer.paperRect().x() + printer.pageRect().width()/1.5,
                                  printer.paperRect().y() + printer.pageRect().height()/2.5);

                painter.scale(scale, scale);
                painter.translate(-widget->width()/1.5, -widget->height()/2.5);
                widget->render(&painter);
                painter.resetTransform();
                if(widget != widgets.last())
                    printer.newPage();
            }
        }

    }
    painter.end();
    ui->pushButton_15->setVisible(true);
     ui->pushButton_16->setVisible(true);
      ui->import_2->setVisible(true);
       ui->pushButton_12->setVisible(true);
}
void MCALIB::on_import_c_clicked()
{




    filename =  QFileDialog::getOpenFileName(
                  this,
                  "Open Document",
                  QDir::currentPath(),
                  "All files (*.*) ;; Document files (*.csv *.rtf );; PNG files (*.png)");
            if( !filename.isNull() )
            {
              qDebug() << "selected file path : " <<filename.toUtf8();
            }
            QFileInfo info(filename);
            QString filename1 = info.path() + "/" + info.completeBaseName() + ".csv";
              QFile file(filename1.toUtf8());
              QTextStream in(&file);
              int line_count=0;
                if(!file.open(QIODevice::ReadOnly)) {
                    QMessageBox::information(0, "error", file.errorString());
                }




                while(!in.atEnd())
                             {
                                QString line=in.readLine();
                                QStringList line_data=line.split(",",QString::SkipEmptyParts);
                              for(int j=5;j<line_data.size();j++)
                              {
                                  QString m_prop=line_data.at(j);
                                  //QStandardItem *item=new QStandardItem(m_prop);  this is for tableview
                                  QTableWidgetItem *it=new QTableWidgetItem(m_prop,1002);
                                  //model->setItem(line_count,j,item);

                                  ui->tableWidget_2->setItem(line_count,j,it);
                                  // ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
                             // ui->tableWidget->setItem();
                              }
                              line_count++;
                             }
                file.close();
}
void MCALIB::on_pushButton_9_clicked()
{



    QList <QWidget *> widgets;
    widgets.append({ui->scrollAreaWidgetContents_5});

    QPrinter printer(QPrinter::HighResolution);

 const QString name = ui->lineEdit_362->text() +".pdf";
    printer.setOutputFormat(QPrinter::PdfFormat);
   printer.setOutputFileName(name);
   // printer.setOrientation(QPrinter::Landscape);
    // printer.setPaperSize(QPrinter::A4);
    QPainter painter;

    if (! painter.begin(&printer)) { // failed to open file
        qWarning("failed to open file, is it writable?");
    }

    for(auto widget: widgets){
        if(widget){
             ui->pushButton_9->setVisible(false);
              ui->pushButton_4->setVisible(false);
            if(widget->width() > 0 && widget->height() >0 ){

                qreal xscale = printer.pageRect().width()/qreal(widget->width());
                qreal yscale = printer.pageRect().height()/qreal(widget->height());

                qreal scale = qMin(xscale, yscale);

                painter.translate(printer.paperRect().x() + printer.pageRect().width()/1.5,
                                  printer.paperRect().y() + printer.pageRect().height()/2.5);

                painter.scale(scale, scale);
                painter.translate(-widget->width()/1.5, -widget->height()/2.5);
                widget->render(&painter);
                painter.resetTransform();
                if(widget != widgets.last())
                    printer.newPage();
            }

        }
 ui->pushButton_9->setVisible(true);
  ui->pushButton_4->setVisible(true);
    }
    painter.end();
}
void MCALIB::on_pushButton_13_clicked()
{

    QList <QWidget *> widgets;
    widgets.append({ui->scrollAreaWidgetContents_9});

    QPrinter printer(QPrinter::HighResolution);

 const QString name = ui->lineEdit_362->text() +".pdf";
    printer.setOutputFormat(QPrinter::PdfFormat);
   printer.setOutputFileName(name);
   // printer.setOrientation(QPrinter::Landscape);
    // printer.setPaperSize(QPrinter::A4);
    QPainter painter;

    if (! painter.begin(&printer)) { // failed to open file
        qWarning("failed to open file, is it writable?");
    }

    for(auto widget: widgets){
        if(widget){
                  ui->pushButton_13->setVisible(false);
                  ui->pushButton_5->setVisible(false);
            if(widget->width() > 0 && widget->height() >0 ){

                qreal xscale = printer.pageRect().width()/qreal(widget->width());
                qreal yscale = printer.pageRect().height()/qreal(widget->height());

                qreal scale = qMin(xscale, yscale);

                painter.translate(printer.paperRect().x() + printer.pageRect().width()/1.5,
                                  printer.paperRect().y() + printer.pageRect().height()/2.5);

                painter.scale(scale, scale);
                painter.translate(-widget->width()/1.5, -widget->height()/2.5);
                widget->render(&painter);
                painter.resetTransform();
                if(widget != widgets.last())
                    printer.newPage();
            }

        }
     ui->pushButton_13->setVisible(true);
     ui->pushButton_5->setVisible(true);
    }
    painter.end();
}
void MCALIB::on_pushButton_14_clicked()
{

    QList <QWidget *> widgets;
    widgets.append({ui->scrollAreaWidgetContents_9});

    QPrinter printer(QPrinter::HighResolution);

 const QString name = ui->lineEdit_362->text() +".pdf";
    printer.setOutputFormat(QPrinter::PdfFormat);
   printer.setOutputFileName(name);
   // printer.setOrientation(QPrinter::Landscape);
    // printer.setPaperSize(QPrinter::A4);
    QPainter painter;

    if (! painter.begin(&printer)) { // failed to open file
        qWarning("failed to open file, is it writable?");
    }

    for(auto widget: widgets){
        if(widget){
                  ui->pushButton_14->setVisible(false);
                  ui->pushButton_8->setVisible(false);
            if(widget->width() > 0 && widget->height() >0 ){

                qreal xscale = printer.pageRect().width()/qreal(widget->width());
                qreal yscale = printer.pageRect().height()/qreal(widget->height());

                qreal scale = qMin(xscale, yscale);

                painter.translate(printer.paperRect().x() + printer.pageRect().width()/1.5,
                                  printer.paperRect().y() + printer.pageRect().height()/2.5);

                painter.scale(scale, scale);
                painter.translate(-widget->width()/1.5, -widget->height()/2.5);
                widget->render(&painter);
                painter.resetTransform();
                if(widget != widgets.last())
                    printer.newPage();
            }

        }
     ui->pushButton_14->setVisible(true);
     ui->pushButton_8->setVisible(true);
    }
    painter.end();
}
void MCALIB::on_pushButton_16_clicked()
{
    QPen pen;
    pen.setWidth(1);

     QVector<double> xval(101), yval(101);
     ui->customPlot->xAxis->setRange(0, 10);
     ui->customPlot->yAxis->setRange(-100, 100);
     ui->customPlot->yAxis->setOffset(10);
     int z;
     z=0;
      for (int j = 0; j<9; j++)
    {
          xval[j]=j;
          yval[j] = ui->tableWidget_3->model()->data(ui->tableWidget_3->model()->index(z, j)).toDouble();
          ui->customPlot->addGraph();
          ui->customPlot->graph(z)->setPen(QPen(Qt::blue));
          ui->customPlot->graph(z)->setData(xval, yval);
          ui->customPlot->replot();

      }

      z=1;
       for (int j = 0; j<9; j++)
     {
           xval[j]=j;
           yval[j] = ui->tableWidget_3->model()->data(ui->tableWidget_3->model()->index(z, j)).toDouble();

           ui->customPlot->addGraph();
           ui->customPlot->graph(z)->setPen(QPen(Qt::red));
           ui->customPlot->graph(z)->setData(xval, yval);
           ui->customPlot->replot();

       }


}
void MCALIB::on_pushButton_7_clicked()
{
    QPen pen;
    pen.setWidth(1);

     QVector<double> xval(101), yval(101);
     ui->customPlot->xAxis->setRange(0, 10);
     ui->customPlot->yAxis->setRange(-100, 100);
     ui->customPlot->yAxis->setOffset(10);
     int z;
     z=0;
      for (int j = 0; j<9; j++)
    {
          xval[j]=j;
          yval[j] = ui->tableWidget_9->model()->data(ui->tableWidget_9->model()->index(z, j)).toDouble();
          ui->customPlot->addGraph();
          ui->customPlot->graph(z)->setPen(QPen(Qt::blue));
          ui->customPlot->graph(z)->setData(xval, yval);
          ui->customPlot->replot();

      }

      z=1;
       for (int j = 0; j<9; j++)
     {
           xval[j]=j;
           yval[j] = ui->tableWidget_9->model()->data(ui->tableWidget_9->model()->index(z, j)).toDouble();

           ui->customPlot->addGraph();
           ui->customPlot->graph(z)->setPen(QPen(Qt::red));
           ui->customPlot->graph(z)->setData(xval, yval);
           ui->customPlot->replot();

       }
}

void MCALIB::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->pushButton_17->setVisible(true);
}
