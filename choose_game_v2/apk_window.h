#ifndef APK_WINDOW_H
#define APK_WINDOW_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class apk_window;
}

class apk_window : public QDialog
{
    Q_OBJECT

public:
    explicit apk_window(QWidget *parent = nullptr);
    ~apk_window();

//запуск команды apk
    void start_apk();
//конец

private:
    Ui::apk_window *ui;
    QString adb = "cd /../../platform-tools/adb.exe";
};

#endif // APK_WINDOW_H
