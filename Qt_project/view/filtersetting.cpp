#include "filtersetting.h"
#include "ui_filtersetting.h"

FilterSetting::FilterSetting(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::FilterSetting),
    mApp(tubeControlSystemApp::instance())
{
    ui->setupUi(this);
}

FilterSetting::~FilterSetting()
{
    delete ui;
}
