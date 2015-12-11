#include "columnselect_dialogue.h"
#include "ui_columnselect_dialogue.h"


columnselect_dialogue::columnselect_dialogue(QWidget *parent, int columncount_):
    QDialog(parent), columncount(columncount_),
    ui(new Ui::columnselect_dialogue)
{


    buttons.resize(columncount);
    setWindowTitle("Choose data column");
    int windowwidth = 640;
    int windowheight = 320;

    int buttonwidth = 100;
    int buttonheight = 100;
    int buttonxpos;
    int buttonypos;
    QString colstring;

    for(int i = 0; i < columncount - 1; i++ )
    {

        buttons[i] = new QPushButton(this);

        buttons[i]->resize(buttonwidth, buttonheight);

        buttonxpos = (windowwidth - (columncount-1)*buttonwidth)*(i+1)/(columncount) + i*buttonwidth;
        //buttonypos = (int) (windowheight/2.0);
        buttonypos = (int)(windowheight/2.0 - buttonheight/2.0);
        buttons[i]->move(buttonxpos, buttonypos);

        colstring = QString::number(i + 1);
        buttons[i]->setText("column " + colstring);

        connect(buttons[i], SIGNAL(clicked()), this, SLOT(buttonPressed()));
    }

    ui->setupUi(this);

}

void columnselect_dialogue::buttonPressed()
{



    for(int i = 0; i < columncount - 1; i++ )
    {
        if( buttons[i] == QObject::sender() )
        {
            ycolumn = i + 1;
            this->close();
        }
    }
    return;
};

columnselect_dialogue::~columnselect_dialogue()
{
    delete ui;
}
