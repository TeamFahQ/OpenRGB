#include "OpenRGBPhilipsHueSettingsEntry.h"
#include "ui_OpenRGBPhilipsHueSettingsEntry.h"

using namespace Ui;

OpenRGBPhilipsHueSettingsEntry::OpenRGBPhilipsHueSettingsEntry(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpenRGBPhilipsHueSettingsEntryUi)
{
    ui->setupUi(this);
}

OpenRGBPhilipsHueSettingsEntry::~OpenRGBPhilipsHueSettingsEntry()
{
    delete ui;
}

void Ui::OpenRGBPhilipsHueSettingsEntry::on_UnpairButton_clicked()
{
    ui->UsernameValue->setText("");
    ui->ClientKeyValue->setText("");
}

