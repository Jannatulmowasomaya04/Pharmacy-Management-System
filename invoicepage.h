#ifndef INVOICEPAGE_H
#define INVOICEPAGE_H

#include <QWidget>
#include "datastructures.h"

class QLabel;
class QTableWidget;

class InvoicePage : public QWidget {
    Q_OBJECT
public:
    explicit InvoicePage(QWidget *parent = nullptr);
    ~InvoicePage();
    void setInvoiceDetails(const QList<CartItem>& cart);

signals:
    void startNewSaleClicked();
    void submitFeedbackClicked(); // !!! NEW !!!

private:
    QLabel *m_invoiceNumberLabel;
    QLabel *m_dateLabel;
    QTableWidget *m_itemsTable;
    QLabel *m_subtotalLabel;
    QLabel *m_taxLabel;
    QLabel *m_grandTotalLabel;
};
#endif // INVOICEPAGE_H
