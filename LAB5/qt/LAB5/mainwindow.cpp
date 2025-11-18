#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Инициализация базы данных
    if (!initDatabase()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось инициализировать базу данных!");
        return;
    }

    // Настройка таблицы
    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"ID", "Исходная строка", "Обработанная строка"});
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    // Загрузка данных при запуске
    refreshTable();
}

MainWindow::~MainWindow()
{
    // Закрытие соединения с базой данных
    if (db.isOpen()) {
        db.close();
    }
    delete ui;
}

// Инициализация базы данных SQLite
bool MainWindow::initDatabase()
{
    // Создание соединения с базой данных SQLite
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("documents.db");

    // Открытие базы данных
    if (!db.open()) {
        qDebug() << "Ошибка открытия базы данных:" << db.lastError().text();
        return false;
    }

    // Создание таблицы если она не существует
    return createTable();
}

// Создание таблицы в базе данных
bool MainWindow::createTable()
{
    QSqlQuery query;

    // SQL запрос для создания таблицы
    QString createTableQuery =
        "CREATE TABLE IF NOT EXISTS documents ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "original_text TEXT NOT NULL, "
        "processed_text TEXT NOT NULL, "
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
        ")";

    if (!query.exec(createTableQuery)) {
        qDebug() << "Ошибка создания таблицы:" << query.lastError().text();
        return false;
    }

    return true;
}

// Преобразование строки в верхний регистр
QString MainWindow::toUpperCase(const QString& text)
{
    return text.toUpper();
}

// Слот для добавления новой строки в базу данных
void MainWindow::on_addButton_clicked()
{
    QString originalText = ui->originalTextEdit->toPlainText().trimmed();

    // Проверка на пустую строку
    if (originalText.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Введите текст для обработки!");
        return;
    }

    // Преобразование в верхний регистр
    QString processedText = toUpperCase(originalText);

    // Вставка данных в базу данных
    QSqlQuery query;
    query.prepare("INSERT INTO documents (original_text, processed_text) VALUES (?, ?)");
    query.addBindValue(originalText);
    query.addBindValue(processedText);

    if (query.exec()) {
        // Очистка поля ввода
        ui->originalTextEdit->clear();

        // Обновление таблицы
        refreshTable();

        // Показать обработанный текст
        ui->processedTextLabel->setText("Обработанный текст: " + processedText);

        QMessageBox::information(this, "Успех", "Запись успешно добавлена в базу данных!");
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось добавить запись: " + query.lastError().text());
    }
}

// Слот для удаления выбранной строки
void MainWindow::on_deleteButton_clicked()
{
    // Получение выбранной строки в таблице
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();

    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Выберите запись для удаления!");
        return;
    }

    // Получение ID выбранной записи
    int row = selectedIndexes.first().row();
    int id = model->item(row, 0)->text().toInt();

    // Подтверждение удаления
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение",
                                  "Вы уверены, что хотите удалить выбранную запись?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("DELETE FROM documents WHERE id = ?");
        query.addBindValue(id);

        if (query.exec()) {
            refreshTable();
            ui->processedTextLabel->setText("Запись удалена");
            QMessageBox::information(this, "Успех", "Запись успешно удалена!");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось удалить запись: " + query.lastError().text());
        }
    }
}

// Слот для очистки всей базы данных
void MainWindow::on_clearButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение",
                                  "Вы уверены, что хотите очистить всю базу данных?\n"
                                  "Это действие нельзя отменить!",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QSqlQuery query;

        if (query.exec("DELETE FROM documents")) {
            // Сброс автоинкремента
            query.exec("DELETE FROM sqlite_sequence WHERE name='documents'");

            refreshTable();
            ui->processedTextLabel->setText("База данных очищена");
            QMessageBox::information(this, "Успех", "База данных успешно очищена!");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось очистить базу данных: " + query.lastError().text());
        }
    }
}

// Обновление данных в таблице
void MainWindow::refreshTable()
{
    // Очистка модели
    model->removeRows(0, model->rowCount());

    // Выборка данных из базы данных
    QSqlQuery query("SELECT id, original_text, processed_text FROM documents ORDER BY created_at DESC");

    int row = 0;
    while (query.next()) {
        // Добавление данных в модель
        model->setItem(row, 0, new QStandardItem(query.value(0).toString()));
        model->setItem(row, 1, new QStandardItem(query.value(1).toString()));
        model->setItem(row, 2, new QStandardItem(query.value(2).toString()));
        row++;
    }

    // Настройка ширины столбцов
    ui->tableView->resizeColumnsToContents();

    // Обновление статуса
    ui->statusLabel->setText(QString("Всего записей: %1").arg(row));
}
