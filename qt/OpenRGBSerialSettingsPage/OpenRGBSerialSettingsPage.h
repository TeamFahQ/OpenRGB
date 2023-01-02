#ifndef OPENRGBSERIALSETTINGSPAGE_H
#define OPENRGBSERIALSETTINGSPAGE_H

#include "ui_OpenRGBSerialSettingsPage.h"
#include <QWidget>

#include "OpenRGBSerialSettingsEntry.h"

namespace Ui {
class OpenRGBSerialSettingsPage;
}

class Ui::OpenRGBSerialSettingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit OpenRGBSerialSettingsPage(QWidget *parent = nullptr);
    ~OpenRGBSerialSettingsPage();

private slots:
    void changeEvent(QEvent *event);
    void on_AddSerialDeviceButton_clicked();

    void on_RemoveSerialDeviceButton_clicked();

    void on_SaveSerialConfigurationButton_clicked();

private:
    Ui::OpenRGBSerialSettingsPageUi *ui;
    std::vector<OpenRGBSerialSettingsEntry*> entries;

};

#endif // OPENRGBSERIALSETTINGSPAGE_H
