#ifndef CARTPAGE_H
#define CARTPAGE_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include "datastructures.h"

class CartPage : public QWidget {
    Q_OBJECT
public:
    explicit CartPage(QList<CartItem>* cart, QWidget *parent = nullptr);
    ~CartPage();
    void updateCartView();

signals:
    void backToShopClicked();
    void purchaseConfirmed();

private:
    void calculateTotals();

    QTableWidget *m_cartTableWidget;
    QLabel *m_subtotalLabel;
    QLabel *m_taxLabel;
    QLabel *m_grandTotalLabel;

    QList<CartItem>* m_cart;
};
#endif // CARTPAGE_H
