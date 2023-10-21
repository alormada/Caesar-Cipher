
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_encryptButton_clicked();

    void on_encryptiondecryptionComboBox_currentIndexChanged(int index);

    void on_plainTextToEncryptTextChanged();
    void on_plainTextEncryptedTextChanged();

    void on_lineEditShiftTextChanged();
    void on_decryptCheckBox_stateChanged(int state);



private:
    Ui::MainWindow *ui;
    bool isEncryptSelected;
    bool isDecryptSelected;
    bool isFirstCharEntered;


};

#endif // MAINWINDOW_H
