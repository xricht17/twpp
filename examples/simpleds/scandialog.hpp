#ifndef SCANDIALOG_HPP
#define SCANDIALOG_HPP

#include <QDialog>
#include <QCloseEvent>
#include "twglue.hpp"

namespace Ui {
class ScanDialog;
}

class ScanDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScanDialog(QWidget* parent, const TwGlue& glue);
    ~ScanDialog() override;

protected:
    void closeEvent(QCloseEvent* e) override;
    void keyPressEvent(QKeyEvent *e) override;

private slots:
    void on_scanButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ScanDialog *ui;
    TwGlue m_glue;

};

#endif // SCANDIALOG_HPP
