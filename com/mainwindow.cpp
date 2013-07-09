#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextStream>
#include <QProcess>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    highlighter = new mySyntaxHighLighter(ui->textEdit->document());
    compiler = "./cmc ";
    tm = "./tm ";
}

MainWindow::~MainWindow()
{
    delete highlighter;
    delete ui;
}

int MainWindow::compile()
{
    savefile();
    ui->label->setText("Compiling");
    QString command = compiler + "< " + filename + " >" + filename + ".cminus 2>&1";
    system(command.toLocal8Bit().data());
    ui->label->setText("Done");
    QFile file(filename + ".cminus");
    file.open( QIODevice::ReadOnly);
    QString strFileContent;
    strFileContent = file.readAll();
    ui->textEdit_2->clear();
    ui->textEdit_2->setText(strFileContent);
    file.close();
}

void MainWindow::savefile()
{
    if(filename.length()!=0)
    {
        QFile file(filename);
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);
        out<<ui->textEdit->toPlainText();
    }
    else
    {
        QString fn = QFileDialog::getSaveFileName (this, tr("另存为..."), ".",tr(" (*.c)"));
        if (!fn.isEmpty())
        {
            if(!fn.endsWith(".c", Qt::CaseInsensitive))
            {
                filename=fn+".c";
            }
            else
            {
                filename=fn;
            }
            savefile ();
        }
    }
    ui->label->setText(filename);
}

void MainWindow::run()
{
    QString command1 = "xterm -e ";
    QString command11 = "konsole -e ";
    QString command2 = "./tm ";
    QProcess p1;
    if(!p1.startDetached(command11+command2+filename+".cminus"))
        p1.startDetached(command1+command2+filename+".cminus");
    p1.waitForFinished();
}




void MainWindow::selectfile()
{
   filename = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Files(*.txt *.c)"));
   if(filename.length() == 0)
   {
       QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
   }
   QFile file(filename);
   file.open( QIODevice::ReadOnly);
   QString strFileContent;
   strFileContent = file.readAll();
   ui->textEdit->clear();
   ui->textEdit->setText(strFileContent);
   file.close();
}
