#ifndef PODROBNEE_H
#define PODROBNEE_H

#include <QDialog>

namespace Ui {
class Podrobnee;
}

class Podrobnee : public QDialog
{
    Q_OBJECT

public:
    explicit Podrobnee(QWidget *parent = nullptr);
    ~Podrobnee();

private:
    Ui::Podrobnee *ui;
};

#endif // PODROBNEE_H
