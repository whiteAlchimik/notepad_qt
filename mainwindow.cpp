#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    documentState = new DocumentState();

    QObject::connect(ui->textEdit, SIGNAL(textChanged()),
                     documentState, SLOT(slotTextChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete documentState;
}

void MainWindow::on_actionNew_triggered()
{
    if(!documentState->isChangesSaved())
    {
        doSaveChanges();
    }
    else
    {
        clearDocument();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    this->on_actionNew_triggered();

    documentState->setPathToTheFile(QFileDialog::getOpenFileName(nullptr,tr("Open File")));

    ui->textEdit->setText(TextFile::loadFile(documentState->getPathToTheFile()));

    documentState->slotChangesSaved();
}

void MainWindow::on_actionSave_triggered()
{   
    if(documentState->getPathToTheFile().isEmpty())
    {
        documentState->setPathToTheFile(QFileDialog::getSaveFileName(nullptr, tr("Save File"),
                                                                     "*.txt", tr("Text files (*.txt)")));
    }

    TextFile::saveFile(documentState->getPathToTheFile(), ui->textEdit->toPlainText());

    documentState->slotChangesSaved();
}

void MainWindow::on_actionSave_as_triggered()
{
    documentState->setPathToTheFile(QFileDialog::getSaveFileName(nullptr,
                                                                 tr("Save File"),
                                                                 "*.txt",
                                                                 tr("Text files (*.txt)")));

    TextFile::saveFile(documentState->getPathToTheFile(), ui->textEdit->toPlainText());

    documentState->slotChangesSaved();
}

void MainWindow::on_actionExit_triggered()
{
    this->on_actionNew_triggered();

    this->close();
}

void MainWindow::on_actionFont_triggered()
{
    bool ok;
    ui->textEdit->setFont(QFontDialog::getFont(&ok));
}

void MainWindow::clearDocument()
{
    ui->textEdit->clear();
    documentState->clear();
}

void MainWindow::doSaveChanges()
{
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    switch(msgBox.exec())
    {
    case QMessageBox::Save:
    {
        if(documentState->getPathToTheFile().isEmpty())
        {
            documentState->setPathToTheFile(QFileDialog::getSaveFileName(nullptr, tr("Save File"),
                                                                         "*.txt", tr("Text files (*.txt)")));
        }

        TextFile::saveFile(documentState->getPathToTheFile(), ui->textEdit->toPlainText());
        ui->textEdit->clear();
        documentState->clear();
        break;
    }
    case QMessageBox::Discard:
    {
        clearDocument();
        break;
    }
    default:
        break;
    }
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionDelete_triggered()
{
    ui->textEdit->textCursor().deletePreviousChar();
}

void MainWindow::on_actionSellect_All_triggered()
{
    ui->textEdit->selectAll();
}

void MainWindow::on_actionFind_triggered()
{
    QTextCursor cursor(ui->textEdit->textCursor());
    cursor.movePosition(QTextCursor::Start);
    ui->textEdit->setTextCursor(cursor);

    QString text;

    while(true)
    {
        bool ok;
        text = QInputDialog::getText(this,
                                             tr("Find"),
                                             tr("Find what:"),
                                             QLineEdit::Normal,
                                             text,
                                             &ok,
                                             Qt::Window);
        if(ok && !text.isEmpty())
        {
            ui->textEdit->find(text);
        }
        else
        {
            break;
        }
    }
}

void MainWindow::on_actionGo_to_triggered()
{
    bool ok = true;
    int line = QInputDialog::getInt(this,
                                    tr("Go to line"),
                                    tr("Line number:"),
                                    0,
                                    0,
                                    2147483647,
                                    1
                                    &ok);
    if(ok && line <= ui->textEdit->document()->lineCount())
    {
        QTextCursor cursor(ui->textEdit->document()->findBlockByLineNumber(line-1)); // ln-1 because line number starts from 0
        ui->textEdit->setTextCursor(cursor);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    this->on_actionExit_triggered();
    QMainWindow::closeEvent(event);
}
