#ifndef MCALIB_H
#define MCALIB_H

#include <QMainWindow>
#include<QUndoStack>

class QUndoStack;
class QAction;
class QActionGroup;
class QLabel;
class QMenu;


namespace Ui {
class MCALIB;
}

class MCALIB : public QMainWindow
{
    Q_OBJECT

public:
    QString filename;
    //QString filename1;
    void saveToFile();
    explicit MCALIB(QWidget *parent = nullptr);
    ~MCALIB();

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU

private slots:

    void makePlot();

    void on_import_2_clicked();


    void newFile();
    //void fileOpen();
    void open();
    void save();
    void print();
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void bold();
    void italic();
    void leftAlign();
    void rightAlign();
    void justify();
    void center();
    void setLineSpacing();
    void setParagraphSpacing();
    void about();
    void aboutQt();


    void on_pushButton_clicked();

    void on_pushButton_78_clicked();

    void on_pushButton_2_clicked();

    //void on_import_2_clicked();

    void on_pushButton_3_clicked();


    void tablecolum();

    void tablecolum1();


    void on_pushButton_35_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_82_clicked();

    void on_pushButton_5_clicked();



    void on_pushButton_6_clicked();

    void on_import_3_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

    void on_import_c_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_7_clicked();



    void on_pushButton_17_clicked();

private:
    Ui::MCALIB *ui;

    void createActions();
    void createMenus();

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;
    QActionGroup *alignmentGroup;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *boldAct;
    QAction *italicAct;
    QAction *leftAlignAct;
    QAction *rightAlignAct;
    QAction *justifyAct;
    QAction *centerAct;
    QAction *setLineSpacingAct;
    QAction *setParagraphSpacingAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QLabel *infoLabel;
     QAction *action;
    QUndoStack *m_undo_stack;
};

#endif // MCALIB_H
