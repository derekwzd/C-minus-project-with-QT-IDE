#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QSyntaxHighlighter>

namespace Ui {
class MainWindow;
}



class mySyntaxHighLighter: public QSyntaxHighlighter
{

public:
    mySyntaxHighLighter(QTextDocument* document):
        QSyntaxHighlighter(document)
    {
    }

    ~ mySyntaxHighLighter()
    {}

    void highlightBlock(const QString &text)
    {

        enum { NormalState = -1, CStyleComment };

        int state = previousBlockState();
        int start = 0;

        for (int i = 0; i < text.length(); ++i)
        {

            if (state == CStyleComment)
            {
                if (text.mid(i, 2) == "*/")
                {
                    state = NormalState;
                    setFormat(start, i - start + 2, Qt::gray);
                }
            }
            else
            {
                if (text.mid(i, 2) == "/*")
                {
                    start = i;
                    state = CStyleComment;
                }
                else if(text.mid(i, 4) == "else" && ( text.mid(i+4,1) == " " || text.mid(i+4,1) == "{" ))
                {
                    setFormat(i, 4, Qt::blue);
                }
                else if(text.mid(i, 2) == "if" && (text.mid(i+2,1) == " " || text.mid(i + 2, 1) == "("))
                {
                    setFormat(i, 2, Qt::blue);
                }
                else if(text.mid(i, 3) == "int" && (text.mid(i+3, 1) == " "))
                {
                    setFormat(i, 3, Qt::blue);
                }
                else if(text.mid(i, 6) == "return" && (text.mid(i + 6, 1) == " "))
                {
                    setFormat(i, 6, Qt::blue);
                }
                else if(text.mid(i, 5) == "while" && (text.mid(i + 5, 1) == " " || text.mid(i + 5, 1) == "("))
                {
                    setFormat(i,5, Qt::blue);
                }
                else if(text.mid(i, 4) == "void" && (text.mid(i + 4, 1) == " "))
                {
                    setFormat(i, 4, Qt::blue);
                }
            }
        }
    }
};







class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    mySyntaxHighLighter* highlighter;
    QString filename;
    QString compiler;
    QString tm;
private:
    Ui::MainWindow *ui;
public slots:
    void selectfile();
    int compile();
    void run();
    void savefile();
};

#endif // MAINWINDOW_H
