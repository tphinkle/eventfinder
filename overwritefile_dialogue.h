#ifndef OVERWRITEFILE_DIALOGUE_H
#define OVERWRITEFILE_DIALOGUE_H

#include <QDialog>

class QString;

namespace Ui {
class OverwriteFile_Dialogue;
}

class OverwriteFile_Dialogue : public QDialog
{
    Q_OBJECT

public:
    explicit OverwriteFile_Dialogue(QWidget *parent = 0, QString filename = ".");
    ~OverwriteFile_Dialogue();
    bool overwritefile;

private slots:
    void buttonPressed();

private:
    Ui::OverwriteFile_Dialogue *ui;
    QString filename;



};

#endif // OVERWRITEFILE_DIALOGUE_H
