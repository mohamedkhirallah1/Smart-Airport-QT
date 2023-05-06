#ifndef PDF_H
#define PDF_H

#include <QMainWindow>

namespace Ui {
class pdf;
}

class pdf : public QMainWindow
{
    Q_OBJECT

public:
    explicit pdf(QWidget *parent = nullptr);
    ~pdf();
private slots :
    void on_pushButton_clicked();

private:
    Ui::pdf *ui;
};

#endif // PDF_H
