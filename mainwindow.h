#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMessageBox>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>

#include <QTextCursor>
#include <QTextBlock>

#include <QString>

#include "documentstate.h"
#include "textfile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionExit_triggered();

    void on_actionFont_triggered();

    void on_actionUndo_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionDelete_triggered();

    void on_actionSellect_All_triggered();

    void on_actionFind_triggered();

    void on_actionGo_to_triggered();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

    DocumentState *documentState;

    void clearDocument();
    void doSaveChanges();
};

#endif // MAINWINDOW_H
