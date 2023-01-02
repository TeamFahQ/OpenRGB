#include "OpenRGBNanoleafSettingsEntry.h"
#include "ui_OpenRGBNanoleafSettingsEntry.h"
#include "ResourceManager.h"
#include "NanoleafController.h"
#include "json.hpp"
using json = nlohmann::json;

using namespace Ui;

OpenRGBNanoleafSettingsEntry::OpenRGBNanoleafSettingsEntry(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpenRGBNanoleafSettingsEntryUi),
    paired(false)
{
    ui->setupUi(this);
}

OpenRGBNanoleafSettingsEntry::OpenRGBNanoleafSettingsEntry(QString a_address, int a_port) :
    OpenRGBNanoleafSettingsEntry(nullptr)
{
    address = a_address;
    port = a_port;
    const std::string location = address.toStdString()+":"+std::to_string(port);

    ui->IPValue->setText(address);
    ui->PortValue->setText(QString::fromStdString(std::to_string(a_port)));

    json nanoleaf_settings = ResourceManager::get()->GetSettingsManager()->GetSettings("NanoleafDevices");

    if(nanoleaf_settings["devices"].contains(location) &&
       nanoleaf_settings["devices"][location].contains("auth_token") &&
       nanoleaf_settings["devices"][location]["auth_token"].size())
    {
        paired = true;
        auth_token = nanoleaf_settings["devices"][location]["auth_token"];
        ui->AuthKeyValue->setText(QString::fromStdString(auth_token));
        ui->PairButton->hide();
    }
    else
    {
        ui->UnpairButton->hide();
    }
}

OpenRGBNanoleafSettingsEntry::~OpenRGBNanoleafSettingsEntry()
{
    delete ui;
}

void OpenRGBNanoleafSettingsEntry::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

void OpenRGBNanoleafSettingsEntry::on_PairButton_clicked()
{
    try
    {
        auth_token = NanoleafController::Pair(address.toStdString(), port);

        // Save auth token.
        const std::string location = address.toStdString()+":"+std::to_string(port);
        json nanoleaf_settings = ResourceManager::get()->GetSettingsManager()->GetSettings("NanoleafDevices");
        nanoleaf_settings["devices"][location]["ip"] = address.toStdString();
        nanoleaf_settings["devices"][location]["port"] = port;
        nanoleaf_settings["devices"][location]["auth_token"] = auth_token;
        ResourceManager::get()->GetSettingsManager()->SetSettings("NanoleafDevices", nanoleaf_settings);
        ResourceManager::get()->GetSettingsManager()->SaveSettings();

        // Update UI.
        paired = true;
        ui->AuthKeyValue->setText(QString::fromStdString(auth_token));
        ui->PairButton->hide();
        ui->UnpairButton->show();
    }
    catch(const std::exception& e)
    {
        paired = false;
        ui->AuthKeyValue->setText("PAIRING FAILED");
    }
}

void OpenRGBNanoleafSettingsEntry::on_UnpairButton_clicked()
{
    NanoleafController::Unpair(address.toStdString(), port, auth_token);

    const std::string location = address.toStdString()+":"+std::to_string(port);
    json nanoleaf_settings = ResourceManager::get()->GetSettingsManager()->GetSettings("NanoleafDevices");
    nanoleaf_settings["devices"].erase(location);
    ResourceManager::get()->GetSettingsManager()->SetSettings("NanoleafDevices", nanoleaf_settings);
    ResourceManager::get()->GetSettingsManager()->SaveSettings();

    paired = false;
    ui->AuthKeyValue->setText("");
    ui->PairButton->show();
    ui->UnpairButton->hide();
}

