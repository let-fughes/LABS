#ifndef PODROBNEE_H
#define PODROBNEE_H

#include <QWidget>

namespace Ui {
class Podrobnee;
}

class Podrobnee : public QWidget
{
    Q_OBJECT

public:
    explicit Podrobnee(QWidget *parent = nullptr);
    ~Podrobnee();

private:
    Ui::Podrobnee *ui;
};

#endif // PODROBNEE_H
