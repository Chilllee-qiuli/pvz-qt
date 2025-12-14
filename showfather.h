#ifndef SHOWFATHER_H
#define SHOWFATHER_H

#include <QDialog>

namespace Ui {
class ShowFather;
}

class ShowFather : public QDialog
{
    Q_OBJECT

public:
    explicit ShowFather(QWidget *parent = nullptr);
    ~ShowFather();

public slots:
    void on_pushButton_clicked();

private:
    Ui::ShowFather *ui;
};

#endif // SHOWFATHER_H
