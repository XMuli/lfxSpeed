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

DWIDGET_USE_NAMESPACE

class WinMain : public DMainWindow
{
public:
    WinMain(QWidget *parent = 0);

    void init();

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
};

#endif // WINMAIN_H
