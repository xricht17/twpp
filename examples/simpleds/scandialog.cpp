#include "scandialog.hpp"
#include "ui_scandialog.h"

ScanDialog::ScanDialog(QWidget* parent, const TwGlue& glue) :
    QDialog(parent, Qt::MSWindowsFixedSizeDialogHint),
    ui(new Ui::ScanDialog), m_glue(glue)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(QStringLiteral("Simple TWPP data source"));
    setWindowIcon(QIcon(QStringLiteral(":/icon.bmp")));
}

ScanDialog::~ScanDialog()
{
    delete ui;
}

void ScanDialog::closeEvent(QCloseEvent* e)
{
    // attempt to close by window close button
    // the dialog must never close itself, the request must go through TWPP
    e->ignore();
    m_glue.m_cancel();
}

void ScanDialog::keyPressEvent(QKeyEvent *e){
    // Qt dialogs can be closed by ESC button, we dont like that
    if (e->key() == Qt::Key_Escape){
        e->ignore();
    } else {
        QDialog::keyPressEvent(e);
    }
}

void ScanDialog::on_scanButton_clicked()
{
    m_glue.m_scan();
}

void ScanDialog::on_cancelButton_clicked()
{
    m_glue.m_cancel();
}
