#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
    class InfoDialog;
}

class InfoDialog : public QDialog{
    Q_OBJECT

    public:
        explicit InfoDialog(QWidget *parent = 0);
        ~InfoDialog();
        void SetMessage(QString Message);
        void ShowWindow();

    private:
        Ui::InfoDialog *ui;
        QTimer timer;
};

#endif // INFODIALOG_H
