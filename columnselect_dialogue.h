#ifndef COLUMNSELECT_DIALOGUE_H
#define COLUMNSELECT_DIALOGUE_H

#include <QMainWindow>
#include <QDialog>
#include <QPushButton>


namespace Ui {
class columnselect_dialogue;
}

class columnselect_dialogue : public QDialog
{
    Q_OBJECT

public:
    explicit columnselect_dialogue(QWidget *parent = 0, int columncount_ = 2 );
    ~columnselect_dialogue();
    int columncount;
    bool columnselected;
    int column;
    int ycolumn;
    std::vector<QPushButton*> buttons;

    void setColumncount(int columncount_);
    void setButtontitles(std::vector<QString> columntitlelist_);

private slots:
    void buttonPressed();

private:
    Ui::columnselect_dialogue *ui;
};

#endif // COLUMNSELECT_DIALOGUE_H
