#ifndef WINMAIN_H
#define WINMAIN_H

#include <DMainWindow>
#include <DTabWidget>

DWIDGET_BEGIN_NAMESPACE
class DLineEdit;
class DSpinBox;
//class DCheckBox; 奇怪, 怎么还不能声明了? 已经知道了
//class DComboBox;
DWIDGET_END_NAMESPACE

class SettingModel;

DWIDGET_USE_NAMESPACE

class WinMain : public DMainWindow
{
    Q_OBJECT
public:
    WinMain(SettingModel *model, QWidget *parent = 0);

    void init();
    inline DLineEdit* getUpload(){return m_lineUpload;}

signals:
    void sigLabUpload(QString lineUpload);
    void sigLabDown(QString lineUpload);
    void sigLabCpu(QString lineUpload);
    void sigLabMemory(QString lineUpload);
    void sigUpAndDown(Qt::CheckState check);

private:
    DTabWidget *m_tab;

    DLineEdit* m_lineUpload;
    DLineEdit* m_lineDown;
    DLineEdit* m_lineCpu;
    DLineEdit* m_lineMemory;
    DCheckBox* m_checkUpAndDown;
    DCheckBox* m_checkMouseTips;
    DSpinBox*  m_spinDecimalsNum;
    DSpinBox*  m_spinInterval;
    DComboBox* m_comSensitive;

    SettingModel *m_model;
};

#endif // WINMAIN_H
