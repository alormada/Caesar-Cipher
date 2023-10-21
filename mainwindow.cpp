
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "CaesarCipher.h"
//#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plainTextToEncrypt->setPlaceholderText("Enter your message");

    ui->lineEditShift->setPlaceholderText("Shift");
    ui->decryptCheckBox->setHidden(true);

    connect(ui->plainTextToEncrypt, &QPlainTextEdit::textChanged, this, &MainWindow::on_plainTextToEncryptTextChanged);
    connect(ui->plainTextEncrypted, &QPlainTextEdit::textChanged, this, &MainWindow::on_plainTextEncryptedTextChanged);
    connect(ui->lineEditShift, &QLineEdit::textChanged, this, &MainWindow::on_lineEditShiftTextChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_encryptButton_clicked()
{
    QString plaintext = ui->plainTextToEncrypt->toPlainText();
    QString plaintext2 = ui->plainTextEncrypted->toPlainText();
    int shift = ui->lineEditShift->text().toInt();

    CaesarCipher cipher;
    std::string plaintextStd = plaintext.toStdString();
    std::string plaintextStd2 = plaintext2.toStdString();


    if (ui->encryptiondecryptionComboBox->currentIndex() == 0){
        std::string encryptedText = cipher.encrypt(plaintextStd, shift);
        ui->plainTextEncrypted->setPlainText(QString::fromStdString(encryptedText));
    }
    else if (ui->encryptiondecryptionComboBox->currentIndex() == 1)
    {
        if (ui->decryptCheckBox->isChecked())
        {
            std::string decryptedTextList = cipher.decryptAll(plaintextStd);
            ui->plainTextEncrypted->setPlainText(QString::fromStdString(decryptedTextList));
        }
        else
        {
            std::string decryptedText = cipher.decrypt(plaintextStd, shift);
            ui->plainTextEncrypted->setPlainText(QString::fromStdString(decryptedText));
        }

    }
    else if (ui->encryptiondecryptionComboBox->currentIndex() == 2)
    {
        cipher.encryptFile(plaintextStd, plaintextStd2, shift);
    }
    else if (ui->encryptiondecryptionComboBox->currentIndex() == 3)
    {
        cipher.decryptFile(plaintextStd, plaintextStd2, shift);
    }
}


void MainWindow::on_encryptiondecryptionComboBox_currentIndexChanged(int index)
{

    ui->plainTextToEncrypt->clear();
    ui->plainTextEncrypted->clear();
    ui->plainTextEncrypted->setPlaceholderText("");
    if (index == 0) {
        ui->encryptButton->setText("Encrypt");
        isEncryptSelected = true;
        isDecryptSelected = false;

        ui->decryptCheckBox->hide();
        ui->decryptCheckBox->setHidden(true);
        ui->decryptCheckBox->setEnabled(false);
        ui->lineEditShift->setEnabled(true);
        ui->lineEditShift->setVisible(true);
    } else if (index == 1) {
        ui->encryptButton->setText("Decrypt");
        isEncryptSelected = false;
        isDecryptSelected = true;
        ui->decryptCheckBox->setHidden(false);
        ui->decryptCheckBox->setEnabled(true);
        ui->decryptCheckBox->show();
        ui->decryptCheckBox->setChecked(false);
        ui->lineEditShift->setEnabled(true);
    } else if (index == 2) {
        on_plainTextToEncryptTextChanged();
        on_plainTextEncryptedTextChanged();
        ui->encryptButton->setText("Encrypt");
        ui->decryptCheckBox->hide();
        ui->decryptCheckBox->setHidden(true);
        ui->decryptCheckBox->setEnabled(false);
        ui->lineEditShift->setEnabled(true);
        ui->lineEditShift->setVisible(true);
    } else if (index == 3) {
        on_plainTextToEncryptTextChanged();
        on_plainTextEncryptedTextChanged();
        ui->encryptButton->setText("Decrypt");
        ui->decryptCheckBox->setHidden(true);
        ui->decryptCheckBox->setEnabled(false);
        ui->lineEditShift->setEnabled(true);
    }

}

void MainWindow::on_plainTextEncryptedTextChanged()
{
    QString text = ui->plainTextEncrypted->toPlainText();


    if (text.isEmpty()) {

        ui->plainTextEncrypted->setPlaceholderText("Enter your destination filename");
    } else {

        ui->plainTextEncrypted->setPlaceholderText("");
    }
}

void MainWindow::on_plainTextToEncryptTextChanged()
{
    QString text = ui->plainTextToEncrypt->toPlainText();


    if (text.isEmpty()) {
        if (ui->encryptiondecryptionComboBox->currentIndex() == 0 || ui->encryptiondecryptionComboBox->currentIndex() == 1)
        {
            ui->plainTextToEncrypt->setPlaceholderText("Enter your message");
        }
        else
        {
            ui->plainTextToEncrypt->setPlaceholderText("Enter your source filename");
        }

    } else {

        ui->plainTextToEncrypt->setPlaceholderText("");
    }
}


void MainWindow::on_lineEditShiftTextChanged()
{
    QString text = ui->lineEditShift->text();


    if (text.isEmpty()) {
        ui->lineEditShift->setPlaceholderText("Shift");
    } else {

        ui->lineEditShift->setPlaceholderText("");
    }

}

void MainWindow::on_decryptCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked)
    {
        ui->lineEditShift->setEnabled(false);
        ui->lineEditShift->setVisible(false);
    }
    else
    {
        ui->lineEditShift->setEnabled(true);
        ui->lineEditShift->setVisible(true);
    }
}



