#ifndef DASHBOARDPAGE_H
#define DASHBOARDPAGE_H

#include <QWidget>
#include <QMap>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QTableWidget>
#include <QSpinBox>
#include "datastructures.h"

class DashboardPage : public QWidget {
    Q_OBJECT
public:
    enum Mode { Guest, LoggedIn };

    explicit DashboardPage(QList<CartItem>* cart, QWidget *parent = nullptr);
    ~DashboardPage();

    void updateWelcomeMessage(const QString& username);
    void refreshTable();
    void setMode(Mode mode);

signals:
    void viewCartClicked();
    void logoutClicked();
    void loginRequired();

private slots:
    void onCategoryChanged(int index);
    void onAddToCartClicked();
    void onViewCartClicked();

private:
    void setupMockData();
    void populateCategories();
    void populateMedicines(const QString& category);

    // Widget Pointers
    QLabel *m_welcomeLabel;
    QPushButton *m_logoutButton;
    QComboBox *m_categoryComboBox;
    QTableWidget *m_medicineTableWidget;
    QSpinBox *m_quantitySpinBox;
    QWidget *m_addToCartSection;

    // Data
    QMap<QString, QList<Medicine>> m_medicineData;
    QList<CartItem>* m_cart;
    Mode m_currentMode;
};
#endif // DASHBOARDPAGE_H
