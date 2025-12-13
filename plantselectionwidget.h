// plantselectionwidget.h
#ifndef PLANTSELECTIONWIDGET_H
#define PLANTSELECTIONWIDGET_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVector>
#include <QString>
#include <QLabel>

class PlantSelectionWidget : public QDialog
{
    Q_OBJECT
public:
    explicit PlantSelectionWidget(const QVector<QString>& allPlants, QWidget *parent = nullptr);
    QVector<QString> getSelectedPlants() const;

private slots:
    void onPlantButtonClicked();
    void onOkButtonClicked();
    void onCancelButtonClicked();

private:
    QVector<QString> allPlants;
    QVector<QPushButton*> topButtons;
    QVector<QPushButton*> bottomButtons;
    QVector<QString> selectedPlants;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLabel *statusLabel;
};


#endif // PLANTSELECTIONWIDGET_H
