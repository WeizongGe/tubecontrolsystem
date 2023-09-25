#ifndef FILTERSETTING_H
#define FILTERSETTING_H

#include <QGroupBox>
#include "model/tubeControlSystemApp.h"

namespace Ui {
class FilterSetting;
}

class FilterSetting : public QGroupBox
{
    Q_OBJECT

public:
    explicit FilterSetting(QWidget *parent = nullptr);
    ~FilterSetting();

private:
    Ui::FilterSetting *ui;
    tubeControlSystemApp* mApp;
};

#endif // FILTERSETTING_H
