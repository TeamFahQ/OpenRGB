#include "OpenRGBQMKORGBSettingsEntry.h"
#include "ui_OpenRGBQMKORGBSettingsEntry.h"

using namespace Ui;

OpenRGBQMKORGBSettingsEntry::OpenRGBQMKORGBSettingsEntry(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpenRGBQMKORGBSettingsEntryUi)
{
    ui->setupUi(this);
}

OpenRGBQMKORGBSettingsEntry::~OpenRGBQMKORGBSettingsEntry()
{
    delete ui;
}
