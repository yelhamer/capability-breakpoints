#ifndef GUI_H
#define GUI_H

#include <QTableWidget>
#include <QWidget>

class CapabilityView : public QWidget {
  public:
    explicit CapabilityView(QWidget* parent = nullptr);

    void refresh();

  private:
    QTableWidget* table = nullptr;

    void setupUi();
    void renameRule(int row);
    void showContextMenu(const QPoint& pos);
    void addRule();
    void deleteRule(int index);
};

void CreateCapabilityView();
void DestroyCapabilityView();
void RefreshCapabilityView();

#endif // GUI_H
