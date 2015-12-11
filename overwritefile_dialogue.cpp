#include "overwritefile_dialogue.h"
#include "ui_overwritefile_dialogue.h"

OverwriteFile_Dialogue::OverwriteFile_Dialogue(QWidget *parent, QString filename_) :
    QDialog(parent), filename(filename_),
    ui(new Ui::OverwriteFile_Dialogue)
{

    ui->setupUi(this);

    setWindowTitle("Overwrite file");

    ui->OverwriteFile_Label->setText("Overwrite file\n" + filename_ + "\n?");
    ui->OverwriteFile_Label->setReadOnly(true);
    ui->OverwriteFile_Label->viewport()->setAutoFillBackground(false);
    connect(ui->Yes, SIGNAL(clicked()), this, SLOT(buttonPressed()));
    connect(ui->No, SIGNAL(clicked()), this, SLOT(buttonPressed()));

}

OverwriteFile_Dialogue::~OverwriteFile_Dialogue()
{
    delete ui;
}

void OverwriteFile_Dialogue::buttonPressed()
{
    if( ui->Yes == QObject::sender() )
    {
        overwritefile = true;
    }

    else
    {
        overwritefile = false;
    }

    this->close();
    return;
}
